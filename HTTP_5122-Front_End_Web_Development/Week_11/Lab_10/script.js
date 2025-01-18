window.onload = function() {

    console.log("Lab 10");

    var locationHtml = document.getElementById("location");
    var temperatureHtml = document.getElementById("temperature");
    var conditionHtml = document.getElementById("conditions");


   var url = "http:///api.openweathermap.org/data/2.5/weather?q=Toronto&appid=e2b00f00e57fdc183c78bd553dbf8dbd&units=metric";

   // var url = "http:///api.opeznweathermap.org/data/2.5/weather?q=Toronto&appid=e2b00f00e57fdc183c78bd553dbf8dbd&units=metric";

    var xhr = new XMLHttpRequest();

    xhr.open('GET', url, true);

    xhr.responseType = "json";

    xhr.send(null);

    xhr.onreadystatechange = function() {

        if(xhr.readyState === 4){
            if(xhr.status === 200)  {
                var DATA = xhr.response;
                console.log(DATA);

                locationHtml.innerHTML = DATA.name;
                conditionHtml.innerHTML =  capitalizeFirstLetter (DATA.weather[0].description) + ".";
                // conditionHtml.innerHTML =  DATA.weather[0].description;
                temperatureHtml.innerHTML = DATA.main.temp + "&#8451;";
                
            }else{
                locationHtml.innerHTML = "API call was unsuccessful";
                console.log(xhr.status);
            }
        }
    }

    function capitalizeFirstLetter(string) {
        return string.charAt(0).toUpperCase() + string.slice(1);
        }
}