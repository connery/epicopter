package epicopter.login;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;

import com.facebook.HttpMethod;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;

import epicopter.database.DataBaseInterface;
import epicopter.database.SendDataToDB;
import epicopter.database.TaskCallback;
import epicopter.interfaces.LoginInterface;
import epicopter.main.R;
import epicopter.utils.SessionManager;
import epicopter.welcome.WelcomeChooseTripActivity;

public class LoginSuccessFragment extends Fragment implements LoginInterface, DataBaseInterface, TaskCallback {

	View	view		= null;
	Session	sessionFb	= null;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.login_success, container, false);
		sessionFb = Session.getActiveSession();
		return view;
	}

	SessionManager	mySession;

	@Override
	public void onHiddenChanged(boolean hidden) {
		Log.i("onHiddenChanged", "Value of hidden bool : " + String.valueOf(hidden));
		super.onHiddenChanged(hidden);

		if (!hidden) {
			mySession = new SessionManager(view.getContext());
			Session sessionFb = Session.getActiveSession();
			if (mySession != null && mySession.isLoggedIn()) {
				if (mySession != null && mySession.isFacebookConnection()) {
					Log.i("onHiddenChanged", " Is a fb connection!!!");
					new Request(sessionFb, "/me", null, HttpMethod.GET, new Request.Callback() {
						public void onCompleted(Response response) {
							Log.i("Request facebook completed : ", response.getGraphObject().getProperty("email").toString());
							new SendDataToDB(view.getContext(), LoginSuccessFragment.this, false, URL_LOGIN, "u_email", response.getGraphObject().getProperty("email")
									.toString(), "is_fb_connection", TRUE);
							mySession.createLoginSession(response.getGraphObject().getProperty("email").toString(), TRUE);
						}
					}).executeAsync();
				} else if (mySession != null && !mySession.isFacebookConnection()) {
					Log.i("onHiddenChanged", " Is a NORMAL connection!!!");
					Intent i = new Intent(view.getContext(), WelcomeChooseTripActivity.class);
					getActivity().finish();
					startActivity(i);
				}
			}
		}
	}

	@Override
	public void taskDone(boolean isOK) {
		if (isOK == true) {
			Intent i = new Intent(view.getContext(), WelcomeChooseTripActivity.class);
			getActivity().finish();
			startActivity(i);
		}
	}
}