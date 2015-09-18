<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
require($root_path.'/businesslogic/Query.inc');
class TeamMemberManage{
	public function getTeamAllMemberInfo($team_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select user_id,user_name,person_note,
			           icon_str,user_level,honor,is_identified
					from user
					where user_id=any(select user_id from join
					                  where team_id=".$team_id."')";
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
					             'person_note'=>$row['person_note'],'icon_str'=>$row['icon_str'],
								 'user_level'=>$row['user_level'],'honor'=>$row['honor'],
								 'is_identified'=>$row['is_identified']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function getTeamMemberDetail($member_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query=new Query();
			$result=$query->queryPersonalUser($member_id);
			if($result==false){
				return false;
			}
			else{
				return $result;
			}
		}
	}
	
	public function inviteTeamMembers($user_id,$team_id,$member_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="insert into invite_to_join(user_id,invitor_id,team_id)
			             value('".$user_id."','".$team_id."','".$member_id."')";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function deleteTeamMembers($team_id,$member_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="delete from join where team_id='".$team_id."' and user_id='".$member_id."'";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function addManagers($team_id,$member_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update join set is_manager=1 where team_id='".$team_id
			        ."' and user_id='".$member_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function deleteManagers($team_id,$member_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="update join set is_manager=0 where team_id='"
			        .$team_id."' and user_id='".$member_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function changeLeader($team_id,$leader_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="udpate join set is_leader=0 where team_id='".$team_id."' and is_leader=1;";
			$query2="update join set is_leader=1 where team_id='".$team_id.
			        "' and user_id='".$leader_id."';";
			$result1=$db->query($query1);
			$result2=$db->query($query2);
			$result=$result1&$result2;
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