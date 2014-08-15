#!/bin/bash -xv

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH
mkdir -p $dir/tmp/

rm $dir/policy

$dir/calc_state_trans > $dir/state_trans

cat $dir/values.0			|
value_iteration -p 150 $dir/state_trans	> $dir/tmp/values.ans

while [ ! -e $dir/policy ] ; do
	cat $dir/tmp/values.ans		|
	value_iteration -p 150 $dir/state_trans	> $dir/tmp/values.tmp
	mv $dir/tmp/values.tmp $dir/tmp/values.ans
done

mv $dir/tmp/values.ans $dir/values.ans

rm -f $dir/tmp/*
