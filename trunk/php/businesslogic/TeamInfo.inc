<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class TeamInfo{
	
	public function listAllTeam(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			//json格式team_id,team_name(团队名称),team_rank(团队等级),
	        //team_logo(团队logo),team_note(团队说明)
			$query="select team_id,team_name,team_rank,team_logo,team_note from team;";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('team_id'=>$row['team_id'],'team_name'=>$row['team_name'],
					             'team_rank'=>$row['team_rank'],'team_logo'=>$row['team_logo'],
								 'team_note'=>$row['team_note']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function listPersonalAllTeam($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			//json格式team_id,team_name(团队名称),team_rank(团队等级),
	        //team_logo(团队logo),team_note(团队说明)
			$query="select team_id,team_name,team_rank,team_logo,team_note from team
			        where team_id=any(select team_id from join where user_id='".$user_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('team_id'=>$row['team_id'],'team_name'=>$row['team_name'],
					             'team_rank'=>$row['team_rank'],'team_logo'=>$row['team_logo'],
								 'team_note'=>$row['team_note']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function detail($team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from team where team_id='".$team_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_rows==0){
				return false;
			}
			else{
				$row=$result->fetch_assoc();
				$value=array('team_id'=>$row['team_id'],'team_name'=>$row['team_name'],
				             'team_rank'=>$row['team_rank'],'team_slogan'=>$row['team_slogan'],
							 'team_logo'=>$row['team_logo'],'team_note'=>$row['team_note'],
							 'member_num'=>$row['member_num'],'setup_time'=>$row['setup_time'],
							 'first_leader_id'=>$row['first_leader_id'],
							 'first_leader_name'=>$row['first_leader_name'],
							 'leader_id'=>$row['leader_id'],'leader_name'=>$row['leader_name']);
				return json_encode($value);
			}
		}
	}
	
	public function modify($team_id,$content){
		//content为一个json数组，里面包括可以修改的内容，其中有
	    //team_name(团队名称),team_slogan(团队口号),team_note(团队说明)
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update team
			        set team_name='".$content['team_name']."',team_slogan='".$content['team_slogan']
					."',team_note='".$content['team_note']."' where team_id='".$team_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function listTeamDoingTask($team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task_id,publish_time,owner_id,owner_name,deadline,
			          task_type,state,description,module,module_type,social_detail,
					  is_man,reward_type,goods_type,reward_note,reward_number,
					  reward_state,task_title
					from task
					where task_id=any(select task_id 
					                  from task_apply
									  where state=1 and team_id='".$team_id."')";
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
								 'social_detail'=>$row['social_detail'],'is_man'=>$row['is_man'],
								 'reward_type'=>$row['reward_type'],'goods_type'=>$row['goods_type'],
								 'reward_note'=>$row['reward_note'],
								 'reward_number'=>$row['reward_number'],
								 'reward_state'=>$row['reward_state'],'task_title'=>$row['task_title']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function listTeamAllTaskRecord($team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task_id,publish_time,owner_id,owner_name,deadline,
			          task_type,state,description,module,module_type,social_detail,
					  is_man,reward_type,goods_type,reward_note,reward_number,
					  reward_state,task_title
					from task
					where task_id=any(select task_id 
					                  from task_apply
									  where state>=1 and stateteam_id='".$team_id."')";
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
								 'social_detail'=>$row['social_detail'],'is_man'=>$row['is_man'],
								 'reward_type'=>$row['reward_type'],'goods_type'=>$row['goods_type'],
								 'reward_note'=>$row['reward_note'],
								 'reward_number'=>$row['reward_number'],
								 'reward_state'=>$row['reward_state'],'task_title'=>$row['task_title']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
}
?>