# MTG Card Display

This project fetches random Magic: The Gathering (MTG) card data from a MySQL database and displays it in a responsive table. Each card's details (name, release date, mana cost, etc.) are shown, and its image is dynamically loaded from the database.

## Key Features:

- Fetches 50 random MTG cards from the database.
- Displays card details in a table format for larger screens.
- Displays cards in a grid layout for smaller screens.
- Each card flips to show more details like power, toughness, artist, etc.
- Fully responsive design with media queries for different screen sizes.

## Setup:

1. **Database Setup**:
    - Set up a MySQL database and ensure it contains a table with the following fields: `name`, `released_at`, `mana_cost`, `type_line`, `oracle_text`, `power`, `toughness`, `colors`, `artist`, and `image_url`.
    - Create a database connection using the provided PHP script. You can modify the database connection details in the PHP code.

2. **PHP Code**:
    - Include the provided PHP script to fetch and display the MTG card data.
    - The PHP script connects to the MySQL database, retrieves 50 random cards, and displays them in both table format and a responsive grid format.

3. **Styling**:
    - The page uses Bootstrap 5 for responsive design.
    - Custom CSS has been added to style the card flip effect and adjust the layout for different screen sizes.

4. **JavaScript**:
    - JavaScript handles the card flip effect by rotating the card on click.
    - A script is included to toggle the `transform` property to rotate the card on the Y-axis.

## File Structure:

- **index.php**: Contains the PHP code to fetch card data and render the HTML.
- **CSS**: Custom styles included within the `<style>` tag to handle card layout and responsiveness.
- **JavaScript**: Embedded in the `<script>` tag to handle the card flip interaction.

## Media Queries:

- The layout adjusts for various screen sizes using media queries:
    - **≥ 1200px**: Displays the card data in a table format.
    - **≤ 992px**: Switches to a grid format with smaller card dimensions.
    - **≤ 776px**: Further adjusts the card layout for even smaller screens.
    - **≤ 575px**: Adjusts for extra-small screens (e.g., mobile devices).

## How to Run:

1. Set up a MySQL database with the correct schema and data.
2. Ensure the PHP code can connect to your database.
3. Include the HTML, CSS, and PHP code in your web server environment.
4. Open the PHP file in a browser, and it will fetch and display the random MTG cards.

## Live Demo

You can view a live demo of this project hosted on Personal Web Server at the following URL:

[Live Demo on Personal Web Server](https://nahid-sekander.duckdns.org/projects/php/Assignment_1/)

## Technologies Used:

- **PHP**: For server-side scripting and MySQL database interaction.
- **MySQL**: For storing and retrieving MTG card data.
- **Bootstrap 5**: For responsive styling and layout.
- **CSS**: Custom styles for the card flip and responsiveness.
- **JavaScript**: For handling the card flip effect on click.

## Notes:

- Ensure that your MySQL connection details in the PHP script are correctly configured.
