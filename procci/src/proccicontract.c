/* ------------------------------------------------------------------------------------	*/
/*				 CompatibleOne Cloudware				*/
/* ------------------------------------------------------------------------------------ */
/*											*/
/* Ce fichier fait partie de ce(tte) oeuvre de Iain James Marshall et est mise a 	*/
/* disposition selon les termes de la licence Creative Commons Paternit‚ : 		*/
/*											*/
/*			 	Pas d'Utilisation Commerciale 				*/
/*				Pas de Modification 					*/
/*				3.0 non transcrit.					*/
/*											*/
/* ------------------------------------------------------------------------------------ */
/* 			Copyright (c) 2011 Iain James Marshall for Prologue 		*/
/*				   All rights reserved					*/
/* ------------------------------------------------------------------------------------ */

#ifndef	_procci_contract_c
#define	_procci_contract_c

#include "occiclient.h"
#include "occiresolver.h"
#include "cp.h"

#define	_MAX_PROVIDERS	6

private	char *	occi_providers[_MAX_PROVIDERS] = {
	(char *) _CORDS_OPENSTACK,
	(char *) _CORDS_OPENNEBULA,
	(char *) _CORDS_WINDOWSAZURE,
	(char *) _CORDS_PROACTIVE,
	(char *) _CORDS_SLAPOS,
	(char *) "amazon"
	};


/*	---------------------------------------------------------	*/
/*	 r e t r i e v e _ c a r r i e r _ i n f o r m a t i o n	*/
/*	---------------------------------------------------------	*/
private	int	retrieve_provider_information( struct cords_contract * pptr )
{
	struct	occi_response *	zptr;
	struct	occi_element *  fptr;
	struct	occi_client *   cptr;
	struct	occi_request *  qptr;
	char	*		sptr;
	char	buffer[1024];

	sprintf(buffer,"occi.%s.",pptr->profile);

	if (!( zptr = occi_simple_get( pptr->provider, _CORDS_CONTRACT_AGENT, Procci.tls ) ))
		return( 400 );
	for (	fptr = zptr->first;
		fptr != (struct occi_element *) 0;
		fptr = fptr->next )
	{
		if (!( sptr = fptr->name ))
			continue;
		else if ( strncmp( sptr, buffer,strlen(buffer) ) != 0 )
			continue;
		else 	sptr += strlen( buffer );
		if (!( strcmp( sptr,"hostname" ) ))
		{
			if ( pptr->hostname ) pptr->hostname = liberate( pptr->hostname );
			if (!( pptr->hostname = occi_unquoted_value( fptr->value ) ))
		 		return( 400 );
		}
		else if (!( strcmp( sptr,"rootpass" ) ))
		{
			if ( pptr->rootpass ) pptr->rootpass = liberate( pptr->rootpass );
			if (!( pptr->rootpass = occi_unquoted_value( fptr->value ) ))
				return( 400 );
		}
		else if (!( strcmp( sptr,"reference" ) ))
		{
			if ( pptr->reference ) pptr->reference = liberate( pptr->reference );
			if (!( pptr->reference = occi_unquoted_value( fptr->value ) ))
				return( 400 );
		}
	}
	return( 0 );
}

/*	-------------------------------------------	*/
/* 	 c o n t r a c t _ i n s t r u c t i o n s
/*	-------------------------------------------	*/
/*	this function retrives the list of contract	*/
/*	configuration instructions selected by the 	*/
/*	target or configured machine contract id	*/
/*	and this with an aim to registering the		*/
/*	provider contract id allowing recognition	*/
/*	of the same collection through the provider	*/
/*	contract id.					*/
/*	-------------------------------------------	*/
private	int	contract_instructions( char * contract, char * provision )
{

	char	*	ihost;
	char 	*	vptr;

	struct	occi_response * zptr=(struct occi_response *) 0;
	struct	occi_response * zzptr=(struct occi_response *) 0;
	struct	occi_response * yptr=(struct occi_response *) 0;
	struct	occi_element  * fptr=(struct occi_element  *) 0;
	struct	occi_element  * eptr=(struct occi_element  *) 0;
	struct	occi_client   * kptr=(struct occi_client   *) 0;
	struct	occi_request  * qptr=(struct occi_request  *) 0;
	char	buffer[4096];
	char	tempname[4096];
	int	length=0;

	if (!( ihost = occi_resolve_category_provider( _CORDS_INSTRUCTION, _CORDS_CONTRACT_AGENT, Procci.tls ) ))
	 	return( 401 );

	sprintf(buffer,"%s/%s/",ihost,_CORDS_INSTRUCTION);
	liberate( ihost );
	length = strlen(buffer);

	if (!( kptr = occi_create_client( buffer, _CORDS_CONTRACT_AGENT, Procci.tls ) ))
		return( 401 );

	else if (!(qptr = occi_create_request( 
			kptr, 
			kptr->target->object, 
			_OCCI_NORMAL )))
		return(401);
	else if (!( fptr = occi_request_element( 
			qptr,
			"occi.instruction.target", contract ) ))
	{
		qptr = occi_remove_request( qptr );
		return( 401 );
	}
	else if (!( yptr = occi_client_get( kptr, qptr ) ))
	{
		qptr = occi_remove_request( qptr );
		return( 401 );
	}

	qptr = occi_remove_request ( qptr );

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

		if (( zptr = occi_simple_get( buffer, _CORDS_CONTRACT_AGENT, Procci.tls )) != (struct occi_response *) 0)
		{
			if (!(fptr = occi_locate_element( zptr->first, "occi.instruction.provision" )))
				zptr = occi_remove_response ( zptr );
			else
			{
				if ( fptr->value ) fptr->value = liberate( fptr->value );
				fptr->value = allocate_string( provision );
				zzptr = occi_simple_put( buffer, zptr->first, _CORDS_CONTRACT_AGENT, Procci.tls);
				zzptr = occi_remove_response ( zzptr );
				zptr = occi_remove_response ( zptr );
			}
		}

		/* quick reset of base url */
		/* ----------------------- */
		buffer[length] = 0;
	}

	yptr = occi_remove_response ( yptr );

	return(0);
}

/*	-------------------------------------------	*/
/* 	       s t a r t _ c o n t r a c t
/*	-------------------------------------------	*/
private	struct	rest_response * start_contract(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_contract * pptr;
	char	fullid[2048];
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else
	{
		if ( pptr->state == _OCCI_IDLE )
		{
			sprintf(fullid,"%s/%s/%s",Procci.identity,_CORDS_CONTRACT,pptr->id);
			contract_instructions( fullid, pptr->provider );
			cords_invoke_action( pptr->provider, "start", _CORDS_CONTRACT_AGENT, Procci.tls );
			retrieve_provider_information( pptr );
			pptr->when  = time((long*)0); 
			pptr->state = _OCCI_RUNNING;
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}


/*	-------------------------------------------	*/
/* 	   r e s t a r t _ c o n t r a c t
/*	-------------------------------------------	*/
private	struct	rest_response * restart_contract(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_contract * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else
	{
		if ( pptr->state == _OCCI_SUSPENDED )
		{
			cords_invoke_action( pptr->provider, "restart", _CORDS_CONTRACT_AGENT, Procci.tls );
			pptr->when  = time((long*)0); 
			pptr->state = _OCCI_RUNNING;
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}



/*	-------------------------------------------	*/
/* 	   s u s p e n d _ c o n t r a c t
/*	-------------------------------------------	*/
private	struct	rest_response * suspend_contract(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_contract * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else
	{
		if ( pptr->state == _OCCI_RUNNING )
		{
			cords_invoke_action( pptr->provider, "suspend", _CORDS_CONTRACT_AGENT, Procci.tls );
			pptr->when  = time((long*) 0);
			pptr->state = _OCCI_SUSPENDED;
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	   	s t o p _ c o n t r a c t
/*	-------------------------------------------	*/
private	struct	rest_response * stop_contract(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_contract * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	{
		if ( pptr->state != _OCCI_IDLE )
		{
			cords_invoke_action( pptr->provider, "stop", _CORDS_CONTRACT_AGENT, Procci.tls );
			if (pptr->reference) pptr->reference = liberate( pptr->reference );
			if (pptr->rootpass ) pptr->rootpass  = liberate( pptr->rootpass  );
			if (pptr->hostname ) pptr->hostname  = liberate( pptr->hostname  );
			pptr->reference =allocate_string("");
			pptr->rootpass  =allocate_string("");
			pptr->hostname  =allocate_string("");
			pptr->when  = time((long*) 0);
			pptr->state = _OCCI_IDLE;
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	   	s a v e _ c o n t r a c t
/*	-------------------------------------------	*/
private	struct	rest_response * save_contract(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_contract * pptr;
	if (!( pptr = vptr ))
	 	return( rest_html_response( aptr, 404, "Invalid Action" ) );
	else
	{
		if ( pptr->state != _OCCI_IDLE )
		{
			cords_invoke_action( pptr->provider, "save", _CORDS_CONTRACT_AGENT,Procci.tls );
			pptr->when  = time((long*) 0);
		}
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	------------------------------------------------------------------	*/
/*		p r o c c i _ c o n t r a c t _ b u i l d e r			*/
/*	------------------------------------------------------------------	*/
private	struct	occi_category *	procci_contract_builder( char * domain, char * category )
{
	struct	occi_category * optr;
	initialise_occi_resolver( _DEFAULT_PUBLISHER, (char *) 0, (char *) 0, (char *) 0 );
	if (!( optr = occi_cords_contract_builder( domain ,category ) ))
		return( optr );
	else if (!( optr = occi_add_action( optr,"start","",start_contract)))
		return( optr );
	else if (!( optr = occi_add_action( optr,"suspend","",suspend_contract)))
		return( optr );
	else if (!( optr = occi_add_action( optr,"restart","",restart_contract)))
		return( optr );
	else if (!( optr = occi_add_action( optr,"save","",save_contract)))
		return( optr );
	else if (!( optr = occi_add_action( optr,"stop","",stop_contract)))
		return( optr );
	else	return( optr );
}

#endif	/* _procci_contract_c */
	/* ----------------- */

