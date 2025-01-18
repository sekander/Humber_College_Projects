import csv

# Path to your CSV file
csv_file_path = 'mtg_card_prices.csv'

# Path to the output SQL file
sql_file_path = 'mtg_card_prices.sql'

# Open the CSV file
with open(csv_file_path, mode='r', newline='', encoding='utf-8') as file:
    reader = csv.reader(file)
    
    # Skip the header row
    next(reader)
    
    # Open the SQL file to write the SQL commands
    with open(sql_file_path, 'w', encoding='utf-8') as sql_file:
        # Write the CREATE TABLE statement to the SQL file
        sql_file.write('''
CREATE TABLE IF NOT EXISTS mtg_cards (
    card_name TEXT,
    set_name TEXT,
    normal_price REAL,
    foil_price REAL
);
''')
        
        # Insert rows into the database
        for row in reader:
            card_name = row[0]
            set_name = row[1]
            
            # Handle 'Not Available' or empty string values and convert to None
            normal_price = "NULL" 
            if row[2] not in ['Not Available', '']:  # Check if the price is not 'Not Available' or empty
                try:
                    normal_price = float(row[2])  # Try converting to float
                except ValueError:
                    normal_price = "NULL" # In case of invalid format, set to None
            
            foil_price = "NULL" 
            if row[3] not in ['Not Available', '']:  # Check if the price is not 'Not Available' or empty
                try:
                    foil_price = float(row[3])  # Try converting to float
                except ValueError:
                    foil_price = "NULL" # In case of invalid format, set to None

            # Create the SQL INSERT statement for each row
            insert_statement = f'''
INSERT INTO mtg_cards (card_name, set_name, normal_price, foil_price)
VALUES ("{card_name}", "{set_name}", {normal_price}, {foil_price});
'''
            # Write the INSERT statement to the SQL file
            sql_file.write(insert_statement)

print(f"SQL file '{sql_file_path}' has been generated successfully!")

