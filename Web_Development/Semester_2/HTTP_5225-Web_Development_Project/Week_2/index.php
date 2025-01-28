<!doctype html>
<html>
  <head>
    
    <title>PHP and Creating Output</title>
    
  </head>
  <body>
  
    <?php 
    echo '<h1>PHP and Creating Output</h1>'; 
    echo '<p>The PHP echo command can be used to create output.</p>'

    ?>

    <p>When creating output using echo and PHP, quotes can often cause problems. There are several solutions to using quotes within an echo statement:</p>
    
    <ul>
        <li>Use HTML special characters</li>
        <li>Alternate between single and double quotes</li>
        <li>Use a backslash to escape quotes</li>
    </ul>
    
    <h2>More HTML to Convert</h2>

    <p>PHP says "Hello World!"</p>

    <p>Can you display a sentence with ''' and """?</p>

    <!-- <img src="php-logo.png"> -->
    <img src="https://banner2.cleanpng.com/20180904/xhu/kisspng-logo-image-computer-icons-php-portable-network-gra-william-davies-meng-mongodb-1713944344684.webp" style="width:200px; height:auto;" >

    <?php
   echo '<img src="https://i.pinimg.com/736x/a4/b3/54/a4b354e7e55143590a1c81636f7a53f6.jpg" alt="ALT TAG" style="width:200px; height:auto;">';
    ?>
    <img src ="<?php echo 'https://sb.blackink.ai/storage/v1/object/public/creations/e628a2e0-803b-4d70-8267-23b26ba684c0/965f33dc-13b2-4e10-97de-995ca5eec77e_0.webp' ?>" alt="<?php echo 'ALT TAG'?>" style="width:200px; height:auto;">

    <br><br><br>


    <?php
    $firstName = "Nahid";
    $lastName = 'Sekander';

    echo 'Hello,' . $firstName. ' '. $lastName;
    
   



    ?>

    <br>
    <?php 
    //$person = array('','','');

    $person['first'] = 'Spock';
    $person['last'] = "S'chn T'gai";
    $person['email'] = 'info@pixelr.io';
    $person['web']='https://nahid-sekander.duckdns.org';

    echo 'Hello, '. $person['first'] . ' '. $person['last'];
    ?>
    <br>
    <a href ="mailto:"<?php echo $person['email'] ?>>Email me here! </a>
    <br>
    <a href ="<?php echo $person['web'] ?>">Visit My Site </a>
   
  </body>
</html>
