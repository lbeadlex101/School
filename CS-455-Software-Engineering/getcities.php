<?php

//print_r($_REQUEST);
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "ajax_demo";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_REQUEST['state'] == 'Colorado') {
    $sql = "SELECT city_name FROM cities WHERE state_name = 'Colorado'";
    $result = $conn->query($sql);
    echo "<select>";
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            echo "<option value = ".$row['city_name']."> ".$row['city_name']."</option>";
        }
    }
    echo "</select>";
    
} else {
    $sql = "SELECT city_name FROM cities WHERE state_name = 'Alabama'";
    $result = $conn->query($sql);
    echo "<select>";
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
           echo "<option value = ".$row['city_name']."> ".$row['city_name']."</option>";
        }
    }
}

$conn->close();
?>