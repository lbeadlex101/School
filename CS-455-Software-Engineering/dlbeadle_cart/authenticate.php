<?php session_start();

$username = $_POST['username'];
$password = $_POST['pwd'];


// 2. authtenticate the user's credentials: valid users provide the password: "foo"

if($password === 'foo') {
	$valid = true;  // replace this hard-coded value with true or false based on rule above
}

else {
	$valid = false;
}

if ($valid) {
    // 3. put the authenticated user's name into the SESSION for later use
    echo "Authenticated, $username";
    
    if(isset($_POST['remember']) && $_POST['remember'] == 'ON') {
    	setcookie("user", $username);
    }
    
    header("Location: cart.php");
} 

else {
	echo "INVALID!! $username";
    header("Location: index.html");
}
?>
