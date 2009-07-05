#include "utils.hpp"
#include <sstream>

void assert_msg(std::string file,int line)throw(std::logic_error)
{
  std::ostringstream os;
  os<<"file: "<<file<<" line:"<<line;
  throw std::logic_error(os.str());
}
