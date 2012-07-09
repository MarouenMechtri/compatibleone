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
#ifndef	_example_c	
#define	_example_c

#include "standard.h"
#include "broker.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"

/* 	----------------------------------------	*/	
/*	Prototype Contract Negotiation Functions	*/
/* 	----------------------------------------	*/
#include "exampleprocci.h"
#include "exampleprocci.c"
#include "occiexampleprocci.c"
#include "contract.h"
#include "contract.c"

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
	"example.xml",
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
/*	e x a m p l e _ c o n f i g u r a t i o n			*/
/*	---------------------------------------------------------------	*/  
/*	this function loads example configuration			*/
/*	from the xml configuration file.				*/
	/*	---------------------------------------------------------------	*/  
private	void	example_configuration()
{
	load_accords_configuration( &Configuration, "example" );
	return;
}

/*	---------------------------------------------------------------	*/  
/*	e x a m p l e _ b a n n e r					*/
/*	---------------------------------------------------------------	*/  
/*	this function will be called to display module identification 	*/
/*	when launched from the command line without any parameters.	*/
/*	---------------------------------------------------------------	*/  
private	int	example_banner()
{
	printf("\n   CompatibleOne Example Service : Version 1.0a.0.01");
	printf("\n   Beta Version : 06/06/2012 ");
	printf("\n   Copyright (c) 2012 Iain James Marshall, Prologue");
	printf("\n");
	accords_configuration_options();
	printf("\n\n");
	return(0);

}

/*	------------------------------------------- */
/*	e x a m p l e _ i n i t i a l i s e		*/
/*	------------------------------------------- */

private	struct rest_server * example_initialise(  void * v,struct rest_server * sptr )
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
/*	e x a m p l e _ a u t h o r i s e 		*/
/*	------------------------------------------- 	*/
private	int	example_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
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
/*	e x a m p l e _ e x t e n s i o n 		*/
/*	-------------------------------------------	*/
private	struct rest_extension * example_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

/*	-------------------------------------------	*/
/*	Example C R U D Method  Extension Functions 	*/
/*	-------------------------------------------	*/
/* 	   c r e a t e _ e x a m p l e  		*/
/*	-------------------------------------------	*/
private	int	create_example(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	exampleprocci * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(create_example_contract(optr, pptr));
}

/*	-------------------------------------------	*/
/* 	 r e t r i e v e _ e x a m p l e 	*/
/*	-------------------------------------------	*/
private	int	retrieve_example(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_contract * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	   u p d a t e _ e x a m p l e		*/
/*	-------------------------------------------	*/
private	int	update_example(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_contract * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	   d e l e t e  _ e x a m p l e 		*/
/*	-------------------------------------------	*/
private	int	delete_example(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	exampleprocci * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(delete_example_contract(optr, pptr));
}

/*	--------------------------------------------	*/
/*	CRUD Methods Relay Table			*/
/*	--------------------------------------------	*/
private	struct	occi_interface	example_interface = {
	create_example,
	retrieve_example,
	update_example,
	delete_example
	};	

/*	--------------------------------------------	*/
/*	e x a m p l e _ o p e r a t i o n 		*/
/*	--------------------------------------------	*/
/*	environment and category preparation		*/
/*	--------------------------------------------	*/
private	int	example_operation( char * nptr )
{

	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_example.xml");

	rest_initialise_log( Configuration.monitor );

	/* ---------------------------------------- */
	/* preparation of application category list */
	/* ---------------------------------------- */
	if (!( optr = occi_exampleprocci_builder( Configuration.domain, "example" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = &example_interface;
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
	if (!( optr = occi_add_action( optr, "start", "", start_example)))
		return( 27 );
	else if (!( optr = occi_add_action( optr, "stop"," ", stop_example)))
		return( 27 );
	else if (!( optr = occi_add_action( optr, "save", "", save_example)))
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
/*	e x a m p l e _ o p t i o n s			*/
/*	------------------------------------------- */
/*	Command line option analysis			*/
/*	------------------------------------------- */
private	int	example_options(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	example_configuration();
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
		else if (!( status = example_operation(aptr) ))
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
		return( example_banner() );
	else	return( example_options( argc, argv ) );
}

	/* ---------- */
#endif 	/* _example_c */
	/* ---------- */


