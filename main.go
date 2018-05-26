package main

/*
#cgo CFLAGS: -Iphp-src
#cgo CFLAGS: -Iphp-src/main
#cgo CFLAGS: -Iphp-src/Zend
#cgo CFLAGS: -Iphp-src/TSRM
#cgo LDFLAGS: php-src/main/libphp.a
#include "binding.h"
*/
import "C"
import "fmt"

func main() {
	fmt.Println("from Go")
	C.asyncphp_init()
	fmt.Println("from Go")
}
