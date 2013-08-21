#ifndef PI
# define PI 3.141592653589793f
#endif

#ifndef M_PI_2
# define M_PI_2 1.570796326794897f
#endif

#ifndef atanf
# define atanf atan
#endif

#ifndef atan2f
# define atan2f atan2
#endif

#include "C:/Users/Simon/Documents/GitHub/mavlink_sniffer/libraries/mavlink/include/include/mavlink/v1.0/ardupilotmega/mavlink.h" 

void communication_receive();
static int packet_drops = 0;

void setup(){
  Serial.begin(57600);
  Serial1.begin(57600);
}

void loop(){
  communication_receive();
}

void communication_receive()
{
  mavlink_message_t msg;
  mavlink_status_t status;

  if(Serial1.available()) {
    Serial.print("\t\tReading some bytes: ");
    Serial.println(Serial1.available());
  }

  // COMMUNICATION THROUGH UART
  while(Serial1.available() > 0)
  {
    uint8_t c = Serial1.read();
    //Serial.print(char(c));

    // Try to get a new message
    if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      Serial.print("\t\t***Message received! id:");
      Serial.println(msg.msgid);

      // Handle message
      //decode(msg);
    }

    // And get the next one
  }
  // Update global packet drops counter
  packet_drops += status.packet_rx_drop_count;
}
