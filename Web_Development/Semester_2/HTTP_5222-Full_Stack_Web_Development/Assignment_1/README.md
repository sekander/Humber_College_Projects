# Docker Management Application

This is a simple web application built with **Express.js** and **MongoDB** that allows you to manage Docker container information and statistics.

## Features

- List, add, update, and delete Docker container data and statistics.
- Simple admin interface to view and manage Docker containers.
- Uses **MongoDB** for storing container states and stats.
- Routes for basic operations like listing files and getting system uptime.

## Requirements

- Node.js (v12.x or above)
- MongoDB (v4.x or above)
- Docker (optional, for managing containers)
- Express.js


## API Endpoints

### 1. **GET /**
   - Displays the index page with a list of Docker containers and their statistics.

### 2. **GET /admin**
   - Admin interface for managing Docker containers.

### 3. **GET /add**
   - Form for adding new Docker containers to the database.

### 4. **GET /delete**
   - Form for deleting Docker containers based on their names.

### 5. **GET /collections**
   - Returns all MongoDB collection names in the `dockerDB`.

### 6. **GET /docker/:id**
   - `:id` can be `1` or `2`.
     - `1`: Returns all documents in the `docker_ps` collection.
     - `2`: Returns all documents in the `docker_stats` collection.

### 7. **POST /docker/:id**
   - `:id` can be `1` or `2` to specify which collection (`docker_ps` or `docker_stats`) to add data to.
   - Accepts JSON payload to add a new document to the respective collection.

### 8. **PUT /docker/:id**
   - `:id` can be `1` or `2` to specify which collection (`docker_ps` or `docker_stats`) to update.
   - Runs a shell script (`docker_ps.sh` or `docker_stats.sh`) to get Docker container information and update the collection.

### 9. **DELETE /docker/:id**
   - `:id` can be `1` or `2` to specify which collection (`docker_ps` or `docker_stats`) to delete data from.
   - Deletes a document from the respective collection based on the request body.

## MongoDB Helper Functions

The helper functions handle the interaction with MongoDB, including:

- **`connection()`**: Establishes a connection to the MongoDB database.
- **`getAllCollections()`**: Retrieves all collection names in the database.
- **`listAllDocuments(collectionName)`**: Fetches all documents from the specified collection.
- **`addDocument(collectionName, document)`**: Adds a new document to the specified collection.
- **`updateFullDocument(collectionName, document)`**: Replaces all documents in the specified collection with new data.
- **`deleteDocument(collectionName, document)`**: Deletes a document from the specified collection.

## File Structure

```plaintext
docker-management-app/
├── app.js               # Main application file
├── views/
│   ├── index.pug        # Index page template
│   ├── admin/
│   │   ├── admin.pug    # Admin page template
│   │   └── add.pug      # Add Docker container page template
│   │   └── delete.pug   # Delete Docker container page template 
├── public/              # Folder for static files like CSS and JavaScript
│   └── styles.css       # Example CSS file
└── docker_ps.sh         # Shell script for updating `docker_ps` data
└── docker_stats.sh      # Shell script for updating `docker_stats` data
