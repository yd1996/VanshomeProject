<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
require($root_path.'/businesslogic/Check.inc');
require($root_path.'/businesslogic/ID.inc');
class Register{
	private $name;
	private $password;
	private $defaultEmail;
	private $defaultPhone;
	private $basicInfo;
	private $interest;
	public function setName($name){
		$checkTool=new Check();
		$checkStatus=$checkTool->checkNameValid($name);
		if(!$checkStatus){
			return false;
		}
		else{
			$this->name=$name;
			return true;
		}
	}
	
	public function setPassword($password){
		$checkTool=new Check();
		$checkStatus=$checkTool->checkPasswordValid($password);
		if(!$checkStatus){
			return false;
		}
		else{
			$this->password=$password;
			return true;
		}
	}
	
	public function setDefaultEmail($checkCode,$email){//迭代一中checkCode忽略不计
	    $checkTool=new Check();
		$checkStatus=$checkTool->checkEmailValid($email);
		if(!$checkStatus){
			return false;
		}
		else{
			$this->email=$email;
			return true;
		}
	}
	
	public function setDefaultPhone($checkCode,$phone){
		//迭代一中验证码忽略不计
		$checkTool=new Check();
		$checkStatus=$checkTool->checkPhoneValid($phone);
		if(!$checkStatus){
			return false;
		}
		else{
			$this->phone=$phone;
			return true;
		}
	}
	
	//public function setBasicInfo($basicInfo){
		//$checkTool=new Check();
		//$checkStatus=$checkTool->checkBasicInfo($basicInfo);
		//if(!$checkStatus){
			//return false;
		//}
		//else{
			//$this->basicInfo=$basicInfo;
			//return true;
		//}
	//}
	
	//public function setInterestArea($interest){//json数组
		//$this->interest=$interest;
		//return true;
	//}
	
	public function commitRegisterInfo(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$user_id=$this->getNewID();
			//icon_str未设定
			$query="insert into user(user_id,user_name,default_phone,default_email,
			       password,person_note,icon_str,is_man,birth_time,address,qq,phone,
				   microblog,email,score,is_personal,user_level,honor,is_identified)
				   value('".$user_id."','".$name."','".$phone."','".$email."','".$password.
				   "','".$basicInfo['person_note']."','".$basicInfo['icon_str']
				   ."','".$basicInfo['is_man']."','".$basicInfo['birth_time']."','"
				   .$basicInfo['address']."','".$basicInfo['qq']."','".$basicInfo['phone']
				   ."','".$basicInfo['microblog']."','".$basicInfo['email']."','".
				   $basicInfo['score']."','".$basicInfo['is_personal']."','"
				   .$basicInfo['user_level']."','".$basicInfo['honor']."','"
				   .$basicInfo['is_identified']."');";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}	
	}
	
	private function getNewID(){
		$id=new ID();
		return $id->getNewUserID();
	}
}
?>