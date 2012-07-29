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
#ifndef	_slam_c
#define	_slam_c

#include "standard.h"
#include "broker.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "occibuilder.h"
#include "occiresolver.h"
#include "cordslang.h"

struct	accords_configuration Slam = {
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
	"slam.xml",
	"europe",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(Slam.debug);		}
public	int	check_verbose()		{	return(Slam.verbose);		}
public	char *	default_publisher()	{	return(Slam.publisher);		}
public	char *	default_operator()	{	return(Slam.operator);		}
public	char *	default_tls()		{	return(Slam.tls);		}
public	char *	default_zone()		{	return(Slam.zone);		}

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
/*	 	   s l a m _ l o a d 			*/
/*	---------------------------------------------	*/
/*	this function loads slam  configuration		*/
/*	from the xml configuration file.		*/
/*	---------------------------------------------	*/  
private	void	slam_load()
{
	load_accords_configuration( &Slam, "slam" );
	return;
}

#include "occibuilder.h"

private	int	banner()
{
	printf("\n   CompatibleOne SLAM Services : Version 1.0a.0.02");
	printf("\n   Beta Version : 25/05/2012");
	printf("\n   Copyright (c) 2011, 2012 Iain James Marshall, Prologue");
	printf("\n");
	accords_configuration_options();
	printf("\n\n");
	return(0);

}

/*	------------------------------------------------------------------	*/
/*			s l a m _ i n i t i a l i s e			*/
/*	------------------------------------------------------------------	*/
private	struct rest_server * slam_initialise(  void * v,struct rest_server * sptr )
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
/*			s l a m _ a u t h o r i s e 			*/
/*	------------------------------------------------------------------	*/
private	int	slam_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, Slam.user ) )
		return(0);
	else if ( strcmp( password, Slam.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------------------------------	*/
/*			s l a m _ e x t e n s i o n 			*/
/*	------------------------------------------------------------------	*/
private	struct rest_extension * slam_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

/*	------------------------------------------------------------------	*/
/* 	  actions and methods required for the slam instance category		*/
/*	------------------------------------------------------------------	*/
#include "comonsconnection.c"

/*	------------------------------------------------------------------	*/
/*			s l a m _ o p e r a t i o n				*/
/*	------------------------------------------------------------------	*/
private	int	slam_operation( char * nptr )
{
	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_slam.xml");


	if (!( optr = occi_cords_agreement_builder( Slam.domain, "agreement" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_terms_builder( Slam.domain, "terms" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_term_builder( Slam.domain, "term" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	if (!( optr = occi_cords_variable_builder( Slam.domain, "variable" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_guarantee_builder( Slam.domain, "guarantee" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback = (void *) 0;

	if (!( optr = occi_cords_business_builder( Slam.domain, "business" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback = (void *) 0;

	if (!( optr = comons_connection_builder( Slam.domain ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	if (!( optr = comons_packet_builder( Slam.domain ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	rest_initialise_log(Slam.monitor);

	if (!( Slam.identity ))
		return( occi_server(  nptr, Slam.restport, Slam.tls, Slam.threads, first,(char *) 0 ) );
	else
	{
		initialise_occi_publisher( Slam.publisher, (char*) 0, (char *) 0, (char *) 0);
		return( publishing_occi_server(
			Slam.user, Slam.password,
			Slam.identity,  nptr, 
			Slam.restport, Slam.tls, 
			Slam.threads, first ) );
	}
}

/*	------------------------------------------------------------------	*/
/*				s l a m 					*/
/*	------------------------------------------------------------------	*/
private	int	slam(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	slam_load();
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
				Slam.verbose=1;
				continue;
			case	'd'	:
				Slam.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( argi = accords_configuration_option( aptr, argi, argv )))
					break;
				else	continue;
			}
			status = 30;
			break;
		}
		else if (!( status = slam_operation(aptr) ))
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
	else	return( slam( argc, argv ) );
}


	/* --------- */
#endif	/* _slam_c */
	/* --------- */

