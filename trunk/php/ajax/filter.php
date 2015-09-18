<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Filter.inc');
$module_type=$_POST['module_type'];
if($module_type<0 || $module_type>12){//0全部 1作业帮助 2学习资料 3课外活动 4校园活动 5日常琐事 6课程辅导 7课程设计 8游戏代练 9海报设计 10情感专栏 11失物招领 12实时委托
	echo '系统错误';
	exit;
}
$task_type=$_POST['task_type'];//0全部 1单人悬赏 2多人悬赏
if($task_type<0 || $task_type>2){
	echo '系统错误';
	exit;
}
$task_state=$_POST['task_state'];//0全部 1悬赏中 2截止日期结束 3悬赏完成 4悬赏失败
if($task_state<0 || $task_state>4){
	echo '系统错误';
	exit;
}
$reward_type=$_POST['reward_type'];//0全部 1积分 2金钱 3物品 4其他
if($reward_type<0 || $reward_type>4){
	echo '系统错误';
	exit;
}
$reward_state=$_POST['reward_state'];//0全部 1已托管 2未托管
if($reward_state<0 || $reward_state>2){
	echo '系统错误';
	exit;
}
$sex=$_POST['sex'];//0全部 1男 2女
if($sex<0 || $sex>2){
	echo '系统错误';
	exit;
}
$match=$_POST['match'];//0全部 1同城 2同校 3同校同院
if($match<0 || $match>3){
	echo '系统错误';
	exit;
}
$filter=new Filter();
$data=$filter->retrieveAllTask();
$count=count($data);
if($count==0){
	echo '系统数据库没有相关数据';
}
else{
	$data=$filter->filterByModuleType($data,$module_type);
	//$data1=$filter->filterByTaskType($data,$task_type);
	//$data2=$filter->filterByTaskState($data1,$task_state);
	//$data3=$filter->filterByRewardType($data2,$reward_type);
	//$data4=$filter->filterByRewardState($data3,$reward_state);
	//$data5=$filter->filterBySex($data4,$sex);
	//$city=$_POST['city'];
	//$school=$_POST['school'];
	//$institute=$_POST['institute'];
	//if(empty($city)||empty($school)||empty($institute)){
		//echo '用户登录存在问题';//需要在登录时返回相关的城市，学校，学院
	//}
	//$data6=$filter->filterByMatchType($data5,$match,$city,$school,$institute);
	//if(count($data5)==0){
		//echo '不存在相关数据';
	//}
	//else{
		//echo json_encode($data5);
	//}
	echo json_encode($data);
}
?>