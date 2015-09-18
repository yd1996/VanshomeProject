<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
require($root_path.'/businesslogic/ID.inc');
class Service{
	public function getAllInterestArea(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from area;";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('name'=>$row['name'],'type'=>$row['type'],'logo'=>$row['logo']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function getAllSchool(){
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
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('id'=>$row['id'],
					             'province'=>$row['province'],
					             'college'=>$row['college'],
								 'institute'=>$row['institute']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function saveNewSchool($province,$college,$institute){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$school_id=new ID().getNewSchoolID();
			$query="insert into school_info(id,province,college,institute)
			        value('".$school_id."','".$province."','".$college."','".$institute."');";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
}
?>