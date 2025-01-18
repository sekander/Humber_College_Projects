import json
import mysql.connector
from mysql.connector import Error

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
with open('cards.json', 'r') as file:
    cards_data = json.load(file)

# Iterate through each card and insert data into the table
for data in cards_data:
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
        data['id'], data['oracle_id'], data['name'], data['lang'], data['released_at'],
        data['uri'], data['scryfall_uri'], data['layout'], data['highres_image'],
        data['image_status'], data['mana_cost'], data['cmc'], data['type_line'],
        data['oracle_text'], data['power'], data['toughness'],
        ', '.join(data['colors']), ', '.join(data['color_identity']),
        data['rarity'], data['artist']
    ))








# Close the connection
if conn:
	# Commit changes and close the connection
	conn.commit()
	cursor.close()
	conn.close()
    #conn.close()

