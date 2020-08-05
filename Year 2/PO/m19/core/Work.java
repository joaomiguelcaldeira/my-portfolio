package m19.core;
import java.io.Serializable;

public abstract class Work implements Serializable{
	private static final long serialVersionUID = 201901101348L;
	private int _id;
	private int _price;
	private int _numberOfRequested;
	private final int _numberOfCopies;
	private final String _title;
	private final Category _category;
	private final String _type;

	public Work(String type, int price,String title, Category category, int numberOfCopies) {
		_type = type;
		_price = price;
		_title = title;
		_numberOfRequested = 0;
		_numberOfCopies = numberOfCopies;
		_category = category;
	}
	
	public void setWorkId(int id) {
		_id = id;
	}
	
	public int getId() {
		return _id;
	}
	
	public String getType() {
		return _type;
	}
	
	public int getNumberOfRequested() {
		return _numberOfRequested;
	}

	public void updateNumberOfRequested() {  // updates everytime a request takes place
		_numberOfRequested += 1;
	}
	
	public int getNumberOfCopies() {
		return _numberOfCopies;
	}
	
	public void removeRequest() {
		_numberOfRequested -= 1;
	}
	
	public int getPrice() {
		return _price;
	}
	
	public String getTitle() {
		return _title;
	}
	
	public String getCategory() {
		return _category.getValue();
	}
	
	public abstract String getDescription();

	public abstract String getCreator();
}