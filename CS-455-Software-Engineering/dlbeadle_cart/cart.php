<?php
// 4. initialize the SESSION
session_start(); 

// get the cart out of the SESSION (if the cart is not in the SESSION, create it)
if (isset($_SESSION['cart'])) {
    $cart = $_SESSION['cart'];
} 

else {
    $cart = array();
}

// add the new item to the cart
$cart[] = $_REQUEST['item'];

// put the cart back into the session (adding a new item may have resulted in a new object in memory)
$_SESSION['cart'] = $cart;
?>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title></title>
    </head>
    <body>
        <?php
        // 5. display the user's name (saved in session previously)
        $usr = $_SESSION['username'];
        echo "Hello, <br>";
        echo "$usr";
        ?>

        Cart Contents:
        <hr/>
        <?php
        echo "<ul>";
        // 6. loop through the cart array and show each entry as a list item using the HTML li tag
        
        foreach($cart as $item) {
        	echo "<li>$item</li>";
		}
        
        echo "</ul>";
        ?>

        Add to your cart:<br/>
        <form action="cart.php" method="POST">
            <select name="item">
                <option>Dog</option>
                <option>Cat</option>
                <option>Hamster</option>
                <option>Coffee</option>
                <option>Copy Paper</option>
                <option>Manilla Folders</option>
                <option>Ink Cartridge</option>
                <option>Paper Towels</option>
                <option>Flash Drive</option>
                
                <!-- 7. create a database using the ddl provided -->
                <!-- 8. add all items from the database as additional drop down options -->

            </select>

            <input type="submit" value="Add" name="add" />
        </form>

    </body>
</html>
