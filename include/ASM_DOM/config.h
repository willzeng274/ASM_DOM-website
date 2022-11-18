#ifndef config_h
#define config_h

#define node asmdom::VNode*

node index_();
node test();
node error();
node t();

inline std::map<std::string, std::function<asmdom::VNode*()>> pages = {
  {"/", index_},
  {"/test", test},
  {"/error", error},
  {"/t", t}
};

#endif