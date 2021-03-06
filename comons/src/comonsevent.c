#ifndef	_comonsevent_c
#define	_comonsevent_c

/*	-------------------------------------------	*/
/* 	      c r e a t e _ e v e n t  			*/
/*	-------------------------------------------	*/
private	int	create_event(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_event * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else
	{
		pptr->timestamp = time((long*) 0);
		return(0);
	}
}

/*	-------------------------------------------	*/
/* 	    r e t r i e v e _ e v e n t  		*/
/*	-------------------------------------------	*/
private	int	retrieve_event(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_event * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	      u p d a t e _ e v e n t  			*/
/*	-------------------------------------------	*/
private	int	update_event(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_event * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

/*	-------------------------------------------	*/
/* 	      d e l e t e _ e v e n t	 	 	*/
/*	-------------------------------------------	*/
private	int	delete_event(struct occi_category * optr, void * vptr)
{
	struct	occi_kind_node * nptr;
	struct	cords_event * pptr;
	if (!( nptr = vptr ))
		return(0);
	else if (!( pptr = nptr->contents ))
		return(0);
	else	return(0);
}

private	struct	occi_interface	event_interface = 
{
	create_event,
	retrieve_event,
	update_event,
	delete_event
};

/*	-----------------------------------------	*/
/*	 c o m o n s _ e v e n t _ b u i l d e r	*/
/*	-----------------------------------------	*/
private	struct	occi_category *	comons_event_builder( char * domain )
{
	struct	occi_category * optr;
	if (!( optr = occi_cords_event_builder( Comons.domain, "event" ) ))
		return( optr );
	else
	{
		optr->callback  = &event_interface;
		optr->access |= _OCCI_NO_PRICING;
		return( optr );
	}
}
#endif	/* _comonsevent_c */
	/* -------------- */

