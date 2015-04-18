package main

import (
	"fmt"
	"strings"
	"testing"

	"github.com/ilahsa/chats/common"
)

func Test_Vigenere(t *testing.T) {
	str := "afsfeqrfqgqarfq234esadf123wasd192168132168081192168132168081guid"
	str1 := common.VigenereEncript(str)
	fmt.Println(str1)
	str2 := common.VigenereDecrypt(str1)
	fmt.Println(str2)

	if str2 != str {
		t.Errorf("failed")
	}
}

func Test_RC4(t *testing.T) {
	str := "afsfeqrfqgqarfq234esadf123wasd#192.168.13216:8081;192.168.13.216:8081#guid"
	key := "12345678901234567890123456789012"
	tmp1 := common.Rc4Encrypt([]byte(str), key)
	tmp2 := common.ToHexString(tmp1)
	fmt.Println(tmp2)
	tmp3 := common.FromHexString(tmp2)
	tmp4 := common.Rc4Encrypt(tmp3, key)
	if str != string(tmp4) {
		t.Errorf("rc4 failed")
	}
}
func Test_StringHex(t *testing.T) {
	str := "helloworld"
	str1 := common.ToHexString([]byte(str))
	fmt.Println(str1)
	str2 := common.FromHexString(str1)
	fmt.Println(string(str2))
	if str != string(str2) {
		t.Errorf("stringhex failed")
	}
}

func Test_CLogin(t *testing.T) {
	credential := "AheIPJDjDa8kBBahAbchsKOhBlABbkOhsJezdHDyEBtiaiEjbycKBLPbDLsich2hBzOlcadjAhCb2zaKOBPlehdidyabcJ8ishckeh2LcAaLcKtjsKbAdKdIsKdhAzdLCJsIakdjsi8zAIByAKOjtaPa2J2AcJBJOIOLPkAjCaeB"
	tmp1 := common.VigenereDecrypt(credential)
	tmp2 := common.FromHexString(tmp1)
	tmp3 := common.Rc4Encrypt(tmp2, common.DefaultRC4Key)
	decryptCredential := string(tmp3)
	fmt.Println(decryptCredential)
	if strings.Index(decryptCredential, "afsfeqrfqgqarfq234esadf123wasd#") < 0 {
		fmt.Println("22222222222222")
		t.Errorf("clogin failed")
	}
	//fmt.Println("3333333333333")
}

func Test_DecsCinfo(t *testing.T) {
	cinfo := "OAdLAIAHtL8ztLPlCjdbBKBHeaPJaAcjabsieHtBDIbHtlBhCIAbCLeiCb"
	t1 := common.VigenereDecrypt(cinfo)
	t2 := common.FromHexString(t1)
	t3 := common.Rc4Encrypt(t2, "1234567wet1234567890abce56adcseq")
	decryptCinfo := string(t3)
	fmt.Println(decryptCinfo)
}
