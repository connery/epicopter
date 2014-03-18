<?php
$link = mysql_connect('mysql51-104.perso', 'talatriqbdd', 'epicopter88');
if (!$link) {
    echo "Could not connect:" . mysql_error());
}
echo 'Connected successfully';

$query = 'SELECT login FROM UserEpi WHERE lower(login) = 'epicop'';
$result = mysql_query($query);
$array = mysql_fetch_assoc($result);
echo $array['login'];

mysql_close($link);

?>
