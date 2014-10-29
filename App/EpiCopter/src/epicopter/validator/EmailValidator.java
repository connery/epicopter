package epicopter.validator;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class EmailValidator implements ValidatorInterface {

	private static Pattern	pattern;
	private static Matcher	matcher;

	public EmailValidator() {
	}

	public static boolean validate(final String hex) {
		pattern = Pattern.compile(EMAIL_PATTERN);
		matcher = pattern.matcher(hex);
		return matcher.matches();
	}
}