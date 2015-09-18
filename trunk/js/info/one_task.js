$(document).ready(function () {

});

function get_task_apply(task_id) {
/*
	 var a = '[{"user_name":"找校园卡!", "note":"物品","apply_dcrt":"昨天六食堂掉了一张校园卡...", '+
	 	'"apply_time":"2014-3-5",apply_state":"审标中"},'+
	 	' {"user_name":"找校园卡!", "note":"物品","apply_dcrt":"昨天六食堂掉了一张校园卡...", '+	
	 	'"apply_time":"2014-3-5", "apply_state":"审标中"}]';
	  	alert("NI mei");
	 	alert(eval(a));
	 	change_apply_html(eval(a));
		*/
		$.ajax({
		url: '../php/ajax/task_info.php?action=get_application_of_task',
		type: 'POST',
		dataType: 'json',
		data: {"task_id": task_id},
		success:function (json) {
			myjson = eval(json);
			if (myjson.success==0) {
				alert(myjson.msg);
			}else {
				var r= myjson.result;
				alert(" sdsd:"+eval(r));
				change_apply_html(eval(r));
			}
		},
		error:function (xhr, textStatus, error) {
			alert("错误类型:"+textStatus+"; 错误方式:"+error);
			document.write(xhr.responseText);
		}
		
	});
}

function get_task_content (uid, task_id) {

	$.ajax({
		asyc:false,
		url: '../php/ajax/task_info.php?action=task_detail',
		type: 'POST',
		dataType: 'json',
		data: {"task_id": task_id, "user_id":uid},
		success:function (json) {
			var myjson = eval(json);
			if (myjson.success==0) {
				alert("数据库连接异常！");
				return;
			}else {
				if (myjson.msg == '不具备查看任务详细信息的条件') {
					alert(myjson.msg);
					return;
				}
			}

			change_task_html(eval("("+myjson.result+")"));
		},
		error:function (xhr, textStatus, error) {
			alert("错误类型:"+textStatus+"; 错误方式:"+error);
			document.write(xhr.responseText);
		}
	});
	
/*	
*/

}

function change_apply_html (data) {
	var text = "";
	for (var i=0,value; value=data[i++];) {
		text += get_one_apply(value);
	}

	$("#apply_mng").html(text);
}

function get_one_apply (apply) {
	$(".apply_name").text(apply.user_name);
	$(".apply_dcrt").text(apply.note);
	$(".apply_time").text(apply.apply_time);
	$(".apply_state").text(apply.apply_state);

	return $("#apply_model").html();
} 

function change_task_html (data) {
	var task_type;
	
	if (data.task_type == 1) {
		task_type="单人悬赏";
	}else if (data.task_type == 2) {
		task_type = "多人悬赏";
	}else {
		task_type = "无法识别的方式";
	}

	var reward_type;
	var reward_value;
	if (data.reward_type == 1) {
		reward_type = "积分";
		reward_value = data.reward_number+" 积分";
	}else if (data.reward_type == 2) {
		reward_type = "金钱";
		reward_value = data.reward_number+"元";
	}else if (data.reward_type == 3) {
		reward_type = "物品";
		reward_value = data.goods_type;
	}else {
		reward_type = "无法识别的类型";
	}

	var want_agent;
	if (data.reward_state) {
		want_agent = "已托管";
	}else {
		want_agent = "未托管";
	}
	
	$("#task_title").text(data.task_title);
	$("#task_ddl").text(data.deadline);
	$("#task_dcrt").text(data.description);
	$("#reward_type").text(reward_type);
	$("#task_type").text(task_type);
	$("#reward_dcrt").text(data.reward_note);
	$("#reward_value").text(reward_value);

}