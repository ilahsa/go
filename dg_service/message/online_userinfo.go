package message

type UserEndPoint struct {
	UserId          int
	Epid            string
	SapAddress      string
	ProtocolVersion string
}

type OnlineUserinfo struct {
	UserId        int
	Nickname      string
	SigNature     string
	BasicPresence int
	UserEndPoint  UserEndPoint
}
