using Microsoft.EntityFrameworkCore;
using Passion_Project.Models;

namespace Passion_Project.Data 
{
    /*
    SUMMARY
        The AppDbContext class represents the database context for the application. 
        It is a central part of the Entity Framework Core (EF Core) framework and defines 
        how the application's data is structured and accessed. This class interacts with 
        the database using DbSet properties to represent entities (like Player, Card, Deck, 
        and CardDeck), allowing you to perform CRUD (Create, Read, Update, Delete) operations. 
        It also configures relationships and constraints between these entities.
    */
    public class AppDbContext : DbContext
    {
        // Constructor to pass the options to the base DbContext class.
        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options) {}

        // DbSet properties representing tables in the database for Player, Card, Deck, and CardDeck entities.
        public DbSet<Player> Players{get; set;}
        public DbSet<Card> Cards{get; set;}
        public DbSet<Deck> Decks{get; set;}
        public DbSet<CardDeck> CardDecks {get; set;}

        // OnModelCreating is called to configure the model for the context (set up relationships, constraints, etc.).
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            

            base.OnModelCreating(modelBuilder);

            // Configure the Description property in the Card entity to use TEXT type in MySQL
            modelBuilder.Entity<Card>()
                .Property(c => c.Description)
                .HasColumnType("TEXT");  // Set the column type to TEXT for the Description field

            // configures one-to-many relationship
            modelBuilder.Entity<Deck>()
                .HasOne(d => d.CurrentPlayer)
                .WithMany(p => p.Decks)
                .HasForeignKey(d => d.PlayerID)
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<CardDeck>()
                .HasKey(cd => new { cd.DeckID, cd.CardID});

            // Define a unique constraint to ensure that each Card can only appear once in a Deck
            modelBuilder.Entity<CardDeck>()
                .HasIndex(cd => new { cd.DeckID, cd.CardID })  // Create index on DeckID and CardID
                .IsUnique();  // Ensure that the combination of DeckID and CardID is unique


             // Configure the foreign key relationships for the CardDeck junction table
            modelBuilder.Entity<CardDeck>()
                .HasOne(cd => cd.Deck)  // A CardDeck belongs to one Deck
                .WithMany(d => d.CardDecks)  // A Deck can have many CardDecks
                .HasForeignKey(cd => cd.DeckID)  // Foreign key in CardDeck referencing Deck
                .OnDelete(DeleteBehavior.Cascade);  // Cascade delete for Deck

            modelBuilder.Entity<CardDeck>()
                .HasOne(cd => cd.Card)  // A CardDeck belongs to one Card
                .WithMany(c => c.CardDecks)  // A Card can have many CardDecks
                .HasForeignKey(cd => cd.CardID)  // Foreign key in CardDeck referencing Card
                .OnDelete(DeleteBehavior.Cascade);  // Cascade delete for Card
        }
    }
}
