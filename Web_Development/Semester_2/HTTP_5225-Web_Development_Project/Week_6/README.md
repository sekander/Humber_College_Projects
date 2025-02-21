# Lab 6 

## Description:
This is a web page designed to display a list of schools in a responsive grid format. It uses **Bootstrap 5** to structure the layout, with **PHP** to fetch school data from a database. The page includes hover effects for interactive cards, which visually highlight different school information such as language and school type.

## Features:
- **Responsive Layout**: The page uses Bootstrap's grid system, ensuring that the cards are displayed in 4 columns on larger screens and adjust for smaller devices.
- **Hover Effects**: When a user hovers over a card, a smooth border color animation is applied, growing and shrinking the border around the card.
- **Dynamic Data**: School data is fetched from a MySQL database (`TABLE 2`) and displayed dynamically. 
- **Conditional Badge Colors**: The language and school type badges change color dynamically based on the values from the database (e.g., green for English, red for French; green for public, yellow for private).

## Tech Stack:
- **HTML5**: For structuring the web page.
- **PHP**: For fetching data from the MySQL database.
- **MySQL**: Database to store and retrieve school data.
- **CSS (with keyframes and animations)**: For styling and animation effects like border growth on hover.
- **Bootstrap 5**: To ensure a responsive and modern design.

## Preview:
- Upon loading the page, each school is represented by a card.
- The card displays the **Board**, **Academic Year**, **Board No**, **Language**, and **School Type**.
- On hover, the card's border color animates, growing and shrinking.
- Each badge has a dynamic color depending on the **Language** and **School Type**.
