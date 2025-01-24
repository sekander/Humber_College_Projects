// Define a JavaScript object representing a video game with four attributes
const video_game = {
    title: "Contra Remix",
    genre: "Action",
    multiplayer: true,
    playLength: 8,

    // Method to modify the multiplayer mode
    // Updates the 'multiplayer' attribute based on the argument provided
    modifyObject: function (changeGameMode) {
        this.multiplayer = changeGameMode
        // Displays an alert showing whether multiplayer is enabled or disabled
        alert("Multi-Player Mode Changed : " +
            (this.multiplayer ? "Enabled" : "Disabled"))
    }
};

// Log the current state of the 'video_game' object to the console
console.log(video_game)

// Prompt the user for input
var input = prompt("Update one of the entries in your javascript object",
    // Displays the current object attributes 
    "Title: " + video_game.title +
    ", Genre: " + video_game.genre +
    ", Multi-Player: " + video_game.multiplayer +
    ", Play Length : " + video_game.playLength + "h")

//Update the 'title' attribute of the video_game object with user input
video_game.title = input

// Prompt the user for input 
var second_input = prompt("Update one of the entries in your javascript object",
    "Title: " + video_game.title +
    ", Genre: " + video_game.genre +
    ", Multi-Player: " + video_game.multiplayer +
    ", Play Length : " + video_game.playLength + "h")

//Update the 'genre' attribute of the video_game object with user input
video_game.genre = second_input

// Call the modifyObject method to change the multiplayer mode to 'false' (disabled)
video_game.modifyObject(false)

// Log the updated state of the 'video_game' object to the console
console.log(video_game)
