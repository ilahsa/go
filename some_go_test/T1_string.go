// test_string
package main

import (
	"fmt"
)

//翻转字符串

func T1_1() {

	str := "你好helloworld!"
	fmt.Println("翻转前", str)
	var ret string
	for _, v := range str { //_ 占位使用
		ret = string(v) + ret
	}
	fmt.Println("翻转后", ret)
}

func T1_2() {
	str := "你好!go"
	fmt.Println("翻转前", str)
	tmp := []rune(str)
	strLen := len(tmp)
	ret := make([]rune, strLen)

	for i := 0; i < strLen; i++ {
		ret[i] = tmp[strLen-i-1]
	}
	fmt.Println("翻转后", string(ret))
}

func T1_3() {
	str := "你好!go"
	fmt.Println("翻转前", str)
	tmp := []rune(str)
	var ret string
	for i, j := 0, len(tmp)-1; i < j; i, j = i+1, j-1 {
		tmp[i], tmp[j] = tmp[j], tmp[i]
	}
	ret = string(tmp)
	fmt.Println("翻转后", ret)
}
