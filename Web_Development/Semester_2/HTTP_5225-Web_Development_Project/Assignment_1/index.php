<?php

	//$connect = mysqli_connect('34.60.40.76', 'root', 'root', 'http_5225');
	$connect = mysqli_connect('localhost', 'fnky', '454732', 'MTG_Final_DB');

	if($connect)
		echo "<h1>Random MTG Card Data</h1>";
		echo "<h3>Connected</h3>";

	   $random_card_query = "SELECT 
                                name, 
                                released_at, 
                                uri, 
                                mana_cost, 
                                type_line, 
                                oracle_text, 
                                power, 
                                toughness, 
                                colors, 
                                color_identity, 
                                rarity, 
                                artist
                          FROM Unique_Cards
                          ORDER BY RAND()
                          LIMIT 50;";

	$cards = mysqli_query($connect, $random_card_query);

    if(mysqli_num_rows($cards) > 0){
        //Render table start
        echo "<table border='1' cellpadding='10'>";

        //Get the column names dynamically
        $columns = mysqli_fetch_fields($cards);


        //create table headers 
        echo "<tr>";
        foreach($columns as $column)
        {
            echo "<th>" . htmlspecialchars($column->name) . "</th>";
        }
        echo "</tr>";

        $card_counter = 0;
        $card_index = 0;
        // Fetch the rows and display the data
        while($row = mysqli_fetch_assoc($cards)) {
            $card_index++;
            echo "<tr>";
            {
                 // Loop through each column in the row
                foreach($row as $column_name => $cell) {
                    if($card_counter != 2)
                        echo "<td>" . htmlspecialchars($cell) . "</td>";
                    else{
                        //Need to do ajax call
                        echo sprintf('<td class="card-image" id="row-index-%d">%s</td>', $card_index, htmlspecialchars($cell));
                        //echo "<td>" . "Loading..." . "</td>";
                    }
                    $card_counter++;
                }
                $card_counter = 0;
            }
            echo "</tr>";
        }

        // Fetch the rows and display the data
        echo "</table>";
    }
    else
        echo "No rows found\n";


    //Close mysql connection
    mysqli_close($connect);
?>
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
		table-layout: auto; /* Allow dynamic resizing based on content */
	    }

	    th, td {
		padding: 8px 12px;
		text-align: left;
		border: 1px solid #ddd;
	    }

	    td {
		overflow-x: hidden; /* Hide overflowing content */
		word-wrap: break-word; /* Allow text to wrap if it's too long */
		width: auto; /* Let the width adjust based on the content */
	    }

	    th {
		background-color: #f2f2f2;
		font-weight: bold;
	    }

	    tr {
		background-color: white;
	    }

	    /* Hover effect for rows */
	    tr:hover {
		background-color: #f1f1f1; /* Light gray on hover */
	    }

	    /* Hover effect for cells */
	    td:hover {
		background-color: #e0e0e0; /* Light gray for cell hover */
		cursor: pointer;
	    }
	
	    .card-image {
		transition: transform 0.3s ease; /* Smooth transition for scaling */
	    }

	    .card-image.enlarged {
		transform: scale(1.5); /* Increase size by 50% when hovered for 3 seconds */
	    }


	    /* Responsive styling for small screens */
	    @media (max-width: 600px) {
		table {
		    width: 100%;
		}

		th, td {
		    padding: 8px;
		    font-size: 14px;
		}

		td {
		    width: 100%; /* Make sure each cell takes full width on small screens */
		}
	    }

	    /* Optional: Add alternating row colors for better readability */
	    tr:nth-child(even) {
		background-color: #f9f9f9;
	    }
	</style>




    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script>
	console.log("Text Script");
        // Select all elements whose id starts with 'row-index-'
        let image_urls = document.querySelectorAll('[id^="row-index-"]');

        // Loop through each element and print its id and content to the console
        image_urls.forEach(function(element) {
            // Perform AJAX call to fetch card data
            $.ajax({
                    url: element.textContent,
                    method: 'GET',
                    success: function(response) {
                        // Get the image_uris normal URL
                        let imageUrl = response.image_uris.normal;

                        // Log the image URL to the console (or update the HTML content)
                        console.log('ID: ' + element.id + ', Image URL: ' + imageUrl);

                        // Create an image element
                        let img = document.createElement('img');
                        img.src = imageUrl;
                        img.alt = "Card Image";
                        img.style.width = "200px";  // Set width to 200px
                        img.style.height = "300px"; // Set height to 300px

                        img.className = "card-image";  // Add a class for styling (optional)

                        // Clear the content of the row and append the image
                        element.innerHTML = '';  // Clear current content
                        element.appendChild(img);  // Append the new image to the row
                    },
                    error: function(error) {
                        console.log('Error fetching data for ' + rowId);
                    }
                });

		/*
		// Select the image element
		const cardImage = document.querySelector('.card-image');

		// Add click event listener
		cardImage.addEventListener('click', function() {
		    // Action on click
		    console.log('Card image clicked!');
		    // Example: Change the size of the image when clicked
		    cardImage.style.width = '400px';  // Set new width
		    cardImage.style.height = '600px'; // Set new height
		});
		*/
		
        });
    </script>

</head>
<body>



</body>
</html>
