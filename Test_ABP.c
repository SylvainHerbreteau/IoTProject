#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <lmic.h>
#include <hal.h>
#include <local_hal.h>

#define LORAWAN_CONFIRMED_MSG_ON 1

static const u1_t DEVEUI[8]  = { 0x00, 0x32, 0xA1, 0x50, 0xB3, 0x52, 0x2D, 0x75};
static const u1_t APPEUI[8]  = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x01, 0x44, 0x71};
u1_t nwkskey[16] = {0xBC, 0xA4, 0x08, 0xD8, 0xF5, 0xDB, 0xA6, 0xBB, 0xFD, 0xD1, 0x0B, 0xA7, 0x97, 0x80, 0x32, 0x1E};
u1_t appskey[16] = {0x10, 0x26, 0xF5, 0xD1, 0xF1, 0x63, 0x62, 0xFA, 0x11, 0x20, 0x37, 0x83, 0x02, 0xFA, 0x92, 0x3C};
static const u1_t DEVKEY[16] = { 0x12, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78 };
static u4_t fcntUp = 1;

/*
 * These three functions are accessor for
 * the LMIC library, do not modify.
 */
void os_getArtEui(u1_t * buf) {
  memcpy(buf, APPEUI, 8);
}

void os_getDevEui(u1_t * buf) {
  memcpy(buf, DEVEUI, 8);
}

void os_getDevKey(u1_t * buf) {
  memcpy(buf, DEVKEY, 16);
}

/*
 * Pinout for the LMIC library.
 * This is the pinout of the RFM95 on
 * the ChisteraPi.
 */
//Chistera Pi V1.2 (OT)
lmic_pinmap pins = {
  .nss = 5,
  .rxtx = UNUSED_PIN,
  .rst = 6,
  .dio = {14,15,16}
};

void onEvent(ev_t ev) {
  switch (ev) {
      // scheduled data sent (optionally data received)
      case EV_TXCOMPLETE:
        if (TXRX_ACK) {
                fprintf(stdout, "TXRX_ACK confirmed UP frame was acked\n");
        }
        fprintf(stdout, "TX complete .....................................%d %d \n", LMIC.dataLen,LMIC.frame[LMIC.dataBeg-1]);
        for (int i = 0;  i <LMIC.dataLen;  i++) {
             fprintf(stdout, "%c", LMIC.frame[LMIC.dataBeg + i]);
        }
        fprintf(stdout, "\n");
        break;
       default:
        break;
  }
}
/*
// initial job
static void initfunc(osjob_t * j) {
  fprintf(stdout, "init ....\n");
  LMIC_reset(); // reset MAC state
  LMIC_setSession(0x010203, 0x06094620, nwkskey, appskey);
  LMIC_setDrTxpow(DR_SF7,14);
  fprintf(stdout, "NetID = %02x DevAddr = %02x \n", LMIC.netid, LMIC.devaddr);
  LMIC.frame[0] = 0x4a;
  LMIC.seqnoUp = fcntUp +1;
  LMIC_setTxData2(1, LMIC.frame, 1, LORAWAN_CONFIRMED_MSG_ON);
}*/

// application entry point
int main() {
  osjob_t initjob;
  // initialize runtime env
  os_init();
  // setup initial job
  os_setCallback(&initjob, initfunc);
  // execute scheduled jobs and events
  os_runloop();
  return 0;
}
