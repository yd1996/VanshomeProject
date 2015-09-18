<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Account.inc');
$action=$_GET['action'];
$account=new Account();
$user_id=$_POST['user_id'];
if(empty($user_id)){
	echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
	exit;
}
if($action=='getTotalCondition'){
	//income payment total
	$status=$account->getTotalCondition($user_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'获取失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'获取成功','result'=>$status));
		exit;
	}
}
else if($action=='listAllItem'){
	//item包括内容item_id,item_time,task_id,task_type,task_small_type,
	//task_content,is_income,role,is_score,reward_content,reward_number,negotient_id,
	//negotient_name
	$status=$account->listAllItem($user_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'查询失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else if($action=='listAllIncomeItem'){
	$status=$account->listAllIncomeItem($user_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'查询失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else if($action=='listAllPaymentItem'){
	$status=$account->listAllPaymentItem($user_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'查询失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else if($action=='queryDetail'){
	$item_id=$_POST['item_id'];
	$status=$account->queryDetail($item_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'查询失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else{
	exit;
}
?>