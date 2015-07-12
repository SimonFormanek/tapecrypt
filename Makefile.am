AUTOMAKE_OPTIONS = foreign
SUBDIRS = src doc examples man scripts

deb:
	dpkg-buildpackage -uc -tc -rfakeroot
#	equivs-build -f tapecrypt.spec
