package main

import (
	php "github.com/deuill/go-php"
	"os"
	"fmt"
)


type testReceiver struct {
	Var    string
	hidden int64
}

func (t *testReceiver) Ignore() {
}

func (t *testReceiver) Hello(p string) string {
	return "Hello " + p
}

func (t *testReceiver) Goodbye(p string) (string, string) {
	return "Goodbye", p
}

func (t *testReceiver) invalid() string {
	return "I'm afraid I can't let you do that, Dave"
}

func newTestReceiver(args []interface{}) interface{} {
	value := "Foo"

	if len(args) > 0 {
		switch v := args[0].(type) {
		case bool:
			return nil
		case string:
			value = v
		}
	}

	return &testReceiver{Var: value, hidden: 42}
}


func main() {
	engine, _ := php.New()
 	engine.Define("TestReceiver", newTestReceiver)

	context, _ := engine.NewContext()
	context.Output = os.Stdout

	context.Eval("$t = new TestReceiver; echo isset($t->hidden) ? 1 : 0;")
	fmt.Println("____")
	// context.Exec("index.php")
	engine.Destroy()
}

