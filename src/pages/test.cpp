#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"

asmdom::VNode* test() {
    asmdom::VNode* new_node = html(
      <div class="root" onclick={[](emscripten::val e) -> bool {
        emscripten::val::global("console").call<void>("log", emscripten::val("another click"));
        return true;
      }}>
        <button class="fancy-button">
          Test button
        </button>
        <div style="
          position: absolute;
          bottom: 8px;
          font-size: 12px;
        ">
          asm-dom-boilerplate
        </div>
      </div>
    );
  return new_node;
};