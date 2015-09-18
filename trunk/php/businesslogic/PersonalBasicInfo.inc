<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class PersonalBasicInfo{
	public function getBasicInfo($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from user
			       where user_id='".$user_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results!=1){
				return false;
			}
			else{
				$row=$result->fetch_assoc();
				$value=array('user_id'=>$row['user_id'],'user_name'=>$row['user_name'],
							 'default_phone'=>$row['default_phone'],
							 'default_email'=>$row['default_email'],'password'=>$row['password'],
							 'person_note'=>$row['person_note'],'icon_str'=>$row['icon_str'],
							 'is_man'=>$row['is_man'],'birth_time'=>$row['birth_time'],
							 'address'=>$row['address'],'qq'=>$row['qq'],'phone'=>$row['phone'],
							 'microblog'=>$row['microblog'],'email'=>$row['email'],
							 'score'=>$row['score'],'is_personal'=>$row['is_personal'],
							 'user_level'=>$row['user_level'],'honor'=>$row['honor'],
							 'is_identified'=>$row['is_identified']);
				return json_encode($value);
			}
		}
	}
	
	public function modifyBasicInfo($basic_info){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update user set user_name='".$basic_info['user_name']
			        ."',person_note='".$basic_info['person_note']
					."',icon_str='".$basic_info['icon_str']
					."',is_man='".$basic_info['is_man']."',birth_time='".$basic_info['birth_time']
					."'，address='".$basic_info['address']."',qq='".$basic_info['qq']."',phone='"
					.$basic_info['phone']."',microblog='".$basic_info['microblog']
					."',email='".$basic_info['email']."',score=".$basic_info['score']
					.",is_personal=".$basic_info['is_personal']
					.",user_level=".$basic_info['user_level'].",honor='".$basic_info['honor']
					."',is_identified=".$basic_info['is_indentified']." where user_id='"
					.$basic_info['user_id']."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}		
	}
	
	public function getDefaultSecurityInf($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select password,default_phone,default_email
			       from user
				   where user_id='".$user_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results!=1){
				return false;
			}
			else{
				$row=$result->fetch_assoc();
				$value=array('password'=>$row['password'],
				             'default_phone'=>$row['default_phone'],
							 'default_email'=>$row['default_email']);
				return json_encode($value);
			}
		}
	}
	
	public function ensureDeleteDefaultPhone($user_id){
		return false;//迭代一不用管
	}
	
	public function deleteDefaultPhone($user_id,$checkCode){
		return false;
	}
	
	public function ensureModifyDefaultPhone($user_id,$newPhone){
		return false;//迭代一不用管
	}
	
	public function modifyDefaultPhone($user_id,$checkCode){
		return false;
	}
	
	public function ensureDeleteDefaultEmail($user_id){
		return false;//迭代一不用管
	}
	
	public function deleteDefaultEmail($user_id,$checkCode){
		return false;
	}
	
	public function ensureModifyDefaultEmail($user_id){
		return false;//迭代一不用管
	}
	
	public function modifyDefaultEmail($user_id,$checkCode){
		return false;
	}
	
	public function getPersonalInterest($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select area.name,area.logo,area.type
			        from area,interest
					where interest.name=area.name and user_id='".$user_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('name'=>$row['name'],'logo'=>$row['logo'],'type'=>$row['type']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function deletePersonalInterest($user_id,$value){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$area=json_decode($value,true);
			$count=count($area);
			if($count==0){
				return false;
			}
			for($i=0;$i<$count;$i++){
				$query="delete from interest
				        where user_id='".$user_id."' and name='".$area[$i]."';";
				$db->query($query);
			}
			return true;
		}
	}
	
	public function addPersonalInterest($user_id,$value){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$area=json_decode($value,true);
			$count=count($area);
			if($count==0){
				return false;
			}
			for($i=0;$i<$count;$i++){
				$query="insert into interest(user_id,name)
				        value('".$user_id."','".$value."');";
				$db->query($query);
			}
			return true;
		}
	}
	
	public function getPersonalEducation($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select year,province,college,institute
			       from education,school_info
			       where school_id=id and user_id='".$user_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('year'=>$row['year'],'province'=>$row['province'],
					             'college'=>$row['college'],'institute'=>$row['institute']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function deletePersonalEducation($user_id,$value){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$school=json_decode($value);//包含school_id
			$count=count($school);
			if($count==0){
				return false;
			}
			for($i=0;$i<$count;$i++){
				$query="delete from education
				        where user_id='".$user_id."' and school_id='".$school[$i]."';";
				$db->query($query);
			}
			return true;
		}
	}
	
	public function addPersonalEducation($user_id,$value){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$school=json_decode($value);//包含school_id和year
			$count=count($school);
			if($count==0){
				return false;
			}
			for($i=0;$i<$count;$i++){
				$query="insert into education(user_id,school_id,year)
				         value('".$user_id."','".$school[$i]['school_id']."','".$year.");";
				$db->query($query);
			}
			return true;
		}
	}
}
	
?>