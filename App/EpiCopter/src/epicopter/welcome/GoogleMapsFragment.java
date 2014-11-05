package epicopter.welcome;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.GoogleMap.OnMapClickListener;
import com.google.android.gms.maps.GoogleMap.OnMarkerDragListener;
import com.google.android.gms.maps.MapView;
import com.google.android.gms.maps.MapsInitializer;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolygonOptions;
import com.google.android.gms.maps.model.PolylineOptions;

import epicopter.database.local.Point;
import epicopter.database.local.PointsDBAdapter;
import epicopter.database.local.Vol;
import epicopter.database.local.VolsDBAdapter;
import epicopter.main.R;

public class GoogleMapsFragment extends Fragment {
	// Google Map
	private MapView						mapView			= null;
	private GoogleMap					googleMap		= null;
	private PolygonOptions				polygonOpt		= null;
	private ArrayList<MarkerOptions>	markers			= null;
	public static ArrayList<Point>		points			= null;
	private static View					view			= null;

	private static final double			DEFAULT_HEIGHT	= 2.1;
	private static final int			DEFAULT_ZOOM	= 12;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.welcome_maps_fragment, container, false);

		// Gets the MapView from the XML layout and creates it
		mapView = (MapView) view.findViewById(R.id.map);
		mapView.onCreate(savedInstanceState);
		// Gets to GoogleMap from the MapView and does initialization stuff
		googleMap = mapView.getMap();

		try {
			// Initialize map
			MapsInitializer.initialize(this.getActivity());
		} catch (Exception e) {
			e.printStackTrace();
		}
		// Set map type
		setMapType(GoogleMap.MAP_TYPE_NORMAL);
		// Set current location button
		setShowingCurrentLocationButton(true);
		// Set current location on map
		setShowingCurrentLocation(true);
		// Set zoom control button
		setShowingZoomControlButton(true);
		// Create the polygon
		initializePolygone();
		// Create marker's list
		markers = new ArrayList<MarkerOptions>();
		// Create point's list
		points = new ArrayList<Point>();

		// Set action click on map
		googleMap.setOnMapClickListener(new OnMapClickListener() {
			@Override
			public void onMapClick(LatLng coordinateClickled) {
				addMarker(coordinateClickled);
				refreshMap();
			}
		});
		// Set long click action on marker
		googleMap.setOnMarkerDragListener(new OnMarkerDragListener() {
			int	markerPositionInMyMarkerList;

			@Override
			public void onMarkerDragStart(Marker markerClicked) {
				markerPositionInMyMarkerList = -1;
				for (Iterator<MarkerOptions> i = markers.iterator(); i.hasNext();) {
					++markerPositionInMyMarkerList;
					MarkerOptions markerTmp = i.next();
					if (markerTmp.getTitle().equals(markerClicked.getTitle())) {
						break;
					}
				}
			}

			@Override
			public void onMarkerDragEnd(Marker markerClicked) {
				if (markerPositionInMyMarkerList != -1) {
					// Change marker's position in marker's list
					markers.get(markerPositionInMyMarkerList).position(markerClicked.getPosition());
					// Change point's position in point's list
					points.get(markerPositionInMyMarkerList).setLatitude(markerClicked.getPosition().latitude);
					points.get(markerPositionInMyMarkerList).setLongitude(markerClicked.getPosition().longitude);
					refreshPolygone();
					refreshMap();
				}
			}

			@Override
			public void onMarkerDrag(Marker arg0) {
			}
		});

		// Get information to know if it will be a new trip or not
		if (!getActivity().getIntent().getBooleanExtra("isNewTrip", true)) {
			loadLastTrip();
		} else {
			putBaseLocation(48.6972012, 6.1673514);
		}
		// Draw the map
		refreshMap();

		return view;
	}

	/**
	 * Function to save all points in local DB
	 */
	public static void saveToLocalDB(int takePicture, int takeVideo) {
		// STEP 1 : Open vol DB
		VolsDBAdapter volsDB = new VolsDBAdapter(view.getContext());
		volsDB.open();
		// STEP 2 : Create Vol
		Vol myNewVol = volsDB.insertVol(takePicture, takeVideo);
		// STEP 3 : Open points DB
		PointsDBAdapter pointsDB = new PointsDBAdapter(view.getContext());
		pointsDB.open();
		// STEP 4 : Insert every point in DB with this vol id
		for (Point pnt : points) {
			pointsDB.insertPoint(myNewVol.getId(), pnt.getLatitude(), pnt.getLongitude(), DEFAULT_HEIGHT);
		}
		// STEP 5 : Close vol DB
		volsDB.close();
		// STEP 6 : Close points DB
		pointsDB.close();
		Toast.makeText(view.getContext(), "Sauvegarde du parcours r�ussi!", Toast.LENGTH_LONG).show();
	}

	/**
	 * Function to load the last trip saved in local DB
	 */
	private void loadLastTrip() {
		// STEP 1 : Get the last trip in local BDD
		VolsDBAdapter volsDB = new VolsDBAdapter(view.getContext());
		volsDB.open();
		Vol myVol = volsDB.getLastVol();
		// STEP 2 : Get every points on this trip
		PointsDBAdapter pointsDB = new PointsDBAdapter(view.getContext());
		pointsDB.open();
		List<Point> allOldPoints = pointsDB.getPointsByVolId(myVol.getId());
		// STEP 3 : Add every point as marker in marker's list
		for (Point pnt : allOldPoints) {
			addMarker(new LatLng(pnt.getLatitude(), pnt.getLongitude()));
		}
		Point lastPoint = allOldPoints.get(allOldPoints.size() - 1);
		moveCameraTo(new LatLng(lastPoint.getLatitude(), lastPoint.getLongitude()), DEFAULT_ZOOM);
		volsDB.close();
		pointsDB.close();
	}

	/**
	 * Function to refresh the map (after add or remove a marker)
	 */
	private void refreshMap() {
		// Clear the map
		googleMap.clear();
		// Add polygon on the map
		googleMap.addPolygon(polygonOpt);
		// Add every marker
		for (int i = 0; i < markers.size(); i++) {
			putMarker(markers.get(i).title(String.valueOf(i)));
		}
	}

	/**
	 * Define and zoom above the base location
	 * 
	 * @param latitude
	 * @param longitude
	 */
	private void putBaseLocation(double latitude, double longitude) {
		// Add one coordinate in marker's list, point's list and polygon
		addMarker(new LatLng(latitude, longitude));
		// Move the camera
		moveCameraTo(new LatLng(latitude, longitude), DEFAULT_ZOOM);
	}

	/**
	 * Function to put a marker on googleMap
	 * 
	 * @param latitude
	 * @param longitude
	 */
	private void putMarker(MarkerOptions marker) {
		googleMap.addMarker(marker);
	}

	/**
	 * Function to move the camera above a position
	 * 
	 * @param lat
	 * @param lng
	 * @param zoom
	 */
	private void moveCameraTo(LatLng coordonnee, int zoom) {
		CameraPosition cameraPosition = new CameraPosition.Builder().target(coordonnee).zoom(zoom).build();
		googleMap.animateCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));
	}

	/**
	 * Function to set map's type
	 * 
	 * @param type
	 */
	private void setMapType(int type) {
		googleMap.setMapType(type);
	}

	/**
	 * Function to set if the user can see the current position
	 * 
	 * @param bool
	 */
	private void setShowingCurrentLocation(boolean bool) {
		googleMap.setMyLocationEnabled(bool);
	}

	/**
	 * Function to set if the user can see the current position button
	 * 
	 * @param bool
	 */
	private void setShowingCurrentLocationButton(boolean bool) {
		googleMap.getUiSettings().setMyLocationButtonEnabled(bool);
	}

	/**
	 * Function to set if the user can see the zoom control button
	 * 
	 * @param bool
	 */
	private void setShowingZoomControlButton(boolean bool) {
		googleMap.getUiSettings().setZoomControlsEnabled(bool);
	}

	/**
	 * Function to create a polyline arround a coordinate
	 * 
	 * @return
	 */
	@SuppressWarnings("unused")
	private void createPolylineArroundCoordinate(double lat, double lng, double size) {
		PolylineOptions rectOptions = new PolylineOptions().add(new LatLng(lat - size, lng - size)).add(new LatLng(lat + size, lng - size))
				.add(new LatLng(lat + size, lng + size)).add(new LatLng(lat - size, lng + size)).add(new LatLng(lat - size, lng - size));
		googleMap.addPolyline(rectOptions);
	}

	/**
	 * Function to add one marker inside ArrayList of marker and inside the polygone
	 * 
	 * @param coordinate
	 */
	private void addMarker(LatLng coordinate) {
		// STEP 1 : Add coordinate to point's list
		points.add(new Point(coordinate.latitude, coordinate.longitude));
		// STEP 2 : Add coordinate to marker's list
		MarkerOptions marker = new MarkerOptions().position(coordinate).title("").draggable(true);
		marker.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED));
		markers.add(marker);
		// STEP 3 : Add coordinate to polygon
		addCoordinateToPolygone(coordinate);
	}

	/**
	 * Function to add one coordinate inside the polygone
	 * 
	 * @param coordinate
	 */
	private void addCoordinateToPolygone(LatLng coordinate) {
		// Add the coordinate in the polygone
		polygonOpt.add(coordinate);
	}

	/**
	 * Function to initialize the polygone
	 * 
	 * @param markers
	 */
	private void initializePolygone() {
		if (polygonOpt == null) {
			createPolygone();
		}
	}

	/**
	 * Function to create the polygone
	 */
	private void createPolygone() {
		polygonOpt = new PolygonOptions().strokeColor(Color.BLUE);
	}

	/**
	 * Function to refresh the polygon (after drag coordinate or delete one coordinate)
	 */
	private void refreshPolygone() {
		createPolygone();
		for (int i = 0; i < markers.size(); i++) {
			addCoordinateToPolygone(markers.get(i).getPosition());
		}
	}

	/**
	 * Function to create a circle
	 * 
	 * @param coordinate
	 * @param sizeMeter
	 */
	@SuppressWarnings("unused")
	private void createCircle(LatLng coordinate, int sizeMeter) {
		CircleOptions circleOptions = new CircleOptions().center(coordinate).radius(sizeMeter);
		googleMap.addCircle(circleOptions);
	}

	@Override
	public void onResume() {
		mapView.onResume();
		super.onResume();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		mapView.onDestroy();
	}

	@Override
	public void onLowMemory() {
		super.onLowMemory();
		mapView.onLowMemory();
	}

}