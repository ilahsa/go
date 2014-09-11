package message

type DGMessage struct {
	Dg_id        int       `json:"dg_id"`
	Online_users []int     `json:"online_users"`
	Messages     []Message `json:"messages"`
}

type Message struct {
	Sender_id int    `json:"sender_id"`
	Msg_id    string `json:"msg_id"`
	Content   string `json:"content"`
	TypeN     string `json:"type"`
	Time      string `json:"time"`
}
