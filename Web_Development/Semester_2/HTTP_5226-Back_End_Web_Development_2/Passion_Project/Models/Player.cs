namespace Passion_Project.Models
{
    public class Player
    {
        // Unique identifier for the player
        public int ID {get; set;}
        // Name of the player
        public string ?Name {get; set;}
        // Email of the player
        public string ?Email {get; set;}
        // Collection of decks owned by the player
        public ICollection<Deck> ?Decks {get; set;}
    }
}