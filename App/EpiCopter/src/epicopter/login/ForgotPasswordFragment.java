package epicopter.login;

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
import android.widget.Toast;
import epicopter.database.DataBaseInterface;
import epicopter.database.SendDataToDB;
import epicopter.database.TaskCallback;
import epicopter.interfaces.LoginInterface;
import epicopter.main.R;
import epicopter.utils.AlertDialogManager;
import epicopter.validator.EmailValidator;

public class ForgotPasswordFragment extends Fragment implements OnClickListener, TaskCallback, DataBaseInterface, LoginInterface {

	AlertDialogManager	alert	= new AlertDialogManager();
	View				view	= null;
	EditText			etEmail	= null;
	Button				btnSend	= null;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.login_forgot_password_fragment, container, false);

		etEmail = (EditText) view.findViewById(R.id.editTextForgotPasswordEmail);
		btnSend = (Button) view.findViewById(R.id.buttonForgotPasswordSend);
		btnSend.setOnClickListener(this);
		return view;
	}

	@Override
	public void onClick(View v) {
		String email = etEmail.getText().toString();
		if (!email.isEmpty() && email.length() > 0) {
			if (EmailValidator.validate(email)) {
				new SendDataToDB(view.getContext(), this, true, URL_EMAIL, "u_email", email);
			} else {
				alert.showAlertDialog(view.getContext(), "Inscription failed...", "There are a problem with your email", false);
			}
		} else {
			alert.showAlertDialog(view.getContext(), "Inscription failed...", "Maybe you should be write your email", false);
		}
		InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(etEmail.getWindowToken(), 0); // token of the window that is making the request
	}

	@Override
	public void taskDone(boolean isOK) {
		if (isOK == true) {
			((MainFragmentActivity) getActivity()).showFragment(LOGIN, false);
		} else {
			Toast.makeText(view.getContext(), "FAILURE SEND EMAIL", Toast.LENGTH_SHORT).show();
			alert.showAlertDialog(view.getContext(), "Send email failed...", "Email is incorrect/doesn't exist", false);
		}
	}
}
