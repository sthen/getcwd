#!/bin/ksh

# .tmuxrc example:
#
# bind-key '"' run-shell -b "getcwd-splitw #{?pane_active,#{pane_pid},} -v"
# bind-key '%' run-shell -b "getcwd-splitw #{?pane_active,#{pane_pid},} -h"

error() {
	echo "$*" >&2 && exit 1
}

[ -z "${TMUX}" ] && error "tmux is not running"
[ -o $# -lt 1 ] && error "usage: ${0##*/} <pid>"

panel_cwd=`getcwd ${1}` || panel_cwd=`/bin/ps -o cwd= -p ${1}` || panel_cwd=.
shift

# if the current dir has since been removed, find the first existing parent
while [ ! -d "${panel_cwd}" ] ; do
	panel_cwd=`dirname "${panel_cwd}"`
done

exec /usr/bin/tmux split-window -c "${panel_cwd}" "$@"
