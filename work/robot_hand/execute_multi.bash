#!/bin/bash -xv

dir=$(dirname $0)
PATH=$dir/../../bin:$PATH
mkdir -p $dir/tmp/
mkdir -p $dir/ans/

OBJ_X=$1
OBJ_Y=$2

rm $dir/policy

$dir/calc_state_trans $OBJ_X $OBJ_Y > $dir/state_trans
[ "$(sed -n '/%%state transitions%%/,$p' $dir/state_trans | wc -l)" -eq 1 ] && exit 0
[ "$(cat $dir/values.0 | wc -l)" -eq 0 ] && exit 0

cat $dir/values.0			|
value_iteration -p 150 $dir/state_trans	> $dir/tmp/values.ans

while [ ! -e $dir/policy ] ; do
	cat $dir/tmp/values.ans		|
	value_iteration -p 150 $dir/state_trans	> $dir/tmp/values.tmp
	mv $dir/tmp/values.tmp $dir/tmp/values.ans
done

mv $dir/tmp/values.ans $dir/ans/values.${OBJ_X}.${OBJ_Y}.txt
mv $dir/policy $dir/ans/policy.${OBJ_X}.${OBJ_Y}.txt

rm -f $dir/tmp/*
