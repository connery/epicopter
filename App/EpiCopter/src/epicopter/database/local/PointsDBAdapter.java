package epicopter.database.local;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class PointsDBAdapter {

	// Databse fields
	public static final String	TABLE_POINTS			= "points";
	public static final String	COLUMN_ID				= "_id";
	public static final int		NUM_COLUMN_ID			= 0;
	public static final String	COLUMN_ID_VOL			= "_id_vol";
	public static final int		NUM_COLUMN_ID_VOL		= 1;
	public static final String	COLUMN_LATITUDE			= "_altitude";
	public static final int		NUM_COLUMN_LATITUDE		= 2;
	public static final String	COLUMN_LONGITUDE		= "_longitude";
	public static final int		NUM_COLUMN_LONGITUDE	= 3;
	public static final String	COLUMN_HAUTEUR			= "_hauteur";
	public static final int		NUM_COLUMN_HAUTEUR		= 4;

	// Database fields
	private SQLiteDatabase		db;
	private SQLiteManager		dbManager;
	private String[]			allColumns				= { COLUMN_ID, COLUMN_ID_VOL, COLUMN_LATITUDE, COLUMN_LONGITUDE, COLUMN_HAUTEUR };

	public PointsDBAdapter(Context context) {
		dbManager = new SQLiteManager(context);
	}

	public void open() throws SQLException {
		db = dbManager.getWritableDatabase();
	}

	public void close() {
		dbManager.close();
	}

	public Point insertPoint(long id_vol, double latitude, double longitude, double hauteur) {
		ContentValues values = new ContentValues();
		values.put(COLUMN_ID_VOL, id_vol);
		values.put(COLUMN_LATITUDE, latitude);
		values.put(COLUMN_LONGITUDE, longitude);
		values.put(COLUMN_HAUTEUR, hauteur);

		long insertId = db.insert(TABLE_POINTS, null, values);
		Cursor cursor = db.query(TABLE_POINTS, allColumns, COLUMN_ID + " = " + insertId, null, null, null, null);
		cursor.moveToFirst();
		Point newPoint = cursorToPoint(cursor);
		cursor.close();
		return newPoint;
	}

	public Point updatePoint(long id, double id_vol, double latitude, double longitude, double hauteur) {
		ContentValues values = new ContentValues();
		values.put(COLUMN_ID_VOL, id_vol);
		values.put(COLUMN_LATITUDE, latitude);
		values.put(COLUMN_LONGITUDE, longitude);
		values.put(COLUMN_HAUTEUR, hauteur);

		db.update(TABLE_POINTS, values, COLUMN_ID + " = " + id, null);
		Cursor cursor = db.query(TABLE_POINTS, allColumns, COLUMN_ID + " = " + id, null, null, null, null);
		cursor.moveToFirst();
		Point newPoint = cursorToPoint(cursor);
		cursor.close();
		return newPoint;
	}

	public Point updatePoint(double id, double hauteur) {
		ContentValues values = new ContentValues();
		values.put(COLUMN_HAUTEUR, hauteur);

		db.update(TABLE_POINTS, values, COLUMN_ID + " = " + id, null);
		Cursor cursor = db.query(TABLE_POINTS, allColumns, COLUMN_ID + " = " + id, null, null, null, null);
		cursor.moveToFirst();
		Point newPoint = cursorToPoint(cursor);
		cursor.close();
		return newPoint;
	}

	public void deletePoint(Point point) {
		long id = point.getId();
		db.delete(TABLE_POINTS, COLUMN_ID + " = " + id, null);

		System.out.println("Point deleted with id: " + id);
	}

	public List<Point> getAllPoints() {
		List<Point> points = new ArrayList<Point>();

		Cursor cursor = db.query(TABLE_POINTS, allColumns, null, null, null, null, null);

		cursor.moveToFirst();
		while (!cursor.isAfterLast()) {
			Point point = cursorToPoint(cursor);
			points.add(point);
			cursor.moveToNext();
		}
		cursor.close();
		return points;
	}
	
	public List<Point> getPointsByVolId(double id_vol) {
		List<Point> points = new ArrayList<Point>();

		Cursor cursor = db.query(TABLE_POINTS, allColumns, COLUMN_ID_VOL + " = " + id_vol, null, null, null, null);

		cursor.moveToFirst();
		while (!cursor.isAfterLast()) {
			Point point = cursorToPoint(cursor);
			points.add(point);
			cursor.moveToNext();
		}
		cursor.close();
		return points;
	}

	private Point cursorToPoint(Cursor cursor) {
		Point point = new Point();
		point.setId(cursor.getLong(NUM_COLUMN_ID));
		point.setId_vol(cursor.getLong(NUM_COLUMN_ID_VOL));
		point.setLatitude(cursor.getDouble(NUM_COLUMN_LATITUDE));
		point.setLongitude(cursor.getDouble(NUM_COLUMN_LONGITUDE));
		point.setHauteur(cursor.getDouble(NUM_COLUMN_HAUTEUR));
		return point;
	}

}
