
#ifndef	_windowsazure_h
#define	_windowsazure_h

struct	windowsazure
{
	char *	id;

	char *	name;
	char *	flavor;
	char *	image;
	char *	profile;

	char *	number;
	char *	rootpass;
	char *	reference;
	char *	publicaddr;
	char *	privateaddr;

	char *	hostname;

	int	when;

	int	status;
};

#endif	


