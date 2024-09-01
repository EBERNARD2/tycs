#!/bin/bash
function File {

    echo $#
}

# Do not change anything
if [ ! $# -lt 1 ]; then
    File $*
    exit 0
fi

# change here
# here you can pass the arguments
bash arguments.sh "Shell is fun"