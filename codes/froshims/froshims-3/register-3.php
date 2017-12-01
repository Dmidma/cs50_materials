<?php

	require("PHPMailer/class.phpmailer.php");

	if (!empty($_POST["name"]) && !empty($_POST["gender"]) && !empty($_POST["dorm"]))
	{
		$mail = new PHPMailer();

		$mail->IsSMTP();
		$mail->Host = "smtp.fas.harvard.edu";

		$mail->SetFrom("jharvard@cs50.net");

		$mail->AddAddress("d.oussema.d@gmail.com");

		$mail->Subject = "registration";

		$mail->Body =
			"This person just registered:\n\n" .
			"Name: " . $_POST["name"] . "\n" .
			"Captain: " . $_POST["captain"] . "\n" .
			"Gender: " . $_POST["gender"] . "\n" .
			"Dorm: " . $_POST["dorm"] . "\n";

		if ($mail->Send() == false)
		{
			die($mail->ErrorInfo);
		}
	}
?>


<!DOCTYPE html>
<html>
<head>
	<title>Frosh IMs</title>
</head>
<body>
	<?php if (empty($_POST["name"]) || empty($_POST["gender"]) || empty($_POST["dorm"])): ?>
		You must provide your name, gender, and dorm! Go <a href="froshims-3.php">back</a>.
	<?php else: ?>
		You are registered! (really.)
	<?php endif ?>
</body>
</html>