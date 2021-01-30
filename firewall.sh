#!/bin/bash

> tmp.txt
> print.txt
while read packet; do
	while read line; do
		line=`echo "$line" | tr -d ' ' | sed -e 's/#.*//'`
		if [[ "" != "$line" ]]; then
			readarray -d , -t rules <<< "$line"
			for i in "${rules[@]}"; do
				echo "$packet" | ./firewall.exe "$i" >> tmp.txt
			done
			counter=`cat tmp.txt | wc -l`
			if [[ counter -eq ${#rules[@]} ]]; then
				echo "$packet" >> print.txt
			fi
			> tmp.txt
		fi
	 done < "$1"
done

cat print.txt | sort | uniq | sed '/^$/d' | tr -d ' ' 
rm tmp.txt 
rm print.txt
