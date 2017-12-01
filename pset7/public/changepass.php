<?php
	
    // configuration
    require("../includes/config.php");
	
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {	
   	// go to profile
	redirect("profile.php");
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {	
	if (isset($_POST["password"]) || isset($_POST["confirmation"]))
	{
	    if (empty($_POST["password"]))
            {
                apologize("You must provide your password.");
            }
	    else if ($_POST["password"] != $_POST["confirmation"])
	    {
		apologize("Password does not match.");
	    }
	    else
	    {
		// change pass
		query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]);
		
		// redirect portfolio
		redirect("/");
	    }
	}
	else
	{
	    // render form
	    render("changepass.php", ["title" => "Change Password"]);
	}
    }
?>
