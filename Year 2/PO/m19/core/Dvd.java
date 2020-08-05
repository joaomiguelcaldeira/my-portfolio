package m19.core;
public class Dvd extends Work {
	private final String _director;
	private final int _igac;

	public Dvd(String type,String title,String director,int price,Category category,int igac,int numberOfCopies) {
		super(type,price,title,category, numberOfCopies);
		_director = director;
		_igac = igac;
	}
	public String toString(){
		return getId() + " - " + (getNumberOfCopies() - getNumberOfRequested()) + " de  " + getNumberOfCopies() + " - " + getType() + " - " + getTitle() + " - " + getPrice() + " - " + getCategory() + " - " + _director + " - " + _igac + "\n";
	}
	
	@Override
	public String getDescription() {
		return toString();
	}
	
	@Override
	public String getCreator() {
		return _director;
	}
	public int getIgac() {
		return _igac;
	}

}