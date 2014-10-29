package epicopter.database;

import android.content.Context;
import android.widget.Toast;
import epicopter.main.R;
import epicopter.utils.InternetConnectionUtils;

public class SendDataToDB extends InternetConnectionUtils {

	/**
	 * @param context
	 *            Context of the current page
	 * @param taskCallBack
	 *            task will be called at the end of the execution
	 * @param args
	 *            List of parameters
	 */
	public SendDataToDB(Context context, TaskCallback taskCallback, boolean showPDialog, String... args) {
		if (networkIsConnected(context)) {
			new SendDataToDBDAO(context, taskCallback, showPDialog).execute(args);
		} else {
			Toast.makeText(context, context.getString(R.string.error_no_internet_connection), Toast.LENGTH_SHORT).show();
		}
	}
}
