<?php
namespace util;
class SecurityMessage{
	public function sendCheckCodeToEmail($loginstr,$email,$checkCode){
		return false;
	}
	
	public function sendCheckCodeToPhone($loginstr,$phone,$checkCode){
		return false;
	}
	
	public function getNewCheckCode(){
		return false;
	}
}
?>