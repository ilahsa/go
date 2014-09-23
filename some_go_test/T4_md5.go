// T4_md5.go
package main

import "crypto/md5"
import "encoding/hex"

//go 生成 md5
func T4_1() {
	m := md5.New()
	m.Write([]byte("123456"))
	println(hex.EncodeToString(m.Sum(nil)))
}
