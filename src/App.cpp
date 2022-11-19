#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"

asmdom::VNode* current_view = NULL;

std::string page = "/";

bool direct(std::string pageN) {
  page = pageN;
  emscripten::val::global("history").call<emscripten::val>(
    "pushState",
    emscripten::val::global("Object").new_(),
    std::string(""),
    std::string(pageN)
  );
  render();
  return true;
}

void render() {
  current_view = asmdom::patch(current_view, pages.find(page) == pages.end() ? pages["/error"]() : pages[page]());
};

int main() {
  asmdom::Config config;
  asmdom::init(config);

  // default view before load
  current_view = asmdom::h("div",
    asmdom::Data(
      asmdom::Attrs {
        {"class", "root"}
      }
    )
  );

  asmdom::patch(
    emscripten::val::global("document").call<emscripten::val>(
      "getElementById",
      std::string("root")
    ),
    current_view
  );

  page = emscripten::val::global("window")["location"]["pathname"].as<std::string>();

  render();

  return 0;
};