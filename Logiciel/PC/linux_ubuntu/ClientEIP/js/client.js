var singelton = -1;
function createXHR()
{
    var request = false;
    try {
	request = new ActiveXObject('Msxml2.XMLHTTP');
    }
    catch (err2)
    {
	try {
	    request = new ActiveXObject('Microsoft.XMLHTTP');
	}
	catch (err3) {
	    try {
		request = new XMLHttpRequest();
	    }
	    catch (err1)
	    {
                request = false;
	    }
      }
    }
    return request;
}

function recupTable(id)
{
    var xhr=createXHR();
    xhr.onreadystatechange=function()
    {
	if (xhr.readyState==4 && xhr.status==200)
	{
	    var tableau = xhr.responseText;
	    
	    document.getElementById("conteneur1").innerHTML=tableau;
	}
    }
    xhr.open("GET","retourphp.php?q="+id,true);
    xhr.send();
    
}


function sendData(latitude, lngitude, distance)
{
    if (singelton == -1)
    {
	var parameters = location.search.substring(1).split("&");
	
	var temp = parameters[0].split("=");
	m_id = unescape(temp[1]);
	
	document.getElementById("map_id").innerHTML = m_id;
	singelton = m_id;
			}
    else
    {
	m_id = singelton;			
    }
    var data = "lat="+latitude+"&lng="+lngitude+"&dist="+distance+"&id="+m_id; // PASSER L'ID EN DYNAMIQUE
    var xhr=createXHR();
    xhr.open("POST", "http://www.talatrique.fr/testEip/my_php.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange=function()
    {
                if(xhr.readyState == 4)
        {
	    document.getElementById("ajax").innerHTML= xhr.responseText;
        }
    };
    xhr.send(data);
    recupTable(m_id);
}

var map;

var location1;
var location2;
var address1;
var address2;
var latlng;
var geocoder;

var myLatlng = new google.maps.LatLng(45.20297, 5.6995);

function initialize() {
    
    var myOptions = {
        zoom: 14,
        center: new google.maps.LatLng(48.681894, 6.184845),
        mapTypeId: google.maps.MapTypeId.HYBRID,
        zoomControl: true,
        zoomControlOptions: { style: google.maps.ZoomControlStyle.SMALL },
    };
    var posBak  = new google.maps.LatLng(48.69124368297936, 6.229848861694336);//position de la base d'operation
    var markerBase = new google.maps.Marker({
        position: posBak,
        map: map
    });
    var distanceKm2 = 0;
    
    
    
    map = new google.maps.Map(document.getElementById('map_canvas'), myOptions);
    
    
    
    

    google.maps.event.addListener(map, 'click', function(event) {
        placeMarker(event.latLng);
    });
    
}

function placeMarker(location) {
    var marker = new google.maps.Marker({
        position: location,
        map: map
    });
    posBak = new google.maps.LatLng(48.69124368297936, 6.229848861694336);//position de la base d'operation
    if ( typeof this.nbr == 'undefined' ) this.nbr = 1;
    if ( typeof this.counter == 'undefined' ) this.counter = [];
    if ( typeof this.counter[0] == 'undefined' ) this.counter[0] = posBak;
    if ( typeof this.counter[nbr] == 'undefined' ) this.counter[nbr] = location;
    if ( typeof this.dis  == 'undefined' ) this.dis = 0;
    
    document.getElementById("lat").innerHTML = location.lat();
    document.getElementById("lon").innerHTML = location.lng();
    document.getElementById("zoom_level").innerHTML = map.getZoom()+1;
    map.setCenter(location);
    
    var distanceKm = google.maps.geometry.spherical.computeDistanceBetween(this.counter[nbr], this.counter[nbr-1]);
    this.dis = this.dis + distanceKm/1000;
    document.getElementById("distance").innerHTML = this.dis;
    
    
    sendData(location.lat(), location.lng(), this.dis);
    
    
    var savelat =  location.lat();
    var savelng =  location.lng();
    
    
    this.nbr++;
    
}

google.maps.event.addDomListener(window, 'load', initialize);
