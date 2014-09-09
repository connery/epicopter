<?php

require("config.inc.php");

if (isset($_POST['lat']) && !empty($_POST['lat']) && isset($_POST['lng']) && !empty($_POST['lng']) && isset($_POST['dist']) && !empty($_POST['dist']) && isset($_POST['id']) && !empty($_POST['id'])) {
	$lat	= $_POST['lat'];
    $lng	= $_POST['lng'];
    $dist	= $_POST['dist'];
    $id		= $_POST['id'];
    
	$query = "INSERT INTO Points ( u_id, lattitude, longitude, distance) VALUES ( :u_id, :lattitude, :longitude, :distance )";
    $query_params = array(
        ':u_id' => $id,
        ':lattitude' => $lat,
        ':longitude' => $lng,
        ':distance' => $dist
    );
    try {
        $stmt   = $db->prepare($query);
        $result = $stmt->execute($query_params);
    }
    catch (PDOException $ex) {
        $response["success"] = 0;
        $response["message"] = "Insert fail in points";
        echo $response;
    }
    $response["success"] = 1;
    $response["message"] = "point added";
    echo $response;
}
?>
