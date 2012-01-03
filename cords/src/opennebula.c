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
#ifndef _opennebula_c_
#define _opennebula_c_

#include "element.h"

#include "opennebula.h"

/*	--------------------------------------	*/
/*	l i b e r a t e _ o p e n n e b u l a 	*/
/*	--------------------------------------	*/
public struct opennebula * liberate_opennebula(struct opennebula * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->number )
			 sptr->number = liberate(sptr->number);
		if ( sptr->hostname )
			 sptr->hostname = liberate(sptr->hostname);
		if ( sptr->flavor )
			 sptr->flavor = liberate(sptr->flavor);
		if ( sptr->image )
			 sptr->image = liberate(sptr->image);
		if ( sptr->node )
			 sptr->node = liberate(sptr->node);
		if ( sptr->price )
			 sptr->price = liberate(sptr->price);
		if ( sptr->account )
			 sptr->account = liberate(sptr->account);
		if ( sptr->publicaddr )
			 sptr->publicaddr = liberate(sptr->publicaddr);
		if ( sptr->privateaddr )
			 sptr->privateaddr = liberate(sptr->privateaddr);
		if ( sptr->profile )
			 sptr->profile = liberate(sptr->profile);
		if ( sptr->publicnetwork )
			 sptr->publicnetwork = liberate(sptr->publicnetwork);
		if ( sptr->privatenetwork )
			 sptr->privatenetwork = liberate(sptr->privatenetwork);
		if ( sptr->started )
			 sptr->started = liberate(sptr->started);
		if ( sptr->created )
			 sptr->created = liberate(sptr->created);
		if ( sptr->configuration )
			 sptr->configuration = liberate(sptr->configuration);
		sptr = liberate( sptr );
	}
	return((struct opennebula *) 0);

}

/*	--------------------------------	*/
/*	r e s e t _ o p e n n e b u l a 	*/
/*	--------------------------------	*/
public struct opennebula * reset_opennebula(struct opennebula * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->number = (char*) 0;
		sptr->hostname = (char*) 0;
		sptr->flavor = (char*) 0;
		sptr->image = (char*) 0;
		sptr->node = (char*) 0;
		sptr->price = (char*) 0;
		sptr->account = (char*) 0;
		sptr->publicaddr = (char*) 0;
		sptr->privateaddr = (char*) 0;
		sptr->profile = (char*) 0;
		sptr->publicnetwork = (char*) 0;
		sptr->privatenetwork = (char*) 0;
		sptr->started = (char*) 0;
		sptr->created = (char*) 0;
		sptr->configuration = (char*) 0;
		sptr->when =  0;
		sptr->status =  0;
	}
	return(sptr);

}

/*	--------------------------------------	*/
/*	a l l o c a t e _ o p e n n e b u l a 	*/
/*	--------------------------------------	*/
public struct opennebula * allocate_opennebula()
{
	struct opennebula * sptr;
	if (!( sptr = allocate( sizeof( struct opennebula ) ) ))
		return( sptr );
	else	return( reset_opennebula(sptr) );
}

/*	--------------------------------	*/
/*	x m l i n _ o p e n n e b u l a 	*/
/*	--------------------------------	*/
public int xmlin_opennebula(struct opennebula * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"number") ))
		{
			if ( wptr->value ) { sptr->number = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"hostname") ))
		{
			if ( wptr->value ) { sptr->hostname = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"flavor") ))
		{
			if ( wptr->value ) { sptr->flavor = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"image") ))
		{
			if ( wptr->value ) { sptr->image = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"node") ))
		{
			if ( wptr->value ) { sptr->node = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"price") ))
		{
			if ( wptr->value ) { sptr->price = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"account") ))
		{
			if ( wptr->value ) { sptr->account = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"publicaddr") ))
		{
			if ( wptr->value ) { sptr->publicaddr = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"privateaddr") ))
		{
			if ( wptr->value ) { sptr->privateaddr = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"profile") ))
		{
			if ( wptr->value ) { sptr->profile = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"publicnetwork") ))
		{
			if ( wptr->value ) { sptr->publicnetwork = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"privatenetwork") ))
		{
			if ( wptr->value ) { sptr->privatenetwork = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"started") ))
		{
			if ( wptr->value ) { sptr->started = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"created") ))
		{
			if ( wptr->value ) { sptr->created = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"configuration") ))
		{
			if ( wptr->value ) { sptr->configuration = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"when") ))
		{
			if ( wptr->value ) { sptr->when = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"status") ))
		{
			if ( wptr->value ) { sptr->status = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	----------------------------------------	*/
/*	r e s t _ o c c i _ o p e n n e b u l a 	*/
/*	----------------------------------------	*/
public int rest_occi_opennebula(FILE * fh,struct opennebula * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.number='%s'\r\n",prefix,nptr,(sptr->number?sptr->number:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.hostname='%s'\r\n",prefix,nptr,(sptr->hostname?sptr->hostname:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.flavor='%s'\r\n",prefix,nptr,(sptr->flavor?sptr->flavor:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.image='%s'\r\n",prefix,nptr,(sptr->image?sptr->image:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.node='%s'\r\n",prefix,nptr,(sptr->node?sptr->node:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.price='%s'\r\n",prefix,nptr,(sptr->price?sptr->price:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.account='%s'\r\n",prefix,nptr,(sptr->account?sptr->account:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.publicaddr='%s'\r\n",prefix,nptr,(sptr->publicaddr?sptr->publicaddr:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.privateaddr='%s'\r\n",prefix,nptr,(sptr->privateaddr?sptr->privateaddr:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.profile='%s'\r\n",prefix,nptr,(sptr->profile?sptr->profile:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.publicnetwork='%s'\r\n",prefix,nptr,(sptr->publicnetwork?sptr->publicnetwork:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.privatenetwork='%s'\r\n",prefix,nptr,(sptr->privatenetwork?sptr->privatenetwork:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.started='%s'\r\n",prefix,nptr,(sptr->started?sptr->started:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.created='%s'\r\n",prefix,nptr,(sptr->created?sptr->created:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.configuration='%s'\r\n",prefix,nptr,(sptr->configuration?sptr->configuration:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.when='%u'\r\n",prefix,nptr,sptr->when);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.status='%u'\r\n",prefix,nptr,sptr->status);
	return(0);

}

#endif	/* _opennebula_c_ */
