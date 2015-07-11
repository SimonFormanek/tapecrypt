#!/bin/bash
#Full script Name: TailAppend
#TODO: pokud soubor neexistuje, zalozime ho, ok, ale udelat H1; pokud soubor neexistuje vygenerovat nazev a soubor z $@
OLDPATHSTRING='MD'
ROOTDIR="$HOME/WWW"
NEWPATHSTRING="$ROOTDIR/HTML"
CPATH=`pwd | sed 's:^.*'$OLDPATHSTRING'::'`
EXT=`echo $1| sed 's/^.*\.//'`

if [[ $EXT == "md" ]]; then 
    F=$1; shift; echo -e $@ >> $F; echo -e $F > .last
else
    if 
	[[ -f .last ]]; then  F=`cat .last`; 
    else 
	echo 'ROBOT: exiting (sorry, no filename given)' && exit;
    fi
    echo -e $@ >> $F
fi

tail $F #show output :)
exit
#HTML generating begin
FF=`echo $F| sed 's:\.md::'` #FF - filenamewithout EXT .md
HTML="$NEWPATHSTRING$CPATH$FF.html"
TITLE=`head -n 1 $F|sed 's/#//'`

#generating HTML
pandoc $F -o $FF.html;cat $FF.html > HTMLBODY
cp $ROOTDIR/tpl/tpl_default.html $HTML
sed -i "/CSSREPLACEME/r $ROOTDIR/tpl/css.css" $HTML; sed '/CSSREPLACEME/d' -i  $HTML
sed -i '/ARTICLEREPLACEME/r HTMLBODY'  $HTML; sed '/ARTICLEREPLACEME/d' -i  $HTML; rm HTMLBODY

sed "s/TITLEREPLACEME/$TITLE/" -i $HTML; 

seamonkey "$HTML" 2>/dev/null &
 
