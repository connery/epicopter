package epicopter.database;

public interface DataBaseInterface {

	/**
	 * PHP script location
	 */
	public static final String	URL_LOGIN		= "http://catchme.fr/Help/login.php";
	public static final String	URL_ADD_USER	= "http://catchme.fr/Help/addUser.php";
	public static final String	URL_EMAIL		= "http://catchme.fr/Help/mail.php";

	/**
	 * JSON element ids from response of PHP script
	 */
	public static final String	TAG_SUCCESS		= "success";
	public static final String	TAG_MESSAGE		= "message";
}
