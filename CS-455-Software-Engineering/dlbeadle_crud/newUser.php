<?php session_start();

	if (!isset($_POST['user'])) 
	{
    	header("location:register.php");
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

	$sql = "SELECT * FROM users WHERE username='".$_POST['user']."'";
	$result = $conn->query($sql);
	
	// From TutorialsPoint "PHP and MySQL Login"
	// Not sure if this ultimately worked, index is stuck at welcoming admin and blocks
	// other user logins. I did not alter index.php but other CRUD ops worked
	$numRows = mysqli_num_rows($result);

	if($numRows == 1)	
	{
		$_SESSION['error'] = 'User is already in the database';
	} 

	else 
	{
		if ($_POST['pwd'] == "")
		{
			$_SESSION['error'] = "Invalid password";
			$conn->close();
			header("location:index.php");
			exit;
		}
	
		if ($_POST['pwd'] === $_POST['repeat'])
		{
			$servername = "localhost";
			$username = "root";
			$password = "";
			$dbname = "march";
			$conn = new mysqli($servername, $username, $password, $dbname);
		
			if ($conn->connect_error) 
			{
				die("Connection failed: " . $conn->connect_error);
			}

			$sql = "INSERT INTO users (username, password, role)
			VALUES ('".$_POST["user"]."', '".$_POST["pwd"]."', 'user')";

			if($conn->query($sql) === TRUE) 
			{
				echo "New record created successfully";
			} 
		
			else 
			{
				echo "Error: " . $sql . "<br>" . $conn->error;
				exit;
			}

			$conn->close();
			$_SESSION['msg'] = 'New user created successfully';
			$_SESSION['error'] = '';
		}
	
		else
		{
			$_SESSION['error'] = 'Invalid password';
		}
	
	}

	$conn->close();

	header("location:index.php");
	?>