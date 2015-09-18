<?php
header('Content-type: text/html; charset=utf8');
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Login{
	public function loginCheck($loginstr,$password){
		$checkStatus=$this->checkLoginInfo($loginstr,$password);
		if($checkStatus==-2){
			return -1;//数据库连接存在问题
		}
		else if($checkStatus==false){
			return false;//没有这个用户或者密码错误
		}
		else {
			return $checkStatus;//返回json数组
		}
	}
	public function checkExistance($loginstr){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,'root','','vanshome');
		if(mysqli_connect_errno()){
			return -2;//连接存在异常，则返回错误码-2
		}
		else{
				$query="select * from user 
		               where user_id='".$loginstr."' or user_name='".$loginstr."'
				       or default_phone='".$loginstr."' or default_email='".$loginstr."';";
				$result=$db->query($query);
				$num_results=$result->num_rows;
				if($num_results==1){
					$row=$result->fetch_assoc();
					return $row['user_id'];
			    }
				else{
					return false;
				}
		}
		
	}
	
	//这个接口用于总的检查所有的登录信息
	public function checkLoginInfo($loginstr,$inputPW){
		$exist=$this->checkExistance($loginstr);
		if($exist==-1){
			return -1;//用户未输入
		}
		else if($exist==-2){
			return -2;//连接异常
		}
		else if($exist==false){
			return false;//没有相关信息
		}
		else{
			$user_id=$exist;
			@ $db=new mysqli($DB_HOST,'root','','vanshome');
			if(mysqli_connect_errno()){
				return -2;//连接存在异常，则返回错误码-2
			}
			else{
				$query="select * from user 
		               where user_id='".$user_id."';";
				$result=$db->query($query);
				$row=$result->fetch_assoc();
				$password=$row['password'];
				if(!$inputPW){
					return -3;//未输入密码，返回-3
				}
				else{
					if($password==$inputPW){
						return $this->getBasicInf($user_id);
					}
					else{
						return false;
					}
				}
			}
		}
	}
	
	public function getBasicInf($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,'root','','vanshome');
		if(mysqli_connect_errno()){
			return NULL;
		}
		else{
			$query="select * from user
			        where user_id='".$user_id."';";
			$result=$db->query($query);
			$row=$result->fetch_assoc();
			$output=array('user_id'=>$row['user_id'],'user_name'=>$row['user_name'],
			        'user_level'=>$row['user_level'],'honor'=>$row['honor'],
					'is_identified'=>$row['is_identified']);
			return json_encode($output);
		}
	}
}
?>