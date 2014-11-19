package epicopter.database.local;

public class Point {

	private long	id;
	private long	id_vol;
	private double	latitude;
	private double	longitude;
	private double	hauteur;

	public Point() {
		this.id = -1;
		this.id_vol = -1;
		this.latitude = -1;
		this.longitude = -1;
		this.hauteur = -1;
	}

	public Point(double latitude, double longitude) {
		this.id = -1;
		this.id_vol = -1;
		this.latitude = latitude;
		this.longitude = longitude;
		this.hauteur = -1;
	}

	public Point(double latitude, double longitude, double hauteur) {
		this.id = -1;
		this.id_vol = -1;
		this.latitude = latitude;
		this.longitude = longitude;
		this.hauteur = hauteur;
	}

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

	public double getLatitude() {
		return latitude;
	}

	public void setLatitude(double latitude) {
		this.latitude = latitude;
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

	public String toString() {
		return latitude + ";" + longitude + ";" + hauteur;
	}

	public String toStringPerso() {
		return "-- id:" + id + "- -id_vol:" + id_vol + "- -altitude:" + latitude + "- -longitude:" + longitude + "- -hauteur:" + hauteur + "--";
	}
}
