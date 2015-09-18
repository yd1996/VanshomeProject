<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Message.inc');
$action=$_GET['action'];
$message=new Message();
if($action=='listAllMessage'){
	$user_id=$_POST['user_id'];
	$type=$_POST['type'];
	$status=$message->listAllMessage($user_id,$type);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'列表中没有消息','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else if($action=='detail'){
	$item_id=$_POST['item_id'];
	$status=$message->detail($item_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'消息不存在','result'=>'null'));
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