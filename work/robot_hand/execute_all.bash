#!/bin/bash -xv

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH

seq 0 149		|
awk '{for(i=0;i<=149;i++){print $1,i}}'		|
while read x y ; do
	./execute_multi.bash $x $y
done
