package epicopter.database.local;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class VolsDBAdapter {

	// Databse fields
	public static final String	TABLE_VOLS		= "vols";
	public static final String	COLUMN_ID		= "_id";
	public static final String	COLUMN_PICTURE	= "_picture";
	public static final String	COLUMN_VIDEO	= "_video";

	// Database fields
	private SQLiteDatabase		db;
	private SQLiteManager		dbManager;
	private String[]			allColumns		= { COLUMN_ID, COLUMN_PICTURE, COLUMN_VIDEO };

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
	public Vol createVol(int picture, int video) {
		ContentValues values = new ContentValues();
		values.put(COLUMN_PICTURE, picture);
		values.put(COLUMN_VIDEO, video);

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

	public List<Vol> getAllVols() {
		List<Vol> vols = new ArrayList<Vol>();

		Cursor cursor = db.query(TABLE_VOLS, allColumns, null, null, null, null, null);

		cursor.moveToFirst();
		while (!cursor.isAfterLast()) {
			Vol vol = cursorToVol(cursor);
			vols.add(vol);
			cursor.moveToNext();
		}
		cursor.close();
		return vols;
	}

	private Vol cursorToVol(Cursor cursor) {
		Vol vol = new Vol();
		vol.setId(cursor.getLong(0));
		vol.setPicture(cursor.getInt(1));
		vol.setVideo(cursor.getInt(2));
		return vol;
	}
}
