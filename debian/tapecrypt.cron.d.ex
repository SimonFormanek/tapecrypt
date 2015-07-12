#
# Regular cron jobs for the tapecrypt package
#
0 4	* * *	root	[ -x /usr/bin/tapecrypt_maintenance ] && /usr/bin/tapecrypt_maintenance
