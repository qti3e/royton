package main

/*
#cgo CFLAGS: -Iphp-src
#cgo CFLAGS: -Iphp-src/main
#cgo CFLAGS: -Iphp-src/Zend
#cgo CFLAGS: -Iphp-src/TSRM
#cgo LDFLAGS: php-src/main/libphp.a
#include "binding.h"
*/
import "C"
import "fmt";

func main() {
	fmt.Println("from Go")
	C.asyncphp_init()
	fmt.Println("from Go")
}

/*
// TODO write an script to auto generate libphp.a
// something like this might work
cd php-s
./configure \                                                                                     
	--prefix=/usr/local/php \
	--enable-mbstring \
	--with-openssl \
	--with-xmlrpc \
	--enable-soap \
	--enable-zip \
	--with-gd \
	--with-jpeg-dir \
	--with-png-dir \
	--with-mysql \
	--with-pgsql \
	--enable-embedded-mysqli \
	--with-freetype-dir \
	--enable-intl \
	--with-xsl
make
cd main
ar q libphp.a *.o
*/
