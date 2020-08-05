package m19.core;
public class Book extends Work {
	private final String _author;
	private final int _isbn;


	public Book(String type,String title,String author,int price,Category category,int isbn,int numberOfCopies) {
		super(type,price,title,category, numberOfCopies);
		_author = author;
		_isbn = isbn;
	}

	public String toString() {
		return getId() + " - " + (getNumberOfCopies() - getNumberOfRequested()) + " de  " + getNumberOfCopies() + " - " + "Livro" + " - " + getTitle() + " - " + getPrice() + " - " + getCategory() + " - " + _author + " - " + _isbn + "\n";
	}
	
	@Override
	public String getDescription() {
		return toString();

	}

	@Override
	public String getCreator() {
		return _author;
	}
	
	public int getIsbn() {
		return _isbn;
	}

}
