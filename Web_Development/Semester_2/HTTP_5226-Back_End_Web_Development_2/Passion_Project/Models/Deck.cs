using System.Text.Json.Serialization;

namespace Passion_Project.Models
{
    public class Deck 
    {
        // Unique identifier for the deck
        public int ID {get; set;}
        // Name of the deck
        public string ?Name {get; set;}
        // Description of the deck
        public string ?Description {get; set;}

        // Player ID associated with this deck
        public int PlayerID {get; set;}
        // The player who owns this deck
        public Player ?CurrentPlayer {get; set;}


        // Collection of CardDeck relationships, 
        // ignored during JSON serialization to prevent circular reference
        [JsonIgnore]
        public virtual ICollection<CardDeck>? CardDecks { get; set; }
    }
}
