package m19.core;
public enum UserBehaviour {
	NORMAL("NORMAL"),CUMPRIDOR("CUMPRIDOR"),FALTOSO("FALTOSO");
private String _value;
	
	UserBehaviour(String value) {
  		_value = value;
 	}

	public String getValue() {
	 	return _value;
	}
}