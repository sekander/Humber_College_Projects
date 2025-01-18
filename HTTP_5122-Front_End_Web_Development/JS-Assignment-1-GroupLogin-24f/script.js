//Input varaibles
var input
var username

//Constant variables used for verification
const groupMembers = ["Nahid", "Sonia", "Joyce", "Jared"]
const groupNumber = 6
var userPrompt = true

//Continously Loops to keep user prompting to enter the correct credentials
while(userPrompt){
    
    //This check is used if the user has entered the correct group number 
    //But failed to enter the correct user name if they decide
    //To re-login they will not be prompt to enter group number again
    if (input !== groupNumber){
        //Prompt user for number to determine which group they belong in
        input = prompt("Which team number do you belong in?")
        //Converts input from string to int
        input = parseInt(input)
    }

    //Checks if input is valid number
    if (isNumber(input))
    {
        //Check if input is between 1 - 6
        if (input <= 0 || input >= 7)
        {
            //Alerts user to only enter number between 1 and 6
            alert("Please Enter a number between 1 - 6")
            //If wrong credentials are entered user will be prompt to try to login again or exit
            if(confirm("Would you like to try to login in again?"))
            {
                //breaks out of the loop
                userPrompt = true 
            }
        }
        //Conditional check passes
        else
        {
            //Check if input is in groupNumber
            if (input === groupNumber){
                //Grabs input from user to enter their name
                username = prompt("Enter your first name")
                //Conditional check 
                var validUser = false
                //Loops through an array of groupmembers to check if user is in array
                for (var i = 0; i < groupMembers.length; i++)
                {
                    //If user is in group validUser is set to true and the loops breaks out
                    if (username === groupMembers[i])
                    {
                        // alert("Welcome " + username)                
                        validUser = true
                        break;
                    }
                }
                //Valid user they can enter the site
                if (validUser)
                {
                    alert("Welcome " + username)                
                    userPrompt = false
                    // break;
                }
                else{
                    alert("Access denied!")
                    //If wrong credentials are entered user will be prompt to try to login again or exit
                    if(confirm("Would you like to try to login in again?"))
                    {
                        //breaks out of the loop
                        userPrompt = true 
                    }
                }
                
            }
            //Input is denied 
            else {
                alert("You do not belong in this group")
                //If wrong credentials are entered user will be prompt to try to login again or exit
                if(confirm("Would you like to try to login in again?"))
                {
                    //breaks out of the loop
                    userPrompt = true 
                }
            }
        }
    }
    else {
        alert("DEnIED")
        //If wrong credentials are entered user will be prompt to try to login again or exit
        if(confirm("Would you like to try to login in again?"))
        {
            //breaks out of the loop
            userPrompt = true 
        }
    }
}

//Testing if function works  
// console.log(isNumber(input))

//Function to check if value is number
function isNumber(value) {
    //Returns true if parseInt is not NaN
    //And Checks if number is finite i.e not 1 / 0 or -1 / 0
    return !isNaN(parseInt(value)) && isFinite(value);
}