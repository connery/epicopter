package epicopter.login;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Base64;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.facebook.widget.LoginButton;

import epicopter.database.DataBaseInterface;
import epicopter.database.GetDataFromDB;
import epicopter.database.TaskCallback;
import epicopter.interfaces.LoginInterface;
import epicopter.main.R;
import epicopter.utils.AlertDialogManager;
import epicopter.utils.EncryptUtils;
import epicopter.utils.SessionManager;

public class LoginFragment extends Fragment implements LoginInterface,
		DataBaseInterface, OnClickListener, OnFocusChangeListener, TaskCallback {

	// Email, password edittext
	EditText etEmail, etPassword;
	// login button
	Button btnLogin;
	Button btnInscription;
	TextView tvForgotPassword;
	// Alert Dialog Manager
	AlertDialogManager alert = new AlertDialogManager();
	// Session Manager Class
	SessionManager session;

	View view;
	GetDataFromDB dataFromDB;

	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		view = inflater
				.inflate(R.layout.login_login_fragment, container, false);

		// Session Manager
		session = new SessionManager(view.getContext());

		etEmail = (EditText) view.findViewById(R.id.editTextLoginEmail);
		etEmail.setOnFocusChangeListener(this);
		etPassword = (EditText) view.findViewById(R.id.editTextLoginPassword);
		etPassword.setOnFocusChangeListener(this);

		// Toast.makeText(view.getContext(), "User Login Status: " +
		// session.isLoggedIn(), Toast.LENGTH_LONG).show();

		btnLogin = (Button) view.findViewById(R.id.btnMyLogin);
		btnLogin.setOnClickListener(this);

		btnInscription = (Button) view.findViewById(R.id.buttonInscripton);
		btnInscription.setOnClickListener(this);

		tvForgotPassword = (TextView) view
				.findViewById(R.id.textViewForgotPassword);
		tvForgotPassword.setOnClickListener(this);
//session.logoutUser();
		LoginButton authButton = (LoginButton) view
				.findViewById(R.id.login_buttonFacebook);
		// authButton.setFragment(this);
		authButton.setReadPermissions(Arrays.asList("email", "user_likes",
				"user_status"));
		showHashKey(view.getContext());
		return view;
	}

	public static void showHashKey(Context context) {
		try {
			PackageInfo info = context.getPackageManager().getPackageInfo(
					"epicopter.main", PackageManager.GET_SIGNATURES); // Your
																		// package
																		// name
																		// here
			for (Signature signature : info.signatures) {
				MessageDigest md = MessageDigest.getInstance("SHA");
				md.update(signature.toByteArray());
				Log.i("KeyHash:",
						Base64.encodeToString(md.digest(), Base64.DEFAULT));
			}
		} catch (NameNotFoundException e) {
		} catch (NoSuchAlgorithmException e) {
		}
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btnMyLogin:
			String email = etEmail.getText().toString();
			String password = etPassword.getText().toString();

			if (email.trim().length() > 0 && password.trim().length() > 0) {
				dataFromDB = new GetDataFromDB(view.getContext(), this,
						URL_LOGIN, "u_email", email, "u_password",
						EncryptUtils.md5(password), "is_fb_connection", FALSE);
			} else {
				alert.showAlertDialog(view.getContext(), "Login failed...",
						"Please enter username and password", false);
			}

			break;
		case R.id.buttonInscripton:
			((MainFragmentActivity) getActivity()).showFragment(INSCRIPTION,
					true);
			break;
		case R.id.textViewForgotPassword:
			((MainFragmentActivity) getActivity()).showFragment(FORGOTPASSWORD,
					true);
			break;
		default:
			break;
		}
	}

	@Override
	public void taskDone(boolean isOK) {
		if (isOK == true) {
			String email = null;
			String isFbConnection = null;

			try {
				/*
				 * Recupérer les données de l'utilisateur grâce à la reponse
				 * JSON
				 */
				JSONObject jsonObj_user = (JSONObject) dataFromDB.getResult()
						.get("user");
				email = jsonObj_user.getString("u_email");
				isFbConnection = jsonObj_user.getString("is_fb_connection");
				/*
				 * Ouvrir la session à l'aide de ces données
				 */
				session.createLoginSession(email, isFbConnection);
			} catch (JSONException e) {
				e.printStackTrace();
			}

			((MainFragmentActivity) getActivity()).showFragment(SUCCESS, false);
		} else {
			alert.showAlertDialog(view.getContext(), "Login failed...",
					"Username/Password is incorrect", false);
		}
	}

	@Override
	public void onFocusChange(View v, boolean hasFocus) {
		if (!hasFocus) {
			InputMethodManager imm = (InputMethodManager) getActivity()
					.getSystemService(Context.INPUT_METHOD_SERVICE);
			imm.hideSoftInputFromWindow(etEmail.getWindowToken(), 0);
		}
	}

}
