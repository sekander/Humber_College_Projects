using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Passion_Project.Migrations
{
    /// <inheritdoc />
    public partial class NewCardMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
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

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
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
        }
    }
}
