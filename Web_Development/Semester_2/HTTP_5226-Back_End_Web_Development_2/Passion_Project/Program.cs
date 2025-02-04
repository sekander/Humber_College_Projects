using Microsoft.EntityFrameworkCore;
using Passion_Project.Data;
using Passion_Project.Interface;
using Passion_Project.Models;


var builder = WebApplication.CreateBuilder(args);


// Add services to the container.
builder.Services.AddControllers();

// Add Pomelo DbContext with MySQL
builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseMySql(
        builder.Configuration.GetConnectionString("DefaultConnection"), 
        ServerVersion.AutoDetect(builder.Configuration.GetConnectionString("DefaultConnection"))
    )
);


// Register IPlayerService and PlayerService for dependency injection
//builder.Services.AddScoped<IPlayerService, PlayerService>();
// builder.Services.AddScoped<IEntityService<T>, PlayerService>();
// builder.Services.AddScoped(typeof(IEntityService<>), typeof(PlayerService<>));
// builder.Services.AddScoped(typeof(IEntityService<>), typeof(PlayerService<>));
builder.Services.AddScoped(typeof(IEntityService<>), typeof(EntityService<>));


// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();


// Test Database Connection
using (var scope = app.Services.CreateScope())
{
    var dbContext = scope.ServiceProvider.GetRequiredService<AppDbContext>();
    try
    {
        // Check if connection is successful
        if (await dbContext.Database.CanConnectAsync())
        {
            Console.WriteLine("Database connection successful!");
        }
        else
        {
            Console.WriteLine("Database connection failed.");
        }
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Error testing the database connection: {ex.Message}");
    }
}


// app.MapGet("/", () => "Welcome to the Player API!");


// Map controllers (this is where the PlayerController comes into play)
app.MapControllers();

app.Run();
