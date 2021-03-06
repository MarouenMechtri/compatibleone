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
#ifndef _enquiry_c_
#define _enquiry_c_

#include "element.h"

#include "enquiry.h"

/*	--------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ e n q u i r y 	*/
/*	--------------------------------------------	*/
public struct cords_enquiry * liberate_cords_enquiry(struct cords_enquiry * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->where )
			 sptr->where = liberate(sptr->where);
		if ( sptr->what )
			 sptr->what = liberate(sptr->what);
		if ( sptr->who )
			 sptr->who = liberate(sptr->who);
		if ( sptr->pass )
			 sptr->pass = liberate(sptr->pass);
		if ( sptr->state )
			 sptr->state = liberate(sptr->state);
		sptr = liberate( sptr );
	}
	return((struct cords_enquiry *) 0);

}

/*	--------------------------------------	*/
/*	r e s e t _ c o r d s _ e n q u i r y 	*/
/*	--------------------------------------	*/
public struct cords_enquiry * reset_cords_enquiry(struct cords_enquiry * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->where = (char*) 0;
		sptr->what = (char*) 0;
		sptr->who = (char*) 0;
		sptr->pass = (char*) 0;
		sptr->state = (char*) 0;
	}
	return(sptr);

}

/*	--------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ e n q u i r y 	*/
/*	--------------------------------------------	*/
public struct cords_enquiry * allocate_cords_enquiry()
{
	struct cords_enquiry * sptr;
	if (!( sptr = allocate( sizeof( struct cords_enquiry ) ) ))
		return( sptr );
	else	return( reset_cords_enquiry(sptr) );
}

/*	--------------------------------------	*/
/*	x m l i n _ c o r d s _ e n q u i r y 	*/
/*	--------------------------------------	*/
public int xmlin_cords_enquiry(struct cords_enquiry * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"where") ))
		{
			if ( wptr->value ) { sptr->where = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"what") ))
		{
			if ( wptr->value ) { sptr->what = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"who") ))
		{
			if ( wptr->value ) { sptr->who = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"pass") ))
		{
			if ( wptr->value ) { sptr->pass = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = allocate_string(wptr->value); }
		}
	}
	return(0);

}

/*	----------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ e n q u i r y 	*/
/*	----------------------------------------------	*/
public int rest_occi_cords_enquiry(FILE * fh,struct cords_enquiry * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.where='%s'\r\n",prefix,nptr,(sptr->where?sptr->where:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.what='%s'\r\n",prefix,nptr,(sptr->what?sptr->what:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.who='%s'\r\n",prefix,nptr,(sptr->who?sptr->who:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.pass='%s'\r\n",prefix,nptr,(sptr->pass?sptr->pass:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%s'\r\n",prefix,nptr,(sptr->state?sptr->state:""));
	return(0);

}

#endif	/* _enquiry_cenquiry_c_ */
