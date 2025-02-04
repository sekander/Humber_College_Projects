using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Passion_Project.Migrations
{
    /// <inheritdoc />
    public partial class CardMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Decks_Cards_CardID",
                table: "Decks");

            migrationBuilder.DropIndex(
                name: "IX_Decks_CardID",
                table: "Decks");

            migrationBuilder.DropColumn(
                name: "CardID",
                table: "Decks");

            migrationBuilder.CreateTable(
                name: "CardDeck",
                columns: table => new
                {
                    CardsID = table.Column<int>(type: "int", nullable: false),
                    DecksID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CardDeck", x => new { x.CardsID, x.DecksID });
                    table.ForeignKey(
                        name: "FK_CardDeck_Cards_CardsID",
                        column: x => x.CardsID,
                        principalTable: "Cards",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_CardDeck_Decks_DecksID",
                        column: x => x.DecksID,
                        principalTable: "Decks",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                })
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.CreateIndex(
                name: "IX_CardDeck_DecksID",
                table: "CardDeck",
                column: "DecksID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "CardDeck");

            migrationBuilder.AddColumn<int>(
                name: "CardID",
                table: "Decks",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.CreateIndex(
                name: "IX_Decks_CardID",
                table: "Decks",
                column: "CardID");

            migrationBuilder.AddForeignKey(
                name: "FK_Decks_Cards_CardID",
                table: "Decks",
                column: "CardID",
                principalTable: "Cards",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
