#!/bin/sh


# Auto-close dialog box after this many seconds
timeout=60

response=`zenity --question \
	--text="
<span size='x-large'>Refresh sketches and restore defaults?\n</span>
<b>This will remove any previously saved work.
Unless you select No below, your changes will be lost!</b>

Pressing ESC, or taking no action, will answer Yes.

This dialog will automatically close in <b>$timeout seconds</b>." \
	--timeout=$timeout \
	--ok-label="No" --cancel-label="Yes" \
	2>/dev/null `
returncode=$?
	case $returncode in
	# 0: OK; 1: Cancel; 5: Timeout
	[15]) 
		~/RoboticsChallenge/brc.sh local
		;;
	0)
		# Do not refresh
		;;
	*)
		notify-send "Unknown response: '$response': exiting."
		exit -1
		;;
	esac

# Launch Arduino IDE
~/arduino-current/arduino
