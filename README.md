# Evented I/O for PHP [![Build Status](https://travis-ci.com/qti3e/async-php.svg?branch=master)](https://travis-ci.com/qti3e/royton)

Asynchronous PHP runtime.  
This project is still a **work in progress** : )

## Motivation and Goals
I think PHP must have something like this:
```php
<?php

setTimeout(function() {
  echo "Hello ";
}, 1000);

setTimeout(function() {
  echo "World";
}, 2000);
```

