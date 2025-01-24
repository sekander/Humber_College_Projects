//author: Nahid Sekander 
//student #: n01001831
// An array of movie titles is declared and initialized with seven different movies
var movie1 = "Eternal Sunshine of The Spotless Mind"
var movie2 = "Star Wars"
var movie3 = "Kill Bill"
var movie4 = "Casino"
var movie5 = "Iron-man"
var movie6 = "Fight-Club"
var movie7 = "Catch Me if You can"

var movies = [movie1,
    movie2,
    movie3,
    movie4,
    movie5,
    movie6,
    movie7]


/*
var movies = ["Eternal Sunshine of The Spotless Mind",
    "Star Wars",
    "Kill Bill",
    "Casino",
    "Iron-man",
    "Fight-Club",
    "Catch Me if You Can"]
*/

// Control flag for the while loop, used to prompt the user until valid input is received
var userPrompt = true

//Entered in a while loop to ensure the user enters the correct value 
while (userPrompt) {
    // Prompt the user to enter a number (1-7) corresponding to a movie in the list
    var input = prompt("Which top 7 movie would you like?", "Pick a number: 1-7")

    // Check if the input is valid: a number within the range of 1 to 7
    if (!isNaN(parseInt(input)) && isFinite(input) && input >= 1 && input <= 7) {
        //Prints users input and retrives the movie array using input provided as the index
        alert("Number " + input + " on the list is " + movies[input - 1])
        //Condition is met exit loop
        userPrompt = false
    }
    //User did not enter correct value 
    else {
        //Error message to prompt user they made a mistake
        var errorMsg = ("Please enter a number between 1 and 7!")
        //Prompts user if they would like to try again 
        if (confirm(errorMsg + "\nWould you like to try to login in again?"))
            //User remains in while loop
            userPrompt = true
        else
            //User wants to exit the loop
            userPrompt = false
    }
}

//Debug message prints contents of array 
for (var i = 1; i < (movies.length + 1); i++) {
    console.log("Movie " + i + " : " + movies[i - 1])
}
