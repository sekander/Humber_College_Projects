window.onload = function () 
{
    /*-- Front End Pet Project Script File*/

        const container = document.getElementById('app-screen');
    // Clear previous divs
    container.innerHTML = '';

    //Player object 
    const playerTemplate = {
        playerID: 0,
        playerLifePoints: 40,
        commanderDeaths: 0,
        lands: 0,
        tokens: 0,
        totalDeck: 99, // Default deck size
        graveyard: 0,
        exiledCards: 0,
        // timer: '00:00',

        increaseLifePoint: function (amount) {
            this.playerLifePoints += amount;
        },

            decreaseLifePoint: function (amount) {
            if(this.playerLifePoints > 0) this.playerLifePoints -= amount;
        },

        incrementCommanderDeath: function () {
            this.commanderDeaths += 1;
        },
        // Methods for lands
        addLand: function () {
            this.lands += 1;
        },

        removeLand: function () {
            if (this.lands > 0) this.lands -= 1;
        },

        // Methods for tokens
        addToken: function () {
            this.tokens += 1;
        },

        removeToken: function () {
            if (this.tokens > 0) this.tokens -= 1;
        },

        // Method for graveyard
        addToGraveyard: function () {
            this.graveyard += 1;
        },

        removeFromGraveyard: function () {
            if (this.graveyard > 0) this.graveyard -= 1;
        },

        // Method for exiled cards
        addExiledCard: function () {
            this.exiledCards += 1;
        },

        // Method for total Deck count
        addCardsToDeck: function () {
            if (this.totalDeck < 99 ) this.totalDeck += 1;
        },

        removeCardFromDeck: function () {
            if (this.totalDeck > 0) this.totalDeck -= 1;
        },

        // // Method for setting/updating the timer
        // updateTimer: function (time) {
        //     this.timer = time;
        // }
    };

    //Helper function to format time 
    function formatTime(secondsElapsed) {
        const minutes = Math.floor(secondsElapsed / 60);  // Calculate minutes
        const seconds = secondsElapsed % 60;  // Calculate remaining seconds

        // Format minutes and seconds to always be 2 digits
        const formattedMinutes = minutes < 10 ? '0' + minutes : minutes;
        const formattedSeconds = seconds < 10 ? '0' + seconds : seconds;

        // Return the formatted time string in MM:SS format
        return `${formattedMinutes}:${formattedSeconds}`;
    }

    //Build Input buttons to enter how many player 1 - 4
    const playerArray = [];
    var numberOfPlayers;
    // var gameStarted = false;

     // Get the buttons by ID
    const onePlayerButton = document.getElementById('one-player');
    const twoPlayerButton = document.getElementById('two-player');
    const threePlayerButton = document.getElementById('three-player');
    const fourPlayerButton = document.getElementById('four-player');
    
    // Helper function to handle the player selection logic
    function setActivePlayerButton(selectedButton, numberOfPlayers) {
        // Set the active button and update the number of players
        selectedButton.classList.add('active');
        container.style.setProperty('--players', numberOfPlayers);

        // Remove 'active' class from all other buttons
        [onePlayerButton, twoPlayerButton, threePlayerButton, fourPlayerButton].forEach(button => {
            if (button !== selectedButton) {
                button.classList.remove('active');
            }
        });
    }

    // Add event listeners for each button to determine how many players
    onePlayerButton.addEventListener('click', function () {
        console.log('1 Player Selected');
        numberOfPlayers = 1;    
        setActivePlayerButton(onePlayerButton, numberOfPlayers);
    });

    twoPlayerButton.addEventListener('click', function () {
        console.log('2 Players Selected');
        numberOfPlayers = 2;    
        setActivePlayerButton(twoPlayerButton, numberOfPlayers);
    });

    threePlayerButton.addEventListener('click', function () {
        console.log('3 Players Selected');
        numberOfPlayers = 3;    
        setActivePlayerButton(threePlayerButton, numberOfPlayers);
    });

    fourPlayerButton.addEventListener('click', function () {
        console.log('4 Players Selected');
            numberOfPlayers = 4;    
        setActivePlayerButton(fourPlayerButton, numberOfPlayers);
    });

    // Optionally, add a listener for the Start button
    const startButton = document.getElementById('start-button');
    startButton.addEventListener('click', function () {
    console.log('App Started');

    document.getElementById("app-screen").style.display = 'contents';
    document.getElementById("start-menu").style.display = 'none';
        /*
        const infoButton = document.getElementById("mtg-info-button");
        var infoMenuActive = false;

         infoButton.addEventListener('click', () => {
             infoMenuActive = !infoMenuActive;
             const players = document.querySelectorAll('.player-div');
             if(infoMenuActive)
             {
                 players.forEach(player => {
                     player.style.display = 'none';
                 });

                const mtgInfoDiv = document.getElementById('mtg-info-div');
                     mtgInfoDiv.style.display = 'block';
                
             }
             else {
                 players.forEach(player => {
                     player.style.display = 'contents';
                 });

                 const mtgInfoDiv = document.getElementById('mtg-info-div');
                     mtgInfoDiv.style.display = 'none';
             }
         });
         */


    //Dynamically create player life point card based on number of players 
        var playerStatContainerActive = true;
        {
        for (var i = 0; i < numberOfPlayers; i++) {
                // Clone the template object to create a new instance
                // ...(Spread operator ) to clone 
                let player = {...playerTemplate};

                player.playerID = i;
                player.playerLifePoints = 40;
                player.commanderDeaths = 0;

                console.log("Adding Player");
                playerArray.push(player);
            }


            //Loop through player count and dynamically create player life point card
            playerArray.forEach(function (p, index) {
                console.log(`Player ${index + 1}:`);
                console.log(`ID : ${p.playerID}`);
                console.log(`LifePoints : ${p.playerLifePoints}`);
                console.log(`Commander Deaths : ${p.commanderDeaths}`);

                console.log(p);

                const playerDiv = document.createElement('div');
                playerDiv.className = 'player-div';
                playerDiv.id = `player-div-${p.playerID}`;
                playerDiv.textContent = `Player ${p.playerID + 1}`;
                // Set default border and box-shadow 
                playerDiv.style.boxShadow = '0 4px 8px rgba(0, 0, 0, 0.2)';  // Default box shadow
                
                
                    //playerDiv.style.border = '2px solid rgba(0, 0, 255, 0.5)';  // Default border color (blue)
                    // Set the border color based on the player index
                    switch (index % 4) {
                        case 0:
                            playerDiv.style.border = '2px solid red';   // Player 1's border: Red
                            break;
                        case 1:
                            playerDiv.style.border = '2px solid blue';  // Player 2's border: Blue
                            break;
                        case 2:
                            playerDiv.style.border = '2px solid green'; // Player 3's border: Green
                            break;
                        case 3:
                            playerDiv.style.border = '2px solid yellow'; // Player 4's border: Yellow
                            break;
                        default:
                            playerDiv.style.border = '2px solid grey';  // Default border color (if needed)
                            break;
                    }

                container.appendChild(playerDiv);

                const _playerID = document.createElement('h2');
                _playerID.id = `playerLifePoint_${p.playerID}`;
                _playerID.textContent = p.playerLifePoints; // Set h2 text
                _playerID.className = `css_playerLife ${p.playerID}`; // Assign css class for styling


                //Logic for plus player life points
                const plusButton = document.createElement('button');
                plusButton.id = `increasePlayerLife_${p.playerID}`;
                plusButton.className = 'lifeButton';
                plusButton.textContent = '+';
                plusButton.onmouseover = function () {
                    plusButton.style.backgroundColor = ' #0056b3'; /* Darker blue on hover */
                };
                plusButton.onmouseout = function () {
                    plusButton.style.backgroundColor = '#007bff'; // Original blue
                };
                
                //Logic for minus player life points
                const minusButton = document.createElement('button');
                minusButton.id = `decreasePlayerLife_${p.playerID}`;
                minusButton.className = 'lifeButton';
                minusButton.textContent = '-';
                minusButton.style.backgroundColor = '#ff000d';
                minusButton.onmouseover = function () {
                    minusButton.style.backgroundColor = '#cc000a'; // Darker red
                };
                minusButton.onmouseout = function () {
                    minusButton.style.backgroundColor = '#ff000d'; // Original red
                };

                // Create an input field to directly change the life points
                const lifePointsInput = document.createElement('input');
                lifePointsInput.type = 'number';
                lifePointsInput.value = p.playerLifePoints; // Set initial value
                lifePointsInput.className = 'life-input';
                lifePointsInput.min = 0;  // Set minimum value to 0
                lifePointsInput.max = 9999;  // Set maximum value to 9999
                lifePointsInput.id = `lifePointsInput_${p.playerID}`;

                // Create a container for the life points and buttons
                const lifeContainer = document.createElement('div');
                lifeContainer.className = 'life-container';

                // Append the life point and buttons to the container
                lifeContainer.appendChild(minusButton);
                lifeContainer.appendChild(_playerID);
                lifeContainer.appendChild(plusButton);

                // Append the container to the player div
                playerDiv.appendChild(lifeContainer);
                playerDiv.appendChild(lifePointsInput); // Add the input field here

                // Create a new container for player stats
                const playerStatsContainer = document.createElement('div');
                playerStatsContainer.className = 'player-stats-container'; // Add class for styling

                const expandPlayerStatButton = document.createElement('button');
                expandPlayerStatButton.id = `plusStatButton__${p.playerID}`;
                expandPlayerStatButton.className = 'expandStatButton';
                expandPlayerStatButton.textContent = '-';
                

                playerStatsContainer.appendChild(expandPlayerStatButton);

                const playerStatsContainerDiv = document.createElement('div');
                playerStatsContainerDiv.id = `player-stats-container_${p.playerID}`; // Add class for styling

                //Open / Close player stats 
                expandPlayerStatButton.addEventListener('click', () => {
                    playerStatContainerActive = !playerStatContainerActive;
                    expandPlayerStatButton.textContent = playerStatContainerActive ? '-' : '+';
                    if(!playerStatContainerActive){
                        playerStatsContainerDiv.style.display = 'none';
                        playerStatsContainerDiv.style.height = '10%';
                    }
                    else
                    {
                        playerStatsContainerDiv.style.display = 'block';
                        playerStatsContainerDiv.style.height = '100%';
                    }
                });

                expandPlayerStatButton.addEventListener('mouseover', () => {
                    expandPlayerStatButton.style.backgroundColor = 'white';
                    expandPlayerStatButton.style.color = 'black';
                });
                expandPlayerStatButton.addEventListener('mouseout', () => {
                    expandPlayerStatButton.style.backgroundColor = 'black';
                    expandPlayerStatButton.style.color = 'white';
                });

                // Array of stats for the player
                const stats = [
                    {id: 'lands', label: 'Lands', value: p.lands || 0},
                    {id: 'totalTokens', label: 'Total Tokens', value: p.tokens || 0},
                    {id: 'totalDeck', label: 'Total Deck', value: p.totalDeck || 0},
                    {id: 'graveyard', label: 'Total Graveyard', value: p.graveyard || 0},
                    {id: 'exiledCards', label: 'Total Exiled Cards', value: p.exiledCards || 0},
                    {id: 'commanderDeaths', label: 'Commander Deaths', value: p.commanderDeaths || 0},  // Add commander deaths to the stats
                    {id: 'timer', label: 'Timer', value: p.timer || '00:00'},
                ];

                // Loop through each stat and create elements
                stats.forEach(stat => {
                    const statLabel = document.createElement('p');
                    statLabel.textContent = `${stat.label}:`;
                    statLabel.className = 'stats-item';

                    const statValue = document.createElement('p');
                    statValue.textContent = stat.value;
                    statValue.id = `${stat.id}_${p.playerID}`;
                    statValue.className = 'stats-item';


                    const plusButton = document.createElement('button');
                    plusButton.id = `plusButton_${stat.id}_${p.playerID}`;
                    plusButton.className = 'statButton';
                    plusButton.textContent = stat.id === 'timer' ? '►/■' : '+';

                    let minusButton = null;

                    if(stat.id !== 'exiledCards' && stat.id !== 'commanderDeaths' && stat.id !== 'timer')
                    {
                        //const minusButton = document.createElement('button');
                        minusButton = document.createElement('button');
                        minusButton.id = `minusButton_${stat.id}_${p.playerID}`;
                        minusButton.className = 'statButton';
                        minusButton.textContent = '-';
                        minusButton.style.backgroundColor = '#ff000d';
                        minusButton.onmouseover = function () {
                            minusButton.style.backgroundColor = '#cc000a'; // Darker red
                        };
                        minusButton.onmouseout = function () {
                            minusButton.style.backgroundColor = '#ff000d'; // Original red
                        };
                    }

                    // Event listener for Plus button (increment stat value)
                    plusButton.addEventListener('click', () => {
                        if (stat.id === 'lands') {
                            p.addLand();
                        } else if (stat.id === 'totalTokens') {
                            p.addToken();
                        } else if (stat.id === 'graveyard') {
                            p.addToGraveyard();
                        } else if (stat.id === 'exiledCards') {
                            p.addExiledCard();
                        } else if (stat.id === 'totalDeck') {
                            p.addCardsToDeck();
                        } else if (stat.id === 'commanderDeaths') {
                            p.incrementCommanderDeath(); // Increment commander death
                        }
                        statValue.textContent = stat.value;
                    });

                    if(minusButton){
                        // Event listener for Minus button (decrement stat value)
                        minusButton.addEventListener('click', () => {
                            if (stat.id === 'lands') {
                                p.removeLand();
                            } else if (stat.id === 'totalTokens') {
                                p.removeToken();
                            } else if (stat.id === 'graveyard') {
                                p.removeFromGraveyard();
                            } else if (stat.id === 'totalDeck') {
                                p.removeCardFromDeck();
                            } 
                            statValue.textContent = stat.value;
                        });
                    }

                    // Create a wrapper div for the buttons
                    const buttons = document.createElement('div');
                    buttons.className = 'stat-buttons';
                    if(minusButton) buttons.appendChild(minusButton);
                    buttons.appendChild(plusButton);
                    
                    // Create a wrapper div for the buttons
                    const labelAndValues = document.createElement('div');
                    labelAndValues.className = 'stat-label-values';
                    labelAndValues.appendChild(statLabel);
                    labelAndValues.appendChild(statValue);

                    const statContainer = document.createElement('div');
                    statContainer.className = 'stat-row';

                    statContainer.appendChild(labelAndValues);
                    statContainer.appendChild(buttons);

                    playerStatsContainerDiv.appendChild(statContainer);

                    //playerStatsContainer.appendChild(statContainer);
                        playerStatsContainer.appendChild(playerStatsContainerDiv);

                });

                playerDiv.appendChild(playerStatsContainer);
    
                // Set up event for player state buttons
                $(`#increasePlayerLife_${p.playerID}`).click(function () {
                    p.increaseLifePoint(1);
                    $(`#playerLifePoint_${p.playerID}`).text(p.playerLifePoints);
                });

                $(`#decreasePlayerLife_${p.playerID}`).click(function () {
                    p.decreaseLifePoint(1);
                    $(`#playerLifePoint_${p.playerID}`).text(p.playerLifePoints);
                });
                
                $(`#plusButton_lands_${p.playerID}`).click(function () {
                document.getElementById(`lands_${p.playerID}`).textContent = p.lands;
                });
                $(`#minusButton_lands_${p.playerID}`).click(function () {
                    document.getElementById(`lands_${p.playerID}`).textContent = p.lands;
                });
                
                $(`#plusButton_totalTokens_${p.playerID}`).click(function () {
                    document.getElementById(`totalTokens_${p.playerID}`).textContent = p.tokens;
                });
                $(`#minusButton_totalTokens_${p.playerID}`).click(function () {
                    document.getElementById(`totalTokens_${p.playerID}`).textContent = p.tokens;
                });
                $(`#plusButton_totalDeck_${p.playerID}`).click(function () {
                    document.getElementById(`totalDeck_${p.playerID}`).textContent = p.totalDeck;
                });
                $(`#minusButton_totalDeck_${p.playerID}`).click(function () {
                    document.getElementById(`totalDeck_${p.playerID}`).textContent = p.totalDeck;
                });

                $(`#plusButton_graveyard_${p.playerID}`).click(function () {
                    document.getElementById(`graveyard_${p.playerID}`).textContent = p.graveyard;
                });
                $(`#minusButton_graveyard_${p.playerID}`).click(function () {
                    document.getElementById(`graveyard_${p.playerID}`).textContent = p.graveyard;
                });
                // Event listeners for player input updates
                $(`#plusButton_exiledCards_${p.playerID}`).click(function () {
                    document.getElementById(`exiledCards_${p.playerID}`).textContent = p.exiledCards;
                });
                $(`#plusButton_commanderDeaths_${p.playerID}`).click(function () {
                    document.getElementById(`commanderDeaths_${p.playerID}`).textContent = p.commanderDeaths;
                });


                //Time Variables
                var startTimer = false;
                var timeInterval = null; 
                var secondsElapsed = 0;

                // //Sine Wave Varaibles
                // const ampliture = 50;
                // const offset = 50;
                // const maxValue = 100;

                $(`#plusButton_timer_${p.playerID}`).click(function () {
                    startTimer = !startTimer;
                    console.log(p.playerID);
                    console.log( startTimer);
                    const playerDivBackground = document.getElementById(`player-div-${p.playerID}`)

                    console.log(playerDivBackground);

                    if(startTimer)
                    {
                         // Disable all other plus buttons
                         //Future Implementations
                        
                        if(!timeInterval)
                        {
                            //Set box shadow to indicate players turn  
                            switch (p.playerID % 4) {
                                case 0:
                                    playerDivBackground.style.boxShadow =  '0 0 15px 5px rgba(255, 8, 8, 0.86)';
                                    break;
                                case 1:
                                    playerDivBackground.style.boxShadow =  '0 0 15px 5px rgba(0, 0, 255, 0.86)';
                                    break;
                                case 2:
                                    playerDivBackground.style.boxShadow =  '0 0 15px 5px rgba(0, 255, 0, 0.86)';
                                    break;
                                case 3:
                                    // playerDiv.style.border = '2px solid yellow'; // Player 4's border: Yellow
                                    playerDivBackground.style.boxShadow =  '0 0 15px 5px rgba(229, 253, 8, 0.86)';
                                    break;
                                default:
                                    playerDivBackground.style.backgroundColor = 'rgba(0, 34, 255, 0.39)';
                                    break;
                            }

                            timeInterval = setInterval(function () {
                                secondsElapsed++;
                                document.getElementById(`timer_${p.playerID}`).textContent = formatTime( secondsElapsed);

                                //Future Implementations 
                                //var sineWave = ampliture * Math.sin(2 * Math.PI * 1 * secondsElapsed) + offset;
                                //playerDivBackground.style.backgroundColor = `rgba(0, 255, 0, ${sineWave/100} )`;


                                // Adjust the sine wave to fluctuate between 0.1 and 1.0
                                // var sineWave = (Math.sin(2 * Math.PI * 1 * secondsElapsed) / 2) + 0.5; // Range from 0 to 1
                                // sineWave = Math.max(0.1, Math.min(sineWave, 1.0)); // Clamp between 0.1 and 1.0
                                // playerDivBackground.style.backgroundColor = `rgba(0, 255, 0, ${sineWave} )`;


                                // console.log(sineWave/100);

                            // }, 10);
                            }, 1000);
                        }
                    }
                    else{
                        // Stop the timer and clear the interval when `startTimer` is false
                        if (timeInterval) {
                            //playerDivBackground.classList.remove('active');
                            //playerDivBackground.style.backgroundColor = '#2a2a2a'; /* Slightly lighter dark background for player div */
                            playerDivBackground.style.boxShadow = '0 4px 8px rgba(0, 0, 0, 0.2)';
                            clearInterval(timeInterval);  // Clear the interval
                            document.getElementById(`timer_${p.playerID}`).textContent = formatTime(0);
                            timeInterval = null;  // Reset the interval variable
                            secondsElapsed = 0;
                        }

                         // Enable all buttons again
                         //Future Implementations

                    }
                });

                lifePointsInput.addEventListener('input', (event) => {
                    var lifePoint = parseInt(event.target.value);

                    var regex = /^\d+$/;  // Regular expression for positive integers

                    // Get or create the error message element
                    var errorMessage = document.getElementById('error-message');

                    var maxLength = 4;    // Maximum allowed characters

                    // Limit the input value to only the first maxLength characters
                    if (lifePointsInput.value.length > maxLength) {
                        lifePointsInput.value = lifePointsInput.value.slice(0, maxLength);
                    }
                    // If the input doesn't match the regex or is negative, set to 0 and show an error message
                    else if (!regex.test(lifePoint)) 
                    {
                        // Remove any non-numeric characters
                        lifePointsInput.value = lifePointsInput.value.replace(/[^0-9]/g, '');
                        
                        // Create the error message if it doesn't exist
                        if (!errorMessage) {
                            errorMessage = document.createElement('p');
                            errorMessage.id = 'error-message';
                            errorMessage.style.color = 'red';  // Set the error message color to red
                            errorMessage.textContent = 'Please enter a valid number (positive integers only).';
                            lifePointsInput.insertAdjacentElement('afterend', errorMessage);  // Display below the input field
                            lifePointsInput.focus();
                        }
                    }
                    else{
                        //Update Player life points
                        p.playerLifePoints = lifePoint;
                        _playerID.textContent = lifePoint;

                         // Remove the error message if the input is valid
                        if (errorMessage) {
                            errorMessage.remove();
                        }
                    }
                });
            });
        }

        });
        
        console.log(numberOfPlayers);
}