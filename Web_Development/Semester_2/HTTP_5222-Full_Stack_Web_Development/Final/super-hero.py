import requests
import time
import json

API_KEY = 'd4f4b5f898eaf35d160c4a0c6a044a43'
base_url = "https://superheroapi.com/api/{}/".format(API_KEY)

character_names = []

#for i in range(1, 733):
#    print (i)
        
#for i in range(1, 733):
for i in range(1, 733):
    try:
        #print (i)
        response = requests.get(f"{base_url}{i}")
        if response.status_code == 200:
            data = response.json()
            character_name = data.get('name')
            character_names.append(character_name)
            print(f"Character name '{character_name}' saved to file.")
            #print(f"Character {i}: {response.json()}")
        else:
            print(f"Failed to retrieve character {i}")
        time.sleep(0.25)
    except requests.exceptions.RequestException as e:
        print(f"An error occurred for character {i}: {e}")
        continue

# Save the character names into a JSON file
file_path = 'character_names.json'
with open(file_path, 'w') as json_file:
    json.dump({"characters": character_names}, json_file, indent=2)

print(f"All character names have been saved to '{file_path}'.")
