<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Accept.inc');
$action=$_GET['action'];
$accept=new Accept();
$task_id=$_POST['task_id'];
$user_id=$_POST['user_id'];//这个是申请人
$author_id=$_POST['author_id'];//发布人
if(empty($task_id)||empty($user_id)||empty($author_id)){
	echo 'error';
}
if($action=='accept'){
	$status=$accept->accept($task_id,$user_id);//这个$user_id是个数组
	if($status==-1){
		echo 'connection error';
	}
	else if($status==false){
		echo 'fail to accept';
	}
	else{
		echo 'succeed to accept';
	}
}
else if($action=='deny'){
	$status=$accept->deny($task_id,$user_id);//这个$user_id也是个数组
	if($status==-1){
		echo 'connection error';
	}
	else if($status==false){
		echo 'fail to deny';
	}
	else{
		echo 'succeed to deny';
	}
}
else if($action=='acceptFinally'){
	$status=$accept->acceptFinally($task_id,$user_id,$author_id);
	if($status==-1){
		echo 'connection error';
	}
	else if($status==false){
		echo 'fail to accept';
	}
	else{
		echo 'succeed to accept finally';
	}
}
else{
	echo '没有相关的服务';
	exit;
}
?>