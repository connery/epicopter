package epicopter.database;

import org.json.JSONObject;

import android.content.Context;
import android.widget.Toast;
import epicopter.main.R;
import epicopter.utils.InternetConnectionUtils;

public class GetDataFromDB extends InternetConnectionUtils {

	private GetDataFromDBDAO	getDataFromDB;

	/**
	 * 
	 * @param context
	 * @param [0] => receiver's id, [1] => nb limit
	 */
	public GetDataFromDB(Context context, TaskCallback taskCallback, String... args) {
		if (networkIsConnected(context)) {
			getDataFromDB = (GetDataFromDBDAO) new GetDataFromDBDAO(context, taskCallback).execute(args);
		} else {
			Toast.makeText(context, context.getString(R.string.error_no_internet_connection), Toast.LENGTH_SHORT).show();
		}
	}

	public JSONObject getResult() {
		if (getDataFromDB != null)
			return (getDataFromDB.getResult());
		return null;
	}
}
