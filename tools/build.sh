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
./buildconf
./configure
make
ar q libphp.a **/*.o **/*.lo
popd
