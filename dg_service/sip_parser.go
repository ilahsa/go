// go_01 project main.go
package main

import (
	"bytes"
	"strconv"
	"strings"

	"github.com/astaxie/beego"
)

//const ddd = "abc"
const (
	BODY_SPLIT, HEADER_SPLIT, START_LINE_SPLIT, KEY_VALUE_SPLIT = "\r\n\r\n", "\r\n", " ", ":"
)

type SipParser struct {
}

///处理接手到的字节流, 不完整包 返回 写入 buf
func (parser *SipParser) SipParse(rev []byte) (reqs []*SIPRequest, left []byte) {

	reqs = make([]*SIPRequest, 1, 1)
	left = rev
	for {
		var req *SIPRequest
		req, left = parse(left)
		if req == nil {
			return reqs, left
		} else {
			reqs = append(reqs, req)
			beego.Info("receive sip request\r\n", req)
		}

	}

	return nil, nil
}

////解析出来一个 rquest
func parse(rev []byte) (*SIPRequest, []byte) {

	index := bytes.Index(rev, []byte(BODY_SPLIT))
	if index == -1 {
		return nil, rev
	}
	var method, domain string
	var content_length int
	sip_header := map[string]string{}
	header_info := rev[0:index]
	method = ""
	domain = ""
	for _, m := range bytes.Split(header_info, []byte(HEADER_SPLIT)) {
		//only care request
		if bytes.Index(m, []byte("SIP/2.0")) > 0 {
			start_line := bytes.Split(m, []byte(START_LINE_SPLIT))
			method = string(start_line[0])
			domain = string(start_line[1])
			continue
		}
		header_split := bytes.SplitN(m, []byte(KEY_VALUE_SPLIT), 2)
		headerKey := strings.TrimSpace(string(header_split[0]))
		headerValue := strings.TrimSpace(string(header_split[1]))

		if string(header_split[0]) == "CONTENT-LENGTH" {
			content_length, _ = strconv.Atoi(string(headerValue))
		} else {
			sip_header[string(headerKey)] = string(headerValue)
		}
	}

	//fmt.Println("c length is", content_length)
	if index+4+content_length <= len(rev) {
		body := string(rev[index+4 : index+4+content_length])

		return &SIPRequest{METHOD: method, DOMAIN: domain,
			CONTENT_LENGTH: content_length, HEADER: sip_header, BODY: body}, rev[index+4+content_length:]
	} else {

		return nil, rev
	}

}
