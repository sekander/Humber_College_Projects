//######## LAB 2-2 LOGIN ########
//1. LINK THIS JS FILE TO THE HTML FILE
// alert("hey 2.2");//COMMENT OUT ONCE CONNECTED TO YOUR HTML PAGE

//====VARIABLES===============
//2. CREATE NECESSARY VARIABLES
var user_name;
var passwd;
var user_name_input;
var passwd_input;
		// Correct user name
		// Correct password
		// user name input
		// password input
var registered_username = "dart";
var registered_passwd= "vader";


//====LOGIC===================
//3. CREATE POPUP BOX FOR USERNAME
user_name = prompt("Enter Username")

//4. OUTPUT PROVIDED USERNAME TO JS CONSOLE
console.log(user_name);

//5. CREATE POPUP BOX FOR PASSWORD
passwd = prompt("Enter Password")

//6. OUTPUT PROVIDED PASSWORD TO JS CONSOLE
console.log(passwd);

//7. CHECK IF PROVIDED USERNAME AND PROVIDED PASSWORD MATCH THE STORED USERNAME/PASSWORD

if (user_name === registered_username && passwd === registered_passwd)
{
	alert("Welcome back " + ":" + user_name);
	console.log("Login Success");

}
//8. IF THEY MATCH, POPUP SUCCESS MESSAGE AND OUTPUT TO CONSOLE
else {
	alert("Invalid username/passord");
	console.log("ERRROR");
}



//9. IF THEY DON'T MATCH, POPUP INVALID MESSAGE & OUTPUT TO CONSOLE