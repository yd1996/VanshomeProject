<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class ID{
    public function getNewUserID(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
	    @ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from user;";
			$result=$db->query($query);
			echo $db->error;
			@ $num_results=$result->num_rows;
			$output="user".$this->dispRepair(strval($num_results+1),8,'0');
			return $output;
		}
	}
	public function getNewTaskID(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
	    $db=new mysqli('localhost','root','','vanshome');
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task;";
			$result=$db->query($query);
			echo $db->error;
			$num_results=$result->num_rows;
			$output="task".$this->dispRepair(strval($num_results+1),8,'0');
			return $output;
		}
	}
	public function getNewSchoolID(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
	    @ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from school_info;";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			$output="school".$this->dispRepair(strval($num_results+1),8,'0');
			return $output;
		}
	}
	
	/*当要的结果001的话，方法：dispRepair('1',3,'0')
	  功能：补位函数
      str:原字符串
      type：类型，0为后补，1为前补
      len：新字符串长度
      msg：填补字符
    */
	private function dispRepair($str,$len,$msg,$type='1') {
		$length = $len - strlen($str);
		if($length<1){
			return $str;
		}
		if($type==1){
			$str = str_repeat($msg,$length).$str;
		}
		else{
			$str .= str_repeat($msg,$length);
		}
		return $str;
	}
}
?>