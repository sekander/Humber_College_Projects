//#### LAB 4 - FUNCTIONS ####
//PART 3:  WALKING THE DOG 


//################## CREATE YOUR checkTemp FUNCTION
//This function will...
//It expects to receive...
//It will return...

/*
a. What the function does
b. What parameters it expects (variable name and data type)
c. What value(s) it returns (data type)


*/
// a. Returns a true or false based on the user input
//    True if input is greater than -10 and less than 30 else returns false 
// b. Parameter takes an integer, function doesnt test parameter is valid or not 
// c. Returns a boolean true or false
function checkTemp(currentTemp){
    if (currentTemp > 30 || currentTemp < - 10)
        return false;
    else
        return true;
}

var userInputTemp = prompt("Get Current Temp")

if (checkTemp(userInputTemp))
    alert("You’re good, have a nice walk!")
else if (userInputTemp < -10)
    alert("Yikes! This is no weather for dog walking!")
else
    alert("Yikes! Too hot for dog walking!")

//################## LOGIC THAT OUTPUTS MESSAGES BASED ON FUNCTION RESULTS
