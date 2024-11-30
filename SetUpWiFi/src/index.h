#ifndef INDEX_H
#define INDEX_H

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Set WiFi</title>
	<style>
		body {
			background-color: #9f9da7;
			font-size: 1.6rem;
			font-family: "Open Sans", sans-serif;
			color: #2b3e51;
		}

		h2 {
			font-weight: 300;
			text-align: center;
		}

		p {
			position: relative;
		}

		a,
		a:link,
		a:visited,
		a:active {
			color: #3ca9e2;
			-webkit-transition: all 0.2s ease;
			transition: all 0.2s ease;
		}

		a:focus,
		a:hover,
		a:link:focus,
		a:link:hover,
		a:visited:focus,
		a:visited:hover,
		a:active:focus,
		a:active:hover {
			color: #329dd5;
			-webkit-transition: all 0.2s ease;
			transition: all 0.2s ease;
		}

		#login-form-wrap {
			background-color: #fff;
			width: 35%;
			margin: 30px auto;
			text-align: center;
			padding: 20px 0 0 0;
			border-radius: 4px;
			box-shadow: 0px 30px 50px 0px rgba(0, 0, 0, 0.2);
			padding: 10px 0;
		}

		#login-form {
			padding: 0 60px;
		}

		input {
			display: block;
			box-sizing: border-box;
			width: 100%;
			outline: none;
			height: 60px;
			line-height: 60px;
			border-radius: 4px;
		}

		input[type="text"],
		input[type="password"] {
			width: 100%;
			padding: 0 0 0 10px;
			margin: 0;
			color: #8a8b8e;
			border: 1px solid #c2c0ca;
			font-style: normal;
			font-size: 16px;
			-webkit-appearance: none;
			-moz-appearance: none;
			appearance: none;
			position: relative;
			display: inline-block;
			background: none;
		}

		input[type="text"]:focus,
		input[type="email"]:focus {
			border-color: #3ca9e2;
		}

		input[type="text"]:focus:invalid,
		input[type="email"]:focus:invalid {
			color: #cc1e2b;
			border-color: #cc1e2b;
		}

		input[type="text"]:valid~.validation,
		input[type="email"]:valid~.validation {
			display: block;
			border-color: #0C0;
		}

		input[type="text"]:valid~.validation span,
		input[type="email"]:valid~.validation span {
			background: #0C0;
			position: absolute;
			border-radius: 6px;
		}

		input[type="text"]:valid~.validation span:first-child,
		input[type="email"]:valid~.validation span:first-child {
			top: 30px;
			left: 14px;
			width: 20px;
			height: 3px;
			-webkit-transform: rotate(-45deg);
			transform: rotate(-45deg);
		}

		input[type="text"]:valid~.validation span:last-child,
		input[type="email"]:valid~.validation span:last-child {
			top: 35px;
			left: 8px;
			width: 11px;
			height: 3px;
			-webkit-transform: rotate(45deg);
			transform: rotate(45deg);
		}

		.validation {
			display: none;
			position: absolute;
			content: " ";
			height: 60px;
			width: 30px;
			right: 15px;
			top: 0px;
		}

		input[type="submit"] {
			border: none;
			display: block;
			background-color: #3ca9e2;
			color: #fff;
			font-weight: bold;
			text-transform: uppercase;
			cursor: pointer;
			-webkit-transition: all 0.2s ease;
			transition: all 0.2s ease;
			font-size: 18px;
			position: relative;
			display: inline-block;
			cursor: pointer;
			text-align: center;
		}

		input[type="submit"]:hover {
			background-color: #329dd5;
			-webkit-transition: all 0.2s ease;
			transition: all 0.2s ease;
		}

		@media (max-width:576px) {
			#login-form-wrap {
				width: 90%;
			}
		}
	</style>
</head>

<body>
	<div id="login-form-wrap">
		<h2>Set WiFi</h2>
		<form id="login-form">
			<p>
				<input type="text" id="ssid" name="ssid" placeholder="SSID" required><i
					class="validation"><span></span><span></span></i>
			</p>
			<p>
				<input type="password" id="pass" name="pass" placeholder="Password" required><i
					class="validation"><span></span><span></span></i>
			</p>
			<p>
				<input type="submit" id="login" value="Set">
			</p>
		</form>
	</div>
	<script>
		document.getElementById('login').addEventListener('click', function (e) {
			e.preventDefault();
			const ssid = document.getElementById('ssid').value;
			const password = document.getElementById('pass').value;
			if (!ssid || !password) {
				alert("Vui lòng nhập SSID và mật khẩu.");
				return;
			}
			fetch("/getwifi", {
				method: 'POST',
				headers: {
					"Content-Type": "application/x-www-form-urlencoded"
				},
				body: `ssid=${encodeURIComponent(ssid)}&password=${encodeURIComponent(password)}`
			})
				.then(response => response.text())
				.then(data => {
					alert(data);
					window.open('', '_self');
					window.close();
				})
				.catch(error => {
					alert("Có lỗi xảy ra. Vui lòng thử lại.");
					console.log(error);
				});
		})
	</script>
</body>

</html>
)rawliteral";
#endif