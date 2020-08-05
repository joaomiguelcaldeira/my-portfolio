package m19.core;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
public class User implements Serializable,Comparable<User> {
	private static final long serialVersionUID = 201901101348L;
	private int _id;
	private boolean _isActive;
	private String _name;
	private String _email;
	private UserBehaviour _behaviour;
	private ArrayList<Integer> _works;
	private ArrayList<Notification> _notifications;
	private ArrayList<Integer> _wantedWorks;
	private int _fine;
	private int _score;
	
	public User(String name,String email) {  /*id atribuido automaticamente de forma incremental */
		_name = name;
		_email = email;
		_isActive = true;
		_behaviour = UserBehaviour.values()[0];		
		_works = new ArrayList<Integer>();
		_notifications = new ArrayList<Notification>();
		_wantedWorks = new ArrayList<Integer>();			
	}
	
	public int getScore() {
		return _score;
	}
	
	public void updateScore(int points) {
		_score += points;
	}
	
	public void setScore(int newscore) {
		_score = newscore;
	}
	
	public void setBehaviour(int value) {
		_behaviour = UserBehaviour.values()[value];
	}
	
	public int getId() {
		return _id;
	}
	
	public void setId(int id) {
		_id = id;
	}
	
	public boolean isActive() {
		return _isActive;
	}
	
	public void badState() {
		_isActive = false;
	}
	
	public void clearState() {
		_isActive = true;
	}
	
	public String toString() {
    String ativo; 
    	if (isActive()){
    		ativo = "ACTIVO";
    		return _id + " - " + _name + " - " + _email + " - "+ _behaviour + " - " + ativo + "\n";
    	}
    	else{
    		ativo = "SUSPENSO";
    		return _id + " - " + _name + " - " + _email + " - "+ _behaviour + " - " + ativo + " - " + "EUR" +" "+_fine + "\n";
    	}
        
    } 
	
	public String getDescription() {
		return toString();
	}

	public String getName() {
		return _name;
	}

	public String getUserBehaviour() {
		return _behaviour.getValue();
	}

	public ArrayList<Integer> getUserWorks() {
		return _works;
	}
	
	public void addWork(int workid) {
		_works.add(workid);
	}
	
	public void removeWork(int workid) {
		_works.remove(Integer.valueOf(workid));
	}
	
	public int getFine(){
		return _fine;
	}
	
	public void updateFine(int cash) {
		_fine += cash;
	}
	
	public void setFine(int cash) {
		_fine = cash;
	}
	
	@Override
	public int compareTo(User user) {     // condition to sort for DoShowAllUsers
		for (int i=0;i < getName().length() && i < user.getName().length();i++) {
			if ((getName().charAt(i) - user.getName().charAt(i)) != 0) {
				return getName().charAt(i) - user.getName().charAt(i);
			}
		}
		return getId()- user.getId();
	}
	
	public void addWantedWork(int workid) {
		_wantedWorks.add(workid);
	}
	
	public void removeWantedWork(int workid){
		_wantedWorks.remove(Integer.valueOf(workid));
	}

	public ArrayList<Integer> getWantedWorks() {
		return _wantedWorks;
	}

	public void removeNotifications() {
		_notifications.removeAll(_notifications);
	}


	public void addNotificacao(Notification n) {
		_notifications.add(n);
	}
	
	public ArrayList<Notification> getNotifications() {
		return _notifications;
	}
}