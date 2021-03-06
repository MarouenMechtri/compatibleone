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
#ifndef _system_c_
#define _system_c_

#include "element.h"

#include "system.h"

/*	------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ s y s t e m 	*/
/*	------------------------------------------	*/
public struct cords_system * liberate_cords_system(struct cords_system * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->nature )
			 sptr->nature = liberate(sptr->nature);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->version )
			 sptr->version = liberate(sptr->version);
		if ( sptr->distribution )
			 sptr->distribution = liberate(sptr->distribution);
		if ( sptr->description )
			 sptr->description = liberate(sptr->description);
		if ( sptr->constraint )
			 sptr->constraint = liberate(sptr->constraint);
		if ( sptr->requirement )
			 sptr->requirement = liberate(sptr->requirement);
		if ( sptr->price )
			 sptr->price = liberate(sptr->price);
		if ( sptr->license )
			 sptr->license = liberate(sptr->license);
		sptr = liberate( sptr );
	}
	return((struct cords_system *) 0);

}

/*	------------------------------------	*/
/*	r e s e t _ c o r d s _ s y s t e m 	*/
/*	------------------------------------	*/
public struct cords_system * reset_cords_system(struct cords_system * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->nature = (char*) 0;
		sptr->name = (char*) 0;
		sptr->version = (char*) 0;
		sptr->distribution = (char*) 0;
		sptr->description = (char*) 0;
		sptr->constraint = (char*) 0;
		sptr->requirement = (char*) 0;
		sptr->price = (char*) 0;
		sptr->license = (char*) 0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ s y s t e m 	*/
/*	------------------------------------------	*/
public struct cords_system * allocate_cords_system()
{
	struct cords_system * sptr;
	if (!( sptr = allocate( sizeof( struct cords_system ) ) ))
		return( sptr );
	else	return( reset_cords_system(sptr) );
}

/*	------------------------------------	*/
/*	x m l i n _ c o r d s _ s y s t e m 	*/
/*	------------------------------------	*/
public int xmlin_cords_system(struct cords_system * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"nature") ))
		{
			if ( wptr->value ) { sptr->nature = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"name") ))
		{
			if ( wptr->value ) { sptr->name = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"version") ))
		{
			if ( wptr->value ) { sptr->version = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"distribution") ))
		{
			if ( wptr->value ) { sptr->distribution = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"description") ))
		{
			if ( wptr->value ) { sptr->description = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"constraint") ))
		{
			if ( wptr->value ) { sptr->constraint = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"requirement") ))
		{
			if ( wptr->value ) { sptr->requirement = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"price") ))
		{
			if ( wptr->value ) { sptr->price = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"license") ))
		{
			if ( wptr->value ) { sptr->license = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	--------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ s y s t e m 	*/
/*	--------------------------------------------	*/
public int rest_occi_cords_system(FILE * fh,struct cords_system * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.nature='%s'\r\n",prefix,nptr,(sptr->nature?sptr->nature:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.version='%s'\r\n",prefix,nptr,(sptr->version?sptr->version:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.distribution='%s'\r\n",prefix,nptr,(sptr->distribution?sptr->distribution:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.description='%s'\r\n",prefix,nptr,(sptr->description?sptr->description:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.constraint='%s'\r\n",prefix,nptr,(sptr->constraint?sptr->constraint:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.requirement='%s'\r\n",prefix,nptr,(sptr->requirement?sptr->requirement:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.price='%s'\r\n",prefix,nptr,(sptr->price?sptr->price:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.license='%s'\r\n",prefix,nptr,(sptr->license?sptr->license:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _system_csystem_c_ */
