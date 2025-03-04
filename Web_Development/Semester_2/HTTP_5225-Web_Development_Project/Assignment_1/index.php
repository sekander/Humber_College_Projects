<?php
// Database connection
$connect = mysqli_connect('localhost', 'fnky', '454732', 'MTG_Final_DB');

// Check connection
if ($connect) {
    echo "<h1>Random MTG Card Data</h1>";
    echo "<h3>Connected</h3>";

	$random_card_query = "SELECT 
	    uc.name, 
	    ci.image_url,
	    uc.released_at, 
	    uc.mana_cost, 
	    uc.type_line, 
	    uc.oracle_text, 
	    uc.power, 
	    uc.toughness, 
	    uc.colors, 
	    uc.artist
	FROM Unique_Cards uc
	LEFT JOIN Card_Images ci ON uc.CardID = ci.id
	ORDER BY RAND()
	LIMIT 50;";


    // Execute query
    $cards = mysqli_query($connect, $random_card_query);

    if (mysqli_num_rows($cards) > 0) {
        // Start the container
        echo '<div class="container mt-5">';
        
        // Show the table for larger screens (≥1200px)
        echo '<div class="d-none d-lg-block">';  // This hides the table on screens smaller than 1200px (Large screens)

        // Render table start
        echo "<table class='table table-striped table-hover table-bordered'>";

        // Get the column names dynamically
        $columns = mysqli_fetch_fields($cards);

        // Create table headers
        echo "<tr>";
        foreach ($columns as $column) {
            echo "<th>" . htmlspecialchars($column->name) . "</th>";
        }
        echo "</tr>";

        // Loop through rows and display data
        while ($row = mysqli_fetch_assoc($cards)) {
            echo "<tr>";

            foreach ($row as $column_name => $cell) {
                if ($column_name == "image_url") {
                    // Ensure the image is placed in the correct column
                    echo sprintf('<td class="card-image"><img src="%s" alt="Card Image" style="max-width: 200px; height: auto;"></td>', htmlspecialchars($cell));
                } else {
                    // For all other columns, just display the data
                    echo "<td>" . htmlspecialchars($cell) . "</td>";
                }
            }
            echo "</tr>";
        }

        echo "</table>";
        echo '</div>';  // Close the div for the table

        // Show the cards in a grid layout for smaller screens
        // This part will show the grid of cards on screens smaller than 1200px
        echo '<div class="row row-cols-1 row-cols-sm-2 row-cols-md-3 row-cols-lg-3 g-4 d-lg-none">';  

        // Loop through each row and output it as a card
        mysqli_data_seek($cards, 0);  // Reset the pointer to the start of the result set
        while ($row = mysqli_fetch_assoc($cards)) {
		
	   //echo '<div class="col mb-4">';
	   echo '<div class="col mb-4">';
            echo '<div class="card shadow-sm card-flip">';  // Card container with flip class

            // Flip container for card
            echo '<div class="card-inner">';

            // Front side of the card
            echo '<div class="card-front">';
            echo '<img src="' . htmlspecialchars($row['image_url']) . '" alt="Card Image" class="card-img-top">';
            echo '<div class="card-body">';
            //echo '<h5 class="card-title">' . htmlspecialchars($row['name']) . '</h5>';
            echo '</div>';
            echo '</div>';

            // Back side of the card
            echo '<div class="card-back">';
            echo '<div class="card-body">';
	    echo '<div class="card-square">';  
            echo '<h5 class="card-title">' . htmlspecialchars($row['name']) . '</h5>';
            echo '<p>Released: ' . htmlspecialchars($row['released_at']) . '</p>';
            echo '<p>Power: ' . htmlspecialchars($row['power']) . '</p>';
            echo '<p>Toughness: ' . htmlspecialchars($row['toughness']) . '</p>';
            echo '<p>Mana Cost: ' . htmlspecialchars($row['mana_cost']) . '</p>';
            echo '<p>Colors: ' . htmlspecialchars($row['colors']) . '</p>';
            echo '<p>Type: ' . htmlspecialchars($row['type_line']) . '</p>';
            echo '<p>Artist: ' . htmlspecialchars($row['artist']) . '</p>';
            echo '</div>';
            echo '</div>';
            echo '</div>';

            // Close flip container
            echo '</div>';

            // Close card container
            echo '</div>';
            echo '</div>';



        }
        echo "</div>";  // Close the grid layout row

        echo "</div>";  // Close container
    } else {
        echo "No rows found";
    }

    // Close MySQL connection
    mysqli_close($connect);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MTG Cards</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <style>
        /* Custom Styles (Optional) */
        .card-image {
            transition: transform 0.3s ease; /* Smooth transition for scaling */
            text-align: center;
        }

        .card-image img {
            max-width: 100%;
            height: auto;
        }

/* Card Body Styling */
.card-body {
    //background-color: #2c2c2c; /* Darker background for card body */
    background-color: rgba(0,0,0, 0);
    color: #e0e0e0; /* Light text color */
    padding: 15px;
    //display: flex;
    flex-direction: column;
    justify-content: space-between;
}





	.card-body {
            height: auto;
	}
	

	/* Card Flip Styles */
	.card-flip {
	    perspective: 1000px;
	    width: 100%;
	    height: 100%;
	}

	.card-inner {
	    position: relative;
	    width: 100%;
	    height: 100%;
	    transform-style: preserve-3d;
	    transition: transform 0.6s;
	}

	/* Front side of the card */
	.card-front, .card-back {
	    position: absolute;
	    width: 100%;
	    height: 100%;
	    backface-visibility: hidden;
	}

	.card-front {
	    background-color: #1c1c1c; /* Keep dark theme on front */
	    display: flex;
	    justify-content: center;
	    align-items: center;
	    color: #fff; /* Light text color */
	}

	.card-back {
	    background-color: #333; /* Darker back side */
	    display: flex;
	    justify-content: center;
	    align-items: center;
	    color: #fff; /* Light text color */
	    transform: rotateY(180deg);
	}
/*
	.card-flip:hover .card-inner {
	    transform: rotateY(180deg);
	}
*/

	@media (max-width: 992px) {
		.mt-5 {
			margin-top: 10rem !important;
		}
		.mb-4 {
			margin-bottom: 15.5rem !important;
		}
		.card-back {
			font-size: 0.65rem;	
		}
	}
	@media (max-width: 776px) {
		g-4, .gy-4 {
		  --bs-gutter-y: 18.5rem;
		}
		.mb-4 {
			margin-bottom: 18.5rem !important;
		}
		.card-back {
			font-size: 0.75rem;	
		}
	}
	@media (max-width: 575px) {
		.mt-5 {
			//margin-top: 24rem !important;
			margin-top: 30vh  !important;
		}
		.mb-4 {
			margin-bottom: 31.5rem !important;
		}
		.card-back {
			font-size: 1.5rem;	
		}
	}

    </style>
<script>
// Function to handle card flip
    function handleCardFlip(event) {
        const cardInner = this.closest('.card-inner'); // Get the closest card-inner element

        // Toggle the transform property to flip the card
        if (cardInner.style.transform === 'rotateY(180deg)') {
            cardInner.style.transform = ''; // Reset the flip
            this.style.background = 'rgba(0, 0, 0, 1)'; // Restore background color
        } else {
            cardInner.style.transform = 'rotateY(180deg)'; // Flip the card
            this.style.background = 'rgba(0, 0, 0, 1)'; // Set transparent background for the front side
        }
    }

    // Add event listeners to both card image and card body elements
    document.querySelectorAll('.card-img-top, .card-body').forEach(element => {
        element.addEventListener('click', handleCardFlip);
    });
</script>

</head>
<body>

</body>
</html>

