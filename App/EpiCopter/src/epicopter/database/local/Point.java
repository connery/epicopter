package epicopter.database.local;

public class Point {

	private long	id;
	private long	id_vol;
	private double	altitude;
	private double	longitude;
	private double	hauteur;

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public long getId_vol() {
		return id_vol;
	}

	public void setId_vol(long id_vol) {
		this.id_vol = id_vol;
	}

	public double getAltitude() {
		return altitude;
	}

	public void setAltitude(double altitude) {
		this.altitude = altitude;
	}

	public double getLongitude() {
		return longitude;
	}

	public void setLongitude(double longitude) {
		this.longitude = longitude;
	}

	public double getHauteur() {
		return hauteur;
	}

	public void setHauteur(double hauteur) {
		this.hauteur = hauteur;
	}

	// Will be used by the ArrauAdapter in the Listview
	public String toString() {
		return "-- id:" + id + "- -id_vol:" + id_vol + "- -altitude:" + altitude + "- -longitude:" + longitude + "- -hauteur:" + hauteur + "--";
	}
}
