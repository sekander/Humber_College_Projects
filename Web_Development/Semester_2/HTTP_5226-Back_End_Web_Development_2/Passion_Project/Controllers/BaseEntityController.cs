using System.Text.RegularExpressions;
using Microsoft.AspNetCore.Mvc;
using Passion_Project.Interface;
using Passion_Project.Models;


/*
SUMMARY
    This BaseEntityController<T> class is a generic API controller used to handle 
    CRUD operations for different entities (T). It provides common actions like 
    retrieving all entities, retrieving an entity by ID, creating, updating, 
    and deleting entities. It also includes a validation method and a mechanism to 
    save changes to the database.
*/

[Route("api/[controller]")]
[ApiController]
public class BaseEntityController<T> : ControllerBase where T : class
{
    private readonly IEntityService<T> _entityService;

    // Provides access to the entity service used for database operations
    public IEntityService<T> GetService(){return _entityService;}

    // Enum to handle validation states for Create and Update operations
    protected enum ValidationState
    {
        CREATE,
        UPDATE
    }
    
    // Default message to be returned during validation errors
    protected string return_message = "";
    // Flag to indicate if the controller is in its initial state (used for optimization)
    protected static bool _controllerInitialState = false;
    
    // Protected constructor to ensure derived classes can initialize the service
    protected BaseEntityController(IEntityService<T> entityService)
    {
        _entityService = entityService;
    }



    /// <summary>
    /// Retrieves all entities of type T from the database.
    /// </summary>
    /// <returns>Returns a list of all entities of type T.</returns>
    [HttpGet]
    public async virtual Task<IActionResult> GetAllEntities()
    {
        var entities = await _entityService.GetAllEntityAsync();
        return Ok(entities);
        
    }

    /// <summary>
    /// Retrieves a specific entity of type T by its ID.
    /// </summary>
    /// <param name="id">The ID of the entity to retrieve.</param>
    /// <returns>Returns the entity with the specified ID, or an error message if not found.</returns>
    [HttpGet("{id}")]
    public async virtual Task<IActionResult> GetEntity(int id)
    {
        var entity = await _entityService.GetEntityByIdAsync(id);
        if ( id <= 0)
        {
            return BadRequest(new  {
                success = false,
                data = id,
                message = "Please Enter an ID greater than 0",
                requestedId = id
            });
        }
        else if (entity == null) return BadRequest(new {
                success = false,
                data = id,
                message = "ID not found",
                requestedId = id
            });
        else{
            return Ok(entity);
        }
        // return (IActionResult)entity;
    }

    /// <summary>
    /// Creates a new entity of type T in the database.
    /// </summary>
    /// <param name="entity">The entity object to create.</param>
    /// <returns>Returns a success message with the created entity.</returns>
    [HttpPost]
    public async virtual Task<IActionResult> CreateEntity([FromBody] T entity)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(new
            {
                message = "Invalid data",
                errors = ModelState.Values.SelectMany(v => v.Errors).Select(e => e.ErrorMessage)
            });
        }
        else{
            await _entityService.CreateEntityAsync(entity);
            // return CreatedAtAction(nameof(GetEntity), new { id = entity.GetType().GetProperty("ID").GetValue(entity) }, entity);
            return Ok(new 
            {
                success = true,
                data = entity,
                message = "Created: " + entity,
            });
        }
    }

    /// <summary>
    /// Updates an existing entity of type T in the database.
    /// </summary>
    /// <param name="entity">The entity object to update.</param>
    /// <returns>Returns a success message with the updated entity.</returns>
    [HttpPut]
    public async virtual Task<IActionResult> UpdateEntity([FromBody] T entity)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(new
            {
                message = "Invalid data",
                errors = ModelState.Values.SelectMany(v => v.Errors).Select(e => e.ErrorMessage)
            });
        }
        else {
            // await _entityService.UpdateEntityAsync(id, entity);
            await _entityService.UpdateEntityAsync(entity);
            return Ok(new 
            {
                success = true,
                data = entity,
                message = "Updated: " + entity,
            });
        }
    }

    /// <summary>
    /// Deletes a specific entity of type T by its ID.
    /// </summary>
    /// <param name="id">The ID of the entity to delete.</param>
    /// <returns>Returns a success message if the entity was deleted, or an error message if not found.</returns>
    [HttpDelete("{id}")]
    public async virtual Task<IActionResult> DeleteEntity(int id)
    {
        var entity = await _entityService.GetEntityByIdAsync(id);

        if ( id <= 0)
        {
            return BadRequest(new  
            {
                success = false,
                data = id,
                message = "Please Enter an ID greater than 0",
                requestedId = id
            });
        }
        else if (entity == null) return BadRequest(new {
                success = false,
                data = id,
                message = "ID not found",
                requestedId = id
            });
        else {
            await _entityService.DeleteEntityAsync(id);
            return Ok(new 
            {
                success = true,
                data = id,
                message = "Deleted : " + id,
                requestedId = id
            });
        }
    }

    // public async Task <IActionResult> Save()
    // {
    //     await _entityService.SaveChangesAsync();
    //     return NoContent();
    // }

    // Method to validate entities during CREATE and UPDATE
    protected bool ValidateEntiy(ValidationState state, T entity, List<int> _entityList)
    {
        //Email regex pattern match
        string pattern = @"^[^@\s]+@[^@\s]+\.[^@\s]+$";

        //Validation for CREATE 
        if(state == ValidationState.CREATE)
        {
            // Check if the entity ID already exists in the list using LINQ
            bool idExists = _entityList.Any(item => 
                (entity is Player player && item == player.ID) ||
                (entity is Card card && item == card.ID) ||
                (entity is Deck deck && item == deck.ID));

            if (idExists)
            {
                // If ID exists, set the appropriate message
                if (entity is Player player)
                {
                    return_message = "PLAYER ID " + player.ID + " is being used, please choose a different ID";
                }
                else if (entity is Card card)
                {
                    return_message = "CARD ID " + card.ID + " is being used, please choose a different ID";
                }
                else if (entity is Deck deck)
                {
                    return_message = "DECK ID " + deck.ID + " is being used, please choose a different ID";
                }
                return false;
            }

            // Validation for empty or invalid IDs
            if( entity is Player _player && _player.ID == 0
                || entity is Card _card && _card.ID == 0
                || entity is Deck _deck && _deck.ID == 0
                || entity is Deck __deck && __deck.PlayerID == 0 )
                // || entity is Deck _deck && _deck.ID == 0 && _deck.PlayerID == 0 )
            {
                return_message = entity is Deck ? "Deck ID or Player ID cannot be 0" : "ID cannot be 0"; 
                return false;
            }

            // Get all the properties of the entity
            var properties = typeof(T).GetProperties();

            // Dynamically check for required string fields (like Name, Email, etc.)
            foreach (var prop in properties)
            {
                if (prop.PropertyType == typeof(string)) // Only check string properties
                {
                    var value = prop.GetValue(entity) as string;
                    if (string.IsNullOrEmpty(value))
                    {
                        return_message = $"{prop.Name} cannot be null or empty.";
                        return false;
                    }

                    // Additional validation for Email
                    if (prop.Name == "Email" && !Regex.IsMatch(value, pattern))
                    {
                        return_message = "Invalid Email format";
                        return false;
                    }
                }
            }
            Console.WriteLine("Validation Passed");
            return true;
        }

        //Validation for UPDATE 
        else if(state == ValidationState.UPDATE)
        {
            // Check if ID exists for update
            var entityId = _entityList.FirstOrDefault(id => 
                 (entity is Player player && id == player.ID ) || 
                 (entity is Card card && id == card.ID)  || 
                 (entity is Deck deck && id == deck.ID));

            //If entityID is returned 0 then ID is not found 
            if (entityId == 0)
            {
                return_message = "ID not found";
                return false;
            }
            
            // Get all the properties of the entity
            var properties = typeof(T).GetProperties();

            // Dynamically check for required string fields (like Name, Email, etc.)
            foreach (var prop in properties)
            {
                if (prop.PropertyType == typeof(string)) // Only check string properties
                {
                    var value = prop.GetValue(entity) as string;
                    if (string.IsNullOrEmpty(value))
                    {
                        return_message = $"{prop.Name} cannot be null or empty.";
                        return false;
                    }

                    // Additional validation for Email
                    if (prop.Name == "Email" && !Regex.IsMatch(value, pattern))
                    {
                        return_message = "Invalid Email format";
                        return false;
                    }
                }
            }
            Console.WriteLine("Validation Passed");
            return true;
        }

        return false;
    }
}
