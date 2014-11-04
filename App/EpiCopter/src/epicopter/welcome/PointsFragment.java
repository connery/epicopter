package epicopter.welcome;

import java.util.ArrayList;
import java.util.List;

import android.content.res.Resources;
import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;
import android.widget.Toast;
import epicopter.main.R;

public class PointsFragment extends ListFragment {

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.welcome_points_fragment, container, false);
		return rootView;
	}

	private List<ListViewPoint>	mItems; // ListView items list

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// initialize the items list
		mItems = new ArrayList<ListViewPoint>();
		Resources resources = getResources();
		mItems.add(new ListViewPoint(resources.getDrawable(R.drawable.ic_launcher), getString(R.string.app_name), getString(R.string.app_name)));
		mItems.add(new ListViewPoint(resources.getDrawable(R.drawable.ic_launcher), getString(R.string.app_name), getString(R.string.app_name)));
		mItems.add(new ListViewPoint(resources.getDrawable(R.drawable.ic_launcher), getString(R.string.app_name), getString(R.string.app_name)));
		// initialize and set the list adapter
		setListAdapter(new ListViewPointAdapter(getActivity(), mItems));
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
		ListViewPoint item = mItems.get(position);
		// do something
		Toast.makeText(getActivity(), item.title, Toast.LENGTH_SHORT).show();
	}
}