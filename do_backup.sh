#!/bin/sh
sudo rsync -avxPz --delete --exclude=lost+found/ /boot/ robot-update@robot01.ninja.org.uk::backup_master1_boot/
sudo rsync -avxPz --delete --exclude=lost+found/ / robot-update@robot01.ninja.org.uk::backup_master1_/
