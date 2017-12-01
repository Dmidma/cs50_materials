<?php
	if (empty($_POST["name"]) || empty($_POST["gender"]) || empty($_POST["dorm"]))
	{
		header("Location: http://192.168.66.128/froshims-1.php");
		exit;
	}
?>

<!DOCTYPE html>
<html>
<head>
	<title>Frosh IMs</title>
</head>
<body>
	You are registered! (Not really.)
</body>
</html>