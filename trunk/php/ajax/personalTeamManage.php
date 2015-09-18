<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Team.inc');
$action=$_GET['action'];
$user_id=$_POST['user_id'];
$team=new Team();
if(empty($user_id)){
	echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
	exit;
}
if($action=='listJoinApplication'){//列出参加团队的申请
    $status=$team->listJoinApplication($user_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'不存在相关申请','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
	//json格式team_id,team_name,apply_time,state(0未接受，1已经接受)
}
else if($action=='joinTeam'){//发出加入某一团队的申请
    $team_id=$_POST['team_id'];
	$reason=$_POST['reason'];
	$status=$team->joinTeam($user_id,$team_id,$reason);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'申请发送失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'申请发送成功','result'=>'null'));
		exit;
	}
}
else if($action=='leaveTeam'){//退出某个团队
    $team_id=$_POST['team_id'];
	$status=$team->leaveTeam($user_id,$team_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'身份原因，退出失败','result'=>'null'));//团队队长
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'退出成功','result'=>'null'));
		exit;
	}
}
else if($action=='acceptInvitation'){//接受某个团队的邀请
    $team_id=$_POST['team_id'];
	$status=$team->acceptInvitation($user_id,$team_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'接受邀请失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'接受邀请成功','result'=>'null'));
		exit;
	}
}
else if($action=='setTeam'){//建立新的团队
    $team_content=$_POST['team_content'];
	//json格式team_name(团队名称),team_rank(团队等级),team_slogan(团队口号),
	//team_logo(团队logo),team_note(团队说明),owner_id(用户编号),owner_name(用户姓名)
	$status=$team->setTeam($team_content);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'建立新团队失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'建立新团队成功','result'=>'null'));
		exit;
	}
}
else if($action=='dismissTeam'){//解散旧的团队
    $team_id=$_POST['team_id'];
	$status=$team->dismissTeam($user_id,$team_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'解散团队失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'解散团队成功','result'=>'null'));
		exit;
	}
}
else{
	exit;
}
?>