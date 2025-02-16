const mongoose = require("mongoose");

//const dbUrl = `mongodb://${process.env.DBUSER}:${process.env.DBPWD}@${process.env.DBHOST}/?authSource=testdb`;
//const dbUrl = `mongodb+srv://${process.env.DBUSER}:${process.env.DBPWD}@${process.env.DBHOST}`;
const dbUrl = 'mongodb://192.168.2.87:27017/testdb';

//set up Schema and model
const MovieSchema = new mongoose.Schema({
  title: String,
  year: Number,
  rating: String
});
const Movie = mongoose.model("Movie", MovieSchema);

//MONGODB FUNCTIONS
async function connect() {
  await mongoose.connect(dbUrl); //connect to mongodb
  console.log("Connected");
}

async function initializeMovies() {
    await connect();
    const movies = [
        {
            title: "Eternal Sunshine of the Spotless Mind",
            year: 2004,
            rating: 'R' 
        },
        {
            title: "Django Unchained",
            year: 2012,
            rating: 'R' 
        },
        {
            title: "Kill Bill",
            year: 2003,
            rating: 'R' 
        }
    ];

    await Movie.insertMany(movies);
}

//Get all pets from the pets collection
async function getMovies() {
    await connect();
    return await Movie.find({}); //return array for find all
}

async function updateMovieRating(_title, newRating) {
    const regex = /^(G|PG|PG-13|R|NC-17)$/;
    if(!regex.test(newRating))
        return { status: 'error', message: 'Ratings must be either G, PG, PG-13, R, NC-17', data: newRating};
    await connect();
    const movie = await Movie.findOne({title:_title});
    if(movie == null)
        return { status: 'error', message: `Movie title ${_title} Not Found in DB`, data: _title};
    else{
        //await movie.updateOne({ title: _title}, { rating: newRating});
        await movie.updateOne({ rating: newRating});
        return { status: 'success', message: `Movie ${_title} Upated with new Rating : ${newRating}`, data: {_title, newRating}};
    }
}

async function deleteMoviesByRating(_rating) {
    const regex = /^(G|PG|PG-13|R|NC-17)$/;
    if(!regex.test(_rating))
        return { status: 'error', message: 'Ratings must be either G, PG, PG-13, R, NC-17', data: _rating};
    await connect();

    //await Movie.deleteMany({ rating: _rating});
    const result = await Movie.deleteMany({ rating: _rating})
    if(result.deletedCount > 0)
        return {status: 'success', message: `${result.deletedCount} Movies Deleted with Rating : ${_rating}`, data: _rating};
    else
        return {status: 'no change', message: `${result.deletedCount} Movies Deleted`, data: _rating};

}

module.exports = {
    initializeMovies,
    getMovies,
    updateMovieRating,
    deleteMoviesByRating
}
