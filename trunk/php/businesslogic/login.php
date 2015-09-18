<?php
namespace bl;
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbController/loginController.php');
class Login{
	public function login($loginstr,$password){
		$loginController=new LoginController();
		$checkStatus=$loginController->checkLoginInfo($loginstr,$password);
		if($checkStatus==-2){
			return -1;
		}
		else if($checkStatus==false){
			return false;
		}
		else {
			return $checkStatus;
			//$output=array('user_id'=>$row['user_id'],'user_name'=>$row['user_name'],
			//'user_level'=>$row['user_level'],'honor'=>$row['honor'],
			//'is_identified'=>$row['is_identified']);
		}
	}
}
?>