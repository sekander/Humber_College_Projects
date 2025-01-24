import json

# Attempt to load JSON data from a file
try:
    with open('cards.json', 'r') as file:
        content = file.read()
        # Try to parse the entire content as a JSON array
        try:
            cards_data = json.loads(content)
        except json.JSONDecodeError as e:
            print(f"Error decoding JSON: {e}")

            # If it fails, split content into multiple parts
            # This assumes the objects are separated by newlines
            for line in content.splitlines():
                line = line.strip()  # Remove surrounding whitespace
                if line:  # Process non-empty lines
                    try:
                        data = json.loads(line)
                        pretty_json = json.dumps(data, indent=4)
                        print(pretty_json)  # Print each card in pretty format
                    except json.JSONDecodeError as e:
                        print(f"Error decoding JSON line: {e}")
except FileNotFoundError:
    print("The specified JSON file was not found.")
except Exception as e:
    print(f"An error occurred: {e}")

