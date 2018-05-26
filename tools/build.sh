#!/bin/bash
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path/.."

sudo apt-get install \
  libxml2-dev \
  libcurl4-openssl-dev \
  libjpeg-dev \
  libpng-dev \
  libxpm-dev \
  libmysqlclient-dev \
  libpq-dev \
  libicu-dev \
  libfreetype6-dev \
  libldap2-dev \
  libxslt-dev
cd php-src
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
