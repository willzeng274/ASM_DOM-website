#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"
#include <functional>
#include <string>

bool decrease(emscripten::val) {
  i--;
  render();
  return true;
};

bool increase(emscripten::val) {
  i++;
  render();
  return true;
};

asmdom::VNode* page1() {
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
      asmdom::h("button",
        asmdom::Data(
          asmdom::Attrs {
            {"class", "button"}
          },
          asmdom::Callbacks {
            {"onclick", decrease}
          }
        ),
        std::string("-")
      ),
      asmdom::h(std::to_string(i), true),
      asmdom::h("button",
        asmdom::Data(
          asmdom::Attrs {
            {"class", "button"}
          },
          asmdom::Callbacks {
            {"onclick", increase}
          }
        ),
        std::string("+")
      ),
      asmdom::h("a",
        asmdom::Data(
          asmdom::Callbacks {
            {"onclick", [](emscripten::val e) -> bool {
              direct("/test");
              return true;
            }}
          }
        ),
        std::string("page2")
      ),
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