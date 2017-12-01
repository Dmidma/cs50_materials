	    <div>
		<p class="bg-info">Welcome <b class="user"><?php print($_SESSION["username"]); ?></b> to your personal profile.</p>
	    </div>
	    <br/>
	    <?php if ($email == "noemail"): ?>
		<p style="font-size: 130%;"> Add an email to your account.</p>
                <form class="form-horizontal" action="profile.php" method="post">
		    <fieldset>
			<div class="form-group">
			    <label class="col-sm-2 control-label">Email</label>
			    <div class="col-sm-2">
				<input type="email" class="form-control" name="email" placeholder="Email">
			    </div>
			    <div class="col-sm-3">
				<button type="submit" class="btn btn-default">Add Email</button>
    			    </div>
			</div>
		    </fieldset>
		</form>
	    <?php else: ?>
		<p style="font-size: 160%;"> current email is:</p><span style="font-size: 130%; text-decoration: underline;"> <?php print($email); ?></span>
                <form class="form-horizontal" action="profile.php" method="post">
		    <fieldset>
			    <div class="col-sm-8">
				<button type="submit" class="btn btn-default">Unbound It.</button>
    			    </div>
		    </fieldset>
		</form>
	    <?php endif ?>
	    <p style="font-size: 160%;">Want to change Password?</p>
            <form class="form-horizontal" action="changepass.php" method="post">
		<fieldset>
			<div class="col-sm-8">
			    <button type="submit" class="btn btn-default">Change pass.</button>
    			</div>
		</fieldset>
	    </form>
