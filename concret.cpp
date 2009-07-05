#include <utils/utils.hpp>
#include <cdata/cdata.hpp>

int main(int argc,char*argv[])
{
  if(argc!=4){
    LOG("usage: "<<argv[0]<<" x_data.csv y7_data.csv y_data.csv");
    return -1;
  }
  Concrete::CData cdata(argv[1]);
  cdata.init();
  LOG("Количество экспериментов: "<<cdata.size());
  
}
