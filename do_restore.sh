#!/bin/sh
sudo RSYNC_PASSWORD=roboteer325 rsync -avxPz --delete --exclude=lost+found/ robot-restore@robot01.ninja.org.uk::restore_master1_boot/ /
sudo RSYNC_PASSWORD=roboteer325 rsync -avxPz --delete --exclude=lost+found/ robot-restore@robot01.ninja.org.uk::restore_master1_/ /
