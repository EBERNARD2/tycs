function ENGLISH_CALC {
  echo $(($1 + $3))
  SIGN=$2
  VAL=0
  if [ $SIGN = "plus" ] ; then 
    SIGN="+"
    VAL=$(($1 + $3))
  elif [ $SIGN = "times" ] ; then 
    SIGN="*"
    VAL=$(($1 * $3))
  elif [ $SIGN = "minus" ] ; then 
    SIGN="-"
    VAL=$(($1 - $3))
  elif [ $SIGN = "divided by" ] ; then
    SIGN="/"
    VAL=$(($1 / $3))
  fi

  echo "$1$SIGN$3=$VAL"
}



ENGLISH_CALC 3 plus 5
ENGLISH_CALC 4 times 6
ENGLISH_CALC 10 minus 2