package epicopter.welcome;

import android.app.ActionBar;
import android.app.ActionBar.Tab;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.view.View;
import epicopter.main.R;
import epicopter.utils.TimePickerFragment;

public class MainFragmentActivity extends FragmentActivity implements ActionBar.TabListener {

	private ViewPager			viewPager;
	private TabsPagerAdapter	mAdapter;
	private ActionBar			actionBar;
	private String[]			tabs	= { "Map", "Points", "Valider" };

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.welcome_management);

		// Initilization
		viewPager = (ViewPager) findViewById(R.id.pager);
		actionBar = getActionBar();
		mAdapter = new TabsPagerAdapter(getSupportFragmentManager());

		viewPager.setOffscreenPageLimit(4);
		viewPager.setAdapter(mAdapter);
		actionBar.setHomeButtonEnabled(false);
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

		// Adding Tabs
		for (String tab_name : tabs) {
			actionBar.addTab(actionBar.newTab().setText(tab_name).setTabListener(this));
		}

		/**
		 * on swiping the viewpager make respective tab selected
		 * */
		viewPager.setOnPageChangeListener(new ViewPager.OnPageChangeListener() {

			@Override
			public void onPageSelected(int position) {
				actionBar.setSelectedNavigationItem(position);
			}

			@Override
			public void onPageScrolled(int arg0, float arg1, int arg2) {
			}

			@Override
			public void onPageScrollStateChanged(int arg0) {
			}
		});
	}

	@Override
	public void onTabSelected(Tab tab, android.app.FragmentTransaction ft) {
		if (tab.getPosition() == 1) { // case 1 in TabsPagerAdapter
		// PointsFragment.setListItem();
			Intent intent = new Intent();
			intent.setAction("testAction");
			sendBroadcast(intent);
		}
		viewPager.setCurrentItem(tab.getPosition());
	}

	@Override
	public void onTabUnselected(Tab tab, android.app.FragmentTransaction ft) {
	}

	@Override
	public void onTabReselected(Tab tab, android.app.FragmentTransaction ft) {
		if (tab.getPosition() == 1) { // case 1 in TabsPagerAdapter
		// PointsFragment.setListItem();
			Intent intent = new Intent();
			intent.setAction("testAction");
			sendBroadcast(intent);
		}
		viewPager.setCurrentItem(tab.getPosition());
	}
}
