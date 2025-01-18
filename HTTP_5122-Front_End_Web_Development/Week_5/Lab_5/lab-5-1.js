//#### LAB 5 - FUNCTIONS & OBJECTS ####
//PART 1:  I OBJECT!

const meObject = {
    name: "Nahid",
    height: 178,
    profession: "Programmer",
    hobby: "Enjoy playing games and making games",

    greet_user_func:function() {
        alert("Hi " + meObject.name + " i am a " + meObject.profession);
    }
};

console.log(meObject.hobby);
//alert("Hi " + meObject.name + " i am a " + meObject.profession);

meObject.greet_user_func();
