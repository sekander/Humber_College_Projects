using Microsoft.AspNetCore.Mvc;
using Passion_Project.Interface;
using Passion_Project.Models;
using System.Text.Json;



enum CardFilterType
{
    Legendary,
    Artifact, 
    Battle, 
    Creature, 
    Emblem, 
    Enchantment, 
    Instant, 
    Sorcery, 
    Token, 

    ColorRed,
    ColorBlue,
    ColorGreen,
    ColorWhite,
    ColorBlack,

    OneManaCost,
    TwoManaCost,
    ThreeManaCost,
    FourManaCost,
    FiveManaCost,
    SixPlusManaCost,
    
    PowerOne,
    PowerTwo,
    PowerThree,
    PowerFour,
    PowerFive,
    PowerSixPlus,
    
    ToughnessOne,
    ToughnessTwo,
    ToughnessThree,
    ToughnessFour,
    ToughnessFive,
    ToughnessSixPlus,

}

namespace Passion_Project.Controllers
{
        // This condition checks whether the controller has been initialized before. 
       
    // [Route("api/[controller]")]
    // [ApiController]
    [Route("login")]
    public class LoginController : Controller 
    {

        private readonly IEntityService<Player> _entityService;
        private static Player? player;
        private static string? deck_id;
        private static List<Deck> playerDeckList;
        private static List<Card> tempLegendaryCards = new List<Card>();
        private static List<Card> tempArtifactCards= new List<Card>();
        private static List<Card> tempBattleCards= new List<Card>();
        private static List<Card> tempCreatureCards= new List<Card>();
        private static List<Card> tempEmblemCards= new List<Card>();
        private static List<Card> tempEnchantmentCards= new List<Card>();
        private static List<Card> tempInstantCards= new List<Card>();
        private static List<Card> tempSorceryCards= new List<Card>();
        private static List<Card> tempTokenCards= new List<Card>();


        private static List<Card> tempREDCards= new List<Card>();
        private static List<Card> tempBLUECards= new List<Card>();
        private static List<Card> tempGREENCards= new List<Card>();
        private static List<Card> tempWHITECards= new List<Card>();
        private static List<Card> tempBLACKCards= new List<Card>();


        private static List<Card> tempOneManaCards= new List<Card>();
        private static List<Card> tempTwoManaCards= new List<Card>();
        private static List<Card> tempThreeManaCards= new List<Card>();
        private static List<Card> tempFourManaCards= new List<Card>();
        private static List<Card> tempFiveManaCards= new List<Card>();
        private static List<Card> tempSixPlusManaCards= new List<Card>();


        private static List<Card> tempOnePowerCards= new List<Card>();
        private static List<Card> tempTwoPowerCards= new List<Card>();
        private static List<Card> tempThreePowerCards= new List<Card>();
        private static List<Card> tempFourPowerCards= new List<Card>();
        private static List<Card> tempFivePowerCards= new List<Card>();
        private static List<Card> tempSixPlusPowerCards= new List<Card>();

        private static List<Card> tempOneToughnessCards= new List<Card>();
        private static List<Card> tempTwoToughnessCards= new List<Card>();
        private static List<Card> tempThreeToughnessCards= new List<Card>();
        private static List<Card> tempFourToughnessCards= new List<Card>();
        private static List<Card> tempFivToughnesseCards= new List<Card>();
        private static List<Card> tempSixPlusToughnessCards= new List<Card>();

        public LoginController(IEntityService<Player> entityService)
        {
            _entityService = entityService;
        }

        // Action method to render the Index view
        [HttpGet("")]
        public IActionResult Login()
        {
            Console.WriteLine("LOGICN");
            return View("/Views/MTG_Deck_Builder/Login.cshtml"); // This will look for Views/Home/Index.cshtml
        }

        // Action method to handle the form POST request (POST request)
        // [HttpPost]
        [HttpPost("")]
        public IActionResult Login(string username, string email)
        {
            Console.WriteLine("Testing " + username + " " + email);
            // var players = _entityService.GetPlayers();
            var players = _entityService.GetPlayers();
            var matchedPlayer =  players.FirstOrDefault(player => player.Name == username && player.Email == email);
             // Check if a match was found
            if (matchedPlayer != null)
            {
                // playerFound = true;
                Console.WriteLine("Player found: " + matchedPlayer.Name + ", " + matchedPlayer.Email + ", " + matchedPlayer.ID);
                // string matchedPlayerJson = JsonConvert.SerializeObject(matchedPlayer);
                string json = JsonSerializer.Serialize(matchedPlayer);
                // Pass the JSON to the view
                ViewData["mtg_player"] = json;

                //Save player in cache
                player = matchedPlayer;


                // Set a success message
                // ViewData["Message"] = "User found!";
                return View("/Views/MTG_Deck_Builder/Player.cshtml"); // Re-render the login page with error message
            }
            else
            {
                // Set an error message
                ViewBag.ErrorMessage = "User not found. Please check your username and email.";
                return View("/Views/MTG_Deck_Builder/Login.cshtml"); // Re-render the login page with error message
            }
        }

        [HttpGet("/PlayerView")]
        public IActionResult PlayerView()
        {
            if(player != null){
                string json = JsonSerializer.Serialize(player);
                // Pass the JSON to the view
                ViewData["mtg_player"] = json;
                
                return View("/Views/MTG_Deck_Builder/Player.cshtml"); // Re-render the login page with error message
            }
            else{
                ViewBag.ErrorMessage = "User is not logged in. Please login.";
                return View("/Views/MTG_Deck_Builder/Login.cshtml"); // Re-render the login page with error message
                // return BadRequest("Player is not logged. Please Login");
            }
                // return BadRequest("Player is not logged. Please Login");
        }

        [HttpGet("/DeckView")]
        public IActionResult DeckView(string subtitle){
            Console.WriteLine("Checking: " + subtitle);
            ViewData["DeckID"] = subtitle;
            deck_id = subtitle;
            // return View("/Views/MTG_Deck_Builder/Player.cshtml"); // Re-render the login page with error message
            return View("/Views/MTG_Deck_Builder/Deck.cshtml"); // Re-render the login page with error message
        }
        
        [HttpGet("/CardView")]
        public IActionResult CardView(){
            Console.WriteLine("Card View  "  );
            // ViewData["DeckID"] = subtitle;
            // return View("/Views/MTG_Deck_Builder/Player.cshtml"); // Re-render the login page with error message
            if(player != null)
            {
                ViewData["PlayerID"] = player.ID.ToString();
                ViewData["PlayerName"] = player.Name.ToString();
            }
            string json = JsonSerializer.Serialize(playerDeckList);
            ViewData["PlayerDecks"] = json;
            return View("/Views/MTG_Deck_Builder/Card.cshtml"); // Re-render the login page with error message
        }

        //Create search feature 
        //in player deck view create side panel showing full list of cards
        //Features - Show deck stats | Filter all cards by any parameters 

        [HttpGet("/get-decks")]
        public IActionResult GetPlayerDecks()
        {
            playerDeckList = new List<Deck>();
            var decks = _entityService.GetDecks();
            if (decks == null)
            {
                Console.WriteLine("Error: Decks list is null");
                return BadRequest("No decks available.");
            }
    
            // Ensure that player is not null
            if (player == null)
            {
                Console.WriteLine("Error: Player is null");
                return BadRequest("Player information is missing.");
            }

            foreach (var deck in decks)
            {
                if(deck.PlayerID == player.ID)
                    playerDeckList.Add(deck);
            }

            foreach (var item in playerDeckList)
            {
                Console.WriteLine("Deck Names : " + item.Name);
                
            }

            string json = JsonSerializer.Serialize(playerDeckList);


            return Ok(json);
        }

        [HttpGet("/get-range")]
        public IActionResult GetRangeOfCards([FromQuery] uint startID, [FromQuery] uint endID)
        {
            Console.WriteLine("Get-Range: " + startID + " - " + endID);
            var cards = _entityService.GetCards();
            var rangeOfCards = cards.Where(card => card.ID >= startID && card.ID <= endID).ToList();
            string json = JsonSerializer.Serialize(rangeOfCards);

            return Ok(json);
        }

        [HttpGet("/filter-card")]
        public IActionResult FilterCards([FromQuery] string filterType)
        {
            if (Enum.TryParse<CardFilterType>(filterType, out var filterTypeEnum))
            {
                Console.WriteLine("Get-Type: " + filterTypeEnum);
                var cards = _entityService.GetCards();
                List<Card> matchingCards = new List<Card>();

                switch (filterTypeEnum)
                {
                    case CardFilterType.Legendary:
                        if(tempArtifactCards.Count > 0 && tempCreatureCards.Count > 0 && tempTokenCards.Count > 0)
                        {}
                        else if(tempArtifactCards.Count > 0  && tempTokenCards.Count > 0)
                        {}
                        else if(tempCreatureCards.Count > 0  && tempTokenCards.Count > 0)
                        {}
                        else if(tempEnchantmentCards.Count > 0  && tempTokenCards.Count > 0)
                        {}
                        else if(tempArtifactCards.Count > 0)
                        {
                            Console.WriteLine("Filtering by Legendary Artifact");
                            matchingCards = tempArtifactCards.Where(c => c.TypeLine.Contains("Legendary")).ToList();
                            // tempLegendaryCards = matchingCards;
                        }
                        else if(tempCreatureCards.Count > 0)
                        {}
                        else if(tempEnchantmentCards.Count > 0)
                        {}
                        else if(tempInstantCards.Count > 0)
                        {}
                        else if(tempSorceryCards.Count > 0)
                        {}
                        else{
                            Console.WriteLine("Filtering by Legendary");
                            matchingCards = cards.Where(c => c.TypeLine.Contains("Legendary")).ToList();
                            tempLegendaryCards = matchingCards;
                        }
                            Console.WriteLine("Filtering by Legendary");
                            matchingCards = cards.Where(c => c.TypeLine.Contains("Legendary")).ToList();
                            tempLegendaryCards = matchingCards;
                        break;
                    case CardFilterType.Artifact:
                        if(tempTokenCards.Count > 0 && tempLegendaryCards.Count > 0 && tempEnchantmentCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempLegendaryCards.Count > 0 && tempCreatureCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempEnchantmentCards.Count > 0 && tempCreatureCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempLegendaryCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempSorceryCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempInstantCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempEnchantmentCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0 && tempCreatureCards.Count > 0)
                        {}
                        else if(tempTokenCards.Count > 0)
                        {}
                        else if(tempLegendaryCards.Count > 0)
                        {}
                        else if(tempSorceryCards.Count > 0)
                        {}
                        else if(tempInstantCards.Count > 0)
                        {}
                        else if(tempEnchantmentCards.Count > 0)
                        {}
                        else
                        {}

                        Console.WriteLine("Filtering by Artifact");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Artifact")).ToList();
                        tempArtifactCards = matchingCards;
                        break;
                    case CardFilterType.Battle:
                        Console.WriteLine("Filtering by Battle");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Battle")).ToList();
                        tempBattleCards = matchingCards;
                        break;
                    case CardFilterType.Creature:
                        Console.WriteLine("Filtering by Creature");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Creature")).ToList();
                        tempCreatureCards = matchingCards;
                        break;
                    case CardFilterType.Emblem:
                        Console.WriteLine("Filtering by Emblem");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Emblem")).ToList();
                        tempEmblemCards = matchingCards;
                        break;
                    case CardFilterType.Enchantment:
                        Console.WriteLine("Filtering by Enchantment");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Enchantment")).ToList();
                        tempEnchantmentCards = matchingCards;
                        
                        break;
                    case CardFilterType.Instant:
                        Console.WriteLine("Filtering by Instant");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Instant")).ToList();
                        tempInstantCards = matchingCards;
                        break;
                    case CardFilterType.Sorcery:
                        Console.WriteLine("Filtering by Sorcery");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Sorcery")).ToList();
                        tempSorceryCards = matchingCards;
                        break;
                    case CardFilterType.Token:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.TypeLine.Contains("Token")).ToList();
                        tempTokenCards = matchingCards;
                        break;
                    case CardFilterType.ColorRed:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Colors.Contains("R")).ToList();

                        tempREDCards = matchingCards;
                        break;
                    case CardFilterType.ColorBlue:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Colors.Contains("U")).ToList();

                        tempBLUECards = matchingCards;
                        break;
                    case CardFilterType.ColorGreen:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Colors.Contains("G")).ToList();

                        tempGREENCards = matchingCards;
                        break;
                    case CardFilterType.ColorBlack:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Colors.Contains("B")).ToList();

                        tempBLACKCards = matchingCards;
                        break;
                    case CardFilterType.ColorWhite:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Colors.Contains("W")).ToList();

                        tempWHITECards = matchingCards;
                        break;
                    case CardFilterType.OneManaCost:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.ManaCost.Contains("1")).ToList();

                        tempOneManaCards = matchingCards;
                        break;
                    case CardFilterType.TwoManaCost:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.ManaCost.Contains("2")).ToList();

                        tempTwoManaCards = matchingCards;
                        break;
                    case CardFilterType.ThreeManaCost:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.ManaCost.Contains("3")).ToList();

                        tempThreeManaCards = matchingCards;
                        break;
                    case CardFilterType.FourManaCost:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.ManaCost.Contains("4")).ToList();

                        tempFourManaCards = matchingCards;
                        break;
                    case CardFilterType.FiveManaCost:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.ManaCost.Contains("5")).ToList();

                        tempFiveManaCards = matchingCards;
                        break;
                    case CardFilterType.SixPlusManaCost:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.ManaCost.Contains("6")).ToList();

                        tempSixPlusManaCards = matchingCards;
                        break;
                    case CardFilterType.PowerOne:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Power.Contains("1")).ToList();

                        tempOnePowerCards= matchingCards;
                        break;
                    case CardFilterType.PowerTwo:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Power.Contains("2")).ToList();

                        tempTwoPowerCards= matchingCards;
                        break;
                    case CardFilterType.PowerThree: 
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Power.Contains("3")).ToList();

                        tempThreePowerCards= matchingCards;
                        break;
                    case CardFilterType.PowerFour:  
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Power.Contains("4")).ToList();

                        tempFourPowerCards= matchingCards;
                        break;
                    case CardFilterType.PowerFive:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Power.Contains("5")).ToList();

                        tempFivePowerCards= matchingCards;
                        break;
                    case CardFilterType.PowerSixPlus:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Power.Contains("6")).ToList();

                        tempSixPlusPowerCards= matchingCards;
                        break;
                    case CardFilterType.ToughnessOne:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Toughness.Contains("1")).ToList();

                        tempOneToughnessCards= matchingCards;
                        break;
                    case CardFilterType.ToughnessTwo:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Toughness.Contains("2")).ToList();

                        tempTwoToughnessCards= matchingCards;
                        break;
                    case CardFilterType.ToughnessThree:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Toughness.Contains("3")).ToList();

                        tempThreeToughnessCards= matchingCards;
                        break;
                    case CardFilterType.ToughnessFour:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Toughness.Contains("4")).ToList();

                        tempFourToughnessCards= matchingCards;
                        break;
                    case CardFilterType.ToughnessFive:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Toughness.Contains("5")).ToList();

                        tempFivToughnesseCards= matchingCards;
                        break;
                    case CardFilterType.ToughnessSixPlus:
                        Console.WriteLine("Filtering by Token");
                        matchingCards = cards.Where(c => c.Toughness.Contains("6")).ToList();

                        tempSixPlusToughnessCards= matchingCards;
                        break;
                    default:
                        return BadRequest("Invalid filter type.");
                }


                // Serialize the filtered results to JSON
                string json = JsonSerializer.Serialize(matchingCards);

                // Return the results as an OK response with the matching cards
                return Ok(json);
            }
            else
            {
                return BadRequest("Invalid filter type.");
            }
        }

        [HttpGet("/get-card-name")]
        public IActionResult GetRangeOfCards([FromQuery] string nameStartsWith)
        {
            Console.WriteLine("Get-Range: " + nameStartsWith);
            // if(nameStartsWith.Length > 4)
            // {
                if (tempArtifactCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempArtifactCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempLegendaryCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempLegendaryCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempCreatureCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempCreatureCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempBattleCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempBattleCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempEmblemCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempEmblemCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempEnchantmentCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempEnchantmentCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempInstantCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempInstantCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempSorceryCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempSorceryCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempTokenCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempTokenCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempREDCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempREDCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempBLUECards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempBLUECards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempGREENCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempGREENCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempWHITECards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempWHITECards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempBLACKCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempBLACKCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempOneManaCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempOneManaCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempTwoManaCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempTwoManaCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempThreeManaCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempThreeManaCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempFourManaCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempFourManaCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempFiveManaCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempFiveManaCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempSixPlusManaCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempSixPlusManaCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempOnePowerCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempOnePowerCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempTwoPowerCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempTwoPowerCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempThreePowerCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempThreePowerCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempFourPowerCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempFourPowerCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to JSON
                    string json = JsonSerializer.Serialize(matchingCards);

                    // Return the results as an OK response with the matching cards
                    return Ok(json);
                }
                else if (tempFivePowerCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempFivePowerCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);
                }
                else if (tempSixPlusPowerCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempSixPlusPowerCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);
                }
                else if (tempOneToughnessCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempOneToughnessCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);
                }
                else if (tempTwoToughnessCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempTwoToughnessCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);
                }
                else if (tempThreeToughnessCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempThreeToughnessCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);
                }
                else if (tempFourToughnessCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var
                    cards = tempFourToughnessCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();  
                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);

                }
                else if (tempFivToughnesseCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempFivToughnesseCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();  
                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);

                }
                else if (tempSixPlusToughnessCards.Count > 0)
                {
                    Console.WriteLine("Get-Range: " + nameStartsWith);
                    var cards = tempSixPlusToughnessCards;
                    // Filter the cards where the name starts with the provided 'nameStartsWith' value
                    var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                    // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();  
                    // Serialize the filtered results to
                    string json = JsonSerializer.Serialize(matchingCards);
                    return Ok(json);

                }
                else
                {
                    if(nameStartsWith.Length > 4){
                        // Assuming _entityService.GetCards() fetches all cards from the database
                        var cards = _entityService.GetCards();

                        // Filter the cards where the name starts with the provided 'nameStartsWith' value
                        var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
                        // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

                        // Serialize the filtered results to JSON
                        string json = JsonSerializer.Serialize(matchingCards);

                        // Return the results as an OK response with the matching cards
                        return Ok(json);
                    }
                    else{
                        return BadRequest("Please enter a valid search term.");
                    }
                }
            // }
            // if(nameStartsWith.Length > 4)
            // {
            //     // Assuming _entityService.GetCards() fetches all cards from the database
            //     var cards = _entityService.GetCards();

            //     // Filter the cards where the name starts with the provided 'nameStartsWith' value
            //     var matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();
            //     // matchingCards = cards.Where(card => card.Name.StartsWith(nameStartsWith)).ToList();

            //     // Serialize the filtered results to JSON
            //     string json = JsonSerializer.Serialize(matchingCards);

            //     // Return the results as an OK response with the matching cards
            //     return Ok(json);
            // }
            // else{
            //     return BadRequest("Please enter a valid search term.");
            // }
        }
        
        // [HttpGet("/clear-card-filter")]
        // public IActionResult ClearFilter()
        // {
        //     tempLegendaryCards.Clear();
        //     tempArtifactCards.Clear();
        //     tempBattleCards.Clear();
        //     tempCreatureCards.Clear();
        //     tempEmblemCards.Clear();
        //     tempEnchantmentCards.Clear();
        //     tempInstantCards.Clear();
        //     tempSorceryCards.Clear();
        //     tempTokenCards.Clear();
        //     return Ok("Filter cleared.");
        // }

        [HttpGet("/clear-card-filter")]
        public IActionResult ClearFilter([FromQuery] string? filterType = null)
        {
            if (string.IsNullOrEmpty(filterType) || filterType.Equals("all", StringComparison.OrdinalIgnoreCase))
            {
                tempLegendaryCards.Clear();
                tempArtifactCards.Clear();
                tempBattleCards.Clear();
                tempCreatureCards.Clear();
                tempEmblemCards.Clear();
                tempEnchantmentCards.Clear();
                tempInstantCards.Clear();
                tempSorceryCards.Clear();
                tempTokenCards.Clear();
                tempREDCards.Clear();
                tempBLUECards.Clear();
                tempGREENCards.Clear();
                tempWHITECards.Clear();
                tempBLACKCards.Clear();
                tempOneManaCards.Clear();
                tempTwoManaCards.Clear();
                tempThreeManaCards.Clear();
                tempFourManaCards.Clear();
                tempFiveManaCards.Clear();
                tempSixPlusManaCards.Clear();
                tempOnePowerCards.Clear();
                tempTwoPowerCards.Clear();
                tempThreePowerCards.Clear();
                tempFourPowerCards.Clear();
                tempFivePowerCards.Clear();
                tempSixPlusPowerCards.Clear();
                tempOneToughnessCards.Clear();
                tempTwoToughnessCards.Clear();
                tempThreeToughnessCards.Clear();
                tempFourToughnessCards.Clear();
                tempFivToughnesseCards.Clear();
                tempSixPlusToughnessCards.Clear();
                return Ok("All filters cleared.");
            }

            switch (filterType.ToLower())
            {
                case "0":
                    Console.WriteLine("Clearing Legendary filter");
                    tempLegendaryCards.Clear();
                    break;
                case "1":
                    Console.WriteLine("Clearing Artifact filter");
                    tempArtifactCards.Clear();
                    break;
                case "2":
                    Console.WriteLine("Clearing Battle filter");
                    tempBattleCards.Clear();
                    break;
                case "3":
                    Console.WriteLine("Clearing Creature filter");
                    tempCreatureCards.Clear();
                    break;
                case "4":
                    Console.WriteLine("Clearing Creature filter");
                    tempEmblemCards.Clear();
                    break;
                case "5":
                    Console.WriteLine("Clearing Enchantment filter");
                    tempEnchantmentCards.Clear();
                    break;
                case "6":
                    Console.WriteLine("Clearing Instant filter");
                    tempInstantCards.Clear();
                    break;
                case "7":
                    Console.WriteLine("Clearing Sorcery filter");
                    tempSorceryCards.Clear();
                    break;
                case "8":
                    Console.WriteLine("Clearing Token filter");
                    tempTokenCards.Clear();
                    break;
                case "9":
                    Console.WriteLine("Clearing Red filter");
                    tempREDCards.Clear();
                    break;
                case "10":
                    Console.WriteLine("Clearing Blue filter");
                    tempBLUECards.Clear();
                    break;
                case "11":
                    Console.WriteLine("Clearing Green filter");
                    tempGREENCards.Clear();
                    break;
                case "12":
                    Console.WriteLine("Clearing White filter");
                    tempWHITECards.Clear();
                    break;
                case "13":
                    Console.WriteLine("Clearing Black filter");
                    tempBLACKCards.Clear();
                    break;
                case "14":
                    Console.WriteLine("Clearing Black filter");
                    tempOneManaCards.Clear();
                    break;
                case "15":
                    Console.WriteLine("Clearing Black filter");
                    tempTwoManaCards.Clear();
                    break;
                case "16":
                    Console.WriteLine("Clearing Black filter");
                    tempThreeManaCards.Clear();
                    break;
                case "17":
                    Console.WriteLine("Clearing Black filter");
                    tempFourManaCards.Clear();
                    break;
                case "18":
                    Console.WriteLine("Clearing Black filter");
                    tempFiveManaCards.Clear();
                    break;
                case "19":
                    Console.WriteLine("Clearing Black filter");
                    tempSixPlusManaCards.Clear();
                    break;
                case "20":
                    Console.WriteLine("Clearing Black filter");
                    tempOnePowerCards.Clear();
                    break;
                case "21":
                    Console.WriteLine("Clearing Black filter");
                    tempTwoPowerCards.Clear();
                    break;
                case "22":
                    Console.WriteLine("Clearing Black filter");
                    tempThreePowerCards.Clear();
                    break;
                case "23":
                    Console.WriteLine("Clearing Black filter");
                    tempFourPowerCards.Clear();
                    break;
                case "24":
                    Console.WriteLine("Clearing Black filter");
                    tempFivePowerCards.Clear();
                    break;
                case "25":
                    Console.WriteLine("Clearing Black filter");
                    tempSixPlusPowerCards.Clear();
                    break;
                case "26":
                    Console.WriteLine("Clearing Black filter");
                    tempOneToughnessCards.Clear();
                    break;
                case "27":
                    Console.WriteLine("Clearing Black filter");
                    tempTwoToughnessCards.Clear();
                    break;
                case "28":
                    Console.WriteLine("Clearing Black filter");
                    tempThreeToughnessCards.Clear();
                    break;
                case "29":
                    Console.WriteLine("Clearing Black filter");
                    tempFourToughnessCards.Clear();
                    break;
                case "30":
                    Console.WriteLine("Clearing Black filter");
                    tempFivToughnesseCards.Clear();
                    break;
                case "31":
                    Console.WriteLine("Clearing Black filter");
                    tempSixPlusToughnessCards.Clear();
                    break;
                default:
                    return BadRequest("Invalid filter type.");
            }

            return Ok($"{filterType} filter cleared.");
        }
    }
}
