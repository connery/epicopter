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
import epicopter.main.R;
import epicopter.utils.JSONParser;

public class GetDataFromDBDAO extends AsyncTask<String, String, String> implements DataBaseInterface {

	/**
	 * Progress dialog and context variables
	 */
	private ProgressDialog	pDialog		= null;
	private Context			context		= null;

	/**
	 * JSON parser class
	 */
	private JSONParser		jsonParser	= new JSONParser();
	private JSONObject		json		= null;
	private TaskCallback	mCallback	= null;

	public GetDataFromDBDAO(Context context, TaskCallback taskCallback) {
		this.context = context;
		this.mCallback = taskCallback;
	}

	public JSONObject getResult() {
		if (json != null)
			return json;
		return null;
	}

	@Override
	protected void onPreExecute() {
		super.onPreExecute();
		pDialog = new ProgressDialog(context);
		pDialog.setMessage(context.getString(R.string.download_your_data));
		pDialog.setIndeterminate(false);
		pDialog.setCancelable(false);
		pDialog.show();
	}

	@Override
	protected String doInBackground(String... args) {
		int success;

		try {
			List<NameValuePair> params = new ArrayList<NameValuePair>();

			for (int i = 1; i < args.length; i += 2) {
				params.add(new BasicNameValuePair(args[i], args[i + 1]));
			}

			json = jsonParser.makeHttpRequest(args[0], "POST", params);
			success = json.getInt(TAG_SUCCESS);
			if (success == 1) {
				Log.d("Get DATA from database OK", json.toString());
				return json.getString(TAG_MESSAGE);
			} else {
				Log.d("Get DATA from database FAIL", json.getString(TAG_MESSAGE));
				return json.getString(TAG_MESSAGE);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return null;
	}

	@Override
	protected void onPostExecute(String result) {
		super.onPostExecute(result);
		if (pDialog != null && pDialog.isShowing())
			pDialog.cancel();
		if (result.equals(TAG_SUCCESS))
			mCallback.taskDone(true);
		else
			mCallback.taskDone(false);
	}
}
