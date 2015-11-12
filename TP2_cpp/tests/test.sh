echo -----------------------------------------------------------
echo Tests pour le binome : $1
echo -----------------------------------------------------------
 # à executer depuis le dossier parent (avec 'make test' par exemple)

nTestCount=0
nSuccesfulTests=0
nStrResult="$1 "

echo ADD
let "nTestCount=$nTestCount+1"
./$1 < tests/test0.in > tests/temp1.txt
grep -v '^#' tests/temp1.txt > tests/temp2.txt
diff -wB tests/test0.ou tests/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo STATS_C
let "nTestCount=$nTestCount+1"
./$1 < tests/test1.in > tests/temp1.txt
grep -v '^#' tests/temp1.txt > tests/temp2.txt
diff -wB tests/test1.ou tests/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo STATS_D7
let "nTestCount=$nTestCount+1"
./$1 < tests/test2.in > tests/temp1.txt
grep -v '^#' tests/temp1.txt > tests/temp2.txt
diff -wB tests/test2.ou tests/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo JAM_DH
let "nTestCount=$nTestCount+1"
./$1 < tests/test3.in > tests/temp1.txt
grep -v '^#' tests/temp1.txt > tests/temp2.txt
diff -wB tests/test3.ou tests/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo OPT
let "nTestCount=$nTestCount+1"
./$1 < tests/test4.in > tests/temp1.txt
grep -v '^#' tests/temp1.txt > tests/temp2.txt
diff -wB tests/test4.ou tests/temp2.txt
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
echo $nStrResult >> tests/results.txt
