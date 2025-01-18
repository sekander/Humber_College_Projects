import json
import mysql.connector
from mysql.connector import Error
import ijson

def create_connection(host_name, user_name, user_password, db_name):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            password=user_password,
            database=db_name
        )
        print("Connection to MySQL DB successful")
    except Error as e:
        print(f"The error '{e}' occurred")
    
    return connection

# Replace with your own values
host = "localhost"  # or your host
user = "****"
password = "******"
database = "mtg"

# Create a connection
conn = create_connection(host, user, password, database)
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS cards (
    id VARCHAR(36) PRIMARY KEY,
    oracle_id VARCHAR(36),
    name VARCHAR(255),
    lang VARCHAR(10),
    released_at DATE,
    uri VARCHAR(255),
    scryfall_uri VARCHAR(255),
    layout VARCHAR(50),
    highres_image BOOLEAN,
    image_status VARCHAR(50),
    mana_cost VARCHAR(50),
    cmc FLOAT,
    type_line VARCHAR(255),
    oracle_text TEXT,
    power VARCHAR(10),
    toughness VARCHAR(10),
    colors VARCHAR(255),
    color_identity VARCHAR(255),
    rarity VARCHAR(50),
    artist VARCHAR(255)
)
''')

# Load JSON data from a file
with open('cards.json', 'r', encoding='utf-8') as file:
    # Use ijson to parse the file iteratively
    for data in ijson.items(file, 'item'):  # Adjust 'item' based on your JSON structure
        try:
            cursor.execute('''
            INSERT INTO cards (
                id, oracle_id, name, lang, released_at, uri, scryfall_uri, layout,
                highres_image, image_status, mana_cost, cmc, type_line, oracle_text,
                power, toughness, colors, color_identity, rarity, artist
            ) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
            ON DUPLICATE KEY UPDATE 
                oracle_id = VALUES(oracle_id), 
                name = VALUES(name), 
                lang = VALUES(lang),
                released_at = VALUES(released_at),
                uri = VALUES(uri),
                scryfall_uri = VALUES(scryfall_uri),
                layout = VALUES(layout),
                highres_image = VALUES(highres_image),
                image_status = VALUES(image_status),
                mana_cost = VALUES(mana_cost),
                cmc = VALUES(cmc),
                type_line = VALUES(type_line),
                oracle_text = VALUES(oracle_text),
                power = VALUES(power),
                toughness = VALUES(toughness),
                colors = VALUES(colors),
                color_identity = VALUES(color_identity),
                rarity = VALUES(rarity),
                artist = VALUES(artist)
            ''', (
                data.get('id'), 
                data.get('oracle_id'), 
                data.get('name'), 
                data.get('lang'), 
                data.get('released_at'),
                data.get('uri'), 
                data.get('scryfall_uri'), 
                data.get('layout'), 
                data.get('highres_image'),
                data.get('image_status'), 
                data.get('mana_cost'), 
                data.get('cmc'), 
                data.get('type_line'),
                data.get('oracle_text'), 
                data.get('power', None),  # Default to None if 'power' is missing
                data.get('toughness', None),  # Default to None if 'toughness' is missing
                ', '.join(data.get('colors', [])),  # Default to empty list if 'colors' is missing
                ', '.join(data.get('color_identity', [])),  # Default to empty list if 'color_identity' is missing
                data.get('rarity'), 
                data.get('artist')
            ))
        except json.JSONDecodeError as e:
            print(f"Error decoding JSON: {e}")
        except MemoryError:
            print("MemoryError: Unable to load more data into memory. Exiting...")
            break
        except Error as e:
            print(f"Database error: {e}")

# Close the connection
if conn:
    # Commit changes and close the connection
    conn.commit()
    cursor.close()
    conn.close()

print("Data inserted successfully")

