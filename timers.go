package main

import "C"
import "time"
import "fmt"

var nextTimerID = 0

//export SetTimeout
func SetTimeout(delay C.double) int {
	wg.Add(1)
	nextTimerID++
	id := nextTimerID
	go func () {
		time.Sleep(time.Millisecond * time.Duration(delay))
		fmt.Println("Timer test", id)
		wg.Done()
	} ()
	return id
}
