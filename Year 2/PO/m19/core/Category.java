package m19.core;
public enum Category {
	REFERENCE("Referência"), FICTION("Ficção"), SCITECH("Técnica e Científica");
private String _value;
	
	Category(String value) {
  		_value = value;
 	}

	public String getValue() {
	  return _value;
	}
}