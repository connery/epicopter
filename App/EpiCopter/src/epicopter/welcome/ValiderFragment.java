package epicopter.welcome;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import epicopter.main.R;

public class ValiderFragment extends Fragment implements OnClickListener {

	private View		view		= null;
	private EditText	etTripName	= null;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.welcome_valider_fragment, container, false);

		etTripName = (EditText) view.findViewById(R.id.welcomeValiderEditTextTripName);
		Button btnSave = (Button) view.findViewById(R.id.welcomeValiderButtonSave);
		btnSave.setOnClickListener(this);
		Button btnSend = (Button) view.findViewById(R.id.welcomeValiderButtonSend);
		btnSend.setOnClickListener(this);
		Button btnSaveAndSend = (Button) view.findViewById(R.id.welcomeValiderButtonSaveAndSend);
		btnSaveAndSend.setOnClickListener(this);
		return view;
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.welcomeValiderButtonSave:
			actionButtonSave();
			break;
		case R.id.welcomeValiderButtonSend:
			actionButtonSend();
			break;
		case R.id.welcomeValiderButtonSaveAndSend:
			actionButtonSave();
			actionButtonSend();
			break;
		default:
			break;
		}
	}

	private void actionButtonSave() {
		String name = etTripName.getText().toString();
		if (name.isEmpty())
			name = "trip";
		GoogleMapsFragment.saveToLocalDB(name, 1, 1);
		// Hide the keyboard
		InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(etTripName.getWindowToken(), 0); // token of the window that is making the request
	}

	private void actionButtonSend() {
		GoogleMapsFragment.sendDataToExternalDB();
	}

}