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
#ifndef	_occi_os_c
#define	_occi_os_c

#include "occiclient.h"

/*	------------------------------------------	*/
/*		o s _ v a l i d _ p r i c e		*/
/*	------------------------------------------	*/
private	int	occi_valid_price( char * price )
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
/*	    o c c i _ o s _ r e f e r e n c e		*/
/*	------------------------------------------	*/
private	int	occi_os_reference( struct rest_response * zptr, struct openstack * pptr )
{
	struct	rest_header * hptr;
	char	buffer[1024];
	char *	host;
	if ((!( hptr = rest_resolve_header( zptr->first, _OCCI_LOCATION ) ))
	&&  (!( hptr = rest_resolve_header( zptr->first, _HTTP_LOCATION ) )))
		return(0);
	else if (!( host = hptr->value ))
		return(0);
	else
	{
		if (!( strncmp( host, "http://", strlen( "http://" ) ) ))
			strcpy( buffer, host );
		else	sprintf(buffer,"http://%s",host);
		if ( pptr->reference ) pptr->reference = liberate( pptr->reference );
		if (!( pptr->reference = allocate_string( buffer ) ))
			return( 0 );
		else	return( 1 );
	}
}

/*	------------------------------------------------------------	*/
/*		o c c i _ o s _ l o c a t e _ a t t r i b u t e		*/
/*	------------------------------------------------------------	*/
private	struct	rest_header * occi_os_locate_attribute( struct rest_response * zptr, char * atbname )
{
	struct	rest_header * hptr;
	if (!( zptr )) 	return((struct rest_header *) 0);

	for (	hptr = rest_resolve_header( zptr->first, _OCCI_ATTRIBUTE );
		hptr != (struct rest_header *) 0;
		hptr = rest_resolve_header( hptr->next, _OCCI_ATTRIBUTE ) )
	{
		if (!( hptr->value ))
			continue;
		else if ( strncmp( 	hptr->value, 
					atbname, strlen( atbname ) ) )
			continue;
		else	break;
	}
	return( hptr );
}

/*	------------------------------------------------------------	*/
/*		o c c i _ o s _ a t t r i b u t e _ v a l u e 		*/
/*	------------------------------------------------------------	*/
private	char *	occi_os_attribute_value( struct rest_header * hptr )
{
	char *	vptr;
	char *	rptr;
	char *	wptr;
	if (!( hptr )) 	
		return((char *) 0);
	else if (!( hptr->value ))
	 	return((char *) 0);
	else if (!( vptr = allocate_string( hptr->value ) ))
	 	return((char *) 0);
	{
		wptr = vptr;
		while (( *vptr ) && ( *vptr != '=' ) ) vptr++;
		if ( *vptr != '=' ) 
			return((char *) 0);
		*(vptr++) = 0;
		rptr = allocate_string( vptr );
		liberate( wptr );
		if (!( rptr ))
			return( rptr );
		else 	return( occi_unquoted_value( rptr ) );
	}
}

/*	------------------------------------------	*/
/*	    o c c i _ o s _ h o s t n a m e 		*/
/*	------------------------------------------	*/
private	int	occi_os_hostname( struct rest_response * zptr, struct openstack * pptr )
{
	struct	rest_header * hptr;
	char	buffer[1024];
	char *	host;

	if (!( hptr = occi_os_locate_attribute( zptr, "org.openstack.network.floating.ip" ) ))
	{
		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if (!( pptr->hostname = occi_unquoted_value( "hostname" ) ))
			return(0);
		else	return(1);
	}
	else
	{
		sprintf(buffer,"http://%s",(hptr->value+strlen("org.openstack.network.floating.ip")+1));
		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if (!( pptr->hostname = allocate_string( buffer ) ))
			return( 0 );
		strcpy( buffer, pptr->hostname );
		if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
		if (!( pptr->hostname = occi_unquoted_value( buffer ) ))
			return( 0 );
		else	return(1);
	}

}

/*	-----------------------------------------------------------	*/
/*		o s _ o c c i _ c l e a n _ s t r i n g			*/
/*	-----------------------------------------------------------	*/
private	void	os_occi_clean_string( char * sptr )
{
	if ( sptr )
	{
		while ( *sptr )
		{
			if ( *sptr == '\t' )
				*(sptr++) = ' ';
			else if ( *sptr == '\r' )
				*sptr = 0;
			else if ( *sptr == '\n' )
				*sptr = 0;
			else	sptr++;
		}
	}
	return;
}

/*	---------------------------------------------------------	*/
/* 	 p r o c e s s _ p l a i n _ t e x t a t t r i b u t e s 	*/
/*	---------------------------------------------------------	*/
private	struct	rest_response * process_plain_text_attributes( struct rest_response * zptr )
{
	struct	rest_header * hptr;
	char *	sptr;
	char *	nptr;
	char *	vptr;
	FILE * h;
	char	buffer[8192];
	if (!( zptr ))
		return( zptr );
	else if (!( zptr->body ))
		return( zptr );
	else if (!( h = fopen( zptr->body, "r" ) ))
		return( zptr );
	else
	{
		while ((nptr = fgets(buffer, 8000, h)) != (char *) 0)
		{
			os_occi_clean_string( nptr );
			while ( *nptr == ' ' ) nptr++;
			if (!( strncasecmp( nptr, _OCCI_ATTRIBUTE, strlen( _OCCI_ATTRIBUTE ) ) ))
			{
				nptr+= strlen( _OCCI_ATTRIBUTE );
				while ( *nptr == ' ' ) nptr++;
				if ( *nptr == ':' ) nptr++;
				while ( *nptr == ' ' ) nptr++;
				if (!( hptr = rest_response_header( zptr, _OCCI_ATTRIBUTE, nptr ) ))
					break;
				else	continue;
			}
		}
		return( zptr );
	}
}

/*	---------------------------------------------------	*/
/*	p r o c e s s _ o c c i _ o s _ a t t r i b u t e s	*/
/*	---------------------------------------------------	*/
private	struct	rest_response * process_occi_os_attributes( struct rest_response * zptr )
{
	struct	rest_header * hptr;
	if (!( zptr ))
		return( zptr );
	else if (!( hptr = rest_resolve_header( zptr->first, _HTTP_CONTENT_LENGTH ) ))
		return( zptr );
	else if (!( hptr->value ))
		return( zptr );
	else if (!( atoi( hptr->value ) ))
		return( zptr );
	else if (!( hptr = rest_resolve_header( zptr->first, _HTTP_CONTENT_TYPE ) ))
		return( zptr );
	else if (!( hptr->value ))
		return( zptr );
	else if (!( strncasecmp( hptr->value, "text/plain", strlen("text/plain") ) ))
		return( process_plain_text_attributes( zptr ) );
	else	return( zptr );
}


/*	-------------------------------------------	*/
/* 	  s t a r t  _ o c c i_ o p e n s t a c k  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * start_occi_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	rest_header * hptr;
	char	reference[1024];
	int	status=0;
	int	startcompute=0;
	struct	openstack * pptr;
	struct	os_config * kptr;
	struct	rest_response * qptr;
	char	flavor[1024];
	char *	fscheme;
	char	image[1024];
	char *	ischeme;

	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->status != _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if (!(kptr = use_occi_openstack_configuration( pptr->profile )))
		return( rest_html_response( aptr, 800, "Configuration Not Found" ) );
	else
	{
		/* ---------------------------------------- */
		/* Prepare the Flavor and Image information */
		/* ---------------------------------------- */
		strcpy(flavor,pptr->flavor);

		fscheme = flavor;
		while (( *fscheme ) && ( *fscheme != ';' ))
			fscheme++;
		if ( *fscheme == ';' )
			*(fscheme++) = 0;

		strcpy(image,pptr->image);

		ischeme = image;
		while (( *ischeme ) && ( *ischeme != ';' ))
			ischeme++;
		if ( *ischeme == ';' )
			*(ischeme++) = 0;
	
		/* ----------------------------- */
		/* Create a new compute instance */
		/* ----------------------------- */
		if (!( qptr = create_occi_os_compute(flavor,image,fscheme,ischeme) ))
		 	return( rest_html_response( aptr, 801, "Bad Request (POST COMPUTE)" ) );

		else if ((status = qptr->status) > 299 )
		{
			qptr = liberate_rest_response( qptr );
		 	return( rest_html_response( aptr, status + 4000, "Bad Request (CREATE COMPUTE FAILURE)" ) );
		}
		/* ------------------------------------------- */
		/* recover the compute instance identifier now */
		/* ------------------------------------------- */
		else if (!( occi_os_reference( qptr, pptr ) ))
		{
			qptr = liberate_rest_response( qptr );
		 	return( rest_html_response( aptr, 801, "Bad Request (NO LOCATION)" ) );
		}
		else if (!( pptr->reference ))
		{
			qptr = liberate_rest_response( qptr );
		 	return( rest_html_response( aptr, 801, "Bad Request (NO REFERENCE)" ) );
		}

		/* ------------------------------------ */
		/* GET the Compute Instance information */
		/* ------------------------------------ */
		if (!( qptr = get_occi_os_compute(pptr->reference )))
		 	return( rest_html_response( aptr, 801, "Bad Request (START COMPUTE)" ) );
		else if (!( qptr = process_occi_os_attributes( qptr )))
		 	return( rest_html_response( aptr, 801, "Bad Request (PROCESSING ATTRIBUTS)" ) );
		else if (!( hptr = occi_os_locate_attribute( qptr, "occi.compute.state" ) ))
			startcompute=1;
		else if (!( vptr = occi_os_attribute_value( hptr ) ))
			startcompute=1;
		else
		{ 
			if (!( strcmp( vptr, "active" ) ))
				startcompute=0;
			else	startcompute=1;
			liberate( vptr );
		}

		qptr = liberate_rest_response( qptr );

		/* -------------------------------------------------- */
		/* The POST COMPUTE seems to start the VM automaticly */
		/* -------------------------------------------------- */
		if ( startcompute )
		{
			/* ----------------------- */
			/* send OCCI START message */
			/* ----------------------- */
			if (!( qptr = start_occi_os_compute(pptr->reference )))
			 	return( rest_html_response( aptr, 801, "Bad Request (START COMPUTE)" ) );
			else if ((status = qptr->status) > 299 )
			{
				qptr = liberate_rest_response( qptr );
			 	return( rest_html_response( aptr, status + 4000, "Bad Request (START FAILURE)" ) );
			}
			else	qptr = liberate_rest_response( qptr );
		}

		/* ---------------------- */
		/* Allocate a Floating IP */
		/* ---------------------- */
		if (!( qptr = allocate_occi_os_floating_ip(pptr->reference)))
		 	return( rest_html_response( aptr, 801, "Bad Request (ALLOCATE FLOATING IP)" ) );
		else if ((status = qptr->status) > 299 )
		{
			qptr = liberate_rest_response( qptr );
		 	return( rest_html_response( aptr, status + 4000, "Bad Request (ALLOCATE IP FAILURE)" ) );
		}
		else	qptr = liberate_rest_response( qptr );

		/* -------------------------------- */
		/* Retrieve the Floating IP address */
		/* -------------------------------- */
		if (!( qptr = get_occi_os_compute(pptr->reference)))
		 	return( rest_html_response( aptr, 801, "Bad Request (RETRIEVE COMPUTE)" ) );
		else if (!( qptr = process_occi_os_attributes( qptr )))
		 	return( rest_html_response( aptr, 801, "Bad Request (PROCESSING ATTRIBUTS)" ) );
		{
			
			/* --------------------------------------- */
			/* establish the resulting host name value */
			/* --------------------------------------- */
			occi_os_hostname( qptr, pptr );
			qptr = liberate_rest_response( qptr );
		}

		/* ---------------------------- */
		/* launch the COSACS operations */
		/* ---------------------------- */
		cosacs_metadata_instructions( 
			pptr->hostname, _CORDS_CONFIGURATION,
			pptr->reference, OsOcciProcci.publisher );

		/* ------------------------------------- */
		/* release the public IP if not required */
		/* ------------------------------------- */
		if (!( strcasecmp( pptr->access , _CORDS_PRIVATE ) ))
		{
			if (!( qptr = release_occi_os_floating_ip(pptr->reference)))
			 	return( rest_html_response( aptr, 801, "Bad Request (RELEASE FLOATING IP)" ) );
			else	qptr = liberate_rest_response( qptr );
		}

		/* ------------------------------------------------------- */
		/* indicate that the machine is running and set start time */
		/* ------------------------------------------------------- */
		pptr->when = time((long *) 0);
		pptr->status = _OCCI_RUNNING;
		status = 0;
		if (!( status ))
		{
			sprintf(reference,"%s/%s/%s",OsOcciProcci.identity,_CORDS_OPENSTACK,pptr->id);
			if (!( occi_valid_price( pptr->price ) ))
				return( rest_html_response( aptr, 200, "OK" ) );
			else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=start", pptr->account, reference ) )
				return( rest_html_response( aptr, 200, "OK" ) );
			else	return( rest_html_response( aptr, 200, "OK" ) );
		}
		else  	return( rest_html_response( aptr, 4256, "Server Failure : OCCI Start Open Stack" ) );
	}
}

/*	-------------------------------------------	*/
/* 	  s a v e  _ o c c i_ o p e n s t a c k  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * save_occi_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	struct	os_config * kptr;
	char	reference[1024];
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->status == _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if (!(kptr = use_occi_openstack_configuration( pptr->profile )))
		return( rest_html_response( aptr, 800, "Configuration Not Found" ) );
	else
	{
		/* ------------------------- */
		/* TODO : add OCCI save code */
		/* ------------------------- */
		sprintf(reference,"%s/%s/%s",OsOcciProcci.identity,_CORDS_OPENSTACK,pptr->id);
		if (!( occi_valid_price( pptr->price ) ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=save", pptr->account, reference ) )
			return( rest_html_response( aptr, 200, "OK" ) );
		else	return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	--------------------------------------------	*/
/* 	s n a p s h o t _ o c c i_ o p e n s t a c k  	*/
/*	--------------------------------------------	*/
private	struct	rest_response * snapshot_occi_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	char	reference[1024];
	struct	os_config * kptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->status == _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if (!(kptr = use_occi_openstack_configuration( pptr->profile )))
		return( rest_html_response( aptr, 800, "Configuration Not Found" ) );
	else
	{
		/* ----------------------------- */
		/* TODO : add OCCI snapshot code */
		/* ----------------------------- */
		sprintf(reference,"%s/%s/%s",OsOcciProcci.identity,_CORDS_OPENSTACK,pptr->id);
		if (!( occi_valid_price( pptr->price ) ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=snapshot", pptr->account, reference ) )
			return( rest_html_response( aptr, 200, "OK" ) );
		else	return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	  s t o p _ o c c i_ o p e n s t a c k  	*/
/*	-------------------------------------------	*/
private	struct	rest_response * stop_occi_openstack(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	openstack * pptr;
	struct	os_config * kptr;
	struct	rest_response * qptr;
	char	reference[1024];
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else if ( pptr->status == _OCCI_IDLE )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if (!(kptr = use_occi_openstack_configuration( pptr->profile )))
		return( rest_html_response( aptr, 800, "Configuration Not Found" ) );
	else
	{
		/* ------------------------------ */
		/* TODO: send OCCI stop   message */
		/* ------------------------------ */
		if (!( qptr = stop_occi_os_compute(pptr->reference)))
		 	return( rest_html_response( aptr, 801, "Bad Request (STOP COMPUTE)" ) );
		else	qptr = liberate_rest_response( qptr );

		/* ----------------------- */
		/* Release the Floating IP */
		/* ----------------------- */
		if (!( qptr = release_occi_os_floating_ip(pptr->reference)))
		 	return( rest_html_response( aptr, 801, "Bad Request (ALLOCATE FLOATING IP)" ) );
		else	qptr = liberate_rest_response( qptr );

		/* ------------------------------ */
		/* TODO: send OCCI DELETE request */
		/* ------------------------------ */
		if (!( qptr = delete_occi_os_compute(pptr->reference) ))
		 	return( rest_html_response( aptr, 801, "Bad Request (DELETE COMPUTE)" ) );
		else	qptr = liberate_rest_response( qptr );

		pptr->status = _OCCI_IDLE;
		pptr->when = time((long *) 0);
		sprintf(reference,"%s/%s/%s",OsOcciProcci.identity,_CORDS_OPENSTACK,pptr->id);

		if (!( occi_valid_price( pptr->price ) ))
			return( rest_html_response( aptr, 200, "OK" ) );
		else if ( occi_send_transaction( _CORDS_OPENSTACK, pptr->price, "action=stop", pptr->account, reference ) )
			return( rest_html_response( aptr, 200, "OK" ) );
		else	return( rest_html_response( aptr, 200, "OK" ) );
	}
}

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
	else	return(create_openstack_contract( optr, pptr, _CORDS_CONTRACT_AGENT, default_tls()));
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
	else	return(delete_openstack_contract(optr, pptr, _CORDS_CONTRACT_AGENT, default_tls()));
}

private	struct	occi_interface	openstack_interface = {
	create_openstack,
	retrieve_openstack,
	update_openstack,
	delete_openstack
	};


	/* ---------- */
#endif	/* _occi_os_c */
	/* ---------- */

