//LAB 9-DATA STORAGE: INDEX PAGE
window.onload = function () {
/*
    console.log("Loaded");
    var welcomeHtml2 = document.getElementById("newMsgBox2");
    //check for stored values
    if(document.cookie.length > 0){
        //retrieve stored values
        var cookieArray = document.cookie.split(";");
        var userName = cookieArray[0].split("=")[1];
        var userColour  = cookieArray[1].split("=")[1];

        //change welcome text to stored name
        console.log("Cookie Name: " + userName);
        console.log("Cookie Colour: " + userColour);

        //change BG colour to stored colour
        document.body.style.background = userColour;
        welcomeHtml2.textContent = "Welcome " + userName;

        //  document.body.style.background = 
        
    }
    */

    var firstName = document.getElementById("inName");
    var colour = document.getElementById("inColor");
    var submitButton = document.querySelector('input[type="submit"]');

    var welcomeHtml = document.getElementById("newMsgBox");

    var deleteBtn = document.getElementById("btnDel");


    

    console.log(firstName.value);
    console.log(colour.value);


    function makeCookie(cookieName, cookieValue, cookieLife)
    {
        document.cookie = `${cookieName}=${cookieValue};max-age=${cookieLife}`;

    }


    // Add an event listener for the 'click' event
    submitButton.addEventListener('click', () => {
        // Prevent the default form submission behavior
        //event.preventDefault();
        makeCookie("firstName", firstName.value, 1000);
        makeCookie("UserColour", colour.value, 1000);

        // Your custom logic goes here
        console.log('Submit button clicked!');
    });
    
    deleteBtn.addEventListener('click', () => {
        // Prevent the default form submission behavior
        //event.preventDefault();
        makeCookie("firstName", null, 0);
        makeCookie("UserColour", null, 0);

        location.reload();

        // Your custom logic goes here
        console.log('Submit button clicked!');
    });

    if(document.cookie.length > 0){
        //retrieve stored values
        var cookieArray = document.cookie.split(";");
        var userName = cookieArray[0].split("=")[1];
        var userColour  = cookieArray[1].split("=")[1];

        //change welcome text to stored name
        console.log("Cookie Name: " + userName);
        console.log("Cookie Colour: " + userColour);

        //change BG colour to stored colour
        document.body.style.background = userColour;
        welcomeHtml.textContent = "Welcome " + userName;

        
    }

    


    


    console.log(document.cookie);

}


		
//#####============== DO THIS PART FIRST! ===============		
    //get the form and set submit listener
	
	

	//onsubmit Function
        
        //get values from form
		
		
		//console.log the form values

        
        //store values
        
        



    
