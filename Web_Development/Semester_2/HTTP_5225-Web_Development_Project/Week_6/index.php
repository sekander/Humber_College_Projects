<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <style>
	body {
		background: grey;
	}
	/* Ensure all cards are the same height */
        .card {
            height: 100%; /* Ensures card height fills the available space */
            display: flex;
    	    border: 5px solid transparent; /* Set an initial transparent border */
            flex-direction: column;
        }
        .card-body {
            flex-grow: 1; /* Ensures content takes available space */
        }
        .row {
            gap: 20px; /* Controls the spacing between the cards */
        }

	.col-md-3 {
		flex: 0 0 23%;
	}

	 /* Hover effect */
        .card:hover {
	    animation: growBorder 1.0s ease-in-out infinite;
            cursor: pointer; /* Changes the cursor to a pointer on hover */
        }

	/* Keyframes to grow/shrink the border */
	@keyframes growBorder {
	    0% {
		border-color: rgba(0, 255/2, 0, 0.2);
	    }
	    50% {
		border-color: rgba(0, 255, 0, 0.6); /* Stronger color at max size */
	    }
	    100% {
		border-color: rgba(0, 255/2, 0, 0.2); /* Back to original border color */
	    }
	}



    </style>

</head>
<body>

<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
    <div class="container-fluid">
        <a class="navbar-brand" href="#">Navbar</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
            <li class="nav-item">
            <a class="nav-link active" aria-current="page" href="#">Home</a>
            </li>
            <li class="nav-item">
            <a class="nav-link" href="#">Link</a>
            </li>
            <li class="nav-item dropdown">
            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-bs-toggle="dropdown" aria-expanded="false">
                Dropdown
            </a>
            <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
                <li><a class="dropdown-item" href="#">Action</a></li>
                <li><a class="dropdown-item" href="#">Another action</a></li>
                <li><hr class="dropdown-divider"></li>
                <li><a class="dropdown-item" href="#">Something else here</a></li>
            </ul>
            </li>
            <li class="nav-item">
            <a class="nav-link disabled" href="#" tabindex="-1" aria-disabled="true">Disabled</a>
            </li>
        </ul>
        </div>
    </div>
</nav>



<div class="container-fluid">
    <div class="container">
        <div class="row">

            <div class="col">
                <h1 class="display-5" style="color:white">All Schools</h1>

            </div>

            <div class="row">
                <?php
                    $connect = mysqli_connect("***.***.*.**", "****", "******", "*********");
                    if(!$connect) {
                        echo "Error Code: " . mysqli_connect_errno();
                        echo "Error Message : " . mysqli_connect_error();
                    exit;
                    }
                ?>
                <?php
                    $db_table = "TABLE 2";
                    $query = "SELECT * FROM `{$db_table}`";
                    $schools = mysqli_query($connect, $query);
			
		    while($school = mysqli_fetch_assoc($schools)){
                        echo "<div class='col-md-3'> 
				<div class='card text-white bg-dark mb-3'>
				    <div class='card-body'>
					<h5 class='card-title'>{$school['Board']} : <strong style=color:blue>{$school['Academic Year']}</strong> </h5>
					<h6 class='card-title' style=color:green>{$school['Board No']}</h6> 

					<span class='badge rounded-pill " . 
					($school['Language'] == 'English' ? 'bg-primary' : 'bg-danger') . "'>
					{$school['Language']}</span> : 

					<span class='badge rounded-pill " . 
					($school['School Type'] == 'Public' ? 'bg-success' : 'bg-warning') . "'>
					{$school['School Type']}</span> 				    
				    </div>
				</div>
			      </div>";
                    }

                ?>
            </div>
        </div>
    </div>
</div>



</body>
</html>

