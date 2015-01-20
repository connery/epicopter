package epicopter.utils;

import java.util.Calendar;

import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.text.format.DateFormat;
import android.widget.TimePicker;

public class TimePickerFragment extends DialogFragment implements TimePickerDialog.OnTimeSetListener {
	CallbackTimePickerFragment	callback;
	int							hour	= 0;
	int							minute	= 0;

	public TimePickerFragment(CallbackTimePickerFragment callback) {
		this.callback = callback;
	}

	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		final Calendar c = Calendar.getInstance();
		int hour = c.get(Calendar.HOUR_OF_DAY);
		int minute = c.get(Calendar.MINUTE);

		TimePickerDialog tpd = new TimePickerDialog(getActivity(), this, hour, minute, DateFormat.is24HourFormat(getActivity()));
		tpd.setCancelable(false);
		return tpd;
	}

	public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
		callback.callbackFromTimePicker(0, minute, hourOfDay);
		this.hour = hourOfDay;
		this.minute = minute;
	}

	public int getMinute() {
		return this.minute;
	}

	public int getHour() {
		return this.hour;
	}
}