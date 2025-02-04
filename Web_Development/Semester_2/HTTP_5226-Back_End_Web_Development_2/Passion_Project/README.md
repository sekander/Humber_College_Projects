# Passion Project API

## Project Overview
The Passion Project API is designed to manage and interact with a collection of `Player`, `Deck`, and `Card` entities, enabling users to perform CRUD operations on players, decks, and cards, establish relationships between them, and manage various interactions. The API is built with ASP.NET Core and follows a RESTful design.

## Features
- **Player Management**: Create, read, update, and delete players.
- **Deck Management**: Create, read, update, and delete decks.
- **Card Management**: Create, read, update, and delete cards.
- **Card-Deck Relationship**: Establish a many-to-many relationship between decks and cards, allowing a card to belong to multiple decks.
- **Data Validation**: Validates data before performing create or update operations to ensure integrity.
- **Logging**: Custom logging to track operations and activities.

## Entities

### Player
Represents a player in the system with the following properties:
- `ID`: The unique identifier for the player.
- `Name`: The name of the player.
- `Email`: The email address of the player.

### Card
Represents an individual playing card with the following properties:
- `ID`: The unique identifier for the card.
- `Name`: The name of the card (e.g., Ace of Spades).
- `Description`: A description of the card.

### Deck
Represents a collection of cards, typically a deck of playing cards, with the following properties:
- `ID`: The unique identifier for the deck.
- `Name`: The name of the deck (e.g., Deck 1, Deck 2).
- `Description`: A description of the deck.

### CardDeck (Many-to-Many Relationship)
This intermediate entity manages the relationship between `Card` and `Deck`. It links each card to the specific decks it belongs to.

## API Endpoints

### Player API Endpoints
1. **Get All Players**  
   `GET /api/player`  
   Fetch all players from the system.

2. **Get Specific Player**  
   `GET /api/player/{id}`  
   Fetch a player by their ID.

3. **Create Player**  
   `POST /api/player`  
   Create a new player.

4. **Update Player**  
   `PUT /api/player`  
   Update an existing player.

5. **Delete Player**  
   `DELETE /api/player/{id}`  
   Delete a player by their ID.

### Deck API Endpoints
1. **Get All Decks**  
   `GET /api/deck`  
   Fetch all decks from the system.
   
2. **Get Specific Deck**  
   `GET /api/deck/{id}`  
   Fetch a deck by its ID.

3. **Create Deck**  
   `POST /api/deck`  
   Create a new deck.

4. **Update Deck**  
   `PUT /api/deck`  
   Update an existing deck.

5. **Delete Deck**  
   `DELETE /api/deck/{id}`  
   Delete a deck by its ID.

6. **Create Card-Deck Relationship**  
   `POST /api/deck/card`  
   Create a relationship between a card and a deck.

7. **List All Cards in a Deck**  
   `GET /api/deck/{id}/allcards`  
   Retrieve all card IDs associated with a deck.

### Card API Endpoints
1. **Get All Cards**  
   `GET /api/card`  
   Fetch all cards from the system.

2. **Get Specific Card**  
   `GET /api/card/{id}`  
   Fetch a card by its ID.

3. **Create Card**  
   `POST /api/card`  
   Create a new card.

4. **Update Card**  
   `PUT /api/card`  
   Update an existing card.

5. **Delete Card**  
   `DELETE /api/card/{id}`  
   Delete a card by its ID.

### Entity Validation
Before creating or updating a deck, card, or player, the API ensures that the ID does not already exist in the system, preventing duplication. If the validation fails, the request returns a `BadRequest` response with a relevant error message.

### Logging
Each action, such as creating, updating, or deleting cards, decks, or players, is logged to the console for debugging and tracking purposes.

## Technology Stack
- **ASP.NET Core**: Framework used for building the API.
- **Entity Framework Core**: ORM for database interaction.
- **SQL Server**: The database used to store card, deck, and player information.
- **LINQ**: Used to filter and retrieve data from the database.

## How the Controllers Work

### `PlayerController`
Handles all CRUD operations related to the `Player` entity:
- Fetches all players and individual player details.
- Allows the creation, update, and deletion of players.
- Maintains a static list of player IDs for validation purposes.
- Logs custom messages for actions such as fetching, creating, updating, and deleting players.

### `CardController`
Handles all CRUD operations related to the `Card` entity:
- Fetches all cards and individual card details.
- Allows the creation, update, and deletion of cards.
- Maintains a static list of card IDs for validation purposes.
- Logs custom messages for actions such as fetching, creating, updating, and deleting cards.

### `DeckController`
Handles all CRUD operations related to the `Deck` entity:
- Fetches all decks and individual deck details.
- Allows the creation, update, and deletion of decks.
- Creates and manages relationships between decks and cards via the `CardDeck` entity.
- Maintains a static list of deck IDs for validation purposes.
- Logs custom messages for actions such as fetching, creating, updating, and deleting decks.

### `CardDeckController`
Handles the creation of relationships between `Card` and `Deck` entities and retrieving associated cards for a deck. It also manages conflicts and ensures that a card is not added multiple times to the same deck.

## Example API Requests

### Creating a Player
**Request**:
```http
POST /api/player
Content-Type: application/json
{
  "name": "John Doe",
  "email": "john.doe@example.com"
}

**Response**:
{
  "success": true,
  "data": { 
    "id": 1, 
    "name": "John Doe", 
    "email": "john.doe@example.com" 
  },
  "message": "Created: John Doe"
}

### Updating a Player
**Request**:
PUT /api/player
Content-Type: application/json
{
  "id": 1,
  "name": "John Doe Updated",
  "email": "john.doe.updated@example.com"
}

**Response**:
{
  "success": true,
  "data": { 
    "id": 1, 
    "name": "John Doe Updated", 
    "email": "john.doe.updated@example.com" 
  },
  "message": "Updated: John Doe Updated"
}

### Error Handling

    If an entity (deck, card, or player) is not found during creation, updating, or linking operations, the API responds with a NotFound or Conflict status code and a relevant error message.
    Invalid operations (e.g., attempting to add an already existing card-deck relationship) return a Conflict response.

### Conclusion
The Passion Project API is a fully functional RESTful API that provides complete management for players, decks, and cards. It ensures data validation, logs key operations, and allows for complex relationships between cards and decks through the CardDeck entity.

This API can be expanded with additional features such as user authentication, pagination for large sets of data, and advanced filtering options for better user experience.
