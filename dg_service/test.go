// test
package main

import (
	"fmt"
)

const (
	a = iota
	b
)

//1. 创建一个基于for 的简单的循环。使其循环10 次，并且使用fmt 包打印出计数器的值。
func Test1() {
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println("sum is ", sum)

}

func Test2() {
	sum, i := 0, 0
T1:
	if i < 10 {
		sum += i
		i++
		goto T1
	}
	fmt.Println("sum is ", sum)

}
func Test3() {
	a := []int{0, 1, 22, 31, 4, 5}

	for k, v := range a {
		fmt.Println("index is ", k, "value is ", v)
	}
}

func Test2_1() {
	for i := 1; i <= 100; i++ {
		t := i
		if t%3 == 0 && t%5 == 0 {
			fmt.Println(t, "fizzbuzz")
		} else if t%3 == 0 {
			fmt.Println(t, "fizz")
		} else if t%5 == 0 {
			fmt.Println(t, "buzz")
		}

	}
}

func Test3_1() {
	for i := 1; i < 100; i++ {
		for j := 0; j < i; j++ {
			fmt.Print("A")
		}
		fmt.Print("\n")
	}
}

func Test3_4() {
	s := "foobar123"
	b := []rune(s)
	l := len(b)
	i := l / 2
	for j := 0; j < i; j++ {
		t := b[j]
		b[j] = b[l-1-j]
		b[l-1-j] = t
	}

	fmt.Println(string(b))
}

func Test5_1(rev []float64) (avg float64) {
	var sum float64 = 0.0
	switch len(rev) {
	case 0:
		avg = 0
	default:
		for _, v := range rev {
			sum += v
		}
		avg = sum / float64(len(rev))
	}
	return avg
}

func Test6_1(i, j int) (int, int) {
	if i > j {
		return j, i
	} else {
		return i, j
	}

}

func Test9_1(p ...int) {
	for _, i := range p {
		fmt.Println(i)
	}
}

func Test10_1(n int) (ret int) {
	if n == 1 || n == 2 {
		return 1
	}
	ret = Test10_1(n-1) + Test10_1(n-2)

	return
}

func Test11(b [3]int) {
	b[0] = 20
}
