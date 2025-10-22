const string TERM_RED = "\033[31m";
const string TERM_RESET = "\033[0m";

template <typename T>
void dump(const T &val) {
  cerr << TERM_RED << "[[ DEBUG ]] " << val << TERM_RESET << std::endl;
}
