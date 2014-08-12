#!/bin/bash
tmp=/tmp/$$

ERROR_CHECK(){
	[ "$(tr -d ' 0' <<< ${PIPESTATUS[@]} )" = "" ] && return
	echo "ERROR:" $1 >&2
	rm -f $tmp-*
	exit 1
}

#TEST1#####################################
# test with the simple_tile sample

../samples/simple_tile/execute.bash > $tmp-output

cat << FIN > $tmp-ans
0 4000
1 3000
2 2000
3 3000
4 2000
5 1000
6 2000
7 1000
8 0
FIN

diff $tmp-output $tmp-ans >&2 || ERROR_CHECK "TEST1"

echo "$0" OK >&2
rm -f $tmp-*
