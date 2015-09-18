<?php
namespace bl;
class Publish{
	public function listAllToPublish($user_id){
		return false;
	}
	
	public function showTheDetail($task_id){
		return false;
	}
	
	public function setBasicInfo($basic_info){
		return false;
	}
	
	public function save($user_id){
		return false;
	}
	
	public function modifyContent($task_id,$content){
		return false;
	}
	
	public function publishBufferTask($buffer_task_id){
		return false;
	}
	
	public function publishNewTask($basic_info){
		return false;
	}
	
	public function invite($task_id,$client_id){
		return false;
	}
	
	//0表示成功，1表示失败
	public function endTask($task_id,$state){
		return false;
	}
}
?>