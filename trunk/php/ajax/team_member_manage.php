<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/TeamMemberManage.inc');
$action=$_GET['action'];
$manage=new TeamMemberManage();
if($action=='getTeamAllMemberInfo'){
	$team_id=$_POST['team_id'];
	$status=$manage->getTeamAllMemberInfo($team_id);
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
	//返回的json数组包括的内容有:
	//user_id,user_name,person_note,icon_str,is_man,user_level,is_identified
}
else if($action=='getTeamMemberDetail'){
	$member_id=$_POST['member_id'];
	$status=$manage->getTeamMemberDetail($member_id);
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
	//返回的json数组的内容有
	//user_id,user_name,person_note,icon_str,is_man,birth_time,address,qq,phone,microblog,
	//email,score,user_level,honor,is_identified
}
else if($action=='inviteTeamMembers'){
	$user_id=$_POST['user_id'];
	$team_id=$_POST['team_id'];
	$member_id=$_POST['member_id'];//是一个数组的json形式
	$status=$manage->inviteTeamMembers($user_id,$team_id,$member_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'邀请失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'邀请成功','result'=>'null'));
		exit;
	}
}
else if($action=='deleteTeamMembers'){
	$team_id=$_POST['team_id'];
	$member_id=$_POST['member_id'];//是一个数组的json形式
	$status=$manage->deleteTeamMembers($team_id,$member_id);
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
else if($action=='addManagers'){
	$team_id=$_POST['team_id'];
	$member_id=$_POST['member_id'];
	$status=$manage->addManagers($team_id,$member_id);
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
else if($action=='deleteManagers'){
	$team_id=$_POST['team_id'];
	$member_id=$_POST['member_id'];//是一个数组的json形式
	$status=$manage->deleteManagers($team_id,$member_id);
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
else if($action=='changeLeader'){
	$team_id=$_POST['team_id'];
	$leader_id=$_POST['leader_id'];
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'转让失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'转让成功','result'=>'null'));
		exit;
	}
}
else{
	exit;
}
?>