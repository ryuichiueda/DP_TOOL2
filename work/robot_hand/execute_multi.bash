#!/bin/bash -xv

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH
mkdir -p $dir/tmp/

$dir/calc_state_trans > $dir/state_trans

cat $dir/values.0			|
value_iteration -p 10 $dir/state_trans	> $dir/tmp/values.ans

while true ; do
	cat $dir/tmp/values.ans		|
	value_iteration -p 10 $dir/state_trans	> $dir/tmp/values.tmp

	diff $dir/tmp/values.{ans,tmp} > /dev/null && break
	mv $dir/tmp/values.tmp $dir/tmp/values.ans
done

cat $dir/tmp/values.ans

rm -f $dir/tmp/*
