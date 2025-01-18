var current = 0;
var total = 4;

function next() {
    // Increment the current variable by one
    // current = current + 1;
    // current += 1;
    current++;

    // If the current variable is greater than the
    // number of slides, reset to zero
    if(current >= total){
        current = 0;
    }
   // Create a reference to all the slide divs
    var slides = document.getElementsByClassName("slide");  
   // Loop through the slides
    for (var i = 0; i < slides.length; i++) {
        slides[i].style.display = "none";
    }
    // Display the selected slide
    slides[current].style.display = "block";

    console.log("next");
    console.log(current);

}

function previous() {
    // Increment the current variable by one
    // current = current - 1;
    // current -= 1;
    current--;

    // If the current variable is greater than the
    // number of slides, reset to zero
    if(current < 0) {
        current = total - 1;
    }


    // Create a reference to all the slide divs
    var slides = document.getElementsByClassName("slide");  
    // Loop through the slides
    for (var i = 0; i < slides.length; i++) {
        slides[i].style.display = "none";
    }
    // Display the selected slide
    slides[current].style.display = "block";

    console.log("previous");
    console.log(current);
}


