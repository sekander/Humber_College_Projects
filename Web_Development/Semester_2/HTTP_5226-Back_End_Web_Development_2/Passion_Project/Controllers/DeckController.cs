using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Passion_Project.Interface;
using Passion_Project.Models;

[Route("api/[controller]")]
[ApiController]
public class DeckController : BaseEntityController<Deck>
{
    // A static list to store deck IDs. Shared across all instances of the DeckController.
    private static List<int> deck_ids = new List<int>();
    public DeckController(IEntityService<Deck> entityService) : base(entityService) 
    { 
        // This condition checks whether the controller has been initialized before. 
        // The flag _controllerInitialState is static, meaning it's shared by all instances of the DeckController.
        // If _controllerInitialState is false, this block will run to initialize the deck IDs.
        if(!_controllerInitialState)
        {
            // Clears the static list to ensure we have no stale data in it when initializing.
            deck_ids.Clear();
            // var counter = 0;
            // Fetch all decks from the entity service and populate the decks_ids list with their IDs.
            foreach (var item in entityService.GetDecks())
            {
                // Add the ID of each deck to the static deck_ids list.
                deck_ids.Add(item.ID);
                // Console.WriteLine(deck_ids[counter]);
                // counter++;
            }
            _controllerInitialState = true;
        }
    }

    /// <summary>
    /// Retrieves all decks from the database.
    /// </summary>
    /// <returns>Returns a list of all decks.</returns>
    /// <example>
    /// GET /api/deck
    /// Response:
    /// [
    ///     { "id": 1, "name": "Deck 1", "description": "First deck" },
    ///     { "id": 2, "name": "Deck 2", "description": "Second deck" }
    /// ]
    /// </example>
    public override async Task<IActionResult> GetAllEntities()
    {
        Console.WriteLine("CUSTOM GET ALL DECKS");
        return Ok(await base.GetAllEntities());
    }

    /// <summary>
    /// Retrieves a specific deck by its ID from the database.
    /// </summary>
    /// <param name="id">The ID of the deck to retrieve.</param>
    /// <returns>Returns the details of the deck with the specified ID.</returns>
    /// <example>
    /// GET /api/deck/{id}
    /// Response:
    /// { "id": 1, "name": "Deck 1", "description": "First deck" }
    /// </example>
    public override async Task<IActionResult> GetEntity(int id)
    {
        Console.WriteLine($"CUSTOM GET DECK : {id}");
        return Ok(await base.GetEntity(id));
    } 


    /// <summary>
    /// Creates a new deck in the database.
    /// </summary>
    /// <param name="deck">The deck object to be created.</param>
    /// <returns>Returns the created deck.</returns>
    /// <example>
    /// POST /api/deck
    /// Request body:
    /// { "id": 3, "name": "New Deck", "description": "A brand new deck." }
    /// Response:
    /// { "id": 3, "name": "New Deck", "description": "A brand new deck." }
    /// </example>
    public override async Task<IActionResult> CreateEntity([FromBody] Deck deck)
    {
        if(!ValidateEntiy(ValidationState.CREATE, deck, deck_ids))
        {
            return BadRequest(new
            {
                data = deck,
                message = return_message,
            });
        }
        else{
            Console.WriteLine($"CUSTOM CREATE DECK");
            deck_ids.Add(deck.ID);
            return await base.CreateEntity(deck);
        }
    }

    /// <summary>
    /// Updates an existing deck in the database.
    /// </summary>
    /// <param name="deck">The updated deck object.</param>
    /// <returns>Returns the updated deck.</returns>
    /// <example>
    /// PUT /api/deck
    /// Request body:
    /// { "id": 1, "name": "Updated Deck", "description": "Updated description." }
    /// Response:
    /// { "id": 1, "name": "Updated Deck", "description": "Updated description." }
    /// </example>
    public override async Task<IActionResult> UpdateEntity([FromBody] Deck deck)
    {
        if(!ValidateEntiy(ValidationState.UPDATE, deck, deck_ids))
        {
            return BadRequest(new
            {
                data = deck,
                message = return_message,
            });
        }
        else{
            Console.WriteLine($"CUSTOM UPDATE DECK");
            // return await base.UpdateEntity(id, deck);
            return await base.UpdateEntity(deck);
        }
    }

    /// <summary>
    /// Deletes a specific deck by its ID from the database.
    /// </summary>
    /// <param name="id">The ID of the deck to delete.</param>
    /// <returns>Returns a response indicating whether the delete was successful or not.</returns>
    /// <example>
    /// DELETE /api/deck/{id}
    /// Response:
    /// No Content (indicates successful deletion)
    /// </example>
    public override async Task<IActionResult> DeleteEntity(int id)
    {
        Console.WriteLine($"CUSTOM DELETE DECK");
        _controllerInitialState = false;
        return await base.DeleteEntity(id);
    }

    /// <summary>
    /// Creates a new CardDeck relationship, linking a card to a deck.
    /// </summary>
    /// <param name="cardDeck">The CardDeck object containing card and deck IDs.</param>
    /// <returns>Returns the created CardDeck object.</returns>
    /// <example>
    /// POST /api/deck/card
    /// Request body:
    /// { "DeckID": 1, "CardID": 5 }
    /// Response:
    /// { "DeckID": 1, "CardID": 5 }
    /// </example>
    [HttpPost("card")]
    public async Task<IActionResult> CreateCardEntity([FromBody] CardDeck cardDeck)
    {
        // Check if the Deck exists
        var deck = await base.GetService().GetDecks().FindAsync(cardDeck.DeckID);
        if (deck == null)
        {
            return NotFound($"Deck with ID {cardDeck.DeckID} not found.");
        }

        // Check if the Card exists
        var card = await base.GetService().GetCards().FindAsync(cardDeck.CardID);
        if (card == null)
        {
            return NotFound($"Card with ID {cardDeck.CardID} not found.");
        }
        
        //Need to handle adding a card that already exists in deck
         // Check if the CardDeck already exists (if a combination of DeckID and CardID already exists)
        var existingCardDeck = await base.GetService().GetCardDecks()
        .FirstOrDefaultAsync(cd => cd.DeckID == cardDeck.DeckID && cd.CardID == cardDeck.CardID);

        if (existingCardDeck != null)
        {
            // If the CardDeck already exists, return a conflict response
            return Conflict(new
            {
                message = $"Card with ID {cardDeck.CardID} already exists in Deck with ID {cardDeck.DeckID}."
            });
        }




        // Add the CardDeck entry
        await base.GetService().GetCardDecks().AddAsync(cardDeck);
        
        // Save changes to the database
        await base.GetService().SaveChangesAsync();

        // Return the created CardDeck object with status code 201
        return CreatedAtAction(nameof(GetEntity), new { id = cardDeck.DeckID }, cardDeck);
    }

    /// <summary>
    /// Retrieves all cards associated with a specific deck.
    /// </summary>
    /// <param name="id">The ID of the deck to retrieve cards for.</param>
    /// <returns>Returns a list of card IDs associated with the deck.</returns>
    /// <example>
    /// GET /api/deck/{id}/allcards
    /// Response:
    /// [ 1, 2, 3 ]  // List of card IDs associated with the deck
    /// </example>
    [HttpGet("{id}/allcards")]
    public async Task<IActionResult> ListAllCards(int id) {
        // Check if there are any CardDeck entries for the given DeckID
        var cardDecks = await base.GetService().GetCardDecks()
                                    .Where(cd => cd.DeckID == id)
                                    .ToListAsync();
        
        // If no card-deck associations are found, return a "Not Found" response. 
        if (cardDecks == null || !cardDecks.Any())
        {
            return NotFound($"No cards found for Deck with ID {id}.");
        }
    
        // Select the CardIDs from the CardDeck entries and return them in the response.
        var cards = cardDecks.Select(cd => cd.CardID).ToList();
    
        return Ok(cards);
    }
}
