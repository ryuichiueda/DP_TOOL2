#!/bin/bash

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH
mkdir -p $dir/tmp/

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
