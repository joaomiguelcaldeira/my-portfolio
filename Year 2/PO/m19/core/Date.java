package m19.core;
import java.io.Serializable;
public class Date implements Serializable {
	private static final long serialVersionUID = 201901101348L;
	private int _currentDate;

	public Date() {
		_currentDate = 0;
	}
	
	protected int getCurrentDate() {
		return _currentDate;
	}

	protected void advanceDay(int nDays) {
		_currentDate += nDays;
	}
}