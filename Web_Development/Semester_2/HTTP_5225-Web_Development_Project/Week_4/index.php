<?php

    echo "Week 4\n";
    echo "HTTP 5225\n";
    echo "Nahid Sekander\n";
    echo "n01001831\n";
    echo "--------------\n";

    // Function to fetch user data from the JSONPlaceholder API
    function getUsers() {
        $url = "https://jsonplaceholder.typicode.com/users";
        $data = file_get_contents($url);
        return json_decode($data, true);
    }

// Get the list of users
$users = getUsers();
#echo var_dump($users);

foreach($users as $key => $value) {
    if (is_array($value)) {
        foreach ($value as $subKey => $subValue) {
            if(!is_array($subValue)) {
                #Printing User Data
                if($subKey != "id")
                echo ($subKey == "username") ? 
                    ucfirst($subKey) . ": \t" . $subValue . "\n" : 
                    ucfirst($subKey) . ": \t\t" . $subValue . "\n";
            }
            else     
                foreach ($subValue as $addressKey => $addressValue) {
                    #Printing Location Data
                    if (!is_array($addressValue))
                        #Printing Address Data
                        #echo ucfirst($addressKey) . ": \t" . $addressValue . "\n";
                        echo ($addressKey  == "suite" || $addressKey == "city") ? 
                            ucfirst($addressKey) . ": \t\t" . $addressValue . "\n" : 
                            ucfirst($addressKey) . ": \t" . $addressValue . "\n";
                    else
                        foreach ($addressValue as $coordKey => $coordValue)
                        #Printing Coordinates Data
                        {
                            echo ucfirst($coordKey) . ": \t\t" . $coordValue . "\n";
                            if ($coordKey == "lng")
                                break 3; 
                        }
                }
            }
    }
    echo "\n";
}

#OLD CODE
#foreach( $users as $user)
#{
  #echo "Name: " . $user['name'] . "</ br>";
  #echo "Username: " . $user['username'] . "</ br>";
  #echo "Email : " . $user['email'] . "</ br>";
  #	echo var_dump($address);
  #$address = $user['address'];
    
    
  #echo "Name: \t\t" . $user['name'] . "\n";
  #echo "Username: \t" . $user['username'] . "\n";
  #echo "Email: \t\t" . $user['email'] . "\n";


  #foreach($address as $key => $value) {
  #foreach($user['address'] as $key => $value) {
     #if (is_array($value)) {
     #   foreach ($value as $subkey => $subvalue) {
     #       echo ucfirst($subkey) . ": \t\t" . $subvalue . "\n";
     #       #echo ucfirst($subkey) . ": " . $subvalue . "<br />";
      #  }
     #}
     #else 
     #   echo (ucfirst($key) == "Suite" || ucfirst($key) == "City") ? 
     #       ucfirst($key) . ": \t\t" . $value . "\n" : 
    #        ucfirst($key) . ": \t" . $value . "\n";
 # }
   # echo "\n";
#}
	

?>

