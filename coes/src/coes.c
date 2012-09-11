/* -------------------------------------------------------------------- */
/*  ACCORDS PLATFORM                                                    */
/*  (C) 2011 by Iain James Marshall (Prologue) <ijm667@hotmail.com>     */
/* -------------------------------------------------------------------- */
/* Licensed under the Apache License, Version 2.0 (the "License"); 	*/
/* you may not use this file except in compliance with the License. 	*/
/* You may obtain a copy of the License at 				*/
/*  									*/
/*  http://www.apache.org/licenses/LICENSE-2.0 				*/
/*  									*/
/* Unless required by applicable law or agreed to in writing, software 	*/
/* distributed under the License is distributed on an "AS IS" BASIS, 	*/
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 	*/
/* implied. 								*/
/* See the License for the specific language governing permissions and 	*/
/* limitations under the License. 					*/
/* -------------------------------------------------------------------- */
#ifndef	_coes_c
#define	_coes_c

#include "standard.h"
#include "broker.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "occiresolver.h"
#include "occibuilder.h"

struct	accords_configuration Coes = {
	0,0,
	0,0,0,0,
	(char *) 0,
	(char *) 0, 
	_CORDS_DEFAULT_PUBLISHER,
	_CORDS_DEFAULT_OPERATOR,
	_CORDS_DEFAULT_USER,
	_CORDS_DEFAULT_PASSWORD,
	"http",  80,
	"xmpp",  8000,
	"domain",
	"coes.xml",
	"europe",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(Coes.debug);		}
public	int	check_verbose()		{	return(Coes.verbose);		}
public	char *	default_publisher()	{	return(Coes.publisher);		}
public	char *	default_operator()	{	return(Coes.operator);		}
public	char *	default_tls()		{	return(Coes.tls);		}
public	char *	default_zone()		{	return(Coes.zone);		}

public	int	failure( int e, char * m1, char * m2 )
{
	if ( e )
	{
		printf("\n*** failure %u",e);
		if ( m1 )
			printf(" : %s",m1);
		if ( m2 )
			printf(" : %s",m2);
		printf(" **`\n");
	}
	return( e );
}

/*	---------------------------------------------	*/  
/*		c o e s _ l o a d 		*/
/*	---------------------------------------------	*/
/*	this function loads coes  configuration	*/
/*	from the xml configuration file.		*/
/*	---------------------------------------------	*/  
private	void	coes_load()
{
	load_accords_configuration( &Coes, "coes" );
	return;
}

#include "occibuilder.h"

private	int	banner()
{
	printf("\n   CompatibleOne Elasticity Services COES : Version 1.0a.0.08");
	printf("\n   Beta Version : 25/05/2012");
	printf("\n   Copyright (c) 2011, 2012 Iain James Marshall, Prologue");
	printf("\n");
	accords_configuration_options();
	printf("\n\n");
	return(0);

}

/*	------------------------------------------------------------------	*/
/*			c o e s _ i n i t i a l i s e			*/
/*	------------------------------------------------------------------	*/
private	struct rest_server * coes_initialise(  void * v,struct rest_server * sptr )
{
	struct	rest_extension * xptr;
	if (!( xptr = rest_add_extension( sptr ) ))
		return((struct rest_server *) 0);
	else
	{
		xptr->net = (struct connection *) 0;
		return( sptr );
	}
}

/*	------------------------------------------------------------------	*/
/*			c o e s _ a u t h o r i s e 			*/
/*	------------------------------------------------------------------	*/
private	int	coes_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, Coes.user ) )
		return(0);
	else if ( strcmp( password, Coes.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------------------------------	*/
/*			c o e s _ e x t e n s i o n 				*/
/*	------------------------------------------------------------------	*/
private	struct rest_extension * coes_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

#include "comonsconnection.c"

/*	-----------------------------------------------------------	*/
/*			s e l e c t _ p l a c e m e n t			*/
/*	-----------------------------------------------------------	*/
private	char *	select_placement( struct occi_response * zptr )
{
	struct	occi_element 	* eptr;
	for (	eptr = zptr->first;
		eptr != (struct occi_element*) 0;
		eptr = eptr->next )
	{
		if (!( eptr->name ))
			continue;
		else if (!( eptr->value ))
			continue;
		else 	return( allocate_string( eptr->value ) );
	}
	return((char *) 0);
}

/*	-----------------------------------------------------------	*/
/*			d e f a u l t _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	default_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( zptr = occi_resolver( pptr->provider, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	-----------------------------------------------------------	*/
/*		p r i c e _ b a s e d _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	price_based_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( strcmp( pptr->price, "any" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( zptr = occi_resolve_by_price( pptr->provider,  pptr->price, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	-----------------------------------------------------------	*/
/*		s e c u r i t y _ b a s e d _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	security_based_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( pptr->security ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->security, "any" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( zptr = occi_resolve_by_security( pptr->provider, pptr->security, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	-----------------------------------------------------------	*/
/*		e n e r g y _ b a s e d _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	energy_based_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( pptr->energy ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->energy, "any" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( zptr = occi_resolve_by_energy( pptr->provider, pptr->energy, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	-----------------------------------------------------------	*/
/*		  z o n e _ b a s e d _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	zone_based_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( pptr->zone ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->zone, "any" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( zptr = occi_resolve_by_zone( pptr->provider, pptr->zone, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	-----------------------------------------------------------	*/
/*		o p e r a t o r _ b a s e d _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	operator_based_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( pptr->operator ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->operator, "any" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( zptr = occi_resolve_by_operator( pptr->provider, pptr->operator, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	-----------------------------------------------------------	*/
/*		s c o r e _ b a s e d _ p l a c e m e n t		*/
/*	-----------------------------------------------------------	*/
private	int	score_based_placement(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	struct	occi_response 	* zptr;
	if (!( pptr->opinion ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->opinion, "any" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( zptr = occi_resolve_by_score( pptr->provider, pptr->opinion, agent ) ))
		return( 48 );
	else if (!( pptr->solution = select_placement( zptr ) ))
		return( 30 );
	else	return( 0  );
}

/*	--------------------------------------------------	*/
/*	c r e a t e _ p l a c e m e n t _ s o l u t i o n	*/
/*	--------------------------------------------------	*/
/*	this will analyse the placement request and choose	*/
/*	an appropriate placement based on the node, zone &	*/
/*	provider information.					*/
/*	--------------------------------------------------	*/
private	int	create_placement_solution(
		struct occi_category * optr, 
		struct cords_placement * pptr,
		char * agent,
		char * tls )
{
	if ( pptr->solution )
	{
		liberate( pptr->solution );
		pptr->solution = (char *) 0;
	}

	/* -------------------------------------------------- */
	/* ensure at least the default algorithm is specified */
	/* -------------------------------------------------- */
	if (!( pptr->algorithm ))
		pptr->algorithm = allocate_string( "default" );

	else if (!( strcmp( pptr->algorithm, _CORDS_NULL ) ))
	{
		pptr->algorithm = liberate( pptr->algorithm );
		if (!( pptr->algorithm = allocate_string( "default" ) ))
			return( 27 );
	}

	/* -------------------------------------------------- */
	/* select by  indicated placement algorithm operation */
	/* -------------------------------------------------- */
	if (!( strcmp( pptr->algorithm, "default" ) ))
		return( default_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->algorithm, "price" ) ))
		return( price_based_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->algorithm, "zone" ) ))
		return( zone_based_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->algorithm, "energy" ) ))
		return( energy_based_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->algorithm, "security" ) ))
		return( security_based_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->algorithm, "operator" ) ))
		return( operator_based_placement( optr, pptr, agent, tls ) );
	else if (!( strcmp( pptr->algorithm, "scoring" ) ))
		return( score_based_placement( optr, pptr, agent, tls ) );
	else	return( 78 );
}

/*	-------------------------------------------	*/
/* 	    c o n s u m e  _ p l a c e m e n t 		*/
/*	-------------------------------------------	*/
/*	the placement has been provisioned and is	*/
/*	now active and deployed.			*/
/*	-------------------------------------------	*/
private	struct rest_response * consume_placement(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_placement * pptr;
	if (!( pptr = vptr ))
		return( rest_html_response( aptr, 400, "Incorrect Message Category" ) );
	else if ( pptr->state != 1 )
		return( rest_html_response( aptr, 200, "OK" ) );
	else 
	{
		pptr->state=2;
		autosave_cords_placement_nodes();
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}
	
/*	-------------------------------------------	*/
/* 	    r e s t o r e  _ p l a c e m e n t 		*/
/*	-------------------------------------------	*/
/*	the placement is reserved but no longer is	*/
/*	provisioned and deployed.			*/
/*	-------------------------------------------	*/
private	struct rest_response * restore_placement(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_placement * pptr;
	if (!( pptr = vptr ))
		return( rest_html_response( aptr, 400, "Incorrect Message Category" ) );
	else if ( pptr->state != 2 )
		return( rest_html_response( aptr, 200, "OK" ) );
	else 
	{
		pptr->state=1;
		autosave_cords_placement_nodes();
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}
	
/*	-------------------------------------------	*/
/* 	    r e l e a s e  _ p l a c e m e n t 		*/
/*	-------------------------------------------	*/
/*	the placement is no longer reserved		*/
/*	-------------------------------------------	*/
private	struct rest_response * release_placement(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_placement * pptr;
	if (!( pptr = vptr ))
		return( rest_html_response( aptr, 400, "Incorrect Message Category" ) );
	else if (!( pptr->state ))
		return( rest_html_response( aptr, 200, "OK" ) );
	else 
	{
		pptr->state=0;
		autosave_cords_placement_nodes();
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}
	
/*	-------------------------------------------	*/
/* 	      c h o o s e  _ p l a c e m e n t 		*/
/*	-------------------------------------------	*/
private	struct rest_response * choose_placement(
		struct occi_category * optr, 
		struct rest_client * cptr, 
		struct rest_request * rptr, 
		struct rest_response * aptr, 
		void * vptr )
{
	struct	cords_placement * pptr;
	int	status;
	if (!( pptr = vptr ))
		return( rest_html_response( aptr, 400, "Incorrect Message Category" ) );
	else if ( pptr->state > 0 )
		return( rest_html_response( aptr, 200, "OK" ) );
	else if ((status = create_placement_solution(optr, pptr, _CORDS_CONTRACT_AGENT, default_tls() )) != 0)
		return( rest_html_response( aptr, status, "PLACEMENT FAILURE" ) );
	else 
	{
		pptr->state = 1;
		autosave_cords_placement_nodes();
		return( rest_html_response( aptr, 200, "OK" ) );
	}
}

/*	-------------------------------------------	*/
/* 	      c r e a t e _ p l a c e m e n t  		*/
/*	-------------------------------------------	*/
private	int	create_placement(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_placement * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else if (!( pptr->node ))
		return( 0 ); 
	else	return( 0 );
}

/*	-------------------------------------------	*/
/* 	    r e t r i e v e _ p l a c e m e n t  	*/
/*	-------------------------------------------	*/
private	int	retrieve_placement(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_placement * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	      u p d a t e _ p l a c e m e n t 	 	*/
/*	-------------------------------------------	*/
private	int	update_placement(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_placement * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	      d e l e t e _ p l a c e m e n t  		*/
/*	-------------------------------------------	*/
private	int	delete_placement(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_placement * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

private	struct	occi_interface	placement_interface = {
	create_placement,
	retrieve_placement,
	update_placement,
	delete_placement
	};


/*	------------------------------------------------------------------	*/
/*			c o e s _ o p e r a t i o n				*/
/*	------------------------------------------------------------------	*/
private	int	coes_operation( char * nptr )
{
	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_coes.xml");

	if (!( optr = occi_cords_placement_builder( Coes.domain, "placement" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = &placement_interface;

	if (!( optr = occi_add_action( optr,_CORDS_CHOOSE,"",choose_placement)))
		return( 28 );
	else if (!( optr = occi_add_action( optr,"consume","",consume_placement)))
		return( 28 );
	else if (!( optr = occi_add_action( optr,"restore","",restore_placement)))
		return( 28 );
	else if (!( optr = occi_add_action( optr,"release","",release_placement)))
		return( 28 );

	if (!( optr = comons_connection_builder( Coes.domain ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	if (!( optr = comons_packet_builder( Coes.domain, "packet_coes.xml" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	if (!( optr = occi_cords_algorithm_builder( Coes.domain, "algorithm" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_quota_builder( Coes.domain, "quota" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	rest_initialise_log( Coes.monitor );

	if (!( Coes.identity ))
		return( occi_server(  nptr, Coes.restport, Coes.tls, Coes.threads, first, (char *) 0 ) );
	else
	{
		initialise_occi_publisher( Coes.publisher, (char*) 0, (char *) 0, (char *) 0);
		return( publishing_occi_server(
			Coes.user, Coes.password,
			Coes.identity,  nptr, 
			Coes.restport, Coes.tls, 
			Coes.threads, first ) );
	}
}

/*	------------------------------------------------------------------	*/
/*				c o e s 					*/
/*	------------------------------------------------------------------	*/
private	int	coes(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	coes_load();
	while ( argi < argc )
	{
		if (!( aptr = argv[++argi] ))
			break;
		else if ( *aptr == '-' )
		{
			aptr++;
			switch( *(aptr++) )
			{
			case	'v'	:
				Coes.verbose=1;
				continue;
			case	'd'	:
				Coes.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( argi = accords_configuration_option( aptr, argi, argv )))
					break;
				else	continue;
			}
			status = 30;
			break;
		}
		else if (!( status = coes_operation(aptr) ))
			continue;
		else	break;
	}
	return(status);
}

/*	------------------------------------------------------------------	*/
/*					m a i n 				*/
/*	------------------------------------------------------------------	*/
public	int	main(int argc, char * argv[] )
{
	if ( argc == 1 )
		return( banner() );
	else	return( coes( argc, argv ) );
}


	/* --------- */
#endif	/* _coes_c */
	/* --------- */

