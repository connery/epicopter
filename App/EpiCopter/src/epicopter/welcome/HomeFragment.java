package epicopter.welcome;

import java.util.HashMap;

import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.facebook.Session;

import epicopter.main.R;
import epicopter.utils.SessionManager;

public class HomeFragment extends ListFragment {
	// Session Manager Class
	SessionManager session = null;
	// Button Logout
	Button btnLogout = null;
	TextView lblName = null;
	TextView lblEmail = null;
	View view = null;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		View view = inflater.inflate(R.layout.welcome_home_fragment, container,
				false);

		// Session class instance
		session = new SessionManager(view.getContext());

		lblName = (TextView) view.findViewById(R.id.lblName);
		lblEmail = (TextView) view.findViewById(R.id.lblEmail);
		// Button logout
		btnLogout = (Button) view.findViewById(R.id.btnLogout);

		Toast.makeText(view.getContext(),
				"User Login Status: " + session.isLoggedIn(), Toast.LENGTH_LONG)
				.show();

		session.checkLogin();

		// get user data from session
		HashMap<String, String> user = session.getUserDetails();
		// name
		String name = user.get(SessionManager.KEY_NAME);
		// email
		String email = user.get(SessionManager.KEY_EMAIL);
		// displaying user data
		lblName.setText("Name: " + name);
		lblEmail.setText("Email: " + email);

		String[] values = new String[] { "Android", "iPhone", "WindowsMobile",
				"Blackberry", "WebOS", "Ubuntu", "Windows7", "Max OS X",
				"Linux", "OS/2", "Android", "iPhone", "WindowsMobile",
				"Blackberry", "WebOS", "Ubuntu", "Windows7", "Max OS X",
				"Linux", "OS/2" };
//		ArrayAdapter<String> adapter = new ArrayAdapter<String>(getActivity(), R.layout.welcome_listview_row, R.id.secondLine, values);
//		setListAdapter(adapter);

		/**
		 * Logout button click event
		 * */
		btnLogout.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Session sessionFb = Session.getActiveSession();
				sessionFb.closeAndClearTokenInformation();
				getActivity().finish();
				session.logoutUser();
			}
		});
		return view;
	}

	@Override
	public void onListItemClick(ListView l, View v, int position, long id) {
		String item = (String) getListAdapter().getItem(position);
		Toast.makeText(v.getContext(), item + " selected", Toast.LENGTH_LONG)
				.show();
	}

	@Override
	public void onResume() {
		super.onResume();
		session.checkLogin();
		// get user data from session
		HashMap<String, String> user = session.getUserDetails();
		// name
		String name = user.get(SessionManager.KEY_NAME);
		// email
		String email = user.get(SessionManager.KEY_EMAIL);
		// displaying user data
		lblName.setText("Name: " + name);
		lblEmail.setText("Email: " + email);
	}
}
