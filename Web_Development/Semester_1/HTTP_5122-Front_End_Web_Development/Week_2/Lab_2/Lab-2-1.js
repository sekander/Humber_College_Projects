//######## LAB 2-1 FILE DELETE CONFIRMATION ########
// alert("hey 2.1");//COMMENT OUT ONCE CONNECTED TO YOUR HTML PAGE
//==== VARIABLES ========
var userChoice;
var messageOut = "Thank you, your file has ";
var yesMessage = "been successfully deleted.";
var noMessage = "not been altered.";

//==== LOGIC ========
var input;

//1. CREATE POPUP TO ASK FOR PERMISSION TO PROCEED WITH DELETION OF FILE.
if (confirm("WOuld you like to delete this file")){
    input = messageOut + yesMessage
    alert(input)
}else{
    input = messageOut + noMessage
    alert(input)
}

//2. IF USER CLICKS OKAY, POPUP messageOut WITH yesMessage.


//3. IF USER CLICKS ANYTHING BUT OKAY, POPUP messageOut WITH noMessage.



