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
#ifndef	_coees_c
#define	_coees_c

#include "standard.h"
#include "broker.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "occiresolver.h"
#include "occibuilder.h"

struct	accords_configuration Coees = {
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
	"coees.xml",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(Coees.debug);		}
public	int	check_verbose()		{	return(Coees.verbose);		}
public	char *	default_publisher()	{	return(Coees.publisher);		}
public	char *	default_operator()	{	return(Coees.operator);		}
public	char *	default_tls()		{	return(Coees.tls);		}

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
/*		c o e e s _ l o a d 			*/
/*	---------------------------------------------	*/
/*	this function loads coees  configuration	*/
/*	from the xml configuration file.		*/
/*	---------------------------------------------	*/  
private	void	coees_load()
{
	load_accords_configuration( &Coees, "coees" );
	return;
}

#include "occibuilder.h"

private	int	banner()
{
	printf("\n   CompatibleOne Energy Efficiency Services COEES : Version 1.0a.0.02");
	printf("\n   Beta Version : 02/02/2012");
	printf("\n   Copyright (c) 2012 Iain James Marshall, Prologue");
	printf("\n");
	accords_configuration_options();
	printf("\n\n");
	return(0);

}

/*	------------------------------------------------------------------	*/
/*			c o e e s _ i n i t i a l i s e				*/
/*	------------------------------------------------------------------	*/
private	struct rest_server * coees_initialise(  void * v,struct rest_server * sptr )
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
/*			c o e e s _ a u t h o r i s e 				*/
/*	------------------------------------------------------------------	*/
private	int	coees_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, Coees.user ) )
		return(0);
	else if ( strcmp( password, Coees.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------------------------------	*/
/*			c o e e s _ e x t e n s i o n 				*/
/*	------------------------------------------------------------------	*/
private	struct rest_extension * coees_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

/*	------------------------------------------------------------------	*/
/*			c o e e s _ o p e r a t i o n				*/
/*	------------------------------------------------------------------	*/
private	int	coees_operation( char * nptr )
{
	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_coees.xml");

	if (!( optr = occi_cords_optimise_builder( Coees.domain, "optimise" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_connection_builder( Coees.domain, "connection" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback = (void *) 0;
	optr->access |= (_OCCI_PRIVATE | _OCCI_CONSUMER);

	rest_initialise_log( Coees.monitor );

	if (!( Coees.identity ))
		return( occi_server(  nptr, Coees.restport, Coees.tls, Coees.threads, first, (char *) 0 ) );
	else
	{
		initialise_occi_publisher( Coees.publisher, (char*) 0, (char *) 0, (char *) 0);
		return( publishing_occi_server(
			Coees.user, Coees.password,
			Coees.identity,  nptr, 
			Coees.restport, Coees.tls, 
			Coees.threads, first ) );
	}
}

/*	------------------------------------------------------------------	*/
/*				c o e e s 					*/
/*	------------------------------------------------------------------	*/
private	int	coees(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	coees_load();
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
				Coees.verbose=1;
				continue;
			case	'd'	:
				Coees.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( argi = accords_configuration_option( aptr, argi, argv )))
					break;
				else	continue;
			}
			status = 30;
			break;
		}
		else if (!( status = coees_operation(aptr) ))
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
	else	return( coees( argc, argv ) );
}


	/* --------- */
#endif	/* _coees_c */
	/* --------- */

