package epicopter.utils;

import java.util.HashMap;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import epicopter.login.MainFragmentActivity;

public class SessionManager {

	// Shared Preferences
	SharedPreferences			pref;
	// Editor for Shared preferences
	Editor						editor;
	// Context
	Context						_context;
	// Shared preferences mode
	int							PRIVATE_MODE			= 0;
	// Shared preferences file name
	private static final String	PREF_NAME				= "EpicopterSharedPreferences";
	// All Shared Preferences Keys
	private static final String	IS_LOGIN				= "IsLoggedIn";

	// User name (make variable public to access from outside)
	public static final String	KEY_NAME				= "name";
	// Email address (make variable public to access from outside)
	public static final String	KEY_EMAIL				= "email";
	// Is a facebook conection or not (make variable public to access from outside)
	public static final String	KEY_FB_CONNECTION		= "facebookConnection";
	// Id of the last trip opened
	public static final String	KEY_ID_LAST_TRIP_USED	= "lastTripUsed";

	// Constructor
	public SessionManager(Context context) {
		this._context = context;
		pref = _context.getSharedPreferences(PREF_NAME, PRIVATE_MODE);
		editor = pref.edit();
	}

	/**
	 * Create login session
	 * */
	public void createLoginSession(String email, String isFbConnection) {
		// Storing login value as TRUE
		editor.putBoolean(IS_LOGIN, true);

		// Storing name in pref
		editor.putString(KEY_NAME, "AChanger");

		// Storing email in pref
		editor.putString(KEY_EMAIL, email);

		// Storing if it's a facebook connection or not in pref
		editor.putString(KEY_FB_CONNECTION, isFbConnection);

		// commit changes
		editor.commit();
	}

	/**
	 * Check login method will check user login status If false it will redirect user to login page Else won't do anything
	 * */
	public void checkLogin() {
		// Check login status
		if (!this.isLoggedIn()) {
			// user is not logged in redirect him to Login Activity
			Intent i = new Intent(_context, epicopter.login.MainFragmentActivity.class);
			// Closing all the Activities
			i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

			// Add new Flag to start new Activity
			i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);

			// Staring Login Activity
			_context.startActivity(i);
		}

	}

	/**
	 * Get stored session data
	 * */
	public HashMap<String, String> getUserDetails() {
		HashMap<String, String> user = new HashMap<String, String>();
		// user name
		user.put(KEY_NAME, pref.getString(KEY_NAME, null));

		// user email id
		user.put(KEY_EMAIL, pref.getString(KEY_EMAIL, null));

		// user type of connection
		user.put(KEY_FB_CONNECTION, pref.getString(KEY_FB_CONNECTION, "0"));

		// return user
		return user;
	}

	public Context getContext() {
		return _context;
	}

	/**
	 * Clear session details
	 * */
	public void logoutUser() {
		// Clearing all data from Shared Preferences
		editor.clear();
		editor.commit();

		// After logout redirect user to Login Activity
		Intent i = new Intent(_context, MainFragmentActivity.class);
		// Closing all the Activities
		i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

		// Add new Flag to start new Activity
		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);

		// Staring Login Activity
		_context.startActivity(i);
	}

	/**
	 * Quick check for login
	 * **/
	public boolean isLoggedIn() {
		return pref.getBoolean(IS_LOGIN, false);
	}

	/**
	 * Quick check the type of connection which is used
	 * **/
	public boolean isFacebookConnection() {
		if (pref.getString(KEY_FB_CONNECTION, "0").equals("1"))
			return true;
		else
			return false;
	}

	/* ************************ PART OF TRIP GESTURE ************************ */
	public void setIdCurrentTrip(Long id) {
		// Storing id of current trip
		editor.putLong(KEY_ID_LAST_TRIP_USED, id);
		// commit changes
		editor.commit();
	}

	public Long getIdLastTripUsed() {
		return pref.getLong(KEY_ID_LAST_TRIP_USED, -1);
	}
	/* ********************************************************************** */
}