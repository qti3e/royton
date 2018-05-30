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
	"unsafe"
	"sync"
)

var wg sync.WaitGroup

func main() {
	C.royton_init()

	data, err := Asset("runtime.php")

	if err != nil {
		return;
	}

	// Skip first two characters (<?)
	cs := (*C.char)(unsafe.Pointer(&data[2]))
	C.royton_eval(cs)
	cs = C.CString("XXX")
	C.royton_send(cs)

	wg.Wait()
}

//export royton_recvCb
func royton_recvCb(data unsafe.Pointer, size C.int) {
	gbuf := C.GoBytes(data, size)
	fmt.Println(string(gbuf))
}
