#! /bin/bash

> inputFile
ARGC=$#
MAX_ARGS=4
counter=0
arr[0]="YES"
arr[1]="NO"

declare -a temp_array
declare -a viruses
declare -a countries
declare -a uniqueIDs

if [[ $ARGC == $MAX_ARGS ]]; then	#check command line arguments
	if [[ $3 > 0 && $4 == 0 || $4 == 1 ]]; then	#check values of numbers given
		while IFS= read -r line; do 			#read virusesFile line by line
		    viruses[$counter]=$line;
		    let counter=counter+1;
		done < "$1"
		counter=0
		while IFS= read -r line; do 			#read countriesFile line by line
		    countries[$counter]=$line;
		    let counter=counter+1;
		done < "$2"
		for(( i=0; i<$3; i++ ))
		do
			if [[ $4 == 1 ]]; then	#if duplicatesAllowed
				temp_rand=$(($RANDOM % 4));
				temp_array[0]=$((1 + $RANDOM % 9999));
				echo -n ${temp_array[0]} >> inputFile; echo -n " " >> inputFile;		#citizenID
				tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)) >> inputFile; echo -n " " >> inputFile;		#firstName
				tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)) >> inputFile; echo -n " " >> inputFile;		#lastName
				echo ${countries[$RANDOM % ${#countries[@]} ]}| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#country
				echo -n $((1 + $RANDOM % 120)) >> inputFile; echo -n " " >> inputFile;		#age
				echo ${viruses[$RANDOM % ${#viruses[@]} ]}| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#virusName
				rand=$[ $RANDOM % 2 ];echo ${arr[$rand]}| tr -d '\n' >> inputFile;	#YES/NO
				if [[ $rand == 0 ]]; then				#if YES
					rand=$[ $RANDOM % 2 ];
					case $rand in
						"0")
							echo -n " " >> inputFile; echo -n $((1 + $RANDOM % 30)) >> inputFile; echo -n "-" >> inputFile; echo -n $((1 + $RANDOM % 12)) >> inputFile; echo -n "-" >> inputFile;echo $((1900 + $RANDOM % 120)) >> inputFile;;
						"1")
							printf "\n" >> inputFile;
					esac
				else
					printf "\n" >> inputFile;
				fi
				: '
				for(( j=0; j<$temp_rand; j++ ))		#print duplicate records in some cases
				do
					echo -n ${temp_array[0]} >> inputFile; echo -n " " >> inputFile;		#citizenID
					echo -n ${temp_array[1]} >> inputFile; echo -n " " >> inputFile;		#firstName
					echo -n ${temp_array[2]} >> inputFile; echo -n " " >> inputFile;		#lastName
					echo -n ${temp_array[3]} >> inputFile; echo -n " " >> inputFile;		#country
					echo -n ${temp_array[4]} >> inputFile; echo -n " " >> inputFile;		#age
					echo ${viruses[$RANDOM % ${#viruses[@]} ]}| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#virusName
					rand=$[ $RANDOM % 2 ];echo ${arr[$rand]}| tr -d '\n' >> inputFile;	#YES/NO
					if [[ $rand == 0 ]]; then				#if YES
						rand=$[ $RANDOM % 2 ];
						case $rand in
							"0")
								echo -n " " >> inputFile; echo -n $((1 + $RANDOM % 30)) >> inputFile; echo -n "-" >> inputFile; echo -n $((1 + $RANDOM % 12)) >> inputFile; echo -n "-" >> inputFile;echo $((1900 + $RANDOM % 120)) >> inputFile;;
							"1")
								printf "\n" >> inputFile;
						esac
					else
						printf "\n" >> inputFile;
					fi
				done'
			else		#duplicates not allowed
				temp_array[0]=$((1 + $RANDOM % 9999));
				while [[ " ${uniqueIDs[@]} " =~ " ${temp_array[0]} " ]]; do 	#check if array contains value
				    temp_array[0]=$((1 + $RANDOM % 9999));
				done
				uniqueIDs+=(" ${temp_array[0]} ")
				echo -n ${temp_array[0]} >> inputFile; echo -n " " >> inputFile;		#citizenID
				tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)) >> inputFile; echo -n " " >> inputFile;		#firstName
				tr -dc A-Za-z </dev/urandom | head -c $((3 + $RANDOM % 10)) >> inputFile; echo -n " " >> inputFile;		#lastName
				echo ${countries[$RANDOM % ${#countries[@]} ]}| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#country
				echo -n $((1 + $RANDOM % 120)) >> inputFile; echo -n " " >> inputFile;		#age
				echo ${viruses[$RANDOM % ${#viruses[@]} ]}| tr -d '\n' >> inputFile; echo -n " " >> inputFile;		#virusName
				rand=$[ $RANDOM % 2 ];echo ${arr[$rand]}| tr -d '\n' >> inputFile;	#YES/NO
				if [[ $rand == 0 ]]; then				#if YES
					rand=$[ $RANDOM % 2 ];
					case $rand in
						"0")
							echo -n " " >> inputFile; echo -n $((1 + $RANDOM % 30)) >> inputFile; echo -n "-" >> inputFile; echo -n $((1 + $RANDOM % 12)) >> inputFile; echo -n "-" >> inputFile;echo $((1900 + $RANDOM % 120)) >> inputFile;;
						"1")
							printf "\n" >> inputFile;
					esac
				else
					printf "\n" >> inputFile;
				fi
			fi
		done
	else
		printf "Wrong values!!!\n";
	fi
else
	printf "Wrong arguments!!!\n";
fi

