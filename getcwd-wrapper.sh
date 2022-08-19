#!/bin/ksh

error() {
	echo "$*" >&2 && exit 1
}

[ -z "${TMUX}" ] && error "tmux is not running"
[ -o $# -lt 1 ] && error "usage: ${0##*/} <pid> <tmux command> [options]"

panel_cwd=`getcwd ${1}` || panel_cwd=`/bin/ps -o cwd= -p ${1}` || panel_cwd=.
shift

tmux_cmd=$1
shift

# if the current dir has since been removed, find the first existing parent
while [ ! -d "${panel_cwd}" ] ; do
	panel_cwd=`dirname "${panel_cwd}"`
done

exec /usr/bin/tmux $tmux_cmd -c "${panel_cwd}" "$@"
