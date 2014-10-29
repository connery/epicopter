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
	public static final String	TABLE_POINTS		= "points";
	public static final String	COLUMN_ID			= "_id";
	public static final String	COLUMN_ID_VOL		= "_id_vol";
	public static final String	COLUMN_ALTITUDE		= "_altitude";
	public static final String	COLUMN_LONGITUDE	= "_longitude";
	public static final String	COLUMN_HAUTEUR		= "_hauteur";

	// Database fields
	private SQLiteDatabase		db;
	private SQLiteManager		dbManager;
	private String[]			allColumns			= { COLUMN_ID, COLUMN_ID_VOL, COLUMN_ALTITUDE, COLUMN_LONGITUDE, COLUMN_HAUTEUR };

	public PointsDBAdapter(Context context) {
		dbManager = new SQLiteManager(context);
	}

	public void open() throws SQLException {
		db = dbManager.getWritableDatabase();
	}

	public void close() {
		dbManager.close();
	}

	public Point createPoint(double id_vol, double altitude, double longitude, double hauteur) {
		ContentValues values = new ContentValues();
		values.put(COLUMN_ID_VOL, id_vol);
		values.put(COLUMN_ALTITUDE, altitude);
		values.put(COLUMN_LONGITUDE, longitude);
		values.put(COLUMN_HAUTEUR, hauteur);

		long insertId = db.insert(TABLE_POINTS, null, values);
		Cursor cursor = db.query(TABLE_POINTS, allColumns, COLUMN_ID + " = " + insertId, null, null, null, null);
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

	public Point getByVolId(double id_vol) {
		Cursor cursor = db.query(TABLE_POINTS, allColumns, COLUMN_ID_VOL + " = " + id_vol, null, null, null, null);
		return cursorToPoint(cursor);
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

	private Point cursorToPoint(Cursor cursor) {
		Point point = new Point();
		point.setId(cursor.getLong(0));
		point.setId_vol(cursor.getLong(1));
		point.setAltitude(cursor.getDouble(2));
		point.setLongitude(cursor.getDouble(3));
		point.setHauteur(cursor.getDouble(4));
		return point;
	}

}
