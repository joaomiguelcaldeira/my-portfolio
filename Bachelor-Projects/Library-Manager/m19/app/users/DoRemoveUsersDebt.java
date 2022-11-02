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
public class DoRemoveUsersDebt extends Command<LibraryManager> {

  private Input<Integer> _fineMax;

  /**
   * @param receiver
   */
  public DoRemoveUsersDebt(LibraryManager receiver) {
    super(Label.USER_DEBT, receiver);
    _fineMax = _form.addIntegerInput(Message.requestMaxFine());
  }
  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    _form.parse();
    List<User> list = _receiver.getAllUsers();
    for (int i = 0 ; i < list.size() ; i++ ) {
      if (list.get(i).getFine() > _fineMax.value() && ( list.get(i).getUserWorks().size() == 0 )){
        _receiver.removeUser(list.get(i).getId());
      }
    }
  }
}