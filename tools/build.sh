#!/bin/bash
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path/.."

cd php-src
./buildconf --force
./configure
make
ar q libphp.a $(find . -name "*.o" -or -name "*.lo")
