// Import the express module
const express = require('express');
const path = require("path"); //needed when setting up static/file paths

const { exec } = require('child_process');
const { MongoClient, ObjectId } = require("mongodb"); //import MongoClient from mongodb
const { send } = require('process');


// Initialize the app
const app = express();
//connection string to connect to localhost db and select the testdb database
const dbUrl = "mongodb://192.168.2.87:27017/dockerDB"; 
const client = new MongoClient(dbUrl);



// Set the port to listen on
//const port = 3000;
//const port = process.env.PORT || "8888";
const port = process.env.PORT || "3000";

//set up application template engine
app.set("views", path.join(__dirname, "views")); //the first "views" is the setting name
//the second value above is the path: __dirname/views
app.set("view engine", "pug");

//set up folder for static files
app.use(express.static(path.join(__dirname, "public")));

app.use(express.urlencoded({ extended: true })); //extend the urlencoded format (i.e. query string format like weight=0&path=/&name=Home)
app.use(express.json()); //allow for form data retrieval as JSON { weight: 0, path: "/", name: "Home"}




// Basic route to handle GET requests
app.get('/', async (req, res) => {
  // res.send('Hello, World!');
  const docker_ps = await listAllDocuments(`docker_ps`)
  const docker_stats = await listAllDocuments(`docker_stats`)
  console.log(docker_ps);
  console.log(docker_stats);

  // res.render("index", {docker_ps : _docker_ps}, {docker_stats : _docker_stats});
  res.render("index", {docker_ps, docker_stats});
});


// Route for Admin page (admin.pug)
app.get('/admin', (req, res) => {
  // res.render('admin'); // Renders 'views/admin.pug'
  res.render('admin/admin'); // Renders 'views/admin.pug'
});

// Route for Admin page (admin.pug)
app.get('/add', async (req, res) => {
  // res.render('admin'); // Renders 'views/admin.pug'
  const docker_ps = await listAllDocuments(`docker_ps`)
  const docker_stats = await listAllDocuments(`docker_stats`)
  console.log("------------------ ADD --------------------");
  console.log(docker_ps[1]);
  var dps = docker_ps[1];
  console.log(docker_stats[1]);
  var stats = docker_stats[1];
  res.render('admin/add', {dps, stats}); // Renders 'views/admin.pug'
});

// Route for Admin page (admin.pug)
app.get('/delete', async (req, res) => {
    const ps = await listAllDocuments(`docker_ps`);
    const ds = await listAllDocuments("docker_stats")

    const id_collection = [];

    ps.forEach(p => {
        const matched = ds.find(s => s.ID === p.ID);
        if (matched)
          //id_collection.push(p.ID);
          id_collection.push(p.Names);
          //id_collection.push(p);
    });

    // const sendData = JSON.stringify(id_collection);
    console.log(id_collection);
    // console.log(sendData);

  // res.render('admin'); // Renders 'views/admin.pug'
  res.render('admin/delete', { sendData: id_collection } ); // Renders 'views/admin.pug'
});

app.get('/ls', (req, res) => {
  // exec('ls -l', (err, stdout, stderr) => {
  // exec('uptime', (err, stdout, stderr) => {
  exec('uptime', (err, stdout, stderr) => {
    if (err) {
      console.error(`Error: ${err.message}`);
      return;
    }
    if (stderr) {
      console.error(`stderr: ${stderr}`);
      return;
    }
    //console.log(`stdout: ${stdout}`);
    res.send(`${stdout}`)
  });
});

app.get('/collections', async (req, res) => {
  try {
        // Await the result of getAllCollections to ensure it completes before sending the response
    const result = await getAllCollections();
    res.json(result); // Send the result as a JSON response
  }
  catch (error) {
    console.error('Error fetching collections:', error);
    res.status(500).send('Error fetching collections');
  }
});

//Read
// app.get('/dockerps', async (req, res) => {
app.get('/docker/:id', async (req, res) => {
  const docker_state = req.params.id;  // Access route parameter 'id'
  try {
        // Await the result of getAllCollections to ensure it completes before sending the response
        if(docker_state == 1)
        {
          // const result = await listAllDocuments("docker_ps")
          const result = await listAllDocuments(`docker_ps`)
          res.json(result); // Send the result as a JSON response
        }
        else if(docker_state == 2)
        {
          const result = await listAllDocuments("docker_stats")
          res.json(result); // Send the result as a JSON response
        }
  }
  catch (error) {
    console.error('Error fetching collections:', error);
    res.status(500).send('Error fetching collections');
  }
});




//Create
app.post('/docker/:id', async (req, res) => {
  const docker_state = req.params.id;  // Access route parameter 'id'
  try {
        if(docker_state == 1) {
          const result = await addDocument("docker_ps" ,req.body);
          res.json(result); // Send the result as a JSON response
          console.log(res.body);
        }
        else if(docker_state == 2) {
          const result = await addDocument("docker_stats" ,req.body);
          res.json(result); // Send the result as a JSON response
          console.log(res.body);
        }
  }
  catch (error) {
    console.error('Error fetching collections:', error);
    res.status(500).send('Error fetching collections');
  }
});

//Update
app.put('/docker/:id', async (req, res) => {
  const docker_state = req.params.id;  // Access route parameter 'id'
  try {
        if(docker_state == 1) {
          exec('./docker_ps.sh', async (err, stdout, stderr) => {
          //exec('dps', async (err, stdout, stderr) => {
            if (err) {
              console.error(`Error: ${err.message}`);
              return;
            }
            if (stderr) {
              cOnsole.error(`stderr: ${stderr}`);
              return;
            }
            //console.log(`stdout: ${stdout}`);
            // res.send(`${stdout}`)
            const document = JSON.parse(stdout); // If `stdout` is JSON, you need to parse it into an object
            const result = await updateFullDocument("docker_ps", document);
            res.json(result); // Send the result as a JSON response

          });
        }
        else if(docker_state == 2) {
          exec('./docker_stats.sh', async (err, stdout, stderr) => {
          //exec('dss', async (err, stdout, stderr) => {
            if (err) {
              console.error(`Error: ${err.message}`);
              return;
            }
            if (stderr) {
              console.error(`stderr: ${stderr}`);
              return;
            }
            //console.log(`stdout: ${stdout}`);
            res.send(`${stdout}`)
            const document = JSON.parse(stdout); // If `stdout` is JSON, you need to parse it into an object
            const result = await updateFullDocument("docker_stats", document);
            console.log("success");
            // res.json(result); // Send the result as a JSON response

          });
        }
  }
  catch (error) {
    console.error('Error fetching collections:', error);
    res.status(500).send('Error fetching collections');
  }
});

//Delete
app.delete('/docker/:id', async (req, res) => {
  const docker_state = req.params.id;  // Access route parameter 'id'
  try {
        if(docker_state == 1) {
          const result = await deleteDocument("docker_ps" ,req.body);
          res.json(result); // Send the result as a JSON response
        }
        else if(docker_state == 2) {
          const result = await deleteDocument("docker_stats" ,req.body);
          res.json(result); // Send the result as a JSON response
        }
  }
  catch (error) {
    console.error('Error fetching collections:', error);
    res.status(500).send('Error fetching collections');
  }
});


app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});

//MONGODB HELPER FUNCTIONS

//Function to connect and return the testdb database
async function connection() {
  //db = client.db();
  db = client.db("dockerDB");
  return db;
}

// Function to get all collection names
async function getAllCollections() {
  try {
    // Get database connection
    const db = await connection();

    // Get list of collections in the database
    const collections = await db.listCollections().toArray();

    // Extract collection names
    const collectionNames = collections.map(collection => collection.name);

    return collectionNames;
  } catch (error) {
    console.error('Error fetching collections:', error);
    throw error; // Optional: rethrow the error to handle it further
  }
}

async function listAllDocuments(collectionName) {
  try {
    // Get database connection
    const db = await connection();

    const collection = db.collection(collectionName);

    const document = await collection.find({}).toArray();

    return document;

  } catch (error) {
    console.error('Error fetching collections:', error);
    throw error; // Optional: rethrow the error to handle it further
  }
}

async function addDocument(collectionName, document) {
  try {
    const db = await connection();
    const collection = db.collection(collectionName);

    console.log(document);
    // Insert a single document
    const result = await collection.insertOne(document);

    console.log(`New document added with ID: ${result.insertedId}`);
    return result;  // Return the result for confirmation
  } catch (error)
  {
    console.error('Error fetching collections:', error);
    throw error; // Optional: rethrow the error to handle it further
  }
}

async function updateFullDocument(collectionName, document) {
    try {
    // Connect to MongoDB
    //const db = await client.connect();
    console.log("Connected to MongoDB");

    // Get the database and collection
    const db = client.db("dockerDB");
    const collection = db.collection(collectionName);  // Replace with your collection name

    await collection.drop();
    console.log("Collection dropped.");

    const newCollection = db.collection(collectionName);  // Recreate the collection
    const result = await newCollection.insertMany(document);
    console.log(`${result.insertedCount} documents inserted.`);
    return result;
  } catch (error) {
    console.error("Error occurred:", error);
  } finally {
    // Close the MongoDB connection
    //await client.close();
    //console.log("MongoDB connection closed.");
  }
}

async function deleteDocument(collectionName, document) {
  try {
    const db = await connection();
    const collection = db.collection(collectionName);
    console.log(document);

    const result = await collection.deleteOne(document);  // Filter to delete document by NAME
    console.log(`${result.deletedCount} document deleted from docker_stats`);
    return result;
    // return document;
  } catch (error) {
    console.error("Error deleting data from docker_stats: ", error);
  }
}
