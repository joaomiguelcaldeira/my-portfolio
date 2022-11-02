package m19.app.main;

import m19.core.LibraryManager;
import m19.core.Parser;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;
import m19.app.exception.FileOpenFailedException;
import m19.core.exception.MissingFileAssociationException;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * 4.1.1. Save to file under current name (if unnamed, query for name).
 */
public class DoSave extends Command<LibraryManager> {
  private Input<String> _filename;

  /**
   * @param receiver
   */
  public DoSave(LibraryManager receiver) {
    super(Label.SAVE, receiver);
    _filename = _form.addStringInput(Message.newSaveAs());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    try { 
      if (_receiver.getFilename() == null) {
        _form.parse();
        _receiver.setFileName(_filename.value());
        _receiver.save();
      }
      else {
        _receiver.save();
      }
    } 
    catch (MissingFileAssociationException | IOException e) {
      e.printStackTrace();
    }
  }
}
