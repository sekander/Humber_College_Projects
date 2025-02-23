# Magic: The Gathering (MTG) Deck Management Application & Passion Project API Overview

The **MTG Deck Management Application** is a web-based platform designed for **Magic: The Gathering (MTG)** players to efficiently manage their decks, cards, and profiles. Powered by the **Passion Project API** built with **ASP.NET Core**, the platform supports full CRUD (Create, Read, Update, Delete) operations for players, decks, and cards. A standout feature is its **advanced card search and filtering system**, which enables players to explore a database of over **30,000 MTG cards** quickly and accurately. With real-time search results, advanced filtering options, and smooth pagination, users can easily manage and interact with their collections.

Whether you are a casual player or a competitive deck builder, the MTG Deck Management Application provides efficient tools for organizing and exploring your MTG collection. Players have full control over deck creation, card management, and real-time search, ensuring an enjoyable user experience when browsing and building decks.

## Key Features

### 1. **Player Management**
Players can securely log in to access their decks and card collections. While profile creation and updating are not available at this time, these features will be introduced in future updates to offer more personalized management options.

### 2. **Deck Management**
Players can create, edit, and manage their decks. This feature allows users to build new decks, organize existing ones, and optimize card selections for better gameplay strategies.

### 3. **Card Management**
Players can view detailed information about each card in their collection. The application displays attributes such as name, description, image, type, rarity, and more, enabling users to make informed decisions while managing their cards.

### 4. **Card Search & Filtering**
The core functionality of the MTG Deck Management Application is the **Card Search & Filtering** system, allowing players to search over **30,000 cards** using a variety of filters:

   - **Search Bar**: Real-time filtering of cards based on keywords such as name, description, or other text attributes.
   - **Advanced Filters**: Refine searches by card type (Creature, Sorcery, Artifact), color, mana cost, power/toughness, and more.
   - **Pagination**: Search results are paginated for easier browsing and navigation.

### 5. **Pagination**
With the vast database of cards, **pagination** ensures a smooth browsing experience. Results are split into pages, allowing players to navigate large datasets efficiently and without performance issues.

---

## Passion Project API Features

The **Passion Project API** serves as the backend for the MTG Deck Management Application, handling all interactions with the MTG card database and managing player profiles and deck operations. The API offers several key features:

### 1. **Login Functionality**
Players securely log in using authentication mechanisms to access their decks and profiles. While profile creation and updating are not yet available, future updates will support these features.

### 2. **Deck Management**
The API allows players to create, edit, and delete decks. It supports the relationship between decks and cards, enabling users to build complex decks with a variety of cards.

### 3. **Card Management**
The **Card Management** functionality enables full CRUD operations for cards, ensuring that data is always accurate and up-to-date. Users can search, update, and delete card entries based on multiple attributes like type, rarity, and mana cost.

### 4. **Search & Filtering**
The backend supports **advanced search and filtering**, ensuring fast, real-time card searches based on attributes such as type, color, rarity, and more.

### 5. **Data Integrity & Validation**
The API performs data validation to ensure consistency and avoid duplicates, keeping the database clean and organized.

### 6. **Logging**
The system logs all user actions (creating, updating, or deleting data) for debugging and system monitoring purposes.

---

## Card Search & Filtering System

The **Card Search & Filtering System** is one of the key features of the application, especially considering the extensive database of **30,000+ cards**. This system is designed to help players find specific cards quickly and efficiently:

- **Search Bar**: Real-time results appear as players type keywords to search cards by name, description, or other attributes.
- **Advanced Filters**: Users can refine searches using filters like card type (Creature, Sorcery), color (Red, Green, etc.), mana cost, power/toughness, and more.
- **Pagination**: To enhance user experience, the results are split into manageable pages, making it easy to browse large sets of data.

### Advanced Search System
Future updates will include additional filters, such as:

- **Mana Cost Range**: Filter cards by mana cost range.
- **Card Type**: Filter based on specific card types.
- **Rarity**: Filter by card rarity (Common, Uncommon, Rare, Mythic).
- **Abilities**: Add filters for specific card abilities like flying or lifelink.

---

## Live Demo

To experience the MTG Deck Management Application firsthand, a **live demo** is available for users. The demo showcases the following features:

- **Login**: Secure login to access profiles and decks.
- **Deck Management**: Create and manage decks with an intuitive interface.
- **Card Search & Filtering**: Experience real-time search and advanced filtering for precise card selection.
- **Pagination & Navigation**: Browse large datasets efficiently with pagination.

Visit the [Live Demo on Personal Web Server](https://nahid-sekander.duckdns.org/mtg-deck-builder)
 to try the application and explore its features.

---

## Conclusion

The **MTG Deck Management Application**, powered by the **Passion Project API**, is a robust and user-friendly platform for managing **Magic: The Gathering** cards and decks. With powerful features such as **real-time card search**, **advanced filtering**, **pagination**, and **secure login**, the platform offers a smooth user experience and efficient data management. As future updates introduce **advanced search filters** and **profile management**, the application will continue to evolve, providing a comprehensive tool for MTG enthusiasts.

