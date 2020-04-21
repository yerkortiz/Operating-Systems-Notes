package main

import "fmt"

var messages = []string{
	"The world itself's",
	"just one big hoax.",
	"Spamming each other with our",
	"running commentary of bullshit,",
	"masquerading as insight, our social media",
	"faking as intimacy.",
	"Or is it that we voted for this?",
	"Not with our rigged elections,",
	"but with our things, our property, our money.",
	"I'm not saying anything new.",
	"We all know why we do this,",
	"not because Hunger Games",
	"books make us happy,",
	"but because we wanna be sedated.",
	"Because it's painful not to pretend,",
	"because we're cowards.",
	"- Elliot Alderson",
	"Mr. Robot",
}

const consumerCount int = 3

func produce(jobs chan<- string) {
	for _, msg := range messages {
		jobs <- msg
	}
	close(jobs)
}

func consume(worker int, jobs <-chan string, done chan<- bool) {
	for msg := range jobs {
		fmt.Printf("Message %v is consumed by worker %v.\n", msg, worker)
	}
	done <- true
}

func main() {
	jobs := make(chan string)
	done := make(chan bool)

	go produce(jobs)

	for i := 1; i <= consumerCount; i++ {
		go consume(i, jobs, done)
	}
	<-done
}