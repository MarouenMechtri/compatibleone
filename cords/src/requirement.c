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
#ifndef _requirement_c_
#define _requirement_c_

#include "element.h"

#include "requirement.h"

/*	----------------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ r e q u i r e m e n t 	*/
/*	----------------------------------------------------	*/
public struct cords_requirement * liberate_cords_requirement(struct cords_requirement * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->description )
			 sptr->description = liberate(sptr->description);
		if ( sptr->expression )
			 sptr->expression = liberate(sptr->expression);
		if ( sptr->type )
			 sptr->type = liberate(sptr->type);
		sptr = liberate( sptr );
	}
	return((struct cords_requirement *) 0);

}

/*	----------------------------------------------	*/
/*	r e s e t _ c o r d s _ r e q u i r e m e n t 	*/
/*	----------------------------------------------	*/
public struct cords_requirement * reset_cords_requirement(struct cords_requirement * sptr)
{
	if ( sptr )
	{
		sptr->previous = (struct cords_requirement*) 0;
		sptr->next = (struct cords_requirement*) 0;
		sptr->id = (char*) 0;
		sptr->description = (char*) 0;
		sptr->expression = (char*) 0;
		sptr->type = (char*) 0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	----------------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ r e q u i r e m e n t 	*/
/*	----------------------------------------------------	*/
public struct cords_requirement * allocate_cords_requirement()
{
	struct cords_requirement * sptr;
	if (!( sptr = allocate( sizeof( struct cords_requirement ) ) ))
		return( sptr );
	else	return( reset_cords_requirement(sptr) );
}

/*	----------------------------------------------	*/
/*	x m l i n _ c o r d s _ r e q u i r e m e n t 	*/
/*	----------------------------------------------	*/
public int xmlin_cords_requirement(struct cords_requirement * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"description") ))
		{
			if ( wptr->value ) { sptr->description = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"expression") ))
		{
			if ( wptr->value ) { sptr->expression = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"type") ))
		{
			if ( wptr->value ) { sptr->type = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	------------------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ r e q u i r e m e n t 	*/
/*	------------------------------------------------------	*/
public int rest_occi_cords_requirement(FILE * fh,struct cords_requirement * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.description='%s'\r\n",prefix,nptr,(sptr->description?sptr->description:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.expression='%s'\r\n",prefix,nptr,(sptr->expression?sptr->expression:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.type='%s'\r\n",prefix,nptr,(sptr->type?sptr->type:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _requirement_crequirement_c_ */
