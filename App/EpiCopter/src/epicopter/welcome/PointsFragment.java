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
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import epicopter.database.local.Point;
import epicopter.main.R;

public class PointsFragment extends ListFragment implements OnClickListener {

	private List<ListViewPoint>	mItems				= null;
	private View				view				= null;
	private Button				btnMinus			= null;
	private Button				btnPlus				= null;
	private ListViewPoint		itemClicked			= null;

	// RECEIVER
	protected BroadcastReceiver	broadcastReceiver	= new BroadcastReceiver() {
														@Override
														public void onReceive(Context context, Intent intent) {
															ArrayList<Point> points = GoogleMapsFragment.points;

															mItems.clear();
															Resources resources = getResources();
															for (Point point : points) {
																mItems.add(new ListViewPoint(resources.getDrawable(R.drawable.ic_launcher), String.valueOf(point
																		.getLongitude()), String.valueOf(point.getLongitude()), String.valueOf(point.getHauteur())));
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
	public void onListItemClick(ListView l, View v, int position, long id) {
		// retrieve theListView item
		itemClicked = mItems.get(position);
		btnMinus = (Button) v.findViewById(R.id.btnMinus);
		btnPlus = (Button) v.findViewById(R.id.btnPlus);
		btnMinus.setOnClickListener(this);
		btnPlus.setOnClickListener(this);
		Toast.makeText(getActivity(), itemClicked.latitude, Toast.LENGTH_SHORT).show();
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

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btnMinus:
			Toast.makeText(v.getContext(), "Bouton - sur " + itemClicked.longitude, Toast.LENGTH_SHORT).show();
			break;
		case R.id.btnPlus:
			Toast.makeText(v.getContext(), "Bouton + sur " + itemClicked.latitude, Toast.LENGTH_SHORT).show();
			break;
		default:
			break;
		}
	}
}