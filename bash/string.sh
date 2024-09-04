#!/bin/bash

BUFFETT="Life is like a snowball. The important thing is finding wet snow and a really long hill."
# write your code here
ISAY=$BUFFETT
CHANGE1=${ISAY[@]/snow/foot}
CHANGE2=${CHANGE1[@]// snow}
CHANGE3=${CHANGE3[@]/finding/getting}

CHANGE4=${CHANGE3%%w*}
echo $CHANGE4
# ISAY=
