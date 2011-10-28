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
#ifndef	_broker_c
#define	_broker_c

#include "standard.h"
#include "broker.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "occibuilder.h"

struct	broker_configuration Broker = {
	0,
	0,
	0,0,0,
	(char *) 0,
	(char *) 0,
	_CORDS_DEFAULT_PUBLISHER,
	"admin", "admin",
	"http",  80,
	"xmpp",  8000,
	"domain",
	"broker.xml",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(Broker.debug);		}
public	int	check_verbose()		{	return(Broker.verbose);		}
public	char *	default_publisher()	{	return(Broker.publisher);	}
public	char *	default_tls()		{	return(Broker.tls);		}

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
/*			b r o k e r _ l o a d 		*/
/*	---------------------------------------------	*/
/*	this function loads broker    configuration	*/
/*	from the xml configuration file.		*/
/*	---------------------------------------------	*/  
private	void	broker_load()
{
	struct	xml_element * document;
	struct	xml_element * eptr;
	struct	xml_element * vptr;
	struct	xml_atribut * aptr;
	set_xml_echo(Broker.debug);
	if (( document = document_parse_file( Broker.config )) != (struct xml_element *) 0)
	{
		if ( Broker.verbose )
			printf("   Broker loading configuration from : %s \n",Broker.config);

		if (( eptr = document_element( document, "broker" )) != (struct xml_element *) 0)
		{
			if ((aptr = document_atribut( eptr, "identity" )) != (struct xml_atribut *) 0)
				Broker.identity = document_atribut_string( aptr );
			if ((aptr = document_atribut( eptr, "publisher")) != (struct xml_atribut *) 0)
				Broker.publisher = document_atribut_string( aptr );
			if ((aptr = document_atribut( eptr, "verbose")) != (struct xml_atribut *) 0)
				Broker.verbose = document_atribut_value( aptr );
			if ((aptr = document_atribut( eptr, "debug")) != (struct xml_atribut *) 0)
				Broker.debug = document_atribut_value( aptr );
			if ((aptr = document_atribut( eptr, "threads")) != (struct xml_atribut *) 0)
				Broker.threads = document_atribut_value( aptr );

			if (( vptr = document_element( eptr, "rest" )) != (struct xml_element *) 0)
			{
				if ((aptr = document_atribut( vptr, "host" )) != (struct xml_atribut *) 0)
					Broker.resthost = document_atribut_string( aptr );
				if ((aptr = document_atribut( vptr, "port" )) != (struct xml_atribut *) 0)
					Broker.restport = document_atribut_value( aptr );
			}
			if (( vptr = document_element( eptr, "security" )) != (struct xml_element *) 0)
			{
				if ((aptr = document_atribut( vptr, "user" )) != (struct xml_atribut *) 0)
					Broker.user = document_atribut_string( aptr );
				if ((aptr = document_atribut( vptr, "password"))  != (struct xml_atribut *) 0)
					Broker.password = document_atribut_string( aptr );
				if ((aptr = document_atribut( vptr, "tls" )) != (struct xml_atribut *) 0)
					if ((Broker.tls = document_atribut_string( aptr )) != 0)
						if (!( strlen(Broker.tls) ))
							Broker.tls = (char *) 0;
				if ((aptr = document_atribut( vptr, "monitor")) != (struct xml_atribut *) 0)
					Broker.monitor = document_atribut_value( aptr );
			}
			if (( vptr = document_element( eptr, "domain" )) != (struct xml_element *) 0)
			{
				if ((aptr = document_atribut( vptr, "name" )) != (struct xml_atribut *) 0)
					Broker.domain = document_atribut_string( aptr );
			}
		}
		document = document_drop( document );
	}
	else if ( Broker.verbose )
		printf("   Broker failed to load configuration from : %s \n",Broker.config);
	set_xml_echo(0);
	return;
}

#include "occibuilder.h"

private	int	banner()
{
	printf("\n   CompatibleOne Request Broker : Version 1.0a.0.02");
	printf("\n   Beta Version : 26/10/2011");
	printf("\n   Copyright (c) 2011 Iain James Marshall, Prologue");
	printf("\n");
	printf("\nOptions: ");
	printf("\n   --debug                    activates debug messages");
	printf("\n   --verbose                  activates info  messages");
	printf("\n   --threads                  activate thread handlers");
	printf("\n   --tls        <name>        specify tls configuration ");
	printf("\n   --resthost   <name>        specify rest server host name or address");
	printf("\n   --restport   <number>      specify rest server port");
	printf("\n   --chathost   <name>        specify chat server host name or address");
	printf("\n   --chatport   <number>      specify chat server port");
	printf("\n   --publisher  <name>        specify url of publisher");
	printf("\n   --identity   <name>        specify url to publish  ");
	printf("\n   --user       <name>        specify user log name   ");
	printf("\n   --password   <value>       specify user password   ");
	printf("\n\n");
	return(0);

}

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ i n i t i a l i s e			*/
/*	------------------------------------------------------------------	*/
private	struct rest_server * broker_initialise(  void * v,struct rest_server * sptr )
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
/*			b r o k e r _ a u t h o r i s e 			*/
/*	------------------------------------------------------------------	*/
private	int	broker_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, Broker.user ) )
		return(0);
	else if ( strcmp( password, Broker.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ e x t e n s i o n 			*/
/*	------------------------------------------------------------------	*/
private	struct rest_extension * broker_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

/*	------------------------------------------------------------------	*/
/* 	  actions and methods required for the broker service category		*/
/*	------------------------------------------------------------------	*/
#include "brokerservice.c"		
#include "brokerplan.c"		

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ o p e r a t i o n				*/
/*	------------------------------------------------------------------	*/
private	int	broker_operation( char * nptr )
{
	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_broker.xml");

	if (!( optr = occi_cords_action_builder( Broker.domain, "action" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = broker_plan_builder( Broker.domain,"plan" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_provider_builder( Broker.domain,"provider" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_profile_builder( Broker.domain,"profile" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = broker_service_builder( Broker.domain,"service" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if ( Broker.autopub ) optr->access   |= _OCCI_AUTO_PUBLISH;

	if (!( optr = occi_cords_configuration_builder( Broker.domain, "configuration" ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	rest_initialise_log(Broker.monitor);

	if (!( Broker.identity ))
		return( occi_server(  nptr, Broker.restport, Broker.tls, Broker.threads, first, (char *) 0 ) );
	else
	{
		initialise_occi_publisher( Broker.publisher, (char*) 0, (char *) 0, (char *) 0);
		return( publishing_occi_server(
			Broker.user, Broker.password,
			Broker.identity,  nptr, 
			Broker.restport, Broker.tls, 
			Broker.threads, first ) );
	}
}

/*	------------------------------------------------------------------	*/
/*				b r o k e r 					*/
/*	------------------------------------------------------------------	*/
private	int	broker(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	broker_load();
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
				Broker.verbose=1;
				continue;
			case	'd'	:
				Broker.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( strcmp( aptr, "auto" ) ))
					Broker.autopub = 1;
				else if (!( strcmp( aptr, "verbose" ) ))
					Broker.verbose = 1;
				else if (!( strcmp( aptr, "debug" ) ))
					Broker.debug = 1;
				else if (!( strcmp( aptr, "config" ) ))
				{
					Broker.config = allocate_string( argv[++argi] );
					broker_load();
				}
				else if (!( strcmp( aptr, "tls" ) ))
					Broker.tls = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "domain" ) ))
					Broker.domain = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "publisher" ) ))
					Broker.publisher = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "identity" ) ))
					Broker.identity = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "user" ) ))
					Broker.user = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "password" ) ))
					Broker.password = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "resthost" ) ))
					Broker.resthost = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "restport" ) ))
					Broker.restport = atoi( argv[++argi] );
				else if (!( strcmp( aptr, "chathost" ) ))
					Broker.chathost = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "chatport" ) ))
					Broker.chatport = atoi( argv[++argi] );
				else if (!( strcmp( aptr, "threads" ) ))
					Broker.threads = _REST_THREAD_WORKER;
				else	break;
				continue;
			}
			status = 30;
			break;
		}
		else if (!( status = broker_operation(aptr) ))
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
	else	return( broker( argc, argv ) );
}


	/* --------- */
#endif	/* _broker_c */
	/* --------- */

