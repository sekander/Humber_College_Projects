// Web Design Project Script

window.onload = function () {

    //-----------------------------------------------Globals------------------------------------------------ 
    
    //const wellnessTrackerArray = [];
    var wellnessTrackerArray = [];

    console.log("Calendar App Loaded");
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------


    //-----------------------------------------Wellness Tracker Function-----------------------------------
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------

    const wellnessTracker = {
        cigarettesSmoked: 0,    // Number of cigarettes smoked today
        exercised: false,       // Whether the user exercised today
        wakeUpTime: '',         // Time the user woke up
        moneySpent: 0,          // Money spent today
        sleepTime: '',          // Time the user went to sleep
        coffeeDrank: 0,         // Number of cups of coffee consumed
        drankVegetableJuice: false, // Whether the user drank vegetable juice

    };
    
    // External Functions (outside of the wellnessTracker object)
    function addCigarette(wellnessTracker) {
        wellnessTracker.cigarettesSmoked += 1;
    }
    function didExercise(wellnessTracker) {
        wellnessTracker.exercised = true;
    }
    function setWakeUpTime(wellnessTracker, time) {
        wellnessTracker.wakeUpTime = time;
    }
    function addMoneySpent(wellnessTracker, amount) {
        wellnessTracker.moneySpent += parseFloat(amount);
    }
    function setSleepTime(wellnessTracker, time) {
        wellnessTracker.sleepTime = time;
    }
    function addCoffee(wellnessTracker) {
        wellnessTracker.coffeeDrank += 1;
    }
    function drinkVegetableJuice(wellnessTracker) {
        wellnessTracker.drankVegetableJuice = true;
    }
    function resetTracker(wellnessTracker) {
        wellnessTracker.cigarettesSmoked = 0;
        wellnessTracker.exercised = false;
        wellnessTracker.wakeUpTime = '';
        wellnessTracker.moneySpent = 0;
        wellnessTracker.sleepTime = '';
        wellnessTracker.coffeeDrank = 0;
        wellnessTracker.drankVegetableJuice = false;
    }
    // Function to calculate score based on the wellness data
    function calculateScore(data) {
        let score = 0;


        // 1. Cigarettes Smoked
        if (data.cigarettesSmoked === 0) {
            score += 20;
        } else if (data.cigarettesSmoked <= 1) {
            score += 10;
        } else if (data.cigarettesSmoked <= 5) {
            score += 5;
        } else {
            score += 0;
        }

        // 2. Exercised
        if (data.exercised) {
            score += 20;
        }

        // 3. Wake Up Time
        let wakeUpHour = parseInt(data.wakeUpTime.split(':')[0]);
        if (wakeUpHour <= 6) {
            score += 10;
        } else if (wakeUpHour === 7) {
            score += 8;
        } else if (wakeUpHour === 8) {
            score += 6;
        } else if (wakeUpHour === 9){
            score += 4;
        } else {
            score += 0;
        }
        

        // 4. Money Spent
        if (data.moneySpent === 0) {
            score += 10;
        } else if (data.moneySpent <= 20) {
            score += 8;
        } else if (data.moneySpent <= 50) {
            score += 5;
        } else {
            score += 0;
        }

        // 5. Sleep Time
        let sleepHour = parseInt(data.sleepTime.split(':')[0]);
        if (sleepHour <= 10) {
            score += 10;
        } else if (sleepHour === 11) {
            score += 8;
        } else if (sleepHour === 11.5) {
            score += 6;
        } else if (sleepHour === 12.5) {
            score += 2;
        } else {
            score += 0;
        }

        // 6. Coffee Drank
        if (data.coffeeDrank === 0) {
            score += 10;
        } else if (data.coffeeDrank <= 2) {
            score += 7;
        } else {
            score += 0;
        }

        // 7. Drank Vegetable Juice
        if (data.drankVegetableJuice) {
            score += 20;
        }

        return score;
    }

    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------


    
    //-----------------------------------------Modal Function----------------------------------------------
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------

    const openModalButtons = document.querySelectorAll('[data-modal-target]');
    const closeModalButtons = document.querySelectorAll('[data-close-button]');
    const overlay = document.getElementById('overlay');

    console.log(openModalButtons);

    openModalButtons.forEach(button => {
        button.addEventListener('click', () => {
            const modal = document.querySelector(button.dataset.modalTarget);
            openModal(modal);
        });
    });

    closeModalButtons.forEach(button => {
        button.addEventListener('click', () => {
            const modal = button.closest('.modal');
            closeModal(modal);
        });
    });

    function scaleDiv() {
        // Get the window width
        var windowWidth = window.innerWidth;

        // Define a base width for scaling. For example, consider 1200px as the base size (scale 1)
        var baseWidth = 1000;

        // Calculate scale factor based on the window width
        var scaleFactor = windowWidth / baseWidth;

        // Get the calendar-month div
        var calendarDiv = document.getElementById('calendar-month');

        console.log("Scale : " + scaleFactor);
        // Apply the scale transformation
    calendarDiv.style.transform = 'scale(' + scaleFactor + ')';
    }
    
    // Debounce function to limit the number of calls during resize
    function debounce(func, delay) {
        let timeout;
        return function() {
            clearTimeout(timeout);
            timeout = setTimeout(func, delay);
        };
    }

    function openModal(modal) {
        if (modal == null) return;



        modal.classList.add('active');
         overlay.classList.add('active');

        
        // Dim the header and container
        //document.querySelector('header').classList.add('dimmed');
        //document.querySelector('footer').classList.add('dimmed');
        document.getElementById('container').classList.add('dimmed');

    }

    function closeModal(modal) {
        if (modal == null) return;

        modal.classList.remove('active');
        overlay.classList.remove('active');
        // Restore the header and container
        //document.querySelector('header').classList.remove('dimmed');
        //document.querySelector('footer').classList.remove('dimmed');
        document.getElementById('container').classList.remove('dimmed');
    }
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------
    
    
    
    //--------------------------------------------Calendar Function----------------------------------------
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------
    function generateCalendarMonth(year, month) {

        const calendar = document.getElementById("calendar");
        const monthHeader = document.getElementById("currentMonth");

        //clear any rows 
        calendar.innerHTML = "";
        // Create the <thead> element
        const thead = document.createElement("thead");

        // Create the <tr> element
        const tr = document.createElement("tr");

        // List of day names
        const daysOfWeek = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];

        var cardFlipped = false;
        var cardFlipCounter = 0;

        // Loop through the days and create <th> elements for each
        daysOfWeek.forEach(day => {
            const th = document.createElement("th");
            th.classList.add("dayHeader");
            th.textContent = day;
            tr.appendChild(th); // Append each <th> to <tr>
        });

        // Append <tr> to <thead>
        thead.appendChild(tr);

        // Append <thead> to the calendar table
        calendar.appendChild(thead);


        var firstDayOfMonth = new Date(year, month).getDay();
        var daysInMonth = new Date(year, month + 1, 0).getDate();

        const monthNames = [
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        ];

        monthHeader.textContent = `${monthNames[month]} ${year}`;

        console.log(firstDayOfMonth);
        console.log(daysInMonth);

        let date = 1;

        //create rows for the week
        for (var i = 0; i < 6; i++) {
            console.log("LOGGGING " + i);
        // for (var i = 0; i < 4; i++) {
            const row = document.createElement("tr");

            //create columns days for each week
            for (var j = 0; j < 7; j++) {
                const cell = document.createElement("th");

                if (date <= daysInMonth) {
                    if (firstDayOfMonth != j && i === 0)
                        cell.textContent = "";
                    else {
                        cell.id = `${month}_${year}_${date}`;
                        //cell.id = `day_${date}`;
                        cell.setAttribute("data-modal-target", "#modal");
                        cell.className = "day";
                        //cell.textContent = date;

                        //Cell Flipping logic
                        // Create the card div with front and back
                        const card = document.createElement('div');
                        card.classList.add('card');

                        const front = document.createElement('div');
                        front.classList.add('front');
                        front.classList.add('square');
                        front.textContent = date; // Display the day number on the front

                        const back = document.createElement('div');
                        back.classList.add('back');
                        back.classList.add('square');
                        // back.textContent = "Details";

                        // Append the front and back to the card
                        card.appendChild(front);
                        card.appendChild(back);

                    // Append the card to the cell
                        cell.appendChild(card);

                        //Create wellnessTracker for each day
                        // Clone the template object to create a new instance
                        let wellnessDay = {...wellnessTracker};

                        wellnessDay.cigarettesSmoked = 0;
                        wellnessDay.exercised = false;
                        wellnessDay.wakeUpTime = '6:00 AM';
                        wellnessDay.moneySpent = 0;
                        wellnessDay.sleepTime = '10:30 PM';
                        wellnessDay.coffeeDrank = 0;
                        wellnessDay.drankVegetableJuice = false;

                        console.log("Adding Wellness Tracker");
                        wellnessTrackerArray.push(wellnessDay);

                        console.log(wellnessTrackerArray);


                        cell.addEventListener("click", () => {
                            //alert(`You clicked on Day ${cell.textContent}`);
                            const dayIndex = parseInt(cell.textContent) - 1;

                            const modal = document.querySelector(cell.dataset.modalTarget);

                            var modalHtml = document.getElementById("modal_title");
                            var modalBodyHtml = document.getElementById("modal-body");

                            // Use a regular expression to match the number at the start of the string
                            const day_number = cell.textContent.match(/^\d+/);

                            modalHtml.textContent = `Day  ${day_number}`;
                            // console.log("CELL CONTEXT: " + str.match(cell.textContent));

                            // Populate modal body with wellness tracker details in a list format
                            modalBodyHtml.innerHTML = `
                                    <h3>Wellness Tracker Details</h3>
                                    <ul>
                                        <div id="${dayIndex}_cigDiv" class="modalBodyButton">
                                        <li id="${dayIndex}_cigText"><strong>Cigarettes Smoked:</strong> ${wellnessTrackerArray[dayIndex].cigarettesSmoked} </li> 
                                        <button id=${dayIndex}_cigBtn>+</button> 
                                        </div>
                                        <div id="${dayIndex}_coffeeDiv" class="modalBodyButton">
                                        <li id="${dayIndex}_coffeeText"><strong>Coffee Drank:</strong> ${wellnessTrackerArray[dayIndex].coffeeDrank} cups </li> 
                                        <button id=${dayIndex}_coffeeBtn>+</button> 
                                        </div>
                                        <div id="${dayIndex}_excDiv" class="modalBodyButton">
                                        <li id="${dayIndex}_excText"><strong>Exercised:</strong> ${wellnessTrackerArray[dayIndex].exercised ? 'Yes' : 'No'} </li> 
                                        <button id=${dayIndex}_excBtn>+</button> 
                                        </div>
                                        <div id="${dayIndex}_vegDiv" class="modalBodyButton">
                                        <li id="${dayIndex}_vegText"><strong>Drank Vegetable Juice:</strong> ${wellnessTrackerArray[dayIndex].drankVegetableJuice ? 'Yes' : 'No'}</li>
                                        <button id=${dayIndex}_vegBtn>+</button>
                                        </div>
                                        <div id="${dayIndex}_moneySpentDiv" class="modalBodyButton">
                                        <li id="${dayIndex}_moneySpentText"><strong>Money Spent:</strong> $${wellnessTrackerArray[dayIndex].moneySpent} </li> 
                                        <input type="number" id=${dayIndex}_moneySpentInput placeholder="0.00" step="1.00" min="0" /> 
                                        </div>
                                        <div id="${dayIndex}_wakeUpDiv" class="modalBodyButton">
                                            <li id="${dayIndex}_wakeupText"><strong>Wake Up Time:</strong> ${wellnessTrackerArray[dayIndex].wakeUpTime} </li> 
                                            <input type="time" id=${dayIndex}_wakeupInput>
                                        </div>
                                        <div id="${dayIndex}_sleepTimeDiv" class="modalBodyButton">
                                        <li id="${dayIndex}_sleepTimeText"><strong>Sleep Time:</strong> ${wellnessTrackerArray[dayIndex].sleepTime} </li> 
                                        <input type="time" id=${dayIndex}_sleepTimeInput> 
                                        </div>
                                    </ul>
                                    <button id="${dayIndex}_saveBtn" class="save-button">save</button>
                                `;


                            const cigBttn = document.getElementById(`${dayIndex}_cigBtn`);
                            const cigText = document.getElementById(`${dayIndex}_cigText`);

                            cigBttn.addEventListener('click', () => {
                                addCigarette(wellnessTrackerArray[dayIndex]);
                                cigText.innerHTML = `<strong>Cigarettes Smoked:</strong> ${wellnessTrackerArray[dayIndex].cigarettesSmoked}`;
                            });

                            const excBttn = document.getElementById(`${dayIndex}_excBtn`);
                            const excText = document.getElementById(`${dayIndex}_excText`);

                            excBttn.addEventListener('click', () => {
                                didExercise(wellnessTrackerArray[dayIndex]);
                                excText.innerHTML = `<strong>Exercised:</strong> ${wellnessTrackerArray[dayIndex].exercised ? 'Yes' : 'No'}`;
                            });

                            const wakeupText = document.getElementById(`${dayIndex}_wakeupText`);
                            const wakeupInput = document.getElementById(`${dayIndex}_wakeupInput`)

                            wakeupInput.addEventListener('input', () => {
                                setWakeUpTime(wellnessTrackerArray[dayIndex], wakeupInput.value);
                                wakeupText.innerHTML = `<strong>Wake Up Time:</strong> ${wakeupInput.value}`;
                            });

                            const moneySpentText = document.getElementById(`${dayIndex}_moneySpentText`);
                            const moneySpentInput = document.getElementById(`${dayIndex}_moneySpentInput`)

                            moneySpentInput.addEventListener('input', () => {
                                addMoneySpent(wellnessTrackerArray[dayIndex], moneySpentInput.value);
                                moneySpentText.innerHTML = `<strong>Money Spent:</strong> ${moneySpentInput.value}`;
                            });

                            const sleepTimeInput = document.getElementById(`${dayIndex}_sleepTimeInput`)
                            const sleepTimeText = document.getElementById(`${dayIndex}_sleepTimeText`);

                            sleepTimeInput.addEventListener('input', () => {
                                setSleepTime(wellnessTrackerArray[dayIndex], sleepTimeInput.value);
                                sleepTimeText.innerHTML = `<strong>Sleep Time:</strong> ${sleepTimeInput.value}`;
                            });

                            const coffeBttn = document.getElementById(`${dayIndex}_coffeeBtn`);
                            const coffeText = document.getElementById(`${dayIndex}_coffeeText`);

                            coffeBttn.addEventListener('click', () => {
                                addCoffee(wellnessTrackerArray[dayIndex]);
                                coffeText.innerHTML = `<strong>Coffee Drank:</strong> ${wellnessTrackerArray[dayIndex].coffeeDrank} cups`;
                            });

                            const vegBttn = document.getElementById(`${dayIndex}_vegBtn`);
                            const vegText = document.getElementById(`${dayIndex}_vegText`);

                            vegBttn.addEventListener('click', () => {
                                drinkVegetableJuice(wellnessTrackerArray[dayIndex]);
                                vegText.innerHTML = `<strong>Drank Vegetable Juice:</strong> ${wellnessTrackerArray[dayIndex].drankVegetableJuice ? 'Yes' : 'No'}`;
                            });
                                
                            const saveBttn = document.getElementById(`${dayIndex}_saveBtn`);

                            saveBttn.addEventListener('click', () => {
                                console.log("Save button Activated for day " + dayIndex);
                                    
                                // Get the data for the specific day
                                let dayData = wellnessTrackerArray[dayIndex];

                                // Calculate the score for this day
                                let score = calculateScore(dayData);
                                    
                                    
                                closeModal(modal);
                                    console.log(score);


                                // Assuming `score` holds the current score value
                                if (score <= 10) {
                                    cell.classList.add('terrible', 'active');
                                } else if (score <= 20) {
                                    cell.classList.add('poor', 'active');
                                } else if (score <= 30) {
                                    cell.classList.add('bad', 'active');
                                } else if (score <= 40) {
                                    cell.classList.add('belowAverage', 'active');
                                } else if (score <= 50) {
                                    cell.classList.add('okay', 'active');
                                } else if (score <= 60) {
                                    cell.classList.add('decent', 'active');
                                } else if (score <= 70) {
                                    cell.classList.add('good', 'active');
                                } else if (score <= 80) {
                                    cell.classList.add('veryGood', 'active');
                                } else if (score <= 90) {
                                    cell.classList.add('excellent', 'active');
                                } else {
                                    cell.classList.add('perfect', 'active');
                                }


                                    
                                cell.classList.add('active');

                                // Using Object.entries to print both keys and values
                                Object.entries(wellnessTrackerArray[dayIndex]).forEach(([key, value]) => {
                                    if (typeof value !== 'function') {  // Only print if the value is not a function
                                        console.log(`${key}: ${value}`);
                                    }
                                });
                                
                                 // Output the total score for the day
                            console.log(`Total Score for day ${dayIndex + 1}: ${score}`);

                            });

                            //Add condition o check if current date 
                            const month_ = (monthNames[month]);  // Assuming month is correctly set
                            const day_ = (cell.id.split('_')[2]);  // Extract the day (after "day_")
                            const year_ = (new Date().getFullYear());  // Current year
                                
                            const formattedDate = `${month_} ${day_}, ${year_}`;

                            console.log(formattedDate);
                            // Get the current date
                            const currentDate = new Date();

                            // Create target date from the formatted date
                            const targetDate = new Date(`${month_} ${day_}, ${year_}`);
                                                    
                            // Compare only the date parts: day, month, and year
                            if (
                                targetDate.getDate() === currentDate.getDate() && 
                                targetDate.getMonth() === currentDate.getMonth() && 
                                targetDate.getFullYear() === currentDate.getFullYear()
                            ) {
                            console.log("The formatted date is today.");
                                dateIsInTheFuture = false;
                                openModal(modal);
                            } else if (targetDate > currentDate) {
                                console.log("The formatted date is in the future.");
                                dateIsInTheFuture = true;
                            } else if (targetDate < currentDate) {
                                console.log("The formatted date is in the past.");
                                dateIsInTheFuture = false;
                                openModal(modal);
                            }
                        });
                           var dayCount = 0;
                    // Add hover effect dynamically
                        cell.addEventListener("mouseover", () => {
                            //Add condition o check if current date 
                            const month_ = (monthNames[month]);  // Assuming month is correctly set
                            const day_ = (cell.id.split('_')[2]);  // Extract the day (after "day_")
                            const year_ = (new Date().getFullYear());  // Current year
                                
                            const formattedDate = `${month_} ${day_}, ${year_}`;

                            console.log("CELL INFO");
                            console.log(day_);
                            console.log(wellnessTrackerArray[day_]);
                            console.log(formattedDate);
                            dayCount++;
                            console.log( "Day Count: " + dayCount);
                            // Get the current date
                            const currentDate = new Date();
                                                    

                            // Create target date from the formatted date
                            const targetDate = new Date(`${month_} ${day_}, ${year_}`);
                            
                            // Check if it has the 'active' class
                            if (cell.classList.contains('active')) {
                                    
                                //This needs work
                                //if(cardFlipCounter <=  1)
                                {
                                    console.log('Cell has the active class.');
                                    //back.textContent = "Need Work";
                                    //console.log(wellnessTrackerArray[day_ - 1]);
                                    // Get the object at the specified index
                                    const jsonObject = wellnessTrackerArray[day_ - 1];

                                        //console.log(jsonObject);
                                    if (dayCount <= 1)
                                        {
                                        // Loop through the keys and values of the object and print them
                                        Object.entries(jsonObject).forEach(([key, value]) => {
                                            console.log(`${key}: ${value}`);
                                            //Ran out of time was trying to implement more`
                                                back.textContent = "Click to Edit/View Progress";
                                                // cardFlipCounter++;
                                                // console.log(cardFlipCounter);
                                                // if (cardFlipCounter < 8 )
                                                    // back.textContent += `${key}: ${value}`;
                                                    // let cs = (key === "cigarettesSmoked") ? value : cs;
                                                    // let e = (key === "exercised") ? value : e;
                                                    // let wt = (key === "wakeUpTime") ? value : wt;
                                                    // let ms = (key === "moneySpent") ? value : ms;
                                                    // let st = (key === "sleepTime") ? value : st;
                                                    // let cd = (key === "coffeeDrank") ? value : cd;
                                                    // let dv = (key === "drankVegetableJuice") ? value : dv;
                                                    // if (key === "cigarettesSmoked")
                                                //back.textContent = `${key}: ${value}`;
                                                    // back.textContent = `
                                                    //       <ul>
                                                    //         <li>Cigarettes Smoked: ${cs} </li>
                                                    //         <li>Exercised: ${e}</li>
                                                    //         <li>Wake Up Time: ${wt}</li>
                                                    //         <li>Money Spent: ${ms}</li>
                                                    //         <li>Sleep Time: ${st}</li>
                                                    //         <li>Coffee Drank: ${cd}</li>
                                                    //         <li>Drank Vegetable Juice: ${dv}</li>
                                                    //     </ul>

                                                    // `
                                        });
                                    }
                                }    
                                const body = document.getElementsByTagName('body')[0];
                                const computedStyle = window.getComputedStyle(cell);
                                const finalBackgroundColor = computedStyle.backgroundColor;

                                body.style.backgroundColor = finalBackgroundColor;
                                console.log(cardFlipCounter);

                            } else {
                                console.log('Cell does not have the active class.');
                                back.textContent = "Details"; 
                            }

                                                    
                            // Compare only the date parts: day, month, and year
                            if (
                                targetDate.getDate() === currentDate.getDate() && 
                                targetDate.getMonth() === currentDate.getMonth() && 
                                targetDate.getFullYear() === currentDate.getFullYear()
                            ) {
                                //Current Day 
                                cell.querySelector('.back').style.backgroundColor = "green";
                                cell.querySelector('.front').style.color = "white";
                      
                                // cell.style.transform = "scale(1.1)";
                                cell.style.cursor = "pointer";
                            }  else if (targetDate < currentDate) {
                                // cell.style.backgroundColor = "lightcoral";
                                cell.style.color = "white";
                                // cell.style.transform = "scale(1.1)";
                                cell.style.cursor = "pointer";
                                // cell.style.transform = "rotateY(180deg)";
                            }  else{
                                cell.style.cursor = "default";
                                cell.querySelector('.card').style.transition = "none";  // Disable transition for future days
                                cell.querySelector('.card').style.transform = "rotateY(0deg)";  // Keep it in the front position
                            }
                        });

                        cell.addEventListener("mouseout", () => {
                            // Resetting to original state on mouse out
                            cell.querySelector('.front').style.backgroundColor = "";
                            cell.querySelector('.front').style.color = "";
                            document.body.style.backgroundColor = 'white';
                            cardFlipCounter = 0;
                            dayCount = 0;
                            
                            {
                            // Dynamically change background to GIF
                                /*
                                 * DRAGONBALL
                                 * https://media.giphy.com/media/F2aE1bfCQl7IA/giphy.gif?cid=790b7611hx9d49acfxh4fae0xbad38idu7l399rqxh8u0fhv&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 *https://media.giphy.com/media/aAbax5anloMNk6TSP9/giphy.gif?cid=ecf05e47hxe8l2ds8ocoz1sgcsbik8e3yq8jdx0j2zfe9pfy&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 *https://media.giphy.com/media/xbL1UwfSic84EDmrcK/giphy.gif?cid=ecf05e4760xdm0ihifd41lyy0yugynevlrsx9x82fjw8ztzy&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/58Uc01V78x1Uk/giphy.gif?cid=ecf05e47b4ghlaxjklnot6sv3dv9mvgdc7tfpg7wtttunndq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/Iqyu5uLlL1ajS/giphy.gif?cid=ecf05e47b4ghlaxjklnot6sv3dv9mvgdc7tfpg7wtttunndq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/1E3izxjVDKZRm/giphy.gif?cid=ecf05e47c1u6abcrjzjyfb2swf22swj1g9s9cfkq74ssfez4&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/GH7rdGafqyeQ0/giphy.gif?cid=ecf05e47haqzlc6ydf3gtub6ezi79vtgegoexbukyt4litco&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/g7oEg8g2jukE0/giphy.gif?cid=ecf05e47haqzlc6ydf3gtub6ezi79vtgegoexbukyt4litco&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/DzeKll1HYxiYo/giphy.gif?cid=ecf05e47haqzlc6ydf3gtub6ezi79vtgegoexbukyt4litco&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/9JxRQ6NOf1orK/giphy.gif?cid=ecf05e47kz4jyvruxc9jdclvtv6ppupepwqhl9ubrtl2xhbh&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                 https://media.giphy.com/media/13HtwCnSoc1ZdK/giphy.gif?cid=ecf05e477b4nbosv5u9253yduvyjmufc7kjvlanhib77ryg3&ep=v1_gifs_search&rid=giphy.gif&ct=g
                                https://media.giphy.com/media/PqcBU8T4SeuO3kOMVu/giphy.gif?cid=ecf05e479hutu5trtvp5ol847zwbpz2mza8i0udqbk7w66zq&ep=v1_gifs_search&rid=giphy.gif&ct=g

                                Anime
                            https://media.giphy.com/media/3o7bugvByW1ZfdGwJW/giphy.gif?cid=790b761128ehznrfjn53005cycsthaqpzmm4pmz3uzra1tru&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExMjhlaHpucmZqbjUzMDA1Y3ljc3RoYXFwem1tNHBtejN1enJhMXRydSZlcD12MV9naWZzX3NlYXJjaCZjdD1n/nlk3Y1u3r1n5C/giphy.gif
                            https://media.giphy.com/media/FqdGGgugkC4Xm/giphy.gif?cid=ecf05e47h1d5pauq2hy8csecwtznmlp4ynjnlo9hzrxqnlil&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExdmVlbGoxdWNjZTV1OHMzOGhveXBkZGYwdXF5d2ZxY2cwdTl5djc0byZlcD12MV9naWZzX3NlYXJjaCZjdD1n/jsoMtBuP1Ahpu/giphy.gif
                            https://media.giphy.com/media/bSgKBZKCxh8Iqlwxne/giphy.gif?cid=790b7611082kyd0ygin73uelk2udn6vq2206sjwtiiiuacmu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/11KzOet1ElBDz2/giphy.gif?cid=790b76112t0hno43zd70ptzv3o2cebnb1cg666qx1hkfn9yq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExZ2NjZ2o0ZmhxdDMyN3Nka3c2dThqdDA5aHdyeDM4eGxmM2Z6OXVvZyZlcD12MV9naWZzX3NlYXJjaCZjdD1n/ispEc1253326c/giphy.gif
                            https://media.giphy.com/media/Yv6RcuiyHYmn6/giphy.gif?cid=ecf05e47ha5mgtr326cy2pf0phupy4leatdi8bji26txj5rx&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/3ohc0PsZLDN5Dgcf5e/giphy.gif?cid=ecf05e478seonn7m03tq7yqg3z8oas8zl62zc37i03d1ujcq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/jKvZYT3pYTy9y/giphy.gif?cid=ecf05e476i1mgk9605nnsrgq4ksl7h685q6vwdk237ijpgly&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/frDFCFK9S4oHm/giphy.gif?cid=ecf05e476i1mgk9605nnsrgq4ksl7h685q6vwdk237ijpgly&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/Gf1RA1jNSpbbuDE40m/giphy.gif?cid=790b7611swbnm7d3usvjtzjwj4rssmjr201533zufdh80mj8&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExOXB2Y3kwaHFsaWFyMDhlaWJob2huOWkyaTJ2ODc4NHM4ZWJpbjNneiZlcD12MV9naWZzX3NlYXJjaCZjdD1n/pUp9Nb1czvHMY/giphy.gif
                            https://media.giphy.com/media/XR9cbNEfzDrFe/giphy.gif?cid=790b76119pvcy0hqliar08eibhohn9i2i2v8784s8ebin3gz&ep=v1_gifs_search&rid=giphy.gif&ct=g

                            marvel
                            https://media.giphy.com/media/zgeZrAyrSCrKaQkitc/giphy.gif?cid=ecf05e47uohzb93lemk6ni00c2tzidznqm2mv5hyy8ugduo7&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/Ri7d8I18cto2jufOKc/giphy.gif?cid=ecf05e47ht4xltwvsb4k4oyk0eim6p63tom8331osld45blj&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/6pYbw8HkA2SO5UKZYj/giphy.gif?cid=ecf05e47ow8zk1xsr29wr2nsbvuy6uc73mq4lpetostqe9nv&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/Af6ldnmNLUXDTk4oyr/giphy.gif?cid=ecf05e47p12dq56a1a14wxdhs80j8edtj1jlsnjn2ddawn94&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/B4bVF2K7Tl5zvumKXG/giphy.gif?cid=ecf05e47nbbu5innmw8i1uistwf39c2ftm0tmgo1y813m5t5&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/EXvjpRdK2rfBAa5DN7/giphy.gif?cid=ecf05e47uo52lt12ize81yxt2shg2v3mklk91eazdas744ao&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/gEwRbygRCpBZFxVj4t/giphy.gif?cid=ecf05e47uo52lt12ize81yxt2shg2v3mklk91eazdas744ao&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/abtXk1Twd1oP295gpM/giphy.gif?cid=ecf05e47h12fptz913fszmgh0ves29k3sm5k2gnvtddxw3th&ep=v1_gifs_search&rid=giphy.gif&ct=g
                            https://media.giphy.com/media/D7ZXU6eiZ4V7AEsOjV/giphy.gif?cid=ecf05e47uy4ese3xet52tz3js4dz8tgqm27xsjcxd1jjzgdd&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/IgFoxYdo7E4zfD4k9y/giphy.gif?cid=ecf05e47uy4ese3xet52tz3js4dz8tgqm27xsjcxd1jjzgdd&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/Y3ZMQtrzy9w3b1vKL9/giphy.gif?cid=790b76110igss6ootcgv68852t44e2oiyuefrvzy3c5ri33z&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/m1f4dtsN7hWbC/giphy.gif?cid=790b7611sl0e7jmonhtus9544x0psdsub9drvpsufskx0tum&ep=v1_gifs_search&rid=giphy.gif&ct=g

                        DC
                        https://media.giphy.com/media/xT0xepnBG2Nh3ukQ2k/giphy.gif?cid=ecf05e4755h1iufq3g58g1s4lzxrzs8twyebnhxy52ynjusg&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExazI1Z3lrMG51NnR4anhkMWl5dmhwOXZzNGgzODZ1aHZ3Z3V4djhkMyZlcD12MV9naWZzX3NlYXJjaCZjdD1n/l396BoOTIFem9xqQU/giphy.gif
                        https://media.giphy.com/media/lTLV2erK8vf1MIz4Rk/giphy.gif?cid=ecf05e47ab4wx35m7a17qyvu6x9ehwjazh1mdb8l7pdf06hb&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/7MTFCnpEOqI5a/giphy.gif?cid=ecf05e473gg3kj5ayt1ai3didnktruh2lu9dvnygezj12e34&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/3o7520lCLgQnTKJ1ni/giphy.gif?cid=ecf05e47tbemokx8113q6dgw486sujamxwmodnqhp2kr50cp&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/l0O9yWXCcLOhFR7xu/giphy.gif?cid=790b7611vgj0n0xawpz2gpnfuncwj7cjla9igg35wxn3ctiq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExeWxwdGVqMXprbGdyc3BlZmFqY3V3aW5mcGJyYmRwZjY1cDB3bmQ3bCZlcD12MV9naWZzX3NlYXJjaCZjdD1n/ktPDzGEpxWGxW/giphy.gif
                        https://media.giphy.com/media/ZSvAC5c9RkW4g/giphy.gif?cid=ecf05e4711rw8htfjfkv7c6bz8jt925glc42i575sy2s4usa&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/qkhrcjj9MGpjO/giphy.gif?cid=790b7611ylptej1zklgrspefajcuwinfpbrbdpf65p0wnd7l&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/iDrtITIIjOXz8YUD2L/giphy.gif?cid=ecf05e47rozgakkw0w5yp6taoyub2o1m3f8fby9h7vso1ioq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/xT5LMY3oG4b4K6RTI4/giphy.gif?cid=ecf05e47gqggju3xenizza3wzyl1bly6zgkx28jh3u0n0p4r&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExcXhjeWIwOTNveGV6cGN6aTg1M2poN3E4N21pNXd6MGduMnE1MjhsZSZlcD12MV9naWZzX3NlYXJjaCZjdD1n/T8o9mVrIMhO6FBJXQc/giphy.gif
                        https://media.giphy.com/media/JKxpqBvzyDpV6/giphy.gif?cid=790b7611qxcyb093oxezpczi853jh7q87mi5wz0gn2q528le&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/eryisLzV7eHD0dgnKq/giphy.gif?cid=ecf05e47erpsktjl990t6v50qne266obrhhiv3ctrnneui07&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/Fnx6d5BBQgTOE/giphy.gif?cid=790b7611vs85ekixx52tva5ngb9hy34xo74vpsoi95gu3edl&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/ibCIiQz8QGdl6/giphy.gif?cid=ecf05e47z4ujjtia16cit92012hmoow9j70tlqxl2i0on3dg&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/FycSuFILgWwfe/giphy.gif?cid=ecf05e47jmb9i3vsze272vw8b983pdm4d0x7afw74yjswvqi&ep=v1_gifs_search&rid=giphy.gif&ct=g`
                        https://media.giphy.com/media/CUEsWj7R9ZC0w/giphy.gif?cid=ecf05e476g8s7vcg7dxiot6ovuq0r37eh8pm88dtiopt4s6y&ep=v1_gifs_search&rid=giphy.gif&ct=g

                        Pokemon
                        https://media.giphy.com/media/pq2pU6B2Ht3pu/giphy.gif?cid=790b7611tg7e6oouz2rz83xjgyuxp2pkmb9nvpo7ikdz8sc2&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/HZpCCbcWc0a3u/giphy.gif?cid=790b7611tg7e6oouz2rz83xjgyuxp2pkmb9nvpo7ikdz8sc2&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/rCftUAVPLExZC/giphy.gif?cid=790b7611tg7e6oouz2rz83xjgyuxp2pkmb9nvpo7ikdz8sc2&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/10LKovKon8DENq/giphy.gif?cid=790b7611tg7e6oouz2rz83xjgyuxp2pkmb9nvpo7ikdz8sc2&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/pPzjpxJXa0pna/giphy.gif?cid=790b7611tg7e6oouz2rz83xjgyuxp2pkmb9nvpo7ikdz8sc2&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/5FYcVhG2mvzGw/giphy.gif?cid=ecf05e470d1hjudy4bt17i83qpejfbudwzy7kaeyb4z82t9v&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/iIbgY9P1m0woM/giphy.gif?cid=ecf05e4714fg5vw2du5areyrp7kzb3ivkr5pzbikg3wdiggi&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/LxSFsOTa3ytEY/giphy.gif?cid=ecf05e471e3jrf1rv7st8m2x0n60zcypobcu4x6p8rr3whcq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/Tf3mp01bfrrUc/giphy.gif?cid=ecf05e471e3jrf1rv7st8m2x0n60zcypobcu4x6p8rr3whcq&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/QzxONYL3xbj6E/giphy.gif?cid=ecf05e47ya5lagj6aop91sf9ux37u1selud6z1wlzexh8tt2&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/lM86pZcDxfx5e/giphy.gif?cid=ecf05e47qyou9n8ze1etvbj6n69tovfu69sblaa6vb9wzcp1&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/Jir3toQTWW9Ne/giphy.gif?cid=ecf05e470t01r99s7mf6tmaa81cj0llct8bhxupvy81x11mt&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/WLXO8OZmq0JK8/giphy.gif?cid=ecf05e47tesapcebiei3dtner87yi0tg4di6r43ujoj8zghb&ep=v1_gifs_search&rid=giphy.gif&ct=g

                        Digimon
                        https://media.giphy.com/media/11TkuRl1Ff32ak/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/8ySKwtFNY28BDGlzp7/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/9VkjMqcDbpNfuKWqmi/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/joYGxDpl7ltxhlIzIm/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/xUOwG2KEKQb4VBPKKc/giphy.gif?cid=ecf05e47ntsu9fiqmll2ax1kip8mrt0nfnm174t9makfi55b&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/jz1iZxHbCwxSE/giphy.gif?cid=ecf05e47tbmk7ru761cgq7jpzbvv5cxhclyxdxnz4gy78xtf&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/2fxVeABUhHjUI/giphy.gif?cid=ecf05e47iz5zenqyrnwi5xe4ofdhnilld5vpmvdrkvrl2gyl&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/xThtaivfYE4jpMKAhy/giphy.gif?cid=ecf05e47ntsu9fiqmll2ax1kip8mrt0nfnm174t9makfi55b&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/zXuWZsgMZt3xe/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/UOvFfXGINpmN2/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/IkLhbMyv1TOymOM9Zi/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/joYGxDpl7ltxhlIzIm/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/3Um5ZDccyEzzq/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/i0UqJCLZky1Qk/giphy.gif?cid=790b7611yc2jpwqp4qxhbqx892lrwqdulhpmzeptww8r47eu&ep=v1_gifs_search&rid=giphy.gif&ct=g

                        star wars 
                        https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExbmU2NWF3dWxocXZnYnBqZTExcTFndXNoOHlocmhxcGZpa2M3Y3F0ZSZlcD12MV9naWZzX3NlYXJjaCZjdD1n/jd6TVgsph6w7e/giphy.gif
                        https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExbmU2NWF3dWxocXZnYnBqZTExcTFndXNoOHlocmhxcGZpa2M3Y3F0ZSZlcD12MV9naWZzX3NlYXJjaCZjdD1n/3ornjPteRwwUdSWifC/giphy.gif
                        https://media.giphy.com/media/krkrHAEodHgzP72rTI/giphy.gif?cid=790b7611ne65awulhqvgbpje11q1gush8yhrhqpfikc7cqte&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/J1nr4o7oolWz6/giphy.gif?cid=790b7611ne65awulhqvgbpje11q1gush8yhrhqpfikc7cqte&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/26FLh6p0NIYPlecCs/giphy.gif?cid=ecf05e47d0fmjw6lpgh2lbgkhcg7i2vux3dbo9gp31jpkay5&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/l2JIaZ8htFKgqwqB2/giphy.gif?cid=ecf05e47ibqnkwwujwjtmn29fpitnnmg3zbi2b2tssrrad6s&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/imk9FPVJta5dC/giphy.gif?cid=ecf05e47ibqnkwwujwjtmn29fpitnnmg3zbi2b2tssrrad6s&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/UG2PNPF0N2ro4/giphy.gif?cid=ecf05e47ibqnkwwujwjtmn29fpitnnmg3zbi2b2tssrrad6s&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/9E7kUhnT9eDok/giphy.gif?cid=ecf05e47enadcmb8wm10z2ce2cybz2r7cx534kt1tqvxj0l6&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/3og0IuwGm4BIHkdjfq/giphy.gif?cid=ecf05e47p18yp514fdj2c78mxp4l3ug4b130f8bj4r1jw6un&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/xT9DPr4VjeCgeiLoMo/giphy.gif?cid=ecf05e47g25e8iajoq7mzskl987tn0ec2daow19okxc10aai&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/Nm1gtrpRWTYRO/giphy.gif?cid=ecf05e47g25e8iajoq7mzskl987tn0ec2daow19okxc10aai&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/fHrLstcrvUtEVJqiR1/giphy.gif?cid=ecf05e47t8zuutdmgs74tvptr06mt9340033c2tfcdxsko0r&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/JsDzMHc0Edo4YnDQxP/giphy.gif?cid=ecf05e47xvm1pyuyz2wuazmz19ub5gby1uhbjmplz9a8ptyo&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/26FxzFK4yudFHRFde/giphy.gif?cid=ecf05e4706e48mbvi1srqtygxv6yc66vasfin48g3e658xc9&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/mZAL1GTRA8VnkRaU47/giphy.gif?cid=ecf05e4706e48mbvi1srqtygxv6yc66vasfin48g3e658xc9&ep=v1_gifs_search&rid=giphy.gif&ct=g

                        star trek 
                        https://media.giphy.com/media/RkHMFkFFPMdMisxcQo/giphy.gif?cid=790b7611mq5k2rwkmb5be1ji1r11lr4afck7elbqazz9jdb6&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/l1xvArCcP5qHmeHI38/giphy.gif?cid=790b7611mq5k2rwkmb5be1ji1r11lr4afck7elbqazz9jdb6&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/QXaGuzIgNSm8OnnyV5/giphy.gif?cid=790b7611mq5k2rwkmb5be1ji1r11lr4afck7elbqazz9jdb6&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/ftZFPBRuTA6fmfT2fN/giphy.gif?cid=790b7611mq5k2rwkmb5be1ji1r11lr4afck7elbqazz9jdb6&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/2yA7T0F1AQHhg0I7GA/giphy.gif?cid=ecf05e47xn0smedr7qa9aanmz69b44d9kre63nre4zub0205&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/Wkym7gz6fu1Nu/giphy.gif?cid=ecf05e47xn0smedr7qa9aanmz69b44d9kre63nre4zub0205&ep=v1_gifs_search&rid=giphy.gif&ct=g
                        https://media.giphy.com/media/LtyywqYw5NgNq/giphy.gif?cid=ecf05e478g1hqyiilwgz6740gzo6ir82g00nvsfwdzuosv2c&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/2wTBgxQIxHDfY0Qzof/giphy.gif?cid=ecf05e47yq0o5jil4yq1x4lenb5c9379nazkaqtixxo8hp07&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/26uf9QPzzlKPvQG5O/giphy.gif?cid=ecf05e47zm6ihnn6ap9v61ze4y8cbma30z2ijhctvlsy0nyt&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/U7zQgz9ag9HbprhU5K/giphy.gif?cid=ecf05e47zm6ihnn6ap9v61ze4y8cbma30z2ijhctvlsy0nyt&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/GnqgAJvlpkK76/giphy.gif?cid=ecf05e47oyqoqossikawh17w9f03u5ocdgdqm56fw90tsho4&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/l3vRkn9iNtQIye1KE/giphy.gif?cid=ecf05e47w8kz8c96dazx6om26adjdxbdxqchwbmdz2jt4pdt&ep=v1_gifs_search&rid=giphy.gif&ct=g
                    https://media.giphy.com/media/EWH6fBrJA7oQQv6px8/giphy.gif?cid=ecf05e47t98oufjqdono693b1eha4osclnyhuolypldpb6lt&ep=v1_gifs_search&rid=giphy.gif&ct=g


                    





                             

                                 * */
                            // document.body.style.backgroundImage = "url('https://media.giphy.com/media/F2aE1bfCQl7IA/giphy.gif?cid=790b7611hx9d49acfxh4fae0xbad38idu7l399rqxh8u0fhv&ep=v1_gifs_search&rid=giphy.gif&ct=g')";
                            // document.body.style.backgroundSize = "cover";
                            // document.body.style.backgroundPosition = "center";
                            // document.body.style.backgroundRepeat = "no-repeat";
                            



                            // cell.style.backgroundColor = "";
                            // cell.style.color = "black";
                            // cell.style.transform = "scale(1)";

                            }
                        });

                        date++;
                        firstDayOfMonth++;
                    }
                }
                calendar.appendChild(cell);
            }
            calendar.appendChild(row);
        }
    }

    // // Call scaleDiv on window resize with debouncing (300ms delay)
    // const debouncedScaleDiv = debounce(scaleDiv, 300);

    // scaleDiv();


    // // Add an event listener for window resize
    // window.addEventListener('resize', debouncedScaleDiv);

    const nextMonth = document.getElementById('next-month');
    const prevMonth = document.getElementById('prev-month');


    const currentDate = new Date();
    const currentMonth = currentDate.getMonth(); // Returns 0-11, where 0 is January and 11 is December
    const currentYear = currentDate.getFullYear(); // Returns the full 4-digit year (e.g., 2024)

    var counter = 0;
    var monthLog = currentMonth;
    var yearLog = currentYear;
    const calendarMonth = document.getElementById('calendar-month');

 
    nextMonth.addEventListener('click', () => {
        // Increment the month
        monthLog += 1;

        // If the month exceeds 11 (December), adjust the year
        if (monthLog > 11) {
            monthLog = 0; // Reset to January
            yearLog += 1; // Increase the year
        }
        
        $(calendarMonth).animate(
            {
                marginLeft: '100%',
                opacity: 0,
            }, 'slow',
            function () {
                //After the first animation completes
                //Reset Position
                $(calendarMonth).css('marginLeft', '-100%');
                generateCalendarMonth(yearLog, monthLog);
                $(calendarMonth).animate(
                    {
                        marginLeft: '0',    //Alide in to the original position
                        opacity: 1,
                    }, 'slow'
                );
            }
        );
    });


    prevMonth.addEventListener('click', () => {
        // Decrement the month
        monthLog -= 1;

        // If the month is less than 0 (January), adjust the year
        if (monthLog < 0) {
            monthLog = 11; // Set to December
            yearLog -= 1; // Decrease the year
        }

        $(calendarMonth).animate(
            {
                marginLeft: '-100%',
                opacity: 0,
            }, 'slow',
            function () {
                //After the first animation completes
                //Reset Position
                $(calendarMonth).css('marginLeft', '100%');
                generateCalendarMonth(yearLog, monthLog);
                $(calendarMonth).animate(
                    {
                        marginLeft: '0',    //Alide in to the original position
                        opacity: 1,
                    }, 'slow'
                );
            }
        );
    });

    generateCalendarMonth(currentYear, currentMonth + counter);
    
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------


    //-------------------------------------------Save/Load Function----------------------------------------
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------


    const saveBtn = document.getElementById('save-button');
    const loadBtn = document.getElementById('load-button');

    saveBtn.addEventListener('click', () => {
        localStorage.setItem(`${monthLog}_${yearLog}_wellnessTracker`, JSON.stringify(wellnessTrackerArray));

        const dayElements = document.querySelectorAll('th.day');  // Select all <th> elements with class "day"
        const dayState = [];

        dayElements.forEach(day => {
            // Save the id, class, and inline styles of each <th> element
            dayState.push({
                id: day.id,
                classList: Array.from(day.classList),  // Convert classList to array
            });
        });

        // Save to localStorage
        localStorage.setItem(`${monthLog}_${yearLog}_dayState`, JSON.stringify(dayState));
        console.log('Table state saved:', dayState);
        console.log("Data saved to localStorage.");
    });



    loadBtn.addEventListener('click', () => {
        //const loadedWellnessData = JSON.parse(localStorage.getItem("wellnessTracker"));
        const loadedWellnessData = JSON.parse(localStorage.getItem(`${monthLog}_${yearLog}_wellnessTracker`));
        if (loadedWellnessData) {
            console.log("Loaded wellness data:", loadedWellnessData);
            
            wellnessTrackerArray = loadedWellnessData; 

        } else {
            console.log("No wellness data found in localStorage.");
        }

        //Load saved styles from localStorage
        const savedState = JSON.parse(localStorage.getItem(`${monthLog}_${yearLog}_dayState`));
        if (savedState) { 
            savedState.forEach(state => {
                const dayElement = document.getElementById(state.id);  // Get the <th> by its id
                if (dayElement) {
                    // Restore the class
                    dayElement.className = '';  // Clear any existing classes
                    state.classList.forEach(className => {
                        dayElement.classList.add(className);  // Re-add the classes
                    });
                }
        });
            console.log('Table state loaded:', savedState);
        } else {
            console.log('No saved state found.');
        }
    });
    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------
}
