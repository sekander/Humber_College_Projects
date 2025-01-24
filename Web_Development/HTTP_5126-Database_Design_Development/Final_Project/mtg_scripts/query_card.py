import mysql.connector
from mysql.connector import Error
import argparse

# Function to execute the query and fetch results for a given card_id
def fetch_card_data(card_id):
    try:
        # Establish the connection to MySQL database
        connection = mysql.connector.connect(
            host='192.168.2.87',      # Your MySQL host
            user='****',           # Your MySQL username
            password='******',  # Replace with your password or use a more secure method
            database='mtg'         # The database to use
        )

        if connection.is_connected():
            print(f"Successfully connected to the database to fetch data for card_id: {card_id}")

            # Create a cursor object to execute queries
            cursor = connection.cursor()

            # Define the query, using the passed card_id
            query = f"SELECT * FROM Data_Store_Available_Cards WHERE card_id = {card_id};"

            # Execute the query
            cursor.execute(query)

            # Fetch and print the result
            result = cursor.fetchall()
            if result:
                for row in result:
                    print("card_id: ", row[0], "name: ", row[1], "quantity: ", row[2], "normal_price: ", row[3], "foil_price: ", row[4])
            else:
                print(f"No data found for card_id: {card_id}")

    except Error as e:
        print("Error while connecting to MySQL", e)

    finally:
        # Close the connection if it's open
        if connection.is_connected():
            cursor.close()
            connection.close()
            print("MySQL connection is closed")

# Parse the card_id from command line arguments
if __name__ == "__main__":
    # Create the argument parser
    parser = argparse.ArgumentParser(description="Fetch card data from MySQL database")
    
    # Add the argument for card_id
    parser.add_argument("card_id", type=int, help="The card_id to fetch data for")
    
    # Parse the arguments
    args = parser.parse_args()

    # Fetch and print the card data using the provided card_id
    fetch_card_data(args.card_id)

