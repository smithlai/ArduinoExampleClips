#include <elapsedMillis.h>
elapsedMillis elapse = 0;
void elapseExample(){
  if(elapse > 2000){
    Serial.println("elapsedMillis triggered");
    elapse = 0;
  }
}

