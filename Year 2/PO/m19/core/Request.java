package m19.core;
import java.io.Serializable;

 
public class Request implements Serializable {
	private static final long serialVersionUID = 201901101348L;
	private int _deadline;
	private User _user;
	private Work _work;
	private boolean _flagPenalty; 
	
	public Request(User user, Work work,int deadline) {
		_user = user;
		_work = work;
		_deadline = deadline;
	}
	
	public User getUser	() {
		return _user;
	}

	public Work getWork() {
		return _work;
	}

	public int getDeadLine() {
		return _deadline;
	}
	
	protected void setDeadline(int deadline) {
		_deadline = deadline;
	}
	
	public boolean getFlag(){
		return _flagPenalty;
	}
	
	public void setFlag(boolean flag) {
		_flagPenalty = flag;
	}
}