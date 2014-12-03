package epicopter.validator;

public interface ValidatorInterface {

	// EMAIL VALIDATOR
	public static final String	EMAIL_PATTERN	= "^[a-zA-Z0-9._-]+@[a-zA-Z0-9._-]{2,}\\.[a-z]{2,4}$";

	// INTEGER VALIDATOR
	public static final String	INTEGER_PATTERN	= "^[0-9]{1,3}$";

	// STRING VALIDATOR
	public static final String	STRING_PATTERN	= "^[a-zA-Z0-9._ -ιθΰκλο]{2,}$";

	// DATE VALIDATOR
	// DD/MM/YYYY - DD/MM/YY - D/MM/YYYY - DD/M/YYYY - D/MM/YY - DD/M/YY
	// Work with "/", "." and "-"
	public static final String	DATE_PATTERN_FR	= "^(?:(?:31(\\/|-|\\.)(?:0?[13578]|1[02]))\\1|(?:(?:29|30)(\\/|-|\\.)(?:0?[1,3-9]|1[0-2])\\2))(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$|^(?:29(\\/|-|\\.)0?2\\3(?:(?:(?:1[6-9]|[2-9]\\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\\d|2[0-8])(\\/|-|\\.)(?:(?:0?[1-9])|(?:1[0-2]))\\4(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$";
}
