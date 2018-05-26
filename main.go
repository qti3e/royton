package main

/*
#cgo CFLAGS: -Iphp-src
#cgo CFLAGS: -Iphp-src/main
#cgo CFLAGS: -Iphp-src/Zend
#cgo CFLAGS: -Iphp-src/TSRM
#cgo LDFLAGS: php-src/libphp.a
#cgo LDFLAGS: -lcrypt -lresolv -lcrypt -lrt -lrt -lm -ldl -lnsl -lxml2 -lxml2 -lxml2 -lcrypt -lxml2 -lxml2 -lxml2 -lcrypt
#include "binding.h"
*/
import "C"
import "fmt"

func main() {
	fmt.Println("from Go")
	C.asyncphp_init()
	fmt.Println("from Go")
}
