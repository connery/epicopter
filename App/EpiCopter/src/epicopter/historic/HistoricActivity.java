package epicopter.historic;

import java.util.List;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.ListView;
import android.widget.Toast;
import epicopter.database.local.Vol;
import epicopter.database.local.VolsDBAdapter;
import epicopter.main.R;
import epicopter.welcome.MainFragmentActivity;

public class HistoricActivity extends ListActivity implements OnItemLongClickListener {

	private HistoricArrayAdapter	adapter	= null;
	private List<Vol>				myVol	= null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// STEP 1 : Get the last trip in local BDD
		VolsDBAdapter volsDB = new VolsDBAdapter(this);
		volsDB.open();
		myVol = volsDB.getAllVols();
		volsDB.close();
		// Is there a past trip
		adapter = new HistoricArrayAdapter(this, myVol);
		setListAdapter(adapter);
		// Define the ItemLongClickListener
		ListView list = getListView();
		list.setOnItemLongClickListener(this);
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

	@Override
	public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
		final Vol item = (Vol) getListAdapter().getItem(position);
		// Create an alertDialog to delete the trip
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setMessage(R.string.delete).setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) { // Action when user answer YES
				// STEP 1 : Open vol DB
				VolsDBAdapter volsDB = new VolsDBAdapter(getApplicationContext());
				volsDB.open();
				// STEP 2 : Delete Vol
				volsDB.deleteVol(item);
				volsDB.close();
				// Update my trip's list and refresh adapter
				myVol.remove(item);
				adapter.notifyDataSetChanged();
			}
		}).setNegativeButton(R.string.no, new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) { // Action when user answer NO
			}
		});
		builder.show();
		return true;
	}
}
