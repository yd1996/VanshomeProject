<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Check{
	public function checkTypeOfUsers($id){
		if($id[0]=='P'){//个人用户
			return 1;
		}
		else if($id[0]=='T'){//团队
			return 2;
		}
		else if($id[0]=='N'){//需求商
			return 3;
		}
		else{
			return 0;
		}
	}
	
	public function checkNameValid($name){
		//存在非法词汇或者非法字符返回-1，已经存在相同的用户名返回false，可以使用返回true
		return false;
	}
	
	public function checkDefaultEmailValid($email){
		return false;
	}
	
	public function checkDefaultPhoneValid($phone){
		if(strlen($phone)==9||strlen($phone)==12){
			return true;
		}
		else{
			return false;
		}
	}
	
	public function checkPasswordValid($password){
		if(strlen($password)<6 || strlen($password) > 30){
			return false;
		}
		else{
			return true;
		}	
	}
	
	public function checkBasicInfo($basicInfo){//json数组
		return true;//需要一项项检查
	}
	
	public function checkRoleOfTeam($user_id,$team_id){
		return false;
		//迭代一暂时不实现
	}
}
?>