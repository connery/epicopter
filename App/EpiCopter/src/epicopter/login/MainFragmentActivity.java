package epicopter.login;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;

import epicopter.database.DataBaseInterface;
import epicopter.database.TaskCallback;
import epicopter.interfaces.LoginInterface;
import epicopter.main.R;
import epicopter.utils.SessionManager;

public class MainFragmentActivity extends FragmentActivity implements
		LoginInterface, DataBaseInterface, TaskCallback {

	/* FRAGMENTS */
	private Fragment[] fragments = new Fragment[FRAGMENT_COUNT];
	private MenuItem settings = null;
	private SessionManager mySession = null;

	/* SESSION LISTENER */
	private UiLifecycleHelper uiHelper = null;
	private Session.StatusCallback callback = new Session.StatusCallback() {
		@Override
		public void call(Session session, SessionState state,
				Exception exception) {
			onSessionStateChange(session, state, exception);
		}
	};

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.login_management);

		/* SESSION */
		mySession = new SessionManager(this);
		/* ******* */

		/* Keep track of the session */
		uiHelper = new UiLifecycleHelper(this, callback);
		uiHelper.onCreate(savedInstanceState);
		/* ************************* */

		/* FRAGMENTS */
		FragmentManager fm = getSupportFragmentManager();
		fragments[LOGIN] = fm.findFragmentById(R.id.loginLoginFragment);
		fragments[INSCRIPTION] = fm
				.findFragmentById(R.id.loginInscriptionFragment);
		fragments[FORGOTPASSWORD] = fm
				.findFragmentById(R.id.loginForgotPasswordFragment);
		fragments[SUCCESS] = fm.findFragmentById(R.id.loginSuccessFragment);
		fragments[SETTINGS] = fm
				.findFragmentById(R.id.comFacebookWidgetUserSettingsFragment);

		FragmentTransaction transaction = fm.beginTransaction();
		for (int i = 0; i < fragments.length; i++) {
			transaction.hide(fragments[i]);
		}
		transaction.commit();
		/* *********** */
	}

	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		// only add the menu when the selection fragment is showing
		if (fragments[SUCCESS].isVisible()) {
			if (menu.size() == 0) {
				settings = menu.add(R.string.settings);
			}
			return true;
		} else {
			menu.clear();
			settings = null;
		}
		return false;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		if (item.equals(settings)) {
			showFragment(SETTINGS, true);
			return true;
		}
		return false;
	}

	@Override
	protected void onResumeFragments() {
		Log.i("onResumeFragments", "onResumeFragments");
		super.onResumeFragments();
		Session session = Session.getActiveSession();

		if ((mySession != null && mySession.isLoggedIn())) {
			showFragment(SUCCESS, false);
		} else {
			showFragment(LOGIN, false);
		}
	}

	@Override
	public void onResume() {
		super.onResume();
		myClearBackStack();
		uiHelper.onResume();
	}

	@Override
	public void onPause() {
		super.onPause();
		uiHelper.onPause();
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		uiHelper.onActivityResult(requestCode, resultCode, data);
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		uiHelper.onDestroy();
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
		uiHelper.onSaveInstanceState(outState);
	}

	/** Called when the session state changes */
	public void showFragment(int fragmentIndex, boolean addToBackStack) {
		FragmentManager fm = getSupportFragmentManager();
		FragmentTransaction transaction = fm.beginTransaction();
		for (int i = 0; i < fragments.length; i++) {
			if (i == fragmentIndex) {
				transaction.show(fragments[i]);
			} else {
				transaction.hide(fragments[i]);
			}
		}
		if (addToBackStack) {
			transaction.addToBackStack(null);
		}
		transaction.commit();
	}

	/** Called due to session state change */
	private void onSessionStateChange(Session session, SessionState state,
			Exception exception) {
		myClearBackStack();
		if (state.isOpened() && !mySession.isLoggedIn()) {

			// new Request(session, "/me", null, HttpMethod.GET, new
			// Request.Callback() {
			// public void onCompleted(Response response) {
			// Log.i("Request facebook completed : ",
			// response.getGraphObject().getProperty("email").toString());
			// new SendDataToDB(getApplicationContext(),
			// MainFragmentActivity.this, false, URL_LOGIN, "u_email",
			// response.getGraphObject().getProperty("email")
			// .toString(), "is_fb_connection", TRUE);
			// mySession.createLoginSession(response.getGraphObject().getProperty("email").toString(),
			// TRUE);
			// }
			// }).executeAsync();
			mySession.createLoginSession("", TRUE);
			showFragment(SUCCESS, false);
		} else if (state.isClosed()) {
			showFragment(LOGIN, false);
		}
	}

	/* MY FONCTIONS */
	/**
	 * Clear the back stack
	 * 
	 * @return The back stack entry count
	 */
	private int myClearBackStack() {
		FragmentManager manager = getSupportFragmentManager();
		int backStackSize = manager.getBackStackEntryCount();

		for (int i = 0; i < backStackSize; i++)
			manager.popBackStack();
		return backStackSize;
	}

	/**
	 * Called when the SendDataToDB is finished
	 * 
	 * @param isOK
	 *            true if no problems are appeared
	 */
	@Override
	public void taskDone(boolean isOK) {
		if (isOK) {
			// logOn();
		}
	}

	private void logOn() {
		Log.i("LOGON : ", "Intent mainFragment");
		Intent i = new Intent(getApplicationContext(),
				epicopter.welcome.MainFragmentActivity.class);
		finish();
		startActivity(i);
	}

}
