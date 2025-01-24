/* LAB 8-1 - FINAL COUNTDOWN!! */


//create page load listener
window.onload = function() {
var dateVar = new Date();
var dueDate = new Date("December, 13, 2024 18:00");

var htmlDate = document.getElementById("todayData");
var htmlfinal = document.getElementById("finalData");
var htmlDueDate = document.getElementById("dueData");
var htmlFinalMsg = document.getElementById("countMsg");

var timeStamp_first = dateVar.getTime();
var timeStamp_second = dueDate.getTime();

var timeDiff = timeStamp_second - timeStamp_first;

var converTimeDiffToDays =  Math.floor(timeDiff/86400000);

    htmlDate.textContent = dateVar.toDateString();
    htmlfinal.textContent = dueDate.toDateString();

    if(converTimeDiffToDays > 0)
        htmlDueDate.textContent = converTimeDiffToDays;
    else
        htmlFinalMsg.textContent = "The Deadline for the Final Assignment has passed!";
        



}

//create page load function

	//create variables for required HTML elements
	
	//create variables for now date and due date
	
	//OUTPUT NOW DATE & DUE DATE TO HTML PAGE
	
	//CONVERT TO UTC AND SUBTRACT TO GET TIME DIFFERENCE
	
	//CONVERT TIME DIFFERENCE TO WHOLE NUMBER OF DAYS
		
	//LOGIC TO CHECK IF DUE DATE HAS PASSED, AND OUPUT APPROPRIATE MESSAGE TO HTML PAGE
