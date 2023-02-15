# streamFlow

Simple and light-weight stream operator for Arduino framework.

This is not an emulation of C++ ostream, but it mimics those good parts

## Supporting
- operator<<
- endl
- flush
- precision(n) for float only
- dec, hex, oct, bin radix base spec. only for integral numbers


## Example
```c++
#include <streamFlow.h>
using namespace StreamFlow;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<"stream style with arduino Serial"<<endl
        <<"version:"<<precision(2)<<2.0<<endl
        <<"hex format 0x"<<hex<<1967<<endl
        <<"enjoy!"<<endl<<flush;
}
```
