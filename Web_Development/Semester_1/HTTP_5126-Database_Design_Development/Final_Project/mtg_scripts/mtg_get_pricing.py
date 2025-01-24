import requests
import csv
import time

# Define the base URL for Scryfall's API
base_url = "https://api.scryfall.com/cards"

# List to hold the card data
card_data_list = []

# Set the initial page number and loop through the pages
page = 1
while True:
    # Construct the URL for the current page
    url = f"{base_url}/search?q=format%3Aedh&page={page}&order=name"
    
    # Make a GET request to fetch data
    response = requests.get(url)
    
    # If the response is successful, process the data
    if response.status_code == 200:
        data = response.json()
        
        # If there are no more cards, break the loop
        if not data['data']:
            break
        
        # Process each card in the response
        for card in data['data']:
            card_name = card.get('name', 'N/A')
            card_set = card.get('set_name', 'N/A')
            prices = card.get('prices', {})
            normal_price = prices.get('usd', 'Not Available')
            foil_price = prices.get('usd_foil', 'Not Available')
            
            print(f"Add card: {card_name} , price : {normal_price}")
            print(f"Size of card_data_list: {len(card_data_list)}")
            # Append the card info to the list
            card_data_list.append([card_name, card_set, normal_price, foil_price])
        
        # Increment the page to get the next set of cards
        page += 1
        
        # Add a small delay to avoid hitting the API too frequently
        time.sleep(1)
    
    else:
        print(f"Error fetching data from page {page}: {response.status_code}")
        break

# Define the CSV file name to save the data
csv_filename = 'mtg_card_prices.csv'

# Write the card data to a CSV file
with open(csv_filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Card Name', 'Set Name', 'Normal Price (USD)', 'Foil Price (USD)'])
    writer.writerows(card_data_list)

print(f"Successfully saved card prices to {csv_filename}")

