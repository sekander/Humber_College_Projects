// Set the pageReady function to be called when the page finishes loading
window.onload = pageReady;

function pageReady() {

    // Set the pageReady function to be called when the page finishes loading
    var formHandler = document.forms.ixdForm;

    // Reference the page header element by its ID
    const pageHeader = document.getElementById("welcome");

    // Reference the form container element by its ID
    const pageForm = document.getElementById("form");

    // Reference the results container element by its ID
    const pageResult = document.getElementById("result");

    // Reference the result display elements for first and last name
    const resultFName = document.getElementById("result__Fname");
    const resultLName = document.getElementById("result__Lname");

    // Reference the result display element for student ID
    const resultID = document.getElementById("result__id");
    // Reference the result display element for the selected program
    const resultProgram = document.getElementById("result__program");
    // Reference the result display element for the selected project
    const resultProject = document.getElementById("result__project");
    // Reference the dropdown element for selecting a program
    const selectElement = document.getElementById("in_program");
    // Reference the radio button selection container by its ID
    const radioButtons = document.getElementById("caption_project");

    // Define a regex pattern for a valid student ID (must start with 'n' or 'N' followed by 8 digits)
    const regex = /^[nN]\d{8}$/;


    // Set the form submission handler to the processForm function
    formHandler.onsubmit = processForm;

    function processForm() {

        // Validate that the first name is not empty
        if (formHandler.f__fName.value === "") {
            // Highlight field in red
            formHandler.f__fName.style.background = "red";
            // Focus on the first name field
            formHandler.f__fName.focus();
            // Prevent form submission
            return false;
        }
        // Validate that the last name is not empty
        else if (formHandler.f__lName.value === "") {
            // Highlight field in red
            formHandler.f__lName.style.background = "red";
            // Focus on the first name field
            formHandler.f__lName.focus();
            // Prevent form submission
            return false;
        }
        // Validate that the student ID is not empty and follows the correct format
        else if (formHandler.f__id.value === "" || !regex.test(formHandler.f__id.value)) {
            // Log regex validation result
            console.log(regex.test(formHandler.f__id.value));
            // Highlight field in red
            formHandler.f__id.style.background = "red";
            // Focus on the id field
            formHandler.f__id.focus();
            // Prevent form submission
            return false;
        }
        // Validate that a program has been selected from the dropdown
        else if (formHandler.f__program.value === "X") {
            formHandler.f__program.style.background = "red"; // Highlight field in red
            formHandler.f__program.focus(); // Focus on the program selection
            return false; // Prevent form submission
        }
        // Validate that a project has been selected from the radio buttons
        else if (formHandler.f__project.value === "") {
            console.log("No project selected"); // Log the selection status
            radioButtons.style.background = "red"; // Highlight radio buttons in red
            return false; // Prevent form submission
        }
        else {
            // Log the selected project value for debugging
            console.log(formHandler.f__project.value);

            // Hide the header and form upon successful validation
            pageHeader.style.display = "none";
            pageForm.style.display = "none";

            // Retrieve and display the user's input in the results section
            resultFName.textContent = formHandler.f__fName.value; // Display first name
            resultLName.textContent = formHandler.f__lName.value; // Display last name
            resultID.textContent = formHandler.f__id.value; // Display student ID

            // Get the selected program's text and display it
            var selectedItem = selectElement.options[selectElement.selectedIndex].text;
            resultProgram.textContent = selectedItem; // Display selected program

            // Display the selected project
            resultProject.textContent = formHandler.f__project.value;

            // Make the results section visible to the user
            pageResult.style.display = "block";

            return false; // Prevent form submission
        }
    }
}
