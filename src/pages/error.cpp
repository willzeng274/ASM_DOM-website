#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"

asmdom::VNode* error() {
  asmdom::VNode* new_node = html(
    <div class="root" onclick={[](emscripten::val e) -> bool {
      emscripten::val::global("console").call<void>("log", emscripten::val("another click"));
      return true;
    }}>
      <div>
        Error 404
      </div>

      <div
        style="
          position: absolute;
          bottom: 8px;
          font-size: 12px;
        "
      >
        asm-dom-boilerplate
      </div>
    </div>
  );
  return new_node;
};