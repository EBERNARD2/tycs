if [ $# -lt 1 ]; then
  echo Usage: wiki {Wikipidea page name}
  exit 1
fi

DATA="$(curl -L https://en.wikipedia.org/wiki/$0)"
echo $DATA