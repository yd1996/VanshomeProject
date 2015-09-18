<?php
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/Publish.inc');
$action=$_GET['action'];
$publish=new Publish();
if($action=='save'){
	$json=$_POST['task_basic_info'];
	$basic_info=json_decode();
	$user_id=$basic_info['owner_id'];
	//传输未发布需要保存的任务的相关信息
	//内容包括owner_id(发布人ID),owner_name(发布人姓名),deadline(截止日期的字符串，格式为YYYY-MM-DD HH:MM:SS)
	//task_type(任务类型),state(任务状态),description(任务描述),module(模块)，module(模块内分类),
	//social_detail(社会任务细分),keyword(关键词的json字符串),college(发布人所在大学),institute(发布人所在学院)
	//is_man(是否为男性,1表示是，0表示否),reward_type(奖励类型)，goods_type(奖励物品，如果不是物品为'null')
	//reward_note(奖励说明，如果没有填则为'null'),reward_number(奖励数量),reward_state(奖励状态),
	//task_title(任务标题)
	$status=$publish->save($user_id,$json);
	if($status==-1){
		echo '网络连接存在问题，请检查你的设备';
	}
	else if($status==false){
		echo '保存失败';
	}
	else{
		echo $status;//输出的是系统自动生成的任务编号
	}
}
else if($action=='publishBuffer'){
	$task_id=$_POST['task_id'];
	$status=$publish->publishBufferTask($task_id);
	if($status==-1){
		echo '网络连接存在问题，请检查您的设备';
	}
	else if($status==false){
		echo '发布失败';
	}
	else{
		echo '发布成功';
	}
}
else if($action=='publishDirectly'){
	$json=$_POST['task_basic_info'];
	$basic_info=json_decode($json,true);
	$user_id=$basic_info['owner_id'];
	$status=$publish->publishNewTask($user_id,$json);
	if($status==-1){
		echo '网络连接存在问题，请检查你的设备';
	}
	else if($status==false){
		echo '保存失败';
	}
	else{
		echo $status;//输出的是系统自动生成的任务编号
	}
}
else if($action=='list'){
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo '用户登录异常';
		exit;
	}
	$result_json=$publish->listAllToPublish($user_id);
	//json格式task_id(任务编号)，task_title(任务标题),save_time(任务保存时间)
	if($result_json==-1){
		echo '网络连接存在问题，请检查设备';
	}
	else{
		echo $result_json;
	}
}
else if($action=='detail'){
	$task_id=$_POST['task_id'];
	if(empty($task_id)){
		echo '任务编号有误';
		exit;
	}
	$result_json=$publish->detail($task_id);
	//json内容:task_id(任务编号),publish_time(发布时间),owner_id(发布人编号),owner_name（）发布人姓名,
	//deadline（）截止时间,hunter_id（最终猎人编号）,hunter_name（最终猎人姓名），task_type(任务类型),
	//state(任务状态),description(任务描述),module(任务模块),module_type(模块分类),
	//social_detail(社会任务细分),keyword(关键词),college(大学),institute(院校),is_man(是否是男性)
	//reward_type(奖励类型),goods_type(物品类型，可选),reward_note(奖励备注),
	//reward_number(奖励数目),reward_state(奖励状态),task_title(任务标题)
	if($result_json==-1){
		echo '存在网络连接问题，请检查您的设备';
	}
	else if($result_json==false){
		echo '该条记录存在问题或者已经被删除';
	}
	else{
		echo $result_json;
	}
}
else if($action=='modify'){
	$task_id=$_POST['task_id'];
	$content=$_POST['task_content'];//包括任务基本信息的json数组
	$status=$publish->modifyBasicInfo($task_id,$content);
	if($status==-1){
		echo '网络连接存在问题，请检查您的设备';
	}
	else if($status==false){
		echo '修改相关信息失败';
	}
	else{
		echo $status;
	}
}
else if($action=='invite'){
	$task_id=$_POST['task_id'];
	$user_id=$_POST['user_id'];
	$invitor=$_POST['invitor'];//包含所有邀请人编号的json数组
	$status=$publish->invite($user_id,$task_id,$invitor);
	if($status==-1){
		echo '网络连接存在问题，请检查您的设备';
	}
	else if($status==false){
		echo '邀请失败';
	}
	else{
		echo '邀请成功';
	}
}
else if($action=='endTask'){
	$task_id=$_POST['task_id'];
	$state=$_POST['state'];
	$status=$publish->endTask($task_id,$state);
	if($status==-1){
		echo '网络连接存在问题，请检查您的设备';
	}
	else if($status==false){
		echo '结束任务失败';
	}
	else{
		echo '结束任务成功';
	}
}
else{
	exit;
}
?>