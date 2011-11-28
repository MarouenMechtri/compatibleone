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
#ifndef	_test_resolver_c
#define	_test_resolver_c

#include "occiresolver.h"

private	int	verbose=0;
private	int	debug=0;
private	int	price=0;
private	char *	tls=(char *) 0;
private	char *	publisher=_CORDS_DEFAULT_PUBLISHER;
private	char *	agent="CO-TEST-RESOLVER";

public	int	check_debug()		{	return(debug);		}
public	int	check_verbose()		{	return(verbose);	}
public	char *	default_publisher()	{	return(publisher);	}
public	char *	default_tls()		{	return(tls);		}

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

/*	------------------------------------------------------------	*/
/*		 r e s o l v e r _ s h o w _ r e s p o n s e 		*/
/*	------------------------------------------------------------	*/
private	void	resolver_show_response( struct occi_response * rptr, char * agent )
{
	struct	occi_element * 	eptr;
	char *			urlprice;
	if ( rptr->response )
	{
		printf("   OCCI Client : %s %u %s \n",
			rptr->response->version,
			rptr->response->status,
			rptr->response->message );
	}
	for (	eptr = rptr->first;
		eptr != (struct occi_element*) 0;
		eptr = eptr->next )
	{
		if (!( eptr->name ))
			continue;
		else if (!( eptr->value ))
			continue;
		else if (!( price ))
			printf("   %s = %s \n",eptr->name,eptr->value );
		else if (!( urlprice = occi_resolve_category_price( eptr->name, eptr->value, agent, tls ) ))
			printf("   %s = %s \n",eptr->name,eptr->value );
		else
		{
			printf("   %s = %s \n\t[ %s ] \n",eptr->name,eptr->value, urlprice );
			urlprice = liberate( urlprice );
		}
	}
	return;
}



private	int	test_resolver_operation( char * host, char * agent, char * object )
{
	struct	occi_client * cptr;
	struct	occi_request * rptr;
	struct	occi_response *	aptr;

	if (!( host )) 
		return( failure(30,"please specify","--publisher name" ));

	else if (!( agent )) 
		return( failure(30,"please specify","--agent name" ));

	if ( check_verbose() )
		printf("\n   OCCI Resolver\n");

	if ( object )
	{
		initialise_occi_resolver( host, (char *) 0, (char *) 0, (char *) 0 );
		if (( aptr = occi_resolver( object, agent )) != (struct occi_response *) 0)
		{
			resolver_show_response( aptr, agent );
			aptr=occi_remove_response( aptr );
		}
	}
	return( 0 );

}

private	int	test_resolver_command( int argc, char * argv[] )
{
	int	argi=1;
	char *	aptr;
	int	status;
	while (argi < argc)
	{
		if (!( aptr = argv[argi++] ))
			break;
		else if ( *aptr !=  '-')
		{
			if (!( status = test_resolver_operation( publisher, agent, aptr ) ))
				continue;
			else	return( status );
		}
		else 
		{
			aptr++;
			if ( *aptr ==  '-')
			{
				aptr++;
				if (!( strcmp( aptr, "verbose" ) ))
				{	verbose=1; continue;	}
				if (!( strcmp( aptr, "price" ) ))
				{	price=1; continue;	}
				else if (!( strcmp( aptr, "debug" ) ))
				{	debug=1; continue;	}
				else if (!( strcmp( aptr, "publisher" ) ))
				{
					publisher = argv[argi++];
					continue;
				}
				else if (!( strcmp( aptr, "tls" ) ))
				{
					tls = argv[argi++];
					continue;
				}
				else if (!( strcmp( aptr, "agent" ) ))
				{
					agent = argv[argi++];
					continue;
				}
				else
				{
					printf("incorrect option : %s\n",aptr);
					break;
				}
			
			}
			else
			{
				switch( *(aptr+1) )
				{
				case	'd'	:
					debug = 1;
					continue;
				case	'v'	:
					verbose = 1;
					continue;
				case	't'	:
					tls = (aptr+2);
					break;
				case	'p'	:
					publisher = (aptr+2);
					continue;
				case	'a'	:
					agent = (aptr+2);
					continue;
				default		:
					printf("incorrect option : %s \n",aptr);
					break;
				}
			}
		}
	}
	return( 0 );
}

private	int	test_resolver_banner()
{
	printf("\n   CO-TEST-RESOLVER : CompatibleOne OCCI Test Resolver : Version 1.0a.0.01");
	printf("\n   Beta Version : 16/10/2011 ");
	printf("\n   Copyright (c) 2011 Iain James Marshall, Prologue \n");
	printf("\n   --verbose                         activate status  messages       ");
	printf("\n   --debug                           activate debug   messages       ");
	printf("\n   --tls       <filename>            specify TLS configuration       ");
	printf("\n   --publisher <hostname>            set publisher URL               ");
	printf("\n   --agent     <agentname>           set client agent identification \n\n");
	return(0);
}

public	int	main( int argc, char * argv[] )
{
	if ( argc == 1 )
		return( test_resolver_banner() );
	else	return( test_resolver_command(argc, argv) );
}

#endif	/* _test_resolver_c */
	/* ------------ */


