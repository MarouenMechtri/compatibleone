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

/* STRUKT WARNING : this file has been generated and should not be modified by hand */
#ifndef _occiapplication_c_
#define _occiapplication_c_

#include "application.h"

/*	--------------------------------------------	*/
/*	o c c i _ c o r d s _ a p p l i c a t i o n 	*/
/*	--------------------------------------------	*/

/*	--------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   m a n a g e m e n t   s t r u c t u r e 	*/
/*	--------------------------------------------------------------------	*/
struct cords_application * allocate_cords_application();
struct cords_application * liberate_cords_application(struct cords_application * optr);
private pthread_mutex_t list_cords_application_control=PTHREAD_MUTEX_INITIALIZER;
private struct occi_kind_node * cords_application_first = (struct occi_kind_node *) 0;
private struct occi_kind_node * cords_application_last  = (struct occi_kind_node *) 0;
public struct  occi_kind_node * occi_first_cords_application_node() { return( cords_application_first ); }
public struct  occi_kind_node * occi_last_cords_application_node() { return( cords_application_last ); }

/*	----------------------------------------------	*/
/*	o c c i   c a t e g o r y   d r o p   n o d e 	*/
/*	----------------------------------------------	*/
private struct occi_kind_node * ll_drop_cords_application_node(struct occi_kind_node * nptr) {
	if ( nptr ) {
	if (!( nptr->previous ))
		cords_application_first = nptr->next;
	else	nptr->previous->next = nptr->next;
	if (!( nptr->next ))
		cords_application_last = nptr->previous;
	else	nptr->next->previous = nptr->previous;
		liberate_occi_kind_node( nptr );
		}
	return((struct occi_kind_node *)0);
}
private struct occi_kind_node * drop_cords_application_node(struct occi_kind_node * nptr) {
	pthread_mutex_lock( &list_cords_application_control );
	nptr = ll_drop_cords_application_node( nptr );
	pthread_mutex_unlock( &list_cords_application_control );
	return(nptr);
}

/*	--------------------------------------------------	*/
/*	o c c i   c a t e g o r y   l o c a t e   n o d e 	*/
/*	--------------------------------------------------	*/
private struct occi_kind_node * ll_locate_cords_application_node(char * id) {
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	for ( nptr = cords_application_first;
		nptr != (struct occi_kind_node *) 0;
		nptr = nptr->next ) {
		if (!( pptr = nptr->contents )) continue;
		else if (!( pptr->id )) continue;
		else if (!( strcmp(pptr->id,id) )) break;
		}
	return( nptr );
}
private struct occi_kind_node * locate_cords_application_node(char * id) {
	struct occi_kind_node * nptr;
	pthread_mutex_lock( &list_cords_application_control );
	nptr = ll_locate_cords_application_node(id);
	pthread_mutex_unlock( &list_cords_application_control );
	return( nptr );
}

/*	--------------------------------------------	*/
/*	o c c i   c a t e g o r y   a d d   n o d e 	*/
/*	--------------------------------------------	*/
private struct occi_kind_node * ll_add_cords_application_node(int mode) {
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	if (!( nptr = allocate_occi_kind_node() ))
		return( nptr );
	else	{
		if (!( nptr->contents = allocate_cords_application()))
			return( liberate_occi_kind_node(nptr) );
		if (!( pptr = nptr->contents ))
			return( liberate_occi_kind_node(nptr) );
		else if (( mode != 0 ) && (!( pptr->id = occi_allocate_uuid())))
			return( liberate_occi_kind_node(nptr) );
		else	{
			if (!( nptr->previous = cords_application_last ))
				cords_application_first = nptr;
			else	nptr->previous->next = nptr;
			cords_application_last = nptr;
			return( nptr );
			}
		}
}
private struct occi_kind_node * add_cords_application_node(int mode) {
	struct occi_kind_node * nptr;
	pthread_mutex_lock( &list_cords_application_control );
	nptr = ll_add_cords_application_node( mode );
	pthread_mutex_unlock( &list_cords_application_control );
	return(nptr);
}

/*	------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   a u t o   l o a d 	*/
/*	------------------------------------------------------------------------------------------	*/
private char*autosave_cords_application_name="cords_application.xml";
private void autoload_cords_application_nodes() {
	char * fn=autosave_cords_application_name;	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	struct xml_element * document;
	struct xml_element * eptr;
	struct xml_element * vptr;
	struct xml_atribut  * aptr;
	if (!( document = document_parse_file(fn)))
		return;
	if ((eptr = document_element(document,"cords_applications")) != (struct xml_element *) 0) {
		for (vptr=eptr->first; vptr != (struct xml_element *) 0; vptr=vptr->next) {
			if (!( vptr->name )) continue;
			else if ( strcmp( vptr->name, "cords_application" ) ) continue;
			else if (!( nptr = add_cords_application_node(0))) break;
			else if (!( pptr = nptr->contents )) break;
			if ((aptr = document_atribut( vptr, "id" )) != (struct xml_atribut *) 0)
				pptr->id = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "state" )) != (struct xml_atribut *) 0)
				pptr->state = document_atribut_value(aptr);
			if ((aptr = document_atribut( vptr, "image" )) != (struct xml_atribut *) 0)
				pptr->image = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "provider" )) != (struct xml_atribut *) 0)
				pptr->provider = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "price" )) != (struct xml_atribut *) 0)
				pptr->price = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "url" )) != (struct xml_atribut *) 0)
				pptr->url = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "account" )) != (struct xml_atribut *) 0)
				pptr->account = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "provision" )) != (struct xml_atribut *) 0)
				pptr->provision = document_atribut_string(aptr);
			if ((aptr = document_atribut( vptr, "created" )) != (struct xml_atribut *) 0)
				pptr->created = document_atribut_value(aptr);
			if ((aptr = document_atribut( vptr, "started" )) != (struct xml_atribut *) 0)
				pptr->started = document_atribut_value(aptr);
			if ((aptr = document_atribut( vptr, "completed" )) != (struct xml_atribut *) 0)
				pptr->completed = document_atribut_value(aptr);
			if ((aptr = document_atribut( vptr, "duration" )) != (struct xml_atribut *) 0)
				pptr->duration = document_atribut_value(aptr);
			}
		}
	document = document_drop( document );
	return;
}

/*	------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   a u t o   s a v e 	*/
/*	------------------------------------------------------------------------------------------	*/
public  void set_autosave_cords_application_name(char * fn) {
	autosave_cords_application_name = fn;	return;
}
public  void autosave_cords_application_nodes() {
	char * fn=autosave_cords_application_name;	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	FILE * h;
	pthread_mutex_lock( &list_cords_application_control );
	if (( h = fopen(fn,"w")) != (FILE *) 0) {
	fprintf(h,"<cords_applications>\n");
	for ( nptr = cords_application_first;
		nptr != (struct occi_kind_node *) 0;
		nptr = nptr->next ) {
		if (!( pptr = nptr->contents )) continue;
		fprintf(h,"<cords_application\n");
		fprintf(h," id=%c",0x0022);
		fprintf(h,"%s",(pptr->id?pptr->id:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," state=%c",0x0022);
		fprintf(h,"%u",pptr->state);
		fprintf(h,"%c",0x0022);
		fprintf(h," image=%c",0x0022);
		fprintf(h,"%s",(pptr->image?pptr->image:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," provider=%c",0x0022);
		fprintf(h,"%s",(pptr->provider?pptr->provider:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," price=%c",0x0022);
		fprintf(h,"%s",(pptr->price?pptr->price:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," url=%c",0x0022);
		fprintf(h,"%s",(pptr->url?pptr->url:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," account=%c",0x0022);
		fprintf(h,"%s",(pptr->account?pptr->account:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," provision=%c",0x0022);
		fprintf(h,"%s",(pptr->provision?pptr->provision:""));
		fprintf(h,"%c",0x0022);
		fprintf(h," created=%c",0x0022);
		fprintf(h,"%u",pptr->created);
		fprintf(h,"%c",0x0022);
		fprintf(h," started=%c",0x0022);
		fprintf(h,"%u",pptr->started);
		fprintf(h,"%c",0x0022);
		fprintf(h," completed=%c",0x0022);
		fprintf(h,"%u",pptr->completed);
		fprintf(h,"%c",0x0022);
		fprintf(h," duration=%c",0x0022);
		fprintf(h,"%u",pptr->duration);
		fprintf(h,"%c",0x0022);
		fprintf(h," />\n");
		}
	fprintf(h,"</cords_applications>\n");
	fclose(h);
	}
	pthread_mutex_unlock( &list_cords_application_control );
	return;
}

/*	------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   s e t   f i e l d 	*/
/*	------------------------------------------------------------------------------------------	*/
private void set_cords_application_field(
	struct occi_category * cptr,void * optr, char * nptr, char * vptr)
{
	struct cords_application * pptr;
	char prefix[1024];
	if (!( pptr = optr )) return;
	sprintf(prefix,"%s.%s.",cptr->domain,cptr->id);
	if (!( strncmp( nptr, prefix, strlen(prefix) ) )) {
		nptr += strlen(prefix);
		if (!( strcmp( nptr, "state" ) ))
			pptr->state = atoi(vptr);
		if (!( strcmp( nptr, "image" ) ))
			pptr->image = allocate_string(vptr);
		if (!( strcmp( nptr, "provider" ) ))
			pptr->provider = allocate_string(vptr);
		if (!( strcmp( nptr, "price" ) ))
			pptr->price = allocate_string(vptr);
		if (!( strcmp( nptr, "url" ) ))
			pptr->url = allocate_string(vptr);
		if (!( strcmp( nptr, "account" ) ))
			pptr->account = allocate_string(vptr);
		if (!( strcmp( nptr, "provision" ) ))
			pptr->provision = allocate_string(vptr);
		if (!( strcmp( nptr, "created" ) ))
			pptr->created = atoi(vptr);
		if (!( strcmp( nptr, "started" ) ))
			pptr->started = atoi(vptr);
		if (!( strcmp( nptr, "completed" ) ))
			pptr->completed = atoi(vptr);
		if (!( strcmp( nptr, "duration" ) ))
			pptr->duration = atoi(vptr);
		}
	return;
}

/*	--------------------------------------------------	*/
/*	o c c i   c a t e g o r y   f i l t e r   i n f o 	*/
/*	--------------------------------------------------	*/
private struct cords_application * filter_cords_application_info(
	struct occi_category * optr,
	struct rest_request  * rptr,
	struct rest_response * aptr) {
	struct cords_application * pptr;
		if (!( pptr = allocate_cords_application()))
		return( pptr );
	else if (!( occi_process_atributs(optr, rptr, aptr, pptr, set_cords_application_field) ))
		return( liberate_cords_application(pptr));
	else	return( pptr );
}

/*	--------------------------------------------------	*/
/*	o c c i   c a t e g o r y   f i l t e r   p a s s 	*/
/*	--------------------------------------------------	*/
private int pass_cords_application_filter(
	struct cords_application * pptr,struct cords_application * fptr) {
	if (( fptr->id )
	&&  (strlen( fptr->id ) != 0)) {
		if (!( pptr->id ))
			return(0);
		else if ( strcmp(pptr->id,fptr->id) != 0)
			return(0);
		}
	if (( fptr->state ) && ( pptr->state != fptr->state )) return(0);
	if (( fptr->image )
	&&  (strlen( fptr->image ) != 0)) {
		if (!( pptr->image ))
			return(0);
		else if ( strcmp(pptr->image,fptr->image) != 0)
			return(0);
		}
	if (( fptr->provider )
	&&  (strlen( fptr->provider ) != 0)) {
		if (!( pptr->provider ))
			return(0);
		else if ( strcmp(pptr->provider,fptr->provider) != 0)
			return(0);
		}
	if (( fptr->price )
	&&  (strlen( fptr->price ) != 0)) {
		if (!( pptr->price ))
			return(0);
		else if ( strcmp(pptr->price,fptr->price) != 0)
			return(0);
		}
	if (( fptr->url )
	&&  (strlen( fptr->url ) != 0)) {
		if (!( pptr->url ))
			return(0);
		else if ( strcmp(pptr->url,fptr->url) != 0)
			return(0);
		}
	if (( fptr->account )
	&&  (strlen( fptr->account ) != 0)) {
		if (!( pptr->account ))
			return(0);
		else if ( strcmp(pptr->account,fptr->account) != 0)
			return(0);
		}
	if (( fptr->provision )
	&&  (strlen( fptr->provision ) != 0)) {
		if (!( pptr->provision ))
			return(0);
		else if ( strcmp(pptr->provision,fptr->provision) != 0)
			return(0);
		}
	if (( fptr->created ) && ( pptr->created != fptr->created )) return(0);
	if (( fptr->started ) && ( pptr->started != fptr->started )) return(0);
	if (( fptr->completed ) && ( pptr->completed != fptr->completed )) return(0);
	if (( fptr->duration ) && ( pptr->duration != fptr->duration )) return(0);
	return(1);
}

/*	----------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   r e s p o n s e 	*/
/*	----------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_occi_response(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr,
	struct cords_application * pptr)
{
	struct rest_header * hptr;
	sprintf(cptr->buffer,"occi.core.id=%s",pptr->id);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.state=%u",optr->domain,optr->id,pptr->state);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.image=%s",optr->domain,optr->id,pptr->image);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.provider=%s",optr->domain,optr->id,pptr->provider);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.price=%s",optr->domain,optr->id,pptr->price);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.url=%s",optr->domain,optr->id,pptr->url);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.account=%s",optr->domain,optr->id,pptr->account);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.provision=%s",optr->domain,optr->id,pptr->provision);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.created=%u",optr->domain,optr->id,pptr->created);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.started=%u",optr->domain,optr->id,pptr->started);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.completed=%u",optr->domain,optr->id,pptr->completed);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	sprintf(cptr->buffer,"%s.%s.duration=%u",optr->domain,optr->id,pptr->duration);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Attribute",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	if ( occi_render_links( aptr, pptr->id ) != 0)
		return( rest_html_response( aptr, 500, "Server Link Failure" ) );
	else	if (!( occi_success( aptr ) ))
		return( rest_response_status( aptr, 500, "Server Failure" ) );
	else	return( rest_response_status( aptr, 200, "OK" ) );
}

/*	----------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   g e t   i t e m 	*/
/*	----------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_get_item(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr, char * id)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	iptr = optr->callback;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 404, "Not Found") );
	if (( iptr ) && (iptr->retrieve)) (*iptr->retrieve)(optr,nptr);
	autosave_cords_application_nodes();
	return( cords_application_occi_response(optr,cptr,rptr,aptr,pptr));
}

/*	------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p o s t   l i n k 	*/
/*	------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_post_link(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr,char * id)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	char * reqhost;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 404, "Not Found") );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	--------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p o s t   m i x i n 	*/
/*	--------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_post_mixin(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr,char * id)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	char * reqhost;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 404, "Not Found") );
	else	return( rest_html_response( aptr, 400, "Bad Request"));
}

/*	----------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p o s t   a c t i o n 	*/
/*	----------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_post_action(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr,char * id)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_action * fptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	char * reqhost;
	char * mptr;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 404, "Not Found") );
	mptr = (rptr->parameters+strlen("action="));
	for ( fptr=optr->firstact;
		fptr != (struct occi_action *) 0;
		fptr = fptr->next )
		if (!( strncmp( mptr, fptr->name, strlen( fptr->name )) ))
			return( occi_invoke_action(fptr,optr,cptr,rptr,aptr,pptr) );
	return( rest_html_response( aptr, 400, "Incorrect Action Request"));
}

/*	------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p o s t   i t e m 	*/
/*	------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_post_item(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	char * reqhost;
	iptr = optr->callback;
	if (!( reqhost = rest_request_host( rptr ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	if (!( nptr = add_cords_application_node(1)))
		return( rest_html_response( aptr, 500, "Server Failure") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 500, "Server Failure") );
	if (!( occi_process_atributs( optr, rptr,aptr, pptr, set_cords_application_field ) ))
		return( rest_html_response( aptr, 500, "Server Failure") );
	if (( iptr ) && (iptr->create)) (*iptr->create)(optr,nptr);
	autosave_cords_application_nodes();
	sprintf(cptr->buffer,"%s%s%s",reqhost,optr->location,pptr->id);
	if (!( hptr = rest_response_header( aptr, "X-OCCI-Location",cptr->buffer) ))
		return( rest_html_response( aptr, 500, "Server Failure" ) );
	else if (!( occi_success( aptr ) ))
		return( rest_response_status( aptr, 500, "Server Failure" ) );
	else	return( rest_response_status( aptr, 200, "OK" ) );
}

/*	----------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p u t   i t e m 	*/
/*	----------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_put_item(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr,char * id)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	iptr = optr->callback;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 404, "Not Found") );
	if (!( occi_process_atributs(optr,rptr,aptr, pptr, set_cords_application_field ) ))
		return( rest_html_response( aptr, 500, "Server Failure") );
	if (( iptr ) && (iptr->update)) (*iptr->update)(optr,nptr);
	autosave_cords_application_nodes();
	return( cords_application_occi_response(optr,cptr,rptr,aptr,pptr));
}

/*	------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   h e a d   i t e m 	*/
/*	------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_head_item(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr,char * id)
{
	struct rest_header * hptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	else if (!( pptr = nptr->contents ))
		return( rest_html_response( aptr, 404, "Not Found") );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	----------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   d e l e t e   i t e m 	*/
/*	----------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_delete_item(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr, char * id)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct cords_application * pptr;
	iptr = optr->callback;
	if (!( nptr = locate_cords_application_node(id)))
		return( rest_html_response( aptr, 404, "Not Found") );
	if (( iptr ) && (iptr->delete)) (*iptr->delete)(optr,nptr);
	drop_cords_application_node( nptr );
	autosave_cords_application_nodes();
	if (!( occi_success( aptr ) ))
		return( rest_response_status( aptr, 500, "Server Failure" ) );
	else	return( rest_response_status( aptr, 200, "OK" ) );
}

/*	----------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   g e t   l i s t 	*/
/*	----------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_get_list(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr)
{
	struct rest_header * hptr;
	struct occi_kind_node * sptr;
	struct cords_application * pptr;
	struct cords_application * fptr;
	char * reqhost;
	if (!( reqhost = rest_request_host( rptr ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	else if (!( fptr = filter_cords_application_info( optr, rptr, aptr ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	for ( sptr = cords_application_first;
		sptr != (struct occi_kind_node *) 0;
		sptr = sptr->next ) {
		if (!( pptr = sptr->contents ))
			continue;
		if (!( pass_cords_application_filter( pptr, fptr ) ))
			continue;
		sprintf(cptr->buffer,"%s%s%s",reqhost,optr->location,pptr->id);
		if (!( hptr = rest_response_header( aptr, "X-OCCI-Location",cptr->buffer) ))
			return( rest_html_response( aptr, 500, "Server Failure" ) );
		}
	if (!( occi_success( aptr ) ))
		return( rest_response_status( aptr, 500, "Server Failure" ) );
	else	return( rest_response_status( aptr, 200, "OK" ) );
}

/*	--------------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   d e l e t e   a l l 	*/
/*	--------------------------------------------------------------------------------------------	*/
private struct rest_response * cords_application_delete_all(
	struct occi_category * optr, struct rest_client * cptr,
	struct rest_request * rptr, struct rest_response * aptr)
{
	struct rest_header * hptr;
	struct occi_interface * iptr;
	struct occi_kind_node * nptr;
	struct occi_kind_node * sptr;
	struct cords_application * pptr;
	struct cords_application * fptr;
	iptr = optr->callback;
	if (!( fptr = filter_cords_application_info( optr, rptr, aptr ) ))
		return( rest_html_response( aptr, 400, "Bad Request" ) );
	nptr=cords_application_first;
	while (nptr != (struct occi_kind_node *) 0) {
		if ((!( pptr = nptr->contents ))
		||  (!( pass_cords_application_filter( pptr, fptr ) ))) {
			nptr = nptr->next;
			continue;
			}
		else	{
			if (( iptr ) && (iptr->delete)) { (*iptr->delete)(optr,nptr); }
			sptr = nptr->next;
			drop_cords_application_node( nptr );
			nptr = sptr;
			}
		}
	autosave_cords_application_nodes();
	if (!( occi_success( aptr ) ))
		return( rest_response_status( aptr, 500, "Server Failure" ) );
	else	return( rest_response_status( aptr, 200, "OK" ) );
}

/*	------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   g e t 	*/
/*	------------------------------------------------------------------------------	*/
private struct rest_response * occi_cords_application_get(void * vptr, struct rest_client * cptr, struct rest_request * rptr)
{
	struct rest_response * aptr;
	struct rest_header   * hptr;
	struct occi_category * optr;
	char * ctptr;
	char * mptr;
	if (!( hptr = rest_resolve_header( rptr->first, "Content-Type" ) ))
		ctptr = "text/occi";
	else	ctptr = hptr->value;
	if (!( optr = vptr )) 
		return( rest_bad_request(vptr,cptr,rptr) );
	if(!(aptr = rest_allocate_response( cptr )))
		return( aptr );
	else if (!(strcmp( rptr->object, optr->location ) ))
		return( cords_application_get_list( optr, cptr, rptr, aptr ) );
	else if (!(strncmp( rptr->object, optr->location, strlen(optr->location) ) ))
		return( cords_application_get_item( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	--------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   h e a d 	*/
/*	--------------------------------------------------------------------------------	*/
private struct rest_response * occi_cords_application_head(void * vptr, struct rest_client * cptr, struct rest_request * rptr)
{
	struct rest_response * aptr;
	struct rest_header   * hptr;
	struct occi_category * optr;
	char * ctptr;
	char * mptr;
	if (!( hptr = rest_resolve_header( rptr->first, "Content-Type" ) ))
		ctptr = "text/occi";
	else	ctptr = hptr->value;
	if (!( optr = vptr )) 
		return( rest_bad_request(vptr,cptr,rptr) );
	if(!(aptr = rest_allocate_response( cptr )))
		return( aptr );
	else if (!(strncmp( rptr->object, optr->location, strlen(optr->location) ) ))
		return( cords_application_head_item( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	--------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p o s t 	*/
/*	--------------------------------------------------------------------------------	*/
private struct rest_response * occi_cords_application_post(void * vptr, struct rest_client * cptr, struct rest_request * rptr)
{
	struct rest_response * aptr;
	struct rest_header   * hptr;
	struct occi_category * optr;
	char * ctptr;
	char * mptr;
	if (!( hptr = rest_resolve_header( rptr->first, "Content-Type" ) ))
		ctptr = "text/occi";
	else	ctptr = hptr->value;
	if (!( optr = vptr )) 
		return( rest_bad_request(vptr,cptr,rptr) );
	if(!(aptr = rest_allocate_response( cptr )))
		return( aptr );
	else if (!( strcmp( rptr->object, optr->location ) ))
		return( cords_application_post_item( optr, cptr, rptr, aptr ) );
	else if ( strncmp( rptr->object, optr->location,strlen(optr->location)) != 0)
		return( rest_html_response( aptr, 400, "Bad Request") );
	else if (!( rptr->parameters ))
		return( rest_html_response( aptr, 400, "Bad Request") );
	else if (!( strncmp( rptr->parameters, "action=", strlen("action=")) ))
		return( cords_application_post_action( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else if (!( strncmp( rptr->parameters, "mixin=", strlen("mixin=")) ))
		return( cords_application_post_mixin( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else if (!( strncmp( rptr->parameters, "link=", strlen("link=")) ))
		return( cords_application_post_link( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   p u t 	*/
/*	------------------------------------------------------------------------------	*/
private struct rest_response * occi_cords_application_put(void * vptr, struct rest_client * cptr, struct rest_request * rptr)
{
	struct rest_response * aptr;
	struct rest_header   * hptr;
	struct occi_category * optr;
	char * ctptr;
	char * mptr;
	if (!( hptr = rest_resolve_header( rptr->first, "Content-Type" ) ))
		ctptr = "text/occi";
	else	ctptr = hptr->value;
	if (!( optr = vptr )) 
		return( rest_bad_request(vptr,cptr,rptr) );
	if(!(aptr = rest_allocate_response( cptr )))
		return( aptr );
	else if (!(strncmp( rptr->object, optr->location, strlen(optr->location) ) ))
		return( cords_application_put_item( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	------------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   m e t h o d   d e l e t e 	*/
/*	------------------------------------------------------------------------------------	*/
private struct rest_response * occi_cords_application_delete(void * vptr, struct rest_client * cptr, struct rest_request * rptr)
{
	struct rest_response * aptr;
	struct rest_header   * hptr;
	struct occi_category * optr;
	char * ctptr;
	char * mptr;
	if (!( hptr = rest_resolve_header( rptr->first, "Content-Type" ) ))
		ctptr = "text/occi";
	else	ctptr = hptr->value;
	if (!( optr = vptr )) 
		return( rest_bad_request(vptr,cptr,rptr) );
	if(!(aptr = rest_allocate_response( cptr )))
		return( aptr );
	else if (!(strcmp( rptr->object, optr->location ) ))
		return( cords_application_delete_all( optr, cptr, rptr, aptr ) );
	else if (!(strncmp( rptr->object, optr->location, strlen(optr->location) ) ))
		return( cords_application_delete_item( optr, cptr, rptr, aptr,rptr->object+strlen(optr->location) ) );
	else	return( rest_html_response( aptr, 400, "Bad Request") );
}

/*	--------------------------------------------------------------------------------	*/
/*	o c c i   c a t e g o r y   r e s t   i n t e r f a c e   r e d i r e c t i o n 	*/
/*	--------------------------------------------------------------------------------	*/
private void	redirect_occi_cords_application_mt( struct rest_interface * iptr )
{
	iptr->get = occi_cords_application_get;
	iptr->post = occi_cords_application_post;
	iptr->put = occi_cords_application_put;
	iptr->delete = occi_cords_application_delete;
	iptr->head = occi_cords_application_head;
	return;
}

/*	------------------------------------	*/
/*	c r u d   d e l e t e   a c t i o n 	*/
/*	------------------------------------	*/
private struct rest_response * delete_action_cords_application(struct occi_category * optr, 
struct rest_client * cptr,  
struct rest_request * rptr,  
struct rest_response * aptr,  
void * vptr )
{
	aptr = liberate_rest_response( aptr );
	return( occi_cords_application_delete(optr,cptr,rptr));
}

/*	------------------------------------------	*/
/*	o c c i   c a t e g o r y   b u i l d e r 	*/
/*	------------------------------------------	*/
/* occi category rest instance builder for : occi_cords_application */
public struct occi_category * occi_cords_application_builder(char * a,char * b) {
	char * c="http://scheme.compatibleone.fr/scheme/compatible#";
	char * d="kind";
	char * e="http://scheme.ogf.org/occi/resource#";
	char * f="CompatibleOne OCCI resource cords_application";
	struct occi_category * optr;
	if (!( optr = occi_create_category(a,b,c,d,e,f) )) { return(optr); }
	else {
		redirect_occi_cords_application_mt(optr->interface);
		if (!( optr = occi_add_attribute(optr, "state",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "image",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "provider",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "price",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "url",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "account",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "provision",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "created",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "started",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "completed",0,0) ))
			return(optr);
		if (!( optr = occi_add_attribute(optr, "duration",0,0) ))
			return(optr);
		if (!( optr = occi_add_action( optr,"DELETE","",delete_action_cords_application)))
			return( optr );
		autoload_cords_application_nodes();
		return(optr);
	}

}

/*	------------------------------------------------------------	*/
/*	c o r d s _ a p p l i c a t i o n _ o c c i _ h e a d e r s 	*/
/*	------------------------------------------------------------	*/
public struct rest_header *  cords_application_occi_headers(struct cords_application * sptr)
{
	struct rest_header * first=(struct rest_header *) 0;
	struct rest_header * last=(struct rest_header *) 0;
	struct rest_header * hptr=(struct rest_header *) 0;
	char buffer[8192];
	if (!( sptr )) return(0);
	if (!( hptr = allocate_rest_header()))
		return(hptr);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("Category")))
		return(first);
	sprintf(buffer,"cords_application; scheme='http://scheme.compatibleone.fr/scheme/compatible#'; class='kind';\r\n");
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.state='%u'\r\n",sptr->state);
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.image='%s'\r\n",(sptr->image?sptr->image:""));
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.provider='%s'\r\n",(sptr->provider?sptr->provider:""));
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.price='%s'\r\n",(sptr->price?sptr->price:""));
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.url='%s'\r\n",(sptr->url?sptr->url:""));
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.account='%s'\r\n",(sptr->account?sptr->account:""));
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.provision='%s'\r\n",(sptr->provision?sptr->provision:""));
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.created='%u'\r\n",sptr->created);
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.started='%u'\r\n",sptr->started);
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.completed='%u'\r\n",sptr->completed);
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	if (!( hptr = allocate_rest_header()))
		return(first);
		else	if (!( hptr->previous = last))
			first = hptr;
		else	hptr->previous->next = hptr;
		last = hptr;
	if (!( hptr->name = allocate_string("X-OCCI-Attribute")))
		return(first);
	sprintf(buffer,"occi.cords_application.duration='%u'\r\n",sptr->duration);
	if (!( hptr->value = allocate_string(buffer)))
		return(first);
	return(first);

}

#endif	/* _occiapplication_c_ */
