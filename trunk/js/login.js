

$(document).ready(function () {	
		$("#logout").click(function () {
			$.get("php/ajax/login.php?action=logout", function () {
				$("#head_in").css("display", "none");
				$("#head_out").css("display", "block");
				document.getElementById("head_in").innerHTML="";
				user_id="";
			});
		});
		
		$(".login_btn").click(function () {
			
			var name = document.getElementById("user_name").value;
			var password = document.getElementById("password").value;
			user_name = name;
			
			if (name == "") {
				alert("请输入用户名!");
				$("#user_name").focus();
				return false;
			}
			if (password=="") {
				alert("请输入密码！");
				$("#password").focus();
				return false;
			}
			var result=false;
			$.ajax({
				async:false,
				type: "POST",
				url: "php/ajax/login.php?action=login",
				dataType: "json",
				data: {"username":name, "password":password},
				beforeSend: function () {
					
				},
				success: function (json) {
					var myjson=eval(json);
					user_id=myjson.user_id;
					user_name=myjson.user_name;
					
					$("#header_in").css("display", "block");
					$("#header_out").css("display", "none");
					$("#user_top_right").html("");
					$("#user_top_right").prepend("<a href='info/info.html'>"+myjson.user_name+"</a>");
					setCookie('user_name', '', 'user_id', '', -1);
					setCookie("user_name", user_name, "user_id", user_id, 1);
					
					window.location.href="index3.html?user_id="+user_id+"&user_name="+user_name; 
				},
				error: function(XMLHttpRequest, textStatus, errorThrown) {
                        alert("xhr.status:"+XMLHttpRequest.status+"; xhr.readyState:"+XMLHttpRequest.readyState
						+"; error_type:"+textStatus);
                        document.write(XMLHttpRequest.responseText);
				
                }
			});
			return result;
		});
});