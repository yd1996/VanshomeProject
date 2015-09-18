function check_login () {
	if (typeof(user_id) == "undefined" || typeof(user_name)=="undefined") {
		return false;
	}
	
	if (user_id=='undefined' || user_name=='undefined') {
		return false;
	}

	$("#header_in").css("display", "block");
	$("#header_out").css("display", "none");
	$("#user_top_right").html("");
	$("#user_top_right").prepend("<a href='info/info.html?user_id="+user_id+"&user_name="+user_name+"'"+">"+user_name+"</a>");

	return true;
}

function getCookie(c_name)
{
if (document.cookie.length>0)
{ 
c_start=document.cookie.indexOf(c_name + "=")
if (c_start!=-1)
{ 
c_start=c_start + c_name.length+1 
c_end=document.cookie.indexOf(";",c_start)
if (c_end==-1) c_end=document.cookie.length
return unescape(document.cookie.substring(c_start,c_end))
} 
}
return ""
}

function setCookie(c_name,value, c_id, id,expiredays)
{
var exdate=new Date()
exdate.setDate(exdate.getDate()+expiredays)
document.cookie=c_name+ "=" +escape(value)+";"+c_id+"="+escape(id)+
((expiredays==null) ? "" : "; expires="+exdate.toGMTString())
}

function checkCookie()
{
user_name=getCookie('user_name');
user_id=getCookie('user_id');
if (user_name !=null && user_id !=null && user_name!="" && user_id!="") {
	alert("已经登录！");
}else {
	alert("尚未登录...");
}

}

function test () {
	alert("test ref");
}