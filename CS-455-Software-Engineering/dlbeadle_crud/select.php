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
?>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title></title>
    </head>
    <body>
        <?php
        	$sql = "SELECT * FROM team order by seed";
        	$result = $conn->query($sql);

        	echo "<table border='1'>
                	<tr>
                		<th>Seed</th>
                		<th>School</th>
                		<th>Conference</th>
                	</tr>";

        	while ($row = $result->fetch_assoc()) 
        	{
            	echo "<tr>";
            	echo "<td>" . $row['seed'] . "</td>";
            	echo "<td>" . $row['school'] . "</td>";
            	echo "<td>" . $row['conference'] . "</td>";
            	echo "</tr>";
        	}
        
        	echo "</table>";

        	$conn->close();
        	?>
    </body>
</html>
