<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/TeamInfo.inc');
$action=$_GET['action'];
$team_info=new TeamInfo();
if($action=='listAllTeam'){
	$json=$team_info->listAllTeam();
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'系统中不存在任何团队数据','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$json));
		exit;
	}
	//返回的json数组包括的内容有
	//team_id(团队编号),team_name(团队名称),team_rank(团队等级),team_slogan(团队口号)
	//team_logo(团队logo的路径),team_note(团队说明),member_num(成员数目),setup_time(成立时间),
	//first_leader_id(创始人编号),first_leader_name(创始人姓名),leader_id(现任团队领袖编号),leader_name(名称)
}
else if($action=='listPersonalAllTeam'){
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	$json=$team_info->listPersonalAllTeam($user_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'该用户未参加任何团队','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$json));
		exit;
	}
	//json中每个元素的格式同上
}
else if($action=='teamInfoDetail'){
	$team_id=$_POST['team_id'];
	$json=$team_info->detail($team_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网路连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'没有相关团队信息','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$json));
		exit;
	}
	//json数组内容同上上
}
else if($action=='modifyTeamInfo'){
	$team_id=$_POST['team_id'];
	$content=$_POST['content'];
	//content为一个json数组，里面包括可以修改的内容，其中有
	//team_name(团队名称),team_slogan(团队口号),team_note(团队说明)
	//头像上传另外接口
	$status=$team_info->modify($team_id,$content);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'修改失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'修改成功','result'=>'null'));
		exit;
	}
}
else if($action=='listTeamAllDoingTask'){//正在做的相关任务
	//task为简要信息
	//task_id(任务编号),owner_id(发布人编号),owner_name(发布人姓名),deadline(截止日期),
	//task_type(任务类型),state(任务状态),module(所属模块),module_type(所属模块中类型),
	//social_detail(社会任务中的细分),keyword(关键词),reward_note(奖励备注),reward_type(奖励类型),
	//goods_type(如果是物品，则物品是什么),reward_state(奖励状态),reward_number(奖励数量),task_title(标题)
	$team_id=$_POST['team_id'];
	$status=$team_info->listTeamDoingTask($team_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'团队没有执行中的相关任务','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$status));
		exit;
	}
}
else if($action=='listTeamAllTaskRecord'){//已经结束和正在做的相关任务
    //json数组同上
	$team_id=$_POST['team_id'];
	$status=$team_info->listTeamAllTaskRecord($team_id);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'该团队没有参与过任何任务的执行','result'=>$status));
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
