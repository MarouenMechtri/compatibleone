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
#ifndef _az_client_h
#define _az_client_h

#include "standard.h"
#include "rest.h"
#include "url.h"
#include "urlpublic.h"
#include "restclient.h"
#include "json.h"
#include "document.h"
#include "azconfig.h"

#define	_TEXT_NONE 	0
#define	_TEXT_XML	1
#define	_TEXT_JSON	2

struct	az_response
{
	int	nature;
	char			*	content;
	struct	xml_element 	*	xmlroot;
	struct	data_element	*	jsonroot;
	struct	rest_response	*	response;
};

#define	_AZ_NS_COMPUTE	"http://schemas.microsoft.com/windowsazure"

public	char * az_create_server_request(
	char * identity, char * flavor, char * image, char * personality, char * resource );
public	char * az_create_image_request(char * identity, char * server );

public	struct	az_response * 
	az_client_get_request(
		char * target, char * tls, char * agent, struct rest_header * hptr );

public	struct	az_response * 
	az_client_delete_request(
		char * target, char * tls, char * agent, struct rest_header * hptr );

public	struct	az_response * 
	az_client_head_request(
		char * target, char * tls, char * agent, struct rest_header * hptr );

public	struct	az_response * 
	az_client_post_request(
		char * target, char * tls, char * agent, char * filename, struct rest_header * hptr );

public	struct	az_response * 
	az_client_put_request(
		char * target, char * tls, char * agent, char * filename, struct rest_header * hptr );

public	struct	az_response *	az_create_hosted_service( char * filename );
public	struct	az_response *	az_retrieve_hosted_service( char * filename );
public	struct	az_response *	az_update_hosted_service( char * filename );
public	struct	az_response *	az_delete_hosted_service( char * filename );
public	struct	az_response *	az_list_hosted_services();
public	struct	az_response *	az_create_affinity_group( char * filename );
public	struct	az_response *	az_retrieve_affinity_group( char * filename );
public	struct	az_response *	az_update_affinity_group( char * filename );
public	struct	az_response *	az_delete_affinity_group( char * filename );
public	struct	az_response *	az_list_affinity_groups();
public	struct	az_response *	az_create_certificate( char * filename );
public	struct	az_response *	az_retrieve_certificate( char * filename );
public	struct	az_response *	az_delete_certificate( char * filename );
public	struct	az_response *	az_list_certificates(char * server);
public	struct	az_response *	az_list_locations();
public	struct	az_response *	az_list_servers	();
public	struct	az_response *	az_list_flavors();
public	struct	az_response *	az_list_images  ();

public	struct	az_response *	az_create_server( char * filename );
public	struct	az_response *	az_create_image( char * filename );

public	struct	az_response *	az_get_server	( char * id );
public	struct	az_response *	az_get_flavor  ( char * id );
public	struct	az_response *	az_get_image    ( char * id );

public	struct	az_response *	az_update_server( char * id, char * filename );

public	struct	az_response *	az_delete_server( char * id );
public	struct	az_response *	az_delete_image ( char * id );

public	struct az_response * liberate_az_response( struct az_response * rptr );	

public	struct	az_response *	az_list_WATM_profiles();
public	struct	az_response *	az_list_WATM_definitions(char * profile );

#endif	/* _az_client_h */
	/* ------------ */



