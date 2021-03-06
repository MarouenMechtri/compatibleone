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
#ifndef _tarif_c_
#define _tarif_c_

#include "element.h"

#include "tarif.h"

/*	----------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ t a r i f 	*/
/*	----------------------------------------	*/
public struct cords_tarif * liberate_cords_tarif(struct cords_tarif * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->period )
			 sptr->period = liberate(sptr->period);
		if ( sptr->value )
			 sptr->value = liberate(sptr->value);
		if ( sptr->rate )
			 sptr->rate = liberate(sptr->rate);
		if ( sptr->taxe )
			 sptr->taxe = liberate(sptr->taxe);
		if ( sptr->nature )
			 sptr->nature = liberate(sptr->nature);
		sptr = liberate( sptr );
	}
	return((struct cords_tarif *) 0);

}

/*	----------------------------------	*/
/*	r e s e t _ c o r d s _ t a r i f 	*/
/*	----------------------------------	*/
public struct cords_tarif * reset_cords_tarif(struct cords_tarif * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->period = (char*) 0;
		sptr->value = (char*) 0;
		sptr->rate = (char*) 0;
		sptr->taxe = (char*) 0;
		sptr->nature = (char*) 0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	----------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ t a r i f 	*/
/*	----------------------------------------	*/
public struct cords_tarif * allocate_cords_tarif()
{
	struct cords_tarif * sptr;
	if (!( sptr = allocate( sizeof( struct cords_tarif ) ) ))
		return( sptr );
	else	return( reset_cords_tarif(sptr) );
}

/*	----------------------------------	*/
/*	x m l i n _ c o r d s _ t a r i f 	*/
/*	----------------------------------	*/
public int xmlin_cords_tarif(struct cords_tarif * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"period") ))
		{
			if ( wptr->value ) { sptr->period = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"value") ))
		{
			if ( wptr->value ) { sptr->value = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"rate") ))
		{
			if ( wptr->value ) { sptr->rate = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"taxe") ))
		{
			if ( wptr->value ) { sptr->taxe = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"nature") ))
		{
			if ( wptr->value ) { sptr->nature = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ t a r i f 	*/
/*	------------------------------------------	*/
public int rest_occi_cords_tarif(FILE * fh,struct cords_tarif * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.period='%s'\r\n",prefix,nptr,(sptr->period?sptr->period:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.value='%s'\r\n",prefix,nptr,(sptr->value?sptr->value:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.rate='%s'\r\n",prefix,nptr,(sptr->rate?sptr->rate:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.taxe='%s'\r\n",prefix,nptr,(sptr->taxe?sptr->taxe:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.nature='%s'\r\n",prefix,nptr,(sptr->nature?sptr->nature:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _tarif_ctarif_c_ */
