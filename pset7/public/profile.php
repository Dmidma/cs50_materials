<?php
	
    // configuration
    require("../includes/functions.php");
	
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {	
   	
	$email = query("SELECT email FROM users WHERE id = ?", $_SESSION["id"])[0]["email"];
        // render the form
        render("profile.php", ["email" => $email, "title" => "Profile"]);
        
      
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {	
	if (isset($_POST["email"]) && $_POST["email"] != "noemail")
	{	
	    // change the current user's email
	    query("UPDATE users SET email = ? WHERE id = ?", $_POST["email"], $_SESSION["id"]);

	    // send email to user
	    sendMail($_POST["email"], "Hope your expericen in C$50 Finance is good " . $_SESSION["username"] .".");
	    
	    // unable to link email
	    query("UPDATE users SET email = ? WHERE id = ?", "noemail", $_SESSION["id"]);

	    // apologize
	    apologize('Ooops, an error just occurred. Please relink your email.');
        }
	// unbound email
	else
	{
	    // change the current user's email
	    query("UPDATE users SET email = ? WHERE id = ?", "noemail", $_SESSION["id"]);
	    
 	    // go to the profile again
	    redirect("profile.php");
	}
    }
?>
