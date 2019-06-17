<?php session_start();

	if (!isset($_SESSION['username'])) 
	{
    	header("location:index.php");
    	exit;
	}

	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "march";
	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) 
	{
    	die("Connection failed: " . $conn->connect_error);
	}

	$sql = "INSERT INTO team (seed, school, conference)
			VALUES ('".$_POST["seed"]."', '".$_POST["school"]."', '".$_POST["conf"]."')";

	if ($conn->query($sql) === TRUE) 
	{
    	echo "New record created successfully";
	} 

	else 
	{
    	echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();

header("location:index.php");
?>
