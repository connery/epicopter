package epicopter.database;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;
import epicopter.main.R;
import epicopter.utils.JSONParser;

public class SendDataToDBDAO extends AsyncTask<String, String, String> implements DataBaseInterface {

	/**
	 * Progress dialog and context variables
	 */
	private boolean			showPDialog		= false;
	private ProgressDialog	pDialog			= null;
	private Context			context			= null;
	private TaskCallback	taskCallback	= null;

	/**
	 * JSON parser class
	 */
	private JSONParser		jsonParser		= new JSONParser();

	public SendDataToDBDAO(Context context, TaskCallback taskCallback, boolean showPDialog) {
		this.context = context;
		this.taskCallback = taskCallback;
		this.showPDialog = showPDialog;
	}

	@Override
	protected void onPreExecute() {
		super.onPreExecute();
		if (showPDialog) {
			pDialog = new ProgressDialog(context);
			pDialog.setMessage(context.getString(R.string.waiting));
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(false);
			pDialog.show();
		}
	}

	/**
	 * Send args to database. args[0] = Url will be called, args[1] = data name, args[2] = data value, args[3] = data name, args[4] = data value
	 */
	@Override
	protected String doInBackground(String... args) {
		int success;

		try {
			List<NameValuePair> params = new ArrayList<NameValuePair>();

			for (int i = 1; i < args.length; i += 2) {
				params.add(new BasicNameValuePair(args[i], args[i + 1]));
			}
			JSONObject json = jsonParser.makeHttpRequest(args[0], "POST", params);
			success = json.getInt(TAG_SUCCESS);
			if (success == 1) {
				Log.d("Send DATA to database OK", json.toString());
				return json.getString(TAG_MESSAGE);
			} else {
				Log.d("Send DATA to database FAIL", json.getString(TAG_MESSAGE));
				return json.getString(TAG_MESSAGE);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return null;
	}

	protected void onPostExecute(String file_url) {
		if (showPDialog && pDialog != null && pDialog.isShowing()) {
			pDialog.cancel();
		}
		if (taskCallback != null)
			if (file_url.equals(TAG_SUCCESS))
				taskCallback.taskDone(true);
			else
				taskCallback.taskDone(false);
		Toast.makeText(context, "OnPostExecute 'SendDataToDAO' : " + file_url, Toast.LENGTH_SHORT).show();
	}
}
