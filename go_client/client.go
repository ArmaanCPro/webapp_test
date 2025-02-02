package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
)

func main() {
	if len(os.Args) != 3 {
		fmt.Println("Usage: go_client <host> <port>")
		return
	}

	conn, err := net.Dial("tcp", os.Args[1]+":"+os.Args[2])
	if err != nil {
		fmt.Println("Error connecting:", err)
		return
	}
	defer conn.Close()

	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print("Enter message: ")
		message, _ := reader.ReadString('\n')

		if message == "exit\n" {
			break
		}

		fmt.Fprintf(conn, message)

		reply, _ := bufio.NewReader(conn).ReadString('\n')
		fmt.Print("Reply from server: " + reply)
	}
}
