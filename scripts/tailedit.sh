#!/bin/bash
#Full script Name: MidnightCommmanderEdit last file or $1
#TODO: pokud soubor neexistuje, zalozime ho, ok, ale udelat H1; pokud soubor neexistuje vygenerovat nazev a soubor z $@
BROWSER='seamonkey'
MYEDITOR=''mcedit
OLDPATHSTRING='MD'
ROOTDIR="$HOME/WWW"
NEWPATHSTRING="$ROOTDIR/HTML"
CPATH=`pwd | sed 's:^.*'$OLDPATHSTRING'::'`
EXT=`echo $1| sed 's/^.*\.//'`

if [[ $EXT == "md" ]]; then 
    F=$1; shift; echo -e $@ >> $F; echo -e $F > .last
#echo -e $1 > .last; $MYED 
else
    if 
	[[ -f .last ]]; then  F=`cat .last`; 
    else 
	echo 'ROBOT: exiting (sorry, no filename given)' && exit;
    fi
fi
#chattr +a $F #change file attributes to append-only
SKIPLINES=`wc -l $F|sed 's/ .*//'` #count lines to 
let SKIPLINES=$SKIPLINES+1
echo -e $@ >> $F
$MYEDITOR $F:$SKIPLINES

#cp $F $F.tmp 
#$MYEDITOR $F.tmp:999999 
#cat $F.tmp >> $F
#rm $F.tmp

FF=`echo $F| sed 's:\.md::'` #FF - filenamewithout EXT .md
HTML="$NEWPATHSTRING$CPATH$FF.html"
TITLE=`head -n 1 $F|sed 's/#//'`
exit
#generating HTML
pandoc $F -o $FF.html;cat $FF.html > HTMLBODY
cp $ROOTDIR/tpl/tpl_default.html $HTML
sed -i "/CSSREPLACEME/r $ROOTDIR/tpl/css.css" $HTML; sed '/CSSREPLACEME/d' -i  $HTML
sed -i '/ARTICLEREPLACEME/r HTMLBODY'  $HTML; sed '/ARTICLEREPLACEME/d' -i  $HTML; rm HTMLBODY

sed "s/TITLEREPLACEME/$TITLE/" -i $HTML; 
echo HTML: $HTML

#su - f -c "$BROWSER $HTML 2>/dev/null &"
 
