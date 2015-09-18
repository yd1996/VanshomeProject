<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/TaskInfo.inc');
$action=$_GET['action'];
$task_info=new TaskInfo();
if($action=='list_to_publish'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	    echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskToPublish($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_published'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskPublished($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_applying'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskApplying($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_accepted'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskAccept($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_refused'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskRefused($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_gaveup'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskGaveUp($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_finished'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskFinished($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_invited'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskInvited($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='list_attention'){
	$user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
	$result=$task_info->listAllTaskAttention($user_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不存在符合条件的任务','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='task_detail'){//需要加入相关查看权限检测的逻辑代码
    $user_id=$_POST['user_id'];
    if(empty($user_id)){
	   echo json_encode(array('success'=>0,'msg'=>'登录态存在问题','result'=>'null'));
    }
    $task_id=$_POST['task_id'];
	$result=$task_info->detail($task_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
	}
	else if($result==false){
		echo json_encode(array('success'=>1,'msg'=>'不具备查看任务详细信息的条件','result'=>'none'));
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$result));
	}
}
else if($action=='modify_task_info'){
	$task_id=$_POST['task_id'];
	$content=$_POST['content'];
	$result=$task_info->modify($task_id,$content);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($result==false){
		echo json_encode(array('success'=>0,'msg'=>'修改失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'修改成功','result'=>$result));
		exit;
	}
}
else if($action=='get_application_of_task'){
	$task_id=$_POST['task_id'];
	$result=$task_info->getApplicationOfTask($task_id);
	if($result==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($result==false){
		echo json_encode(array('success'=>0,'msg'=>'获取失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'获取成功','result'=>$result));
		exit;
	}
}
else{
	exit;
}
?>