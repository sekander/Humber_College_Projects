using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.EntityFrameworkCore;

namespace Passion_Project.Models
{
    [Index(nameof(email), IsUnique = true)]
    public class Player
    {
        [Key]
        public int player_id {get; set;}

        public required string name {get; set;}

        public required string email {get; set;}

    }

}