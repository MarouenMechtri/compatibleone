/* ------------------------------------------------------------------- */
/*  ACCORDS PLATFORM                                                   */
/*  (C) 2011 by Iain James Marshall (Prologue) <ijm667@hotmail.com>    */
/* --------------------------------------------------------------------*/
/*  This is free software; you can redistribute it and/or modify it    */
/*  under the terms of the GNU Lesser General Public License as        */
/*  published by the Free Software Foundation; either version 2.1 of   */
/*  the License, or (at your option) any later version.                */
/*                                                                     */
/*  This software is distributed in the hope that it will be useful,   */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of     */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   */
/*  Lesser General Public License for more details.                    */
/*                                                                     */
/*  You should have received a copy of the GNU Lesser General Public   */
/*  License along with this software; if not, write to the Free        */
/*  Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA */
/*  02110-1301 USA, or see the FSF site: http://www.fsf.org.           */
/* --------------------------------------------------------------------*/
#ifndef	_proccios_c
#define	_proccios_c

#include "azclient.h"
#include "cordslang.h"
#include "cosacsctrl.h"
#include "stdnode.h"

#define	_AZURE_STATUS_POLL	5

/* ---------------------------------------------------------------------------------- */
/* if ((status = az_initialise_client( user, pass, host, agent, version, tls )) != 0) */
/* ---------------------------------------------------------------------------------- */
private	struct	az_config * resolve_az_configuration( char * sptr )
{
	struct	occi_kind_node * nptr;
	struct	az_config * pptr=(struct az_config *) 0;
	struct	occi_kind_node  * occi_first_az_config_node();
	for (	nptr = occi_first_az_config_node();
		nptr != (struct occi_kind_node *) 0;
		nptr = nptr->next )
	{
		if (!( pptr = nptr->contents ))
			continue;
		else if (!( pptr->name ))
			continue;
		else if (!( strcmp( pptr->name, sptr ) ))
			return( pptr );
	}
	return((struct az_config *) 0);
}


/*	--------------------------------------------------------	*/
/* 	 u s e _ w i n d o w s a z u r e _ c o n f i g u r a t i o n 		*/
/*	--------------------------------------------------------	*/
private	int	use_windowsazure_configuration( char * sptr )
{
	struct	az_config * pptr;
	int	status;

	if (!( pptr = resolve_az_configuration( sptr )))
	 	return( 404 );

	else if ((status = az_initialise_client( 
			pptr->user, pptr->password, 
			pptr->host, pptr->agent, pptr->version, pptr->tls,
			pptr->namespace, pptr->subscription )) != 0)
		return(status);
	else if (!( pptr->hostedservice ))
		return(0);
	else if ((status = az_initialise_service( pptr->hostedservice )) != 0)
		return( status );
	else	return( 0 );
}

/*	--------------------------------------------------------	*/
/* 	       r e s e t _ w i n d o w s a z u r e _ s e r v e r		*/
/*	--------------------------------------------------------	*/
private	int	reset_windowsazure_server( struct windowsazure * pptr )
{
	if ( pptr )
	{
		if ( pptr->number ) pptr->number = liberate( pptr->number );
		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if ( pptr->reference ) pptr->reference = liberate( pptr->reference );
		if ( pptr->rootpass ) pptr->rootpass = liberate( pptr->rootpass );
		if ( pptr->publicaddr ) pptr->publicaddr = liberate( pptr->publicaddr );
		if ( pptr->privateaddr ) pptr->privateaddr = liberate( pptr->privateaddr );
		pptr->number = allocate_string("");
		pptr->hostname = allocate_string("");
		pptr->rootpass  = allocate_string("");
		pptr->publicaddr = allocate_string("");
		pptr->privateaddr = allocate_string("");
		pptr->state = _OCCI_IDLE;
	}
	return(0);
}

/*	--------------------------------------------------------	*/
/* 	     c o n n e c t _ w i n d o w s a z u r e _ i m a g e  		*/
/*	--------------------------------------------------------	*/
private	int	connect_windowsazure_image( struct az_response * rptr,struct windowsazure * pptr )
{
	struct	az_response * zptr;
	struct	az_response * yptr;
	char *	vptr;
	if (!( pptr ))
		return( 118 );
	else if (!( vptr = json_atribut( rptr->jsonroot, "id") ))
	{
		reset_windowsazure_server( pptr );
		return( 27 );
	}
	else
	{
		if ( pptr->image )
			pptr->image = liberate( pptr->image );
		if (!( pptr->image = allocate_string( vptr ) ))
		{
			reset_windowsazure_server( pptr );
			return( 27 );
		}
		autosave_windowsazure_nodes();
		/* ----------------------------------------------------- */
		/* we must now await ACTIVE status to be able to collect */
		/* the final identification information to complete the  */
		/* windowsazure provisioning request.			 */
		/* ----------------------------------------------------- */
		yptr = rptr;
		zptr = (struct az_response *) 0;
		while (1)
		{
			if (!( vptr = json_atribut( yptr->jsonroot, "status" )))
			{
				reset_windowsazure_server( pptr );
				return( 27 );
			}
			else if (!( strcmp( vptr, "SAVING" )))
			{
				sleep(1);
				if ( zptr )
					zptr = liberate_az_response( zptr );
				if (!( zptr = az_get_image( pptr->image )))
				{
					reset_windowsazure_server( pptr );
					return( 555 );
				}
				else	yptr = zptr;
			}
			else if (!( strcmp( vptr, "ACTIVE" )))
				break;
		}
		return( 0 );
	}
}

/*	-------------------------------------------------------		*/
/*	c h e c k _ w i n d o w s a z u r e _ o p e r a t i o n		*/
/*	-------------------------------------------------------		*/
private	int	check_windowsazure_operation( struct az_response * zptr )
{
	struct	rest_header * hptr;
	struct	xml_element * eptr;
	char	buffer[2048];
	int	status;

	if ((!( zptr ))
	||  (!( zptr->response )))
		return(599);

	switch((status = zptr->response->status))
	{
	case	200	:	/* OK 		*/
		zptr = liberate_az_response( zptr );
		return(200);

	case	201	:	/* Created 	*/
	case	202	:	/* Accepted 	*/
		/* locate a request id header 	*/
		if (!( hptr = rest_resolve_header( zptr->response->first, "x-ms-request-id" ) ))
		{
			zptr = liberate_az_response( zptr );
			return(200);
		}
		else if (!( hptr->value ))
		{
			zptr = liberate_az_response( zptr );
			return(200);
		}
		else
		{
			strcpy( buffer, hptr->value );
			break;
		}
	default		:
		zptr = liberate_az_response( zptr );
		return( status );
	}

	while(1)
	{
		zptr = liberate_az_response( zptr );
		if (!( zptr = az_get_operation_status( buffer )))
			return( 518 );
		else if (!( zptr->response ))
		{
			zptr = liberate_az_response( zptr );
			return( 501 );
		}
		else if ((zptr->response->status) != 200 )
		{
			zptr = liberate_az_response( zptr );
			return( status );
		}
		else if (!( zptr->xmlroot ))
		{
			zptr = liberate_az_response( zptr );
			return( 502 );
		}
		else if ((!( eptr = document_element( zptr->xmlroot, "Status" ) ))
		     ||  (!( eptr->value )))
		{
			zptr = liberate_az_response( zptr );
			return( 503 );
		}
		else if ((!( strcasecmp( eptr->value, "SUCCEEDED" )))
		     ||  (!( strcasecmp( eptr->value, "SUCCESS"   ))))
			break;
		else if ((!( strcasecmp( eptr->value, "FAILED"    )))
		     ||  (!( strcasecmp( eptr->value, "FAILURE"   ))))
			break;
		else if (!( strcasecmp( eptr->value, "INPROGRESS" )))
		{
			sleep( _AZURE_STATUS_POLL );
			continue;
		}
		else	continue;
	}
	/* ---------------------------------------------------------- */
	/* recover and return the status code of the original request */
	/* ---------------------------------------------------------- */
	if ((!( eptr = document_element( zptr->xmlroot, "HttpStatusCode" ) ))
	||  (!( eptr->value ))
	||  (!( status = atoi( eptr->value ) )))
	{
		zptr = liberate_az_response( zptr );
		return( 504 );
	}
	else
	{
		zptr = liberate_az_response( zptr );
		return( status );
	}
	
}


/*	--------------------------------------------------------	*/
/* 	 c o n n e c t _ w i n d o w s a z u r e _ s e r v e r		*/
/*	--------------------------------------------------------	*/
private	int	connect_windowsazure_server( struct az_response * zptr,struct windowsazure * pptr )
{
	int	status;
	char	buffer[2048];

	if ((!( pptr ))
	||  (!( zptr ))
	||  (!( zptr->response )))
	{
		zptr = liberate_az_response( zptr );
		return( 500 );
	}
	else if ((status = check_windowsazure_operation( zptr )) != 200 )
		return( status );
		
	else
	{
		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if ( pptr->reference ) pptr->reference = liberate( pptr->reference );
		if ( pptr->publicaddr ) pptr->publicaddr = liberate( pptr->publicaddr );
		if ( pptr->privateaddr ) pptr->privateaddr = liberate( pptr->privateaddr );

		sprintf(buffer,"%s.cloudapp.net",pptr->hostedservice);

		if (!( pptr->hostname = allocate_string( buffer) ))
			return( 505 );
		else	
		{
			pptr->when = time((long *) 0);
			pptr->state = _OCCI_RUNNING;
			autosave_windowsazure_nodes();
			return(0);
		}
	}
}

/*	----------------------------------------------------------------	*/
/*	     b u i l d _ w i n d o w s a z u r e _ f i r e w a l l		*/
/*	----------------------------------------------------------------	*/
private	char *	build_windowsazure_firewall(/* struct os_subscription * subptr,*/ struct windowsazure * pptr )
{
	int	status;
	char *	sptr;
	char *	filename;
	FILE *	h;
	char *	rulename;
	char *	rulefrom;
	char *	ruleproto;
	char *	ruleto;
	struct	occi_element * eptr;
	struct	standard_message firewall;
	struct	standard_message port;

	memset( &firewall, 0, sizeof(struct standard_message));
	memset( &port, 0, sizeof(struct standard_message));

	/* ---------------------------------------------------- */
	/* prepare the file containing the firewall description */
	/* ---------------------------------------------------- */
	if (!( filename = rest_temporary_filename( ".xml" )))
		return( filename );
	else if (!( h = az_start_endpoints( filename )))
		return( liberate( filename ) );
	else if ((status = get_standard_message( &firewall, pptr->firewall, _CORDS_CONTRACT_AGENT, default_tls() )) != 0)
		return( liberate( filename ) );
	{
		/* -------------------------- */
		/* create the security group  */
		/* -------------------------- */
		for (	eptr = first_standard_message_link( firewall.message );
			eptr != (struct occi_element *) 0;
			eptr = next_standard_message_link( eptr ) )
		{
			/* ------------------------ */
			/* retrieve the port record */
			/* ------------------------ */
			if (!( sptr = standard_message_link_value( eptr->value )))
				continue;
			else if ((status = get_standard_message( &port, sptr, _CORDS_CONTRACT_AGENT, default_tls() )) != 0)
				continue;

			/* ---------------------------------- */
			/* retrieve the port rule information */
			/* ---------------------------------- */
			if ((!( rulename = occi_extract_atribut( port.message, "occi", 
				_CORDS_PORT, _CORDS_NAME ) ))
			||  (!( ruleproto = occi_extract_atribut( port.message, "occi", 
				_CORDS_PORT, _CORDS_PROTOCOL ) ))
			||  (!( rulefrom = occi_extract_atribut( port.message, "occi", 
				_CORDS_PORT, _CORDS_FROM ) ))
			||  (!( ruleto = occi_extract_atribut( port.message, "occi", 
				_CORDS_PORT, _CORDS_TO   ) )) )
			{
				release_standard_message( &port );
				release_standard_message( &firewall );
				filename = liberate(filename);
				break;
			}
			else	az_create_endpoint( h, rulename, atoi(rulefrom), atoi(rulefrom), ruleproto );
		}
		az_close_endpoints( h );
		return( filename );
	}

}

/*	-------------------------------------------	*/
/* 	   s t a r t  _ w i n d o w s a z u r e	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * start_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	xml_element * eptr;
	struct	az_response * azptr;
	struct	windowsazure * pptr;
	int	status;
	char	* filename;
	char	reference[512];
	char	buffer[2048];

	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "WINDOWS AZURE Invalid Action" ) );
	else if ( pptr->state != _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if ((status = use_windowsazure_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "WINDOWS AZURE Configuration Not Found" ) );
	else if ((status = az_initialise_service( pptr->hostedservice)) != 0)
		return( rest_html_response( aptr, 800 + status, "WINDOWS AZURE Hosted Service Failure" ) );
	else if (!(filename = build_windowsazure_firewall( /* subptr,*/ pptr )))
		return( rest_html_response( aptr, 888, "WINDOWS AZURE Firewall Failure" ) );
	else if (!( filename = az_create_vm_request(
		pptr->id,  pptr->name,
		pptr->image, pptr->media, pptr->flavor,
		pptr->publicnetwork,
		(char *) 0, 0, filename )))
		return( rest_html_response( aptr, 500, "Error Creating WINDOWS AZURE VM Request" ) );
	else if (!( azptr = az_create_vm( filename ) ))
		return( rest_html_response( aptr, 501, "Error Creating WINDOWS AZURE VM" ) );
	else if (!( azptr->response ))
	{
		azptr = liberate_az_response( azptr );
		return( rest_html_response( aptr, 501, "No Response Creating WINDOWS AZURE VM" ) );
	}
	else if ((status = azptr->response->status) > 299 )
	{
		if (!( azptr->xmlroot ))
			strcpy(buffer,"Failure Creating WINDOWS AZURE VM");
		else if (!( eptr = document_element( azptr->xmlroot, "Message" ) ))
			strcpy(buffer,"Failure Creating WINDOWS AZURE VM");
		else	strcpy(buffer,eptr->value);
		azptr = liberate_az_response( azptr );
		return( rest_html_response( aptr, status, buffer ) );
	}
	else if ((status = connect_windowsazure_server( azptr, pptr )) != 0)
		return( rest_html_response( aptr, status, "Connection to WINDOWS AZURE VM" ) );
	else if (!( filename = az_start_vm_request() ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else if (!( azptr = az_operation_vm( filename, pptr->name, pptr->number ) ))				
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else
	{
		sprintf(reference,"%s/%s/%s",WazProcci.identity,_CORDS_WINDOWSAZURE,pptr->id);

		/* ---------------------------- */
		/* launch the COSACS operations */
		/* ---------------------------- */
		if ( cosacs_test_interface( pptr->hostname, _COSACS_TIMEOUT, _COSACS_RETRY ) )
		{
			cosacs_metadata_instructions( 
				pptr->hostname, _CORDS_CONFIGURATION,
				reference, WazProcci.publisher, pptr->account );
		}

		/* --------------------------- */
		/* now handle the transactions */
		/* --------------------------- */
		if (!( rest_valid_string( pptr->price ) ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else if ( occi_send_transaction( _CORDS_WINDOWSAZURE, pptr->price, "action=start", pptr->account, reference ) )
			return( rest_html_response( aptr, 200, "OK" ) );
		else	return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	      s a v e  _ w i n d o w s a z u r e	*/
/*	-------------------------------------------	*/
private	struct	rest_response * save_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	az_response * azptr;
	int	status;
	struct	windowsazure * pptr;
	char	* filename;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->state == _OCCI_IDLE )
		return( rest_html_response( aptr, 400, "Contract Not Active" ) );
	else if ((status = use_windowsazure_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
	else if ((status = az_initialise_service( pptr->hostedservice)) != 0)
		return( rest_html_response( aptr, 800 + status, "WINDOWS AZURE Service Failure Found" ) );

	else if (!( filename = az_capture_vm_request( pptr->name, pptr->number, pptr->image, 0 ) ))	
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else if (!( azptr = az_operation_vm( filename, pptr->name, pptr->number ) ))				
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else
	{
		/* --------------------------------- */
		/* retrieve crucial data from server */
		/* --------------------------------- */
		status = connect_windowsazure_image( azptr, pptr );
		azptr = liberate_az_response( azptr );
		if (!( status ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else  	return( rest_html_response( aptr, 400, "Bad Request" ) );
	}
}

/*	-----------------------------------------------------------------	*/
/*	   s t o p _ w i n d o w s a z u r e _ p r o v i s i o n i n g		*/
/*	-----------------------------------------------------------------	*/
private	int	stop_windowsazure_provisioning( struct windowsazure * pptr )
{
	char *	filename;
	char 	reference[2024];
	int	status;
	struct	az_response * azptr;

	/* ------------------------ */
	/* prepare the subscription */
	/* ------------------------ */
	if ((status = use_windowsazure_configuration( pptr->profile )) != 0)
		return(118);
	else if ((status = az_initialise_service( pptr->hostedservice)) != 0)
		return(27);
	else	sprintf(reference,"%s/%s/%s",WazProcci.identity,_CORDS_WINDOWSAZURE,pptr->id);

	/* ------------------------------------------- */
	/* perform pre-release actions for destruction */
	/* ------------------------------------------- */
	cosacs_metadata_instructions( 
		pptr->hostname, _CORDS_RELEASE,
		reference, WazProcci.publisher, pptr->account );

	/* --------------------------------- */
	/* release the provisioned resources */
	/* --------------------------------- */
	if (!( filename = az_shutdown_vm_request() ))
	 	return( 56 );
	else if (!( azptr = az_operation_vm( filename, pptr->name, pptr->number ) ))				
	 	return( 56 );
	if (!( azptr = az_delete_deployment( 
			pptr->hostedservice, 
			pptr->id  )))
		return(40);
	else if ((status = check_windowsazure_operation( azptr )) != 200 )
		return(56);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	     s t o p  _ w i n d o w s a z u r e	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * stop_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	char	reference[512];
	struct	az_response * azptr;
	int	status;
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid WINDOWS AZUREAction" ) );
	else if ( pptr->state == _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else 
	{
		stop_windowsazure_provisioning( pptr );
		reset_windowsazure_server( pptr );
		pptr->when = time((long *) 0);
		autosave_windowsazure_nodes();
		sprintf(reference,"%s/%s/%s",WazProcci.identity,_CORDS_WINDOWSAZURE,pptr->id);
		if (!( rest_valid_string( pptr->price ) ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else if ( occi_send_transaction( _CORDS_WINDOWSAZURE, pptr->price, "action=stop", pptr->account, reference ) )
			return( rest_html_response( aptr, 200, "OK" ) );
		else	return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	 r e s t a r t  _ w i n d o w s a z u r e	*/
/*	-------------------------------------------	*/
private	struct	rest_response * restart_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	int	status;
	struct	windowsazure * pptr;
	char *	filename;
	struct	az_response * azptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ((status = use_windowsazure_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
	else if ((status = az_initialise_service( pptr->hostedservice)) != 0)
		return( rest_html_response( aptr, 800 + status, "WINDOWS AZURE Service Failure Found" ) );
	else if (!( filename = az_restart_vm_request() ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else if (!( azptr = az_operation_vm( filename, pptr->name, pptr->number ) ))				
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else
	{
		if ( pptr->state == _OCCI_SUSPENDED )
		{
			pptr->when = time((long *) 0);
			pptr->state = _OCCI_RUNNING;
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	  s u s p e n d  _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * suspend_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	int	status;
	struct	windowsazure * pptr;
	char *	filename;
	struct	az_response * azptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ((status = use_windowsazure_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
	else if ((status = az_initialise_service( pptr->hostedservice)) != 0)
		return( rest_html_response( aptr, 800 + status, "WINDOWS AZURE Service Failure Found" ) );
	else if (!( filename = az_shutdown_vm_request() ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	else if (!( azptr = az_operation_vm( filename, pptr->name, pptr->number ) ))				
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );		
	{
		if ( pptr->state == _OCCI_RUNNING )
		{
			pptr->when = time((long *) 0);
			pptr->state = _OCCI_SUSPENDED;
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	   s o f t b o o t _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * softboot_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	   h a r d b o o t _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * hardboot_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	   r e b u i l d_ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * rebuild_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	    r e s i z e _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * resize_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	  c o n f i r m _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * confirm_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	  r e v e r t _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * revert_windowsazure(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	windowsazure * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

#include "azcontract.c"

/*	-------------------------------------------	*/
/* 	  c r e a t e _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	int	create_windowsazure(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	windowsazure * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(create_windowsazure_contract(optr,pptr, _CORDS_CONTRACT_AGENT, WazProcci.tls));
}

/*	-------------------------------------------	*/
/* 	 r e t r i e v e _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	int	retrieve_windowsazure(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	windowsazure * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	   u p d a t e _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	int	update_windowsazure(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	windowsazure * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);}

/*	-------------------------------------------	*/
/* 	   d e l e t e _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
private	int	delete_windowsazure(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	windowsazure * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(delete_windowsazure_contract(optr, pptr, _CORDS_CONTRACT_AGENT, WazProcci.tls));
}

private	struct	occi_interface	windowsazure_interface = {
	create_windowsazure,
	retrieve_windowsazure,
	update_windowsazure,
	delete_windowsazure
	};

/*	-------------------------------------------	*/
/* 	    b u i l d _ w i n d o w s a z u r e  	*/
/*	-------------------------------------------	*/
/*	this function is to be called to build the	*/
/*	complete windowsazure occi category to offer	*/
/*	an windowsazure compute provisioning service	*/
/*	through a compatible one published occi		*/
/*	service interface.				*/
/*	-------------------------------------------	*/
public	struct	occi_category * build_windowsazure( char * domain )
{
	struct	occi_category * optr;
	if (!( optr = occi_windowsazure_builder( domain,"windowsazure" ) ))
		return( optr );
	else
	{
		optr->callback  = &windowsazure_interface;
		optr->access |= _OCCI_PROVIDER;

		if (!( optr = occi_add_action( optr,_CORDS_START,"",start_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_SAVE,"",save_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_STOP,"",stop_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_SUSPEND,"",suspend_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_RESTART,"",restart_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"softboot","",softboot_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"hardboot","",hardboot_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"rebuild","",rebuild_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"resize","",resize_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"confirm","",confirm_windowsazure)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"revert","",revert_windowsazure)))
			return( optr );
		else	return( optr );
	}
}

/*	------------------------------------------------	*/
/*	 s e t _ d e f a u l t _ w i n d o w s a z u r e	*/
/*	------------------------------------------------	*/
private	int	set_default_windowsazure(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	az_config * pptr;
	struct	az_config * wptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else
	{
		while ( nptr->previous )
			nptr = nptr->previous;
		while ( nptr )
		{
			if ((wptr = nptr->contents) != (struct az_config*) 0)
				wptr->current = 0,
			nptr = nptr->next;
		}
		pptr->current = 1;
		return(0);
	}
}

/*	---------------------------------------------------------	*/
/* 	b u i l d _ w i n d o w s a z u r e _ c o n f i g u r a t i o n	*/
/*	---------------------------------------------------------	*/
/*	this category handles the configuration of the interface	*/
/*	to the oepn stack server for the preceeding category of		*/
/*	provisioning instance requests.					*/
/*	---------------------------------------------------------	*/
public	struct	occi_category * build_windowsazure_configuration( char * domain )
{
	struct	occi_category * optr;
	if (!( optr = occi_az_config_builder( domain, "windowsazure_configuration" ) ))
		return( optr );
	else if (!( optr = occi_add_action( optr,"current","",set_default_windowsazure)))
		return( optr );
	else	return( optr );
}

#endif	/* _procciaz_c */
	/* ----------- */



