// T2_map.go
package main

import "fmt"

func T2_1() {
	// 键值string , 值 int 类型
	m1 := map[string]int{}
	//添加一个元素
	m1["str1"] = 1
	fmt.Println(m1)
	//直接覆盖
	m1["str1"] = 2
	fmt.Println(m1)
	if v, ok := m1["str1"]; ok { // 判断 key 是否存在。
		fmt.Println(v)
	}
	fmt.Println(m1["c"]) // 对于不存在的 key，直接返回 \0，不会出错。
	delete(m1, "str1")   //删除元素

	fmt.Println(m1)

	//预先给 make 函数⼀一个合理元素数量参数，有助于提升性能。
	//因为事先申请⼀一⼤大块内存,可避免后续操作时频繁扩张。
	m2 := make(map[string]int, 1000)
	m2["str2"] = 200
	fmt.Println(m2)
	// len 返回实际存储的元素数目，cap 不起作用
	fmt.Println(len(m2))
}
