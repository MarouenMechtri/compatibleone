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
#ifndef	_occixml_c
#define _occixml_c

/*	---------------------------------------------------	*/
/*		o c c i _ x m l _ c a p a c i t y 		*/
/*	---------------------------------------------------	*/
public	char *	occi_xml_capacity( struct occi_category * optr )
{
	char	buffer[8192];
	char  *	term;
	struct	occi_attribute * mptr;
	struct	occi_action    * fptr;
	sprintf(buffer,"%s;\r\n scheme=\"%s\";\r\n class=%s;\r\n rel=\"%s\";\r\n",
		optr->id,optr->scheme,optr->class,optr->rel );

	if ( optr->first )
	{
		strcat( buffer, " attributes");
		term = "=";
		for (	mptr = optr->first;
			mptr != (struct occi_attribute *) 0;
			mptr = mptr->next )
		{
			strcat( buffer, term );
			strcat( buffer, optr->domain );
			strcat( buffer, "." );
			strcat( buffer, optr->id   );
			strcat( buffer, "." );
			strcat( buffer, mptr->name );
			if ( mptr->mandatory )
				strcat( buffer,"{mandatory}" );
			if ( mptr->immutable )
				strcat( buffer,"{immutable}" );
			term=",";
		}
		strcat( buffer, ";\r\n" );

	}
	if ( optr->firstact )
	{
		strcat( buffer, " actions");
		term = "=";
		for (	fptr = optr->firstact;
			fptr != (struct occi_action *) 0;
			fptr = fptr->next )
		{
			strcat( buffer, term );
			strcat( buffer, fptr->name );
			term=",";
		}
		strcat( buffer, ";\r\n" );
	}

	strcat( buffer, " location=\"" );
	strcat( buffer, optr->location );
	strcat( buffer, "\";" );

	return( allocate_string( buffer ) );

}

/*	---------------------------------------------------	*/
/*		o c c i _ x m l _ c a t e g o r y  		*/
/*	---------------------------------------------------	*/
public	char *	occi_xml_category( struct occi_category * optr )
{
	char	buffer[8192];
	char  *	term;
	sprintf(buffer,"%s;\r\n scheme=\"%s\";\r\n class=%s;\r\n rel=\"%s\";",
		optr->id,optr->scheme,optr->class,optr->rel );

	return( allocate_string( buffer ) );
}

/*	---------------------------------------------------	*/
/*		o c c i _ x m l _ l i n k			*/
/*	---------------------------------------------------	*/
public	char *	occi_xml_link( struct occi_category * optr, char * target, char * id )
{
	char	buffer[8192];
	char *	rptr;
	char *	mptr;
	char *	wptr;
	char *	sptr;
	struct	url * uptr;
	if ((!( optr )) || (!( target )) || (!( id )))
		return((char *) 0);
	else if (!( uptr = analyse_url( target )))
		return((char *) 0);
	else if (!( uptr = validate_url( uptr )))
		return((char *) 0);
	else if (!( mptr = uptr->object))
	{
		liberate( uptr );
		return((char *) 0);
	}
	else if (!( mptr = allocate_string( mptr ) ))
	{
		liberate( uptr );
		return((char *) 0);
	}
	else		
	{
		/* cut out the target category name */
		/* -------------------------------- */
		wptr = mptr;
		if ( *wptr == '/' ) wptr++;
		rptr = sptr = wptr;
		while ( *wptr )
		{
			if ( *wptr == '/' )
				rptr = wptr;
			wptr++;
		}
		if ( *rptr == '/' )
			*(rptr++) = 0;

		/* generate the link content */
		/* ------------------------- */
		sprintf(buffer,"<%s>;\r\n rel=\"%s%s\";\r\n self=\"%s\";\r\n category=\"%s\";",
			target, "xml://scheme.compatibleone.fr/occi/compatible#",sptr,
			id, optr->scheme );
		liberate( mptr );
		liberate( uptr );
		return( allocate_string( buffer ) );
	}
}

/*	---------------------------------------------------	*/
/*		o c c i _ x m l _ a t t r i b u t e 		*/
/*	---------------------------------------------------	*/
public	char *	occi_xml_attribute( struct occi_category * optr, struct occi_attribute * aptr )
{
	char	buffer[8192];
	if ( optr->domain )
	{
		strcpy( buffer, optr->domain );
		strcat( buffer, "." );
		strcat( buffer, optr->id   );
		strcat( buffer, "." );
		strcat( buffer, aptr->name );
	}
	else 	strcpy( buffer, aptr->name );
	strcat( buffer, "=" );
	return( allocate_string( buffer ) );
}

/*	---------------------------------------------------	*/
/* 	 o c c i _ x m l _ a t t r i b u t e _ v a l u e	*/
/*	---------------------------------------------------	*/
public	char *	occi_xml_attribute_value( struct occi_category * optr, struct occi_attribute * aptr, char * vptr )
{
	char	buffer[8192];
	if ( optr->domain )
	{
		strcpy( buffer, optr->domain );
		strcat( buffer, "." );
		strcat( buffer, optr->id   );
		strcat( buffer, "." );
		strcat( buffer, aptr->name );
	}
	else 	strcpy( buffer, aptr->name );
	strcat( buffer, "=" );
	strcat( buffer, vptr );
	return( allocate_string( buffer ) );
}

#endif	/* _occixml_c */
	/* ----------- */


