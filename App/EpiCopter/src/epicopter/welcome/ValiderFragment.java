package epicopter.welcome;

import java.util.List;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import epicopter.database.local.Point;
import epicopter.database.local.PointsDBAdapter;
import epicopter.database.local.Vol;
import epicopter.database.local.VolsDBAdapter;
import epicopter.main.R;

public class ValiderFragment extends Fragment {

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.welcome_valider_fragment, container, false);

		PointsDBAdapter pointsSource = new PointsDBAdapter(rootView.getContext());
		VolsDBAdapter volsSource = new VolsDBAdapter(rootView.getContext());
		pointsSource.open();
		volsSource.open();

		List<Point> myPoints = pointsSource.getAllPoints();
		List<Vol> myVols = volsSource.getAllVols();

		if (myPoints.size() > 0)
			Log.i("1. MY INFO!!!", myPoints.get(0).toString());
		if (myVols.size() > 0)
			Log.i("1. MY INFO!!!", myVols.get(0).toString());

		pointsSource.createPoint(15, 12.55, 12.46, 2.5);
		volsSource.createVol(0, 0);

		myPoints = pointsSource.getAllPoints();
		Log.i("2. MY INFO!!!", myPoints.get(0).toString());
		myVols = volsSource.getAllVols();
		Log.i("2. MY INFO!!!", myVols.get(0).toString());
		
		return rootView;
	}

}