package epicopter.welcome;

import java.util.ArrayList;
import java.util.List;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;
import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import epicopter.database.local.Point;
import epicopter.main.R;

public class PointsFragment extends ListFragment /* implements OnClickListener */{

	private List<ListViewPoint>	mItems				= null;
	private View				view				= null;

	// RECEIVER
	protected BroadcastReceiver	broadcastReceiver	= new BroadcastReceiver() {
														@Override
														public void onReceive(Context context, Intent intent) {
															ArrayList<Point> points = GoogleMapsFragment.points;

															mItems.clear();
															Resources resources = getResources();
															for (Point point : points) {
																mItems.add(new ListViewPoint(resources.getDrawable(R.drawable.ic_launcher), String.valueOf(point
																		.getLatitude()), String.valueOf(point.getLongitude()), String.valueOf(point.getHauteur())));
															}
															setListAdapter(new ListViewPointAdapter(getActivity(), mItems));
														}
													};

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mItems = new ArrayList<ListViewPoint>();
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.welcome_points_fragment, container, false);
		return view;
	}

	@Override
	public void onViewCreated(View view, Bundle savedInstanceState) {
		super.onViewCreated(view, savedInstanceState);
		// remove the dividers from the ListView of the ListFragment
		getListView().setDivider(null);
	}

	@Override
	public void onResume() {
		super.onResume();
		// Create the filter corresponding to the action defined in the broadcast sent
		IntentFilter filter = new IntentFilter();
		filter.addAction("testAction");
		view.getContext().registerReceiver(this.broadcastReceiver, filter);
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		// Destroy receiver
		view.getContext().unregisterReceiver(this.broadcastReceiver);
	}

}