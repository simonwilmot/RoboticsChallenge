#!/bin/sh
cat <<__EOF__

About to update master image (hosted online) from local laptop

You will need to enter the local password for the robot user, when prompted
by sudo below - and then also the remote password for the master image (twice),
when prompted by rsync.

__EOF__

# First of all, clean up our image
sudo apt-get clean

sudo rsync -avxPz --delete \
	--exclude=lost+found/ \
	/boot/ \
	robot-update@robot01.ninja.org.uk::backup_master1_boot/  && \
sudo rsync -avxPz --delete \
	--exclude=lost+found/ \
	--exclude=/tmp/ \
	/ \
	robot-update@robot01.ninja.org.uk::backup_master1_/
retval=$?

if [ $retval -eq 0 ]; then
	read -p "Successfully backed up. Press ENTER to close" REPLY
else
	read -p "Failed to back up due to one or more errors. Press ENTER to close, then please try again" REPLY
fi
