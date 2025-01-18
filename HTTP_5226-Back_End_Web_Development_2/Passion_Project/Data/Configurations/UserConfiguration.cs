using Passion_Project.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace Passion_Project.Data.ApplyConfigurations
{
    public class PlayerConfiguration : IEntityTypeConfiguration<Player>
    {
        public void Configure(EntityTypeBuilder<Player> builder)
        {
            builder.HasKey(u => u.player_id); // Set Primary Key
            
            builder.Property(p => p.name)
                   .IsRequired()
                   .HasMaxLength(100); // Example: Add restrictions on name length

            builder.Property(p => p.email)
                   .IsRequired()
                   .HasMaxLength(255);
        }
    }
}