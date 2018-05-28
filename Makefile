GO_FILES = \
					 main.go \
					 assets.go

royton: $(GO_FILES)
	go build -o royton

assets.go: runtime.php
	go-bindata -pkg main -o assets.go runtime.php

clean:
	-rm -f royton assets.go
