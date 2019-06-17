<?php

$q = $_REQUEST["q"];
$hint = "";

$con = mysqli_connect('localhost','root','','email_demo');
if (!$con) {
    die('Could not connect: ' . mysqli_error($con));
}


mysqli_select_db($con,"email_demo");

$sql="SELECT * FROM email_list WHERE last_name = '".$q."'";
$result = mysqli_query($con,$sql);

if ($q !== "") {
    $q = strtolower($q);
    $len=strlen($q);
    foreach($result as $name) {
        if (stristr($q, substr($name, 0, $len))) {
            if ($hint === "") {
                $hint = $name;
            } else {
                $hint .= ", $name";
            }
        }
    }
}

echo $hint === "" ? "no suggested email" : $hint;
?>