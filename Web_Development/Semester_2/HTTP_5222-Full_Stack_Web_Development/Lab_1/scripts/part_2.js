  // Part 2: Simulating blocking and asynchronous behaviour
        console.log("\nPART 2");
        console.log("-----------------------");

        // Message before blocking operation
        console.log("Starting blocking call using while loop for 2 seconds : (Line 41)");

        // This while loop blocks the execution of the script for 2 seconds.
        // During this time, no other code can run, including asynchronous tasks.
        // It continuously checks the time in a busy-wait loop.
        const delay = Date.now() + 2000;
        while (Date.now() < delay) {
            // Busy-wait (blocks the script)
        }

        // Message after blocking operation
        // This line executes only after the while loop finishes (i.e., after 2 seconds).
        console.log("This is executed after the blocking code but before the setTimeout calls : (Line 53)");

        // Example of NON-BLOCKING CODE:
        // The following setTimeout schedules tasks to be executed later.
        // They are asynchronous, meaning they won't block the main thread.
        // Instead, they will execute after their specified delay.
        setTimeout(() => {
            // This task is scheduled to execute immediately after the blocking code ends.
            console.log("This is executed asynchronously (setTimeout with 0ms delay) : (Line 61) ");
        }, 0);

        setTimeout(() => {
            // This task is scheduled to execute 1 second after the blocking code ends.
            console.log("This will execute after 1 second but does not block the code: (Line 66)");
        }, 1000);

        // Message immediately after scheduling timeouts
        // This line executes immediately after scheduling the asynchronous tasks, 
        // even before the timeouts are triggered.
        console.log("This is executed immediately within the main thread after scheduling timeouts: (Line 72)");

