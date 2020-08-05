package m19.app.works;

import pt.tecnico.po.ui.Input;
import m19.core.LibraryManager;
import m19.core.Work;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Command;
import java.util.List;
import java.util.ArrayList;

// FIXME import other core concepts
// FIXME import ui concepts

/**
 * 4.3.3. Perform search according to miscellaneous criteria.
 */
public class DoPerformSearch extends Command<LibraryManager> {

  private Input<String> _searchTerm;

  /**
   * @param m
   */
  public DoPerformSearch(LibraryManager receiver) {
    super(Label.PERFORM_SEARCH, receiver);
    _searchTerm = _form.addStringInput(Message.requestSearchTerm());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    _form.parse();
    if (!_searchTerm.value().isEmpty() && _searchTerm.value() != null) {
      List<Work> works = _receiver.getAllWorks();
      String substring = _searchTerm.value().toLowerCase();
      for (Work work : works ) {
        if (work.getTitle().toLowerCase().contains(substring) || work.getCreator().toLowerCase().contains(substring)) {
          _display.add(work.getDescription());
        }
      }
      _display.display(true);
    }
  }
}