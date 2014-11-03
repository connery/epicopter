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
	public static final String	TABLE_VOLS			= "vols";
	public static final String	COLUMN_ID			= "_id";
	public static final int		NUM_COLUMN_ID		= 0;
	public static final String	COLUMN_PICTURE		= "_picture";
	public static final int		NUM_COLUMN_PICTURE	= 1;
	public static final String	COLUMN_VIDEO		= "_video";
	public static final int		NUM_COLUMN_VIDEO	= 2;

	// Database fields
	private SQLiteDatabase		db;
	private SQLiteManager		dbManager;
	private String[]			allColumns			= { COLUMN_ID, COLUMN_PICTURE, COLUMN_VIDEO };

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
	public Vol insertVol(int picture, int video) {
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

	public void deleteVol(int idVol) {
		db.delete(TABLE_VOLS, COLUMN_ID + " = " + idVol, null);

		System.out.println("Vol deleted with id: " + idVol);
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

	public Vol getLastVol() {
		Cursor cursor = db.query(TABLE_VOLS, allColumns, null, null, null, null, COLUMN_ID + " DESC LIMIT 1");

		cursor.moveToFirst();
		Vol vol = cursorToVol(cursor);
		cursor.close();

		return vol;
	}

	private Vol cursorToVol(Cursor cursor) {
		Vol vol = new Vol();
		vol.setId(cursor.getLong(NUM_COLUMN_ID));
		vol.setPicture(cursor.getInt(NUM_COLUMN_PICTURE));
		vol.setVideo(cursor.getInt(NUM_COLUMN_VIDEO));
		return vol;
	}
}
