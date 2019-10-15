#!/bin/sh
diff=0
best=50
worst=0
limit=3
lower=-10
result=0
gen=0
iterations=100
loop=iterations
sum=0
set -e
set -o pipefail
while [[ $loop != "0" ]]
do
	./generator --big > file
	result="$( ./lem-in < file | grep L | wc -l )"
	gen=$( tail -2 file | grep '#' | cut -d":" -f2 )
	diff=$(( result - gen ))
	if [ $diff -gt $limit ]
		then
			cp file maps/"flowone_bad_diff"$diff
	elif [ $diff -lt $lower ]
		then
			cp file maps/"flowone_good_diff"$diff
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
printf "Average on $iterations iterations : "
echo "scale=1; $sum / $iterations" | bc
echo "best score : $best"
echo "worst score : $worst"
rm file
