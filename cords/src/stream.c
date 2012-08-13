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
#ifndef _stream_c_
#define _stream_c_

#include "element.h"

#include "stream.h"

/*	------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ s t r e a m 	*/
/*	------------------------------------------	*/
public struct cords_stream * liberate_cords_stream(struct cords_stream * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->service )
			 sptr->service = liberate(sptr->service);
		if ( sptr->session )
			 sptr->session = liberate(sptr->session);
		if ( sptr->consumer )
			 sptr->consumer = liberate(sptr->consumer);
		if ( sptr->connection )
			 sptr->connection = liberate(sptr->connection);
		if ( sptr->nature )
			 sptr->nature = liberate(sptr->nature);
		if ( sptr->date )
			 sptr->date = liberate(sptr->date);
		sptr = liberate( sptr );
	}
	return((struct cords_stream *) 0);

}

/*	------------------------------------	*/
/*	r e s e t _ c o r d s _ s t r e a m 	*/
/*	------------------------------------	*/
public struct cords_stream * reset_cords_stream(struct cords_stream * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->service = (char*) 0;
		sptr->session = (char*) 0;
		sptr->consumer = (char*) 0;
		sptr->connection = (char*) 0;
		sptr->nature = (char*) 0;
		sptr->date = (char*) 0;
		sptr->probes =  0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ s t r e a m 	*/
/*	------------------------------------------	*/
public struct cords_stream * allocate_cords_stream()
{
	struct cords_stream * sptr;
	if (!( sptr = allocate( sizeof( struct cords_stream ) ) ))
		return( sptr );
	else	return( reset_cords_stream(sptr) );
}

/*	------------------------------------	*/
/*	x m l i n _ c o r d s _ s t r e a m 	*/
/*	------------------------------------	*/
public int xmlin_cords_stream(struct cords_stream * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"service") ))
		{
			if ( wptr->value ) { sptr->service = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"session") ))
		{
			if ( wptr->value ) { sptr->session = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"consumer") ))
		{
			if ( wptr->value ) { sptr->consumer = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"connection") ))
		{
			if ( wptr->value ) { sptr->connection = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"nature") ))
		{
			if ( wptr->value ) { sptr->nature = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"date") ))
		{
			if ( wptr->value ) { sptr->date = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"probes") ))
		{
			if ( wptr->value ) { sptr->probes = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	--------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ s t r e a m 	*/
/*	--------------------------------------------	*/
public int rest_occi_cords_stream(FILE * fh,struct cords_stream * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.service='%s'\r\n",prefix,nptr,(sptr->service?sptr->service:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.session='%s'\r\n",prefix,nptr,(sptr->session?sptr->session:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.consumer='%s'\r\n",prefix,nptr,(sptr->consumer?sptr->consumer:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.connection='%s'\r\n",prefix,nptr,(sptr->connection?sptr->connection:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.nature='%s'\r\n",prefix,nptr,(sptr->nature?sptr->nature:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.date='%s'\r\n",prefix,nptr,(sptr->date?sptr->date:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.probes='%u'\r\n",prefix,nptr,sptr->probes);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _stream_cstream_c_ */
