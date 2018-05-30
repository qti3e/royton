<?

echo "Hello world!\n";

$id = 0;

royton_recv(function($msg) {
  echo "R;" . $msg . "\n";
  return "TEST TEST";
});

echo "Hello world!\n";

echo royton_send("Test from PHP") . "\n";
