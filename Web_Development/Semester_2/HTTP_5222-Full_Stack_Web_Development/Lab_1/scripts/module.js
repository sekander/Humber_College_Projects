// module.js
// Lab_1
// HTTP-5222
// Nahid Sekander
// n01001831

const Module = (() => {
    
    //private array for module 
    let module_list = [];

    function addItem(element) {
        module_list.push(element);
    }

    function getItemCount() {
        return module_list.length;
    }

    //Return public members
    return {
        addItem,
        getItemCount
    };
});

//Export Syntax for node
//module.exports = Module;
//Export Syntax for live server 
export default Module;
