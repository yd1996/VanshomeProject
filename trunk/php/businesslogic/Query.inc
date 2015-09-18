<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Query{
	public function queryPersonalUser($key){
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
			       where user_id='".$key."' or user_name='".$key."';";
			$result=$db->query($query);
			$num_results=$results->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('user_id'=>$row['user_id'],'user_name'=>$row['user_name'],
					            'default_phone'=>$row['default_phone'],
								'default_email'=>$row['default_email'],
								'password'=>$row['password'],'person_note'=>$row['person_note'],
								'icon_str'=>$row['icon_str'],'is_man'=>$row['is_man'],
								'birth_time'=>$row['birth_time'],'address'=>$row['address'],
								'qq'=>$row['qq'],'phone'=>$row['phone'],'microblog'=>$row['microlog'],
								'email'=>$row['email'],'score'=>$row['score'],
								'is_personal'=>$row['is_personal'],'user_level'=>$row['user_level'],
								'honor'=>$row['honor'],'is_identified'=>$row['is_identified']
								);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function queryTeamUser($key){
		//团队部分迭代一暂不实现
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			
		}
	}
	
	public function queryNeedUser($key){
		//需求商部分迭代一暂不实现
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			
		}
	}
	
	public function queryTask($module,$type){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task
			       where state=0 and module=".$module." and module_type=".$type.";";
			$result=$db->query($query);
			$num_results=$result->num_results;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('task_id'=>$row['task_id'],
					             'publish_time'=>$row['publish_time'],
								 'owner_id'=>$row['owner_id'],
								 'owner_name'=>$row['owner_name'],
								 'deadline'=>$row['deadline'],
								 'hunter_id'=>$row['hunter_id'],
								 'hunter_name'=>$row['hunter_name'],
								 'task_type'=>$row['task_type'],
								 'state'=>$row['state'],
								 'description'=>$row['description'],
								 'module'=>$row['module'],
								 'module_type'=>$row['module_type'],
								 'social_detail'=>$row['social_detail'],
								 'keyword'=>$row['keyword'],
								 'college'=>$row['college'],
								 'institute'=>$row['institute'],
								 'is_man'=>$row['is_man'],
								 'reward_type'=>$row['reward_type'],
								 'goods_type'=>$row['goods_type'],
								 'reward_note'=>$row['reward_note'],
								 'reward_number'=>$row['reward_number'],
								 'reward_state'=>$row['reward_state'],
								 'task_title'=>$row['task_title']
								 );
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
}
?>