/* LAB 8.2 - STOP TIME */


//create page load listener
window.onload = function() {

    //var currentTime = new Date();

    var htmlHours = document.getElementById("hoursOut");
    var htmlMinutes = document.getElementById("minsOut");
    var htmlSeconds = document.getElementById("secsOut");


    var startBtn = document.getElementById("btnStart");
    var stopBtn = document.getElementById("btnStop");

    
    // Variable to store the interval ID for stopping the timer
    var timerInterval;

    function checkS (timeSet)
    {
        if(String(timeSet).length == 1)
            return timeSet +"0";
        else
            return timeSet;
    }

    function checkString(currentTime, timeSet) {
        
        if(timeSet === "hours")
            if(String(currentTime.getHours()).length <= 1)
                return "0" + String(currentTime.getHours());
            else 
                return String(currentTime.getHours());
        else if(timeSet === "minutes")
            if(String(currentTime.getMinutes()).length <= 1)
                return "0" + String(currentTime.getMinutes());
            else 
                return String(currentTime.getMinutes());
        else if(timeSet === "seconds")
            if(String(currentTime.getSeconds()).length <= 1)
                return "0" + String(currentTime.getSeconds());
            else 
                return String(currentTime.getSeconds());
    }

    function displayTime () {

        var currentTime = new Date();
        var hours = checkS(currentTime.getHours());
        var minutes = checkS(currentTime.getMinutes());
        var seconds  = checkS(currentTime.getSeconds());

        //var hours = checkString(currentTime, "hours");
        //var minutes = checkString(currentTime, "minutes");
        //var seconds  = checkString(currentTime, "seconds");
        //var hours = String(currentTime.getHours()).padStart(2, '0');
        //var minutes = String(currentTime.getMinutes()).padStart(2, '0');
        //var seconds = String(currentTime.getSeconds()).padStart(2, '0');
        // Update the HTML elements with formatted time
        htmlHours.textContent = hours;
        htmlMinutes.textContent = ":" + minutes;
        htmlSeconds.textContent = ":" + seconds;
    }

    function stopTimer(){
        clearInterval(timerInterval);

    }

    function startTimer(){
        // Clear any existing interval to avoid multiple intervals
        clearInterval(timerInterval);
        // Start a new interval to update the time every second
        timerInterval = setInterval(displayTime, 1000);

        

    }

    startBtn.onclick = startTimer;
    stopBtn.onclick = stopTimer;

}

//create page load function

	//create variables for required HTML elements
	
	//create time variable so all functions have access to it
	
	
	//CREATE FUNCTION THAT DISPLAYS THE TIME
	
	
	//CREATE FUNCTION TO START THE CLOCK.
	
	
	//CREATE FUNCTION TO STOP THE CLOCK
	
	
	// SET EVENT LISTENERS
