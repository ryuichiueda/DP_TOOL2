#!/bin/bash
tmp=/tmp/$$


ERROR_CHECK(){
	[ "$(tr -d ' 0' <<< ${PIPESTATUS[@]} )" = "" ] && return
	rm -f $tmp-*
	echo ERROR >&2
	exit 1
}

cd $(dirname $0) || echo "FATAL ERROR: Directory error" >&2
./simple_tile.bash  ; ERROR_CHECK

echo "$0" OK >&2
rm -f $tmp-*
