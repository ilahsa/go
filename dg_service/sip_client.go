// sip_client
package main

import (
	"net"

	"github.com/astaxie/beego"
)

type SipClient struct {
}

func (client *SipClient) SendMsg(url string, msg []byte) {
	c, err := net.Dial("tcp", url)
	if err != nil {
		beego.Error("cann't connect "+url, err)
	}
	defer c.Close()

	c.Write(msg)

	beego.Info("client send message ", string(msg))
	buf := make([]byte, 1024)
	lenght, err := c.Read(buf)
	if err != nil {
		beego.Error("sip client receive error", err)
	}
	buf1 := buf[:lenght]
	beego.Info("sip client receive ", string(buf1))
}
