//IMPORT REQUIRED MODULES
const express = require("express");
const path = require("path"); //contains methods to help with path concatenation
const { MongoClient, ObjectId } = require("mongodb"); //import MongoClient from mongodb

//Connect to DB
const dbUrl = "mongodb://127.0.0.1:27017/testdb"; //connection string to connect to localhost db and select the testdb database

//Test Machine IP
//const dbUrl = "mongodb://192.168.2.87:27017/testdb"; //connection string to connect to localhost db and select the testdb database
const client = new MongoClient(dbUrl);

//SET UP EXPRESS APP
const app = express(); //express() is a function to initialize an Express app
const port = process.env.PORT || "8888";

//SET UP TEMPLATE ENGINE
app.set("views", path.join(__dirname, "templates")); //set "views" to use the <app_directory>/templates folder to store template files
app.set("view engine", "pug");//set Express to use Pug as the template (view) engine

//SET UP FOLDER FOR STATIC FILES (CSS, client-side JS)
app.use(express.static(path.join(__dirname, "public")));

app.use(express.urlencoded({ extended: true })); //extend the urlencoded format (i.e. query string format like weight=0&path=/&name=Home)
app.use(express.json()); //allow for form data retrieval as JSON { weight: 0, path: "/", name: "Home"}

//TEST APP PATH
app.get("/", async (request, response) => {
  let links = await getLinks();
  response.render("index", { title: "Home", menu: links });
});
app.get("/about", async (request, response) => {
  let links = await getLinks();
  response.render("about", { title: "About", menu: links });
});
//ADMIN PAGES
app.get("/admin/menu", async (request, response) => {
  let links = await getLinks();
  //render admin page
  response.render("menu-list", { title: "Administer menu", menu: links });
});
app.get("/admin/menu/add", async (request, response) => {
  let links = await getLinks();
  //render admin page
  response.render("menu-add", { title: "Add menu link", menu: links });
});
app.post("/admin/menu/add/submit", async (request, response) => {
  //for POST forms (for this form submission), data is sent in request.body
  //for GET forms, data is sent in request.query
  let weight = request.body.weight; //get the value for field with name=weight
  let href = request.body.href;     //request.body is form POST data
  let name = request.body.name;
  //console.log(request.body.path);
  let newLink = {
    //weight: request.body.weight,
    weight: weight,
    //path: request.body.path,
    path: href,
    //name: request.body.name
    name: name
  };
  await addLink(newLink);
  response.redirect("/admin/menu"); //redirect back to main menu admin page
});
app.get("/admin/menu/delete", async (request, response) => {
  console.log(request.query.linkId);
  let id = request.query.linkId;
  await deleteLink(id);
  response.redirect("/admin/menu");
})

//SET UP SERVER LISTENING
app.listen(port, () => {
  console.log(`Listening at http://localhost:${port}`)
})

//Lab 3 Edits
//
app.get("/admin/menu/edit", async (request, response) => {
    if(request.query.linkId) {
        let linkToEdit = await getSingleLink(request.query.linkId);
        let links = await getLinks();
        response.render("menu-edit", { title: "Edit menu link", menu: links, editLink: linkToEdit });
    } else {
        response.redirect("/admin/menu");
    }
});

app.post("/admin/menu/edit/submit", async (request, response) => {
    try {
        console.log("working edit");
        //get the _id and set it as a JSON object to be used for the filter
        let idFilter = {_id: new ObjectId(request.body.linkId)}; 
        //get weight/path/name form values and build a JSON object containing
        // these (updated) values
        let link = {
            weight: request.body.weight,
            path: request.body.path,
            name: request.body.name
        };
        
        //let result = await editLink(idFilter, link);
        await editLink(idFilter, link);
        response.redirect("/admin/menu");

    }
    catch (err){
        console.log("Error updating menu link: ", err);
        response.status(500).send("An error occurred while updating the menu link.");
    }
});


//MONGODB HELPER FUNCTIONS

//Function to connect and return the testdb database
async function connection() {
  //db = client.db();
  db = client.db("testdb");
  return db;
}

//Get all menu links
async function getLinks() {
  db = await connection();
  let results = db.collection("menuLinks").find({}); //use empty {} as the query to select (find) all
  let resultArray = await results.toArray(); //convert the results pointer to an array we can use (toArray() is an asynchronous method so we need to use await)
  return resultArray;
}

//expects a link JSON object to be inserted into menuLinks
async function addLink(link) {
  db = await connection();
  let status = await db.collection("menuLinks").insertOne(link);
  console.log("link added");
}

async function deleteLink(id) {
  db = await connection();
  let query = { _id: new ObjectId(id) };
  let result = await db.collection("menuLinks").deleteOne(query);
}


// Lab 3 Edits
async function getSingleLink(id) {
    db = await connection();
    const editId = { _id: new ObjectId(id)};
    const result = await db.collection("menuLinks").findOne(editId);
    return result;
}

async function editLink(filter, link) {
    try {
        db = await connection();
        //create the update set { $set: <JSON document> }
        const updateSet = { $set: link };
        //execute an updateOne() to update the link as selected via the filte
        const result = await db.collection("menuLinks").updateOne(filter, updateSet);
        return result;
    }
    catch (err) {
        console.errror("Error updating link: ", err);
        throw err;
    }
}
