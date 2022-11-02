#ifndef __FIR_FACTORY_H__
#define __FIR_FACTORY_H__

#include <memory>
#include <cdk/yy_factory.h>
#include "fir_scanner.h"

namespace fir {

  /**
   * This class implements the compiler factory for the FIR compiler.
   */
  class factory: public cdk::yy_factory<fir_scanner> {
    /**
     * This object is automatically registered by the constructor in the
     * superclass' language registry.
     */
    static factory _self;

  protected:
    /**
     * @param language name of the language handled by this factory (see .cpp file)
     */
    factory(const std::string &language = "fir") :
        cdk::yy_factory<fir_scanner>(language) {
    }

  };

} // fir

#endif
