#!/bin/sh
avg=0
diff=0
result=0
gen=0
number=1
sum=0
​
set -e
set -o pipefail
while true
do
	./generator --big > file
	result="$( ./lem-in < file | grep L | wc -l )"
	gen=$( tail -2 file | grep '#' | cut -d":" -f2 )
	diff=$(( result - gen ))
	echo "diff = $diff"
	sum=$(( sum + diff ))
	printf "for $number of rounds, average =  "
	echo "scale=1; $sum / $number " | bc
	number=$(( number + 1 ))
done
