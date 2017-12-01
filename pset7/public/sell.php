<?php
	
    // configuration
    require("../includes/config.php");
	
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {	
        // fetch the stocks of the current user from database
        $rows = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);
		
        if (count($rows) != 0)
        {   
            $positions = [];
            foreach ($rows as $row)
            {
                $positions[] = [
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"],
                ];
            }
            // render the form
            render("sell.php", ["positions" => $positions, "title" => "Sell"]);
        }
        // the current users does not have any stocks to sell
        else
        {
            apologize("Nothing to sell.");
        }
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {	
	
	// get the price of the stock
	$price = lookup($_POST["symbol"])["price"];
        // get the number of shares
        $shares = query("SELECT shares FROM stocks where id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"])[0]["shares"];
	
	// delete the stocks, update the amount of cash and add the transaction to history
	query("START TRANSACTION;");
	query("DELETE FROM stocks WHERE id = ? AND symbol = ?;", $_SESSION["id"], $_POST["symbol"]);
	query("UPDATE users SET cash = cash + ? WHERE id = ?", ($price * $shares), $_SESSION["id"]);
	query("INSERT INTO history (id, datetime, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?, ?)", 
	    $_SESSION["id"], date("Y-m-d, h:i:sa"), "SELL", strtoupper($_POST["symbol"]), $shares, number_format($price, 2, "." ,","));
	query("COMMIT");
	
        // go to the main page
        redirect("index.php");
    }
?>
