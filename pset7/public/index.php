<?php

    // configuration
    require("../includes/config.php"); 
    
    
    // store all stocks of the current user
    $rows = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);
   
   
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => number_format($stock["price"] * $row["shares"], 2, "." ,",")
            ];
       }
    }

    // amount of money the current user have
    $money = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    // first (and only) row				
    $cash = number_format($money[0]["cash"], 2, ".", ",");


    // render portfolio
    render("portfolio.php", ["cash" => $cash, "positions" => $positions, "title" => "Portfolio"]);

?>
