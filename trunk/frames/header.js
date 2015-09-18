
document.write("\
	<div style='background: #444444' id='header'>\
        <div class='header' id='header_out'>\
            <div class='user-wrap-left'>Hi，欢迎你来到本网站</div>\
            <div class='user-wrap'>\
                <a href='login.html'　target='center'>登陆</a>\
                <a href='register.html' target='center'>注册</a>\
                <a href='findCode.html' target='center'>忘记密码？</a>\
                <a href='navigation.html' target='center'>导航</a>\
            </div>\
        </div>\
		<div class='header' id='header_in' style='display:none;'>\
			<div class='user-wrap-left'></div>\
			<div class='user-wrap'>\
				<div id='user_top_right'></div>\
				<a href='navigation.html'></a>\
				<a id='logout' href='login.html'>注销</a>\
			</div>\
		</div>\
    </div>\
");

