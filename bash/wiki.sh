if [ $# -lt 1 ]; then
  echo Usage: wiki {Wikipidea page name}
  exit 1
fi

DATA="$(curl -L -s https://en.wikipedia.org/wiki/$1)"
 
# IFS="<ul class="vector-toc-contents

#read -ra newarr <<< "$DATA"

delimiter="<ul class="vector-toc-contents""

echo ${#DATA}
 
 


