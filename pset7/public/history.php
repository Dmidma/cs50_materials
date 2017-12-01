<?php
	
    // configuration
    require("../includes/config.php");
	
    // fetch the history of the current user
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
   
    $positions = [];
    foreach ($rows as $row)
    {
	$positions[] = [
            "transaction" => $row["transaction"],
            "datetime" => $row["datetime"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"]
        ];
    }

    // render the form
    render("history.php", ["positions" => $positions, "title" => "History"]);

?>
