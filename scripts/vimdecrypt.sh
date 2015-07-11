#!/bin/bash
MYFILENAME=`echo $1 | sed 's:^.*/::' | sed 's/\..*$//'`.md
EXT=`echo $1 | sed 's:^.*/::' | sed 's/^.*\.//'`

#FILEEXT=$1
#FILE="${FILEEXT%%.*}"
#decrypt $MYFILENAME
decrypt $MYFILENAME
#cat $1
