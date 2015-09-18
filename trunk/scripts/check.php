<?php

require("../php/businesslogic/Login.inc");

$name = $_GET['user_name'];
$code = $_GET['user_code'];


$loginInstance = new Login();
$result = $loginInstance->loginCheck($name, $code);
if ($result == false) {
	echo '<p>Error</p>';
}else {
	echo $result;
}

?>