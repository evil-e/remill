#!/usr/bin/env bash
# Copyright 2016 Peter Goodman (peter@trailofbits.com), all rights reserved.

DIR=$(dirname $(dirname $( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )))

if [[ "${TRAVIS_OS_NAME}" = "linux" ]] ; then
    
    # Print out useful information to see what Linux environment is being used
    # by Travis.
    uname -a
    lsb_release -a

    sudo apt-get update -qq
    sudo apt-get --force-yes purge isc-dhcp-client
    sudo apt-get install -y isc-dhcp-client
    sudo apt-get upgrade -yqq
    
    $DIR/scripts/travis/install_linux.sh
fi 

if [[ "${TRAVIS_OS_NAME}" = "osx" ]] ; then 
    $DIR/travis/install_macos.sh
fi
