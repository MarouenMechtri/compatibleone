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

/* STRUKT WARNING : this file has been generated and should not be modified by hand */
#ifndef _paas_application_manifest_c_
#define _paas_application_manifest_c_

#include "element.h"

#include "paas_application_manifest.h"

/*	--------------------------------------------------------------------	*/
/*	l i b e r a t e _ p a a s _ a p p l i c a t i o n _ m a n i f e s t 	*/
/*	--------------------------------------------------------------------	*/
public struct paas_application_manifest * liberate_paas_application_manifest(struct paas_application_manifest * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->access )
			 sptr->access = liberate(sptr->access);
		if ( sptr->scope )
			 sptr->scope = liberate(sptr->scope);
		if ( sptr->paas_description )
			 sptr->paas_description = liberate(sptr->paas_description);
		if ( sptr->paas_application )
			 sptr->paas_application = liberate(sptr->paas_application);
		sptr = liberate( sptr );
	}
	return((struct paas_application_manifest *) 0);

}

/*	--------------------------------------------------------------	*/
/*	r e s e t _ p a a s _ a p p l i c a t i o n _ m a n i f e s t 	*/
/*	--------------------------------------------------------------	*/
public struct paas_application_manifest * reset_paas_application_manifest(struct paas_application_manifest * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->access = (char*) 0;
		sptr->scope = (char*) 0;
		sptr->paas_description = (char*) 0;
		sptr->paas_application = (char*) 0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	--------------------------------------------------------------------	*/
/*	a l l o c a t e _ p a a s _ a p p l i c a t i o n _ m a n i f e s t 	*/
/*	--------------------------------------------------------------------	*/
public struct paas_application_manifest * allocate_paas_application_manifest()
{
	struct paas_application_manifest * sptr;
	if (!( sptr = allocate( sizeof( struct paas_application_manifest ) ) ))
		return( sptr );
	else	return( reset_paas_application_manifest(sptr) );
}

/*	--------------------------------------------------------------	*/
/*	x m l i n _ p a a s _ a p p l i c a t i o n _ m a n i f e s t 	*/
/*	--------------------------------------------------------------	*/
public int xmlin_paas_application_manifest(struct paas_application_manifest * sptr,struct xml_element * eptr)
{
	struct xml_element * wptr;
	if (!( eptr )) return(0);
	if (!( sptr )) return(0);
	for ( wptr=eptr->first; wptr != (struct xml_element *) 0; wptr=wptr->next)
	{
		if (!( strcmp(wptr->name,"id") ))
		{
			if ( wptr->value ) { sptr->id = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"name") ))
		{
			if ( wptr->value ) { sptr->name = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"access") ))
		{
			if ( wptr->value ) { sptr->access = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"scope") ))
		{
			if ( wptr->value ) { sptr->scope = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"paas_description") ))
		{
			if ( wptr->value ) { sptr->paas_description = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"paas_application") ))
		{
			if ( wptr->value ) { sptr->paas_application = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	----------------------------------------------------------------------	*/
/*	r e s t _ o c c i _ p a a s _ a p p l i c a t i o n _ m a n i f e s t 	*/
/*	----------------------------------------------------------------------	*/
public int rest_occi_paas_application_manifest(FILE * fh,struct paas_application_manifest * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.access='%s'\r\n",prefix,nptr,(sptr->access?sptr->access:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.scope='%s'\r\n",prefix,nptr,(sptr->scope?sptr->scope:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.paas_description='%s'\r\n",prefix,nptr,(sptr->paas_description?sptr->paas_description:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.paas_application='%s'\r\n",prefix,nptr,(sptr->paas_application?sptr->paas_application:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _paas_application_manifest_cpaas_application_manifest_c_ */
