using System.Text.Json.Serialization;

namespace Passion_Project.Models
{
    public class Card 
    {
        //type_line, colors, power, toughness, mana_cost 
        // Unique identifier for the card
        public int ID {get; set;}
        // Name of the card
        public string ?Name {get; set;}
        // Description of the card
        public string ?Description {get; set;}

        public string ?ImageUrl {get; set;}

        public string ?TypeLine {get; set;}

        public string ?Colors {get; set;}

        public string ?ManaCost {get; set;} 

        public string ?Power {get; set;}

        public string ?Toughness {get; set;}


        
        // Collection of CardDeck relationships, 
        // ignored during JSON serialization to prevent circular reference
        [JsonIgnore]
        public virtual ICollection<CardDeck>? CardDecks { get; set; }
        
    }
}
