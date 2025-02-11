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
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }
        th, td {
            padding: 8px 12px;
            text-align: left;
            border: 1px solid #ddd;
        }
        th {
            background-color: #f2f2f2;
        }
	tr {
	   background-color: white;
	}
	.color-box {
            width: 30px;
            height: 30px;
            border: 1px solid #ddd;
        }
    </style>
</head>
<body>
    <h1>Random Colour Data</h1>



<?php

	$connect = mysqli_connect('**.**.**.**', '****', '****', '*********');

	if($connect)
		echo "<h3>Connected</h3>";

    //$table = 'Colours';
	//$query = `SELECT * FROM ` . {$table};
	$query = "SELECT * FROM `Colours`";
	$colours = mysqli_query($connect, $query);

    if(mysqli_num_rows($colours) > 0){
        //Create HTML Table of Colours
         echo "<table border='1'>
            <tr>
                <th>Name</th>
                <th>Hex</th>
                <th>Red</th>
                <th>Green</th>
                <th>Blue</th>
                <th>Hue</th>
                <th>HSLS</th>
                <th>HSLL</th>
                <th>Colour</th>
            </tr>";

        $randomNumber = rand(0, 1298 - 6);
        $counter = 0;
        $colour_counter = 0;
        while($row = mysqli_fetch_assoc($colours)) {
            $counter++;
            if($randomNumber <= $counter && $colour_counter < 6)
            {
                 echo "<tr>
                    <td>" . htmlspecialchars($row['Name']) . "</td>
                    <td>" . htmlspecialchars($row['Hex']) . "</td>
                    <td>" . htmlspecialchars($row['Red']) . "</td>
                    <td>" . htmlspecialchars($row['Green']) . "</td>
                    <td>" . htmlspecialchars($row['Blue']) . "</td>
                    <td>" . htmlspecialchars($row['Hue']) . "</td>
                    <td>" . htmlspecialchars($row['HSLS']) . "</td>
                    <td>" . htmlspecialchars($row['HSLL']) . "</td>
                    <td><div class='color-box' style='background-color:" . htmlspecialchars($row['Hex']) . ";'></div></td>
                  </tr>";
                $colour_counter++;
            }
        }
        echo "</table>";
            //echo("\n" . $counter . "\n");
            //echo($randomNumber);
    }
    else
        echo "No rows found\n";


    //Close mysql connection
    mysqli_close($connect);
?>

</body>
</html>
