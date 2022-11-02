package m19.core;

import java.util.Collections;
import java.io.Serializable;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.Arrays;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import m19.core.exception.MissingFileAssociationException;
import m19.core.exception.BadEntrySpecificationException;
import m19.core.exception.ImportFileException;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
/**
 * The façade class.
 */
public class LibraryManager implements Serializable {
  private static final long serialVersionUID = 201901101348L;
  private Library _library;
  private String _filename;

  public LibraryManager() {
    _library = new Library();
  }

  public String getFilename() {
    return _filename;
  }
  
  public void setFileName(String filename) {
      _filename = filename;
    }
  /**
   * Serialize the persistent state of this application.
   * 
   * @throws MissingFileAssociationException if the name of the file to store the persistent
   *         state has not been set yet.
   * @throws IOException if some error happen during the serialization of the persistent state

   */
  
  public void save() throws MissingFileAssociationException, IOException {
    FileOutputStream novofile = new FileOutputStream(_filename);
    ObjectOutputStream outp = new ObjectOutputStream(novofile);
    outp.writeObject(_library);
    outp.close();
    novofile.close();   
  }

  /**
   * Serialize the persistent state of this application into the specified file.
   * 
   * @param filename the name of the target file
   *
   * @throws MissingFileAssociationException if the name of the file to store the persistent
   *         is not a valid one.
   * @throws IOException if some error happen during the serialization of the persistent state
   */
  public void saveAs(String filename) throws MissingFileAssociationException, IOException {
    FileOutputStream novofile = new FileOutputStream(filename);
    ObjectOutputStream outp = new ObjectOutputStream(novofile);
    outp.writeObject(_library);
    outp.close();
    novofile.close();
  }

  /**
   * Recover the previously serialized persitent state of this application.
   * 
   * @param filename the name of the file containing the perssitente state to recover
   *
   * @throws IOException if there is a reading error while processing the file
   * @throws FileNotFoundException if the file does not exist
   * @throws ClassNotFoundException 
   */
  public void load(String filename) throws FileNotFoundException, IOException, ClassNotFoundException {
    FileInputStream file = new FileInputStream(filename);
    ObjectInputStream inp = new ObjectInputStream(file);
    Library nova = (Library) inp.readObject();
    _library = nova;
    _filename = filename;
    inp.close();
    file.close();
  }

  /**
   * Set the state of this application from a textual representation stored into a file.
   * 
   * @param datafile the filename of the file with the textual represntation of the state of this application.
   * @throws ImportFileException if it happens some error during the parsing of the textual representation.
   */
  public void importFile(String datafile) throws ImportFileException {
    try {
      _library.importFile(datafile);
    } catch (IOException | BadEntrySpecificationException e) {
      throw new ImportFileException(e);
    }
  }
  
  public int registerUser(String name, String email) {
    if (name != null && email != null && !name.isEmpty() && !email.isEmpty()) {
      User user = new User(name,email);
      user.setId(_library.getNextUserId());
      _library.register(user);
      return _library.getUserId(user);
    }
    return -1;
   
  }

  public int getCurrentDate() {
    return _library.getCurrentDate();
  }
  
  public void advanceDays(int nDays) {
    if (nDays > 0) {
      _library.advanceDay(nDays);  
    }
  }
  
  public User getUser(int id) {
    return _library.getUser(id);
  }

  public Work getWork(int id) {
    return _library.getWork(id);
  }
  
  public int nextUserId() {
    return _library.getNextUserId();
  }
  
  public int getId(User _user) {
    return _library.getUserId(_user);
  }
  
  public String getUserDescription(int id) {
    return _library.getUserDescription(id);
  }
  
  public int getSizeUsers() {
    return _library.getSizeUsers();
  }
  
  public int getSizeWorks() {
    return _library.getSizeWorks();
  }
  
  public String getWorkDescription(int id) {
    Work work = _library.getWork(id);
    return work.getDescription();
  }

  public List<User> getAllUsers() {;
    List<User> list = _library.getAllUsers();
    Collections.sort(list);
    return list;
  }

  public List<Work> getAllWorks() {
    return _library.getAllWorks();
  }

  public String getUserName(int id) {
    User user = _library.getUser(id);
    return user.getName();
  }

  public String getWorkCreator(Work work) {
    return work.getCreator();
  }
  
  public String getWorkTitle(Work work) {
    return work.getTitle();
  }
  
  public int requestWork(User user,Work work) {
    return _library.requestWork(user,work);
  }

  public int verificaRules(int workId,int userId) {
    return _library.verificaRules(workId,userId);
  }

  public boolean checkRequested(int userid,int workid) {
    return _library.checkRequested(userid,workid);
  }

  public int returnWork(int userid,int workid) {
    return _library.returnWork(userid,workid);
  }
  
  public void userRedemption(int userid) {
    _library.userRedemption(userid);
  }

  public boolean maxRegists(){
    return _library.maxRegists();
  }

  public void removeUser(int id){
    _library.removeUser(id);
  }
  
}