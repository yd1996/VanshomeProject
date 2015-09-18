<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require_once($root_path.'/businesslogic/PersonalBasicInfo.inc');
$action=$_GET['action'];
$datasource=new PersonalBasicInfo();
if($action=='get_basic_info'){
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录异常','result'=>'null'));
		exit;
	}
	$json=$datasource->getBasicInfo($user_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'不存在相关的用户','result'=>'none'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$json));
		exit;
	}
	//返回的json数组中user_id(用户编号),user_name(用户姓名),default_phone(绑定手机号),default_email(绑定邮箱)
	//person_note(个人说明),icon_str(头像路径),is_man(是否为男性),birth_time(出生日期),address(常住地址),
	//qq(qq账号),phone(常用手机号码),microblog(微博账号),email(常用邮箱),score(积分),
	//is_personal(是否为个人用户),user_level(用户等级),honor(荣誉称号),is_identified(是否为认证用户)
}
else if($action=='modify_basic_info'){
	//传进一个basic_info的json数组，其中内容包括:
	//user_id(用户编号),user_name(用户姓名),person_note(个人说明),icon_str(头像路径),is_man(是否是男性),
	//address(常住地址),birth_time(出生日期),qq(QQ账号),phone(常用手机号码），microblog(常用微博),
	//email(常用邮箱),score(积分),is_personal(是否为个人账户),user_level(用户等级),honor(荣誉称号),
	//is_identified(是否为认证用户)
	$basic_info=json_decode($_POST['basic_info'],true);
	if(empty($basic_info)){
		echo json_encode(array('success'=>0,'msg'=>'用户登陆态异常','result'=>'null'));
		exit;
	}
	$json=$datasource->modifyBasicInfo($basic_info);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'修改失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'修改成功','result'=>'null'));
		exit;
	}
}
else if($action=='get_interest_info'){
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态异常','result'=>'null'));
		exit;
	}
	$json=$datasource->getPersonalInterest($user_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在异常','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'用户未添加相关的兴趣领域','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$json));
		exit;
	}
}
else if($action=='add_interest_info'){
	$user_id=$_POST['user_id'];
	$interest=$_POST['interest'];//注意这是个数组的json
	$area=json_decode($interest,true);
	$count=count($area);
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	if($count==0){
		echo json_encode(array('success'=>0,'msg'=>'未执行任何操作','result'=>'null'));
		exit;
	}
	$json=$datasource->addPersonalInterest($user_id,$interest);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'添加失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'添加成功','result'=>'null'));
		exit;
	}
}
else if($action=='delete_interest_info'){
	$user_id=$_POST['user_id'];
	$interest=$_POST['interest'];//注意这是个数组的json
	$area=json_decode($interest,true);
	$count=count($area);
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	if($count==0){
		echo json_encode(array('success'=>0,'msg'=>'未执行任何操作','result'=>'null'));
		exit;
	}
	$json=$datasource->deletePersonalInterest($user_id,$interest);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'添加失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'添加成功','result'=>'null'));
		exit;
	}
}
else if($action=='get_education_info'){
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在异常','result'=>'null'));
		exit;
	}
	$json=$datasource->getPersonalEducation($user_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if ($json==false){
		echo json_encode(array('success'=>0,'msg'=>'获取失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'获取成功','result'=>$json));
		exit;
	}
	//返回json数组内容包括year(入学年份),province(省份),college(大学),institute(学院)
}
else if($action=='add_education_info'){
	$user_id=$_POST['user_id'];
	$school_id=$_POST['school_id'];//一个学校编号的数组的json
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	$school=json_decode($school_id,true);
	$count=count($school_id);
	if($count==0){
		echo json_encode(array('success'=>0,'msg'=>'未输入相关学校','result'=>'null'));
		exit;
	}
	$json=$datasource->addPersonalEducation($user_id,$school_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'添加失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'添加成功','result'=>'null'));
		exit;
	}
}
else if($action=='delete_education_info'){
	$user_id=$_POST['user_id'];
	$school_id=$_POST['school_id'];//一个学校编号的数组的json
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	$school=json_decode($school_id,true);
	$count=count($school_id);
	if($count==0){
		echo json_encode(array('success'=>0,'msg'=>'未输入相关学校','result'=>'null'));
		exit;
	}
	$json=$datasource->deletePersonalEducation($user_id,$school_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'添加失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'添加成功','result'=>'null'));
		exit;
	}
}
else if($action=='get_security_info'){
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	$json=$datasource->getSecurityInfo($user_id);
	if($json==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($json==false){
		echo json_encode(array('success'=>0,'msg'=>'没有相关数据','result'=>'null'));
		exit;
	}
	else{
		//返回的json数组内容包括default_phone(绑定手机),default_email(绑定邮箱)
		echo json_encode(array('success'=>1,'msg'=>'查询成功','result'=>$json));
		exit;
	}
}
else if($action=='add_default_phone'){
	//TODO:因为包含发送手机验证码问题所以先不管
}
else if($action=='delete_default_phone'){
	//TODO:因为包含发送手机验证码问题所以先不管
}
else if($action=='add_default_email'){
	//TODO:因为包含发送手机验证码问题所以先不管
}
else if($action=='delete_default_email'){
	//TODO:因为包含发送手机验证码问题所以先不管
}
else if($action=='modify_password'){//修改密码
	$user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	$password=$_POST['password'];
	$status=$datasource->modifyPassword($user_id,$password);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'密码修改失败','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'密码修改成功','result'=>'null'));
		exit;
	}
}
else if($action=='check_password'){//输入修改前密码后检测是否和原来的密码一致
    $user_id=$_POST['user_id'];
	if(empty($user_id)){
		echo json_encode(array('success'=>0,'msg'=>'用户登录态存在问题','result'=>'null'));
		exit;
	}
	$password=$_POST['password'];
	$status=$datasource->checkPassword($user_id,$password);
	if($status==-1){
		echo json_encode(array('success'=>0,'msg'=>'网络连接存在问题','result'=>'null'));
		exit;
	}
	else if($status==false){
		echo json_encode(array('success'=>0,'msg'=>'密码错误','result'=>'null'));
		exit;
	}
	else{
		echo json_encode(array('success'=>1,'msg'=>'密码正确','result'=>'null'));
		exit;
	}
}
else{
	exit;
}
?>