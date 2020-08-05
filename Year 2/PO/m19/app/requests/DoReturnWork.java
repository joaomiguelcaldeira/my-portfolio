package m19.app.requests;
import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import m19.app.exception.NoSuchUserException;
import m19.app.exception.NoSuchWorkException;
import m19.app.exception.WorkNotBorrowedByUserException;
import m19.core.User;
import pt.tecnico.po.ui.Form;
/**
 * 4.4.2. Return a work.
 */
public class DoReturnWork extends Command<LibraryManager> {

  private Input<Integer> _userId;
  private Input<Integer> _workId;
  private Input<String> _answer;
  /**
   * @param receiver
   */
  public DoReturnWork(LibraryManager receiver) {
    super(Label.RETURN_WORK, receiver);
    _userId = _form.addIntegerInput(Message.requestUserId());
    _workId = _form.addIntegerInput(Message.requestWorkId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    _form.parse();
    if (_receiver.getUser(_userId.value()) == null) {
      throw new NoSuchUserException(_userId.value()); 
    }
    if (_receiver.getWork(_workId.value()) == null) {
      throw new NoSuchWorkException(_workId.value());
    }
    else {
      if(_receiver.checkRequested(_userId.value(),_workId.value())) {
        int n = _receiver.returnWork(_userId.value(),_workId.value());
        if (n > 0) {
          _display.popup(Message.showFine(_userId.value(), n + _receiver.getUser(_userId.value()).getFine()));
          Form fine = new Form();
          _answer = fine.addStringInput(Message.requestFinePaymentChoice());
          fine.parse();
          if (_answer.value().equals("s")) {
            _receiver.userRedemption(_userId.value());
          }
          else {
            _receiver.getUser(_userId.value()).updateFine(n);
          }
        }
      }
      else {
        throw new WorkNotBorrowedByUserException(_workId.value(),_userId.value());
      } 
    }
  }
}