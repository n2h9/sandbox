package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	n := 10

	// create a buffered channel of n*2 objects
	// fill it with n values
	busyCh := make(chan any, n*2)
	{
		v := 1
		for i := 0; i < n; i++ {
			v = v << i
			busyCh <- v
		}
	}

	// create a close channel and close it after 8 seconds
	closeCh := make(chan struct{})
	go func() {
		<-time.After(8 * time.Second)
		close(closeCh)
	}()

	// run n goroutines
	var wg sync.WaitGroup
	wg.Add(n)
	for i := 0; i < n; i++ {
		go routine(i, busyCh, busyCh, closeCh, func() {
			wg.Add(-1)
		})
	}
	wg.Wait()

	close(busyCh)

	fmt.Println("all done")
}

func routine(i int, in <-chan any, out chan<- any, closeCh chan struct{}, deff func()) {
	defer deff()
	for {
		select {
		case v := <-in:
			fmt.Printf("inside go routine %d -- received value %v \n", i, v)
			out <- v
		case <-closeCh:
			fmt.Printf("inside go routine %d -- finished \n", i)
			return
		}
	}
}
