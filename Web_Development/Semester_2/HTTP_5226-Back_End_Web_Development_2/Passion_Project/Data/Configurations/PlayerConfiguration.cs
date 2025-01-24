using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Passion_Project.Models;

public class PlayerConfiguration : IEntityTypeConfiguration<Player>
{
    public void Configure(EntityTypeBuilder<Player> builder)
    {
        builder.HasKey(u => u.player_id); // Set Primary Key
        builder.HasIndex(u => u.email).IsUnique(); // Unique constraint for email

        // Define other configurations (if any)
    }

    void IEntityTypeConfiguration<Player>.Configure(EntityTypeBuilder<Player> builder)
    {
        throw new NotImplementedException();
    }
}
