package main

//参考书籍A Thorough Introduction to the Go Programming Language，IVO BALBAERT
import (
	"bytes"
	"fmt"
	"net"
	"strconv"
	"strings"
	"time"
	"github.com/ilahsa/dg_service/message"

	"github.com/astaxie/beego"
)

var (
	bufSize = 65535
	maxRead = 256
)

type SipServer struct {
	Par Parser
}

func (s *SipServer) InitServer(hostAndPort string) *net.TCPListener {
	serverAddr, err := net.ResolveTCPAddr("tcp", hostAndPort)
	s.CheckError(err, "Resolving address:port failed: '"+hostAndPort+"'")
	listener, err := net.ListenTCP("tcp", serverAddr)
	s.CheckError(err, "ListenTCP: ")
	beego.Info("Listening to: ", listener.Addr().String())
	return listener
}

func (s *SipServer) ConnectionHandler(conn net.Conn) {
	connFrom := conn.RemoteAddr().String()
	beego.Info("Connection from: ", connFrom)
	buf := bytes.NewBuffer(nil)

	for {

		var ibuf []byte = make([]byte, maxRead+1)
		length, err := conn.Read(ibuf[0:maxRead])
		ibuf[maxRead] = 0 // to prevent overflow
		switch err {
		case nil:
			{
				iibuf := ibuf[0:length]
				n, innerrErr := buf.Write(iibuf)
				fmt.Println(string(buf.Bytes()), n, innerrErr)
				reqs, left := s.Par.SipParse(buf.Bytes())
				buf.Reset()
				if left != nil && len(left) > 0 {
					buf.Write(left)
				}
				for _, v := range reqs {
					if v != nil {
						fmt.Println("req is .....", v)
						resp := &SIPResponse{}
						resp.STATUSCODE = "200"
						resp.HEADER = map[string]string{}
						resp.HEADER["CALL-ID"] = v.HEADER["CALL-ID"]
						resp.HEADER["CSEQ"] = v.HEADER["CSEQ"]
						if from, ok := v.HEADER["FROM"]; ok { // 判断 key 是否存在。
							resp.HEADER["FROM"] = from
						}

						s.talktoclients(conn, resp.ToByte())

						dealMessage(v)
					}

				}
			}
		default:
			goto DISCONNECT
		}
	}
DISCONNECT:
	err := conn.Close()
	beego.Info("Closed connection:", connFrom)
	s.CheckError(err, "Close:")
}

//处理讨论组消息
func dealMessage(req *SIPRequest) {
	//处理请求消息
	toHeader := req.HEADER["TO"]
	dgId := strings.SplitN(toHeader, "@", 2)[0][4:]

	fromHeader := req.HEADER["FROM"]
	fromId := strings.SplitN(fromHeader, "@", 2)[0][5:]

	newReq := &SIPRequest{}

	newReq.METHOD = "MESSAGE"
	newReq.HEADER = map[string]string{}
	for k, v := range req.HEADER {
		newReq.HEADER[k] = v
	}

	newReq.HEADER["FROM"] = toHeader
	newReq.HEADER["SOURCE"] = fromId
	if req.BODY != "" {
		newReq.BODY = req.BODY
		newReq.HEADER["CONTENT-LENGTH"] = strconv.Itoa(len(req.BODY))
	}

	onlineUserInfos := GetOnlineUserInfos2(fromId, dgId)

	if onlineUserInfos == nil {
		beego.Error("error", "onlineuserinfos is null,dg_id is "+dgId)
		return
	}

	ddd := message.UserEndPoint{UserId: 0}
	onlineUserIds, indx := make([]int, len(onlineUserInfos)), 0

	for _, v := range onlineUserInfos {
		//在线且不给本人发消息
		if v.UserEndPoint != ddd && strconv.Itoa(v.UserId) != fromId {
			newReq.DOMAIN = v.UserEndPoint.SapAddress
			toHeaderValue := "<sip:" + strconv.Itoa(v.UserId) + "@dg.uu.com>;epid=" + v.UserEndPoint.Epid

			newReq.HEADER["TO"] = toHeaderValue
			beego.Info("newreq is ", newReq)
			trfByte := newReq.ToByte()
			client := &SipClient{}
			//tcp:10.1.9.101:5068 截掉 tcp:
			client.SendMsg(v.UserEndPoint.SapAddress[4:], trfByte)

			//
			onlineUserIds[indx] = v.UserId
			indx++
		}
	}

	//发送者是在线用户
	onlineUserIds[indx], _ = strconv.Atoi(fromId)
	//存储离线消息
	msg := message.Message{}
	msg.Content = req.BODY
	msg.TypeN = req.HEADER["EVENT"]
	msg.Msg_id = req.HEADER["MESSAGE-ID"]
	msg.Sender_id, _ = strconv.Atoi(fromId)
	msg.Time = strconv.FormatInt(time.Now().Unix(), 10)
	dgMsg := message.DGMessage{}
	dgMsg.Dg_id, _ = strconv.Atoi(dgId)
	dgMsg.Online_users = onlineUserIds[0 : indx+1]
	dgMsg.Messages = make([]message.Message, 1)
	dgMsg.Messages[0] = msg

	AddDGMessage(dgMsg)
}
func (s *SipServer) talktoclients(to net.Conn, msg []byte) {
	wrote, err := to.Write(msg)

	s.CheckError(err, "Write: wrote "+string(wrote)+" bytes.")
}

func (s *SipServer) handleMsg(length int, err error, msg []byte) {
	if length > 0 {

		for i := 0; ; i++ {
			if msg[i] == 0 {
				break
			}
		}
	}

}

func (s *SipServer) CheckError(error error, info string) {
	if error != nil {
		panic("ERROR: " + info + " " + error.Error()) // terminate program
	}
}
