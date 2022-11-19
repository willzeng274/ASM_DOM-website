#include <emscripten/val.h>
#include "asm-dom.hpp"
#include "globals.h"

std::string body = "";

std::string val = "/";

asmdom::VNode* admin() {
  asmdom::VNode* new_node = html(
    <div class="root" onclick={[](emscripten::val e) -> bool {
      emscripten::val::global("console").call<void>("log", emscripten::val("another click"));
      return true;
    }}>
      <button onclick={[](emscripten::val e) -> bool {
        body = asmdom::toHTML(pages[val]());
        render();
        return true;
      }}>
        Show page source
      </button>
      <label for="b">Page name</label>
      <input id="b" value={val} onchange={[](emscripten::val e) -> bool {
        val = e["target"]["value"].as<std::string>();
        if (val == "") {
            body = "";
            render();
            return true;
        }

        for (auto [k, v]: pages) {
          emscripten::val::global("window").call<void>("eval", emscripten::val(
            "function download(filename, text) {"
              "var element = document.createElement('a');"
              "element.setAttribute('href', 'data:text/html;charset=utf-8,' + encodeURIComponent(text));"
              "element.setAttribute('download', filename);"

              "element.style.display = 'none';"
              "document.body.appendChild(element);"

              "element.click();"

              "document.body.removeChild(element);"
            "}"
            "download('" + (k == "/" ? "index" : k.substr(1, k.length()-1)) + ".html', '"
              "<html lang=\"en\">"
                "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">"
                  "<title>asm-dom boilerplate</title>"
                "</head>"

                "<body>"
                  "<!-- this is where app gets mounted -->"
                  "<div id=\"root\">"
                    + asmdom::toHTML(v()) +
                  "</div>"
                  "<!-- replace the js file with your actual file below -->"
                  "<script src=\"/index.js\"></script>"
                "</body>"
              "</html>"
            "')"
          ));
        }
        render();
        return true;
      }} />
      <div class="content">
        {{ body }}
      </div>
    </div>
  );
  return new_node;
};