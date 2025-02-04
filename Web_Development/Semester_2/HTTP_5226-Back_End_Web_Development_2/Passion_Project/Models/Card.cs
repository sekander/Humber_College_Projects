using System.Text.Json.Serialization;

namespace Passion_Project.Models
{
    public class Card 
    {
        // Unique identifier for the card
        public int ID {get; set;}
        // Name of the card
        public string ?Name {get; set;}
        // Description of the card
        public string ?Description {get; set;}

        
        // Collection of CardDeck relationships, 
        // ignored during JSON serialization to prevent circular reference
        [JsonIgnore]
        public virtual ICollection<CardDeck>? CardDecks { get; set; }
        
    }
}
