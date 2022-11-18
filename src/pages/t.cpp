#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"

asmdom::VNode* t() {
  asmdom::VNode* new_node = html(
    <div class="root" onclick={[](emscripten::val e) -> bool {
      emscripten::val::global("console").call<void>("log", emscripten::val("another click"));
      return true;
    }}>
      ttttttt
    </div>
  );
  return new_node;
};