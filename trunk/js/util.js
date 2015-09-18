// JavaScript Document
function getMyDateStr(date)
{
	var str=date.getFullYear()+"-"+(date.getMonth()+1)+"-"+date.getDate();
	return str;
}


function getUrlArg (url, arg) {
	var rs=new RegExp("(^|)"+arg+"=([^\&]*)(\&|$)","gi").exec(url),tmp;
	if(tmp=rs)	{
		return tmp[2];
	}else {
		return undefined;
	}
}

function getArg () {
	var user_id = getUrlArg(window.location.href, 'user_id');
	var user_name = getUrlArg(window.location.href, 'user_name');
	return "?user_id="+user_id+"&user_name="+user_name;
}