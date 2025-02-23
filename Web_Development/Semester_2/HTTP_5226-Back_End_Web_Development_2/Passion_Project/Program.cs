using Microsoft.EntityFrameworkCore;
using Passion_Project.Data;
using Passion_Project.Interface;
using Passion_Project.Models;


var builder = WebApplication.CreateBuilder(args);

// Add services to the container
builder.Services.AddControllersWithViews(); // Adds support for controllers and views


// Add services to the container.
builder.Services.AddRazorPages();

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
app.UseStaticFiles();  // Enable static file serving

// Map controllers (MVC routing)
app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Login}/{action=Login}/{id?}");

// Map Razor Pages (Razor Pages routing)
app.MapRazorPages();  // This maps any Razor Pages in the Pages directory

app.UseRouting();  // Use routing for both MVC and Razor Pages

app.UseAuthorization();

//app.Run();
app.Run("http://0.0.0.0:5050");



/*

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddRazorPages();


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
// Set the default route to LoginController/Index
app.UseRouting();
// app.UseEndpoints(endpoints =>
// {
//     // Default route configuration
//     _ = endpoints.MapControllerRoute(
//         name: "default",
//         pattern: "{controller=Login}/{action=Login}/{id?}");
// });


// Map controllers (this is where the PlayerController comes into play)
app.MapControllers();


// Add controllers and views
builder.Services.AddControllersWithViews();

// Add services to the container.
builder.Services.AddRazorPages();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Error");
    app.UseHttpsRedirection();
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Login}/{action=Login}/{id?}");

app.MapRazorPages();


app.Run();
*/
