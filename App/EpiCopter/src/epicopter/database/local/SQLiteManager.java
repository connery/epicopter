package epicopter.database.local;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class SQLiteManager extends SQLiteOpenHelper {

	private static final String	DATABASE_NAME		= "epicopter.db";
	private static final int	DATABASE_VERSION	= 3;

	private static final String	CREATE_TABLE_POINTS	= 
			"CREATE TABLE " + PointsDBAdapter.TABLE_POINTS	+ "(" 
					+ PointsDBAdapter.COLUMN_ID				+ " INTEGER PRIMARY KEY AUTOINCREMENT, "  
					+ PointsDBAdapter.COLUMN_ID_VOL			+ " INTEGER NOT NULL, " 
					+ PointsDBAdapter.COLUMN_LATITUDE		+ " DOUBLE NOT NULL, " 
					+ PointsDBAdapter.COLUMN_LONGITUDE		+ " DOUBLE NOT NULL, " 
					+ PointsDBAdapter.COLUMN_HAUTEUR		+ " DOUBLE NOT NULL);";

	private static final String CREATE_TABLE_VOLS = 
			"CREATE TABLE " + VolsDBAdapter.TABLE_VOLS		+ "(" 
					+ VolsDBAdapter.COLUMN_ID				+ " INTEGER PRIMARY KEY AUTOINCREMENT, " 
					+ VolsDBAdapter.COLUMN_NAME				+ " TEXT NOT NULL, "
					+ VolsDBAdapter.COLUMN_PICTURE			+ " INTEGER NOT NULL, " 
					+ VolsDBAdapter.COLUMN_VIDEO			+ " INTEGER NOT NULL);";

	public SQLiteManager(Context context) {
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
	}

	@Override
	public void onCreate(SQLiteDatabase database) {
		database.execSQL(CREATE_TABLE_POINTS);
		database.execSQL(CREATE_TABLE_VOLS);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		Log.w(SQLiteManager.class.getName(), "Upgrading database from version " + oldVersion + " to " + newVersion + ", which will destroy all old data");

		db.execSQL("DROP TABLE IF EXISTS " + PointsDBAdapter.TABLE_POINTS + ";");
		db.execSQL("DROP TABLE IF EXISTS " + VolsDBAdapter.TABLE_VOLS + ";");

		onCreate(db);
	}

}
