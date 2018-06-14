GO_FILES = \
					 main.go \
					 binding.c \
					 binding.h \
					 assets.go \

royton: $(GO_FILES)
	go build -o royton

assets.go: index.php
	go-bindata -pkg main -o assets.go index.php

clean:
	-rm -f royton assets.go
