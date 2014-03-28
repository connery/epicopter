<?php

require("config.inc.php");

if (!empty($_POST)) {

    $query = "UPDATE UserEpi SET ";
	$query_params = array();
	
	$pos = 0;
	while (!empty($_POST['data_name'.(string)$pos])) {
		if ($pos > 0)
			$query .= " , ";
		$query .= $_POST["data_name".(string)$pos];
		$query .= " = :data_value".(string)$pos." ";
		$query_params[":data_value".(string)$pos] = $_POST["data_value".(string)$pos];
		$pos++;
	}
        $query .= " WHERE id = :id;";
        $query_params[':id'] = $_POST['id'];
	
    try {
        $stmt   = $db->prepare($query);
        $result = $stmt->execute($query_params);
    }
    catch (PDOException $ex) {
        $response["success"] = 0;
        $response["message"] = $ex;
        //die(json_encode($response));
          echo "raté";
    }

    $response["success"] = 1;
    $response["message"] = "user_updating";
    echo json_encode($response);

}
?>
