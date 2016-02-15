#!/bin/bash
#
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
    read -r -p "${1:-Are you sure? [y/N]} " response
    case $response in
        [lL]) 
            true
            ;;
        *)
            false
            ;;
    esac
}


if  ! confirm "Warning do you want to download and replace your build ?" ; then
	exit
fi

(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed


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
	elif [ "$(expr substr $(uname -s) 1 19)" == "CYGWIN_NT-6.2-WOW64" ]; then
		ping_cmd="$SYSTEMROOT/system32/ping -n"
		#echo "Cygwin"
	else
			ping_cmd="$SYSTEMROOT/system32/ping -n"
	
	fi

	net_check_target="www.google.com"
	
	connected=`$ping_cmd 1 $net_check_target &> /dev/null && echo 1 || echo 0`

	if [ $connected == 0 ]; then
		echo "Not connected, cannot refresh"
		exit -1
	fi
	
	# Do a clone and deal with it 
	rm -rf RoboticsChallenge
	git clone $MASTER_LOCATION

else
	echo "This will be a local refresh - all sketches will be deleted"
fi



# Remove everything from the master location locally

echo "Removing all existing data... "
rm -rf sketches
rm -rf sketches.zip.*
rm -rf sketches.zip
rm -rf dhrobertson.com
rm -f refresh_remote.sh*
rm -f refresh_local.sh*
rm -rf Desktop/Re*.desktop


echo "Copying all folders to sketches"
mkdir sketches
find RoboticsChallenge   -maxdepth 1 -mindepth 1 -type d -exec cp -r {} sketches \;
rm -rf sketches/.git
rm -rf sketches/Demos
rm -rf sketches/Projects
rm -rf sketches/Testing

# Copy the latest script down to replace this one running
cp "RoboticsChallenge/BRC Refresh.desktop" ~/Desktop


echo "Fully Installed - restart Arduino or Processing to test"
echo "Upgrading brc.sh - this will only work next time you run"
cp RoboticsChallenge/brc.sh . 
chmod +x brc.sh
