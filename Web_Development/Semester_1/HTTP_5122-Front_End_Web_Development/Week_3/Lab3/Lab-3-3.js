//LAB 3 - ARRAYS & LOOPS - PART 3



//PART 3 - SHOPPING CART SHIPPING
//==== VARIABLES ========
var shoppingCart = []
var userTotalItem = 0
const totalItems = 35

while(userTotalItem <= totalItems)
{
	var item = prompt("Enter the cost of the item")
	console.log("Value: ", (item))
	shoppingCart.push(item)
	userTotalItem += parseInt(item)
	console.log("Total : ", userTotalItem)
}
alert("Your shipping for this order will be free! Total: $" + userTotalItem )

var prices = '';
for (var i = 0; i < shoppingCart.length; i++)
{
	prices += shoppingCart[i] + " | "
}
console.log("Free Shipping Item prices: " + prices)

//==== LOGIC ========
//CHECK FOR ITEMS UNTIL THRESHOLD IS MET.

	//GET ITEM COST FROM USER
	
	
	//CONVERT USER INPUT TO A NUMBER
	
	
	//ADD ITEM COST TO RUNNING TOTAL VARIABLE
	
	
	//PUSH ITEM COST TO CART ARRAY
	
	
	


//SEND POPUP MESSAGE TO USER


//SEND OUTPUT TO CONSOLE

