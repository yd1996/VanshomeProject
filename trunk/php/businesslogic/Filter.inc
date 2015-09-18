<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Filter{
	public function retrieveAllTask(){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from task";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$item=array('task_id'=>$row['task_id'],'publish_time'=>$row['publish_time'],
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
					array_push($output,$item);
				}
				return $output;
			}
		}
	}
	public function filterByModuleType($data,$module_type){
		if($module_type==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			for($i=0;$i<$count;$i++){
				if($data[$i]['module_type']==$module_type){
					array_push($output,$data[$i]);
				}
			}
			return $output;
		}
	}
	
	//0全部 1单人悬赏 2多人悬赏
	public function filterByTaskType($data,$value){
		if($value==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			for($i=0;$i<$count;$i++){
				if($data[$i]['task_type']==$value){
					array_push($output,$data[$i]);
				}
			}
			return $output;
		}
	}
	//0全部 1悬赏中 2截止日期结束 3悬赏完成 4悬赏失败
	public function filterByTaskState($data,$value){
		if($value==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			for($i=0;$i<$count;$i++){
				if($data[$i]['state']==$value){
					array_push($output,$data[$i]);
				}
			}
			return $output;
		}
	}
	//0全部 1积分 2金钱 3物品 4其他
	public function filterByRewardType($data,$value){
		if($value==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			if($count==0){
				return false;
			}
			for($i=0;$i<$count;$i++){
				if($data[$i]['reward_type']==$value){
					array_push($output,$data[$i]);
				}
			}
			return $output;
		}
	}
	//0全部 1已托管 2未托管
	public function filterByRewardState($data,$value){
		if($value==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			for($i=0;$i<$count;$i++){
				if($data[$i]['reward_state']==(2-$value)){
					array_push($output,$data[$i]);
				}
			}
			return $output;
		}
	}
	//0全部 1男 2女
	public function filterBySex($data,$value){
		if($value==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			for($i=0;$i<$count;$i++){
				if($data[$i]['is_man']==(2-$value)){
					array_push($output,$data[$i]);
				}
			}
			return $output;
		}
	}
	//0全部 1同城 2同校 3同校同院
	public function filterByMatchType($data,$value,$city,$school,$institute){
		if($value==0){
			return $data;
		}
		else{
			$output=array();
			$count=count($data);
			if($value==1){
				for($i=0;$i<$count;$i++){
					if($data[$i]['city']==$city){
						array_push($output,$data[$i]['city']);
					}
				}
			}
			else if($value==2){
				for($i=0;$i<$count;$i++){
					if($data[$i]['school']==$school){
						array_push($output,$data[$i]['city']);
					}
				}
			}
			else if($value==3){
				for($i=0;$i<$count;$i++){
					if($data[$i]['school']==$school&&$data[$i]['institute']==$institute){
						array_push($output,$data[$i]['city']);
					}
				}
			}
			return $output;
		}
	}
}
?>