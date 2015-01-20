package epicopter.database.local;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class VolsDBAdapter {

	// Database fields
	public static final String	TABLE_VOLS					= "vols";
	public static final String	COLUMN_ID					= "_id";
	public static final int		NUM_COLUMN_ID				= 0;
	public static final String	COLUMN_NAME					= "_name";
	public static final int		NUM_COLUMN_NAME				= 1;
	public static final String	COLUMN_USER_NAME			= "_username";
	public static final int		NUM_COLUMN_USER_NAME		= 2;
	public static final String	COLUMN_PICTURE				= "_picture";
	public static final int		NUM_COLUMN_PICTURE			= 3;
	public static final String	COLUMN_VIDEO				= "_video";
	public static final int		NUM_COLUMN_VIDEO			= 4;
	public static final String	COLUMN_MILLI_SECOND			= "_milli_second";
	public static final int		NUM_COLUMN_MILLI_SECOND		= 5;
	public static final String	COLUMN_NUMBER_OF_TRIP		= "_number_of_trip";
	public static final int		NUM_COLUMN_NUMBER_OF_TRIP	= 6;

	// Database fields
	private SQLiteDatabase		db;
	private SQLiteManager		dbManager;
	private String[]			allColumns					= { COLUMN_ID, COLUMN_NAME, COLUMN_USER_NAME, COLUMN_PICTURE, COLUMN_VIDEO, COLUMN_MILLI_SECOND,
			COLUMN_NUMBER_OF_TRIP							};

	public VolsDBAdapter(Context context) {
		dbManager = new SQLiteManager(context);
	}

	public void open() throws SQLException {
		db = dbManager.getWritableDatabase();
	}

	public void close() {
		dbManager.close();
	}

	/**
	 * 
	 * @param picture
	 *            1 to take picture else 0
	 * @param video
	 *            1 to take video alse 0
	 * @return
	 */
	public Vol insertVol(String name, String userName, int picture, int video, long millisecond, int numberOfTrip) {
		ContentValues values = new ContentValues();
		values.put(COLUMN_NAME, name);
		values.put(COLUMN_USER_NAME, userName);
		values.put(COLUMN_PICTURE, picture);
		values.put(COLUMN_VIDEO, video);
		values.put(COLUMN_MILLI_SECOND, millisecond);
		values.put(COLUMN_NUMBER_OF_TRIP, numberOfTrip);

		long insertId = db.insert(TABLE_VOLS, null, values);
		Cursor cursor = db.query(TABLE_VOLS, allColumns, COLUMN_ID + " = " + insertId, null, null, null, null);
		cursor.moveToFirst();
		Vol newVol = cursorToVol(cursor);
		cursor.close();
		return newVol;
	}

	public void deleteVol(Vol vol) {
		long id = vol.getId();
		db.delete(TABLE_VOLS, COLUMN_ID + " = " + id, null);

		System.out.println("Vol deleted with id: " + id);
	}

	public void deleteVol(int idVol) {
		db.delete(TABLE_VOLS, COLUMN_ID + " = " + idVol, null);

		System.out.println("Vol deleted with id: " + idVol);
	}

	public List<Vol> getAllVols(String userName) {
		List<Vol> vols = new ArrayList<Vol>();

		Cursor cursor = db.query(TABLE_VOLS, allColumns, COLUMN_USER_NAME + " = '" + userName + "'", null, null, null, null);

		cursor.moveToFirst();
		while (!cursor.isAfterLast()) {
			Vol vol = cursorToVol(cursor);
			vols.add(vol);
			cursor.moveToNext();
		}
		cursor.close();
		return vols;
	}

	public Vol getVolById(long id) {
		Cursor cursor = db.query(TABLE_VOLS, allColumns, COLUMN_ID + " = " + id, null, null, null, null);

		cursor.moveToFirst();
		Vol vol = cursorToVol(cursor);
		cursor.close();

		return vol;
	}

	public Vol getLastVol(String userName) {
		Cursor cursor = db.query(TABLE_VOLS, allColumns, COLUMN_USER_NAME + " = '" + userName + "'", null, null, null, COLUMN_ID + " DESC LIMIT 1");

		cursor.moveToFirst();
		Vol vol = cursorToVol(cursor);
		cursor.close();

		return vol;
	}

	private Vol cursorToVol(Cursor cursor) {
		if (cursor.getCount() != 0) {
			Vol vol = new Vol();
			vol.setId(cursor.getLong(NUM_COLUMN_ID));
			vol.setName(cursor.getString(NUM_COLUMN_NAME));
			vol.setUserName(cursor.getString(NUM_COLUMN_USER_NAME));
			vol.setPicture(cursor.getInt(NUM_COLUMN_PICTURE));
			vol.setVideo(cursor.getInt(NUM_COLUMN_VIDEO));
			vol.setMillisecond(cursor.getLong(NUM_COLUMN_MILLI_SECOND));
			vol.setNumberOfTrip(cursor.getInt(NUM_COLUMN_NUMBER_OF_TRIP));
			return vol;
		}
		return null;
	}
}
