echo -----------------------------------------------------------
echo Tests pour le binome : $1
echo -----------------------------------------------------------

nTestCount=0
nSuccesfulTests=0
nStrResult="$1 "

echo ADD.1
let "nTestCount=$nTestCount+1"
./$1 < add.1.in > temp1.txt
grep -v '^#' temp1.txt > temp2.txt
diff -wB add.1.out temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo ADD.2
let "nTestCount=$nTestCount+1"
./$1 < add.2.in > temp1.txt
grep -v '^#' temp1.txt > temp2.txt
diff -wB add.2.out temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo DIVERS.3
let "nTestCount=$nTestCount+1"
./$1 < divers.3.in > temp1.txt
grep -v '^#' temp1.txt > temp2.txt
diff -wB divers.3.out temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo -----------------------------------------------------------
echo RESULTS
echo -----------------------------------------------------------
echo Results: $nSuccesfulTests/$nTestCount
echo CSVLine: $nStrResult
echo $nStrResult >> results.txt
