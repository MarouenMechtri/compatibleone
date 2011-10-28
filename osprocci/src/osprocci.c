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
#ifndef	_osprocci_c
#define	_osprocci_c

#include "standard.h"
#include "procci.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "occibuilder.h"

struct	procci_configuration OsProcci = {
	0,
	0,0,0,
	(char *) 0,
	(char *) 0, (char *) 0,
	"admin", "admin",
	"http",  80,
	"xmpp",  8000,
	"domain",
	"osprocci.xml",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(OsProcci.debug);		}
public	int	check_verbose()		{	return(OsProcci.verbose);	}
public	char *	default_publisher()	{	return(OsProcci.publisher);	}
public	char *	default_tls()		{	return(OsProcci.tls);		}

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
/*		 o s p r o c c i _ l o a d 		*/
/*	---------------------------------------------	*/
/*	this function loads osprocci    configuration	*/
/*	from the xml configuration file.		*/
/*	---------------------------------------------	*/  
private	void	osprocci_load()
{
	struct	xml_element * document;
	struct	xml_element * eptr;
	struct	xml_element * vptr;
	struct	xml_atribut * aptr;
	set_xml_echo(OsProcci.debug);
	if (( document = document_parse_file( OsProcci.config )) != (struct xml_element *) 0)
	{
		if ( OsProcci.verbose )
			printf("   OsProcci loading configuration from : %s \n",OsProcci.config);

		if (( eptr = document_element( document, "osprocci" )) != (struct xml_element *) 0)
		{
			if ((aptr = document_atribut( eptr, "identity" )) != (struct xml_atribut *) 0)
				OsProcci.identity = document_atribut_string( aptr );
			if ((aptr = document_atribut( eptr, "publisher")) != (struct xml_atribut *) 0)
				OsProcci.publisher = document_atribut_string( aptr );
			if ((aptr = document_atribut( eptr, "verbose")) != (struct xml_atribut *) 0)
				OsProcci.verbose = document_atribut_value( aptr );
			if ((aptr = document_atribut( eptr, "debug")) != (struct xml_atribut *) 0)
				OsProcci.debug = document_atribut_value( aptr );
			if ((aptr = document_atribut( eptr, "threads")) != (struct xml_atribut *) 0)
				OsProcci.threads = document_atribut_value( aptr );

			if (( vptr = document_element( eptr, "rest" )) != (struct xml_element *) 0)
			{
				if ((aptr = document_atribut( vptr, "host" )) != (struct xml_atribut *) 0)
					OsProcci.resthost = document_atribut_string( aptr );
				if ((aptr = document_atribut( vptr, "port" )) != (struct xml_atribut *) 0)
					OsProcci.restport = document_atribut_value( aptr );
			}
			if (( vptr = document_element( eptr, "security" )) != (struct xml_element *) 0)
			{
				if ((aptr = document_atribut( vptr, "user" )) != (struct xml_atribut *) 0)
					OsProcci.user = document_atribut_string( aptr );
				if ((aptr = document_atribut( vptr, "password"))  != (struct xml_atribut *) 0)
					OsProcci.password = document_atribut_string( aptr );
				if ((aptr = document_atribut( vptr, "tls" )) != (struct xml_atribut *) 0)
					if ((OsProcci.tls = document_atribut_string( aptr )) != 0)
						if (!( strlen(OsProcci.tls) ))
							OsProcci.tls = (char *) 0;
				if ((aptr = document_atribut( vptr, "monitor")) != (struct xml_atribut *) 0)
					OsProcci.monitor = document_atribut_value( aptr );
			}
			if (( vptr = document_element( eptr, "domain" )) != (struct xml_element *) 0)
			{
				if ((aptr = document_atribut( vptr, "name" )) != (struct xml_atribut *) 0)
					OsProcci.domain = document_atribut_string( aptr );
			}
		}
		document = document_drop( document );
	}
	else if ( OsProcci.verbose )
		printf("   OsProcci failed to load configuration from : %s \n",OsProcci.config);
	set_xml_echo(0);
	return;
}

private	int	banner()
{
	printf("\n   CompatibleOne Open Stack OsProcci : Version 1.0a.0.02");
	printf("\n   Beta Version : 26/10/2011");
	printf("\n   Copyright (c) 2011 Iain James Marshall, Prologue ");
	printf("\n");
	printf("\nOptions: ");
	printf("\n   --debug                    activates debug messages");
	printf("\n   --verbose                  activates info  messages");
	printf("\n   --tls        <name>        specify tls configuration ");
	printf("\n   --threads                  activate thread handlers");
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
/*			o s p r o c c i _ i n i t i a l i s e			*/
/*	------------------------------------------------------------------	*/
private	struct rest_server * osprocci_initialise(  void * v,struct rest_server * sptr )
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
/*			o s p r o c c i _ a u t h o r i s e 			*/
/*	------------------------------------------------------------------	*/
private	int	osprocci_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, OsProcci.user ) )
		return(0);
	else if ( strcmp( password, OsProcci.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------------------------------	*/
/*			o s p r o c c i _ e x t e n s i o n 			*/
/*	------------------------------------------------------------------	*/
private	struct rest_extension * osprocci_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

#include "proccios.c"

/*	------------------------------------------------------------------	*/
/*			o s p r o c c i _ o p e r a t i o n				*/
/*	------------------------------------------------------------------	*/
private	int	osprocci_operation( char * nptr )
{

	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_openstack.xml");

	if (!( optr = build_openstack( OsProcci.domain ) ))
		return( 27 );

	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;


	if (!( optr = build_openstack_configuration( OsProcci.domain ) ))
		return( 27 );

	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;

	rest_initialise_log( OsProcci.monitor );

	if (!( OsProcci.identity ))
		return( occi_server(  nptr, OsProcci.restport, OsProcci.tls, OsProcci.threads, first, (char *) 0 ) );
	else
	{
		initialise_occi_publisher( OsProcci.publisher, (char*) 0, (char *) 0, (char *) 0);
		return( publishing_occi_server(
			OsProcci.user, OsProcci.password,
			OsProcci.identity,  nptr, 
			OsProcci.restport, OsProcci.tls, 
			OsProcci.threads, first ) );
	}
}


/*	------------------------------------------------------------------	*/
/*				o s p r o c c i 					*/
/*	------------------------------------------------------------------	*/
private	int	osprocci(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	osprocci_load();
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
				OsProcci.verbose=1;
				continue;
			case	'd'	:
				OsProcci.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( strcmp( aptr, "verbose" ) ))
					OsProcci.verbose = 1;
				else if (!( strcmp( aptr, "debug" ) ))
					OsProcci.debug = 1;
				else if (!( strcmp( aptr, "config" ) ))
				{
					OsProcci.config = allocate_string( argv[++argi] );
					osprocci_load();
				}
				else if (!( strcmp( aptr, "tls" ) ))
					OsProcci.tls = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "domain" ) ))
					OsProcci.domain = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "publisher" ) ))
					OsProcci.publisher = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "identity" ) ))
					OsProcci.identity = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "user" ) ))
					OsProcci.user = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "password" ) ))
					OsProcci.password = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "resthost" ) ))
					OsProcci.resthost = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "restport" ) ))
					OsProcci.restport = atoi( argv[++argi] );
				else if (!( strcmp( aptr, "chathost" ) ))
					OsProcci.chathost = allocate_string( argv[++argi] );
				else if (!( strcmp( aptr, "chatport" ) ))
					OsProcci.chatport = atoi( argv[++argi] );
				else if (!( strcmp( aptr, "threads" ) ))
					OsProcci.threads = _REST_THREAD_WORKER;
				else	break;
				continue;
			}
			status = 30;
			break;
		}
		else if (!( status = osprocci_operation(aptr) ))
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
	else	return( osprocci( argc, argv ) );
}


	/* ----------- */
#endif	/* _osprocci_c */
	/* ----------- */

