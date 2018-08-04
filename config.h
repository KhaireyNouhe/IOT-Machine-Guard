/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "Write your adafruit.io username here!"
#define IO_KEY         "Write your adafruit.io KEY here!"

/******************************* WIFI **************************************/
#define WIFI_SSID       "Write your WIFI SSID here!"
#define WIFI_PASS       "Write your WIFI password here!"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);



