package epicopter.welcome;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

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
			return new GoogleMapsFragment();
		case 1:
			return new HomeFragment();
		case 2:
			return new ValiderFragment();
		}
		return null;
	}

	@Override
	public int getCount() {
		return PAGE_COUNT;
	}

}