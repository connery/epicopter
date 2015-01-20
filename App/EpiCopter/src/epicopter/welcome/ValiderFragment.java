package epicopter.welcome;

import java.text.SimpleDateFormat;
import java.util.Calendar;

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
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TextView;
import epicopter.database.local.Vol;
import epicopter.database.local.VolsDBAdapter;
import epicopter.main.R;
import epicopter.utils.CallbackDatePickerFragment;
import epicopter.utils.CallbackTimePickerFragment;
import epicopter.utils.DatePickerFragment;
import epicopter.utils.SessionManager;
import epicopter.utils.TimePickerFragment;

public class ValiderFragment extends Fragment implements OnClickListener, CallbackDatePickerFragment, CallbackTimePickerFragment {

	private View				view			= null;
	private CheckBox			cb_video		= null;
	private CheckBox			cb_picture		= null;
	private CheckBox			cb_immediatly	= null;
	private EditText			etTripName		= null;
	private TextView			tvDateAndTime	= null;
	private EditText			etNumberOfTrip	= null;

	private final static String	DATE_PICKER_ID	= "1";
	private DatePicker			datePicker		= null;

	Calendar					date			= Calendar.getInstance();

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.welcome_valider_fragment, container, false);

		etTripName = (EditText) view.findViewById(R.id.welcomeValiderEditTextTripName);
		etNumberOfTrip = (EditText) view.findViewById(R.id.editTextNumberOfTrip);
		tvDateAndTime = (TextView) view.findViewById(R.id.textViewClickableDateAndTime);
		tvDateAndTime.setOnClickListener(this);
		Button btnSave = (Button) view.findViewById(R.id.welcomeValiderButtonSave);
		btnSave.setOnClickListener(this);
		Button btnSend = (Button) view.findViewById(R.id.welcomeValiderButtonSend);
		btnSend.setOnClickListener(this);
		Button btnSaveAndSend = (Button) view.findViewById(R.id.welcomeValiderButtonSaveAndSend);
		btnSaveAndSend.setOnClickListener(this);
		cb_video = (CheckBox) view.findViewById(R.id.checkBoxVideo);
		cb_picture = (CheckBox) view.findViewById(R.id.checkBoxPicture);
		cb_immediatly = (CheckBox) view.findViewById(R.id.checkBoxImmediatly);

		if (!getActivity().getIntent().getBooleanExtra("isNewTrip", true)) {
			loadLastTrip();
		}
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
		case R.id.textViewClickableDateAndTime:
			TimePickerFragment timeFragment = new TimePickerFragment(this);
			timeFragment.show(getActivity().getSupportFragmentManager(), "timePicker");
			DatePickerFragment dateFragment = new DatePickerFragment(this);
			dateFragment.show(getActivity().getSupportFragmentManager(), "datePicker");
			break;
		default:
			break;
		}
	}

	private void actionButtonSave() {
		String name = etTripName.getText().toString();
		int takeVideo = (cb_video.isChecked()) ? 1 : 0;
		int takePicture = (cb_picture.isChecked()) ? 1 : 0;
		long seconds = 0;
		int numberOfTrip = Integer.valueOf(etNumberOfTrip.getText().toString());

		if (cb_immediatly.isChecked()) {
			date = Calendar.getInstance();
			seconds = date.getTimeInMillis();
		} else {
			seconds = date.getTimeInMillis();
		}

		if (name.isEmpty())
			name = "trip";

		GoogleMapsFragment.saveToLocalDB(name, takePicture, takeVideo, seconds, numberOfTrip);

		// Hide the keyboard
		InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(etTripName.getWindowToken(), 0); // token of the window that is making the request
	}

	private void actionButtonSend() {
		GoogleMapsFragment.sendDataToExternalDB();
	}

	/**
	 * Function to load the last trip saved in local DB
	 */
	private void loadLastTrip() {
		SessionManager mySession = new SessionManager(view.getContext());

		// STEP 1 : Open the Vol's DB
		VolsDBAdapter volsDB = new VolsDBAdapter(view.getContext());
		volsDB.open();
		// STEP 2 : Get the last trip or the trip come from historicActivity click
		Vol myVol = null;
		if (getActivity().getIntent().getLongExtra("volId", -1) != -1) {
			myVol = volsDB.getVolById(getActivity().getIntent().getLongExtra("volId", -1));
		} else if (mySession.getIdLastTripUsed() != -1) {
			myVol = volsDB.getVolById(mySession.getIdLastTripUsed());
		} else {
			myVol = volsDB.getLastVol(mySession.getUserDetails().get(SessionManager.KEY_EMAIL));
		}
		// STEP 3 : Is there a past trip
		if (myVol != null) { // No past trip
			// Trip's name
			etTripName.setText(myVol.getName());
			// Trip's date and time
			date.setTimeInMillis(myVol.getMillisecond());
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd - HH:mm");
			tvDateAndTime.setText(sdf.format(date.getTime()));
			// Trip's immediately
			cb_immediatly.setChecked(false);
			// Trip's number
			etNumberOfTrip.setText(String.valueOf(myVol.getNumberOfTrip()));
			// Take picture
			cb_picture.setChecked((myVol.getPicture() == 1) ? true : false);
			// Take video
			cb_video.setChecked((myVol.getVideo() == 1) ? true : false);
		}
		// Close vol's DB
		volsDB.close();
	}

	@Override
	public void callbackFromDatePicker(int day, int month, int year) {
		date = Calendar.getInstance();
		date.set(Calendar.DAY_OF_MONTH, day);
		date.set(Calendar.MONTH, month);
		date.set(Calendar.YEAR, year);
	}

	@Override
	public void callbackFromTimePicker(int second, int minute, int hour) {
		date.set(Calendar.MINUTE, minute);
		date.set(Calendar.HOUR_OF_DAY, hour);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd - HH:mm");
		tvDateAndTime.setText(sdf.format(date.getTime()));
		cb_immediatly.setChecked(false);
	}

}