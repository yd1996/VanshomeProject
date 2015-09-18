<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
require($root_path.'/businesslogic/Score.inc');
class Accept{
	public function listAllApplication($task_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task_apply.user_id,user_name,apply_time,note
			        from task_apply,user
					where task_apply.user_id=user.user_id
					and task_id='".$task_id."' and state=0;";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('user_id'=>$row['user_id'],
					             'user_name'=>$row['user_name'],
								 'apply_time'=>$row['apply_time'],
								 'note'=>$row['note']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	//task_apply中state为1时候为执行中，3时候为已拒绝,这里相当于入围
	public function accept($task_id,$user_id){
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
			        set state=1
					where task_id='".$task_id."' and user_id='".$user_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	public function deny($task_id,$user_id){
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
			        set state=3
					where task_id='".$task_id."' and user_id='".$user_id."';";
			$result=$db->query($query);
			if(!$result){
				return false;
			}
			else{
				return true;
			}
		}
	}
	
	//入围,4代表最终采纳,百分之十的总分
	public function acceptFinally($task_id,$user_id,$author_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="update task_apply
			        set state=4
					where task_id='".$task_id."' and user_id='".$user_id."';";
			$query2="update task_apply
			        set state=2
					where  task_id='".$task_id."' and state=1 and user_id<>'".$user_id."';";
			$query3="select user_id from task_apply where state=1 and task_id='".$task_id."';";
			$db->query($query1);
			$db->query($query2);
			$result=$db->query($query3);
			$query4="select reward_number from task where task_id='".$task_id."';";
			$row0=$db->query($query4)->fetch_assoc();
			$score=$row0['reward_number'];
			$scoreManage=new Score();
			$num_results=$result->num_rows;
			if($num_results!=0){
				for($i=0;$i<$num_results;$i++){
					$row=$result->fetch_assoc();
					$scoreManage->add($row['user_id'],$score*0.1);
					$scoreManage->sub($author_id,$score*0.1);
				}	
			}
			$scoreManage->add($user_id,$score);
			$scoreManage->sub($author_id,$score);
			$query5="update task set reward_state=0 where task_id='".$task_id."';";
			$db->query($query);
			return true;
		}
	}
}
?>