// sip_message
package http

import (
	"bytes"
	"strconv"
	"strings"
)

const (
	BODY_SPLIT, HEADER_SPLIT, START_LINE_SPLIT, KEY_VALUE_SPLIT = "\r\n\r\n", "\r\n", " ", ":"
	Status_UnKnow                                               = "0"
	Status_OK                                                   = "200"
	Status_Accepted                                             = "202"
	Status_SeeOther                                             = "302"
	Status_BadRequest                                           = "400"
	Status_NotFound                                             = "404"
	Status_UnAuthorized                                         = "401"
	Status_NotAccept                                            = "406"
	Status_Failed                                               = "409"
	Status_ServerError                                          = "500"
	Status_NotImplemented                                       = "501"
)

type Http_Request struct {
	METHOD         string
	ACTION         string
	CONTENT_LENGTH int
	HEADER         map[string]string
	BODY           string
}

type Http_Response struct {
	STATUSCODE     string
	HEADER         map[string]string
	BODY           string
	CONTENT_LENGTH int
}

func (req *Http_Request) AddRequestHeader(k string, v string) {
	if req.HEADER == nil {
		req.HEADER = map[string]string{}
	}
	req.HEADER[k] = v
}

func (resp *Http_Request) ToByte() []byte {
	buf := bytes.Buffer{}

	buf.WriteString(resp.METHOD + " " + resp.ACTION + " HTTP/1.1")
	buf.WriteString("\r\n")
	for k, v := range resp.HEADER {
		buf.WriteString(k + ": " + v + "\r\n")
	}

	buf.WriteString("\r\n")

	if resp.BODY != "" {
		buf.WriteString(resp.BODY)
	}

	return buf.Bytes()
}

func (resp *Http_Response) AddResponseHeader(k string, v string) {
	if resp.HEADER == nil {
		resp.HEADER = map[string]string{}
	}
	resp.HEADER[k] = v
}

func (resp *Http_Response) ToByte() []byte {
	buf := bytes.Buffer{}
	if resp.STATUSCODE == "200" {
		buf.WriteString("HTTP/1.1 200 OK")
	} else {
		buf.WriteString("HTTP/1.1 " + resp.STATUSCODE + " ERROR")
	}
	buf.WriteString("\r\n")
	for k, v := range resp.HEADER {
		buf.WriteString(k + ": " + v + "\r\n")
	}

	buf.WriteString("\r\n")

	if resp.BODY != "" {
		buf.WriteString(resp.BODY)
	}

	return buf.Bytes()
}

////解析出来一个 rquest
func Parse(rev []byte) (*Http_Request, []byte) {

	index := bytes.Index(rev, []byte(BODY_SPLIT))
	if index == -1 {
		return nil, rev
	}
	var method, action string
	var content_length int
	sip_header := map[string]string{}
	header_info := rev[0:index]
	method = ""
	action = ""
	for _, m := range bytes.Split(header_info, []byte(HEADER_SPLIT)) {
		//only care request
		if bytes.Index(m, []byte("HTTP/1.1")) > 0 {
			start_line := bytes.Split(m, []byte(START_LINE_SPLIT))
			method = string(start_line[0])
			action = string(start_line[1])
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

		return &Http_Request{METHOD: method, ACTION: action,
			CONTENT_LENGTH: content_length, HEADER: sip_header, BODY: body}, rev[index+4+content_length:]
	} else {

		return nil, rev
	}

}
