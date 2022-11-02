package m19.app.works;

import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Command;
import m19.app.exception.NoSuchWorkException;

/**
 * 4.3.1. Display work.
 */
public class DoDisplayWork extends Command<LibraryManager> {

  private Input<Integer> _id;

  /**
   * @param receiver
   */
  public DoDisplayWork(LibraryManager receiver) {
    super(Label.SHOW_WORK, receiver);
    _id = _form.addIntegerInput(Message.requestWorkId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    try{
    _form.parse();
    int id = _id.value();
    _display.popup(_receiver.getWorkDescription(id));
    }
    catch(NullPointerException e){
      throw new NoSuchWorkException(_id.value());
    }
  }  
}
