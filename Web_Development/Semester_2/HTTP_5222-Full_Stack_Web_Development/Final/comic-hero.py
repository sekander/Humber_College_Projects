import requests

# Define your API key and base URL
API_KEY = '4102852836802edc6c87a2657b99f8f9dd40e852'
BASE_URL = 'https://comicvine.gamespot.com/api/'

def get_character_id(character_name):
    # Construct the search URL
    search_url = f"{BASE_URL}search/"
    
    # Parameters for the API request
    params = {
        'api_key': API_KEY,
        'format': 'json',
        'query': character_name,
        'resources': 'character'  # We only want to search for characters
    }
    
    # Make the API request
    response = requests.get(search_url, params=params)
    
    # Check if the request was successful
    if response.status_code == 200:
        data = response.json()
        
        # Check if there are results
        if 'results' in data and len(data['results']) > 0:
            # Get the first result and return the character's ID
            character = data['results'][0]
            character_id = character['id']
            return character_id
        else:
            print(f"No characters found for '{character_name}'.")
    else:
        print(f"Error: {response.status_code}")
    
    return None


def get_comic_covers(character_id):
    # Construct the comics URL to get related issues (using character ID)
    comic_url = f"{BASE_URL}issues/"
    
    # Parameters for the API request
    params = {
        'api_key': API_KEY,
        'format': 'json',
        'character_id': character_id,  # Using the character ID here
        'limit': 5  # Fetch only the first 5 issues
    }
    
    # Make the API request
    response = requests.get(comic_url, params=params)
    
    # Check if the request was successful
    if response.status_code == 200:
        data = response.json()
        
        # Check if there are results
        if 'results' in data and len(data['results']) > 0:
            print(f"Found comic issues for character ID {character_id}:")
            for comic in data['results']:
                comic_title = comic.get('name', 'No Title')
                comic_cover_url = comic.get('image', {}).get('small_url', None)
                
                if comic_cover_url:
                    print(f"Title: {comic_title}")
                    print(f"Cover Image URL: {comic_cover_url}")
                    print('---')
                else:
                    print(f"Title: {comic_title} has no cover image available.")
        else:
            print(f"No comic issues found for character ID {character_id}.")
    else:
        print(f"Error: {response.status_code}")


# Main function to execute the process
if __name__ == "__main__":
    character_name = input("Enter the character name: ")
    character_id = get_character_id(character_name)
    
    if character_id:
        get_comic_covers(character_id)
    else:
        print("Character ID not found.")

