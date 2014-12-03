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
import epicopter.database.DataBaseInterface;
import epicopter.database.SendDataToDB;
import epicopter.database.TaskCallback;
import epicopter.interfaces.LoginInterface;
import epicopter.main.R;
import epicopter.utils.AlertDialogManager;
import epicopter.utils.EncryptUtils;
import epicopter.validator.EmailValidator;

public class InscriptionFragment extends Fragment implements OnClickListener, TaskCallback, LoginInterface, DataBaseInterface {

	AlertDialogManager	alert		= new AlertDialogManager();
	View				view		= null;

	EditText			etEmail		= null;
	EditText			etPassword	= null;
	Button				btnValider	= null;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		view = inflater.inflate(R.layout.login_inscription_fragment, container, false);

		etEmail = (EditText) view.findViewById(R.id.editTextInscriptionEmail);
		etPassword = (EditText) view.findViewById(R.id.editTextInscriptionPassword);

		btnValider = (Button) view.findViewById(R.id.buttonInscriptionValider);
		btnValider.setOnClickListener(this);

		return view;
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.buttonInscriptionValider:
			String email = etEmail.getText().toString();
			String pass = etPassword.getText().toString();

			if (email != null && pass != null && !email.isEmpty() && !pass.isEmpty()) {
				if (EmailValidator.validate(email) == true)
					new SendDataToDB(view.getContext(), this, true, URL_ADD_USER, "u_email", email, "u_password", EncryptUtils.md5(pass));
				else
					alert.showAlertDialog(view.getContext(), "Inscription failed...", "There are a problem with your email", false);
			} else {
				alert.showAlertDialog(view.getContext(), "Inscription failed...", "Please enter your email and password", false);
			}
			InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
			imm.hideSoftInputFromWindow(btnValider.getWindowToken(), 0); // token of the window that is making the request
			break;
		default:
			break;
		}
	}

	@Override
	public void taskDone(boolean isOK) {
		if (isOK == true)
			((MainFragmentActivity) getActivity()).showFragment(LOGIN, false);
		else
			alert.showAlertDialog(view.getContext(), "Inscription failed...", "Error with internet connection", false);
	}
}
