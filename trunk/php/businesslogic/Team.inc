<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Team{
	
	public function listJoinApplication($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select team.team_id,apply_time,team_name,team_logo,reason
			        from apply_to_join,team
			        where apply_to_join.team_id=team.team_id
					  and user_id='".$user_id."';";
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
					             'apply_time'=>$row['apply_time'],'team_logo'=>$row['team_logo'],
								 'reason'=>$row['reason']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function joinTeam($user_id,$team_id,$reason){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$apply_time=date('YYYY-MM-DD hh:ii:ss');
			$query="insert into apply_to_join(user_id,team_id,reason,apply_time)
			          value('".$user_id."','".$team_id."','".$reason."','".$apply_time."');";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function leaveTeam($user_id,$team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="delete from join where user_id='".$user_id."' and team_id='".$team_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function acceptInvitation($user_id,$team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="delete from invite_to_join 
			       where user_id='".$user_id."' and team_id='".$team_id."';";
			$status1=$db->query($query1);
			if(!$status1){
				return false;
			}
			else{
				$query2="insert into join(user_id,team_id,is_leader,is_manager)
				         value('".$user_id."','".$team_id."',0,0);";
				$status2=$db->query($query2);
				if(!$status){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
	
	public function setTeam($content){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			//json格式team_name(团队名称),team_rank(团队等级),team_slogan(团队口号),
	        //team_logo(团队logo),team_note(团队说明),owner_id(用户编号),owner_name(用户姓名)
			$id_factory=new ID();
			$team_id=$id_factory->getNewTeamID();
			$time=date('YYYY-MM-DD hh:ii:ss');
			$query1="insert into team(team_id,team_name,team_rank,team_slogan,team_logo,team_note,
			            first_leader_id,first_leader_name,leader_id,leader_name,member_num,setup_time)
					value('".$team_id."','".$content['team_name']."',".$content['team_rank'].",'".
					$content['team_slogan']."','".$content['team_logo']."','".$content['team_note']
					."','".$content['owner_id']."','".$content['owner_name']."','".$content['owner_id']
					."','".$content['owner_name']."',0,'".$time."');";
			$status=$db->query($query1);
			if(!$status){
				return false;
			}
			else{
				$query2="insert into join(user_id,team_id,is_leader,is_manager)
				           value('".$content['owner_id']."','".$team_id."',1,0);";
				$status2=$db->query($query2);
				if(!$status){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
	
	public function dismissTeam($user_id,$team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="delete from team where team_id='".$team_id."';";
			$status1=$db->query($query1);
			if(!$status1){
				return false;
			}
			else{
				$query2="delete from join where team_id='".$team_id."';";
				$status2=$db->query($query2);
				if(!$status2){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
}
?>