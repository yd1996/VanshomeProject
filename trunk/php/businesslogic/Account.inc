<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/dbConfig/dbconfig.php');
class Account{
	public function getTotalCondition($user_id){
		$allItem=$this->listAllItem($user_id);
		$incomeItem=$this->listAllIncomeItem($user_id);
		$paymentItem=$this->listAllPaymentItem($user_id);
		$checkStatus1=$this->checkItems($allItem);
		$checkStatus2=$this->checkItems($incomeItem);
		$checkStatus3=$this->checkItems($paymentItem);
		$result=array('income'=>0,'payment'=>0,'total'=>0);
		if($checkStatus1){
			return json_encode($result);
		}
		if($checkStatus2){
			$itemarray=json_decode($incomeItem);
			$count=count($itemarray);
			for($i=0;$i<$count;$i++){
				if($itemarray[$i]['is_score']==1){
					$result['income']=$result['income']+$itemarray[$i]['reward_number'];
					$result['total']=$result['total']+$itemarray[$i]['reward_number'];
				}
			}
		}
		if($checkStatus3){
			$itemarray=json_decode($paymentItem);
			$count=count($itemarray);
			for($i=0;$i<$count;$i++){
				if($itemarray[$i]['is_score']==1){
					$result['payment']=$result['payment']+$itemarray[$i]['reward_number'];
					$result['total']=$result['total']-$itemarray[$i]['reward_number'];
				}
			}
		}
		return json_encode($result);
	}
	
	private function checkItems($item){
		if($item==-1||$item==false){
			return false;
		}
		else{
			return true;
		}
	}
	
	public function listAllItem($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select account_item.item_id,item_time,task_id,task_type,task_small_type,
			        task_content,is_income,role,is_score,reward_content,reward_number,negotient_id,
					negotient_name
					from account,account_item
					where account.item_id=account_item.item_id and user_id='".$user_id."';";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('item_id'=>$row['item_id'],'item_time'=>$row['item_time'],
					             'task_id'=>$row['task_id'],'task_type'=>$row['task_type'],
								 'task_small_type'=>$row['task_small_type'],
								 'task_content'=>$row['task_content'],'is_income'=>$row['is_income'],
								 'role'=>$row['role'],'reward_content'=>$row['reward_content'],
								 'reward_number'=>$row['reward_number'],
								 'negotient_id'=>$row['negotient_id'],
								 'negotient_name'=>$row['negotient_name'],
								 'is_score'=>$row['is_score']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function listAllIncomeItem($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select account_item.item_id,item_time,task_id,task_type,task_small_type,
			        task_content,is_income,role,reward_content,reward_number,negotient_id,
					negotient_name,is_score
					from account,account_item
					where account.item_id=account_item.item_id and user_id='".$user_id."' 
					and is_income=1;";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('item_id'=>$row['item_id'],'item_time'=>$row['item_time'],
					             'task_id'=>$row['task_id'],'task_type'=>$row['task_type'],
								 'task_small_type'=>$row['task_small_type'],
								 'task_content'=>$row['task_content'],'is_income'=>$row['is_income'],
								 'role'=>$row['role'],'reward_content'=>$row['reward_content'],
								 'reward_number'=>$row['reward_number'],
								 'negotient_id'=>$row['negotient_id'],
								 'negotient_name'=>$row['negotient_name'],
								 'is_score'=>$row['is_score']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function listAllPaymentItem($user_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select account_item.item_id,item_time,task_id,task_type,task_small_type,
			        task_content,is_income,role,reward_content,reward_number,negotient_id,
					negotient_name,is_score
					from account,account_item
					where account.item_id=account_item.item_id and user_id='".$user_id."' 
					and is_income=0;";
			$result=$db->query($query);
			$num_results=$result->num_rows;
			if($num_results==0){
				return false;
			}
			else{
				$output=array();
				for($i=1;$i<=$num_results;$i++){
					$row=$result->fetch_assoc();
					$value=array('item_id'=>$row['item_id'],'item_time'=>$row['item_time'],
					             'task_id'=>$row['task_id'],'task_type'=>$row['task_type'],
								 'task_small_type'=>$row['task_small_type'],
								 'task_content'=>$row['task_content'],'is_income'=>$row['is_income'],
								 'role'=>$row['role'],'reward_content'=>$row['reward_content'],
								 'reward_number'=>$row['reward_number'],
								 'negotient_id'=>$row['negotient_id'],
								 'negotient_name'=>$row['negotient_name'],
								 'is_score'=>$row['is_score']);
					array_push($output,$value);
				}
				return json_encode($output);
			}
		}
	}
	
	public function queryDetail($item_id){
		global $DB_NAME;
	    global $DB_HOST;
	    global $DB_USER;
	    global $DB_PASSWORD;
		@ $db=new mysqli($DB_HOST,$DB_USER,$DB_PASSWORD,$DB_NAME);
		if(mysqli_connect_errno()){
			return -1;
		}
		else{
			$query="select * from account_item where item_id='".$item_id."';";
			$result=$db->query($query);
			$row=$result->fetch_assoc();
			$value=array('item_id'=>$row['item_id'],'item_time'=>$row['item_time'],
					     'task_id'=>$row['task_id'],'task_type'=>$row['task_type'],
						 'task_small_type'=>$row['task_small_type'],
						 'task_content'=>$row['task_content'],'is_income'=>$row['is_income'],
						 'role'=>$row['role'],'reward_content'=>$row['reward_content'],
						 'reward_number'=>$row['reward_number'],
						 'negotient_id'=>$row['negotient_id'],
						 'negotient_name'=>$row['negotient_name'],
						 'is_score'=>$row['is_score']);
			return json_encode($value);
		}
	}
	
}
?>