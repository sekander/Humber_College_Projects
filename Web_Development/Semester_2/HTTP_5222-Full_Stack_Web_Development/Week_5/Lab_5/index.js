const express = require("express");
const path = require("path"); //needed when setting up static/file paths
const dotenv = require("dotenv");
const db = require("./modules/movies/db"); //load db.js


//load the environment variables from .env
dotenv.config();


//set up the Express app
const app = express();


const port = process.env.PORT || "8889";

//set up application template engine
app.set("views", path.join(__dirname, "views")); //the first "views" is the setting name
//the second value above is the path: __dirname/views
app.set("view engine", "pug");

//set up folder for static files
app.use(express.static(path.join(__dirname, "public")));

//USE PAGE ROUTES FROM ROUTER(S)
app.get("/", async (request, response) => {
    //Get Movie List From MongoDB
    const result = await getMovieList();
    //Render to results to Index
    response.render("index", { movies: result});
});

app.get("/update", async (request, response) => {
    //Get title through url query parameter
    const title = request.query.title;
    //Get rating through url query parameter
    const rating = request.query.rating;

    //Get Results from mongo db query
    const result = await db.updateMovieRating(title, rating);
    //await db.updateMovieRating("Max", "G");
    //response.redirect("/");
    //console.log(response.json(result));
    console.log(result);
    
    const _movies = await getMovieList();
    response.render('index', {movies: _movies, jsonData: result});
})

app.get("/delete", async (request, response) => {
    //Get rating through url query parameter
    const rating = request.query.rating;

    //Get Results from mongo db query
    const result = await db.deleteMoviesByRating(rating);
    //response.redirect("/");
    console.log(result);
    //alert(result.message);
    const _movies = await getMovieList();
    response.render('index', {movies: _movies, jsonData: result});
})


//set up server listening
app.listen(port, () => {
  console.log(`Listening on http://localhost:${port}`);
}); 


//Helper Function to grab list of movies
async function getMovieList(){
  let movielist = await db.getMovies();
  //if there's nothing in the movie collection, initialize with some content then get the movies again
  if (!movielist.length) {
    await db.initializeMovies(); 
    movielist = await db.getMovies();
  }
  return movielist;
}

