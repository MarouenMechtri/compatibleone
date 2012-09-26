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
#ifndef	_jpaasprocci_c	
#define	_jpaasprocci_c

#include "standard.h"
#include "broker.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "cordslang.h"
#include "jpaas.h"
#include "jpaascontract.h"

#include "jpaas.c"
#include "occijpaas.c"
#include "jpaascontract.c"

struct	accords_configuration Configuration = {
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
	"europe",
	"jpaasprocci.xml",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(Configuration.debug);		}
public	int	check_verbose()		{	return(Configuration.verbose);		}
public	char *	default_publisher()	{	return(Configuration.publisher);	}
public	char *	default_operator()	{	return(Configuration.operator);		}
public	char *	default_tls()		{	return(Configuration.tls);		}
public	char *	default_zone()		{	return(Configuration.zone);		}

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

/*	---------------------------------------------------------------	*/  
/*	j p a a s p r o c c i  _ c o n f i g u r a t i o n			*/
/*	---------------------------------------------------------------	*/  
/*	this function loads jpaasprocci configuration			*/
/*	from the xml configuration file.				*/
	/*	---------------------------------------------------------------	*/  
private	void	jpaasprocci_configuration()
{
	load_accords_configuration( &Configuration, "jpaasprocci" );
	return;
}

/*	---------------------------------------------------------------	*/  
/*	j p a a s p r o c c i  _ b a n n e r					*/
/*	---------------------------------------------------------------	*/  
/*	this function will be called to display module identification 	*/
/*	when launched from the command line without any parameters.	*/
/*	---------------------------------------------------------------	*/  
private	int	jpaasprocci_banner()
{
	printf("\n   CompatibleOne JPAAS PROCCI : Version 1.0a.0.01");
	printf("\n   Beta Version : 14/09/2012 ");
	printf("\n   Copyright (c) 2012 Iain James Marshall, Prologue");
	printf("\n");
	accords_configuration_options();
	printf("\n\n");
	return(0);

}

/*	------------------------------------------- */
/*	j p a a s p r o c c i  _ i n i t i a l i s e		*/
/*	------------------------------------------- */

private	struct rest_server * jpaasprocci_initialise(  void * v,struct rest_server * sptr )
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

/*	-------------------------------------------	*/
/*	j p a a s p r o c c i  _ a u t h o r i s e 		*/
/*	------------------------------------------- 	*/
private	int	jpaasprocci_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, Configuration.user ) )
		return(0);
	else if ( strcmp( password, Configuration.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------- */
/*	j p a a s p r o c c i  _ e x t e n s i o n 		*/
/*	-------------------------------------------	*/
private	struct rest_extension * jpaasprocci_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

/*	-------------------------------------------	*/
/*	Example C R U D Method  Extension Functions 	*/
/*	-------------------------------------------	*/
/* 	   	c r e a t e _ j p a a s 		*/
/*	-------------------------------------------	*/
private	int	create_jpaas(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	jpaas * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(create_jpaas_contract(optr, pptr));
}

/*	-------------------------------------------	*/
/* 	 	r e t r i e v e _ j p a a s 	  	*/
/*	-------------------------------------------	*/
private	int	retrieve_jpaas(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	jpaas * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 		u p d a t e _ j p a a s 		*/
/*	-------------------------------------------	*/
private	int	update_jpaas(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	jpaas * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 		d e l e t e  _ j p a a s		*/
/*	-------------------------------------------	*/
private	int	delete_jpaas(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	jpaas * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(delete_jpaas_contract(optr, pptr));
}

/*	--------------------------------------------	*/
/*	CRUD Methods Relay Table			*/
/*	--------------------------------------------	*/
private	struct	occi_interface	jpaas_interface = {
	create_jpaas,
	retrieve_jpaas,
	update_jpaas,
	delete_jpaas
	};	

/*	--------------------------------------------	*/
/*	j p a a s p r o c c i  _ o p e r a t i o n 		*/
/*	--------------------------------------------	*/
/*	environment and category preparation		*/
/*	--------------------------------------------	*/
private	int	jpaasprocci_operation( char * nptr )
{

	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_jpaasprocci.xml");

	rest_initialise_log( Configuration.monitor );

	/* ---------------------------------------- */
	/* preparation of application category list */
	/* ---------------------------------------- */
	if (!( optr = occi_jpaas_builder( Configuration.domain, "jpaas" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	optr->callback  = &jpaas_interface;

	/* -------------------------------------------------------------- */
	/* this option indicates that the category is a provider category */
	/* and con be used as a legal value for the provider attribute of */
	/* a node description of a manifest.				  */
	/* -------------------------------------------------------------- */
	optr->access    |= _OCCI_PROVIDER;

	/* ---------------------------------------------*/
	/* Addition of the start, stop and save actions */
	/* these are necessary for a PROCCI to be able  */
	/* coordinate provisioning with the calls from  */
	/* the service manager for the management of    */
	/* the service life cycle.			*/
	/* ---------------------------------------------*/
	if (!( optr = occi_add_action( optr, _CORDS_START, "", start_jpaas)))
		return( 27 );
	else if (!( optr = occi_add_action( optr, _CORDS_STOP," ", stop_jpaas)))
		return( 27 );
	else if (!( optr = occi_add_action( optr, _CORDS_SAVE, "", save_jpaas)))
		return( 27 );

	if (!( Configuration.identity ))
	{
		/* --------------------------	*/
		/* launch simple occi server 	*/
		/* --------------------------	*/
		return( occi_server(  
			nptr, 
			Configuration.restport, Configuration.tls, 
			Configuration.threads, first, (char *) 0 ) );
	}
	else
	{
		/* --------------------------------------------------------------- */
		/* publication and pricing of categories before occi server launch */
		/* --------------------------------------------------------------- */
		initialise_occi_publisher( 
			Configuration.publisher, (char*) 0, (char *) 0, (char *) 0);

		return( publishing_occi_server(
				Configuration.user, Configuration.password,
				Configuration.identity,  nptr, 
				Configuration.restport, Configuration.tls, 
				Configuration.threads, first ) );
	}
}

/*	------------------------------------------- */
/*	j p a a s p r o c c i  _ o p t i o n s			*/
/*	------------------------------------------- */
/*	Command line option analysis			*/
/*	------------------------------------------- */
private	int	jpaasprocci_options(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	jpaasprocci_configuration();
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
				Configuration.verbose=1;
				continue;
			case	'd'	:
				Configuration.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( argi = accords_configuration_option( aptr, argi, argv )))
					break;
				else	continue;
			}
			status = 30;
			break;
		}
		else if (!( status = jpaasprocci_operation(aptr) ))
			continue;
		else	break;
	}
	return(status);
}

/*	--------------------------------------------	*/
/*	m a i n 					*/
/*	--------------------------------------------	*/
/*	Entry point from the command line		*/
/*	--------------------------------------------	*/
public	int	main(int argc, char * argv[] )
{
	if ( argc == 1 )
		return( jpaasprocci_banner() );
	else	return( jpaasprocci_options( argc, argv ) );
}

	/* ---------- */
#endif 	/* _jpaasprocci_c */
	/* ---------- */


