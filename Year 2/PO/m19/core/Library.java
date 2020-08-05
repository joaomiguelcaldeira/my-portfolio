package m19.core;

import java.io.Serializable;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import m19.core.exception.MissingFileAssociationException;
import m19.core.exception.BadEntrySpecificationException;
import java.util.Iterator;

/**
 * Class that represents the library as a whole.
 */
public class Library implements Serializable {

  /** Serial number for serialization. */
  
  private static final long serialVersionUID = 201901101348L;
  private int _nextWorkId;
  private int _nextUserId;
  private Date _date;
  private HashMap<Integer,User> _users;
  private HashMap<Integer,Work> _works;
  private ArrayList<Request> _requests;
  private int _regists;
  public Library() {
    _date = new Date();
    _nextWorkId = -1;
    _nextUserId = -1;
    _users = new HashMap<Integer,User>();
    _works = new HashMap<Integer,Work>();
    _requests = new ArrayList<Request>();
    _regists = 0;
  }
  
  public Library getLibrary() {
    return this;
  }
  
  public int getNextUserId() {
    _nextUserId++;
    return _nextUserId;
  }
  
  public int getNextWorkId() {
    _nextWorkId++;
    return _nextWorkId;
  }
  
  public int getUserId(User _user) {
    return _user.getId();
  }
  
  public void removeUser(int id){
    _users.remove(Integer.valueOf(id));
  }

  public int getCurrentDate(){
    return _date.getCurrentDate();
  }

  public void advanceDay(int nDays) {
     _date.advanceDay(nDays);
     updateLibrary();
  }

  /**
   * Read the text input file at the beginning of the program and populates the
   * instances of the various possible types (books, DVDs, users).
   * 
   * @param filename
   *          name of the file to load
   * @throws BadEntrySpecificationException
   * @throws IOException
   */
  void importFile(String filename) throws BadEntrySpecificationException, IOException {
    Parser parser = new Parser(this);
    parser.parseFile(filename);

  }
  
  
  /**
  * Inserts in Hashmap.
  * @param user
  *         object of class User
  *
  */
  public boolean maxRegists(){
    return _regists <= 10;
  }

  public void register(User user) {
    _users.put(user.getId(),user);
    _regists++;
  }
  
  /**
  * Sets the user Id.
  * @param user
  *         object of class User
  *
  */  
  public void setId(User user) {
    user.setId(getNextUserId());
  }
  
  /**
  * gets description using get method to get the required user
  * @param id
  *         int id
  * @return String
  *         user atributes
  */
  
  public String getUserDescription(int id) {
     User user = _users.get(id);
    return user.getDescription();
  }
  
  /**
  * @return int 
  *         size of users Hashmap
  */
  
  public int getSizeUsers() {
    return _users.size();
  }
  
  /**
  * @return int 
  *         size of works Hashmap
  */
  
  public int getSizeWorks() {
    return _works.size();
  }
  
  /**
  * Sets the work Id.
  * @param wrk
  *         object of class Work
  *
  */

  public void setWorkID(Work wrk) {
    wrk.setWorkId(getNextWorkId());
  }

  /**
  * Inserts in Hashmap.
  * @param wrk
  *         object of class Work
  *
  */

  public void registerWork(Work wrk) {
    _works.put(wrk.getId(),wrk);
  }
  
  public List<User> getAllUsers() {
    List<User> list = new ArrayList<User>();
    for (int i = 0;i<_users.size() ;i++) {
      list.add(_users.get(i));
    }
    return list;
  }

  protected List<Work> getAllWorks() {
    List<Work> works = new ArrayList<Work>();
    for (int i = 0;i<_works.size() ;i++) {
      works.add(_works.get(i));
    }
    return works;
  }

  protected User getUser(int id) {
    return _users.get(id);
  }

  protected Work getWork(int id) {
    return _works.get(id);
  }

  public ArrayList<Request> getRequests() {
    return _requests;
  }

  public HashMap<Integer,Work> getWorks() {
    return _works;
  }

  public int deadlineCalculator(User user, Work work) { //calculates the deadline of delivery based on
    int numWorks = work.getNumberOfCopies();            // user behaviour and number of copies
    String userBehaviour = user.getUserBehaviour();
    if (userBehaviour.equals("FALTOSO")) {
      return getCurrentDate() + 2;
    }
    if (numWorks == 1){
      if (userBehaviour.equals("NORMAL")) {
        return getCurrentDate() + 3;
      }
      if (userBehaviour.equals("CUMPRIDOR")) {
        return getCurrentDate() + 8;
      }
    }
    if(numWorks <= 5 && numWorks > 1){
      if (userBehaviour.equals("NORMAL")) {
        return getCurrentDate() + 8;
      }
      if (userBehaviour.equals("CUMPRIDOR")) {
        return getCurrentDate() + 15;
      }
    }
    if(numWorks > 5) {
      if (userBehaviour.equals("NORMAL")) {
        return getCurrentDate() + 15;
      }
      if (userBehaviour.equals("CUMPRIDOR")) {
        return getCurrentDate() + 30;
      }
    }
    return 0;
  }
  
  public int requestWork(User user,Work work) {     // adds a request to the requests array 
  int workId = work.getId();                        // adds a workId to the user's "inventory"
  int userId = user.getId();
  int deadline = deadlineCalculator(user,work);
  Request _request = new Request(user,work,deadline);
  work.updateNumberOfRequested();
  user.addWork(workId);
  _requests.add(_request);
  for (User person : _users.values()) {
    for(int i = 0; i < person.getWantedWorks().size(); i++) {
      if (person.getWantedWorks().get(i) == workId) {
        Notification notif = new Notification("REQUISIÇÃO: " + work.getDescription());
        person.addNotificacao(notif);
      }
    }
  }
  return _request.getDeadLine();                    // returns the deadline to the DoRequestWork menu
  }

  public boolean checkRequested(int userid,int workid) {  
    for(int j = 0;j < _requests.size();j++){
      if(_requests.get(j).getUser().getId() == userid && _requests.get(j).getWork().getId() == workid) {
        return true;
      }
    }
    return false;
  }
  
  public int calculateWorkFine(int userid,int workid) {
    for(int j = 0;j < _requests.size();j++){
      if (_requests.get(j).getUser().getId() == userid && _requests.get(j).getWork().getId() == workid) {
       return 5*(getCurrentDate() - _requests.get(j).getDeadLine()); // fine based on the delay
      }
    }
    return -1; // no fine
  }
  
  public int returnWork(int userid,int workid) { //updates user's behaviour , "inventory" and score in the library 
    int deadline = 0;
    Work work = getWork(workid);
    User user = getUser(userid);
    work.removeRequest();   //updates the number of requested works with this id 
    int fine = calculateWorkFine(userid,workid);
    user.removeWork(workid);
    for(int j = 0;j < _requests.size();j++) {
      if (_requests.get(j).getUser().getId() == userid && _requests.get(j).getWork().getId() == workid) {
        deadline = _requests.get(j).getDeadLine();
        _requests.remove(_requests.get(j));
      }
    }
    if(getCurrentDate() <= deadline) {    // return within the established deadline
      if(user.getScore() >= 0) {
        user.updateScore(1);
      }
      if (user.getScore() < 0) {
        user.setScore(1);
      }
      if(user.getScore() == 3 && user.getUserBehaviour().equals("FALTOSO")){
        user.setBehaviour(0);
      }
      if(user.getScore() >= 5) {
        user.setBehaviour(1);
      }
    }
    if(getCurrentDate() > deadline) {   // return after the deadline
      if (user.getScore() <= 0){
        user.updateScore(-1);   
      }
      if(user.getScore() >= 5){
        user.setBehaviour(0);
      }
      if(user.getScore() > 0) {
        user.setScore(-1);
      }
      if(user.getScore() <= -3) {
        user.setBehaviour(2);
      }
    }
    for (User person : _users.values() ) {  // sends notifications to users that wanted this work
      for(int i = 0; i < person.getWantedWorks().size(); i++){
        if (person.getWantedWorks().get(i) == workid){
          Notification notif = new Notification("ENTREGA: " + work.getDescription());
          person.addNotificacao(notif);
          person.removeWantedWork(workid);
        }
      }
    }
    return fine;
  } 
  
  public int verificaRules(int workId,int userId) {   // rule verification for DoRequest
    Work work = getWork(workId);
    User user = getUser(userId);
    Rule _rule = new Rule(user,work,getLibrary());
    if (_rule.isRequested()){
      return 1;
    }
    if(_rule.isSuspended()){
      return 2;
    }
    if(_rule.allWorksRequested()){
      return 3;
    }
    if(_rule.canRequest()){
      return 4;
    }
    if(_rule.isReference()){
      return 5;
    }
    if(_rule.canRequestPrice()){
      return 6;
    }
    return 0; //SUCCESS
  }
  
  public void updateLibrary() {  //update the user's state if they have works that should already have been delivered
    for(int j = 0;j < _requests.size();j++){
      if(_requests.get(j).getDeadLine() < getCurrentDate()){
        _requests.get(j).getUser().badState();
        }
      }
    }
    
  public void userRedemption(int userid) { // only used after the user pays the fines
    boolean flag = true;
    for(int j = 0;j < _requests.size();j++){
      if (_requests.get(j).getUser().getId() == userid && _requests.get(j).getDeadLine() < getCurrentDate()) { 
        flag = false;    
      }
    }
    if(getUser(userid).getScore() >= 3 && getUser(userid).getScore() < 5 ) {
        getUser(userid).setBehaviour(0);  //set's behaviour to normal
      }
    if (flag) {
      getUser(userid).clearState();
    }
  }
}