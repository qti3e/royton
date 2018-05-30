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
#include "timers.h"
*/
import "C"
import (
	"fmt"
	"unsafe"
	"sync"
	"time"
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

	wg.Wait()
}

//export SetTimeout
func SetTimeout(id C.int, delay C.double) {
	fmt.Println("Timer start", id)
	wg.Add(1)
	go func () {
		time.Sleep(time.Millisecond * time.Duration(delay))
		C.SetTimeoutCb(id)
		fmt.Println("Timer end", id)
		wg.Done()
	} ()
}
