// Import for live server
import Module from './module.js';

// Import for Node.js
// const Module = require('./module.js');

// Create an instance of the module
const moduleInstance = Module();

// Initialize a flag to manage execution state
let blockCode = false;

// Function to execute the code logic
// async is used to make the function asynchronous
// allowing the function to use awiat inside the function 
// enabling it to wait for asynchronous tasks 
async function executeCode() {
    if (!blockCode) {
        // Part 1: Adding items to the module
        console.log("PART 1");
        console.log("-----------------------");
        console.log("Adding items to module instance");
        moduleInstance.addItem("Apple");
        moduleInstance.addItem("Banana");
        moduleInstance.addItem("Orange");

        console.log("Utilizing module instance public getItemCount()");
        console.log("Item count: " + moduleInstance.getItemCount());

        // Set the flag to true for the next execution
        blockCode = true;
    } else {
        // Part 2: Simulating blocking and asynchronous behaviour
        console.log("\nPART 2");
        console.log("-----------------------");

        // Message before blocking operation
        console.log("Blocking call sleeping  : (Line 38)");

        // Simulate blocking operation
        // await is used to cause the function to pause/block until the 
        // sleep promise is resolved 
        await sleep(2000);

        // Message after blocking operation
        console.log("This is executed after the blocking code but before the setTimeout calls : (Line 46)");

        // Example of NON-BLOCKING CODE:
        // The following setTimeout schedules tasks to be executed later.
        setTimeout(() => {
            console.log("This is executed asynchronously (setTimeout with 0ms delay) : (Line 51) ");
        }, 0);

        setTimeout(() => {
            console.log("This will execute after 1 second but does not block the code: (Line 55)");
        }, 1000);

        console.log("This is executed immediately within the main thread after scheduling timeouts: (Line 58)");
    }
}

// Helper function for asynchronous sleep
// The sleep function is typically a custom function that returns a Promise which 
// resolves after a specified time delay. It can simulate a pause in the program, 
// much like a "blocking" operation.
function sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
}

// Main execution sequence
(async function main() {
    // Execute Part 1 first
    await executeCode();

    // Execute Part 2 after Part 1 completes
    await executeCode();
})();

