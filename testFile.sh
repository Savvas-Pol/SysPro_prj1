#! /bin/bash

> inputFile
arr[0]="YES"
arr[1]="NO"
for(( i=0; i<$3; i++ ))
do
	echo -n $((1 + $RANDOM % 9999)) >> inputFile; echo -n " " >> inputFile;		#citizenID
	tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)) >> inputFile; echo -n " " >> inputFile;	#firstName
	tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)) >> inputFile; echo -n " " >> inputFile;	#lastName
	shuf -n 1 $2| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#country
	echo -n $((1 + $RANDOM % 120)) >> inputFile; echo -n " " >> inputFile;		#age
	shuf -n 1 $1| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#virusName
	rand=$[ $RANDOM % 2 ];echo ${arr[$rand]}| tr -d '\n' >> inputFile;	#YES/NO
	rand=$[ $RANDOM % 2 ];
	case $rand in
		"0")
			echo -n " " >> inputFile; echo -n $((1 + $RANDOM % 30)) >> inputFile; echo -n "-" >> inputFile; echo -n $((1 + $RANDOM % 12)) >> inputFile; echo -n "-" >> inputFile;echo $((1900 + $RANDOM % 120)) >> inputFile;;
		"1")
			printf "\n" >> inputFile;
	esac
done