#!/bin/sh
diff=0
best=50
worst=0
limit=10
result=0
gen=0
loop=100
sum=0
set -e
set -o pipefail
while [[ $loop != "0" ]]
do
	./generator --big > file
	result="$( ./lem-in-alban < file | grep L | wc -l )"
	gen=$( tail -2 file | grep '#' | cut -d":" -f2 )
	diff=$(( result - gen ))
	if [ $diff -gt $limit ]
		then
			cp file maps/"perfalban"$diff
	fi
	if [ $diff -gt $worst ]
		then
			worst=$diff
	fi
	if [ $best -gt $diff ]
		then
			best=$diff
	fi
	echo "You have $diff more steps than expected."
	sum=$(( sum + diff ))
	loop=$(( loop - 1 ))
done
echo ""
printf "Average on 100 iterations : "
echo "scale=1; $sum / 100" | bc
echo "best score : $best"
echo "worst score : $worst"
rm file
