package epicopter.utils;

import android.content.Context;
import android.net.ConnectivityManager;

public class InternetConnectionUtils {

	/**
	 * Checks if the device has Internet connection
	 */
	protected static boolean networkIsConnected(Context context) {
		final ConnectivityManager connMgr = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

		final android.net.NetworkInfo wifi = connMgr.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		final android.net.NetworkInfo mobile = connMgr.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);

		if (wifi.isConnected() || mobile.isConnected())
			return true;
		else
			return false;
	}

	/**
	 * Checks if the device has Internet connection and if it's connected by mobile connection
	 */
	protected static boolean networkIsConnectedByWifi(Context context) {
		if (networkIsConnected(context) == true) {
			final ConnectivityManager connMgr = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
			final android.net.NetworkInfo wifi = connMgr.getNetworkInfo(ConnectivityManager.TYPE_WIFI);

			if (wifi.isConnected())
				return true;
		}
		return false;
	}

	/**
	 * Checks if the device has Internet connection and if it's connected by mobile connection
	 */
	protected static boolean networkIsConnectedByMobile(Context context) {
		if (networkIsConnected(context) == true) {
			final ConnectivityManager connMgr = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
			final android.net.NetworkInfo mobile = connMgr.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);

			if (mobile.isConnected())
				return true;
		}
		return false;
	}

}
