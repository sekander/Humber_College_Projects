console.log("Loaded");
//LAB 9-DATA STORAGE: PRODUCTS PAGE
window.onload = function () {

    console.log("Loaded");

    var welcomeHtml = document.getElementById("newMsgBox");

    if (document.cookie.length > 0) {
        //retrieve stored values
        var cookieArray = document.cookie.split(";");
        var userName = cookieArray[0].split("=")[1];
        var userColour = cookieArray[1].split("=")[1];

        //change welcome text to stored name
        console.log("Cookie Name: " + userName);
        console.log("Cookie Colour: " + userColour);

        //change BG colour to stored colour
        document.body.style.background = userColour;
        welcomeHtml.textContent = "Welcome " + userName;

        document.body.style.background = userColour;

    }
}
