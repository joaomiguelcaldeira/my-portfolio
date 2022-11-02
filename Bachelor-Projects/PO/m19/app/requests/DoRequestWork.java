package m19.app.requests;

import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import m19.core.Rule;
import m19.app.exception.NoSuchUserException;
import m19.app.exception.NoSuchWorkException;
import m19.app.exception.RuleFailedException;
import m19.core.Notification;
import m19.core.User;
import pt.tecnico.po.ui.Form;

/**
 * 4.4.1. Request work.
 */
public class DoRequestWork extends Command<LibraryManager> {

  private Input<Integer> _userId;
  private Input<Integer> _workId;
  private Input<String> _answer;

  /**
   * @param receiver
   */
  public DoRequestWork(LibraryManager receiver) {
    super(Label.REQUEST_WORK, receiver);
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
      int n = _receiver.verificaRules(_workId.value(),_userId.value());
      if (n == 0) {
        int deadline = _receiver.requestWork(_receiver.getUser(_userId.value()),_receiver.getWork(_workId.value()));
        _display.popup(Message.workReturnDay(_workId.value(),deadline));
      }
      if(n > 0 && n != 3) {
        throw new RuleFailedException(_userId.value(),_workId.value(),n);
      }
      if(n == 3) {
        Form ans = new Form();
        _answer = ans.addStringInput(Message.requestReturnNotificationPreference());
        ans.parse();
        if (_answer.value().equals("s")) {
         _receiver.getUser(_userId.value()).addWantedWork(_workId.value());
        }
      } 
    }
  }
}