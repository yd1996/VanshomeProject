<?php
$root_path=dirname(dirname(__FILE__));
include($root_path.'/dbConfig/dbconfig.php');
require($root_path.'/businesslogic/ID.inc');
class Publish{
	
	public function listAllToPublish($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task_id,task_title,publish_time
			        from task
					where task_id=any(select task_id
					                  from task_publish
									  where user_id='".$user_id."' and state=0);";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('task_id'=>$row['task_id'],
					             'task_title'=>$row['task_title'],
								 'save_time'=>$row['publish_time']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function detail($task_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task where task_id='".$task_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results!=1){
				return false;
			}
			else{
				$row=$result->fetch_assoc();
				$value=array('task_id'=>$row['task_id'],'publish_time'=>$row['publish_time'],
				'owner_id'=>$row['owner_id'],'owner_name'=>$row['owner_name'],
				'deadline'=>$row['deadline'],'hunter_id'=>$row['hunter_id'],
				'hunter_name'=>$row['hunter_name'],'task_type'=>$row['task_type'],
				'state'=>$row['state'],'description'=>$row['description'],
				'module'=>$row['module'],'module_type'=>$row['module_type'],
				'social_detail'=>$row['social_detail'],'keyword'=>$row['keyword'],
				'college'=>$row['college'],'institute'=>$row['institute'],
				'is_man'=>$row['is_man'],'reward_type'=>$row['reward_type'],
				'goods_type'=>$row['goods_type'],'reward_note'=>$row['reward_note'],
				'reward_number'=>$row['reward_number'],'reward_state'=>$row['reward_state'],
				'task_title'=>$row['task_title']);
				return json_encode($value);
			}
		}
	}
	
	//-1表示未发布
	public function save($user_id,$basic_info){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$task_id=new ID().getNewTaskID();
			//keyword删掉,institute,college,is_man自动赋值,申请任务获取时查看相关的
			$query1="insert into task(task_id,publish_time,owner_id,owner_name,
			        deadline,task_type,state,description,module,module_type,social_detail,
					keyword,college,institute,is_man,reward_type,goods_type,reward_note,
					reward_number,reward_state,task_title)
					value('".$task_id."','".$basic_info['publish_time']
					."','".$basic_info['owner_id']."','".$basic_info['owner_name']."','".
					$basic_info['deadline']."','".$basic_info['task_type'].
					"',0,'".$basic_info['description']."','".$basic_info['module'].
					"','".$basic_info['module_type']."','".$basic_info['social_detail']."','".
					$basic_info['keyword']."','".$basic_info['college']."','".$basic_info['institute'].
					"',".$basic_info['is_man'].",".$basic_info['reward_type'].",'"
					.$basic_info['goods_type']."','".$basic_info['reward_note']."',"
					.$basic_info['reward_number'].",".
					$basic_info['reward_state'].",'".$basic_info['task_title']."');";
			$query2="insert into task_publish(user_id,task_id,state,publish_time)
			         value('".$user_id."','".$task_id."',-1,'".$basic_info['publish_time']."');";
			$db->query($query1);
			$db->query($query2);
			return true;
		}
	}
	
	public function modifyBasicInfo($task_id,$basic_info){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="delete from task where task_id='".$task_id."';";
			$query2="insert into task(task_id,publish_time,owner_id,owner_name,deadline,hunter_id,
			        hunter_name,task_type,state,description,module,module_type,social_detail,
					keyword,college,institute,is_man,reward_type,goods_type,reward_note,
					reward_number,reward_state,task_title)
					value('".$task_id."','".$basic_info['publish_time']
					."','".$basic_info['owner_id']."','".$basic_info['owner_name']."','".
					$basic_info['deadline']."','".$basic_info['hunter_id']."','"
					.$basic_info['hunter_name']."','".$basic_info['task_type']."','".
					$basic_info['state']."','".$basic_info['description']."','".$basic_info['module'].
					"','".$basic_info['module_type']."','".$basic_info['social_detail']."','".
					$basic_info['keyword']."','".$basic_info['college']."','".$basic_info['institute'].
					"',".$basic_info['is_man'].",".$basic_info['reward_type'].",'"
					.$basic_info['goods_type']."','".$reward_note."',".$reward_number.",".
					$basic_info['reward_state'].",'".$basic_info['task_title']."');";
			$db->query($query1);
			$db->query($query2);
			return true;
		}
	}
	
	public function publishBufferTask($task_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update task set state=0 where task_id='".$task_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function publishNewTask($user_id,$basicInfo){
		//$db=new mysqli('localhost','root','','vanshome');
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		$db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$id=new ID();
			$task_id=$id->getNewTaskID();
			$basic_info=json_decode($basicInfo,true);
			$query1="insert into task(task_id,publish_time,owner_id,owner_name,
			        deadline,task_type,state,description,module,module_type,social_detail,
					college,institute,is_man,reward_type,goods_type,reward_note,
					reward_number,reward_state,task_title)
					value('".$task_id."','".$basic_info['publish_time']
					."','".$basic_info['owner_id']."','".$basic_info['owner_name']."','".
					$basic_info['deadline']."','".$basic_info['task_type']
					."',0,'".$basic_info['description']."','".$basic_info['module'].
					"','".$basic_info['module_type']."',1,'nju','se',0,".$basic_info['reward_type'].",'"
					.$basic_info['goods_type']."','".$basic_info['reward_note']
					."',0,".//reward_number
					$basic_info['reward_state'].",'".$basic_info['task_title']."')";
			 $query2="insert into task_publish(user_id,task_id,state,publish_time)
			         value('".$user_id."','".$task_id."',0,'".$basic_info['publish_time']."')";
			$status1=$db->query($query1);
			$status2=$db->query($query2);
			return $task_id;
		}
	}
	
	public function invite($user_id,$task_id,$client_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="insert into task_invite(user_id,invitor_id,task_id)
			        value('".$user_id."','".$invitor_id."','".$task_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	//0表示成功，1表示失败
	public function endTask($task_id,$state){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="update task_publish set state=";
			$query3=" where task_id='".$task_id."';";
			$query2=" ";
			if($state==0){
				$query2=3;
			}
			else if($state==1){
				$query2=4;
			}
			else{
				$query=2;
			}
			$query=$query1.$query2.$query3;
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