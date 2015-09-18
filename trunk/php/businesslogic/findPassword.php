<?php
namespace bl;
class FindPassword{
	public function findPasswordByDefaultPhone($loginstr){
		return false;
	}
	
	public function findPasswordByDefaultEmail($loginstr){
		return false;
	}
	
	public function modifyPassword($loginstr,$checkCode,$password){
		return false;
	}
}
?>