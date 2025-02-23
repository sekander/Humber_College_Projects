using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Passion_Project.Migrations
{
    /// <inheritdoc />
    public partial class AddImageUrlToCard : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Cards_Decks_DeckID",
                table: "Cards");

            migrationBuilder.DropIndex(
                name: "IX_Cards_DeckID",
                table: "Cards");

            migrationBuilder.DropColumn(
                name: "DeckID",
                table: "Cards");

            migrationBuilder.AddColumn<string>(
                name: "ImageUrl",
                table: "Cards",
                type: "longtext",
                nullable: true)
                .Annotation("MySql:CharSet", "utf8mb4");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "ImageUrl",
                table: "Cards");

            migrationBuilder.AddColumn<int>(
                name: "DeckID",
                table: "Cards",
                type: "int",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_Cards_DeckID",
                table: "Cards",
                column: "DeckID");

            migrationBuilder.AddForeignKey(
                name: "FK_Cards_Decks_DeckID",
                table: "Cards",
                column: "DeckID",
                principalTable: "Decks",
                principalColumn: "ID");
        }
    }
}
