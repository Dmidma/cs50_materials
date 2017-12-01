<form action="sell.php" method="post">
    <fieldset>
	<div class="form-group">
            <select class="form-control" name="symbol">
                <option disabled selected value="">Symbol</option>
                <?php
                    foreach ($positions as $position)
                    {   
                        print('<option value="' . $position["symbol"] . '">' . $position["symbol"] . '</option>');
                    }
                ?>
            </select>
        </div>
	<!--<div class="form-group">
            <input class="form-control" selected value ="1" type="number" min="1" max="20" />
	</div>-->
        <div class="form-group">
            <button class="btn btn-default" type="submit">Sell</button>
        </div>
    </fieldset>
</form>
