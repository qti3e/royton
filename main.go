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
	fmt.Println("from Go")
	C.royton_init()

	cs := C.CString("$a = 4; echo $a . \"\\n\";")
	C.royton_eval(cs)
	cs = C.CString("$a++; echo $a . \"\\n\";")
	C.royton_eval(cs)

	data, err := Asset("runtime.php")
	if err != nil {
		return;
	}
	// Skip first two characters (<?)
	cs = (*C.char)(unsafe.Pointer(&data[2]))
	C.royton_eval(cs)

	fmt.Println("from Go")

	wg.Wait()
}

func eval(code string) {
	cs := C.CString(code)
	C.royton_eval(cs)
}
