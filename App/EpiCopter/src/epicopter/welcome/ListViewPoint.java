package epicopter.welcome;

import android.graphics.drawable.Drawable;

public class ListViewPoint {
	public final Drawable	icon;			// the drawable for the ListView item ImageView
	public final String		latitude;			// the text for the ListView item title
	public final String		longitude;	// the text for the ListView item description
	public final String		height;			// the text for the ListView item height

	public ListViewPoint(Drawable icon, String title, String description, String height) {
		this.icon = icon;
		this.latitude = title;
		this.longitude = description;
		this.height = height;
	}
}
