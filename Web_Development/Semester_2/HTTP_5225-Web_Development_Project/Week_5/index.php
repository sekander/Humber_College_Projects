<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Colour Data</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f4f4f4;
        }
	h3 {
	   color: green;
	}
	.colour-box {
            width: 95w;
            height: 10vh;
            border: 1px solid #ddd;
        }
    </style>
</head>
<body>
    <h1>Random Colour Data</h1>



<?php

	$connect = mysqli_connect('34.60.40.76', 'root', 'root', 'http_5225');


	if($connect)
		echo "<h3>Connected</h3>";

	$query = "SELECT * FROM `Colours`";
	$colours = mysqli_query($connect, $query);

    if(mysqli_num_rows($colours) > 0){

        $randomNumber = rand(0, 1298 - 6);
        $counter = 0;
        $colour_counter = 0;
        while($row = mysqli_fetch_assoc($colours)) {
            $counter++;
            if($randomNumber <= $counter && $colour_counter < 6)
            {
                echo "<div class='colour-box' style='background-color:" . htmlspecialchars($row['Hex']) . ";'></div>";
                $colour_counter++;
            }
        }
    }
    else
        echo "No rows found\n";


    //Close mysql connection
    mysqli_close($connect);
?>

</body>
</html>
