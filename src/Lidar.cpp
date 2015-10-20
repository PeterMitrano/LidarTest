#include "Lidar.h"

void VX11::read(){
  if (Serial.available()){
    byte b = Serial.read();

    if (startReading){
      if (packetIndex == 21){
        startReading = false;
        endPacket();
      }
      else {
        packet[packetIndex] = b;
        packetIndex++;
      }
    }

    //check start bit
    if (!startReading && b == 0xFA){
      startReading = true;
      packetIndex = 0;
      packet[packetIndex] = b;
      packetIndex++;
    }

  }
}

void VX11::endPacket(){
  int newPacketNumber = packet[1];

  // watch out for missed packets
  if ((newPacketNumber - packetNumber) == 1){
    for (int i=0;i<22;i++){
      switch(i){
        case 2:
          // speed
          speed = (float)(packet[3] << 8 | packet[2]);
          speed /= 64;
          break;
        case 4:
        case 8:
        case 12:
        case 16:
          //distance 0
          distanceIndex = (newPacketNumber - 0xA0) * 4 + i/4 - 1;
          if (distanceIndex >= 0 && distanceIndex < 360){
            if ((packet[i+1] & 0x80) >> 7){
              distances[distanceIndex] = 0;
            }
            else {
              int d = packet[i] | ((packet[i+1] & 0x3F) << 8);

              //cap between limits
              if (d < 0 || d > 6000){
                d = 0;
              }

              // finally store valid data
              distances[distanceIndex] = d;
              Serial.print(distanceIndex);
              Serial.print(",");
              Serial.println(d);
            }
          }

          break;
        default:
          //checksum, packet num, and start bit go here
          break;
      }
    }
  }

  packetNumber = newPacketNumber;

  //reset when you reach the last packet
  if (packetNumber >= 0xF9){
    packetNumber = 0x9F;
  }
}

//DOESN'T WORK RIGHT NOW
int VX11::calcChecksum(){
  int data[20];
  for (int i=0;i<10;i++){
    int a = packet[2*i];
    int b = (packet[2*i+1]<<8);
    data[i] = a + b;
  }

  int chk32 = 0;
  for (int i=0;i<10;i++){
    chk32 = (chk32 << 1) + data[i];
  }

  int checksum = (chk32 & 0x7FFF) + (chk32 >> 15);
  checksum = checksum & 0x7FFF;
  return checksum;
}

byte *VX11::getLatestPacket(){
  return NULL;
}

int *VX11::getLatestDistance(){
  return distances;
}
