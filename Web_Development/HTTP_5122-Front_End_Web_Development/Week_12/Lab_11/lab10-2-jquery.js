//LAB 10 - 2 INVENTORY PAGE
$(window).on("load", function() {

    $('td.desc').hide();

    //ADD MOUSEOVER/MOUSEOUT FUNCTIONS FOR <tr>

    //Store original colour
    $('tr').each(function() {
        var originalColour = $(this).css('background-color');
        var originalTextColour = $(this).css('color');

        //Storeing colour in data attributes 
        $(this).data('originalColour', originalColour);
        $(this).data('originalTextColour', originalTextColour);
    });

    //CHANGE <tr> BACKGROUND ON HOVER
    $('tr').hover(
        function() {
            $(this).css({
            //Change colour on hover
                'background-color': 'red',
                'color': 'white'
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

	//ADD CLICK EVENT TO <tr>
    $('tr').click(
        function() {
            console.log("Got clicked");
            $(this).find('td.desc').show();
        });
});
