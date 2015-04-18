package main

import (
	"flag"

	"github.com/funny/link"
	"github.com/ilahsa/chats/common"
	"github.com/ilahsa/chats/http"
	"github.com/ilahsa/chats/proxy"
)

var (
	benchmark  = flag.Bool("bench", false, "is for benchmark, will disable print")
	buffersize = flag.Int("buffer", 1024, "session read buffer size")
)

// This is an echo server demo work with the echo_client.
// usage:
//     go run echo_server/main.go
func main() {
	common.ULogger.Info("stat chat at ", 10010)

	//flag.Parse()

	link.DefaultConnBufferSize = *buffersize
	link.DefaultProtocol = http.HttpPacket

	server, err := link.Listen("tcp", "0.0.0.0:10010")
	if err != nil {
		panic(err)
	}
	//server.Protocol()
	common.ULogger.Info("server start:", server.Listener().Addr().String())

	server.Serve(func(session *link.Session) {

		common.ULogger.Info("client", session.Conn().RemoteAddr().String(), "in")
		SessionInfo := &proxy.Session_Info{}
		session.State = SessionInfo

		session.Process(func(msg *link.InBuffer) error {

			common.ULogger.Info("receive request ", session.Conn().RemoteAddr().String(), ":", string(msg.Data))

			req, _ := http.Parse(msg.Data)
			req_CallId, ok1 := req.HEADER["CallId"]
			resp, other := proxy.ProcessRequest(req,
				SessionInfo)

			_ = other
			_, ok2 := resp.HEADER["CallId"]
			// add callid
			if ok1 && !ok2 {
				resp.AddResponseHeader("CallId", req_CallId)
			}
			//str := "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n"

			common.ULogger.Info("send response ", session.Conn().RemoteAddr().String(), ":", string(resp.ToByte()))

			if SessionInfo.Data_Ex != "" {
				session.Send(link.Bytes(resp.ToByte()))
				return session.Send(link.String(SessionInfo.Data_Ex))
			} else {
				return session.Send(link.Bytes(resp.ToByte()))
			}
		})

		common.ULogger.Info("client", session.Conn().RemoteAddr().String(), "close")
	})
}
