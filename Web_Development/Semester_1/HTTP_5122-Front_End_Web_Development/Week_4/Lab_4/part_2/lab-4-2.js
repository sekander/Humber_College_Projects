//#### LAB 4 - FUNCTIONS ####
//PART 2:  AN AVERAGE FUNCTION


//################## CREATE YOUR AVERAGE FUNCTION
//This function takes five numbers and returns their average to one decimal place.
function averageCalc(one, two, three, four, five)
{
    var sum = one + two + three + four + five;
    return (sum/5).toFixed(1)
    //return (sum/5)

}


//################## LOGIC THAT OUTPUTS MESSAGES BASED ON FUNCTION RESULTS
console.log(averageCalc(5, 10, 15, 20, 25))

var grade1 = 100;
var grade2 = 100;
var grade3 = 100;
var grade4 = 100;
var grade5 = 100;

if (averageCalc(grade1, grade2, grade3, grade4, grade5) > 70)
    alert("Above Average ")
else
    alert("Needs Improvement")