#!/bin/sh
if [ -z `which zenity` ]; then
	# Zenity is not installed - use text mode
	cat <<__EOF__

About to restore entire laptop from master image (hosted online)

This will remove any data on this machine.

__EOF__
	read -r -p "${1:-Are you sure? [y/N]} " response
	case $response in
	[yY])
		;;
	*)
		exit
		;;
	esac
else
	# Prompt graphically
	zenity --question 2>/dev/null
	if [ "$?" -ge "1" ]; then
		exit
	fi
fi

sudo RSYNC_PASSWORD=roboteer325 \
	rsync -avxPz --delete \
	--exclude=lost+found/ \
	robot-restore@robot01.ninja.org.uk::restore_master1_boot/ \
	/boot/ && \
sudo RSYNC_PASSWORD=roboteer325 \
	rsync -avxPz --delete \
	--exclude=lost+found/ \
	robot-restore@robot01.ninja.org.uk::restore_master1_/ \
	/
retval=$?

if [ $retval -eq 0 ]; then
        read -p "Successfully restored. Press ENTER to reboot" REPLY
	sudo shutdown -r now
else
        read -p "Failed to restore due to one or more errors. Press ENTER to close, then please try again" REPLY
fi

