package m19.core;
import java.io.Serializable;

public class Rule implements Serializable {
	private static final long serialVersionUID = 201901101348L;
	private User _user;
	private Work _work;
	private String _reference;
	private String _behaviour;
	private String _behaviourPrice;
	private Library _library;
	private boolean _isReference;
	private boolean _isSuspended;
	private boolean _canRequest;
	private boolean _worksAreAllRequested;
	private boolean _canRequestPrice;
	
	public Rule(User user , Work work, Library library) {
		_user = user;
		_work = work;
		_library = library;

	}
	
	public void setUser(User user) {
		_user = user;
	}
	
	public void setWork(Work work) {
		_work = work;
	}
	
	public boolean isReference() {
		String _reference = _work.getCategory();
		if (_reference.equals("Referência")) {
			_isReference = true;
			return _isReference;
		}
		return _isReference;
	}
	
	public boolean isRequested() { 
		int workId = _work.getId();
		int userId = _user.getId();
		return _library.checkRequested(userId,workId);		
	}
	
	public boolean isSuspended() {
		if(!_user.isActive()){
			_isSuspended = true;
		}
		return _isSuspended;
	}
	
	public boolean canRequest() { 
		int numOfRequests = _user.getUserWorks().size();
		_behaviour = _user.getUserBehaviour();
		if (_behaviour.equals("NORMAL")) {
			if (numOfRequests >= 3) {
				_canRequest = true;
				return _canRequest;
			}
		}
		else if (_behaviour.equals("CUMPRIDOR")) {
			if (numOfRequests >= 5) {
				_canRequest = true;
				return _canRequest;
			}
		}
		else if (numOfRequests >= 1) {  //FALTOSO
				_canRequest = true;
				return _canRequest;
		}
		return _canRequest;
	}
	
	public boolean allWorksRequested() {
		if(_work.getNumberOfRequested() == _work.getNumberOfCopies()) {
			_worksAreAllRequested = true;
		}
		return _worksAreAllRequested;				
	}
	
	public boolean canRequestPrice() {
		if (_work.getPrice() <= 25) {
			return _canRequestPrice;
		}
		else if (_user.getUserBehaviour().equals("CUMPRIDOR")) {
			return _canRequestPrice;
		}
		else {
			return true;
		}
	}
}