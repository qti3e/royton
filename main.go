package main

/*
#cgo CFLAGS: -Iphp-src
#cgo CFLAGS: -Iphp-src/main
#cgo CFLAGS: -Iphp-src/Zend
#cgo CFLAGS: -Iphp-src/TSRM
#cgo LDFLAGS: php-src/libphp.a
#cgo LDFLAGS: -lcrypt -lresolv -lcrypt -lrt -lrt -lm -ldl -lnsl -lxml2
#cgo LDFLAGS: -lxml2 -lcrypt -lxml2 -lxml2 -lxml2 -lcrypt -lxml2
#include <stdlib.h>
#include "binding.h"
*/
import "C"
import (
	"fmt"
	"sync"
	"unsafe"
)

func main() {
}

//export royton_recvCb
func royton_recvCb(data unsafe.Pointer, size C.int) *C.char {
}
