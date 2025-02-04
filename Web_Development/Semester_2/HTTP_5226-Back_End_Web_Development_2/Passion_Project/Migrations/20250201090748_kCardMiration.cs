using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Passion_Project.Migrations
{
    /// <inheritdoc />
    public partial class kCardMiration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CardDeck_Cards_CardID",
                table: "CardDeck");

            migrationBuilder.DropForeignKey(
                name: "FK_CardDeck_Decks_DeckID",
                table: "CardDeck");

            migrationBuilder.DropPrimaryKey(
                name: "PK_CardDeck",
                table: "CardDeck");

            migrationBuilder.RenameTable(
                name: "CardDeck",
                newName: "CardDecks");

            migrationBuilder.RenameIndex(
                name: "IX_CardDeck_DeckID_CardID",
                table: "CardDecks",
                newName: "IX_CardDecks_DeckID_CardID");

            migrationBuilder.RenameIndex(
                name: "IX_CardDeck_CardID",
                table: "CardDecks",
                newName: "IX_CardDecks_CardID");

            migrationBuilder.AddColumn<int>(
                name: "DeckID",
                table: "Cards",
                type: "int",
                nullable: true);

            migrationBuilder.AddPrimaryKey(
                name: "PK_CardDecks",
                table: "CardDecks",
                columns: new[] { "DeckID", "CardID" });

            migrationBuilder.CreateIndex(
                name: "IX_Cards_DeckID",
                table: "Cards",
                column: "DeckID");

            migrationBuilder.AddForeignKey(
                name: "FK_CardDecks_Cards_CardID",
                table: "CardDecks",
                column: "CardID",
                principalTable: "Cards",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CardDecks_Decks_DeckID",
                table: "CardDecks",
                column: "DeckID",
                principalTable: "Decks",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Cards_Decks_DeckID",
                table: "Cards",
                column: "DeckID",
                principalTable: "Decks",
                principalColumn: "ID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CardDecks_Cards_CardID",
                table: "CardDecks");

            migrationBuilder.DropForeignKey(
                name: "FK_CardDecks_Decks_DeckID",
                table: "CardDecks");

            migrationBuilder.DropForeignKey(
                name: "FK_Cards_Decks_DeckID",
                table: "Cards");

            migrationBuilder.DropIndex(
                name: "IX_Cards_DeckID",
                table: "Cards");

            migrationBuilder.DropPrimaryKey(
                name: "PK_CardDecks",
                table: "CardDecks");

            migrationBuilder.DropColumn(
                name: "DeckID",
                table: "Cards");

            migrationBuilder.RenameTable(
                name: "CardDecks",
                newName: "CardDeck");

            migrationBuilder.RenameIndex(
                name: "IX_CardDecks_DeckID_CardID",
                table: "CardDeck",
                newName: "IX_CardDeck_DeckID_CardID");

            migrationBuilder.RenameIndex(
                name: "IX_CardDecks_CardID",
                table: "CardDeck",
                newName: "IX_CardDeck_CardID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_CardDeck",
                table: "CardDeck",
                columns: new[] { "DeckID", "CardID" });

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
    }
}
