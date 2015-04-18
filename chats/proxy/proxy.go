package proxy

import (
	"github.com/ilahsa/chats/common"
	"github.com/ilahsa/chats/http"
	"strings"
	"time"
)

var (
	Filtter_Actions = []string{"/login", "/keepalive",
		"/transport", "/report", "/report_ipinfo", "/pair", "/leave", "/operation"}
)

func ProcessRequest(req *http.Http_Request, sessionInfo *Session_Info) (resp *http.Http_Response, otherInfo interface{}) {
	if !fillterReq(req.ACTION) {
		resp := &http.Http_Response{STATUSCODE: http.Status_NotAccept}
		return resp, nil
	}
	switch req.ACTION {
	case "/login":
		resp = login(req, sessionInfo)
	case "/keepalive":
		resp = keepalive(req, sessionInfo)
	case "/report_ipinfo":
		resp = report_ipinfo(req, sessionInfo)
	default:
		resp = &http.Http_Response{STATUSCODE: http.Status_NotAccept}
	}

	return resp, nil

}
func login(req *http.Http_Request, sessionInfo *Session_Info) (resp *http.Http_Response) {
	resp = &http.Http_Response{STATUSCODE: http.Status_OK}
	content := req.HEADER["Content"]
	strs1 := strings.Split(content, " ")
	var clientType, credential, cinfo string
	clientType = strings.Split(strs1[0], "=")[1]
	credential = strings.Split(strs1[1], "=")[1]
	_, _ = credential, cinfo

	if clientType == "c" {
		cinfo = strings.Split(strs1[2], "=")[1]
		tmp1 := common.VigenereDecrypt(credential)
		tmp2 := common.FromHexString(tmp1)
		tmp3 := common.Rc4Encrypt(tmp2, common.DefaultRC4Key)
		decryptCredential := string(tmp3)
		decryptCinfo := string(common.Rc4Encrypt(common.FromHexString(common.VigenereDecrypt(cinfo)), "1234567wet1234567890abce56adcseq"))
		common.ULogger.Info(decryptCinfo)
		if strings.Index(decryptCredential, "afsfeqrfqgqarfq234esadf123wasd#") < 0 {
			resp.STATUSCODE = http.Status_Failed

		} else {
			dataEx := `POST /ipinforeq HTTP/1.1
Resp:host=ipinfo.io
CallId:ipinforeq_e4641547-6e66-49a0-b23f-db2bf71d4584
Content-Length:96

R0VUIC8gSFRUUC8xLjENClVzZXItQWdlbnQ6Y3VybC83LjMyLjANCkhvc3Q6aXBpbmZvLmlvDQpBY2NlcHQ6Ki8qDQoNCg==`
			sessionInfo.Last_Active_Time = time.Now().Unix()
			sessionInfo.Data_Ex = dataEx

			sessionInfo.Login_Status = true
			sessionInfo.Client_Type = "c"
			cinfos := strings.Split(decryptCinfo, "|")
			if len(cinfos) == 3 {
				sessionInfo.os = cinfos[0]
				sessionInfo.language = cinfos[1]
				sessionInfo.clientversion = cinfos[2]
			}

		}
	} else if clientType == "r" {
		return resp
	} else {

	}

	common.ULogger.Info("sessioninfo\r\n %v", sessionInfo)

	return resp
}
func keepalive(req *http.Http_Request, sessionInfo *Session_Info) (resp *http.Http_Response) {
	resp = &http.Http_Response{STATUSCODE: http.Status_OK}
	sessionInfo.Last_Active_Time = time.Now().Unix()
	return resp
}

func report_ipinfo(req *http.Http_Request, sessionInfo *Session_Info) (resp *http.Http_Response) {
	resp = &http.Http_Response{STATUSCODE: http.Status_OK}
	sessionInfo.Last_Active_Time = time.Now().Unix()
	return resp
}

func fillterReq(action string) bool {

	result := false
	for _, v := range Filtter_Actions {
		if action == v {
			result = true
			break
		}
	}
	return result
}
