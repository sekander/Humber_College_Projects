//Nahid Sekander
//n01001831
//Lab 2
//HTTP-5222

//import required modules
const express = require("express");
const path = require("path");
//set up Express object and port
const app = express();

app.set("views", path.join(__dirname, "views"));
app.set("view engine", "pug");

app.use(express.static(path.join(__dirname, "public")));

const port = process.env.PORT || "8888";

//Routes
app.get("/", (req, res) => {
    res.render("index", {title: "Home" });
});

app.get("/about", (req, res) => {
    res.render("about", {title: "About" });
});

app.get("/contact", (req, res) => {
    res.render("contact", {title: "Contact" });
});


//set up server listening
app.listen(port, () => {
console.log(`Listening on http://localhost:${port}`);
});
