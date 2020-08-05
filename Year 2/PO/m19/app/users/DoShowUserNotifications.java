package m19.app.users;
import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import m19.core.Notification;
import m19.app.exception.NoSuchUserException;
import m19.core.User;

/**
 * 4.2.3. Show notifications of a specific user.
 */
public class DoShowUserNotifications extends Command<LibraryManager> {

  private Input<Integer> _userId;

  /**
   * @param receiver
   */
  public DoShowUserNotifications(LibraryManager receiver) {
    super(Label.SHOW_USER_NOTIFICATIONS, receiver);
    _userId = _form.addIntegerInput(Message.requestUserId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    _form.parse();
    if (_receiver.getUser(_userId.value()) == null){
      throw new NoSuchUserException(_userId.value()); 
    }
    for(int j = 0;j <_receiver.getUser(_userId.value()).getNotifications().size();j++){
      _display.add(_receiver.getUser(_userId.value()).getNotifications().get(j).getMessage());
    }
    _receiver.getUser(_userId.value()).removeNotifications();
    _display.display(true);
  }
}