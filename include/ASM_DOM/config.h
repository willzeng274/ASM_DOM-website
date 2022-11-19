#ifndef config_h
#define config_h

#include <map>
#include "asm-dom.hpp"
#define node asmdom::VNode*

node index_();
node test();
node error();
node t();
node admin();

inline std::map<std::string, std::function<asmdom::VNode*()>> pages = {
  {"/", index_},
  {"/test", test},
  {"/error", error},
  {"/t", t},
  {"/admin", admin}
};

#endif