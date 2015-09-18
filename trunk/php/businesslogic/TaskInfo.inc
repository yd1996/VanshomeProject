<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class TaskInfo{
	
	public function listLatestTask($type){
		//TODO
		
	}
	
	//获取所有自己发布的任务的信息列表，包括未受理、受理中、已完成、失败，参数中type代表任务状态用于筛选
	//关于type，0为全部，1为未受理，2为受理中，3为已完成，4为失败.-1表示未发布，-2表示已经删除
	public function listAllTaskPublished($user_id){
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
			       where task_id=any(select task_id from task_publish
				                    where user_id='".$user_id."');";
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
	
	//获取自己所有的受理任务的信息列表，包括正在受理、已完成、已放弃，参数中type代表任务状态用于筛选
	//关于type，0为全部，1为正在受理，2为已经完成，3为已经放弃,4表示入围未完成,-1为申请被拒绝
	public function listAllTaskToFinish($type,$user_id){
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task
			       where task_id=any(select task_id from task_apply
				                     where ) and type=".$type.";";
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
	
	//获取自己所有正在申请中和已经被申请拒绝的任务
	public function listAllTaskApplying($user_id){
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task
			       where task_id=any(select task_id from task_apply
				                    where (user_id='".$user_id." and state=1)
									   or (user_id='".$user_id." and state=-1));";
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
	
	//获取自己所有的被邀请但是还未接受的任务
	public function listAllTaskInvited($user_id){
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task
			       where task_id=any(select task_id from task_invite
				                    where invitor_id='".$user_id."');";
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
	
	//获取自己被推送的任务
	public function listAllTaskRecommend($user_id){
		//推送功能放到迭代二中去
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			
		}
	}
	
	//列出所有的收藏任务
	public function listAllTaskAttention($user_id){
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task
			       where task_id=any(select task_id from task_attention
				                    where user_id='".$user_id."');";
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
	
	//查询某一任务的详细信息
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
			$query="select * from task
			       where task_id='".$task_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
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
				             'reward_number'=>$row['reward_number'],
						     'reward_state'=>$row['reward_state'],
				             'task_title'=>$row['task_title']);
				return json_encode($value);
			}	
		}
	}
	
	//针对自己已经发布但是还未完结的相关任务进行修改
	public function modify($task_id,$content){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update task 
			        set deadline='".$content['deadline']."' and hunter_id='".$content['hunter_id'].
					"' and hunter_name='".$hunter_name."' and state=".$content['state']
					." and description='".$content['description']."' and task_type="
					.$content['task_type']." and module=".$content['module']." and module_type="
					.$content['module_type']." and social_detail=".$content['social_detail']
					." and keyword='".$content['keyword']."' and reward_type=".$reward_type
					." and goods_type=".$content['goods_type']." and reward_note='"
					.$content['reward_note']."' and reward_number=".$content['reward_number']
					." and reward_state=".$content['reward_state']." and task_title='"
					.$content['task_title']."' where task_id='".$task_id."';"; 
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function getApplicationOfTask($task_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select user.user_id,user_name,note,solution,apply_time,state
			        from task_apply,user
					where task_apply.user_id=user.user_id and task_id='".$task_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('user_id'=>$row['user_id'],'user_name'=>$row['user_name'],
					             'note'=>$row['note'],'solution'=>$row['solution'],
								 'apply_time'=>$row['apply_time'],'state'=>$row['state']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
}
?>