
function init_apply_task (task_id) {
	$.ajax({
		url: '/path/to/file',
		type: 'default GET (Other values: POST)',
		dataType: 'default: Intelligent Guess (Other values: xml, json, script, or html)',
		data: {param1: 'value1'},
	});


}

function change_apply_list (data) {
	for (var i=0,value; value=data[i++];) {
		text += get_apply_txt(value);
	}
	$("#task_list").html(text);
}

function get_apply_txt (one_task) {
	$(".publisher_name").text();
	$(".task_title").text();
	$(".reward_type").text();
	$(".reward_value").text();
	$(".state").text();
	$(".apply_time").text();
}