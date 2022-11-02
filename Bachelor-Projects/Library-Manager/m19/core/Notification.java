package m19.core;
import java.io.Serializable;

public class Notification implements Serializable {
	private static final long serialVersionUID = 201901101348L;
	private String _message;
	

	public Notification(String message) {
		_message = message;
	}
	
	public String getMessage() {
		return _message;
	}
}