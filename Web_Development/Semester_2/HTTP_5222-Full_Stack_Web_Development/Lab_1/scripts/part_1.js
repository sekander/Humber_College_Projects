// Lab_1
// HTTP-5222
// Nahid Sekander
// n01001831

// Import for live server
import Module from './module.js';

// Import for Node.js
// const Module = require('./module.js');

// Create an instance of the module
const moduleInstance = Module();


       // Part 1: Adding items to the module
        console.log("PART 1");
        console.log("-----------------------");
        console.log("Adding items to module instance");
        moduleInstance.addItem("Apple");
        moduleInstance.addItem("Banana");
        moduleInstance.addItem("Orange");

        console.log("Utilizing module instance public getItemCount()");
        console.log("Item count: " + moduleInstance.getItemCount());

