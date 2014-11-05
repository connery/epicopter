package epicopter.welcome;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import epicopter.main.R;

public class ListViewPointAdapter extends ArrayAdapter<ListViewPoint> {

	public ListViewPointAdapter(Context context, List<ListViewPoint> items) {
		super(context, R.layout.listview_points_item, items);
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		ViewHolder viewHolder;
		if (convertView == null) {
			// inflate the GridView item layout
			LayoutInflater inflater = LayoutInflater.from(getContext());
			convertView = inflater.inflate(R.layout.listview_points_item, parent, false);
			// initialize the view holder
			viewHolder = new ViewHolder();
			viewHolder.ivIcon = (ImageView) convertView.findViewById(R.id.ivIcon);
			viewHolder.tvLatitude = (TextView) convertView.findViewById(R.id.tvLatitude);
			viewHolder.tvLongitude = (TextView) convertView.findViewById(R.id.tvLongitude);
			viewHolder.tvHeight = (TextView) convertView.findViewById(R.id.tvHeight);;
			convertView.setTag(viewHolder);
		} else {
			// recycle the already inflated view
			viewHolder = (ViewHolder) convertView.getTag();
		}
		// update the item view
		ListViewPoint item = getItem(position);
		viewHolder.ivIcon.setImageDrawable(item.icon);
		viewHolder.tvLatitude.setText(viewHolder.tvLatitude.getText() + item.latitude);
		viewHolder.tvLongitude.setText(viewHolder.tvLongitude.getText() + item.longitude);
		viewHolder.tvHeight.setText(viewHolder.tvHeight.getText() + item.height);
		return convertView;
	}

	/**
	 * The view holder design pattern prevents using findViewById() repeatedly in the getView() method of the adapter.
	 * 
	 * @see http://developer.android.com/training/improving-layouts/smooth-scrolling.html#ViewHolder
	 */
	private static class ViewHolder {
		ImageView	ivIcon;
		TextView	tvLatitude;
		TextView	tvLongitude;
		TextView	tvHeight;
	}
}
