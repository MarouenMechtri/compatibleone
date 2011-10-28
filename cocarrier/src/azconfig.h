
#ifndef	_az_config_h
#define	_az_config_h

struct	az_config
{
	char	*	id;
	char	*	name;
	char 	*	description;
	char	*	user;
	char	*	password;
	char	*	authenticate;
	char	*	agent;
	char 	*	host;
	char	*	version;
	char 	*	namespace;
	char	*	base;
	char	*	subscription;
	char	*	certificate;
	char 	*	tls;
	int		current;
};

#endif

