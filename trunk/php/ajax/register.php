<?php
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Check.inc');
require_once($root_path.'/businesslogic/Register.inc');
session_start();
$check=new Check();
$action=$_GET['action'];
if($action=='name'){
	$username=$_POST['username'];
	if(empty($username)){
		echo '用户名为空，未能正确输入';
	}
	$checkStatus=$check->checkNameValid($username);
	if($checkStatus==-1){
		echo '用户名存在非法字符或者违禁词汇';
	}
	else if($checkStatus==false){
		echo '系统中存在重复的用户名';
	}
	else{
		$_SESSION['username']=$username;
	}
}
else if($action=='password'){
	$password=$_POST['password'];
	$checkStatus=$check->checkPasswordValid($password);
	if($checkStatus==false){
		echo '密码过于简单';
	}
	else{
		$_SESSION['password']=$password;
	}
}
else if($action=='default_phone'){//这里的相关发送验证码的功能暂时还没加，目前是直接设置
	$defaultPhone=$_POST['default_phone'];
	$checkStatus=$check->checkDefaultPhoneValid($defaultPhone);
	if($checkStatus==-1){
		echo '手机号码格式存在问题';
	}
	else if($checkStatus==false){
		echo '该手机号已被占用';
	}
	else{
		$_SESSION['default_phone']=$defaultPhone;
	}
}
else if($action='default_email'){
	$defaultEmail=$_POST['default_email'];
	$checkStatus=$check->checkDefaultPhoneValid($defaultEmail);
	if($checkStatus==-1){
		echo '该邮箱格式存在问题';
	}
	else if($checkStatus==false){
		echo '该邮箱已被占用';
	}
	else{
		$_SESSION['default_email']=$defaultEmail;
	}
}
else if($action=='interest'){
	$interest=$_POST['interest'];//用一个json数组把所有的感兴趣领域名传过来
	$area=json_decode($interest);
	$count=count($area);
	if($count==0){
		$_SESSION['interest']='none';
	}
	else{
		$_SESSION['interest']=$interest;
	}
}
else if($action=='basic_info'){
	$basicInfo=$_POST['basic_info'];
	$checkStatus=$check->checkBasicInfo($basicInfo);
	if($checkStatus==-1){
		echo '基本信息填写不完整';
	}
	else if($checkStatus==false){
		echo '基本信息填写存在问题';
	}
	else{
		$_SESSION['basic_info']=$basicInfo;
	}
}
else if($action=='commit'){
	$register=new Register();
	$register->setName($_SESSION['username']);
	$register->setPassword($_SESSION['password']);
	$register->setDefaultEmail($_SESSION['default_email']);
	$register->setDefaultPhone($_SESSION['default_phone']);
	$register->setBasicInfo($_SESSION['basic_info']);
	$register->setInterestArea($_SESSION['interest']);
	$checkStatus=$register->commitRegisterInfo();
	if($checkStatus==-1){
		echo '网络存在问题，请检查你的设备';
	}
	else if($checkStatus==false){
		echo '注册失败';
	}
	else{
		unset($_SESSION);
		session_destroy();
		echo '注册成功，您的账号为'.$checkStatus;
	}
}	
?>