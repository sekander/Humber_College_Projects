<!doctype html>
<html>
    <head>
        <title>PHP If Statements</title>
        <!--
Nahid Sekander
n01001831

Challenge 1: Welcome to the Quirky Zoo Management System! 
You have been hired to manage the feeding schedule for various quirky 
animals in the zoo. Each animal has its unique feeding requirements 
based on the time of day. Your task is to write a PHP script that 
determines what each animal should eat based on the current time. 
Here's the challenge: 
 If the time is between 5 AM and 9 AM, the animals should have breakfast. 
 If the time is between 12 PM and 2 PM, the animals should have lunch. 
 If the time is between 7 PM and 9 PM, the animals should have dinner. 
 If the time does not fall within any of the above intervals, 
the animals are not being fed.  Each meal has specific food items: 
o Breakfast: "Bananas, Apples, and Oats" 
o Lunch: "Fish, Chicken, and Vegetables" 
o Dinner: "Steak, Carrots, and Broccoli"




Challenge 2: PHP Control Structures - 
The Magic Number Game Welcome to the Magic Number Game! 
Your task is to write a PHP script that determines the magic number 
based on a set of quirky rules. The user will input a number, 
and your script will follow these rules to determine the magic number: 
 If the number is divisible by 3, the magic number is "Fizz". 
 If the number is divisible by 5, the magic number is "Buzz". 
 If the number is divisible by both 3 and 5, the magic number is "FizzBuzz". 
 If the number is not divisible by either 3 or 5, the magic number is the 
number itself. 
Write a PHP script that takes an input number and prints the 
magic number according to these rules

        -->
   </head>
    <body>

        <h1>Challenge 1</h1>
        <?php
            //$hour = date('G');
            $hour = ceil(rand(1, 24));
            echo $hour;
            echo '<br/>';

            if ($hour > 5 && $hour < 9)
            {
                echo ' Breakfast: "Bananas, Apples, and Oats" ';
            }
            else if ($hour > 12 && $hour < 14)
            {
                echo ' Lunch: "Fish, Chicken, and Vegetables" ';
            }
            else if ($hour > 19 && $hour < 21)
            {
                echo ' Dinner: "Steak, Carrots, and Broccoli" ';
            }
            else
            {
                echo 'Not Feeding Time';
            }
        ?>



        <h1>Challenge 2</h1>
        <?php
        $input = readline('Enter number: ');
        echo $input;

        if ($input % 3 == 0 && $input % 5 == 0)
            echo "FizzBuzz";
        else if ($input % 3 == 0)
            echo "Fizz";
        else if ($input % 5 == 0)
            echo "Buzz";
        else
            echo $input;
            

        ?>

    </body>
</html>






<!--

 If the number is divisible by 3, the magic number is "Fizz". 
 If the number is divisible by 5, the magic number is "Buzz". 
 If the number is divisible by both 3 and 5, the magic number is "FizzBuzz". 
 If the number is not divisible by either 3 or 5, the magic number is the number itself. 
-->



