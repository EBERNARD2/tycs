a=(3 5 8 10 6)
b=(6 5 4 12)
c=(14 7 5 7) 

for x in ${a[@]} ; do 
  for j in ${b[@]} ; do
    for z in ${c[@]} ; do 
      if [[ $x = $j && $j = $z ]] ; then 
        echo $x
      fi
    done
  done
done