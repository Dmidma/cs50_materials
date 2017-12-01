<?php
	
    // configuration
    require("../includes/config.php");
	
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {	
        // render the form
	render("buy.php", ["title" => "Buy"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {	
	
	if (!preg_match("/^\d+$/", $_POST["shares"]))
	{
	    apologize("Invalid number of shares.");
	}
	else
	{
	    $stock = lookup($_POST["symbol"]);
	    // check if the stock does exist
	    if ($stock !== false)
	    {
	        // get the amount of money the current user have
	        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"];
	        
                if ($cash < ($_POST["shares"] * $stock["price"]))
		{
		    // can not afford
		    apologize("You can't afford that.");
		}
		else
		{	
		    // update cash, portfolio and add transaction to history
		    query("START TRANSACTION");
		    query("UPDATE users SET cash = cash - ? WHERE id = ?", ($stock["price"] * $_POST["shares"]), $_SESSION["id"]);
		    query("INSERT INTO stocks (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?" , 
			$_SESSION["id"], strtoupper($stock["symbol"]), $_POST["shares"], $_POST["shares"]);			
		    query("INSERT INTO history (id, datetime, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?, ?)", 
			$_SESSION["id"], date("Y-m-d, h:i:sa"), "BUY", strtoupper($stock["symbol"]), $_POST["shares"], number_format($stock["price"], 2, "." ,","));
		    query("COMMIT");
		}
	    }
	    else
	    {
	        // could not find the stock
	        apologize("Symbol not found.");
	    }
	}

        // go to the main page
        redirect("index.php");
    }
?>
