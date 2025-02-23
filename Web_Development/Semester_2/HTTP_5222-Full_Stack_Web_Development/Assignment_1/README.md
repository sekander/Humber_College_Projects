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

## Deployment

You can view a live demo of this project hosted on Personal Web Server at the following URL:

[Live Demo on Personal Web Server](https://nahid-sekander.duckdns.org/docker-service)



## Docker Service Views

This project has several views that allow users to interact with Docker containers via a web interface. Below is a brief summary of each view and its functionality.

### 1. `index.pug`
- **Purpose:** This is the main home page of the application.
- **Key Features:**
  - Displays a page title "Assignment 1".
  - Provides a link to navigate to the admin page (`/admin`).
  - Displays the current Docker container details by pairing Docker `ps` with Docker `stats` using matching IDs.
  - Each container's info from `docker_ps` and its corresponding stats from `docker_stats` are shown in a table format.
  - Provides a message section to show the result of API requests.

### 2. `admin.pug` (Admin Page)
- **Purpose:** This is the admin control page.
- **Key Features:**
  - Displays a page title "Admin Pages".
  - Provides buttons and links for performing different actions, including navigating to Add (`/add`) and Delete (`/delete`) pages.
  - Implements an "UPDATE" button that makes two AJAX `PUT` requests to update Docker containers. Both requests must complete before the page is reloaded.

### 3. `add.pug` (Admin Add Page)
- **Purpose:** This page allows users to add Docker container data.
- **Key Features:**
  - Displays a page title "Admin Add Pages".
  - Users can choose to add either `docker_ps` or `docker_stats` data.
  - Displays dynamic forms depending on the selected data type (`docker_ps` or `docker_stats`), with input fields for each key-value pair.
  - Submitting the form sends a POST request to the server with the form data, allowing the user to add new Docker container information.

### 4. `delete.pug` (Admin Delete Page)
- **Purpose:** This page allows users to delete Docker containers.
- **Key Features:**
  - Displays a page title "Admin Delete Page".
  - Lists available Docker container IDs as radio buttons that users can select.
  - Shows the selected container ID dynamically as the user selects a radio button.
  - Includes a "DELETE" button that sends an AJAX `DELETE` request to the server to delete the selected container.

### 5. `common/layout.pug`
- **Purpose:** A common layout file used by all pages for consistent styling and structure.
- **Key Features:**
  - Contains the basic HTML structure (header, footer, etc.).
  - Ensures that all pages share a unified look and feel.

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
