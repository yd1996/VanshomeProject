// JavaScript Document

$(document).ready(function() {
	$("#basic_info").click(function () {
		$("#right_content").attr("src", "basic_info.html"+getArg());
	});
		
	$("#connect_way").click(function () {
		$("#right_content").attr("src", "connect_way.html"+getArg());
	});
	
	$("#code_modify").click(function () {
		$("#right_content").attr("src", "code_modify.html"+getArg());
	});
	
	$("#release_task_mng").click(function () {
		$("#right_content").attr("src", "release_task_mng.html"+getArg());
	});
	
	$("#apply_task_mng").click (function () {
		$("#right_content").attr("src", "apply_task_mng.html"+getArg());
	});
	
	$("#team_mng").click(function () {
		$("#right_content").attr("src", "current_team.html"+getArg());
	});
	
	$("#current_team").click (function () {
		$("#right_content").attr("src", "current_team.html"+getArg());
	});
	
	$("#create_team").click (function () {
		$("#right_content").attr("src", "create_team.html"+getArg());
	});
	
	$("#join_team").click (function () {
		$("#right_content").attr("src", "join_team.html"+getArg());
	});
	
	$("#collection").click(function () {
		$("#right_content").attr("src", "collection.html"+getArg());
	});
	
	$("#care").click(function () {
		$("#right_content").attr("src", "care.html"+getArg());
	});
	
	$("#msg_center").click(function () {
		$("#right_content").attr("src", "msg_center.html"+getArg());
	});
	
	
	$("dd").mouseenter(function () {
		$(this).css({"text-decoration":"underline"});
	});
	$("dd").mouseleave(function () {
		$(this).css({"text-decoration":"none"});
	});

});