<?php
include('dbconfig.php');

@mysql_connect("$DB_HOST:$DB_PORT","$DB_USER","$DB_PASSWORD") or die("mysql连接失败");

@mysql_select_db("$DB_NAME") or die("db连接失败");

mysql_query("set names 'utf-8'");//更为通用
?>