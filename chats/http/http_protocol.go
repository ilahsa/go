package http

import (
	"bytes"
	"io"
	"strconv"
	"strings"

	"github.com/funny/link"
)

var (
	HttpPacket = newHttpProtocol()
)

// The packet spliting protocol like Erlang's {packet, N}.
// Each packet has a fix length packet header to present packet length.
type httpProtocol struct {
	header_data   []byte
	writePos      int
	MaxPacketSize int
}

func newHttpProtocol() *httpProtocol {
	protocol := &httpProtocol{
		header_data:   make([]byte, 1024),
		writePos:      0,
		MaxPacketSize: 1024,
	}

	return protocol
}

func (p *httpProtocol) New(v interface{}, _ link.ProtocolSide) (link.ProtocolState, error) {
	return p, nil
}

func (p *httpProtocol) PrepareOutBuffer(buffer *link.OutBuffer, size int) {
	buffer.Prepare(size)
	//buffer.Data = buffer.Data[:p.n]
}

func (p *httpProtocol) Write(writer io.Writer, packet *link.OutBuffer) error {
	if p.MaxPacketSize > 0 && len(packet.Data) > p.MaxPacketSize {
		return link.PacketTooLargeError
	}
	//fmt.Println("1111" + string(packet.Data))
	//p.encodeHead(packet.Data)
	if _, err := writer.Write(packet.Data); err != nil {
		return err
	}
	return nil
}

func (p *httpProtocol) Read(reader io.Reader, buffer *link.InBuffer) error {
	// head
	p.writePos = 0

	header_buf := make([]byte, 1)
	for {
		if p.writePos == p.MaxPacketSize {
			return link.PacketTooLargeError
		}

		if _, err := io.ReadFull(reader, header_buf); err != nil {
			return err
		}
		p.header_data[p.writePos] = header_buf[0]
		p.writePos++
		if header_buf[0] == '\n' && p.writePos > 4 && string(p.header_data[p.writePos-4:p.writePos]) == "\r\n\r\n" {
			break
		}
	}
	header_buf = p.header_data[:p.writePos]
	content_length := 0
	if !(string(header_buf[:3]) == "GET") {
		for _, m := range bytes.Split(header_buf, []byte("\r\n")) {
			if bytes.Index(m, []byte("HTTP/1.1")) > 0 || bytes.Index(m, []byte(":")) < 0 {
				continue
			}
			header_split := bytes.SplitN(m, []byte(":"), 2)
			//headerKey := strings.TrimSpace(string(header_split[0]))
			headerValue := strings.TrimSpace(string(header_split[1]))

			if string(header_split[0]) == "CONTENT-LENGTH" {
				content_length, _ = strconv.Atoi(string(headerValue))
			}
		}
	}

	body_buf := make([]byte, content_length)
	if _, err := io.ReadFull(reader, body_buf); err != nil {
		return err
	}

	buffer.Prepare(p.writePos + 1 + content_length)
	for i := 0; i < p.writePos; i++ {
		buffer.Data[i] = p.header_data[i]
	}
	for i := 0; i < content_length; i++ {
		buffer.Data[p.writePos+i] = body_buf[i]
	}

	return nil
}
