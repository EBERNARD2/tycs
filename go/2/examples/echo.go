package main

import (
	"flag"
	"fmt"
	"strings"
)

var n = flag.Bool("n", false, "omit trailing newline")
var sep = flag.String("s", " ", "seperator")

func main() {
	flag.Parse()
	fmt.Print(strings.Join(flag.Args(), *sep))
	if !*n {
		fmt.Println()
	}
}

// Summary: Divide players until there aren't any more matches to play. Give 1 player a bye if there is an odd number of players. 
function numberOfRounds(players) {
  let rounds = 0;
	let remainingPlayers = players;
  // while there are at least two players remaining
  while (remainingPlayers > 1) {
    // if the number of players is even split in half
    if (remainingPlayers % 2 === 0) {
      remainingPlayers = remainingPlayers / 2;
    } else {
      // else give one player a bye-round
      remainingPlayers = remainingPlayers - 1;

      // split the remaining players in half
      remainingPlayers = remainingPlayers / 2;

      // add the bye-round player back to the group
      remainingPlayers = remainingPlayers + 1;
    }
    // round is complete so add 1
    rounds = rounds + 1;
  } 
  
  // return number of rounds
  return rounds;
}