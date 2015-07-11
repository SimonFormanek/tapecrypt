#!/bin/bash
SOURCE=alphabetsrc.txt
COUNT=`wc -l $SOURCE`
COUNT=`echo $COUNT | sed -s "s/$SOURCE//"`

sed = alphabetsrc.txt  | sed 'N;s/\n/:/' > anumlong.txt #opravit nazev a zkompilovat #todo


exit
cp alphabetsrc.txt tmp
sed = tmp  | sed 'N;s/\n/:/' > anumshort.txt
cat alphabetsrc.txt >> tmp
sed = tmp  | sed 'N;s/\n/:/' > anumlong.txt
rm tmp
