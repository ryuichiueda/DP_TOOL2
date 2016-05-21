#!/bin/bash 

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH
mkdir -p $dir/tmp/

cat $dir/values.0			|
value_iteration $dir/state_trans > $dir/tmp/values.1

cat $dir/tmp/values.1			|
value_iteration $dir/state_trans > $dir/tmp/values.2

cat $dir/tmp/values.2			|
value_iteration $dir/state_trans > $dir/tmp/values.3

cat $dir/tmp/values.3			|
value_iteration $dir/state_trans > $dir/tmp/values.4

cat $dir/tmp/values.4			|
value_iteration $dir/state_trans > $dir/tmp/values.5

cat $dir/tmp/values.5

rm -f $dir/tmp/*
