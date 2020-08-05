package m19.app.users;
import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import m19.core.User;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
/**
 * 4.2.4. Show all users.
 */
public class DoShowBigFine extends Command<LibraryManager> {

  /**
   * @param receiver
   */
  public DoShowBigFine(LibraryManager receiver) {
    super(Label.BIG_FINE, receiver);
  }
  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    List<User> list = _receiver.getAllUsers();
    int biggestfine = 0;
    int numberOfFines = 0;
    int utenteId = 0;
    for (int i = 0;i < list.size() ; i++ ) {
      if (list.get(i).getFine() > biggestfine){
        utenteId = list.get(i).getId();
        biggestfine = list.get(i).getFine();
      }
      if (list.get(i).getFine() > 0){
        numberOfFines++;
      }
    }
    _display.popup("Utentes com dívida: "+numberOfFines+"\nUtente com maior dívida: "+ utenteId);
    }
  }