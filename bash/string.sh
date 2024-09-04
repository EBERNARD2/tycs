#!/bin/bash

BUFFETT="Life is like a snowball. The important thing is finding wet snow and a really long hill."
# write your code here
ISAY=$BUFFETT
echo "Before $ISAY"
CHANGE1=${ISAY[@]/snow/foot}
CHANGE2=${CHANGE1[@]// snow}
CHANGE3=${CHANGE2[@]//finding/getting}
ISAY=${CHANGE3%%w*}
echo "After $ISAY"

