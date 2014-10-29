package epicopter.interfaces;

public interface LoginInterface {

	static final int	LOGIN			= 0;
	static final int	INSCRIPTION		= 1;
	static final int	FORGOTPASSWORD	= 2;
	static final int	SUCCESS			= 3;
	static final int	SETTINGS		= 4;
	static final int	FRAGMENT_COUNT	= SETTINGS + 1;

	static final String	TRUE			= "1";
	static final String	FALSE			= "0";
}
