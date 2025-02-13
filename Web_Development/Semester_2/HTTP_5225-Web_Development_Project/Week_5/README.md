# Random Colour Data

This project displays random color data retrieved from a MySQL database and presents it in an HTML page. The data includes color information such as name, hexadecimal code, and a visual representation of the color in the form of a small color box.

## Features

- **Random color display**: The page fetches color data from a MySQL database and randomly selects 6 colors to display.
- **Color preview**: Each color is displayed as a small color box, showing the color itself.
- **Hexadecimal format**: The colors are represented using their hexadecimal values, and the colors are fetched from the database based on those values.

## Technology Stack

- **HTML**: To structure the webpage and display the content.
- **PHP**: To connect to the database, retrieve color data, and dynamically generate the page.
- **MySQL**: To store color data, including names and hexadecimal codes.
- **CSS**: For basic styling of the webpage.

## Setup

1. Clone or download this project to your local machine.
2. Ensure you have a running MySQL server.
3. Create a database named `http_5225` and a table called `Colours` with the following fields:
    - `Name` (VARCHAR)
    - `Hex` (VARCHAR)
    - `Red` (INT)
    - `Green` (INT)
    - `Blue` (INT)
    - `Hue` (FLOAT)
    - `HSLS` (FLOAT)
    - `HSLL` (FLOAT)
4. Update the PHP code with the correct database credentials in the `$connect` variable in the `index.php` file.

## Database Example

Here is an example of the `Colours` table structure:

| Name    | Hex      | Red | Green | Blue | Hue   | HSLS  | HSLL  |
|---------|----------|-----|-------|------|-------|-------|-------|
| Red     | #FF0000  | 255 | 0     | 0    | 0     | 100   | 100   |
| Green   | #00FF00  | 0   | 255   | 0    | 120   | 100   | 100   |
| Blue    | #0000FF  | 0   | 0     | 255  | 240   | 100   | 100   |

## Usage

1. Open the `index.php` file in your browser.
2. The PHP script will query the `Colours` table in the MySQL database to fetch random color data.
3. It will randomly select and display 6 colors, showing their respective hexadecimal codes.
4. Each color will be presented as a small colored box, allowing you to visually identify the color.

## Live Demo

You can view a live demo of this project hosted on Google Cloud at the following URL:

[Live Demo on Google Cloud](http://35.184.194.219/php/http_5225/week_5/)

You can view a live demo of this project hosted on Personal Web Server at the following URL:

[Live Demo on Personal Web Server](https://nahid-sekander.duckdns.org/projects/php/Week_5/)

## License

This project is open source and available under the [MIT License](LICENSE).

