package epicopter.welcome;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

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
	private MapView							mapView		= null;
	private GoogleMap						googleMap	= null;
	private PolygonOptions					polygonOpt	= null;
	private static ArrayList<MarkerOptions>	points		= null;
	private static View						view		= null;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.welcome_maps_fragment, container, false);

		PointsDBAdapter pointsSource = new PointsDBAdapter(view.getContext());
		pointsSource.open();
		pointsSource.insertPoint(3, 12.55, 12.46, 2.5);
		pointsSource.insertPoint(3, 12.8, 12.46, 2.5);
		pointsSource.insertPoint(3, 12.6, 12.0, 2.5);
		pointsSource.insertPoint(3, 113, 11.6, 2.5);
		VolsDBAdapter volsSource = new VolsDBAdapter(view.getContext());
		volsSource.open();

		// Gets the MapView from the XML layout and creates it
		mapView = (MapView) view.findViewById(R.id.map);
		mapView.onCreate(savedInstanceState);
		// Gets to GoogleMap from the MapView and does initialization stuff
		googleMap = mapView.getMap();

		try {
			// initilizeMap();
			MapsInitializer.initialize(this.getActivity());
		} catch (Exception e) {
			e.printStackTrace();
		}
		// Set map type
		setMapType(GoogleMap.MAP_TYPE_NORMAL);
		// Set current locatio button
		setShowingCurrentLocationButton(true);
		// Set current location point on map
		setShowingCurrentLocation(true);
		// Set zoom controle button
		setShowingZoomControlButton(true);
		// Create the polygone
		initializePolygone();
		// create the list of points
		points = new ArrayList<MarkerOptions>();
		// Add one point (in the list and in the polygone
		addPoint(new LatLng(48.6972012, 6.1673514));
		moveCameraTo(new LatLng(48.6972012, 6.1673514), 12);

		googleMap.setOnMapClickListener(new OnMapClickListener() {
			@Override
			public void onMapClick(LatLng arg0) {
				LatLng pnt = new LatLng(arg0.latitude, arg0.longitude);
				addPoint(pnt);
				refreshMap();
			}
		});
		googleMap.setOnMarkerDragListener(new OnMarkerDragListener() {
			int	pos;

			@Override
			public void onMarkerDragStart(Marker arg0) {
				pos = -1;
				for (Iterator<MarkerOptions> i = points.iterator(); i.hasNext();) {
					++pos;
					MarkerOptions pointTmp = i.next();
					if (pointTmp.getTitle().equals(arg0.getTitle())) {
						break;
					}
				}
			}

			@Override
			public void onMarkerDragEnd(Marker arg0) {
				if (pos != -1) {
					points.get(pos).position(new LatLng(arg0.getPosition().latitude, arg0.getPosition().longitude));
					refreshPolygone();
					refreshMap();
					// addPoint(arg0.getPosition());
				}
			}

			@Override
			public void onMarkerDrag(Marker arg0) {
			}
		});
		if (getActivity().getIntent().getBooleanExtra("loadOldTrip", false)) {
			loadOldTrip();
		}
		refreshMap();

		return view;
	}

	/**
	 * Function to save all points in local BDD
	 */
	public static void saveToLocalDB() {
		// STEP 1 : Create trip
		VolsDBAdapter volsDB = new VolsDBAdapter(view.getContext());
		volsDB.open();
		Vol myNewVol = volsDB.insertVol(1, 1);
		// STEP 2 : Add all points inside DB with this vol id
		PointsDBAdapter pointsDB = new PointsDBAdapter(view.getContext());
		pointsDB.open();
		for (MarkerOptions point : points) {
			pointsDB.insertPoint(myNewVol.getId(), point.getPosition().latitude, point.getPosition().longitude, 2);
		}
		Log.i("MY INFO!!!", "Tout est enregistrer dans la BDD local");
	}

	/**
	 * Function to load the last trip saved in local BDD
	 */
	private void loadOldTrip() {
		// STEP 1 : Get the last trip in local BDD
		VolsDBAdapter volsDB = new VolsDBAdapter(view.getContext());
		volsDB.open();
		Vol myVol = volsDB.getLastVol();
		PointsDBAdapter pointsDB = new PointsDBAdapter(view.getContext());
		pointsDB.open();
		List<Point> points = pointsDB.getPointsByVolId(myVol.getId());
		for (Point point : points) {
			addPoint(new LatLng(point.getAltitude(), point.getLongitude()));
		}
	}

	/**
	 * Function to refresh th map (after add or remove a checkPoint)
	 */
	private void refreshMap() {
		// Clear the map
		googleMap.clear();
		// Add the polygone on the map
		googleMap.addPolygon(polygonOpt);
		// Add all marker
		for (int i = 0; i < points.size(); i++) {
			putMarker(points.get(i).title(String.valueOf(i)));
		}
	}

	/**
	 * Function to put a marker
	 * 
	 * @param latitude
	 * @param longitude
	 */
	private void putMarker(MarkerOptions point) {
		googleMap.addMarker(point);
	}

	/**
	 * Function to move the camera above a position
	 * 
	 * @param lat
	 * @param lng
	 * @param zoom
	 */
	private void moveCameraTo(LatLng point, int zoom) {
		CameraPosition cameraPosition = new CameraPosition.Builder().target(point).zoom(zoom).build();
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
	 * Function to create a polyline arround a point
	 * 
	 * @return
	 */
	@SuppressWarnings("unused")
	private void createPolylineArroundPoint(double lat, double lng, double size) {
		PolylineOptions rectOptions = new PolylineOptions().add(new LatLng(lat - size, lng - size)).add(new LatLng(lat + size, lng - size))
				.add(new LatLng(lat + size, lng + size)).add(new LatLng(lat - size, lng + size)).add(new LatLng(lat - size, lng - size));
		/* Polyline polyline = */googleMap.addPolyline(rectOptions);
	}

	/**
	 * Function to add one point inside ArrayList of point and inside the polygone
	 * 
	 * @param point
	 */
	private void addPoint(LatLng point) {
		// Add this point in the ArrayList
		MarkerOptions marker = new MarkerOptions().position(point).title("").draggable(true);
		marker.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED));
		points.add(marker);
		// Add the same point in the polygone
		addPointToPolygone(point);
	}

	/**
	 * Function to add one point inside the polygone
	 * 
	 * @param point
	 */
	private void addPointToPolygone(LatLng point) {
		// Add the point in the polygone
		polygonOpt.add(point);
	}

	/**
	 * Function to initialize the polygone
	 * 
	 * @param points
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
	 * Function to refresh the polygone (after drag point or delete one point)
	 */
	private void refreshPolygone() {
		createPolygone();
		for (int i = 0; i < points.size(); i++) {
			addPointToPolygone(points.get(i).getPosition());
		}
	}

	/**
	 * Function to create a circle
	 * 
	 * @param point
	 * @param sizeMeter
	 */
	private void createCircle(LatLng point, int sizeMeter) {
		CircleOptions circleOptions = new CircleOptions().center(point).radius(sizeMeter);
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