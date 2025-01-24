//#### LAB 5 - FUNCTIONS & OBJECTS ####
//PART 2:  MAKE THE BANK
//1. Create the object structure first.
const bankCustomer = {
    //2. Add the required properties to your object.
    lastName: "Sekander",
    branchNumber: 22056,
    accountBalance: 100000.00,
    interestRate: 0.03,
    multipleAccounts: false,

    //3. Add your first method and test it. Remember, the methods will change the properties of the object.
    makeDepost: function (amount) {
        this.accountBalance += amount;
        return "Thank you, your current balance is now $" + (this.accountBalance.toFixed(2))
    },
    //4. Add your second method and test it.
    makeWithdrawl: function (amount) {
        this.accountBalance -= amount;
        return "Thank you, your current balance is now $" + (this.accountBalance.toFixed(2))
    },

    //Stretch goal 
    addInterest: function () {
        if (this.multipleAccounts) {
            // this.accountBalance += this.accountBalance*(this.interestRate + 0.005)
            var accumulatedInterest = this.accountBalance * (this.interestRate + 0.005)
            this.accountBalance = this.accountBalance + accumulatedInterest;
        }
        else {
            //this.accountBalance += this.accountBalance*this.interestRate
            var accumulatedInterest = this.accountBalance * (this.interestRate)
            this.accountBalance = this.accountBalance + accumulatedInterest;
        }
        return "Thank you, your current balance is now $" + (this.accountBalance.toFixed(2))
    }
};
//5. Create the required output to complete steps 6-10 of the lab.
console.log("Starting Balance $" + bankCustomer.accountBalance.toFixed(2));
console.log(bankCustomer.makeDepost(200));
console.log(bankCustomer.addInterest());
console.log("New Balance $" + bankCustomer.accountBalance.toFixed(2));
console.log(bankCustomer.makeWithdrawl(75));
console.log(bankCustomer.addInterest());
console.log("New Balance $" + bankCustomer.accountBalance.toFixed(2));


console.log("\nMULTIPLE ACCOUNTS TRUE\n");
//6. Once everything is working, tackle the Stretch Goal!
bankCustomer.accountBalance = 100000.00;
bankCustomer.multipleAccounts = true;
console.log("Starting Balance $" + bankCustomer.accountBalance.toFixed(2));
console.log(bankCustomer.makeDepost(200));
console.log(bankCustomer.addInterest());
console.log("New Balance $" + bankCustomer.accountBalance.toFixed(2));
console.log(bankCustomer.makeWithdrawl(75));
console.log(bankCustomer.addInterest());
console.log("New Balance $" + bankCustomer.accountBalance.toFixed(2));

