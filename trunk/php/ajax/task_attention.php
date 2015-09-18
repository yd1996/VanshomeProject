<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/TaskAttention.inc');
$action=$_GET['action'];
$task_attention=new TaskAttention();
$user_id=$_POST['user_id'];
$task_id=$_POST['task_id'];
if(empty($user_id)||empty($task_id)){
	echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
	exit;
}
if($action=='set_attention'){
	$status=$task_attention->add($user_id,$task_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'设置失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'设置成功','result'=>$status));
		exit;
	}
}
else if($action=='delete_attention'){
	$status=$task_attention->delete($user_id,$task_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'删除关注失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'删除关注成功','result'=>'null'));
		exit;
	}
}
else{
	exit;
}
?>