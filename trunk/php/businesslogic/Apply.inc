<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Apply{
	//$content包括申请时间，申请备注
	public function applyTask($user_id,$task_id,$content){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$info=json_decode($content,true);
			$query="insert into task_apply(user_id,task_id,state,apply_time,note,file_id)
			       value('".$user_id."','".$task_id."',0,'".$info['apply_time']."','"
				   .$info['note']."',0);";//缺了些什么东西
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
			$query1="select * from task_apply
			        where user_id='".$user_id."' and task_id='".$task_id."';";
			$result1=$db->query($query1);
			$num_results1=$results1->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$row=$result1->fetch_assoc();
				if($row['state']==2){
					return false;
				}
				else{
					$query2="delete from task_apply
					        where task_id='".$task_id."' and user_id='".$user_id."';";
					$result2=$db->query($query2);
					if(!$result2){
						return false;
					}
					else{
						return true;
					}
				}
			}
		}
	}
	
	//入围后提供完整解决方案，迭代一中不包括相关文件
	public function submit($user_id,$task_id,$solution){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query1="select * from task_apply
			        where user_id='".$user_id."' and task_id='".$task_id."';";
			$result1=$db->query($query1);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$query2="update task_apply set solution='".$solution
				        ."' where user_id='".$user_id."' and task_id='".$task_id."';";
				$result2=$db->query($query2);
				if(!$result2){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
	
	//入围后修改解决方案，迭代一中不包括相关文件
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
			$query1="select * from task_apply
			       where user_id='".$user_id."' and task_id='".$task_id."';";
			$result1=$db->query($query);
			$num_results=$result1->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$query2="update task_apply set solution='".$solution."' where 
				        user_id='".$user_id."' and task_id='".$task_id."';";
				$result2=$db->query($query2);
				if(!$result2){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
	
	public function listAllApplication($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select task_id,task_title,owner_id,owner_name,deadline,task_type,
			            state,description,module,module_type,social_detail,
						reward_type,goods_type,reward_note,reward_number,reward_state
					from task
					where task_id=any(select task_id from task_apply where user_id='".$user_id."');";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('task_id'=>$row['task_id'],'task_title'=>$row['task_title'],
					             'owner_id'=>$row['owner_id'],'owner_name'=>$row['owner_name'],
								 'deadline'=>$row['deadline'],'task_type'=>$row['task_type'],
								 'state'=>$row['state'],'description'=>$row['description'],
								 'module'=>$row['module'],'module_type'=>$row['module_type'],
								 'social_detail'=>$row['social_detail'],
								 'reward_type'=>$row['reward_type'],'goods_type'=>$row['goods_type'],
								 'reward_note'=>$row['reward_note'],
								 'reward_number'=>$row['reward_number'],
								 'reward_state'=>$row['reward_state']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
}
?>