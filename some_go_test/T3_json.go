// T3_json
package main

import (
	"encoding/json"
	"fmt"
)

//定义结构体
//首字母大写 ， json:"msg_id" 是 tag
type Message struct {
	MsgId   string `json:"msg_id"`
	Content string `json:"content"`
}

//json 序列号反序列化
func T3_1() {
	msg := Message{"msgid_001", "contente2222222222"}
	str, err := json.Marshal(msg)
	//输出 {"msg_id":"msgid_001","content":"contente2222222222"}
	fmt.Println(string(str), err)

	var msg1 Message
	//	str := `{"changes": [{"armid":3,"Index":5}, {"armid":3,"Index":6}]}`
	//反序列化为 stuct
	err = json.Unmarshal(str, &msg1)
	//输出 {msgid_001 contente2222222222}
	fmt.Println(msg1)
	//反序列化为map
	var msg2 map[string]string
	err = json.Unmarshal(str, &msg2)
	//输出 map[msg_id:msgid_001 content:contente2222222222]
	fmt.Println(msg2)
}
