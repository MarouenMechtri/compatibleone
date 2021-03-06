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
#ifndef _quota_c_
#define _quota_c_

#include "element.h"

#include "quota.h"

/*	----------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ q u o t a 	*/
/*	----------------------------------------	*/
public struct cords_quota * liberate_cords_quota(struct cords_quota * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->property )
			 sptr->property = liberate(sptr->property);
		if ( sptr->description )
			 sptr->description = liberate(sptr->description);
		if ( sptr->operator )
			 sptr->operator = liberate(sptr->operator);
		if ( sptr->price )
			 sptr->price = liberate(sptr->price);
		if ( sptr->zone )
			 sptr->zone = liberate(sptr->zone);
		if ( sptr->opinion )
			 sptr->opinion = liberate(sptr->opinion);
		sptr = liberate( sptr );
	}
	return((struct cords_quota *) 0);

}

/*	----------------------------------	*/
/*	r e s e t _ c o r d s _ q u o t a 	*/
/*	----------------------------------	*/
public struct cords_quota * reset_cords_quota(struct cords_quota * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->property = (char*) 0;
		sptr->description = (char*) 0;
		sptr->operator = (char*) 0;
		sptr->price = (char*) 0;
		sptr->zone = (char*) 0;
		sptr->opinion = (char*) 0;
		sptr->ceiling =  0;
		sptr->offered =  0;
		sptr->reserved =  0;
		sptr->consumed =  0;
		sptr->granularity =  0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	----------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ q u o t a 	*/
/*	----------------------------------------	*/
public struct cords_quota * allocate_cords_quota()
{
	struct cords_quota * sptr;
	if (!( sptr = allocate( sizeof( struct cords_quota ) ) ))
		return( sptr );
	else	return( reset_cords_quota(sptr) );
}

/*	----------------------------------	*/
/*	x m l i n _ c o r d s _ q u o t a 	*/
/*	----------------------------------	*/
public int xmlin_cords_quota(struct cords_quota * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"property") ))
		{
			if ( wptr->value ) { sptr->property = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"description") ))
		{
			if ( wptr->value ) { sptr->description = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"operator") ))
		{
			if ( wptr->value ) { sptr->operator = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"price") ))
		{
			if ( wptr->value ) { sptr->price = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"zone") ))
		{
			if ( wptr->value ) { sptr->zone = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"opinion") ))
		{
			if ( wptr->value ) { sptr->opinion = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"ceiling") ))
		{
			if ( wptr->value ) { sptr->ceiling = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"offered") ))
		{
			if ( wptr->value ) { sptr->offered = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"reserved") ))
		{
			if ( wptr->value ) { sptr->reserved = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"consumed") ))
		{
			if ( wptr->value ) { sptr->consumed = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"granularity") ))
		{
			if ( wptr->value ) { sptr->granularity = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ q u o t a 	*/
/*	------------------------------------------	*/
public int rest_occi_cords_quota(FILE * fh,struct cords_quota * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.property='%s'\r\n",prefix,nptr,(sptr->property?sptr->property:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.description='%s'\r\n",prefix,nptr,(sptr->description?sptr->description:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.operator='%s'\r\n",prefix,nptr,(sptr->operator?sptr->operator:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.price='%s'\r\n",prefix,nptr,(sptr->price?sptr->price:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.zone='%s'\r\n",prefix,nptr,(sptr->zone?sptr->zone:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.opinion='%s'\r\n",prefix,nptr,(sptr->opinion?sptr->opinion:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.ceiling='%u'\r\n",prefix,nptr,sptr->ceiling);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.offered='%u'\r\n",prefix,nptr,sptr->offered);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.reserved='%u'\r\n",prefix,nptr,sptr->reserved);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.consumed='%u'\r\n",prefix,nptr,sptr->consumed);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.granularity='%u'\r\n",prefix,nptr,sptr->granularity);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _quota_cquota_c_ */
