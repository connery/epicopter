package epicopter.utils;

import java.util.Calendar;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.widget.DatePicker;

public class DatePickerFragment extends DialogFragment implements DatePickerDialog.OnDateSetListener {

	CallbackDatePickerFragment	callback;
	int							day		= 0;
	int							month	= 0;
	int							year	= 0;

	public DatePickerFragment(CallbackDatePickerFragment callback) {
		super();
		this.callback = callback;
	}

	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		final Calendar c = Calendar.getInstance();
		int year = c.get(Calendar.YEAR);
		int month = c.get(Calendar.MONTH);
		int day = c.get(Calendar.DAY_OF_MONTH);

		DatePickerDialog dpd = new DatePickerDialog(getActivity(), this, year, month, day);
		dpd.setCancelable(false);
		dpd.setCanceledOnTouchOutside(false);
		dpd.getDatePicker().setMinDate(System.currentTimeMillis() - 10000);
		return dpd;
	}

	public void onDateSet(DatePicker view, int year, int month, int day) {
		callback.callbackFromDatePicker(day, month, year);
	}

	public int getDay() {
		return day;
	}

	public int getMonth() {
		return month;
	}

	public int getYear() {
		return year;
	}
}