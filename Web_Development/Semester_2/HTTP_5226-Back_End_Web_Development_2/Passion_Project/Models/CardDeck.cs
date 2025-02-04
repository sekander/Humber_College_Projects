namespace Passion_Project.Models
{
    public class CardDeck
    {
        // Deck ID for this card-deck relationship
        public int DeckID { get; set; }
        // The deck associated with this card-deck relationship
        public Deck ?Deck { get; set; }
        // Card ID for this card-deck relationship
        public int CardID { get; set; }
        // The card associated with this card-deck relationship
        public Card ?Card { get; set; }
    }
}