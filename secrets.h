#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_LED"
 
// Set the proper values for your wifi connection
const char WIFI_SSID[] = "Garrulus";
const char WIFI_PASSWORD[] = "foobar12";
const char AWS_IOT_ENDPOINT[] = "a3tn5spx481p8c-ats.iot.eu-central-1.amazonaws.com";
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----

 
 
)KEY";
 
// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----
 
)KEY";