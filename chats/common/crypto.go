package common

import (
	"bytes"
	"fmt"
	"strconv"
	"strings"
)

const (
	orgDict       = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	dict0         = "AaBbCcDdEeFfGg06hHiIjJkKlLmMNn17opqrst28OPQRST39UVWXYZ45uvwxyz"
	dict1         = "hHiIjJkKlLmMNn17opqrst28UVWXYZ45uvwxyzAaBbCcDdEeFfGg06OPQRST39"
	DefaultRC4Key = "12345678901234567890123456789012"
)

func Rc4Encrypt(data []byte, pass string) []byte {
	output := make([]byte, len(data))
	i, j := 0, 0
	mbox := getKey([]byte(pass), 256)
	//加密
	for offset := 0; offset < len(data); offset++ {
		i = (i + 1) % len(mbox)
		j = (j + int(mbox[i])) % len(mbox)
		temp := mbox[i]
		mbox[i] = mbox[j]
		mbox[j] = temp
		a := data[offset]
		b := mbox[(int(mbox[i])+int(mbox[j]))%len(mbox)]
		output[offset] = byte(int(a) ^ int(b))
	}
	return output
}

func getKey(pass []byte, klen int) []byte {
	mbox := make([]byte, klen)
	var tmp1 uint8
	tmp1 = 0
	for i := 0; i < klen; i++ {
		mbox[i] = byte(tmp1)
		tmp1++
	}
	j := 0
	for i := 0; i < klen; i++ {
		j = (j + int(mbox[i]) + int(pass[i%len(pass)])) % klen
		temp := mbox[i]
		mbox[i] = mbox[j]
		mbox[j] = temp
	}
	return mbox
}

func VigenereEncript(text string) string {
	es := bytes.Buffer{}
	len := len(text)
	textChars := []byte(text)
	dictoChars := []byte(dict0)
	dict1Chars := []byte(dict1)
	for i := 0; i < len; i += 2 {
		c := dictoChars[strings.Index(orgDict, string(textChars[i]))]
		es.WriteString(string(c))

		next := i + 1
		if next < len {
			c = dict1Chars[strings.Index(orgDict, string(textChars[next]))]
			es.WriteString(string(c))
		}
	}
	return es.String()
}

func VigenereDecrypt(cipher string) string {
	es := bytes.Buffer{}
	len := len(cipher)
	cipherChars := []byte(cipher)
	orgChars := []byte(orgDict)
	//dictoChars := []byte(dict0)
	//dict1Chars := []byte(dict1)
	for i := 0; i < len; i += 2 {
		c := orgChars[strings.Index(dict0, string(cipherChars[i]))]
		es.WriteString(string(c))

		next := i + 1
		if next < len {
			c = orgChars[strings.Index(dict1, string(cipherChars[next]))]
			es.WriteString(string(c))
		}
	}
	return es.String()
}

func ToHexString(binary []byte) string {
	es := bytes.Buffer{}
	for _, b := range binary {
		tmp := int(b)
		if tmp > 15 {
			es.WriteString(fmt.Sprintf("%X", b))
		} else {
			//es.WriteString("0")
			es.WriteString(fmt.Sprintf("%02X", b))
		}
	}
	return es.String()
}

func FromHexString(hex string) []byte {
	if hex == "" || len(hex) < 1 {
		return nil
	}
	length := len(hex) / 2
	result := make([]byte, length)
	length *= 2

	for index := 0; index < length; index++ {
		s := hex[index : index+2]
		b, _ := strconv.ParseInt(s, 16, 0)
		result[index/2] = byte(b)
		index++
	}

	return result
}
