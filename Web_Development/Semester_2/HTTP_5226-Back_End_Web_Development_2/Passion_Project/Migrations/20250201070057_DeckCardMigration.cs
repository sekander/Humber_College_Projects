using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Passion_Project.Migrations
{
    /// <inheritdoc />
    public partial class DeckCardMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CardDeck_Cards_CardsID",
                table: "CardDeck");

            migrationBuilder.DropForeignKey(
                name: "FK_CardDeck_Decks_DecksID",
                table: "CardDeck");

            migrationBuilder.RenameColumn(
                name: "DecksID",
                table: "CardDeck",
                newName: "CardID");

            migrationBuilder.RenameColumn(
                name: "CardsID",
                table: "CardDeck",
                newName: "DeckID");

            migrationBuilder.RenameIndex(
                name: "IX_CardDeck_DecksID",
                table: "CardDeck",
                newName: "IX_CardDeck_CardID");

            migrationBuilder.CreateIndex(
                name: "IX_CardDeck_DeckID_CardID",
                table: "CardDeck",
                columns: new[] { "DeckID", "CardID" },
                unique: true);

            migrationBuilder.AddForeignKey(
                name: "FK_CardDeck_Cards_CardID",
                table: "CardDeck",
                column: "CardID",
                principalTable: "Cards",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CardDeck_Decks_DeckID",
                table: "CardDeck",
                column: "DeckID",
                principalTable: "Decks",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CardDeck_Cards_CardID",
                table: "CardDeck");

            migrationBuilder.DropForeignKey(
                name: "FK_CardDeck_Decks_DeckID",
                table: "CardDeck");

            migrationBuilder.DropIndex(
                name: "IX_CardDeck_DeckID_CardID",
                table: "CardDeck");

            migrationBuilder.RenameColumn(
                name: "CardID",
                table: "CardDeck",
                newName: "DecksID");

            migrationBuilder.RenameColumn(
                name: "DeckID",
                table: "CardDeck",
                newName: "CardsID");

            migrationBuilder.RenameIndex(
                name: "IX_CardDeck_CardID",
                table: "CardDeck",
                newName: "IX_CardDeck_DecksID");

            migrationBuilder.AddForeignKey(
                name: "FK_CardDeck_Cards_CardsID",
                table: "CardDeck",
                column: "CardsID",
                principalTable: "Cards",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CardDeck_Decks_DecksID",
                table: "CardDeck",
                column: "DecksID",
                principalTable: "Decks",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
