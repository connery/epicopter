package epicopter.welcome;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import epicopter.historic.HistoricActivity;
import epicopter.main.R;

public class WelcomeChooseTripActivity extends Activity implements OnClickListener {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.welcome_choose_trip);

		Button btnNewTrip = (Button) findViewById(R.id.welcomeChooseTripButtonNewTrip);
		Button btnHistoricTrip = (Button) findViewById(R.id.welcomeChooseTripButtonHistoricTrip);
		Button btnOldTrip = (Button) findViewById(R.id.welcomeChooseTripButtonResumeTrip);
		btnNewTrip.setOnClickListener(this);
		btnHistoricTrip.setOnClickListener(this);
		btnOldTrip.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		Intent i = new Intent(this, MainFragmentActivity.class);

		switch (v.getId()) {
		case R.id.welcomeChooseTripButtonNewTrip:
			i.putExtra("isNewTrip", true);
			startActivity(i);
			break;
		case R.id.welcomeChooseTripButtonHistoricTrip:
			Intent b = new Intent(this, HistoricActivity.class);
			startActivity(b);
			break;
		case R.id.welcomeChooseTripButtonResumeTrip:
			i.putExtra("isNewTrip", false);
			startActivity(i);
			break;
		default:
			break;
		}
	}

}
