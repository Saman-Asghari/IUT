#!/bin/bash

number=$(( RANDOM % 30 +1 ))
prefix=$2
if [ -e $1 ]; then
	echo the directory exists!!
else
	mkdir $1
	echo directory has created!!!
fi

for(( integer=1 ; integer<number ; integer++ )); do
	touch "$1/$prefix$integer.txt"
	echo file "$1/$prefix$integer.txt created at $1"
done


for(( x=2 ; x<=$# ; x++ )); do
	if [ -e $1/$prefix${!x}.txt ]; then
		rm -f $1/$prefix${!x}.txt
		echo "$1/$prefix${!x}.txt removed!"
	fi
done
