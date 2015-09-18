<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class TaskListManage{
	//特别针对自己接的已完成的和未完成的任务
	public function listAllTaskToDo($user_id){
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
			       where task_id=any(select task_id from task_apply 
				                     where user_id='".$user_id."' and state>0);";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
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
				                 'reward_number'=>$row['reward_number'],
								 'reward_state'=>$row['reward_state'],
				                 'task_title'=>$row['task_title']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	//1申请中 2完成过程中 3任务完成 4任务失败
	public function listAllFinishedTask($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task.task_id,publish_time,owner_id,owner_name,deadline,task_type,
			             task_apply.state,description,module,module_type,social_detail,
						 keyword,is_man,reward_type,goods_type,reward_note,reward_number,
						 reward_state,task_title
			        from task_apply,task 
			        where task_apply.task_id=task.task_id
					  and user_id='".$user_id."' and task_apply.state=3;"; 
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('task_id'=>$row['task_id'],'publish_time'=>$row['publish_time'],
					            'owner_id'=>$row['owner_id'],'owner_name'=>$row['owner_name'],
								'deadline'=>$row['deadline'],'task_type'=>$row['task_type'],
								'state'=>$row['state'],'description'=>$row['description'],
								'module'=>$row['module'],'module_type'=>$row['module_type'],
								'social_detail'=>$row['social_detail'],'keyword'=>$row['keyword'],
								'is_man'=>$row['is_man'],'reward_type'=>$row['reward_type'],
								'goods_type'=>$row['goods_type'],'reward_note'=>$row['reward_note'],
								'reward_number'=>$row['reward_number'],
								'reward_state'=>$row['reward_state'],'task_title'=>$row['task_title']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function listAllUnfinishedTask($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task.task_id,publish_time,owner_id,owner_name,deadline,task_type,
			             task_apply.state,description,module,module_type,social_detail,
						 keyword,is_man,reward_type,goods_type,reward_note,reward_number,
						 reward_state,task_title
			        from task_apply,task 
			        where task_apply.task_id=task.task_id
					  and user_id='".$user_id."' and task_apply.state=2;"; 
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('task_id'=>$row['task_id'],'publish_time'=>$row['publish_time'],
					            'owner_id'=>$row['owner_id'],'owner_name'=>$row['owner_name'],
								'deadline'=>$row['deadline'],'task_type'=>$row['task_type'],
								'state'=>$row['state'],'description'=>$row['description'],
								'module'=>$row['module'],'module_type'=>$row['module_type'],
								'social_detail'=>$row['social_detail'],'keyword'=>$row['keyword'],
								'is_man'=>$row['is_man'],'reward_type'=>$row['reward_type'],
								'goods_type'=>$row['goods_type'],'reward_note'=>$row['reward_note'],
								'reward_number'=>$row['reward_number'],
								'reward_state'=>$row['reward_state'],'task_title'=>$row['task_title']);
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
			if($num_results==0){
				return false;
			}
			else{
				$row=$result->fetch_assoc();
				$output=array('owner_id'=>$row['owner_id'],'owner_name'=>$row['owner_name'],
				             'deadline'=>$row['deadline'],'task_type'=>$row['task_type'],
							 'state'=>$row['state'],'description'=>$row['description'],
							 'module'=>$row['module'],'module_type'=>$row['module_type'],
							 'social_detail'=>$row['social_detail'],'keyword'=>$row['keyword'],
							 'college'=>$row['college'],'institute'=>$row['institute'],
							 'is_man'=>$row['is_man'],'reward_type'=>$row['reward_type'],
							 'goods_type'=>$row['goods_type'],'reward_note'=>$row['reward_note'],
							 'reward_number'=>$row['reward_number'],
							 'reward_state'=>$row['reward_state'],'task_title'=>$row['task_title']);
				return json_encode($output);
			}
		}
	}
	
	public function modify($user_id,$task_id,$solution){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update task_apply 
			       set solution='".$solution."' 
				   where user_id='".$user_id."' and task_id='".$task_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function giveup($user_id,$task_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update task_apply 
			       set state=4
				   where user_id='".$user_id."' and task_id='".$task_id."';";
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