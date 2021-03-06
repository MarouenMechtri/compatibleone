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
#ifndef _control_c_
#define _control_c_

#include "element.h"

#include "control.h"

/*	--------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ c o n t r o l 	*/
/*	--------------------------------------------	*/
public struct cords_control * liberate_cords_control(struct cords_control * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->contract )
			 sptr->contract = liberate(sptr->contract);
		if ( sptr->agreement )
			 sptr->agreement = liberate(sptr->agreement);
		if ( sptr->property )
			 sptr->property = liberate(sptr->property);
		if ( sptr->condition )
			 sptr->condition = liberate(sptr->condition);
		if ( sptr->objective )
			 sptr->objective = liberate(sptr->objective);
		if ( sptr->reference )
			 sptr->reference = liberate(sptr->reference);
		if ( sptr->importance )
			 sptr->importance = liberate(sptr->importance);
		if ( sptr->obligated )
			 sptr->obligated = liberate(sptr->obligated);
		if ( sptr->scope )
			 sptr->scope = liberate(sptr->scope);
		if ( sptr->session )
			 sptr->session = liberate(sptr->session);
		if ( sptr->account )
			 sptr->account = liberate(sptr->account);
		if ( sptr->monitor )
			 sptr->monitor = liberate(sptr->monitor);
		if ( sptr->connection )
			 sptr->connection = liberate(sptr->connection);
		if ( sptr->metric )
			 sptr->metric = liberate(sptr->metric);
		if ( sptr->probe )
			 sptr->probe = liberate(sptr->probe);
		sptr = liberate( sptr );
	}
	return((struct cords_control *) 0);

}

/*	--------------------------------------	*/
/*	r e s e t _ c o r d s _ c o n t r o l 	*/
/*	--------------------------------------	*/
public struct cords_control * reset_cords_control(struct cords_control * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->contract = (char*) 0;
		sptr->agreement = (char*) 0;
		sptr->property = (char*) 0;
		sptr->condition = (char*) 0;
		sptr->objective = (char*) 0;
		sptr->reference = (char*) 0;
		sptr->importance = (char*) 0;
		sptr->obligated = (char*) 0;
		sptr->scope = (char*) 0;
		sptr->session = (char*) 0;
		sptr->account = (char*) 0;
		sptr->monitor = (char*) 0;
		sptr->connection = (char*) 0;
		sptr->metric = (char*) 0;
		sptr->probe = (char*) 0;
		sptr->process =  0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	--------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ c o n t r o l 	*/
/*	--------------------------------------------	*/
public struct cords_control * allocate_cords_control()
{
	struct cords_control * sptr;
	if (!( sptr = allocate( sizeof( struct cords_control ) ) ))
		return( sptr );
	else	return( reset_cords_control(sptr) );
}

/*	--------------------------------------	*/
/*	x m l i n _ c o r d s _ c o n t r o l 	*/
/*	--------------------------------------	*/
public int xmlin_cords_control(struct cords_control * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"contract") ))
		{
			if ( wptr->value ) { sptr->contract = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"agreement") ))
		{
			if ( wptr->value ) { sptr->agreement = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"property") ))
		{
			if ( wptr->value ) { sptr->property = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"condition") ))
		{
			if ( wptr->value ) { sptr->condition = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"objective") ))
		{
			if ( wptr->value ) { sptr->objective = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"reference") ))
		{
			if ( wptr->value ) { sptr->reference = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"importance") ))
		{
			if ( wptr->value ) { sptr->importance = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"obligated") ))
		{
			if ( wptr->value ) { sptr->obligated = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"scope") ))
		{
			if ( wptr->value ) { sptr->scope = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"session") ))
		{
			if ( wptr->value ) { sptr->session = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"account") ))
		{
			if ( wptr->value ) { sptr->account = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"monitor") ))
		{
			if ( wptr->value ) { sptr->monitor = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"connection") ))
		{
			if ( wptr->value ) { sptr->connection = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"metric") ))
		{
			if ( wptr->value ) { sptr->metric = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"probe") ))
		{
			if ( wptr->value ) { sptr->probe = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"process") ))
		{
			if ( wptr->value ) { sptr->process = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	----------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ c o n t r o l 	*/
/*	----------------------------------------------	*/
public int rest_occi_cords_control(FILE * fh,struct cords_control * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.contract='%s'\r\n",prefix,nptr,(sptr->contract?sptr->contract:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.agreement='%s'\r\n",prefix,nptr,(sptr->agreement?sptr->agreement:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.property='%s'\r\n",prefix,nptr,(sptr->property?sptr->property:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.condition='%s'\r\n",prefix,nptr,(sptr->condition?sptr->condition:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.objective='%s'\r\n",prefix,nptr,(sptr->objective?sptr->objective:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.reference='%s'\r\n",prefix,nptr,(sptr->reference?sptr->reference:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.importance='%s'\r\n",prefix,nptr,(sptr->importance?sptr->importance:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.obligated='%s'\r\n",prefix,nptr,(sptr->obligated?sptr->obligated:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.scope='%s'\r\n",prefix,nptr,(sptr->scope?sptr->scope:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.session='%s'\r\n",prefix,nptr,(sptr->session?sptr->session:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.account='%s'\r\n",prefix,nptr,(sptr->account?sptr->account:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.monitor='%s'\r\n",prefix,nptr,(sptr->monitor?sptr->monitor:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.connection='%s'\r\n",prefix,nptr,(sptr->connection?sptr->connection:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.metric='%s'\r\n",prefix,nptr,(sptr->metric?sptr->metric:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.probe='%s'\r\n",prefix,nptr,(sptr->probe?sptr->probe:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.process='%u'\r\n",prefix,nptr,sptr->process);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _control_ccontrol_c_ */
