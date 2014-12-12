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
import android.widget.CheckBox;
import android.widget.EditText;
import epicopter.main.R;

public class ValiderFragment extends Fragment implements OnClickListener {

	private View		view		= null;
	private EditText	etTripName	= null;
	private CheckBox	cb_video	= null;
	private CheckBox	cb_picture	= null;

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
		cb_video = (CheckBox) view.findViewById(R.id.checkBoxVideo);
		cb_picture = (CheckBox) view.findViewById(R.id.checkBoxPicture);
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
		if (cb_picture.isChecked() && cb_video.isChecked()) {
			GoogleMapsFragment.saveToLocalDB(name, 1, 1);
		} else if (cb_picture.isChecked()) {
			GoogleMapsFragment.saveToLocalDB(name, 1, 0);
		} else if (cb_video.isChecked()) {
			GoogleMapsFragment.saveToLocalDB(name, 0, 1);
		} else {
			GoogleMapsFragment.saveToLocalDB(name, 0, 0);
		}
		// Hide the keyboard
		InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(etTripName.getWindowToken(), 0); // token of the window that is making the request
	}

	private void actionButtonSend() {
		GoogleMapsFragment.sendDataToExternalDB();
	}

}