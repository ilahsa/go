// go_01 project main.go
package main

import "github.com/astaxie/beego"

import "github.com/astaxie/beego/config"

var (
	Config_Data_URL string
	Config_PRS_URL  string
)

func main() {
	////// 初始化日志
	beego.SetLogger("file", `{"filename":"go_dg.log"}`)
	iniconf, err := config.NewConfig("ini", "config.conf")
	if err != nil {
		beego.Error("init config error", err)
		beego.BeeLogger.Flush()
		return
	}
	Config_Data_URL = iniconf.String("data_url")
	Config_PRS_URL = iniconf.String("prs_url")

	//fmt.Println(Config_Data_URL, Config_PRS_URL)

	parser := &SipParser{}

	s := &SipServer{parser}

	hostAndPort := "0.0.0.0:54321"
	listener := s.InitServer(hostAndPort)

	for {
		conn, err := listener.Accept()
		s.CheckError(err, "Accept: ")
		go s.ConnectionHandler(conn)
	}

}
