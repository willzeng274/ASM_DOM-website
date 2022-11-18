#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"
#include <functional>
#include <string>

int i = 1;

asmdom::VNode* current_view = NULL;

asmdom::VNode* page1();
asmdom::VNode* page2();

std::string page = "/";
std::map<std::string, std::function<asmdom::VNode*()>> pages = {
  {"/", page1},
  {"/test", page2}
};

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
  // emscripten::val::global("console").call<emscripten::val>(
  //   "log",
  //   std::string(page)
  // );
  current_view = asmdom::patch(current_view, pages.find(page) == pages.end() ? pages["/"] : pages[page]);
};

int main() {
  asmdom::Config config;
  asmdom::init(config);

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

  render();

  return 0;
};