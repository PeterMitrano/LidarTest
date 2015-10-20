#include "Lidar.h"

VX11 lidar;

void setup(){
  Serial.begin(115200);
}

void loop(){
  lidar.read();
}
