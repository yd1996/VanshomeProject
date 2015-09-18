<?php
header('Content-type: text/html; charset=utf8');
session_start();
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Login.inc');
$action=$_GET['action'];
$action='login';
if($action=='login'){
	$username=stripslashes($_POST['username']);
	$password=stripslashes($_POST['password']);
	if(empty($username)){//检测用户名是否为空
		echo '用户名不能为空';
		exit;
	}
	if(empty($password)){//检测密码是否填写
		echo '请正确输入密码';
		exit;
	} 
	$login=new Login();
	$checkResult=$login->loginCheck($username,$password);
	if($checkResult==-1){
		echo '网络连接存在问题，请检查连接情况';
	}
	else if($checkResult==false){
		echo '认证失败，用户名或者密码有误。';
	}
	else{
		$result=json_decode($checkResult, true);
		$_SESSION['user_id']=$result['user_id'];
		$_SESSION['user_name']=$result['user_name'];
		echo $checkResult;
		//json内容:user_id(用户账号),user_name(用户名),
		//user_level(用户等级),honor(荣誉称号),is_identified(认证情况，1为认证用户，0为非认证用户)
	}
} 
elseif ($action == 'logout') {  //退出 
    //unset($_SESSION); 
    session_destroy(); 
    echo '已经退出登录'; 
} 
?>