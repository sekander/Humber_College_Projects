<?php
  $connect = mysqli_connect('************', '****', '******', '*********');
  
  if(!$connect){
    die("Connection Failed: " . mysqli_connect_error());
  }
