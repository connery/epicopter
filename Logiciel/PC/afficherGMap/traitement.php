<?php

$error = 0;


	if (isset($_POST['lat']) && !empty($_POST['lat']))
		$lat =$_POST['lat'];
	else
		$error = 1;
	if (isset($_POST['lng']) && !empty($_POST['lng']))
		$lng =$_POST['lng'];
	else
		$error = 1;
	if (isset($_POST['dist']) && !empty($_POST['dist']))
		$dist =$_POST['dist'];
	else
		$error = 1;
		
		
	$fp = fopen("test.txt","a");
	fputs($fp, "\n");
	fputs($fp, "lat = ".$lat."      lng = ".$lng."       dist = ".$dist);
	fclose($fp);



	if ($error == 0)
		echo "Succes<br />lat = ".$lat."<br />lng = ".$lng."<br />dist = ".$dist;
	else
		echo "error";
?>
