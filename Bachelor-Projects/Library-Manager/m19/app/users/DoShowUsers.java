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
public class DoShowUsers extends Command<LibraryManager> {

  /**
   * @param receiver
   */
  public DoShowUsers(LibraryManager receiver) {
    super(Label.SHOW_USERS, receiver);
  }
  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    List<User> list = _receiver.getAllUsers();
    for (int i = 0;i < list.size() ;i++ ) {
      _display.add(_receiver.getUserDescription(_receiver.getId(list.get(i))));
    }
    _display.display(true);
    }
  }

