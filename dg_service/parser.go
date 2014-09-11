// parser
package main

type Parser interface {
	SipParse(by []byte) ([]*SIPRequest, []byte)
}
