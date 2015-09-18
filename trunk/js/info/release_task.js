// JavaScript Document
// $(document).ready(function () {
// 	$("#last_page").click(function () {
		
// 	});
	
// 	$("#next_page").click(function () {
		
// 	});
// 	alert("YYYYY");
// });

function get_first_task_list (user_id) {

	if (user_id==undefined) {
		alert("请登录后重试!");
		window.location.href = "../login.html";
	}
	
	$.ajax({
		async:false,
		type:"POST",
		url:"../php/ajax/task_info.php?action=list_published",
		dataType:"json",
		data:{"user_id":user_id},
		success: function (json) {
			var result;
			
			json = eval(json);
			if (json.success==0) {
				alert(json.msg);
			}else if (json.success==1) {
				if (json.result=="none") {
					change_task_list_empty();
				}else {
					result = json.result;
					change_task_list(user_id, eval("("+result+")"));
				}
			}else {
				alert("Error.");
			}
		},
		
		error: function (xhr, status, error) {
			alert("\nerror:"+status);
			document.write(xhr.responseText);
		}
	});

	/*test code*/
	
	// var a = '[{"task_title":"找校园卡!", "goods_type":"物品", "reward_note":"二手手表一只！", "description":"昨天六食堂掉了一张校园卡...", '+
	// 	'"publish_time":"2014-3-5", "task_id":"0x00001"}, {"task_title":"找校园卡!", "goods_type":"物品", "reward_note":"二手手表一只！", "description":"昨天六食堂掉了一张校园卡...", '+
	// 	' "publish_time":"2014-3-5", "task_id":"0x00002"}]';
	// change_task_list(eval(a));

}

 function change_task_list_empty () {
 	$("#task_list").html('<h1 class="no_task">没有任务</h1>');	
 }

function change_task_list (user_id, data) {
	var text="";
	
	for (var i=0,value;value=data[i++];) {
		text += get_task_text(user_id, eval(value));
	}
	
	$("#task_list").html(text);
}

function get_task_text (user_id, task) {
	var str = "";
	$(".title_txt").text(task.task_title);
	$(".state_txt").text("奖励类型:"+task.goods_type+" 奖励内容:"+task.reward_note);
	$(".content_txt").text(task.description);
	$(".time_txt").text(task.publish_time);
	$(".title_txt").attr({
		href: 'one_task.html?task_id='+task.task_id+'&user_id='+user_id
	});
	str = $("#item_model").html();
	return str;	
}
