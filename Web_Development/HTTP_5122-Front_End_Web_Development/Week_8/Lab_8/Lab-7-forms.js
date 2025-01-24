/* LAB 7 - SHIPPING FORM */

window.onload = function () {

    //Order Shipping object (for extra EXTRA challenge, otherwise, ignore it)
    var shipInfo = {
        cid: 0,
        name: "",
        pc: "",
        speed: "",
        cost: 0
    };

    ///shipInfo customer;

    var formHandle = document.forms.form_ship;


    formHandle.onsubmit = processForm;

    function processForm() {

        var name = formHandle.f_Name;
        var postal = formHandle.f_pc;
        var speed = formHandle.f_speed;

        console.log(speed.value);


        const selectElement = document.getElementById("in_Speed");
        const thankMsg = document.getElementById("thanks_msg");
        const thankUser = document.getElementById("thanksCustomer");
        const userSpeed = document.getElementById("thanksSpeed");
        const thankCost = document.getElementById("thanksCost");
        const userPostal = document.getElementById("thanksPC");

        var selectedItem = selectElement.options[selectElement.selectedIndex].text
        console.log(selectedItem);

        if (speed.value == 0) {
            speed.style.background = "red";
            speed.focus();
            return false;

        }
        else if (name.value === "") {
            console.log("TESST");
            name.style.background = "red";
            name.focus();
            return false;
        }
        else if (postal.value === "") {
            //console.log("TESST");
            postal.style.background = "red";
            postal.focus();
            return false;
        }
        else {

            formHandle.style.display = "none";
            thankMsg.style.display = "block";

            shipInfo.name = name.value;
            //thankUser.textContent = name.value;
            thankUser.textContent = shipInfo.name;
            shipInfo.pc = postal.value;
            //userPostal.textContent = postal.value;
            userPostal.textContent = shipInfo.pc;
            //userSpeed.textContent = selectedOption;
            //var selectedOptionText = selectElement.options[selectElement.selectedIndex].text;

            //userSpeed.textContent = selectElement;
            shipInfo.speed = selectedItem;
            //userSpeed.textContent = selectedItem;
            userSpeed.textContent = shipInfo.speed;


            userSpeed.cost = speed.value;
            //thankCost.textContent = speed.value;
            thankCost.textContent = userSpeed.cost;

        }




        return false;

    }


}



