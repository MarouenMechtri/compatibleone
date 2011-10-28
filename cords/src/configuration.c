/* ------------------------------------------------------------------------------------	*/
/*				 CompatibleOne Cloudware				*/
/* ------------------------------------------------------------------------------------ */
/*											*/
/* Ce fichier fait partie de ce(tte) oeuvre de Iain James Marshall et est mise a 	*/
/* disposition selon les termes de la licence Creative Commons Paternit‚ : 		*/
/*											*/
/*			 	Pas d'Utilisation Commerciale 				*/
/*				Pas de Modification 					*/
/*				3.0 non transcrit.					*/
/*											*/
/* ------------------------------------------------------------------------------------ */
/* 			Copyright (c) 2011 Iain James Marshall for Prologue 		*/
/*				   All rights reserved					*/
/* ------------------------------------------------------------------------------------ */
#ifndef _configuration_c_
#define _configuration_c_

#include "element.h"

#include "configuration.h"

/*	--------------------------------------------------------	*/
/*	l i b e r a t e _ c o r d s _ c o n f i g u r a t i o n 	*/
/*	--------------------------------------------------------	*/
public struct cords_configuration * liberate_cords_configuration(struct cords_configuration * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->name )
			 sptr->name = liberate(sptr->name);
		if ( sptr->firstact )
			 sptr->firstact = liberate_cords_action(sptr->firstact);
		if ( sptr->lastact )
			 sptr->lastact = liberate_cords_action(sptr->lastact);
		sptr = liberate( sptr );
	}
	return((struct cords_configuration *) 0);

}

/*	--------------------------------------------------	*/
/*	r e s e t _ c o r d s _ c o n f i g u r a t i o n 	*/
/*	--------------------------------------------------	*/
public struct cords_configuration * reset_cords_configuration(struct cords_configuration * sptr)
{
	if ( sptr )
	{
		sptr->id = (char*) 0;
		sptr->name = (char*) 0;
		sptr->actions =  0;
		sptr->firstact = (struct cords_action*) 0;
		sptr->lastact = (struct cords_action*) 0;
		sptr->state =  0;
	}
	return(sptr);

}

/*	--------------------------------------------------------	*/
/*	a l l o c a t e _ c o r d s _ c o n f i g u r a t i o n 	*/
/*	--------------------------------------------------------	*/
public struct cords_configuration * allocate_cords_configuration()
{
	struct cords_configuration * sptr;
	if (!( sptr = allocate( sizeof( struct cords_configuration ) ) ))
		return( sptr );
	else	return( reset_cords_configuration(sptr) );
}

/*	--------------------------------------------------	*/
/*	x m l i n _ c o r d s _ c o n f i g u r a t i o n 	*/
/*	--------------------------------------------------	*/
public int xmlin_cords_configuration(struct cords_configuration * sptr,struct xml_element * eptr)
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
		else if (!( strcmp(wptr->name,"actions") ))
		{
			if ( wptr->value ) { sptr->actions = atoi(wptr->value); }
		}
		else if (!( strcmp(wptr->name,"state") ))
		{
			if ( wptr->value ) { sptr->state = atoi(wptr->value); }
		}
	}
	return(0);

}

/*	----------------------------------------------------------	*/
/*	r e s t _ o c c i _ c o r d s _ c o n f i g u r a t i o n 	*/
/*	----------------------------------------------------------	*/
public int rest_occi_cords_configuration(FILE * fh,struct cords_configuration * sptr,char * prefix, char * nptr)
{
	struct xml_element * wptr;
	if (!( sptr )) return(0);
	fprintf(fh,"POST /%s/ HTTP/1.1\r\n",nptr);
	fprintf(fh,"Category: %s; scheme='http://scheme.%s.org/occi/%s#'; class='kind';\r\n",nptr,prefix,prefix);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.id='%s'\r\n",prefix,nptr,(sptr->id?sptr->id:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.name='%s'\r\n",prefix,nptr,(sptr->name?sptr->name:""));
	fprintf(fh,"X-OCCI-Attribute: %s.%s.actions='%u'\r\n",prefix,nptr,sptr->actions);
	fprintf(fh,"X-OCCI-Attribute: %s.%s.state='%u'\r\n",prefix,nptr,sptr->state);
	return(0);

}

#endif	/* _configuration_c_ */
