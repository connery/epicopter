package epicopter.welcome;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
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
			viewHolder.tvHeight = (TextView) convertView.findViewById(R.id.tvHeight);
			;
			convertView.setTag(viewHolder);
		} else {
			// recycle the already inflated view
			viewHolder = (ViewHolder) convertView.getTag();
		}
		// update the item view
		ListViewPoint item;
		item = getItem(position);
		viewHolder.ivIcon.setImageDrawable(item.icon);
		viewHolder.tvLatitude.setText(convertView.getResources().getString(R.string.latitude) + item.latitude);
		viewHolder.tvLongitude.setText(convertView.getResources().getString(R.string.longitude) + item.longitude);
		viewHolder.tvHeight.setText(item.height);

		buttonAction(convertView, item, viewHolder);

		return convertView;
	}

	private void buttonAction(View convertView, final ListViewPoint item, final ViewHolder viewHolder) {
		Button btnMinus = (Button) convertView.findViewById(R.id.btnMinus);
		Button btnPlus = (Button) convertView.findViewById(R.id.btnPlus);
		btnPlus.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				item.height = String.valueOf(Double.valueOf(item.height) + 1);
				viewHolder.tvHeight.setText(item.height);
				GoogleMapsFragment.updateListOfPoint(Double.valueOf(item.latitude), Double.valueOf(item.longitude), Double.valueOf(item.height));
			}
		});
		btnMinus.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				item.height = String.valueOf(Double.valueOf(item.height) - 1);
				viewHolder.tvHeight.setText(item.height);
				GoogleMapsFragment.updateListOfPoint(Double.valueOf(item.latitude), Double.valueOf(item.longitude), Double.valueOf(item.height));
			}
		});
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
