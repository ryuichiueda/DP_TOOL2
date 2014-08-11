#!/bin/bash 

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH

cat $dir/values.0	|
value_iteration $dir/state_trans

