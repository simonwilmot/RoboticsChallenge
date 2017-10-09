#!/bin/bash
# Updated to v2 for new (slimmed down) repository
# This is the main start download script for the Barclays Robotics Challenge build
# Can be used on any Ubuntu based build - with Arduino and Processing already installed
# Processing must be configured to use sketchbook and Arduino to use sketches in /home/roboteer or
# the user thats been used to run the config
#

confirm () {
    # call with a prompt string or use a default
    read -r -p "${1:-Are you sure? [y/N]} " response
    case $response in
        [yY][eE][sS]|[yY]) 
            true
            ;;
        *)
            false
            ;;
    esac
}

confirmLocal () {
    # call with a prompt string or use a default

    if [ -z `which zenity` ]; then
        # zenity is not installed - fall back to text mode
        read -r -p "${1:-Are you sure? [y/N]} " response
        case $response in
            [lL]) 
                true
                ;;
            *)
                false
                ;;
        esac
    else
        # Prompt graphically
        response=`zenity --list --title "${1:-Local or Remote Refresh}" \
          --column="Type" --column="Description" \
          local "Does not need Internet connectivity" \
          remote "Pulls from online repository" \
          2>/dev/null `
        case $response in
            local) 
                true
                ;;
            remote)
                false
                ;;
            *)
                notify-send "Unknown response: '$response': exiting."
		exit -1
                ;;
        esac
    fi
}


(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed


# Make sure we are in the home directory of the robot user, before we start
cd ~

if  confirmLocal "Local or Remote refresh ?" ; then
	localRefresh=true
else
	localRefresh=false
fi

MASTER_LOCATION="https://github.com/simonwilmot/RoboticsChallenge.git"


if [ $localRefresh == false ]; then

	echo "You must be connected to the Internet to refresh the sketches folder"
	echo "Checking to see if you are...."

	command -v git >/dev/null 2>&1 || { sudo apt-get -y install git; }

	echo "Platform type: " $(uname)
	if [ "$(uname)" == "Darwin" ]; then
		echo "Mac"
	elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
		ping_cmd='ping -q -c'
		#echo "Linux"
	elif [ "$(expr substr $(uname -s) 1 13)" == "CYGWIN_NT-6.2" ]; then
		ping_cmd="$SYSTEMROOT/system32/ping -n"
		#echo "Cygwin"
	else
			ping_cmd="$SYSTEMROOT/system32/ping -n"
	
	fi

	net_check_target="github.com"
	
	connected=`$ping_cmd 1 $net_check_target &> /dev/null && echo 1 || echo 0`

	if [ $connected == 0 ]; then
		echo "Not connected, cannot refresh"
		exit -1
	else
		echo "Yes, you are connected. Refreshing..."
	fi
	
	# Remove all old files; do a brand new clone and deal with it 
	rm -rf RoboticsChallenge
	git clone $MASTER_LOCATION

else
	echo "This will be a local refresh - all sketches will be deleted"

	cd ~/RoboticsChallenge

	# Remove all files (apart from perhaps .git, and anything similar that
	# someone has been clever enough to create!)
	rm -rf *

	# Reset to latest GIT
	git reset --hard
fi

# Empty the trash, if there are any files here
rm -rf ~/.local/share/Trash/*

# Reset Arduino Preferences
cp -p ~/RoboticsChallenge/preferences.txt ~/.arduino15/

# Copy the latest script down to replace this one running
# (Could symlink it, but the symlink's icon is not aesthetically pleasing :) )
cp -p "~/RoboticsChallenge/BRC Refresh.desktop" ~/Desktop

notify-send "Robot Refresh" "Completed refresh"
