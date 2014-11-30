#!/bin/sh
while [ true ]
do
./gen 
./wang < test.in > yang.out
./me < test.in > wu.out
if ! diff yang.out wu.out
then
echo WA
break
fi
echo $((i=i+1)) TESTS OK
done
