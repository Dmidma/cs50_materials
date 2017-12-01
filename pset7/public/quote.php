<?php
	
	// configuration
	require("../includes/functions.php");
	
	// if user reached page via GET (as by clicking a link or via redirect)
	if ($_SERVER["REQUEST_METHOD"] == "GET")
    	{
        	// else render form
	        render("quote_form.php", ["title" => "Get Quote"]);
	}
    	// else if user reached page via POST (as by submitting a form via POST)
	else if ($_SERVER["REQUEST_METHOD"] == "POST")
    	{	
		// store the name, symbol and price of a stock in an associative array
		$stock = lookup($_POST["symbol"]);
		
		// check if the stock does exist
		if ($stock !== false)
		{	
			render("quote.php", ["stock" => $stock, "title" => "Quote"]);
		}
		else
		{
			// could not find the stock
			apologize("Symbol not found.");
		}
    }
?>
