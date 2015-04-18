package proxy

type Session_Info struct {
	Login_Status     bool
	Client_Type      string
	Client_Id        string
	Data_Ex          string
	Last_Active_Time int64

	clientversion string
	os            string
	language      string
}
