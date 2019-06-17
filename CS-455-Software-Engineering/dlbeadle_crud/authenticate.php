<?php session_start();

	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "march";
	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) 
	{
    	die("Connection failed: " . $conn->connect_error);
	} 

	$sql = "SELECT * FROM users WHERE username='".$_POST['enduser']."' 
			AND password='".$_POST['userpass']."'";
	$result = $conn->query($sql);
	
	// From TutorialsPoint "PHP and MySQL Login"
	// Not sure if this ultimately worked, index is stuck at welcoming admin and blocks
	// other user logins. I did not alter index.php but other CRUD ops worked
	$numRows = mysqli_num_rows($result);

	//if($_REQUEST['enduser] === 'admin')	
	if($numRows == 1)	
	{
    	$_SESSION['username'] = $_REQUEST['enduser'];
    	$_SESSION['error'] = '';
	}
	
	else 
	{
    	$_SESSION['error'] = 'invalid username or password';
	}

	$conn->close();

header("location:index.php");
?>