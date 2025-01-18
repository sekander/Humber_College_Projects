//#### LAB 6 - DOM MANIPULATION ####
//PART 2: MYSTERY BOX

//LISTEN FOR load EVENT
window.onload = pageReady;

function pageReady(){
	var mysteryBox = document.getElementById("mysteryBox");
	var buttonBox = document.getElementById("buttonBox");


	mysteryBox.onmouseover = hoverFunc;

	buttonBox.onclick = clickFunc;

	var input;

	function hoverFunc(){

		input = confirm("Do you want to see something")

		if(input)
		{
			mysteryBox.style.display = "none";
			buttonBox.style.display = "block";

		}
	}

	function clickFunc(){
		buttonBox.style.width = "600px";
		buttonBox.style.background =  "orange";
		// const heading = buttonBox.querySelector("h2");
		buttonBox.innerHTML = "<h2>SURPISE!!</h2>"
		buttonBox.innerHTML += "<h2>SURPISE!!</h2>"

	}


}

//'WRAPPER' FUNCTION FOR DOM LOGIC

	//GET DOM ELEMENTS WE'LL NEED


	//====CREATE THE FUNCTIONS WE'LL NEED====
	//FUNCTION TO ASK USER


	//FUNCTION TO CHANGE buttonBox


	//SETUP LISTENERS


//END onload FUNCTION