#!/bin/sh
cat <<__EOF__

About to update master image (hosted online) from local laptop

You will need to enter the local password for the robot user, when prompted
by sudo below - and then also the remote password for the master image, when
prompted by rsync.

__EOF__

sudo rsync -avxPz --delete \
	--exclude=lost+found/ \
	/boot/ \
	robot-update@robot01.ninja.org.uk::restore_master1_boot/  && \
sudo rsync -avxPz --delete \
	--exclude=lost+found/ \
	/ \
	robot-update@robot01.ninja.org.uk::restore_master1_/ \

if [ $? == 0 ]; then
	read -n -p "Successfully backed up. Press ENTER to close"
else
	read -n -p "Failed to back up due to one or more errors. Press ENTER to close, then please try again"
fi
