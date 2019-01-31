/*******************************************************************************
 * Copyright (c) 2019 ENSEIRB-MATMECA's Embedded Systems class project 
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * This is the code that sends a valid LoRaWAN packet with payload in CayenneLPP
 * mode containing the Temperature, Humidity & The Pressure that
 * will be processed by The Things Network server.
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in g1, 
 *  0.1% in g2). 
 *
 *  *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
#include <wiringPi.h>
#include <lmic.h>
#include <hal.h>
#include <local_hal.h>
#include "CayenneLPP.h"

// LoRaWAN NwkSKey, network session key 
// Use this key for The Things Network
static const u1_t DEVKEY[16] = { 0xBC, 0xA4, 0x08, 0xD8, 0xF5, 0xDB, 0xA6, 0xBB, 0xFD, 0xD1, 0x0B, 0xA7, 0x97, 0x80, 0x32, 0x1E };

// LoRaWAN AppSKey, application session key
// Use this key to get your data decrypted by The Things Network
static const u1_t ARTKEY[16] = { 0x10, 0x26, 0xF5, 0xD1, 0xF1, 0x63, 0x62, 0xFA, 0x11, 0x20, 0x37, 0x83, 0x02, 0xFA, 0x92, 0x3C };
// LoRaWAN end-device address (DevAddr)
static const u4_t DEVADDR = 0x260113BD ; // <-- Change this address for every node!


#define CLPP_LEN (LPP_TEMPERATURE_SIZE + LPP_RELATIVE_HUMIDITY_SIZE + LPP_BAROMETRIC_PRESSURE_SIZE)

#define SHELLSCRIPT "\
#/bin/bash \n\
sudo python sensors.py"

CayenneLPP LPP(CLPP_LEN);


uint8_t * buf_LPP;

FILE* file=NULL;


// provide application router ID (8 bytes, LSBF)
void os_getArtEui (u1_t* buf) {
    memcpy(buf, APPEUI, 8);
}

// provide device ID (8 bytes, LSBF)
void os_getDevEui (u1_t* buf) {
    memcpy(buf, DEVEUI, 8);
}

// provide device key (16 bytes)
void os_getDevKey (u1_t* buf) {
    memcpy(buf, DEVKEY, 16);
}

u4_t cntr=0;
u1_t mydata[] = {"How you doing ?"};
static osjob_t sendjob;


// Pin mapping
lmic_pinmap pins = {
  .nss = 10,
  .rxtx = UNUSED_PIN,
  .rst = 0,
  .dio = {7,4,5}
};


static void do_send(osjob_t* j){

	file=fopen("StationMeteo.txt","r");
	LPP.reset();
		if (file != NULL){
			time_t t = time(NULL);
			fprintf(stdout, "[%x] (%ld) %s\n", hal_ticks(), t, ctime(&t));
			// Show TX channel (channel numbers are local to LMIC)
			// Check if there is not a current TX/RX job running
			if (LMIC.opmode & (1 << 7)) {
			fprintf(stdout, "OP_TXRXPEND, not sending");
			} 
			else{
				// Prepare upstream data transmission at the next possible time.
				char line[128];
				int j=0;
				double buf[3] ={ 1, 2, 3};
				

				char buff1[128];
				char buff2[128];
				char buff3[128];
								
				fgets(line,sizeof line, file);				
				sprintf(buff1,line);
				fgets(line,sizeof line, file);				
				sprintf(buff2,line);
				fgets(line,sizeof line, file);				
				sprintf(buff3,line);
		
				 
				buf[0]=atof(buff1);
				buf[1]=atof(buff2);
				buf[2]=atof(buff3);

				LPP.addTemperature(1, buf[0]);
				LPP.addRelativeHumidity(2, buf[1]);
				LPP.addBarometricPressure(3, buf[2]);

				buf_LPP = LPP.getBuffer();

				int i=0;
				while(i < CLPP_LEN) {
					mydata[i]=buf_LPP[i];
					i++;
				}
				
				mydata[i]='\0';

				LMIC_setTxData2(1, mydata, CLPP_LEN , 0);
				
			}
			
			os_setTimedCallback(j, os_getTime()+sec2osticks(60), do_send);
		}
         else printf("Could Not Open file \n");
}


void onEvent (ev_t ev) {
	switch(ev) {
	
		case EV_TXCOMPLETE:
			// We use this event to keep track of actual transmissions
			fprintf(stdout, "Event EV_TXCOMPLETE, time: %d\n", millis() / 1000);
			if(LMIC.dataLen) { // data received in rx slot after tx
			
			fprintf(stdout, "Data Received!\n");
			}
			do_send(&sendjob);
		break;
	default:
		break;
	}
}


void setup() {
  // LMIC init
  wiringPiSetup();

  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();
  // Set static session parameters. Instead of dynamically establishing a session 
  // by joining the network, precomputed session parameters are be provided.
  LMIC_setSession (0x1, DEVADDR, (u1_t*)DEVKEY, (u1_t*)ARTKEY);
  // Disable data rate adaptation
  LMIC_setAdrMode(0);
  // Disable link check validation
  LMIC_setLinkCheckMode(0);
  // Disable beacon tracking
  LMIC_disableTracking ();
  // Stop listening for downstream data (periodical reception)
  LMIC_stopPingable();
  // Set data rate and transmit power (note: txpow seems to be ignored by the library)
  LMIC_setDrTxpow(DR_SF7,14);
  //
  do_send(&sendjob);
}

void loop() {

while(1) {
  os_runloop();
  }
}


int main() {
  
  setup();

  while (1) {
	system(SHELLSCRIPT);    
	loop();
  }
  return 0;
}

