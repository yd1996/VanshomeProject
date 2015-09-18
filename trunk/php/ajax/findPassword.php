<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/FindPassword.inc');
$action=$_GET['action'];
$tool=new FindPassword();
$loginstr=$_POST['loginstr'];
if($action=='findPasswordByDefaultPhone'){
	$status=$tool->findPasswordByDefaultPhone($loginstr);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'找回密码失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>0,'msg'=>'找回密码成功','result'=>'null'));
		exit;
	}
}
else if($action=='findPasswordByDefaultEmail'){
	$status=$tool->findPasswordByDefaultEmail($loginstr);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'找回密码失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>0,'msg'=>'找回密码成功','result'=>'null'));
		exit;
	}
}
else if($action=='modifyPassword'){
	$checkCode=$_POST['check_code'];
	$password=$_POST['password'];
	$status=$tool->modifyPassword($loginstr);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'修改密码失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>0,'msg'=>'修改密码成功','result'=>'null'));
		exit;
	}
}
else{
	exit;
}
?>