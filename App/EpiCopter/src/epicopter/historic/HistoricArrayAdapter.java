package epicopter.historic;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import epicopter.database.local.Vol;
import epicopter.main.R;

public class HistoricArrayAdapter extends ArrayAdapter<Vol> {

	private final Context	context;
	private final List<Vol>	values;

	public HistoricArrayAdapter(Context context, List<Vol> values) {
		super(context, R.layout.listview_trip_item, values);
		this.context = context;
		this.values = values;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View rowView = inflater.inflate(R.layout.listview_trip_item, parent, false);

		TextView textView = (TextView) rowView.findViewById(R.id.tripInformation);
		textView.setText(values.get(position).getName());

		return rowView;
	}

	@Override
	public int getCount() {
		return values.size();
	}

	@Override
	public Vol getItem(int position) {
		return values.get(position);
	}
}