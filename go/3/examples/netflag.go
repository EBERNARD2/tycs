package netflag


type Flags uint

const (
	FlagUp Flags = 1 << iota
	FlagBroadcast
	FlagLoopback
	FlagPointToPoint
	FlagMulticast
)

func IsUp( v Flags) bool { return v&FlagUp == FlagUp }
func TurnDown(v *Flags) { *v &^ = FlagUp }
func SetBroadCast(v *Flags) { *v |= FlagBroadcast }
func IsCast(v Flags) bool { return v&(FlagBroadcast|FlagMulticast) != 0 }
 