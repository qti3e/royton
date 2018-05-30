<?

echo "Hello world!\n";

royton_recv(function($msg) {
  echo "R;" . $msg . "\n";
});

echo "Hello world!\n";

royton_send("Test from PHP");
