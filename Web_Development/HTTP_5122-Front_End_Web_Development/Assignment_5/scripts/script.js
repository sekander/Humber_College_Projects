window.onload = function() {
    console.log("Assignment 5");

    // Get references to HTML elements
    const torontoBttn = document.getElementById("Toronto"); // Toronto button
    const edmontonBttn = document.getElementById("Edmonton"); // Edmonton button
    const outputDisplay = document.getElementById("output"); // Div to display the weather information
    const locationDisplay = document.getElementById("location"); // Element to show the city name
    const iconDisplay = document.getElementById("icon"); // Element to display the weather icon
    const conditionDisplay = document.getElementById("conditions"); // Element to display the weather conditions
    const windDisplay = document.getElementById("windConditions"); // Element to display wind conditions
    const errorDisplay = document.getElementById("error"); // Element to display error messages
    const temperatureDisplay = document.getElementById("temperature"); // Element to display the temperature

    let outputDisplayFlag = false; // Flag to track if the output display is shown
    let currentCity = ""; // Variable to keep track of the currently selected city

    // Function to get weather data for a specific city
    function getCityData(city, callback) {
        var url = `http://api.openweathermap.org/data/2.5/weather?q=${city}&appid=e2b00f00e57fdc183c78bd553dbf8dbd&units=metric`;

        // Create a new XMLHttpRequest object
        var xhr = new XMLHttpRequest();
        xhr.open('GET', url, true); // Open a GET request to the URL
        xhr.responseType = "json"; // Set the response type to JSON
        xhr.send(null); // Send the request to the server

        // When the response is ready, process it
        xhr.onreadystatechange = function() {
            if (xhr.readyState === 4) { // Check if request has completed
                if (xhr.status === 200) { // If the request was successful
                    var DATA = xhr.response; // Get the JSON data from the response
                    callback(null, DATA); // Call the callback with the data
                } else { // If the request failed
                    console.log(xhr.status); // Log the error status code
                    callback("Error", null); // Call the callback with an error message
                }
            }
        };
    }

    // General function to process and display weather data for any city
    function getWeatherData(city) {
        getCityData(city, function(error, data) {
            if (error) {
                // If there was an error, log it and display the error message
                console.log("Error:", error);
                errorDisplay.innerHTML = error; // Show the error message on the page
            } else {
                // If the data was successfully retrieved, display it
                console.log(data); // Log the data to the console for debugging

                locationDisplay.innerHTML = data.name; // Display the city name
                temperatureDisplay.innerHTML = data.main.temp + "&#8451;"; // Display the temperature with the Celsius symbol
                conditionDisplay.innerHTML = data.weather[0].description; // Display the weather condition (e.g., "clear sky")

                windDisplay.innerHTML = `Wind Speed: ${data.wind.speed} m/s`; // Display the wind speed

                // Construct the URL for the weather icon
                const iconCode = data.weather[0].icon; // Get the icon code from the data
                const iconUrl = `http://openweathermap.org/img/wn/${iconCode}@2x.png`; // Construct the URL for the icon

                // Set the icon image in the HTML
                iconDisplay.innerHTML = `<img src="${iconUrl}" alt="${data.weather[0].description}" />`;
            }
        });
    }

    // Event listener for the Toronto button
    torontoBttn.addEventListener('click', () => {
        // If the output is already visible and the same button is clicked, hide the output
        if (outputDisplayFlag && currentCity === "Toronto") {
            outputDisplay.style.display = 'none'; // Hide the output display
            outputDisplayFlag = false; // Update the flag to indicate the display is hidden
        } else {
            // Otherwise, show the output and fetch the weather data for Toronto
            outputDisplayFlag = true; // Update the flag to indicate the display is visible
            currentCity = "Toronto"; // Set the current city to Toronto
            getWeatherData(currentCity); // Fetch and display Edmonton's weather data
            outputDisplay.style.display = 'block'; // Show the output display
        }
    });

    // Event listener for the Edmonton button
    edmontonBttn.addEventListener('click', () => {
        // If the output is already visible and the same button is clicked, hide the output
        if (outputDisplayFlag && currentCity === "Edmonton") {
            outputDisplay.style.display = 'none'; // Hide the output display
            outputDisplayFlag = false; // Update the flag to indicate the display is hidden
        } else {
            // Otherwise, show the output and fetch the weather data for Edmonton
            outputDisplayFlag = true; // Update the flag to indicate the display is visible
            currentCity = "Edmonton"; // Set the current city to Edmonton
            getWeatherData(currentCity); // Fetch and display Edmonton's weather data
            outputDisplay.style.display = 'block'; // Show the output display
        }
    });
}

