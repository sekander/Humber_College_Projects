//LAB 10 - 1 FAQ PAGE

//Listen for window load the jQuery way
$(window).on("load", function() {

	//Inside of here is your jQuery/JavaScript


	//ADD CLICK EVENT TO <h2>
    $('h2').on('click', function() { 
           var currentParagraph = $(this).next('p');

            // Slide up all paragraphs that are currently open (except the clicked one)
            $('p').not(currentParagraph).stop(true, true).slideUp(3000); // Close all other paragraphs

            // Slide down the clicked paragraph
            currentParagraph.stop(true, true).slideDown(3000); // Open the clicked paragraph
    }); 

    //Store original colour
    $('p').each(function() {
        var originalColour = $(this).css('background-color');
        var originalTextColour = $(this).css('color');

        //Storeing colour in data attributes 
        $(this).data('originalColour', originalColour);
        $(this).data('originalTextColour', originalTextColour);
    });

	//CHANGE <p> BACKGROUND ON HOVER
    $('p').hover(
        function() {
            $(this).css({
            //Change colour on hover
                'background-color': 'blue',
                'color': 'black'
            });
        },
        function() {
            $(this).css({
            //Change colour on hover
                'background-color': $(this).data('originalColour'),
                'color': $(this).data('originalTextColour')
            });
        }
    );
});








