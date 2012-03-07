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

#ifndef	_occi_body_c
#define	_occi_body_c

#include "occibody.h"
#include "xlink.h"
/*	------------------------------------------------------------	*/
/*		o c c i _ c o n s u m e _ h e a d e r 			*/
/*	------------------------------------------------------------	*/
private	struct rest_header * occi_consume_header( struct rest_header * hptr )
{
	struct	rest_header * previous;
	struct	rest_header * next;
	if ( hptr->name )
		hptr->name = liberate( hptr->name );
	return( hptr->next );
}

/*	------------------------------------------------------------	*/
/*		o c c i _ c o n t e n t _ l e n g t h 			*/
/*	------------------------------------------------------------	*/
private	char *	occi_content_length( struct rest_header * hptr, char * filename )
{
	struct	stat info;
	char	length[64];
	if ( stat( filename,&info ) < 0 )
		return( filename );
	else
	{
		sprintf(length,"%u",info.st_size);
		rest_replace_header( hptr, length );
		return( filename );
	}
}	

/*	------------------------------------------------------------	*/
/*	  		o c c i _ j s o n _ b o d y 			*/
/*	------------------------------------------------------------	*/
private	char *	occi_json_body( 
		struct occi_category * cptr,
		struct rest_header  * hptr )
{
	FILE *	h;
	char *	filename;
	char	buffer[2048];
	char *	vptr;
	char *	nptr;
	int	attributs=0;
	int	locations=0;
	struct	rest_header * contentlength=(struct rest_header *) 0;
	if (!( filename = rest_temporary_filename( "json" ) ))
		return( filename );

	else if (!( h = fopen(filename,"w")))
	{
		return(liberate(filename));
	}
	else
	{
		while ( hptr )
		{
			if (!( hptr->name ))
				hptr = hptr->next;
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_TYPE ) ))
			{
				rest_replace_header( hptr, _OCCI_MIME_JSON );
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_LENGTH ) ))
			{
				contentlength = hptr;
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _OCCI_LOCATION ) ))
			{
				if (!( locations++ ))
				{
					fprintf(h,"{ %c%s%c : { %c%s%c : { %clocation%c : [\n",
						0x0022,cptr->domain,0x0022, 
						0x0022,cptr->id,0x0022,
						0x0022, 0x0022 );
				}
				else	fprintf(h,",\n");
				fprintf(h,"\t%c%s%c",0x0022,hptr->value,0x0022);
				hptr = occi_consume_header( hptr );
			}
			else if (!( strcasecmp( hptr->name, _OCCI_ATTRIBUTE ) ))
			{
				if (!( attributs++ ))
				{
					fprintf(h,"{ %c%s%c : { %c%s%c : { \n",
						0x0022,cptr->domain,0x0022, 
						0x0022,cptr->id,0x0022 );
				}
				else	fprintf(h,",\n");
				strcpy((nptr = vptr = buffer),hptr->value);
				while ( *vptr )
				{
					if ( *vptr == '=' )
					{
						*(vptr++) = 0;
						break;
					}
					else if ( *(vptr++) == '.' )
						nptr = vptr;
				}
				fprintf(h,"\t%c%s%c : %c%s%c",0x0022,nptr,0x0022,0x0022,vptr,0x0022);
				hptr = occi_consume_header( hptr );
			}
			else	hptr = hptr->next;
		}
		if ( attributs )
			fprintf(h,"\t}\n");
		else if ( locations )
			fprintf(h,"\t] } \n");
		fprintf(h,"}\n}\n");
		fclose(h);
		return( occi_content_length(contentlength, filename ));
	}
}

/*	------------------------------------------------------------	*/
/*	  		o c c i _ h t m l _ s t y l e 			*/
/*	------------------------------------------------------------	*/
private	void	occi_html_style( FILE * h, char * filename )
{
	FILE * css;
	int	c;
	if (!( filename ))
		return;
	else if (!( css = fopen( filename,"r" ) ))
		return;
	else	
	{
		fprintf(h,"<style type='text/css' media=SCREEN>\n");
		while ((c = fgetc(css)) > 0)
			fputc(c,h);
		fclose(css);
		fprintf(h,"</style>\n");
		return;
	}
}

/*	------------------------------------------------------------	*/
/*	  		o c c i _ h t m l _ b o d y 			*/
/*	------------------------------------------------------------	*/
private	char *	occi_html_capacities( 
		struct occi_category * cptr,
		struct rest_header  * hptr )
{
	FILE *	h;
	char *	filename;
	char	buffer[2048];
	char *	vptr;
	char *	nptr;
	struct	rest_header * contentlength=(struct rest_header *) 0;
	if (!( filename = rest_temporary_filename( "html" ) ))
		return( filename );

	else if (!( h = fopen(filename,"w")))
	{
		return(liberate(filename));
	}
	else
	{
		fprintf(h,"<html><head><title>ACCORDS OCCI Capabilities</title>\n");
		occi_html_style(h,"style.css");
		fprintf(h,"</head><body><div align=center><h2>ACCORDS OCCI Capabilities</h2>\n");
		fprintf(h,"<a href='/-/'>/-/</a><p><table>\n");
		fprintf(h,"<a href='/%s/'>/%s/</a><p><table>\n",cptr->id,cptr->id);
		fprintf(h,"</table>\n");
		fprintf(h,"</div></body></html>\n");
		fclose(h);
		return( filename );
	}
}

/*	------------------------------------------------------------	*/
/*	  		o c c i _ h t m l _ b o d y 			*/
/*	------------------------------------------------------------	*/
private	char *	occi_html_body( 
		struct occi_category * cptr,
		struct rest_header  * hptr )
{
	FILE *	h;
	char *	filename;
	char	buffer[2048];
	char *	vptr;
	char *	name;
	char *	wptr;
	int	attributs=0;
	int	locations=0;
	char *	publisher;
	struct	rest_header * contentlength=(struct rest_header *) 0;
	struct	occi_link_node  * nptr;
	struct	cords_xlink	* lptr;
	if (!( filename = rest_temporary_filename( "html" ) ))
		return( filename );

	else if (!( h = fopen(filename,"w")))
	{
		return(liberate(filename));
	}
	else
	{
		while ( hptr )
		{
			if (!( hptr->name ))
				hptr = hptr->next;
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_TYPE ) ))
			{
				rest_replace_header( hptr, _OCCI_TEXT_HTML );
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_LENGTH ) ))
			{
				contentlength = hptr;
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _OCCI_LOCATION ) ))
			{
				if (!( locations++ ))
				{
					fprintf(h,"<html><head><title>ACCORDS OCCI Location List %s</title>\n",cptr->id);
					occi_html_style(h,"style.css");
					fprintf(h,"</head><body><div align=center><table><tr><th><h2>ACCORDS OCCI Location List</h2></th></tr>\n");
					if ((publisher = default_publisher()) != (char *) 0)
					{
						fprintf(h,"<tr><th>");
						fprintf(h,"<a href='%s/publication/'>",publisher);
						fprintf(h,"/publication/</a>\n");
						fprintf(h,"</th></tr>");
					}
					fprintf(h,"<tr><th><a href='/%s/'>/%s/</a></th></tr><tr><td><div align=center><table>\n",cptr->id,cptr->id);
				}
				fprintf(h,"<tr><th><a href='http://%s'>http://%s</a></th></tr>\n",hptr->value,hptr->value);
				hptr = occi_consume_header( hptr );
			}
			else if (!( strcasecmp( hptr->name, _OCCI_ATTRIBUTE ) ))
			{
				if (!( attributs++ ))
				{
					fprintf(h,"<html><head><title>ACCORDS OCCI Category Instance %s</title>\n",cptr->id);
					occi_html_style(h,"style.css");
					fprintf(h,"</head><body><div align=center><table><tr><th><h2>ACCORDS OCCI Category Instance</h2></th></tr>\n");
					if ((publisher = default_publisher()) != (char *) 0)
					{
						fprintf(h,"<tr><th>");
						fprintf(h,"<a href='%s/publication/'>",publisher);
						fprintf(h,"/publication/</a>\n");
						fprintf(h,"</th></tr>");
					}
					fprintf(h,"<tr><th><a href='/%s/'>/%s/</a></th></tr><tr><td><div align=center><table>\n",cptr->id,cptr->id);
				}
				strcpy((name = vptr = buffer),hptr->value);
				while ( *vptr )
				{
					if ( *vptr == '=' )
					{
						*(vptr++) = 0;
						break;
					}
					else if ( *(vptr++) == '.' )
						name = vptr;
				}
				fprintf(h,"<tr><th>%s</th>",name);
				fprintf(h,"<td><input type=text name='%s' value='%s'></td></tr>\n",name,vptr);
				hptr = occi_consume_header( hptr );
			}
			else	hptr = hptr->next;
		}
		if ( attributs )
		{
			fprintf(h,"<tr><th>Links</th><td>\n");
			for (	nptr=occi_first_link_node();
				nptr != (struct occi_link_node *) 0;
				nptr = nptr->next )
			{
				if (!( lptr = nptr->contents ))
					continue;
				else if (!( lptr->source ))
					continue;
				else if (!( lptr->target ))
					continue;
				else if (!( wptr = occi_category_id( lptr->source ) ))
					continue;
				else if ( strcmp( wptr, cptr->id ) != 0)
					continue;
				else	fprintf(h,"%s<br>",lptr->target);
			}
			fprintf(h,"</td></tr>\n");
			fprintf(h,"</table>\n");
		}
		else if ( locations )
			fprintf(h,"</table>\n");
		else	fprintf(h,"<html><head></head><body><div align=center><table><tr><th>No Content</th></tr>\n");
		fprintf(h,"</div></table></div></body></html>\n");
		fclose(h);
		return( occi_content_length(contentlength, filename ));
	}
}

/*	------------------------------------------------------------	*/
/*		   	o c c i _ t e x t _ b o d y 			*/
/*	------------------------------------------------------------	*/
private	char *	occi_text_body( 
		struct occi_category * cptr,
		struct rest_header  * hptr )
{
	FILE *	h;
	struct	rest_header * contentlength=(struct rest_header *) 0;
	char *	filename;
	char		buffer[2048];
	char *	vptr;
	int		attributs=0;

	if (!( filename = rest_temporary_filename( "txt" ) ))
		return((char *) 0);

	else if (!( h = fopen(filename,"w") ))
		return( liberate( filename ) );

	else
	{
		fprintf(h,"{ Category: %c%s%c; ",0x0022,cptr->id,0x0022 );
		while ( hptr )
		{
			if (!( hptr->name ))
				hptr = hptr->next;
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_TYPE ) ))
			{
				rest_replace_header( hptr, _OCCI_MIME_JSON );
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_LENGTH ) ))
			{
				contentlength = hptr;
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _OCCI_ATTRIBUTE ) ))
			{
				fprintf(h,"%s: %s\n",hptr->name,hptr->value);
				hptr = occi_consume_header( hptr );
			}
			else	hptr = hptr->next;
		}
		if ( attributs )
			fprintf(h,"\t}\n");
		else	fprintf(h,"%c%c\n",0x0022,0x0022);
		fprintf(h,"}\n");

		fclose(h);
		return( occi_content_length(contentlength, filename ));
	}
}

/*	------------------------------------------------------------	*/
/*		   	o c c i _ p h p _ b o d y 			*/
/*	------------------------------------------------------------	*/
private	char *	occi_php_body( 
		struct occi_category * cptr,
		struct rest_header  * hptr )
{
	FILE *	h;
	struct	rest_header * contentlength=(struct rest_header *) 0;
	char *	filename;
	char		buffer[2048];
	char *	vptr;
	char *	nptr;
	int		attributs=0;
	if (!( filename = rest_temporary_filename( "php" ) ))
		return( filename );

	else if (!( h = fopen(filename,"w")))
	{
		return( liberate( filename ) );
	}
	else
	{
		fprintf(h,"<?php\n\%c%s%c => array(",0x0022,cptr->id,0x0022);
		while ( hptr )
		{
			if (!( hptr->name ))
				hptr = hptr->next;
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_TYPE ) ))
			{
				rest_replace_header( hptr, _OCCI_MIME_JSON );
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_LENGTH ) ))
			{
				contentlength = hptr;
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _OCCI_ATTRIBUTE ) ))
			{
				strcpy((nptr = vptr = buffer),hptr->value);
				while ( *vptr )
				{
					if ( *vptr == '=' )
					{
						*(vptr++) = 0;
						break;
					}
					else if ( *(vptr++) == '.' )
						nptr = vptr;
				}
				if ( attributs++ )
					fprintf(h,",\n");
				fprintf(h,"\t%c%s%c => %c%s%c",0x0022,nptr,0x0022,0x0022,vptr,0x0022);
				hptr = occi_consume_header( hptr );
			}
			else	hptr = hptr->next;
		}
		fprintf(h," );\n");
		fprintf(h,"?>");

		fclose(h);
		return( occi_content_length(contentlength, filename ));
	}
}

/*	------------------------------------------------------------	*/
/*	     		o c c i _ x m l _ b o d y 			*/
/*	------------------------------------------------------------	*/
private	char * 	occi_xml_body( 
		struct occi_category * cptr,
		struct rest_header  * hptr )
{
	FILE *	h;
	struct	rest_header * contentlength=(struct rest_header *) 0;
	char *	filename;
	char		buffer[2048];
	char *	vptr;
	char *	nptr;
	int		elements=0;
	int		attributs=0;
	if (!( filename = rest_temporary_filename( "xml" ) ))
		return( filename );

	else if (!( h = fopen(filename,"w")))
	{
		return(liberate( filename ) );
	}
	else
	{
		fprintf(h,"<?xml version='1.0' encoding='UTF-8'?>\n");

		while ( hptr )
		{
			if (!( hptr->name ))
				hptr = hptr->next;
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_TYPE ) ))
			{
				rest_replace_header( hptr, _OCCI_MIME_XML );
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _HTTP_CONTENT_LENGTH ) ))
			{
				
				contentlength = hptr;
				hptr = hptr->next;
			}
			else if (!( strcasecmp( hptr->name, _OCCI_LOCATION  ) ))
			{

				if (!( elements++ ))
					fprintf(h,"<%s>\n",cptr->id);
				fprintf(h,"<location href=%c%s%c/>\n",0x0022,hptr->value,0x0022);
				hptr = occi_consume_header( hptr );

			}
			else if (!( strcasecmp( hptr->name, _OCCI_ATTRIBUTE ) ))
			{
				strcpy((nptr = vptr = buffer),hptr->value);
				while ( *vptr )
				{
					if ( *vptr == '=' )
					{
						*(vptr++) = 0;
							break;
					}
					else if ( *(vptr++) == '.' )
						nptr = vptr;
				}
				if (!( attributs++ ))
					fprintf(h,"<%s\n",cptr->id);
				fprintf(h,"\t%s=%c%s%c\n",nptr,0x0022,vptr,0x0022);
				hptr = occi_consume_header( hptr );
			}
			else	hptr = hptr->next;
		}
		if ( elements )
			fprintf(h,"</%s>\n",cptr->id);
		else if ( attributs )
			fprintf(h," />\n");
		fclose(h);
		return( occi_content_length(contentlength, filename ));
	}
}

/*	--------------------------------------------------------------	*/
/*		a c c e p t _ s t r i n g _ i n c l u d e s		*/
/*	--------------------------------------------------------------	*/
private	int	accept_string_includes( char * sptr, char * tptr )
{
	char *	xptr;
	char *	wptr;
	char *	root;
	if (!( wptr = allocate_string( sptr ) ))
		return( 0 );
	else	root = wptr;
	while ( *wptr )
	{
		xptr = wptr;
		while ( *xptr )
		{
			if (( *xptr == ',' )|| ( *xptr == ';' ))
			{
				*(xptr++) = 0;
				break;
			}
			else	xptr++;
		}
		if (!( strcmp( wptr, tptr ) ))
		{
			liberate( root );
			return( 1 );
		}
		wptr = xptr;	
	}
	liberate( root );
	return( 0 );
}

/*	---------------------------------------------------	*/
/*		o c c i _ r e s p o n s e _ b o d y  		*/
/*	---------------------------------------------------	*/
public	char * occi_response_body( char * accepts, struct occi_category * cptr, struct rest_header * hptr )
{
	if (!( strcasecmp( accepts, _OCCI_TEXT_OCCI ) ))
		return( occi_text_body( cptr, hptr ) );
	else if ( accept_string_includes( accepts, _OCCI_TEXT_HTML ) )
		return( occi_html_body( cptr, hptr ) );
	else if ((!( strcasecmp( accepts, _OCCI_OCCI_PHP ) ))
	     ||  (!( strcasecmp( accepts, _OCCI_APP_PHP  ) ))
	     ||  (!( strcasecmp( accepts, _OCCI_TEXT_PHP ) )))
		return( occi_php_body(  cptr, hptr ) );
	else if ((!( strcasecmp( accepts, _OCCI_OCCI_JSON ) ))
	     ||  (!( strcasecmp( accepts, _OCCI_APP_JSON  ) ))
	     ||  (!( strcasecmp( accepts, _OCCI_TEXT_JSON ) )))
		return( occi_json_body(  cptr, hptr ) );
	else if ((!( strcasecmp( accepts, _OCCI_MIME_XML  ) ))
	     ||  (!( strcasecmp( accepts, _OCCI_APP_XML   ) ))
	     ||  (!( strcasecmp( accepts, _OCCI_TEXT_XML  ) )))
		return( occi_xml_body(  cptr, hptr  ) );
	else	return( occi_text_body( cptr, hptr ) );
}

	/* ---------- */
#endif	/* _occi_body */
	/* ---------- */

