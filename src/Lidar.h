#pragma once
#include "Arduino.h"

class VX11 {
  public:

    /** \brief should be called every loop to read and store data */
    void read();

    /** \brief get the last packet speed and distances */
    byte *getLatestPacket();

    /** \brief get the full array of 360 distance values */
    int *getLatestDistance();

  private:

    int calcChecksum();

    byte packet[22];

    int distances[360];

    int packetIndex = 0, distanceIndex = 0;
    float speed = 0;
    int packetNumber = 0;

    bool startReading = false,
         invalidPacket = false,
         doneReading = false;

};
