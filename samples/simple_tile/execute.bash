#!/bin/bash 

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH

cat $dir/values.0			|
value_iteration $dir/state_trans > $dir/values.1

cat $dir/values.1			|
value_iteration $dir/state_trans > $dir/values.2

cat $dir/values.2			|
value_iteration $dir/state_trans > $dir/values.3

cat $dir/values.3			|
value_iteration $dir/state_trans > $dir/values.4

cat $dir/values.4			|
value_iteration $dir/state_trans > $dir/values.5

cat $dir/values.5
