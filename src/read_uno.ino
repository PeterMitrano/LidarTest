#include "Lidar.h"
#include "MemoryFree.h"

VX11 lidar;

void setup(){
  Serial.begin(115200);
}

void loop(){
  lidar.read();

  int *distances;
  distances = lidar.getLatestDistance();
/*
  for (int i=0;i<360;i++){
    Serial.print(distances[i]);
    Serial.print(" ");
  }
  Serial.println();
*/
}
