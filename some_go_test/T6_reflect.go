package main

//反射的使用 可以参见 fmt.Println 的实现

//interface 相当于object
import (
	"fmt"
	"reflect"
)

func T6_test(a interface{}) {
	fmt.Println(a)

	kk := reflect.TypeOf(a).Kind()

	if kk == reflect.String {
		fmt.Println("string")
	}

	if kk == reflect.Int {

		fmt.Println("int")
	}
}
