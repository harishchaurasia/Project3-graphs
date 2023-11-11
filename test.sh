#!/bin/bash
# Author: Alexander Ng (alexanderng@asu.edu)

TESTNUM=${1:-$(seq -f "%02g" 1 20)}
TESTDIR=./posted-test-cases
NETSDIR=$(realpath ./networks)
EXE=$(realpath ./PJ3)

pass=0

for n in $TESTNUM; do
    echo "Running test case $n..."
    pushd "$TESTDIR/$n" >/dev/null || exit
    TEMP=$(mktemp)
    CMD=$(sed -En "2s/^[^ ]+//p" ./Execution)
    IFS=" " read -r -a ARGS <<< "$CMD"
    ARGS[0]="$NETSDIR/${ARGS[0]}"
    "$EXE" < ./Instructions "${ARGS[@]}" >"$TEMP"

    res=$(delta --side-by-side --paging=never "$TEMP" ./Output.txt)
    if [ "$res" == "" ]; then
        ((pass+=1))
        echo "Your output is identical to the expected output."
    else
        echo "Your output is NOT identical to the expected output. Diff output:"
        echo "$res"
    fi

    echo
    rm "$TEMP"
    popd >/dev/null || exit

done

if [ $pass == 20 ]; then
    sym=✔️
else
    sym=❌
fi
echo "==================================="
echo "$sym Passed $pass/20 posted test cases"
echo "==================================="
