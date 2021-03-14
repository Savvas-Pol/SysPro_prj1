#! /bin/bash

for(( i=0; i<$3; i++ ))
do
	echo -n $((1 + $RANDOM % 9999)); echo -n " "
	tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)); echo -n " "
	tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)); echo -n " "
	shuf -n 1 $2| tr -d '\n'; echo -n " "
	echo -n $((1 + $RANDOM % 120)); echo -n " "
	shuf -n 1 $1;
done