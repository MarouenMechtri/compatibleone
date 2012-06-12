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

#include "osclient.h"
#include "cordslang.h"
#include "occiresolver.h"
#include "cosacsctrl.h"
#include "cp.h"
#include "cb.h"
#include "stdnode.h"

public	char *	occi_extract_atribut( 
	struct occi_response * zptr, char * domain,
	char * category, char * nptr );

/*	------------------------------------------	*/
/*		o s _ v a l i d _ p r i c e		*/
/*	------------------------------------------	*/
private	int	os_valid_price( char * price )
{
	if (!( price ))
		return(0);
	else if (!( strlen( price )))
		return( 0 );
	else if (!( strcmp( price, _CORDS_NULL ) ))
		return( 0 );
	else	return( 1 );
}	

/*	------------------------------------------	*/
/*		o s _ v a l i d _ a d d r e s s		*/
/*	------------------------------------------	*/
private	int	os_valid_address( char * address )
{
	if (!( address ))
		return(0);
	else if (!( strlen( address )))
		return( 0 );
	else if (!( strcmp( address, _CORDS_NULL ) ))
		return( 0 );
	else	return( 1 );
}	

/* ---------------------------------------------------------------------------- */
/* 		r e s o l v e _ o s _ c o n f i g u r a t i o n			*/
/* ---------------------------------------------------------------------------- */
private	struct	os_config * resolve_os_configuration( char * sptr )
{
	struct	occi_kind_node * nptr;
	struct	os_config * pptr=(struct os_config *) 0;
	struct	occi_kind_node  * occi_first_os_config_node();
	for (	nptr = occi_first_os_config_node();
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
	return((struct os_config *) 0);
}

/*	--------------------------------------------------------	*/
/* 	   r e s o l v e _ o p e n s t a c k _ v e r s i o n 		*/
/*	--------------------------------------------------------	*/
private	char *	resolve_openstack_version( char * sptr )
{
	struct	os_config * pptr;

	if (!( pptr = resolve_os_configuration( sptr )))
	 	return( "" );
	else	return( ( pptr->version ? pptr->version : "" ) );
}

/*	-----------------------------------------------------------	*/
/* 		o p e n s t a c k _ i n s t r u c t i o n s		*/
/*	-----------------------------------------------------------	*/
/*	Collect the instruction values which apply to this provider	*/
/*	contract. These values will be the result of configuration	*/
/*	actions complied to instructions during instance creation	*/
/*	and the values will have been collected and prepared by the 	*/
/*	from the corresponding provisioned contracts.			*/
/*	The values collected will be used to build the META DATA to	*/
/*	be made available as the provisioned instance personality	*/
/*	-----------------------------------------------------------	*/
private	char *	openstack_instructions( char * contract, char * result, char * nature )
{

	char	*	ihost;
	char 	*	vptr;

	struct	occi_response * zptr=(struct occi_response *) 0;
	struct	occi_response * zzptr=(struct occi_response *) 0;
	struct	occi_response * yptr=(struct occi_response *) 0;
	struct	occi_element  * fptr=(struct occi_element  *) 0;
	struct	occi_element  * gptr=(struct occi_element  *) 0;
	struct	occi_element  * jptr=(struct occi_element  *) 0;
	struct	occi_element  * eptr=(struct occi_element  *) 0;
	struct	occi_client   * kptr=(struct occi_client   *) 0;
	struct	occi_request  * qptr=(struct occi_request  *) 0;
	char	buffer[4096];
	char	tempname[4096];
	int	length=0;

	/* ------------------------------------------------------------------------- */
	/* select / resolve the instruction category service provider identification */
	/* ------------------------------------------------------------------------- */
	if (!( ihost = occi_resolve_category_provider( _CORDS_INSTRUCTION, _CORDS_CONTRACT_AGENT, OsProcci.tls ) ))
	 	return( result );

	sprintf(buffer,"%s/%s/",ihost,_CORDS_INSTRUCTION);
	liberate( ihost );
	length = strlen(buffer);

	/* --------------------------------------------------------------------------- */
	/* retrieve the collection of instruction category instances for this contract */
	/* --------------------------------------------------------------------------- */
	if (!( kptr = occi_create_client( buffer, _CORDS_CONTRACT_AGENT, OsProcci.tls ) ))
		return( result );

	else if (!(qptr = occi_create_request( 
			kptr, 
			kptr->target->object, 
			_OCCI_NORMAL )))
		return(result);
	else if (!( fptr = occi_request_element( 
			qptr,
			"occi.instruction.provision", contract ) ))
	{
		qptr = occi_remove_request( qptr );
		return( result );
	}
	else if (!( yptr = occi_client_get( kptr, qptr ) ))
	{
		qptr = occi_remove_request( qptr );
		return( result );
	}

	qptr = occi_remove_request ( qptr );

	/* -------------------------------------------------- */
	/* for each instruction category instance in the list */
	/* -------------------------------------------------- */
	for (	eptr = yptr->first;
		eptr != (struct occi_element*) 0;
		eptr = eptr->next )
	{
		if (!( eptr->name ))
			continue;
		else if (!( eptr->value ))
			continue;
		else if (!( vptr = allocate_string( eptr->value )))
			continue;
		else if (!( vptr = occi_category_id( vptr ) ))
			continue;
		else
		{
			strcat( buffer, vptr );
			liberate( vptr );
		}

		/* -------------------------------------------------- */
		/* retrieve the current instruction category instance */
		/* -------------------------------------------------- */
		if (( zptr = occi_simple_get( buffer, _CORDS_CONTRACT_AGENT, OsProcci.tls )) != (struct occi_response *) 0)
		{
			/* ensure its a configuration method */
			/* --------------------------------- */
			if (!(fptr = occi_locate_element( zptr->first, "occi.instruction.nature" )))
				zptr = occi_remove_response ( zptr );
			else if ( strcasecmp( fptr->value, nature ) )
				zptr = occi_remove_response ( zptr );
			else if (!(fptr = occi_locate_element( zptr->first, "occi.instruction.type" )))
				zptr = occi_remove_response ( zptr );
			else if ( strcasecmp( fptr->value, "method" ) )
				zptr = occi_remove_response ( zptr );
			else if (!(fptr = occi_locate_element( zptr->first, "occi.instruction.method" )))
				zptr = occi_remove_response ( zptr );
			else if ( strcasecmp( fptr->value, "configure" ) )
				zptr = occi_remove_response ( zptr );

			/* collect the configuration details */
			/* --------------------------------- */
			else if (!(fptr = occi_locate_element( zptr->first, "occi.instruction.symbol" )))
				zptr = occi_remove_response ( zptr );
			else if (!(gptr = occi_locate_element( zptr->first, "occi.instruction.property" )))
				zptr = occi_remove_response ( zptr );
			else if (!(jptr = occi_locate_element( zptr->first, "occi.instruction.value" )))
				zptr = occi_remove_response ( zptr );
			else
			{
				/* ------------------------------------------------------- */
				/* create the corresponding META DATA type NAME=VALUE pair */
				/* ------------------------------------------------------- */
				sprintf(tempname,"%s_%s=%s\n",fptr->value,gptr->value,jptr->value);
				zzptr = occi_remove_response ( zzptr );
				zptr = occi_remove_response ( zptr );
				if (!( vptr = allocate( strlen( result ) + strlen( tempname ) + 8 ) ))
					break;
				else	
				{
					sprintf(vptr, "%s%s",result,tempname);
					liberate( result );
					result = vptr;
				}
			}
		}

		/* ----------------------- */
		/* quick reset of base url */
		/* ----------------------- */
		buffer[length] = 0;
	}

	yptr = occi_remove_response ( yptr );

	return(result);
}



/*	--------------------------------------------------------	*/
/* 	 u s e _ o p e n s t a c k _ c o n f i g u r a t i o n 		*/
/*	--------------------------------------------------------	*/
private	int	use_openstack_configuration( char * sptr )
{
	struct	os_config * pptr;

	if (!( pptr = resolve_os_configuration( sptr )))
	 	return( 404 );

	else 	return( os_initialise_client( 
			pptr->user, pptr->password, pptr->namespace,
			pptr->host, _CORDS_OS_AGENT, pptr->version, pptr->tls ));
}

/*	--------------------------------------------------------	*/
/* 	       r e s e t _ o p e n s t a c k _ s e r v e r		*/
/*	--------------------------------------------------------	*/
private	int	reset_openstack_server( struct openstack * pptr )
{
	if ( pptr )
	{
		if ( pptr->number ) pptr->number = liberate( pptr->number );
		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if ( pptr->workload ) pptr->workload = liberate( pptr->workload );
		if ( pptr->reference ) pptr->reference = liberate( pptr->reference );
		if ( pptr->rootpass ) pptr->rootpass = liberate( pptr->rootpass );
		if ( pptr->publicaddr ) pptr->publicaddr = liberate( pptr->publicaddr );
		if ( pptr->privateaddr ) pptr->privateaddr = liberate( pptr->privateaddr );
		if ( pptr->accessip ) pptr->accessip = liberate( pptr->accessip );
		if ( pptr->floating ) pptr->floating = liberate( pptr->floating );
		if ( pptr->floatingid ) pptr->floatingid = liberate( pptr->floatingid );
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
/* 	     c o n n e c t _ o p e n s t a c k _ i m a g e  		*/
/*	--------------------------------------------------------	*/
private	int	connect_openstack_image( struct os_response * rptr,struct openstack * pptr )
{
	struct	os_response * zptr;
	struct	os_response * yptr;
	char *	vptr;
	if (!( pptr ))
		return( 118 );
	else if (!( vptr = json_atribut( rptr->jsonroot, "id") ))
	{
		reset_openstack_server( pptr );
		return( 27 );
	}
	else
	{
		if ( pptr->image )
			pptr->image = liberate( pptr->image );
		if (!( pptr->image = allocate_string( vptr ) ))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		autosave_openstack_nodes();
		/* ----------------------------------------------------- */
		/* we must now await ACTIVE status to be able to collect */
		/* the final identification information to complete the  */
		/* openstack provisioning request.			 */
		/* ----------------------------------------------------- */
		yptr = rptr;
		zptr = (struct os_response *) 0;
		while (1)
		{
			if (!( vptr = json_atribut( yptr->jsonroot, "status" )))
			{
				reset_openstack_server( pptr );
				return( 27 );
			}
			else if (!( strcmp( vptr, "ACTIVE" )))
				break;
			else 
			{
				sleep(1);
				if ( zptr )
					zptr = liberate_os_response( zptr );
				if (!( zptr = os_get_image( pptr->image )))
				{
					reset_openstack_server( pptr );
					return( 555 );
				}
				else	yptr = zptr;
			}
		}
		return( 0 );
	}
}

/*	--------------------------------------------------------	*/
/*	    r e s o l v e _ o s _ v 1 0 _ a d d r e s s e s		*/
/*	--------------------------------------------------------	*/
private	int	resolve_os_v10_addresses( struct os_response * yptr, struct openstack * pptr )
{
	char *	vptr;
	if (( vptr = json_atribut( yptr->jsonroot, "private")) != (char *) 0)
	{
		if (!( pptr->privateaddr  = allocate_string(vptr)))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI Instance PRIVATE IP ***");
			rest_log_message( pptr->privateaddr );
		}
	}

	if (( vptr = json_atribut( yptr->jsonroot, "public")) != (char *) 0)
	{
		if (!( pptr->publicaddr  = allocate_string(vptr)))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI Instance PUBLIC IP ***");
			rest_log_message( pptr->publicaddr );
		}
	}
	return(0);
}

/*	--------------------------------------------------------	*/
/*	    r e s o l v e _ o s _ v 1 1 _ a d d r e s s e s		*/
/*	--------------------------------------------------------	*/
private	int	resolve_os_v11_addresses( struct os_response * yptr, struct openstack * pptr )
{
	struct	data_element * eptr;
	struct	data_element * aptr;
	char *	vptr;
	int	addresses=0;
	if (!( aptr = json_element( yptr->jsonroot, "addresses" )))
		return(0);

	else 
	{
		if (( eptr = json_element( aptr, "private" )) != (struct data_element *) 0)
		{
			if (( vptr = json_atribut( eptr, "addr" )) != (char *) 0)
			{
				if (!( pptr->privateaddr  = allocate_string(vptr)))
				{
					reset_openstack_server( pptr );
					return( 27 );
				}
				if ( check_debug() )
				{
					rest_log_message("*** OS PROCCI Instance PRIVATE IP ***");
					rest_log_message( pptr->privateaddr );
				}
				addresses |= 1;
			}
		}

		if (( eptr = json_element( aptr, "public" )) != (struct data_element *) 0)
		{
			if (( vptr = json_atribut( eptr, "addr" )) != (char *) 0)
			{
				if (!( pptr->publicaddr  = allocate_string(vptr)))
				{
					reset_openstack_server( pptr );
					return( 27 );
				}
				if ( check_debug() )
				{
					rest_log_message("*** OS PROCCI Instance PUBLIC IP ***");
					rest_log_message( pptr->publicaddr );
				}
				addresses |= 2;
			}
		}
		if (!( addresses ))
		{
			if (( vptr = json_atribut( aptr, "addr" )) != (char *) 0)
			{
				if (!( pptr->publicaddr  = allocate_string(vptr)))
				{
					reset_openstack_server( pptr );
					return( 27 );
				}
				else if (!( pptr->privateaddr  = allocate_string(vptr)))
				{
					reset_openstack_server( pptr );
					return( 27 );
				}
				if ( check_debug() )
				{
					rest_log_message("*** OS PROCCI Instance PUBLIC IP ***");
					rest_log_message( pptr->publicaddr );
				}
				addresses |= 2;
			}
		}

	}
	return(0);
}

/*	--------------------------------------------------------	*/
/* 	     c o n n e c t _ o p e n s t a c k _ s e r v e r		*/
/*	--------------------------------------------------------	*/
private	int	connect_openstack_server( struct os_response * rptr,struct openstack * pptr )
{
	char *	version;
	struct	os_response * zptr;
	struct	os_response * yptr;
	char *	vptr;

	if (!( pptr ))
		return( 118 );
	else
	{
		/* ---------------------------------------------------- */
		/* we must now analyse the response from the open stack	*/
		/* and collect the valuable data : admin pass is only 	*/
		/* available at this point and cannot be retrieved by	*/
		/* any other means so it must not be lost.		*/ 
		/* ---------------------------------------------------- */
		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI connect_openstack_server( entry ) ***");
		}

		if ( pptr->number ) 
			pptr->number = liberate( pptr->number );

		if ( pptr->rootpass ) 
			pptr->rootpass = liberate( pptr->rootpass );

		if (!( vptr = json_atribut( rptr->jsonroot, "id") ))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		else if (!( pptr->number = allocate_string(vptr)))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI Instance ID ***");
			rest_log_message( pptr->number );
		}
		if (!( vptr = json_atribut( rptr->jsonroot, "adminPass") ))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		else if (!( pptr->rootpass  = allocate_string(vptr)))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}

		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI Instance ADMIN PASS ***");
			rest_log_message( pptr->rootpass );
		}

		autosave_openstack_nodes();

		/* ----------------------------------------------------- */
		/* we must now await ACTIVE status to be able to collect */
		/* the final identification information to complete the  */
		/* openstack provisioning request.			 */
		/* ----------------------------------------------------- */
		yptr = rptr;
		zptr = (struct os_response *) 0;
		while (1)
		{
			if (!( vptr = json_atribut( yptr->jsonroot, "status" )))
			{
				if ( zptr ) zptr = liberate_os_response( zptr );
				if (!( zptr = os_get_server( pptr->number )))
				{
					reset_openstack_server( pptr );
					return( 27 );
				}
				else if (!( vptr = json_atribut( zptr->jsonroot, "status" )))
				{
					reset_openstack_server( pptr );
					return( 27 );
				}
				else	yptr = zptr;
			}
			if (!( strcmp( vptr, "BUILD" )))
			{
				sleep(1);
				if ( zptr )
					zptr = liberate_os_response( zptr );
				if (!( zptr = os_get_server( pptr->number )))
				{
					reset_openstack_server( pptr );
					return( 555 );
				}
				else	yptr = zptr;
			}
			else if (!( strcmp( vptr, "ACTIVE" )))
				break;
		}

		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if ( pptr->reference ) pptr->reference = liberate( pptr->reference );
		if ( pptr->publicaddr ) pptr->publicaddr = liberate( pptr->publicaddr );
		if ( pptr->privateaddr ) pptr->privateaddr = liberate( pptr->privateaddr );

		if ((!( vptr = json_atribut( yptr->jsonroot, "hostId") ))
		&& (!( vptr = pptr->number )))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}
		else if (!( pptr->reference = allocate_string(vptr)))
		{
			reset_openstack_server( pptr );
			return( 27 );
		}

		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI Instance HOST ID ***");
			rest_log_message( pptr->reference );
		}

		/* ------------------------------------------------------------- */
		/* determine the openstack message version and collect addresses */
		/* ------------------------------------------------------------- */
		if (!( version = resolve_openstack_version( pptr->profile ) ))
			resolve_os_v10_addresses( yptr, pptr );

		else if (!( strcmp( version, "v1.0" ) ))
			resolve_os_v10_addresses( yptr, pptr );

		else if (!( strcmp( version, "v1.1" ) ))
			resolve_os_v11_addresses( yptr, pptr );

		/* ------------------------------------------------ */
		/* now overload using a floating IP or an access IP */
		/* if one or the other is available.		    */
		/* ------------------------------------------------ */
		if ( os_valid_address( pptr->floating ) )
		{
			if ( pptr->publicaddr ) 
				pptr->publicaddr = liberate( pptr->publicaddr );
			if (!( pptr->publicaddr  = allocate_string(pptr->floating) ))
			{
				reset_openstack_server( pptr );
				return( 27 );
			}
		}
		else if ( os_valid_address( pptr->accessip ) )
		{
			if ( pptr->publicaddr ) 
				pptr->publicaddr = liberate( pptr->publicaddr );
			if (!( pptr->publicaddr  = allocate_string(pptr->accessip) ))
			{
				reset_openstack_server( pptr );
				return( 27 );
			}
		}

		/* ------------------------------------------------------------ */
		/* set the host name field now to the public or private address */
		/* ------------------------------------------------------------ */
		if (( pptr->publicaddr ) && ( strlen( pptr->publicaddr ) != 0))
		{
			if (!( pptr->hostname = allocate_string( pptr->publicaddr ) ))
			{
				reset_openstack_server( pptr );
				return( 27 );
			}
		}
		else if (( pptr->privateaddr ) && ( strlen( pptr->privateaddr ) != 0))
		{
			if (!( pptr->hostname = allocate_string( pptr->privateaddr ) ))
			{
				reset_openstack_server( pptr );
				return( 27 );
			}
		}

		/* ------------------------------------------------- */
		/* The instance is ready for use ( or more or less ) */
		/* ------------------------------------------------- */
		pptr->when = time((long *) 0);
		pptr->state = _OCCI_RUNNING;
		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI Instance is UP and RUNNING ***");
		}
		autosave_openstack_nodes();
		if ( check_debug() )
		{
			rest_log_message("*** OS PROCCI connect_openstack_server( exit ) ***");
		}
		return(0);
	}
}


/*	------------------------------------------------------------------	*/
/*		c o n e t s _ a c c e s s _ a d d r e s s			*/
/*	------------------------------------------------------------------	*/
private	int	conets_access_address( struct openstack * pptr )
{
	struct	occi_element * header=(struct occi_element *) 0;
	struct	occi_response * yptr=(struct occi_response *) 0;
	char	buffer[1024];
	char 	* vptr;
	/* ----------------------------------------- */
	/* check of use of CONETS has been inhibited */
	/* ----------------------------------------- */
	if ((vptr = getenv( "USECONETS" )) != (char *) 0)
	{
		if ( *vptr == '0' ) 
		{
			pptr->accessip = (char *) 0;
			return( 0 );
		}
		/* -------------------------------------- */
		/* USECONETS must exist and be set to '1' */
		/* in order that CONETS be used for IP    */
		/* address allocation 			  */
		/* -------------------------------------- */
	}
	else
	{
		pptr->accessip = (char *) 0;
		return( 0 );
	}
	

	/* ------------------------------------------------ */
	/* create an IP address for the provisioned machine */
	/* ------------------------------------------------ */
	if (!( header = occi_create_element( "occi.ipaddress.network", pptr->network ) ))
	{
		return( 1002 );
	}
	else if (!( yptr = cords_create_instance( 
			_CORDS_IPADDRESS, 
			_CORDS_CONTRACT_AGENT, 
			header, default_tls() ) ))
	{
		return( 1003 );
	}
	else if (!( vptr = occi_extract_location( yptr ) ))
	{
		yptr = occi_remove_response( yptr );
		return( 1004 );
	}
	else if (!( vptr = occi_category_id( vptr ) ))
	{
		yptr = occi_remove_response( yptr );
		return( 1005 );
	}
	else
	{
		sprintf(buffer,"%s/%s/%s",yptr->host,_CORDS_IPADDRESS,vptr);
		yptr = occi_remove_response( yptr );
		if (!( yptr = occi_simple_get( buffer, _CORDS_CONTRACT_AGENT, default_tls() ) ))
			return( 1006 );
		else if (!( vptr = occi_extract_atribut( 
					yptr, "occi", _CORDS_IPADDRESS, "value" ) ))
		{
			yptr = occi_remove_response( yptr );
			return( 1007 );
		}
		else
		{
			strcpy( buffer, vptr );
			yptr = occi_remove_response( yptr );
			if ( pptr->accessip )
				pptr->accessip = liberate( pptr->accessip );
			if ( pptr->floating )
				pptr->floating = liberate( pptr->floating );
			if ( pptr->floatingid )
				pptr->floatingid = liberate( pptr->floatingid );
			if (!( pptr->accessip = allocate_string( buffer ) ))
				return( 1008 );
			else	return( 0 );
		}
	}		
}

/*	------------------------------------------------------------------	*/
/*			 n o v a _ a c c e s s _ a d d r e s s			*/
/*	------------------------------------------------------------------	*/
private	int	nova_access_address( struct openstack * pptr )
{
	struct	os_response	*	rptr;
	char *	vptr;
	char *	wptr;
	if (!( rptr = os_create_address() ))
		return( 118 );
	else if (!( vptr = json_atribut( rptr->jsonroot, "ip" )))
		return( 118 );
	else if (!( wptr = json_atribut( rptr->jsonroot, "id" )))
		return( 118 );
	else
	{
		if ( pptr->accessip )
			pptr->accessip = liberate( pptr->accessip );

		if ( pptr->floating )
			pptr->floating = liberate( pptr->floating );

		if ( pptr->floatingid )
			pptr->floatingid = liberate( pptr->floatingid );

		if (!( pptr->floating = allocate_string( vptr )))
		{
			liberate_os_response( rptr );
			return( 27 );
		}
		else if (!( pptr->floatingid = allocate_string( wptr )))
		{
			liberate_os_response( rptr );
			return( 27 );
		}
		else
		{
			liberate_os_response( rptr );
			return( 0 );
		}

	}
}

/*	--------------------------------------------------------------------	*/
/*			o s _ u s e _ c o n e t s				*/
/*	--------------------------------------------------------------------	*/
private	int	os_use_conets( struct openstack * pptr )
{
	char *	version;
	if (!( version = resolve_openstack_version( pptr->profile ) ))
		return( 1 );
	else if (!( strcmp( version, "v1.0" ) ))
		return( 1 );
	else if (!( strcmp( version, "v1.1" ) ))
		return( 0 );
	else	return( 1 );
}

/*	--------------------------------------------------------------------	*/
/*		o s _ r e s o l v e _ a c c e s s _ a d d r e s s		*/
/*	--------------------------------------------------------------------	*/
private	int	os_resolve_access_address( struct openstack * pptr )
{
	if (!( pptr ))
		return( 0 );
	else if ( os_use_conets( pptr ) )
		return( conets_access_address( pptr ) );
	else	return( nova_access_address( pptr ) );
}


/*	------------------------------------------------------------------	*/
/*		  a s s o c i a t e _ s e r v e r _ a d d r e s s		*/
/*	------------------------------------------------------------------	*/
/*	the server is up and running, an address has been allocated and 	*/
/*	now we must attribute this addresse to this serrver and wait until	*/
/*	it is ready ...								*/
/*	------------------------------------------------------------------	*/
private	int	associate_server_address( struct openstack * pptr )
{
	int	iterate=30;
	char *	nomfic;
	char *	vptr;
	struct	os_response * osptr;
	if (!( pptr ))
		return( 1001 );
	else if (!( os_valid_address( pptr->floating ) ))
		return( 1002 );
	else if (!( nomfic = os_create_address_request( pptr->floating ) ))
		return( 1003 );
	else if (!( osptr = os_server_address( nomfic, pptr->number ) ))
		return( 1004 );
	else
	{
		osptr = liberate_os_response( osptr );
		nomfic = liberate( nomfic );
		while (iterate)
		{
			if (!( osptr = os_get_address( pptr->floatingid ) ))
				return( 1005 );
			else if (!( vptr = json_atribut( osptr->jsonroot, "instance_id") ))
			{
				osptr = liberate_os_response( osptr );
				return( 1006 );
			}
			else if ( strcmp( vptr, pptr->number ) )
			{
				osptr = liberate_os_response( osptr );
				sleep(1);
				iterate--;
				continue;
			}
			else
			{
				osptr = liberate_os_response( osptr );
				break;
			}
		}
		if (!( iterate ))
			return( 1007 );
		else
		{
			return( 0 );
		}
	}
}

/*	------------------------------------------------------------------	*/
/*		  d i s a s s o c i a t e _ s e r v e r _ a d d r e s s		*/
/*	------------------------------------------------------------------	*/
/*	the server is up and running, an address has been attributed and 	*/
/*	now we must noe disconnect the address from the server			*/
/*	------------------------------------------------------------------	*/
private	int	disassociate_server_address( struct openstack * pptr )
{
	int	iterate=30;
	char *	nomfic;
	char *	vptr;
	struct	os_response * osptr;
	if (!( pptr ))
		return( 1001 );
	else if (!( os_valid_address( pptr->floating ) ))
		return( 1002 );
	else if (!( nomfic = os_remove_address_request( pptr->floating ) ))
		return( 1003 );
	else if (!( osptr = os_server_address( nomfic, pptr->number ) ))
		return( 1004 );
	else
	{
		osptr = liberate_os_response( osptr );
		nomfic = liberate( nomfic );
		if (!( osptr = os_get_address( pptr->floatingid ) ))
			return( 1005 );
		else
		{
			osptr = liberate_os_response( osptr );
				return( 0 );
		}
	}
}

/*	----------------------------------------------------------------	*/
/*		r e l e a s e _f l o a t i n g _ a d d r e s s			*/
/*	----------------------------------------------------------------	*/
private	void	release_floating_address( struct openstack * pptr )
{
	struct	os_response * osptr;
	if ( pptr->floatingid )
	{
		if ((osptr = os_delete_address( pptr->floatingid )) != (struct os_response *) 0)
			osptr = liberate_os_response( osptr );
	}
	return;
}

/*	----------------------------------------------------------------	*/
/*		r e m o v e _f l o a t i n g _ a d d r e s s			*/
/*	----------------------------------------------------------------	*/
private	void	remove_floating_address( struct openstack * pptr )
{
	struct	os_response * osptr;
	if ( pptr->floatingid )
	{
		if ((osptr = os_delete_address( pptr->floatingid )) != (struct os_response *) 0)
			osptr = liberate_os_response( osptr );
		pptr->floatingid = liberate( pptr->floatingid );
	}
	if ( pptr->floating )
		pptr->floating = liberate( pptr->floating );
	return;
}

/*	----------------------------------------------------------------	*/
/*		r e m o v e _s e c u r i t y _ g r o u p    			*/
/*	----------------------------------------------------------------	*/
private	void	remove_security_group( struct openstack * pptr )
{
	struct	os_response * osptr;
	if ( pptr->group )
	{
		if ((osptr = os_delete_security_group( pptr->group )) != (struct os_response *) 0)
			osptr = liberate_os_response( osptr );
		pptr->group = liberate( pptr->group );
	}
	return;
}

/*	------------------------------------------------------------------	*/
/*		r e s o l v e _ o p e n s t a c k _ f i r e w a l l		*/
/*	------------------------------------------------------------------	*/
private	char *	resolve_openstack_firewall( struct openstack * pptr )
{
	struct	os_response *	osptr;
	struct	data_element * fptr;
	struct	data_element * dptr;
	char *	vptr;
	/* -------------------------- */
	/* resolve the security group */
	/* -------------------------- */
	if (!( pptr->firewall ))
		return((char *) 0);
	else if (!(osptr = os_list_security_groups()))
		return((char *) 0);
	else if (!( fptr = json_element( osptr->jsonroot, "security_groups" )))
		return((char *) 0);

	for ( 	dptr=fptr->first;
		dptr != (struct data_element *) 0;
		dptr = dptr->next )
	{
		if (!( vptr = json_atribut( dptr, "name" ) ))
			continue;
		else if ( strcmp( vptr, pptr->firewall ) )
			continue;
		else if (!( vptr = json_atribut( dptr, "id" ) ))
			continue;
		else
		{
			if ( pptr->group ) pptr->group = liberate( pptr->group );
			pptr->group = allocate_string( vptr );
			osptr = liberate_os_response( osptr );
			return( pptr->group );
		}					
	}
	return( (char *) 0 );
}

/*	----------------------------------------------------------------	*/
/*		b u i l d _ o p e n s t a c k _ f i r e w a l l			*/
/*	----------------------------------------------------------------	*/
private	int	build_openstack_firewall( struct openstack * pptr )
{
	char *	filename;
	struct	os_response *	osptr;
	struct	standard_message firewall;
	struct	standard_message port;
	struct	occi_element * eptr;
	char * rulegroup=(char *) 0;
	char * rulefrom=(char *) 0;
	char * rulename=(char *) 0;
	char * ruleto=(char *) 0;
	char * ruleproto=(char *) 0;
	int	started=0;
	int	status=0;
	char *	sptr;

	memset( &firewall, 0, sizeof(struct standard_message));
	memset( &port, 0, sizeof(struct standard_message));

	if (!( pptr ))
		return(0);
	else if (!( pptr->firewall ))
		return(0);
	else if (( rulegroup = resolve_openstack_firewall( pptr )) != (char *) 0)
	{
		if ( pptr->group ) pptr->group = liberate( pptr->group );
		pptr->group = allocate_string( rulegroup );
		return( 0 );
	}
	else if ((status = get_standard_message( &firewall, pptr->firewall, _CORDS_CONTRACT_AGENT, default_tls() )) != 0)
		return( 0 );
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

			/* --------------------------------------- */
			/* build the security group if not started */
			/* --------------------------------------- */
			if (!( started++ ))
			{
				if (!( filename = os_create_security_group_request( pptr->firewall )))
					return(0);
				else if (!( osptr = os_create_security_group( filename ) ))
				{
					liberate( filename );
					return(0);
				}
				else if (!( rulegroup = json_atribut( osptr->jsonroot, "id") ))
				{
					osptr = liberate_os_response( osptr );
					liberate( filename );
				}
				else
				{
					/* ---------------------------------- */
					/* save the security group identifier */
					/* ---------------------------------- */
					pptr->group = allocate_string( rulegroup );
					osptr = liberate_os_response( osptr );
					liberate( filename );
				}
			}			

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
				return(0);
			}
			/* ---------------------------------- */
			/* add the rule to the security group */
			/* ---------------------------------- */
			if (!( filename = os_create_security_rule_request( 
					pptr->group, ruleproto, rulefrom, ruleto, "0.0.0.0/0" ) ))
				return(0);
			else if (!( osptr = os_create_security_rule( filename ) ))
			{
				liberate( filename );
				return(0);
			}
			else
			{
				osptr = liberate_os_response( osptr );
				liberate( filename );
			}
		}
		release_standard_message( &port );
		release_standard_message( &firewall );
		return(0);
	}
}


/*	-------------------------------------------	*/
/* 	      s t a r t  _ o p e n s t a c k	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * start_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	char		* idptr;
	struct	os_response * osptr;
	struct	os_response * metaptr;
	struct	openstack * pptr;
	int		status;
	char 	*	accessAddress=(char *) 0;
	char	*	filename;
	char	*	metafilename;
	char		buffer[512];
	char		reference[512];
	char 	*	personality;
	char 	*	resource=_CORDS_LAUNCH_CFG;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->state != _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if ((status = use_openstack_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Configuration Not Found" ) );

	sprintf(buffer,"contract=%s/%s/%s\npublisher=%s\n",
		OsProcci.identity,_CORDS_OPENSTACK,pptr->id,OsProcci.publisher);
	
	if (!( personality = allocate_string(buffer) ))
		return( rest_html_response( aptr, 4000, "Server Failure : Personality" ) );

	sprintf(reference,"%s/%s/%s",OsProcci.identity,_CORDS_OPENSTACK,pptr->id);

	if (( status = os_resolve_access_address( pptr )) != 0)
		return( rest_html_response( aptr, status, "Server Failure : Access Address" ) );

	if (!( personality = openstack_instructions( reference, personality, _CORDS_CONFIGURATION ) ))
	{
		release_floating_address( pptr );
		return( rest_html_response( aptr, 4001, "Server Failure : Configuration Instructions" ) );
	}
	if ((status = build_openstack_firewall( pptr )) != 0)
	{
		release_floating_address( pptr );
		return( rest_html_response( aptr, 4002, "Server Failure : Firewall Preparation" ) );
	}
	else if (!( pptr->workload = os_build_image_reference( pptr->image ) ))
	{
		release_floating_address( pptr );
		return( rest_html_response( aptr, 4003, "Server Failure : Workload preparation" ) );
	}
	if (!( filename = os_create_server_request( 
		pptr->name, pptr->image, pptr->flavor, pptr->accessip, personality, resource, pptr->firewall, pptr->zone ) ))
	{
		release_floating_address( pptr );
	 	return( rest_html_response( aptr, 4004, "Server Failure : Create Server Message" ) );
	}
	else if (!( osptr = os_create_server( filename )))
	{
		release_floating_address( pptr );
	 	return( rest_html_response( aptr, 4008, "Server Failure : Create Server Request" ) );
	}
	else if (!( osptr->response ))
	{
		release_floating_address( pptr );
	 	return( rest_html_response( aptr, 4010, "Bad Request : Create Server No Response" ) );
	}
	else if ( osptr->response->status >= 400 )
	{
		release_floating_address( pptr );
		aptr = rest_html_response( aptr, osptr->response->status + 4000, "Bad Request : Create Server No Response" );
		osptr = liberate_os_response( osptr );
		return( aptr );
	}
	else
	{
		liberate( filename );
		/* --------------------------------- */
		/* retrieve crucial data from server */
		/* --------------------------------- */
		if (!( status = connect_openstack_server( osptr, pptr ) ))
		{
			/* -------------------------------------------- */
			/* attempt to associate the floating IP address */
			/* -------------------------------------------- */
			if ( pptr->floating )
				if ((status = associate_server_address( pptr )) != 0 )
				 	return( rest_html_response( aptr, status, "Bad Request : Create Server Request" ) );

			/* ---------------------------- */
			/* launch the COSACS operations */
			/* ---------------------------- */
			if ( cosacs_test_interface( pptr->hostname, _COSACS_TIMEOUT, _COSACS_RETRY ) )
			{
				cosacs_metadata_instructions( 
					pptr->hostname, _CORDS_CONFIGURATION,
					reference, OsProcci.publisher );
			}

			/* ------------------------------------- */
			/* release the public IP if not required */
			/* ------------------------------------- */
			if (!( strcasecmp( pptr->access , _CORDS_PRIVATE ) ))
			{
				/* -------------------------------- */
				/* disassociate address from server */
				/* -------------------------------- */
				if ( disassociate_server_address( pptr ) != 0 )
				{
					reset_openstack_server( pptr );
				 	return( rest_html_response( aptr, 4088, "Server Failure : Address removal failure" ) );
				}
				/* ------------------------ */
				/* then release the address */
				/* ------------------------ */
				release_floating_address( pptr );
				if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
				if (!( pptr->hostname = allocate_string( pptr->privateaddr ) ))
				{
					remove_floating_address( pptr );
					reset_openstack_server( pptr );
				 	return( rest_html_response( aptr, 4016, "Server Failure : Allocation Failure" ) );
				}
				remove_floating_address( pptr );
			}

			/* ----------------------- */
			/* create server meta data */
			/* ----------------------- */
			if (!( idptr = json_atribut( osptr->jsonroot, "id") ))
			 	return( rest_html_response( aptr, 4032, "Server Failure : Missing Meta Data Server ID" ) );

			else if (!( metafilename = os_create_metadata_request( personality ) ))
			 	return( rest_html_response( aptr, 4064, "Server Failure : Create MetaData Message" ) );
			else if (!( metaptr = os_create_server_metadata( idptr, metafilename )))
			 	return( rest_html_response( aptr, 4128, "Server Failure : Create MetaData Request" ) );
			else
			{
				metaptr = liberate_os_response( metaptr );
				liberate( metafilename );
			}
		}
		osptr = liberate_os_response( osptr );
		if (!( status ))
		{
			if (!( os_valid_price( pptr->price ) ))
				return( rest_html_response( aptr, 200, "OK" ) );
			else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=start", pptr->account, reference ) )
				return( rest_html_response( aptr, 200, "OK" ) );
			else	return( rest_html_response( aptr, 200, "OK" ) );
		}
		else  	
		{
			release_floating_address( pptr );
			return( rest_html_response( aptr, 4256, "Server Failure : Connect Open Stack" ) );
		}
	}

}

/*	-------------------------------------------	*/
/*		o s _ i m a g e _ n u m b e r 		*/
/*	-------------------------------------------	*/
private	char * os_image_number( char * url )
{
	int	c;
	char *	rptr;
	char *	wptr;
	if (!( wptr = rptr = url ))
		return( url );
	else
	{
		while ((c =  *(wptr++)) != 0)
			if ( c == '/' )
				rptr = wptr;
		return(allocate_string( rptr ) );
	}
}

/*	-------------------------------------------	*/
/* 	    s n a p s h o t _ o p e n s t a c k	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * snapshot_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	char	reference[512];
	struct	rest_header * hptr;
	struct	os_response * osptr;
	int		status;
	struct	openstack * pptr;
	char 	*	inumber;
	char	*	filename;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->state == _OCCI_IDLE )
		return( rest_html_response( aptr, 400, "Contract Not Active" ) );
	else if ((status = use_openstack_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
	/* ------------------------------------------------------------	*/
	/* here we will launch a snapshot of the current server image 	*/
	/* this will be because the service contract requested it in   	*/
	/* which case it will be the future restart state of the vm   	*/
	/* but this must be handled carefully. The current state must 	*/
	/* be generated to a new image filename. 		      	*/
	/* ------------------------------------------------------------ */
	/* the id field is the best choice for this since it is unique	*/
	/* the number   is the current server instance number		*/
	/* ------------------------------------------------------------ */
	else if (!( filename = os_create_image_request( pptr->id, pptr->number ) ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( osptr = os_create_image( filename, pptr->number, 0 ) ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( osptr->response ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if ( osptr->response->status  >= 300 )
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( hptr = rest_resolve_header( osptr->response->first, _HTTP_LOCATION ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( hptr->value ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( pptr->workload = os_build_image_reference( hptr->value ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( inumber = os_image_number( hptr->value ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else
	{
		/* --------------------------------- */
		/* retrieve crucial data from server */
		/* --------------------------------- */
		osptr = liberate_os_response( osptr );
		if (!( osptr = os_get_image( inumber ) ))
		 	return( rest_html_response( aptr, 400, "Bad Request" ) );

		status = connect_openstack_image( osptr, pptr );
		osptr = liberate_os_response( osptr );
		if (!( status ))
		{
			sprintf(reference,"%s/%s/%s",OsProcci.identity,_CORDS_OPENSTACK,pptr->id);
			if (!( os_valid_price( pptr->price ) ))
				return( rest_html_response( aptr, 200, "OK" ) );
			else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=save", pptr->account, reference ) )
				return( rest_html_response( aptr, 200, "OK" ) );
			else	return( rest_html_response( aptr, 200, "OK" ) );
		}
		else  	return( rest_html_response( aptr, 400, "Bad Request" ) );
	}
}

/*	-------------------------------------------	*/
/* 	      s a v e _ o p e n s t a c k	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * save_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	rest_header * hptr;
	char	reference[512];
	struct	os_response * osptr;
	int		status;
	struct	openstack * pptr;
	char	*	inumber;
	char	*	filename;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->state == _OCCI_IDLE )
		return( rest_html_response( aptr, 400, "Contract Not Active" ) );
	else if ((status = use_openstack_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
	/* ------------------------------------------------------------	*/
	/* here we will launch a snapshot of the current server image 	*/
	/* this will result from  an image production request from the	*/
	/* image production services COIPS. 				*/
	/* ------------------------------------------------------------ */
	/* the name field is : the name of the contract and is the same */
	/* for all contracts of the same original node description.	*/
	/* the number     is :	the current server instance number	*/
	/* ------------------------------------------------------------ */
	else if (!( filename = os_create_image_request( pptr->name, pptr->number ) ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( osptr = os_create_image( filename, pptr->number, 1 ) ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( osptr->response ))
	 	return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if ( osptr->response->status  >= 300 )
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( hptr = rest_resolve_header( osptr->response->first, _HTTP_LOCATION ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( hptr->value ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( pptr->workload = os_build_image_reference( hptr->value ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( inumber = os_image_number( hptr->value ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else
	{
		/* --------------------------------- */
		/* retrieve crucial data from server */
		/* --------------------------------- */
		osptr = liberate_os_response( osptr );
		if (!( osptr = os_get_image( inumber ) ))
		 	return( rest_html_response( aptr, 400, "Bad Request" ) );

		status = connect_openstack_image( osptr, pptr );
		osptr = liberate_os_response( osptr );
		if (!( status ))
		{
			/* ----------------------------- */
			/* save must update the original */
			/* to ensure image preservation  */
			/* ----------------------------- */
			if ( pptr->image )
			{ 
				if ( pptr->original ) 
					pptr->original = liberate( pptr->original );
				pptr->original = allocate_string( pptr->image );
				/* -------------------------------------------- */
				/* its a save operation and MUST be made public */
				/* -------------------------------------------- */
				if ((osptr = os_glance_access( inumber, 1 )) != (struct os_response *) 0)
					osptr = liberate_os_response( osptr );

			}
			sprintf(reference,"%s/%s/%s",OsProcci.identity,_CORDS_OPENSTACK,pptr->id);
			if (!( os_valid_price( pptr->price ) ))
				return( rest_html_response( aptr, 200, "OK" ) );
			else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=save", pptr->account, reference ) )
				return( rest_html_response( aptr, 200, "OK" ) );
			else	return( rest_html_response( aptr, 200, "OK" ) );
		}
		else  	return( rest_html_response( aptr, 400, "Bad Request" ) );
	}
}

/*	--------------------------------------------------------	*/
/* 	 s t o p  _ o p e n s t a c k _ p r o v i s i o n i n g  	*/
/*	--------------------------------------------------------	*/
private	struct os_response *	stop_openstack_provisioning( struct openstack * pptr )
{
	int	status;
	struct	os_response * osptr;

	if ((status = use_openstack_configuration( pptr->profile )) != 0)
		return((struct os_response *) 0);
	else
	{
		/* ------------------------------------------ */
		/* disconnect the floating IP from the server */
		/* ------------------------------------------ */
		if ( pptr->floatingid )
		{
			occi_flush_client( pptr->floating, _COSACS_PORT );
			release_floating_address( pptr );
		}
		/* ------------------------------------------ */
		/* launch the deletion of the server instance */
		/* ------------------------------------------ */
		if ((osptr=os_delete_server( pptr->number )) != (struct os_response *) 0)
		{
			/* ----------------------------- */
			/* await server instance removal */
			/* ----------------------------- */
			do
			{
				if (!( osptr ))
					break;
				else if (!( osptr->response ))
					break;
				else if ( osptr->response->status > 299 )
					break;
				else
				{
					sleep(1);
					osptr = liberate_os_response( osptr );
				}
			}
			while ((osptr=os_get_server( pptr->number )) != (struct os_response *) 0);
		}
		/* ------------------------------------------- */
		/* ensure release of the allocated floating IP */
		/* ------------------------------------------- */
		remove_floating_address( pptr );
		return( osptr );
	}
}

/*	-------------------------------------------	*/
/* 	      s t o p  _ o p e n s t a c k	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * stop_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	char	reference[512];
	struct	os_response * osptr;
	int		status;
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->state == _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if (!(osptr = stop_openstack_provisioning( pptr )))
		return( rest_html_response( aptr, status, "Not Found" ) );
	else
	{
		osptr = liberate_os_response( osptr );
		reset_openstack_server( pptr );
		pptr->when = time((long *) 0);
		sprintf(reference,"%s/%s/%s",OsProcci.identity,_CORDS_OPENSTACK,pptr->id);
		if (!( os_valid_price( pptr->price ) ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=stop", pptr->account, reference ) )
			return( rest_html_response( aptr, 200, "OK" ) );
		else	return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	      r e s t a r t  _ o p e n s t a c k	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * restart_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	int	status;
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ((status = use_openstack_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
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
/* 	     s u s p e n d  _ o p e n s t a c k	  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * suspend_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	int	status;
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ((status = use_openstack_configuration( pptr->profile )) != 0)
		return( rest_html_response( aptr, status, "Not Found" ) );
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
/* 	   s o f t b o o t _ o p e n s t a c k  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * softboot_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	   h a r d b o o t _ o p e n s t a c k  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * hardboot_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	     r e b u i l d_ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
private	struct	rest_response * rebuild_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	      r e s i z e _ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
private	struct	rest_response * resize_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	    c o n f i r m _ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
private	struct	rest_response * confirm_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

/*	-------------------------------------------	*/
/* 	      r e v e r t _ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
private	struct	rest_response * revert_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else	return( rest_html_response( aptr, 200, "OK" ) );
}

#include "oscontract.c"

/*	-------------------------------------------	*/
/* 	      c r e a t e _ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
private	int	create_openstack(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	openstack * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else if (!( pptr->node ))
		return( 0 ); 
	else	return(create_openstack_contract(optr,pptr, _CORDS_CONTRACT_AGENT, OsProcci.tls));
}

/*	-------------------------------------------	*/
/* 	    r e t r i e v e _ o p e n s t a c k  	*/
/*	-------------------------------------------	*/
private	int	retrieve_openstack(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	openstack * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	      u p d a t e _ o p e n s t a c k 	 	*/
/*	-------------------------------------------	*/
private	int	update_openstack(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	openstack * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	      d e l e t e _ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
private	int	delete_openstack(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	openstack * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(delete_openstack_contract(optr, pptr, _CORDS_CONTRACT_AGENT, OsProcci.tls));
}

private	struct	occi_interface	openstack_interface = {
	create_openstack,
	retrieve_openstack,
	update_openstack,
	delete_openstack
	};

/*	-------------------------------------------	*/
/* 	       b u i l d _ o p e n s t a c k  		*/
/*	-------------------------------------------	*/
/*	this function is to be called to build the	*/
/*	complete openstack occi category to offer	*/
/*	an openstack compute provisioning service	*/
/*	through a compatible one published occi		*/
/*	service interface.				*/
/*	-------------------------------------------	*/
public	struct	occi_category * build_openstack( char * domain )
{
	struct	occi_category * optr;
	if (!( optr = occi_openstack_builder( domain,_CORDS_OPENSTACK ) ))
		return( optr );
	else
	{
		optr->callback  = &openstack_interface;
		optr->access |= _OCCI_PROVIDER;
		if (!( optr = occi_add_action( optr,_CORDS_START,"",start_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_SAVE,"",save_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_SNAPSHOT,"",snapshot_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_STOP,"",stop_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_SUSPEND,"",suspend_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,_CORDS_RESTART,"",restart_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"softboot","",softboot_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"hardboot","",hardboot_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"rebuild","",rebuild_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"resize","",resize_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"confirm","",confirm_openstack)))
			return( optr );
		else if (!( optr = occi_add_action( optr,"revert","",revert_openstack)))
			return( optr );
		else	return( optr );
	}
}

/*	-------------------------------------------	*/
/*	 s e t _ d e f a u l t _ o p e n s t a c k	*/
/*	-------------------------------------------	*/
private	int	set_default_openstack(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	os_config * pptr;
	struct	os_config * wptr;
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
			if ((wptr = nptr->contents) != (struct os_config*) 0)
				wptr->current = 0,
			nptr = nptr->next;
		}
		pptr->current = 1;
		return(0);
	}
}

/*	---------------------------------------------------------	*/
/* 	b u i l d _ o p e n s t a c k _ c o n f i g u r a t i o n	*/
/*	---------------------------------------------------------	*/
/*	this category handles the configuration of the interface	*/
/*	to the oepn stack server for the preceeding category of		*/
/*	provisioning instance requests.					*/
/*	---------------------------------------------------------	*/
public	struct	occi_category * build_openstack_configuration( char * domain )
{
	struct	occi_category * optr;
	if (!( optr = occi_os_config_builder( domain, "openstack_configuration" ) ))
		return( optr );
	else if (!( optr = occi_add_action( optr,"current","",set_default_openstack)))
		return( optr );
	else	return( optr );
}

#endif	/* _proccios_c */
	/* ----------- */


