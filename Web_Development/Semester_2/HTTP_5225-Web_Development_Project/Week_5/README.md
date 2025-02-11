# Random Colour Data

This project displays random color data retrieved from a MySQL database and presents it in an HTML table format. The data includes color name, hexadecimal code, RGB values, and hue information. It also shows the color itself as a small color box.

## Features

- **Displays random color data**: The page fetches color information from a MySQL database and presents it in a table.
- **Color preview**: Each color is shown as a small box filled with its respective color.
- **Hex, RGB, and HSL details**: Displays not only the color name and hex code but also the RGB (Red, Green, Blue) values, Hue, and HSL (Hue, Saturation, Lightness) details.

## Technology Stack

- **HTML**: To structure the webpage and display the content.
- **PHP**: To connect to the database, retrieve color data, and dynamically generate the table.
- **MySQL**: To store color data (name, hex, RGB, hue, HSL).
- **CSS**: For basic styling of the webpage and table.

## Setup

1. Clone or download this project to your local machine.
2. Make sure you have a running MySQL server.
3. Create a database named `http_5225` and a table called `Colours` with the following fields:
    - `Name` (VARCHAR)
    - `Hex` (VARCHAR)
    - `Red` (INT)
    - `Green` (INT)
    - `Blue` (INT)
    - `Hue` (FLOAT)
    - `HSLS` (FLOAT)
    - `HSLL` (FLOAT)
4. Update the PHP code with the correct database credentials in the `$connect` variable (currently set to `'34.60.40.76', 'root', 'root'`).

## Database Example

Here's an example of the `Colours` table structure:

| Name    | Hex      | Red | Green | Blue | Hue   | HSLS  | HSLL  |
|---------|----------|-----|-------|------|-------|-------|-------|
| Red     | #FF0000  | 255 | 0     | 0    | 0     | 100   | 100   |
| Green   | #00FF00  | 0   | 255   | 0    | 120   | 100   | 100   |
| Blue    | #0000FF  | 0   | 0     | 255  | 240   | 100   | 100   |

## Usage

1. When you open the page in a browser, the PHP script will query the `Colours` table in the MySQL database.
2. A random selection of 6 colors will be displayed, showing their respective details in a table.
3. Each row includes a small color box that shows the color itself based on the hex value.

## Example Output

| Name   | Hex     | Red | Green | Blue | Hue  | HSLS | HSLL | Colour      |
|--------|---------|-----|-------|------|------|------|------|-------------|
| Red    | #FF0000 | 255 | 0     | 0    | 0    | 100  | 100  | ![color](#FF0000) |
| Green  | #00FF00 | 0   | 255   | 0    | 120  | 100  | 100  | ![color](#00FF00) |
| Blue   | #0000FF | 0   | 0     | 255  | 240  | 100  | 100  | ![color](#0000FF) |

## License

This project is open source and available under the [MIT License](LICENSE).

