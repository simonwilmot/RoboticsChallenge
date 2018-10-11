#!/bin/sh
cat <<__EOF__

About to restore entire laptop from master image (hosted online)

You will need to enter the local password for the robot user, when prompted
by sudo below.

__EOF__

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

