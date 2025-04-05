const axios = require('axios');

// Load environment variables from the .env file
require('dotenv').config();

// Importing required modules
const express = require('express');
const path = require('path');
const fs = require('fs');
const { get } = require('https');

// Creating an instance of Express
const app = express();

// Set up the view engine as Pug
app.set('view engine', 'pug');
app.set('views', path.join(__dirname, 'views')); // Setting the path to the 'views' folder

// Serve static files (like CSS) from the public directory
app.use(express.static(path.join(__dirname, 'public')));

// Access the API_KEY from the environment variable
const apiKey = process.env.API_KEY;
const comicApiKey = process.env.COMICVINE_API_KEY;

// Path to the local JSON file containing character names
const charactersFilePath = path.join(__dirname, 'character_names.json');

// Define a route for the home page
app.get('/', (req, res) => {
  res.render('index', { title: 'Node.js with Express and Pug', 
                      message: 'Welcome to the Node.js app with Pug!' });
});

// Define another route to show the API Key (for testing)
app.get('/api-key', (req, res) => {
  res.send(`Your API key is: ${apiKey}`);
});


// Function to load characters from the JSON file
const loadCharacterNames = () => {
  const data = fs.readFileSync(charactersFilePath, 'utf8');
  const parsedData = JSON.parse(data);
  return parsedData.characters || [];
};

// Endpoint to filter characters based on the query parameter
app.get('/characters', (req, res) => {
  // Get the query parameter (e.g., 'L' from /characters?query=L)
  const query = req.query.query;

  // If no query parameter is provided, return an error
  if (!query) {
    return res.status(400).json({ error: "Query parameter is required." });
  }

  const characters = loadCharacterNames();

  // Filter characters that start with the given query parameter (case insensitive)
  const filteredCharacters = characters.filter(character =>
    character.toLowerCase().startsWith(query.toLowerCase())
  );

    

  // Return the filtered list of characters
  res.json(filteredCharacters);
});


// Endpoint to search for superheroes by name using the Superhero API
app.get('/superhero/search', async (req, res) => {
  const name = req.query.name;

  // If no name parameter is provided, return an error
  if (!name) {
    return res.status(400).json({ error: "Name parameter is required." });
  }

  const apiUrl = `https://superheroapi.com/api/${apiKey}/search/${name}`;

  try {
    const response = await axios.get(apiUrl);
    if (response.data.response === 'success') {
      res.json(response.data.results);
    } else {
      res.status(404).json({ error: 'Superhero not found' });
    }
  } catch (error) {
    console.error('Error fetching superhero data:', error);
    res.status(500).json({ error: 'An error occurred while fetching superhero data' });
  }
});

async function getCharacterId(characterName) {
  const apiKey = 'YOUR_API_KEY'; // Replace with your API key
  const url = `https://comicvine.gamespot.com/api/characters/?api_key=${comicApiKey}&format=json&name=${encodeURIComponent(characterName)}`;

  try {
    const response = await fetch(url);
    const data = await response.json();

    // Check if the API returned results
    if (data.results && data.results.length > 0) {
      // You can extract the character ID from the response
      const characterId = data.results[0].id;
      console.log(`Character ID for ${characterName}: ${characterId}`);
      return characterId;
    } else {
      console.log(`Character ${characterName} not found.`);
    }
  } catch (error) {
    console.error('Error fetching data from Comic Vine API:', error);
  }
}

// Endpoint to search for superheroes by name using the Superhero API
app.get('/comic/search', async (req, res) => {
  const characterId = req.query.id;
  console.log(characterId);
  const apiUrl = `https://comicvine.gamespot.com/api/issues/?api_key=${comicApiKey}&format=json&filter=characters:${characterId}&field_list=name,image,issue_number,description,publisher`;
  const response = await axios.get(apiUrl);
  if (response.data.results.length > 0) {
    res.json(response.data.results);
  } else {
    res.status(404).json({ error: 'No comic issues found for this character' });
  }

});

// Set the app to listen on a port
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});

