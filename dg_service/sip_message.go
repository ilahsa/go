// sip_message
package main

import "bytes"

type SIPRequest struct {
	METHOD         string
	DOMAIN         string
	CONTENT_LENGTH int
	HEADER         map[string]string
	BODY           string
}

type SIPResponse struct {
	STATUSCODE     string
	HEADER         map[string]string
	BODY           string
	CONTENT_LENGTH int
}

func (resp *SIPRequest) ToByte() []byte {
	buf := bytes.Buffer{}

	buf.WriteString(resp.METHOD + " " + resp.DOMAIN + " SIP/2.0")
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

func (resp *SIPResponse) ToByte() []byte {
	buf := bytes.Buffer{}
	if resp.STATUSCODE == "200" {
		buf.WriteString("SIP/2.0 200 OK")
	} else {
		buf.WriteString("SIP/2.0 " + resp.STATUSCODE + " ERROR")
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
