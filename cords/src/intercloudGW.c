/*-------------------------------------------------------------------------------*/
/* ACCORDS PLATFORM                                                              */
/* copyright 2011 by Iain James Marshall (Prologue) <ijm667@hotmail.com>         */
/*-------------------------------------------------------------------------------*/
/* Licensed under the Apache License, Version 2.0 (the "License");             */
/* you may not use this file except in compliance with the License.              */
/* You may obtain a copy of the License at                                       */
/*                                                                               */
/*       http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                               */
/* Unless required by applicable law or agreed to in writing, software           */
/* distributed under the License is distributed on an "AS IS" BASIS,           */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.      */
/* See the License for the specific language governing permissions and           */
/* limitations under the License.                                                */
/*-------------------------------------------------------------------------------*/

#ifndef _intercloudGW_c_
#define _intercloudGW_c_
#include "element.h"
#include "intercloudGW.h"

/*----------------------------------------------------------------------------------------*/
/*                               Liberate_intercloudGW
       *//*----------------------------------------------------------------------------------------*/
public struct intercloudGW * liberate_intercloudGW(struct intercloudGW * sptr)
{
	if( sptr )
	{
		if(sptr->id)
			sptr->id = liberate(sptr->id);
		if(sptr->name)
			sptr->name = liberate(sptr->name);
		if(sptr->node)
			sptr->node = liberate(sptr->node);
		if(sptr->account)
			sptr->account = liberate(sptr->account);
		if(sptr->price)
			sptr->price = liberate(sptr->price);
		if(sptr->state)
			sptr->state = liberate(sptr->state);
		sptr = liberate(sptr);
	}
	return((struct intercloudGW * )0);
}

/*-----------------------------------------------------------------------------------------*/
/*                            Reset_intercloudGW   */
/*-----------------------------------------------------------------------------------------*/
public struct intercloudGW * reset_intercloudGW(struct intercloudGW * sptr)
{
	if( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->node = (char*) 0;
		sptr->account = (char*) 0;
		sptr->price = (char*) 0;
		sptr->state = (char*) 0;
	}
	return (sptr);
}

/*-----------------------------------------------------------------------------------------*/
/*                            Allocate_intercloudGW     */
/*-----------------------------------------------------------------------------------------*/
public struct intercloudGW * allocate_intercloudGW()
{
	struct intercloudGW * sptr;
	if (!( sptr = allocate( sizeof( struct intercloudGW ) ) ))
		return( sptr );
	else  return( reset_intercloudGW(sptr) );
}

/*------------------------------------------------------------------------------------------*/
/*                             Xmlin_intercloudGW      */
/*------------------------------------------------------------------------------------------*/
public int xmlin_intercloudGW(struct intercloudGW * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"node") ))
		{
			if ( wptr->value ) { sptr->node = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"account") ))
		{
			if ( wptr->value ) { sptr->account = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"price") ))
		{
			if ( wptr->value ) { sptr->price = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = allocate_string(wptr->value); }
		}
	}
	return(0);
}

/*---------------------------------------------------------------------------------------*/
/*                         Rest_occi_intercloudGW  */
/*---------------------------------------------------------------------------------------*/
public int rest_occi_intercloudGW(FILE * fh, struct intercloudGW * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.node='%s'\r\n",prefix,nptr,(sptr->node?sptr->node:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.account='%s'\r\n",prefix,nptr,(sptr->account?sptr->account:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.price='%s'\r\n",prefix,nptr,(sptr->price?sptr->price:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%s'\r\n",prefix,nptr,(sptr->state?sptr->state:""));
	return(0);
}

#endif
