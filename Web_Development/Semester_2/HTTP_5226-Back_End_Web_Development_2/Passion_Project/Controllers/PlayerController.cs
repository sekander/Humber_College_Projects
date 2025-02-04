using Microsoft.AspNetCore.Mvc;
using Passion_Project.Interface;
using Passion_Project.Models;

[Route("api/[controller]")]
[ApiController]
public class PlayerController : BaseEntityController<Player>
{
    // A static list to store player IDs. Shared across all instances of the PlayerController.
    private static List<int> player_ids = new List<int>(); 

    public PlayerController(IEntityService<Player> entityService) : base(entityService) 
    { 
        // This condition checks whether the controller has been initialized before. 
        // The flag _controllerInitialState is static, meaning it's shared by all instances of the PlayerController.
        // If _controllerInitialState is false, this block will run to initialize the player IDs.
        if(!_controllerInitialState)
        {
            // Clears the static list to ensure we have no stale data in it when initializing.
            player_ids.Clear();
            // var counter = 0;
            // Fetch all players from the entity service and populate the player_ids list with their IDs.
            foreach (var item in entityService.GetPlayers())
            {
                // Add the ID of each player to the static player_ids list.
                player_ids.Add(item.ID);
                // Console.WriteLine(player_ids[counter]);
                // counter++;
            }
            _controllerInitialState = true;
        }
    }

    /// <summary>
    /// Retrieves all players from the database.
    /// </summary>
    /// <returns>Returns a list of all players.</returns>
    /// <example>
    /// GET /api/player
    /// Response:
    /// [
    ///     { "id": 1, "name": "John Doe", "email": "john.doe@example.com" },
    ///     { "id": 2, "name": "Jane Smith", "email": "jane.smith@example.com" }
    /// ]
    /// </example>
    public override async Task<IActionResult> GetAllEntities()
    {
        Console.WriteLine("CUSTOM GET ALL PLAYERS");
        return Ok(await base.GetAllEntities());
    }

    /// <summary>
    /// Retrieves a specific player by their ID.
    /// </summary>
    /// <param name="id">The ID of the player to retrieve.</param>
    /// <returns>Returns the player with the specified ID, or an error message if not found.</returns>
    /// <example>
    /// GET /api/player/1
    /// Response:
    /// { "id": 1, "name": "John Doe", "email": "john.doe@example.com" }
    /// </example>
    public override async Task<IActionResult> GetEntity(int id)
    {
        Console.WriteLine($"CUSTOM GET PLAYER : {id}");
        return Ok(await base.GetEntity(id));
    } 

    /// <summary>
    /// Creates a new player in the database.
    /// </summary>
    /// <param name="player">The player object to create.</param>
    /// <returns>Returns a success message with the created player.</returns>
    /// <example>
    /// POST /api/player
    /// Request Body:
    /// { "name": "John Doe", "email": "john.doe@example.com" }
    /// Response:
    /// { "success": true, "data": { "id": 1, "name": "John Doe", "email": "john.doe@example.com" }, "message": "Created: John Doe" }
    /// </example>
    public override async Task<IActionResult> CreateEntity([FromBody] Player player)
    {
        if(!ValidateEntiy(ValidationState.CREATE, player, player_ids))
        {
            return BadRequest(new
            {
                data = player,
                message = return_message,
            });
        }
        else{
            Console.WriteLine($"CUSTOM CREATE PLAYER");
            player_ids.Add(player.ID);
            return await base.CreateEntity(player);
        }
    }

    /// <summary>
    /// Updates an existing player in the database.
    /// </summary>
    /// <param name="player">The player object to update.</param>
    /// <returns>Returns a success message with the updated player.</returns>
    /// <example>
    /// PUT /api/player
    /// Request Body:
    /// { "id": 1, "name": "John Doe Updated", "email": "john.doe.updated@example.com" }
    /// Response:
    /// { "success": true, "data": { "id": 1, "name": "John Doe Updated", "email": "john.doe.updated@example.com" }, "message": "Updated: John Doe Updated" }
    /// </example>
    public override async Task<IActionResult> UpdateEntity([FromBody] Player player)
    {
        if(!ValidateEntiy(ValidationState.UPDATE, player, player_ids))
        {
            return BadRequest(new
            {
                data = player,
                message = return_message,
            });
        }
        else{
            Console.WriteLine($"CUSTOM UPDATE PLAYER");
            return await base.UpdateEntity(player);
        }
    }

    /// <summary>
    /// Deletes a specific player by their ID.
    /// </summary>
    /// <param name="id">The ID of the player to delete.</param>
    /// <returns>Returns a success message if the player was deleted, or an error message if not found.</returns>
    /// <example>
    /// DELETE /api/player/1
    /// Response:
    /// { "success": true, "data": 1, "message": "Deleted: 1", "requestedId": 1 }
    /// </example>
    public override async Task<IActionResult> DeleteEntity(int id)
    {
        Console.WriteLine($"CUSTOM DELETE PLAYER");
        _controllerInitialState = false;
        return await base.DeleteEntity(id);
    }

}