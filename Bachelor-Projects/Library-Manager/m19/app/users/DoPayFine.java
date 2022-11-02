package m19.app.users;
import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import m19.core.User;
import m19.app.exception.NoSuchUserException;
import m19.app.exception.UserIsActiveException;

/**
 * 4.2.5. Settle a fine.
 */
public class DoPayFine extends Command<LibraryManager> {

  private Input<Integer> _userId;

  /**
   * @param receiver
   */
  public DoPayFine(LibraryManager receiver) {
    super(Label.PAY_FINE, receiver);
    _userId = _form.addIntegerInput(Message.requestUserId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    _form.parse();
    if (_receiver.getUser(_userId.value()) == null){
      throw new NoSuchUserException(_userId.value()); 
    }
    if(_receiver.getUser(_userId.value()).isActive()){
      throw new UserIsActiveException(_userId.value());
    }
    else{
      _receiver.getUser(_userId.value()).setFine(0);
      _receiver.userRedemption(_userId.value());
    }
  }
}