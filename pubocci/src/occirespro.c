/* ------------------------------------------------------------------- */
/*  ACCORDS PLATFORM                                                   */
/*  (C) 2011 by Iain James Marshall (Prologue) <ijm667@hotmail.com>    */
/* --------------------------------------------------------------------*/
/*  This is free software; you can redistribute it and/or modify it    */
/*  under the terms of the GNU Lesser General Public License as        */
/*  published by the Free Software Foundation; either version 2.1 of   */
/*  the License, or (at your option) any later version.                */
/*                                                                     */
/*  This software is distributed in the hope that it will be useful,   */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of     */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   */
/*  Lesser General Public License for more details.                    */
/*                                                                     */
/*  You should have received a copy of the GNU Lesser General Public   */
/*  License along with this software; if not, write to the Free        */
/*  Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA */
/*  02110-1301 USA, or see the FSF site: http://www.fsf.org.           */
/* --------------------------------------------------------------------*/
#ifndef _occirespro_c_
#define _occirespro_c_

#include "occirespro.h"

/*	--------------------------------------------------------------	*/
/*	l i b e r a t e _ o c c i _ r e s o l v e d _ a g e n c y 	*/
/*	--------------------------------------------------------------	*/
public struct occi_resolved_agency * liberate_occi_resolved_agency(struct occi_resolved_agency * sptr)
{
	if ( sptr )
	{
		if ( sptr->id )
			 sptr->id = liberate(sptr->id);
		if ( sptr->host )
			 sptr->host = liberate(sptr->host);
		sptr = liberate( sptr );
	}
	return((struct occi_resolved_agency *) 0);

}

/*	--------------------------------------------------------	*/
/*	r e s e t _ o c c i _ r e s o l v e d _ a g e n c y 	*/
/*	--------------------------------------------------------	*/
public struct occi_resolved_agency * reset_occi_resolved_agency(struct occi_resolved_agency * sptr)
{
	if ( sptr )
	{
		sptr->previous = (struct occi_resolved_agency*) 0;
		sptr->next = (struct occi_resolved_agency*) 0;
		sptr->parent = (struct occi_resolved_category*) 0;
		sptr->id = (char*) 0;
		sptr->host = (char*) 0;
		sptr->ttl =  0;
	}
	return(sptr);

}

/*	--------------------------------------------------------------	*/
/*	a l l o c a t e _ o c c i _ r e s o l v e d _ a g e n c y 	*/
/*	--------------------------------------------------------------	*/
public struct occi_resolved_agency * allocate_occi_resolved_agency()
{
	struct occi_resolved_agency * sptr;
	if (!( sptr = allocate( sizeof( struct occi_resolved_agency ) ) ))
		return( sptr );
	else	return( reset_occi_resolved_agency(sptr) );
}

/*	----------------------------------------------------	*/
/*	a d d _ o c c i _ r e s o l v e d _ a g e n c y 	*/
/*	----------------------------------------------------	*/
public struct occi_resolved_agency * add_occi_resolved_agency(struct occi_resolved_category * pptr)
{
	struct occi_resolved_agency * sptr;
	if (!( sptr = allocate( sizeof( struct occi_resolved_agency ) ) ))
		return( sptr );
	else if (!( sptr = reset_occi_resolved_agency(sptr) ))
		return( sptr );
	else
	{
		if (!( sptr->previous = pptr->last ))
			pptr->first = sptr;
		else	sptr->previous->next = sptr;
		pptr->last = sptr;
		sptr->parent = pptr;
		return( sptr );
	}

}

/*	------------------------------------------------------	*/
/*	d r o p _ o c c i _ r e s o l v e d _ a g e n c y 	*/
/*	------------------------------------------------------	*/
public struct occi_resolved_agency * drop_occi_resolved_agency(struct occi_resolved_agency * sptr)
{
	if ( sptr )
	{
		if (!( sptr->parent )) return(sptr);
		if (!( sptr->previous ))
		{
			if (!( sptr->parent->first = sptr->next ))
				sptr->parent->last = (struct occi_resolved_agency *) 0;
			else	sptr->parent->first->previous = (struct occi_resolved_agency *) 0;
		}
		else if (!( sptr->previous->next = sptr->next ))
			sptr->parent->last = sptr->previous;
		if (!( sptr->next ))
		{
			if (!( sptr->parent->last = sptr->previous ))
				sptr->parent->first = (struct occi_resolved_agency *) 0;
			else	sptr->parent->last->next = (struct occi_resolved_agency *) 0;
		}
		else if (!( sptr->next->previous = sptr->previous ))
			sptr->parent->first = sptr->next;
		sptr = liberate_occi_resolved_agency(sptr);
	}
	return((struct occi_resolved_agency *) 0);
}

#endif	/* _occirespro_c_ */
