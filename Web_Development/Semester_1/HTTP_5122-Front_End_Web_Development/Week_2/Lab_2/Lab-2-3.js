//######## LAB 2-3 EMAIL SIGNUP ########
// alert("hey 2.3");//COMMENT OUT ONCE CONNECTED TO YOUR HTML PAGE
//==== VARIABLES =========
var user_email;


//==== LOGIC =============
if (confirm("would like to join your mailing list?"))
{
    user_email = prompt("Enter Email Address", "default@humber.ca");
    if (user_email === "" || user_email === "default@humber.ca" || user_email === "Enter Email Address" || user_email === null)
    {
        alert("Thank you, but your email was not valid.")
    }
    else {
        alert("Thank you, our next newsletter will be sent to")
    }
}
else {
    alert("Thank you, we will not bother you again.");
}
/*
Create a popup box that asks the user if they would like to join your mailing
list.
2. If the user agrees to sign up for the mailing list, provide a popup textbox to
ask for that information. me@example.com should appear in the text box
itself as helper text.
3. Validate the input against no input, the default text, or a Cancel click.
4. A popup will end the transaction. If the user declines to join, the message
will read, “Thank you, we will not bother you again.”
If successful, the message will read, “Thank you, our next newsletter will be
sent to “, with the provided email address.
If they intend to signup but the input is invalid (empty string, null, or the
default text), the message will be, “Thank you, but your email was not
valid.”
You do not need to check for an email pattern, it can be any string other
than the default text or an empty string.


*/