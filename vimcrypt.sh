#!/bin/bash
MYFILENAME=`echo $1 | sed 's:^.*/::' | sed 's/\..*$//'`
EXT=`echo $1 | sed 's:^.*/::' | sed 's/^.*\.//'`
TC=`cat ~/.config/.tapelast | sed 's/^.*://'`;let TC=$TC+1
#echo TC: $TC
crypt /dev/stdin $TC
##crypt $MYFILENAME.md $TC
sed -n '1p' $MYFILENAME.md.htmc | sed 's/:.*//' > ~/.config/.tapelast


#FILEEXT=$1
#FILE="${FILEEXT%%.*}"
#cat $1
#basename $PWD
