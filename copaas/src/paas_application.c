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
#ifndef _paas_application_c_
#define _paas_application_c_

#include "element.h"

#include "paas_application.h"

/*	--------------------------------------------------	*/
/*	l i b e r a t e _ p a a s _ a p p l i c a t i o n 	*/
/*	--------------------------------------------------	*/
public struct paas_application * liberate_paas_application(struct paas_application * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->date_created )
			 sptr->date_created = liberate(sptr->date_created);
		if ( sptr->description )
			 sptr->description = liberate(sptr->description);
		if ( sptr->paas_application_version )
			 sptr->paas_application_version = liberate(sptr->paas_application_version);
		if ( sptr->paas_application_environment )
			 sptr->paas_application_environment = liberate(sptr->paas_application_environment);
		if ( sptr->paas_application_configuration_template )
			 sptr->paas_application_configuration_template = liberate(sptr->paas_application_configuration_template);
		sptr = liberate( sptr );
	}
	return((struct paas_application *) 0);

}

/*	--------------------------------------------	*/
/*	r e s e t _ p a a s _ a p p l i c a t i o n 	*/
/*	--------------------------------------------	*/
public struct paas_application * reset_paas_application(struct paas_application * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->date_created = (char*) 0;
		sptr->description = (char*) 0;
		sptr->paas_application_version = (char*) 0;
		sptr->paas_application_environment = (char*) 0;
		sptr->paas_application_configuration_template = (char*) 0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	--------------------------------------------------	*/
/*	a l l o c a t e _ p a a s _ a p p l i c a t i o n 	*/
/*	--------------------------------------------------	*/
public struct paas_application * allocate_paas_application()
{
	struct paas_application * sptr;
	if (!( sptr = allocate( sizeof( struct paas_application ) ) ))
		return( sptr );
	else	return( reset_paas_application(sptr) );
}

/*	--------------------------------------------	*/
/*	x m l i n _ p a a s _ a p p l i c a t i o n 	*/
/*	--------------------------------------------	*/
public int xmlin_paas_application(struct paas_application * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"date_created") ))
		{
			if ( wptr->value ) { sptr->date_created = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"description") ))
		{
			if ( wptr->value ) { sptr->description = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"paas_application_version") ))
		{
			if ( wptr->value ) { sptr->paas_application_version = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"paas_application_environment") ))
		{
			if ( wptr->value ) { sptr->paas_application_environment = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"paas_application_configuration_template") ))
		{
			if ( wptr->value ) { sptr->paas_application_configuration_template = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	----------------------------------------------------	*/
/*	r e s t _ o c c i _ p a a s _ a p p l i c a t i o n 	*/
/*	----------------------------------------------------	*/
public int rest_occi_paas_application(FILE * fh,struct paas_application * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.date_created='%s'\r\n",prefix,nptr,(sptr->date_created?sptr->date_created:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.description='%s'\r\n",prefix,nptr,(sptr->description?sptr->description:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.paas_application_version='%s'\r\n",prefix,nptr,(sptr->paas_application_version?sptr->paas_application_version:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.paas_application_environment='%s'\r\n",prefix,nptr,(sptr->paas_application_environment?sptr->paas_application_environment:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.paas_application_configuration_template='%s'\r\n",prefix,nptr,(sptr->paas_application_configuration_template?sptr->paas_application_configuration_template:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _paas_application_cpaas_application_c_ */
