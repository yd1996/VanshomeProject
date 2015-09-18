<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Apply.inc');
$action=$_GET['action'];
$apply=new Apply();
if($action=='apply'){//初步申请
	$user_id=$_POST['user_id'];
	$task_id=$_POST['task_id'];
	$content=$_POST['content'];//content为一个json数组，里面包含内容有note(如果不填为'null'),apply_time
	if(empty($user_id)){
		echo 'error:login failure';
		exit;
	}
	if(empty($task_id)){
		echo 'error:the information of task has mistakes';
		exit;
	}
	$status=$apply->applyTask($user_id,$task_id,$content);
	if($status==-1){
		echo 'error:connection mistake';
		exit;
	}
	else if($status==false){
		echo 'error:fail to apply the task';
		exit;
	}
	else{
		echo 'success:succeed to apply the task';
		exit;
	}
}
else if($action=='giveup'){//申请后放弃（不论是否已经入围或者采纳）
	$user_id=$_POST['user_id'];
	$task_id=$_POST['task_id'];
	if(empty($user_id)){
		echo 'error:login failure';
		exit;
	}
	if(empty($task_id)){
		echo 'error:the information of task has mistakes';
		exit;
	}
	$status=$apply->apply($user_id,$task_id);
	if($status==-1){
		echo 'error:connection mistake';
		exit;
	}
	else if($status==false){
		echo 'fail to apply the task';
		exit;
	}
	else{
		echo 'succeed to apply the task';
		exit;
	}
}
else if($action=='submit'){//进入入围状态后提交详细的解决方案，传文件的以后另加接口，这里只有文字叙述
	$user_id=$_POST['user_id'];
	$task_id=$_POST['task_id'];
	$solution=$_POST['solution'];
	if(empty($user_id)){
		echo 'error:login failure';
		exit;
	}
	if(empty($task_id)){
		echo 'error:the information of task has mistakes';
		exit;
	}
	if(empty($solution)){
		echo 'error:the solution has not been filled right';
		exit;
	}
	$status=$apply->submit($user_id,$task_id,$solution);
	if($status==-1){
		echo 'connection error';
		exit;
	}
	else if($status==false){
		echo 'fail to submit the solution';
		exit;
	}
	else{
		echo 'succeed to submit the solution';
		exit;
	}
}
else if($action=='modify'){//入围后、采纳前对具体解决方案的修改，依旧不能在此处上传文件
    $user_id=$_POST['user_id'];
	$task_id=$_POST['task_id'];
	$solution=$_POST['solution'];
	if(empty($user_id)){
		echo 'error:login failure';
		exit;
	}
	if(empty($task_id)){
		echo 'error:the information of task has mistakes';
		exit;
	}
	if(empty($solution)){
		echo 'error:the solution has not been filled right';
		exit;
	}
	$status=$apply->modify($user_id,$task_id,$solution);
	if($status==-1){
		echo 'connection error';
		exit;
	}
	else if($status==false){
		echo 'fail to modify the solution';
		exit;
	}
	else{
		echo 'succeed to modify the solution';
		exit;
	}
}
else if($action=='list'){
	$user_id=$_POST['user_id'];
	$status=$apply->listAllApplication($user_id);
	if($status==-1){
		echo 'connection error';
		exit;
	}
	else if($status==false){
		echo 'fail to fetch the data';
		exit;
	}
	else{
		echo $status;
		exit;
	}
}
else{
	exit;
}
?>