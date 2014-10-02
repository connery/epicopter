<?php

	$q = intval($_GET['q']);

	$con = mysqli_connect('mysql51-104.perso','talatriqbdd','epicopter88','talatriqbdd');
	if (!$con) 
	{
		die('Could not connect: ' . mysqli_error($con));
	}

	mysqli_select_db($con,"ajax_demo");
	$sql="SELECT * FROM Points WHERE u_id="+$q;
	$result = mysqli_query($con,$sql);

	$val = "<TABLE BORDER=\"1\">";
	$val =$val."<CAPTION> Table des points </CAPTION>";
	$val =$val."<TR>";
		$val =$val."<TH>  Numero      </TH>";
		$val =$val."<TH>  Latitude  </TH>";
		$val =$val."<TH>  Longitude </TH>";
		$val =$val."<TH>  Distance </TH>";
		$val =$val."<TH>  Hauteur   </TH>";
	$val =$val."</TR> ";
	$points = 0;
	while($row = mysqli_fetch_array($result))
	{
		$val =$val."<TR>" ;
			$val =$val."<TH>" . $points++ . "</TH>";
			$val =$val."<TD>" . $row['lattitude'] . "</TD>";
			$val =$val."<TD>" . $row['longitude'] . "</TD>";
			$val =$val."<TD>" . $row['distance'] . "</TD>";
			$val =$val."<TD>" . $row['hauteur'] . "</TD>";
			$val =$val."<TD> <INPUT type=\"checkbox\" value=\"".$points."\" onclick=\"photo(".$points.")\" ></INPUT>photo</TD>";
		$val =$val."</TR>" ;
	}  
	$val = $val."</TABLE> ";
	echo $val;
	mysqli_close($con);

?>
