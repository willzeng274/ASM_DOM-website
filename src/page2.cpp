#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"
#include <functional>
#include <string>

asmdom::VNode* page2() {
    asmdom::VNode* new_node = asmdom::h("div",
    asmdom::Data(
      asmdom::Attrs {
        {"class", "root"}
      },
      asmdom::Callbacks {
        {"onclick", [](emscripten::val e) -> bool {
          emscripten::val::global("console").call<void>("log", emscripten::val("another click"));
          return true;
        }}
      }
    ),
    asmdom::Children {
      asmdom::h("div",
        asmdom::Data(
          asmdom::Attrs {
            {"style",
              "position: absolute;"
              "bottom: 8px;"
              "font-size: 12px;"}
          }
        ),
        std::string("asm-dom-boilerplate")
      )
    }
  );

  return new_node;
};