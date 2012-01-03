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
#ifndef _ipaddress_c_
#define _ipaddress_c_

#include "element.h"

#include "ipaddress.h"

/*	------------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ i p a d d r e s s 	*/
/*	------------------------------------------------	*/
public struct cords_ipaddress * liberate_cords_ipaddress(struct cords_ipaddress * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->version )
			 sptr->version = liberate(sptr->version);
		if ( sptr->type )
			 sptr->type = liberate(sptr->type);
		if ( sptr->value )
			 sptr->value = liberate(sptr->value);
		if ( sptr->domain )
			 sptr->domain = liberate(sptr->domain);
		if ( sptr->timestamp )
			 sptr->timestamp = liberate(sptr->timestamp);
		if ( sptr->owner )
			 sptr->owner = liberate(sptr->owner);
		sptr = liberate( sptr );
	}
	return((struct cords_ipaddress *) 0);

}

/*	------------------------------------------	*/
/*	r e s e t _ c o r d s _ i p a d d r e s s 	*/
/*	------------------------------------------	*/
public struct cords_ipaddress * reset_cords_ipaddress(struct cords_ipaddress * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->version = (char*) 0;
		sptr->type = (char*) 0;
		sptr->value = (char*) 0;
		sptr->domain = (char*) 0;
		sptr->timestamp = (char*) 0;
		sptr->owner = (char*) 0;
	}
	return(sptr);

}

/*	------------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ i p a d d r e s s 	*/
/*	------------------------------------------------	*/
public struct cords_ipaddress * allocate_cords_ipaddress()
{
	struct cords_ipaddress * sptr;
	if (!( sptr = allocate( sizeof( struct cords_ipaddress ) ) ))
		return( sptr );
	else	return( reset_cords_ipaddress(sptr) );
}

/*	------------------------------------------	*/
/*	x m l i n _ c o r d s _ i p a d d r e s s 	*/
/*	------------------------------------------	*/
public int xmlin_cords_ipaddress(struct cords_ipaddress * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"version") ))
		{
			if ( wptr->value ) { sptr->version = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"type") ))
		{
			if ( wptr->value ) { sptr->type = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"value") ))
		{
			if ( wptr->value ) { sptr->value = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"domain") ))
		{
			if ( wptr->value ) { sptr->domain = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"timestamp") ))
		{
			if ( wptr->value ) { sptr->timestamp = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"owner") ))
		{
			if ( wptr->value ) { sptr->owner = allocate_string(wptr->value); }
		}
	}
	return(0);

}

/*	--------------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ i p a d d r e s s 	*/
/*	--------------------------------------------------	*/
public int rest_occi_cords_ipaddress(FILE * fh,struct cords_ipaddress * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.version='%s'\r\n",prefix,nptr,(sptr->version?sptr->version:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.type='%s'\r\n",prefix,nptr,(sptr->type?sptr->type:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.value='%s'\r\n",prefix,nptr,(sptr->value?sptr->value:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.domain='%s'\r\n",prefix,nptr,(sptr->domain?sptr->domain:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.timestamp='%s'\r\n",prefix,nptr,(sptr->timestamp?sptr->timestamp:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.owner='%s'\r\n",prefix,nptr,(sptr->owner?sptr->owner:""));
	return(0);

}

#endif	/* _ipaddress_c_ */
