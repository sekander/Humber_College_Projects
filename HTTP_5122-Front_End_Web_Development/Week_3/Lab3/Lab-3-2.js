//LAB 3 - ARRAYS & LOOPS - PART 2


//TEAM MEMBER ARRAY
const ourTeam = ["Nahid", "Sonia", "Joyce", "Jared"]


console.log(ourTeam)
//OUTPUT TEAM ARRAY TO JS CONSOLE
for(var i = 0; i < ourTeam.length; i++)
{
    console.log("Team members : " + ourTeam[i])
}


console.log("REMOVING LAST MEMBER")
//REMOVE LAST MEMBER
ourTeam.pop();

console.log(ourTeam)
console.log("ADDING SEAN")
//ADD SEAN TO FRONT OF ARRAY
ourTeam.push("Sean")

console.log(ourTeam)

//REARRANGE THE ARRAY ALPHABETICALLY
ourTeam.sort()

console.log(ourTeam)

console.log("SORTING MEMBERS")
console.log("We have " + ourTeam.length + " people in our group.")
//OUTPUT REQUIRED MESSAGE TO JS CONSOLE
for(var i = 1; i < ourTeam.length + 1; i++)
{
    console.log("Team members : " + ourTeam[i - 1] + " is #" + i)
    
}


//LOOP THROUGH ARRAY TO OUTPUT TEAM MEMBERS/NUMBERS TO JS CONSOLE

// 9. A message on the console should say, “We have NUMBER people in our
// group.”, where NUMBER is a dynamic number that is the number of items
// in the ourTeam array.


// 10.Next, the console will display the names of the group members with each
// name on its own line. Beside each name should be " is # NUM." with the
// person's number for NUM. Remember: we want ‘1’ and not ‘0’ for the first
// person.
// Part 3: Shopping Cart (1