package epicopter.historic;

import java.util.List;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;
import android.widget.Toast;
import epicopter.database.local.Vol;
import epicopter.database.local.VolsDBAdapter;
import epicopter.welcome.MainFragmentActivity;

public class HistoricActivity extends ListActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// STEP 1 : Get the last trip in local BDD
		VolsDBAdapter volsDB = new VolsDBAdapter(this);
		volsDB.open();
		List<Vol> myVol = volsDB.getAllVols();
		// Is there a past trip
		HistoricArrayAdapter adapter = new HistoricArrayAdapter(this, myVol);
		setListAdapter(adapter);
	}

	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		Vol item = (Vol) getListAdapter().getItem(position);
		Toast.makeText(this, item.getName() + " selected", Toast.LENGTH_LONG).show();

		Intent i = new Intent(this, MainFragmentActivity.class);
		i.putExtra("isNewTrip", false);
		i.putExtra("volId", item.getId());
		startActivity(i);
	}

}
