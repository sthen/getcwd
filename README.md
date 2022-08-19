Simple tool to fetch the current working directory of a process using
sysctl(2) on OpenBSD. Like "ps -o cwd -p $pid" but doesn't strip at 40 chars.

A wrapper script is provided that can be used as follows:

bind-key '"' run-shell -b "getcwd-wrapper #{?pane_active,#{pane_pid},} split-window -v"
bind-key '%' run-shell -b "getcwd-wrapper #{?pane_active,#{pane_pid},} split-window -h"
bind-key 'C' run-shell -b "getcwd-wrapper #{?pane_active,#{pane_pid},} new-window"
