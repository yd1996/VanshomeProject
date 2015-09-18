<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Relationship.inc');
$action=$_GET['action'];
$relationship=new Relationship();
if($action=='set_user_attention'){//添加对某个个人用户的普通关注
    $user_id=$_POST['user_id'];//用户编号
    $user_type=$_POST['user_type'];//用户类型，1代表个人用户，2代表团队用户，3代表需求商
	$goal_id=$_POST['goal_id'];//对方编号
	$goal_type=$_POST['goal_type'];//对方类型，同用户类型
	$is_special=$_POST['is_special'];//是否为特别关注，1表示是特别关注，0代表是普通关注
	if(empty($user_id)||empty($goal_id)){
		echo json_encode(array('success'=>0,'msg'=>'输入存在问题','result'=>'null'));
		exit;
	}
	$status=$relationship->addAttention($user_id,$user_type,$goal_id,$goal_type);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'添加失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'添加成功','result'=>'null'));
		exit;
	}
}
else if($action=='delete_user_attention'){//取消对某个个人用户的普通关注
    $user_id=$_POST['user_id'];
	$goal_id=$_POST['goal_id'];
	if(empty($user_id)||empty($goal_id)){
		echo json_encode(array('success'=>0,'msg'=>'输入存在问题','result'=>'null'));
		exit;
	}
	$status=$relationship->deleteAttention($user_id,$goal_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'删除失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'删除成功','result'=>'null'));
		exit;
	}
}
else if($action=='set_user_black'){
	$user_id=$_POST['user_id'];
	$goal_id=$_POST['goal_id'];
	$user_type=$_POST['user_type'];
	$goal_type=$_POST['goal_type'];
	if(empty($user_id)||empty($goal_id)){
		echo json_encode(array('success'=>0,'msg'=>'输入存在问题','result'=>'null'));
		exit;
	}
	$status=$relationship->addBlack($user_id,$user_type,$goal_id,$goal_type);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'输入存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'设置失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'设置成功','result'=>'null'));
		exit;
	}
}
else if($action=='delete_user_black'){
	$user_id=$_POST['user_id'];
	$goal_id=$_POST['goal_id'];
	if(empty($user_id)||empty($goal_id)){
		echo json_encode(array('success'=>0,'msg'=>'输入存在问题','result'=>'null'));
		exit;
	}
	$status=$relationship->deleteBlack($user_id,$goal_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'删除失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'删除成功','result'=>'null'));
		exit;
	}
}
else if($action=='list_attention'){
	//TODO:json格式待定
	$user_id=$_POST['user_id'];
	$goal_type=$_POST['goal_type'];
	$attention_level=$_POST['attention_level'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在异常','result'=>'null'));
		exit;
	}
	$status=$relationship->listAttention($user_id,$goal_type,$attention_level);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'对应关注列表为空','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else if($action=='list_black'){
	//TODO:json格式待定
	$user_id=$_POST['user_id'];
	$goal_type=$_POST['goal_type'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在异常','result'=>'null'));
		exit;
	}
	$status=$relationship->listBlack($user_id,$goal_type);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'对应黑名单列表为空','result'=>'null'));
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