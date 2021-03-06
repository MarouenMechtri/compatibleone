#
# ACCORDS Makefile.am
#
# Copyright 2011, Mandriva, All rights reserved
#
# Authors:
#   Jean Parpaillon <jparpaillon@mandriva.com>
#
pkgsysconfdir=$(sysconfdir)/$(PACKAGE)
dist_pkgsysconf_DATA=cords_user.xml accords.ini

scripts=accords co-check

aliases = \
	co-start co-platform co-provision co-broker co-command co-parser co-provider co-resolver co-status co-stop \
	run-azprocci run-broker run-cops run-coees run-coips run-comons run-conets run-coobas run-conagios \
	run-coss run-ezvm run-fileserver run-onprocci run-osprocci run-paprocci run-parser run-procci \
	run-cosched run-publisher run-osocciprocci run-dcprocci run-slam \
	run-cosacs run-copaas run-paasprocci accords-config run-cool


EXTRA_DIST = accords.in openssl.cnf accords.ini publication.xml accords-config.in co-check.in accords.init accords.default
CLEANFILES = $(scripts) $(aliases)

# Edit for local run (without installation)
localpath = $(PATH_AZPROCCI):$(PATH_BROKER):$(PATH_COOL):$(PATH_COPS):$(PATH_COMONS):$(PATH_CONETS):$(PATH_COOBAS):$(PATH_COSS):$(PATH_EZVM):$(PATH_FILESERVER):$(PATH_ONPROCCI):$(PATH_OSPROCCI):$(PATH_PARSER):$(PATH_PROCCI):$(PATH_COSCHED):$(PATH_PUBLISHER):$(builddir)
localedit = sed \
        -e 's|@sitepath[@]|$(localpath)|g' \
	-e 's|@bindir[@]|$(bindir)|g' \
        -e 's|@pkgsysconfdir[@]|$(pkgsysconfdir)|g' \
	-e 's|@aliases[@]|$(aliases)|g'

# Edit for normal run (installed)
installpath = $(pkglibexecdir)
installedit = sed \
        -e 's|@sitepath[@]|$(installpath)|g' \
	-e 's|@bindir[@]|$(bindir)|g' \
        -e 's|@pkgsysconfdir[@]|$(pkgsysconfdir)|g' \
	-e 's|@aliases[@]|$(aliases)|g'

all-local: $(scripts)
	chmod 755 accords co-check
	for alias in $(aliases); do \
	  ln -fs accords $$alias; \
	done

install-exec-local: accords.in Makefile accords.init co-check.in
	mkdir -p $(DESTDIR)$(bindir)
	srcdir=''; \
	  test -f ./co-check.in || srcdir=$(srcdir)/; \
	  $(installedit) $${srcdir}co-check.in >$(DESTDIR)$(bindir)/co-check
	srcdir=''; \
	  test -f ./accords.in || srcdir=$(srcdir)/; \
	  $(installedit) $${srcdir}accords.in >$(DESTDIR)$(bindir)/accords
	chmod 755 $(DESTDIR)$(bindir)/accords
	for alias in $(aliases); do \
	  ln -fs accords $(DESTDIR)$(bindir)/$$alias; \
	done
	install -p -m 0755 -D $(srcdir)/accords.init $(DESTDIR)$(sysconfdir)/init.d/compatibleone
	install -p -m 0644 -D $(srcdir)/accords.default $(DESTDIR)$(sysconfdir)/default/accords

uninstall-local:
	for alias in $(aliases); do \
	  rm -f $(DESTDIR)$(bindir)/$$alias; \
	done
	rm -f $(DESTDIR)$(bindir)/accords
	rm -f $(DESTDIR)$(bindir)/co-check
	rm -f $(DESTDIR)$(sysconfdir)/init.d/compatibleone
	rm -f $(DESTDIR)$(sysconfdir)/default/accords

accords: accords.in
accords: Makefile
	rm -f $@ $@.tmp
	srcdir=''; \
	  test -f ./$@.in || srcdir=$(srcdir)/; \
	  $(installedit) $${srcdir}$@.in >$@.tmp
	mv $@.tmp $@

co-check: co-check.in
co-check: Makefile
	rm -f $@ $@.tmp
	srcdir=''; \
	  test -f ./$@.in || srcdir=$(srcdir)/; \
	  $(installedit) $${srcdir}$@.in >$@.tmp
	mv $@.tmp $@
