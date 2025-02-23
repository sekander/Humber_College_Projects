using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Passion_Project.Interface;
using Passion_Project.Models;

[Route("api/[controller]")]
[ApiController]
public class CardController : BaseEntityController<Card>
{
    // A static list to store card IDs. Shared across all instances of the CardController.
    private static List<int> card_ids = new List<int>();

    private IEntityService<Card> _cardService;

    public CardController(IEntityService<Card> entityService) : base(entityService) 
    {
        // This condition checks whether the controller has been initialized before. 
        // The flag _controllerInitialState is static, meaning it's shared by all instances of the CardController.
        // If _controllerInitialState is false, this block will run to initialize the card IDs.
        if(!_controllerInitialState)
        {
            // Clears the static list to ensure we have no stale data in it when initializing.
            card_ids.Clear();
            // var counter = 0;
            // Fetch all cards from the entity service and populate the card_ids list with their IDs.
            foreach (var item in entityService.GetCards())
            {
                // Add the ID of each card to the static card_ids list.
                card_ids.Add(item.ID);
                // Console.WriteLine(card_ids[counter]);
                // counter++;
            }
            _controllerInitialState = true;
        }

        _cardService = entityService;
     }

    /// <summary>
    /// Retrieves all cards from the database.
    /// </summary>
    /// <returns>Returns a list of all cards.</returns>
    /// <example>
    /// GET /api/card
    /// Response:
    /// [
    ///     { "id": 1, "name": "Ace of Spades", "description": "High value card" },
    ///     { "id": 2, "name": "Two of Hearts", "description": "Low value card" }
    /// ]
    /// </example>
    public override async Task<IActionResult> GetAllEntities()
    {
        Console.WriteLine("CUSTOM GET ALL CARDS");
        return Ok(await base.GetAllEntities());
    }


    /// <summary>
    /// Retrieves a specific card by its ID.
    /// </summary>
    /// <param name="id">The ID of the card to retrieve.</param>
    /// <returns>Returns the card with the specified ID, or an error message if not found.</returns>
    /// <example>
    /// GET /api/card/1
    /// Response:
    /// {"id":2,"name":"Shahrazad","description":"Players play a Magic subgame, using their libraries as their decks. 
    /// Each player who doesn't win the subgame loses half their life, rounded up."}
    /// </example>
    public override async Task<IActionResult> GetEntity(int id)
    {
        Console.WriteLine($"CUSTOM GET CARD : {id}");
        return Ok(await base.GetEntity(id));
    } 

    /// <summary>
    /// Creates a new card in the database.
    /// </summary>
    /// <param name="card">The card object to create.</param>
    /// <returns>Returns a success message with the created card.</returns>
    /// <example>
    /// POST /api/card
    /// Request Body:
    /// { "id": "100000", "name": "Ace of Spades", "description": "High value card" }
    /// Response:
    /// { "success": true, "data": { "id": 100000, "name": "Ace of Spades", "description": "High value card" }, "message": "Created: Ace of Spades" }
    /// </example>
    public override async Task<IActionResult> CreateEntity([FromBody] Card card)
    {
        if(!ValidateEntiy(ValidationState.CREATE, card, card_ids))
        {
            return BadRequest(new
            {
                data = card,
                message = return_message,
            });
        }
        else {
            Console.WriteLine($"CUSTOM CREATE CARD");
            card_ids.Add(card.ID);
            return await base.CreateEntity(card);
        }
    }

    /// <summary>
    /// Updates an existing card in the database.
    /// </summary>
    /// <param name="card">The card object to update.</param>
    /// <returns>Returns a success message with the updated card.</returns>
    /// <example>
    /// PUT /api/card
    /// Request Body:
    /// { "id": 1, "name": "Ace of Diamonds", "description": "Updated high value card" }
    /// Response:
    /// { "success": true, "data": { "id": 1, "name": "Ace of Diamonds", "description": "Updated high value card" }, "message": "Updated: Ace of Diamonds" }
    /// </example>
    public override async Task<IActionResult> UpdateEntity([FromBody] Card card)
    {
        if(!ValidateEntiy(ValidationState.UPDATE, card, card_ids))
        {
            return BadRequest(new
            {
                data = card,
                message = return_message,
            });
        }
        else{
            Console.WriteLine($"CUSTOM UPDATE CARD");
            return await base.UpdateEntity(card);
        }
    }

    /// <summary>
    /// Deletes a specific card by its ID.
    /// </summary>
    /// <param name="id">The ID of the card to delete.</param>
    /// <returns>Returns a success message if the card was deleted, or an error message if not found.</returns>
    /// <example>
    /// DELETE /api/card/1
    /// Response:
    /// { "success": true, "data": 1, "message": "Deleted: 1", "requestedId": 1 }
    /// </example>
    public override async Task<IActionResult> DeleteEntity(int id)
    {
        Console.WriteLine($"CUSTOM DELETE CARD");
        _controllerInitialState = false;
        return await base.DeleteEntity(id);
    }
}
