package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"github.com/astaxie/beego"
	"github.com/ilahsa/dg_service/message"
	//"message"
	. "net/http"
	"regexp"
	"strconv"
	"strings"
)

//获取讨论组内成员列表 需要转 int64
func GetMemberList(user_id string, dg_id string) []string {

	client := &Client{}
	url := Config_Data_URL //"http://10.1.9.102/fbddc/api/api.php"
	//拼接字符串 这样比较高效
	buf := bytes.Buffer{}
	buf.WriteString(`{"user_id":`)
	buf.WriteString(user_id)
	buf.WriteString(`,"dg_id":`)
	buf.WriteString(dg_id)
	buf.WriteString("}")

	json := buf.String()
	fmt.Println("web req is ", json)
	b := strings.NewReader(json)

	req, err := NewRequest("POST", url, b)
	req.Header.Add("Content-Type", "application/json")
	req.Header.Add("UU-REQUEST-MODULE", "discussion")
	req.Header.Add("UU-REQUEST-ACTION", "get_member_list")
	req.Header.Add("UU-AUTH-TYPE", "2")
	if err != nil {
		beego.Error("GetMemberList error", err)
		return nil
	}

	response, err := client.Do(req)
	if err != nil {
		beego.Error("GetMemberList error", err)
		return nil
	}
	beego.Info("web response is ", response)
	status := response.Header.Get("UU-Response-RC")
	if response.StatusCode == 200 && status == "0" {
		body, _ := ioutil.ReadAll(response.Body)
		bodystr := string(body)

		re := regexp.MustCompile("\"user_id\":\\w*\\s*\\d*\\b")
		user_ids := re.FindAllString(bodystr, -1)

		length := len(user_ids)

		if length > 0 {
			for i := 0; i < len(user_ids); i++ {
				user_ids[i] = user_ids[i][10:]
			}

		}
		return user_ids
	}

	return nil
}

func GetOnlineUserInfos2(user_id string, dg_id string) []message.OnlineUserinfo {

	memberIds := GetMemberList(user_id, dg_id)
	if memberIds == nil {
		return nil
	}

	user_ids := make([]int, len(memberIds))
	for k, v := range memberIds {
		v1, _ := strconv.ParseInt(v, 10, 64)
		user_ids[k] = int(v1)
	}
	onlineUserInfos := GetOnlineUserInfos(user_ids)
	return onlineUserInfos
}

///获取在线用户信息
func GetOnlineUserInfos(user_ids []int) []message.OnlineUserinfo {

	client := &Client{}
	url := Config_PRS_URL //"http://10.1.9.103:6577/prs_api/"
	json1, _ := json.Marshal(user_ids)

	beego.Info("web req is ", string(json1))
	b := strings.NewReader(string(json1))

	req, _ := NewRequest("POST", url, b)
	req.Header.Add("Content-Type", "application/json")
	req.Header.Add("UU-REQUEST-MODULE", "kernel")
	req.Header.Add("UU-REQUEST-ACTION", "get_onlineuserinfo")
	req.Header.Add("UU-AUTH-TYPE", "2")

	response, err := client.Do(req)

	if err != nil {
		beego.Info("GetOnlineUserInfos web respoonse error", err)
		return nil
	}
	beego.Info("web response is ", response)
	status := response.Header.Get("UU-Response-RC")

	if response.StatusCode == 200 && status == "0" {
		body, _ := ioutil.ReadAll(response.Body)

		type Result struct {
			RC      int
			Payroll []message.OnlineUserinfo
		}

		var msg Result
		//	str := `{"changes": [{"armid":3,"Index":5}, {"armid":3,"Index":6}]}`
		err := json.Unmarshal(body, &msg)

		if err != nil {
			fmt.Println("Can't decode json message", err)
			return nil
		}
		//fmt.Println("onlineuserinfos is ", msg)
		return msg.Payroll

	}

	return nil
}

///添加讨论组消息
func AddDGMessage(dg_msg message.DGMessage) int {
	client := &Client{}
	url := Config_Data_URL //"http://10.1.9.102/fbddc/api/api.php"

	json, _ := json.Marshal(dg_msg)
	beego.Info("web req is ", string(json))
	b := strings.NewReader(string(json))

	req, err := NewRequest("POST", url, b)
	req.Header.Add("Content-Type", "application/json")
	req.Header.Add("UU-REQUEST-MODULE", "messaging")
	req.Header.Add("UU-REQUEST-ACTION", "add_discussion_messages")
	req.Header.Add("UU-AUTH-TYPE", "2")
	if err != nil {
		//return nil
		fmt.Println(err)
	}

	response, err := client.Do(req)

	if err != nil {
		beego.Info("add_dgmsg error", err)
		return 500
	}
	beego.Info("web response is ", response)
	status := response.Header.Get("UU-Response-RC")
	if response.StatusCode == 200 && status == "0" {

		return 200
	}

	return 500
}
