using Passion_Project.Models;
using Microsoft.EntityFrameworkCore;

// namespace Passion_Project.Data
namespace Passion_Project
{
    public class AppDbContext : DbContext
    {
        public DbSet<Player> Players { get; set; }
        // public DbSet<Role> Roles { get; set; }

        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.ApplyConfigurationsFromAssembly(typeof(AppDbContext).Assembly);
        }
    }
}