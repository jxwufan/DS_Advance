#!/bin/sh
while [ true ]
do
./gen 
echo ' regions'
./bit < test.in > bit.out
./naive < test.in > naive.out
if ! diff bit.out naive.out 
then
echo WA
break
fi
echo $((i=i+1)) TESTS OK
done
