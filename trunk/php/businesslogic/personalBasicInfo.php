<?php
namespace bl;
class PersonalBasicInfo{
	public function getBasicInfo($user_id){
		return false;
	}
	
	public function modifyBasicInfo($basic_info){
		return false;
	}
	
	public function getDefaultSecurityInf($user_id){
		return false;
	}
	
	public function ensureDeleteDefaultPhone($user_id){
		return false;
	}
	
	public function deleteDefaultPhone($user_id,$checkCode){
		return false;
	}
	
	public function ensureModifyDefaultPhone($user_id,$newPhone){
		return false;
	}
	
	public function modifyDefaultPhone($user_id,$checkCode){
		return false;
	}
	
	public function ensureDeleteDefaultEmail($user_id){
		return false;
	}
	
	public function deleteDefaultEmail($user_id,$checkCode){
		return false;
	}
	
	public function ensureModifyDefaultEmail($user_id){
		return false;
	}
	
	public function modifyDefaultEmail($user_id,$checkCode){
		return false;
	}
	
	public function getPersonalInterest($user_id){
		return false;
	}
	
	public function modifyPersonalInterest($user_id,$value){
		return false;
	}
	
	public function getPersonalEducation($user_id){
		return false;
	}
	
	public function modifyPersonalEducation($user_id,$value){
		return false;
	}
}
	
?>