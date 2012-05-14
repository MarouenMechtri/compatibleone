#ifndef	_testdc_c
#define	_testdc_c

#include "standard.h"
#include "dcclient.h"

private	int	verbose=0;
private	int	debug=0;
private	char *	publisher=(char *) 0;
private	char *	tls=(char *) 0;

public	int	check_debug()	{	return( debug);		}
public	int	check_verbose()	{	return( verbose);	}
public	char *	default_tls()	{	return( tls );		}
public	int	failure(int status, char * message)
{
	if ( status )
		printf("**failure(%u,%s)**\n",status,message);
	return( status );
}

public	char *	default_publisher()	
{
	return( publisher );
}

private	int	dc_result( struct rest_response* rptr )
{
	rptr = liberate_rest_response( rptr );
	return( 0 );
}

private	int	dc_operation( char * host, char * user, char * password, char * command, char * subject, char * option )
{
	if (!( host ))
		return( 30 );
	else if (!( user ))
		return( 31 );
	else if (!( password ))
		return( 32 );
	else if (!( command ))
		return( 33 );
	else if (!( subject ))
		return( 34 );
	else if (!( strcmp( command, "list" ) ))
	{
		if (!( strcmp( subject, "features" ) ))
			return( dc_result( dc_list_features() ) );
		else if (!( strcmp( subject, "profiles" ) ))
			return( dc_result( dc_list_profiles() ) );
		else if (!( strcmp( subject, "images" ) ))
			return( dc_result( dc_list_images() ) );
		else if (!( strcmp( subject, "servers" ) ))
			return( dc_result( dc_list_instances() ) );
		else if (!( strcmp( subject, "keys" ) ))
			return( dc_result( dc_list_keys() ) );
		else if (!( strcmp( subject, "addresses" ) ))
			return( dc_result( dc_list_addresses() ) );
		else if (!( strcmp( subject, "firewalls" ) ))
			return( dc_result( dc_list_firewalls() ) );
		else if (!( strcmp( subject, "loadbalancers" ) ))
			return( dc_result( dc_list_loadbalancers() ) );
		else	return( failure( 35, subject ) );
	}

	else if (!( strcmp( command, "get" ) ))
	{
		if (!( option ))
			return( failure( 36, "option") );
		else if (!( strcmp( subject, "profile" ) ))
			return( dc_result( dc_get_profile(option) ) );
		else if (!( strcmp( subject, "image" ) ))
			return( dc_result( dc_get_image(option) ) );
		else if (!( strcmp( subject, "server" ) ))
			return( dc_result( dc_get_instance(option) ) );
		else if (!( strcmp( subject, "key" ) ))
			return( dc_result( dc_get_key(option) ) );
		else if (!( strcmp( subject, "addresse" ) ))
			return( dc_result( dc_get_address(option) ) );
		else if (!( strcmp( subject, "firewall" ) ))
			return( dc_result( dc_get_firewall(option) ) );
		else if (!( strcmp( subject, "loadbalancer" ) ))
			return( dc_result( dc_get_loadbalancer(option) ) );
		else	return( failure( 35, subject ) );
	}

	else if (!( strcmp( command, "create" ) ))
	{
		if (!( option ))
			return( failure( 36, "option") );
		else if (!( strcmp( subject, "image" ) ))
			return( dc_result( dc_create_image(option) ) );
		else if (!( strcmp( subject, "key" ) ))
			return( dc_result( dc_create_key(option) ) );
		else if (!( strcmp( subject, "server" ) ))
			return( dc_result( dc_create_instance(option) ) );
		else if (!( strcmp( subject, "addresse" ) ))
			return( dc_result( dc_create_address(option) ) );
		else if (!( strcmp( subject, "firewall" ) ))
			return( dc_result( dc_create_firewall(option) ) );
		else if (!( strcmp( subject, "loadbalancer" ) ))
			return( dc_result( dc_create_loadbalancer(option) ) );
		else	return( failure( 35, subject ) );
	}

	else if (!( strcmp( command, "delete" ) ))
	{
		if (!( option ))
			return( failure( 36, "option") );
		else if (!( strcmp( subject, "image" ) ))
			return( dc_result( dc_delete_image(option) ) );
		else if (!( strcmp( subject, "server" ) ))
			return( dc_result( dc_delete_instance(option) ) );
		else if (!( strcmp( subject, "key" ) ))
			return( dc_result( dc_delete_key(option) ) );
		else if (!( strcmp( subject, "addresse" ) ))
			return( dc_result( dc_delete_address(option) ) );
		else if (!( strcmp( subject, "firewall" ) ))
			return( dc_result( dc_delete_firewall(option) ) );
		else if (!( strcmp( subject, "loadbalancer" ) ))
			return( dc_result( dc_delete_loadbalancer(option) ) );
		else	return( failure( 35, subject ) );

	}
	else	return( failure( 37, command ) );

	return(0);
}

private int	dc_create_command( char * subject, int argi, int argc, char * argv[] )
{
	char *	filename;
	int	argn=0;
	char *	args[10];
	for ( argn=0; argn < 10; argn++ ) args[argn] = (char *) 0;
	argn=0;
	while ( argi < argc )
		args[argn++] = argv[argi++];

	if (!( strcmp( subject, "server" ) ))
	{
		if (!( filename = dc_create_instance_message( args[0], args[1], args[2], args[3], args[4] ) ))
			return( 46 );
		else 	return( dc_result( dc_create_instance( filename ) ) );
	}
	if (!( strcmp( subject, "rule" ) ))
	{
		if (!( filename = dc_create_rule_message(  args[1], args[2], args[3], args[4] ) ))
			return( 46 );
		else 	return( dc_result( dc_create_rule( args[0], filename ) ) );
	}
	if (!( strcmp( subject, "loadbalancer" ) ))
	{
		if (!( filename = dc_create_loadbalancer_message( args[0], args[1], args[2], args[3], args[4] ) ))
			return( 46 );
		else 	return( dc_result( dc_create_loadbalancer( filename ) ) );
	}
	else if (!( strcmp( subject, "key" ) ))
	{
		if (!( filename = dc_create_key_message( args[0] ) ))
			return( 46 );
		else 	return( dc_result( dc_create_key( filename ) ) );
	}
	else if (!( strcmp( subject, "image" ) ))
	{
		if (!( filename = dc_create_image_message( args[0], args[1], args[2] ) ))
			return( 46 );
		else 	return( dc_result( dc_create_image( filename ) ) );
	}
	else if (!( strcmp( subject, "firewall" ) ))
	{
		if (!( filename = dc_create_firewall_message( args[0], args[1] ) ))
			return( 46 );
		else 	return( dc_result( dc_create_firewall( filename ) ) );
	}
	else if (!( strcmp( subject, "address" ) ))
	{
		return( dc_result( dc_create_address() ) );
	}

}

private int	dc_test_main( int argc, char * argv[] )
{
	char *	host=(char *) 0;
	int	port=80;
	char *	user=(char *) 0;
	char * 	tenant=(char *) 0;
	char *	agent="deltacloud-client/1.0";
	char *	password=(char *) 0;
	char *	command=(char *) 0;
	char *	subject=(char *) 0;
	int	argi=1;
	char * aptr;
	while ( argi < argc )
	{
		if (!( aptr = argv[argi++] ))
			break;
		else if ( *aptr != '-' )
		{
			set_dc_api_configuration( host, port, user, password, tenant, agent,tls );
			if (!( command ))
				command = aptr;
			else if (!( subject ))
			{
				subject = aptr;
				if (!( strcmp( command, "list" ) ))
					return( dc_operation( host, user, password, command, subject, (char *) 0 ) );
				else if (!( strcmp( command, "create" ) ))
					return( dc_create_command( subject, argi, argc, argv ) );
			}
			else	return( dc_operation( host, user, password, command, subject, aptr) );
		}
		else if ( *(aptr+1) = '-' )
		{
			aptr+=2;
			if (!( strcmp(aptr,"host" )))
				host = argv[argi++];
			else if (!( strcmp(aptr,"user" )))
				user = argv[argi++];
			else if (!( strcmp(aptr,"password" )))
				password = argv[argi++];
			else if (!( strcmp(aptr,"tenant" )))
				tenant = argv[argi++];
			else if (!( strcmp(aptr,"tls" )))
				tls = argv[argi++];
			else if (!( strcmp(aptr,"port" )))
			{
				port = atoi(argv[argi]);
				argi++;
			}
			else if (!( strcmp( aptr, "verbose" ) ))
				verbose =1;
			else if (!( strcmp( aptr, "debug" ) ))
				debug =1;
			else
			{
				printf("\nincorrect option: %s\n",aptr);
				return(30);
			}
		}
		else
		{
			printf("\nincorrect option: %s\n",aptr);
			return(30);
		}
	}
	return( 0 );
}

private int dc_test_banner()
{
	printf("\n   CompatibleOne Delta Cloud Test Client : Version 1.0a.0.01 ");
	printf("\n   Beta Version 14/05/2012 ");
	printf("\n   Copyright (c) 2012 Iain James Marshall\n");
	printf("\n   Options:\n");
	printf("\n   --host     {hostname}       specify delta cloud host ");
	printf("\n   --user     {username}       specify delta cloud user ");
	printf("\n   --password {password}       specify user password    ");
	printf("\n   --tls      {filename}       specify traansport layer security ");
	printf("\n   --verbose                   activate information messages ");
	printf("\n   --debug                     activate debug messages \n");
	printf("\n   Syntax:\n");
	printf("\n   list   [ features | profiles | images | servers | keys | addresses | firewalls | loadbalancers ]");
	printf("\n   get               [ profile  | image  | server  | key  | addresse  | firewall  | loadbalancer  ] {id} ");
	printf("\n   delete                       [ image  | server  | key  | addresse  | firewall  | loadbalancer  ] {id} ");
	printf("\n   create server name image profile firewall realm ");
	printf("\n   create loadbalancer name realm protocol port1 port2 ");
	printf("\n   create image instance name description ");
	printf("\n   create firewall name description ");
	printf("\n   create rule firewall proto from to range ");
	printf("\n   create key name ");
	printf("\n   create address ");
	printf("\n\n");
	return( 0 );
}

public int	main( int argc, char * argv[] )
{
	if ( argc == 1 )
		return( dc_test_banner() );
	else	return( dc_test_main(argc, argv) );
}

#endif 	/* _testdc_c */
	/* -------- */

