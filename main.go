package main

/*
#cgo CFLAGS: -Iphp-src
#cgo CFLAGS: -Iphp-src/main
#cgo CFLAGS: -Iphp-src/Zend
#cgo CFLAGS: -Iphp-src/TSRM
#cgo LDFLAGS: php-src/libphp.a
#cgo LDFLAGS: -lcrypt -lresolv -lcrypt -lrt -lrt -lm -ldl -lnsl -lxml2
#cgo LDFLAGS: -lxml2 -lcrypt -lxml2 -lxml2 -lxml2 -lcrypt -lxml2
#include "binding.h"
*/
import "C"
import "fmt"
import "time"

func main() {
	fmt.Println("from Go")
	C.asyncphp_init()
	cs := C.CString("$a = 4; echo $a . \"\\n\";")
	wait := make(chan bool, 0)
	go func () {
		time.Sleep(time.Second * 2)
		code := C.CString("async_test();")
		C.asyncphp_eval(code)
		wait <- true
	} ()
	C.asyncphp_eval(cs)
	cs = C.CString("$a++; echo $a . \"\\n\";")
	C.asyncphp_eval(cs)
	<- wait
	fmt.Println("from Go")
}
