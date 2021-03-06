/* STRUKT WARNING : this file has been generated and should not be modified by hand */
#ifndef _script_c_
#define _script_c_

#include "element.h"

#include "script.h"

/*	------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ s c r i p t 	*/
/*	------------------------------------------	*/
public struct cords_script * liberate_cords_script(struct cords_script * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->syntax )
			 sptr->syntax = liberate(sptr->syntax);
		if ( sptr->identifier )
			 sptr->identifier = liberate(sptr->identifier);
		if ( sptr->nature )
			 sptr->nature = liberate(sptr->nature);
		sptr = liberate( sptr );
	}
	return((struct cords_script *) 0);

}

/*	------------------------------------	*/
/*	r e s e t _ c o r d s _ s c r i p t 	*/
/*	------------------------------------	*/
public struct cords_script * reset_cords_script(struct cords_script * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->status =  0;
		sptr->name = (char*) 0;
		sptr->syntax = (char*) 0;
		sptr->identifier = (char*) 0;
		sptr->nature = (char*) 0;
		sptr->result =  0;
	}
	return(sptr);

}

/*	------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ s c r i p t 	*/
/*	------------------------------------------	*/
public struct cords_script * allocate_cords_script()
{
	struct cords_script * sptr;
	if (!( sptr = allocate( sizeof( struct cords_script ) ) ))
		return( sptr );
	else	return( reset_cords_script(sptr) );
}

/*	------------------------------------	*/
/*	x m l i n _ c o r d s _ s c r i p t 	*/
/*	------------------------------------	*/
public int xmlin_cords_script(struct cords_script * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"status") ))
		{
			if ( wptr->value ) { sptr->status = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"name") ))
		{
			if ( wptr->value ) { sptr->name = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"syntax") ))
		{
			if ( wptr->value ) { sptr->syntax = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"identifier") ))
		{
			if ( wptr->value ) { sptr->identifier = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"nature") ))
		{
			if ( wptr->value ) { sptr->nature = allocate_string(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"result") ))
		{
			if ( wptr->value ) { sptr->result = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	--------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ s c r i p t 	*/
/*	--------------------------------------------	*/
public int rest_occi_cords_script(FILE * fh,struct cords_script * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.status='%u'\r\n",prefix,nptr,sptr->status);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.syntax='%s'\r\n",prefix,nptr,(sptr->syntax?sptr->syntax:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.identifier='%s'\r\n",prefix,nptr,(sptr->identifier?sptr->identifier:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.nature='%s'\r\n",prefix,nptr,(sptr->nature?sptr->nature:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.result='%u'\r\n",prefix,nptr,sptr->result);
	return(0);

}

#endif	/* _script_c_ */
