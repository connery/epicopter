package epicopter.welcome;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.util.Log;

public class TabsPagerAdapter extends FragmentPagerAdapter {

	// Number of item
	final int	PAGE_COUNT	= 3;

	public TabsPagerAdapter(FragmentManager fragmentManager) {
		super(fragmentManager);
	}

	@Override
	public Fragment getItem(int index) {
		switch (index) {
		case 0:
			Log.e("CAS 0", "GOOGLE MAP CREATED");
			return new GoogleMapsFragment();
		case 1:
			Log.e("CAS 1", "HOME FRAGMENTS CREATED");
			return new HomeFragment();
		case 2:
			Log.e("CAS 2", "POINTSFRAGMENTS CREATED");
			return new PointsFragment();
		}
		return null;
	}

	@Override
	public int getCount() {
		return PAGE_COUNT;
	}

}