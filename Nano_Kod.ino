
#include <Wire.h>
#define SSD1306_NO_SPLASH 
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define DHTPIN 2 // what digital pin we're connected to
#define DHTTYPE DHT11  //DHT 11
const int PIN_RED   = 9;
const int PIN_GREEN = 6;
const int PIN_BLUE  = 8;
DHT dht (DHTPIN, DHTTYPE);

//Definerar skärmens upplösning
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//Väljer reset knapp(samma som arduino) och adressen och några fler variabler som behövs.
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3D
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int SENSOR_PIN = 7;
int rad;
float gas;
int menu;
int before;
int resultat;
int svar;

#define bitmap_height   128
#define bitmap_width    64
//Tillfällig bitmap som representerar en meny på skärmen
// 'Mäta', 128x64px
// 'Darecloud', 128x64px
const unsigned char epd_bitmap_Darecloud [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1e, 0x3f, 0x87, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
	epd_bitmap_Darecloud
};
const unsigned char epd_bitmap_M_ta [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x0f, 0xc3, 0xff, 0x0f, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x0f, 0xc3, 0xff, 0x0f, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0xcf, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0xcf, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x33, 0x3f, 0xf0, 0x30, 0x3f, 0xf0, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x33, 0x3f, 0xf0, 0x30, 0x3f, 0xf0, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0xfc, 0x3f, 0xcf, 0xfc, 0x3f, 0x0f, 0xf0, 0xfc, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0xfc, 0x3f, 0xcf, 0xfc, 0x3f, 0x0f, 0xf0, 0xfc, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0xc0, 0x00, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0xc0, 0x00, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xfc, 0x30, 0x3f, 0x00, 0xc0, 0xc0, 0xcf, 0xf0, 0x30, 0xfc, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xfc, 0x30, 0x3f, 0x00, 0xc0, 0xc0, 0xcf, 0xf0, 0x30, 0xfc, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0xfc, 0x3f, 0x00, 0xc0, 0x3f, 0x0c, 0x0c, 0xfc, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x0c, 0xfc, 0x3f, 0x00, 0xc0, 0x3f, 0x0c, 0x0c, 0xfc, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'historik', 128x64px
const unsigned char epd_bitmap_historik [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x0f, 0xc3, 0xff, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x0f, 0xc3, 0xff, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xcf, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xcf, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x3f, 0xf0, 0x30, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x3f, 0xf0, 0x30, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0xfc, 0x3f, 0xcf, 0xfc, 0x3f, 0x0f, 0xf0, 0xfc, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0xfc, 0x3f, 0xcf, 0xfc, 0x3f, 0x0f, 0xf0, 0xfc, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0xc0, 0x00, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0xc0, 0x00, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0f, 0xfc, 0x30, 0x3f, 0x00, 0xc0, 0xc0, 0xcf, 0xf0, 0x30, 0xfc, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0f, 0xfc, 0x30, 0x3f, 0x00, 0xc0, 0xc0, 0xcf, 0xf0, 0x30, 0xfc, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc3, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0x00, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0xc0, 0xcc, 0x0c, 0x30, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0xfc, 0x3f, 0x00, 0xc0, 0x3f, 0x0c, 0x0c, 0xfc, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x0c, 0x0c, 0xfc, 0x3f, 0x00, 0xc0, 0x3f, 0x0c, 0x0c, 0xfc, 0xc0, 0xc0, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int epd_bitmap_historikvalue = 1;
const unsigned char* epd_bitmap_historik_array[1] = {
	epd_bitmap_historik
};

;

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int epd_bitmap_M_tavalue = 1;
const unsigned char* epd_bitmap_M_ta_array[1] = {
	epd_bitmap_M_ta
};
int j=0;
int r = 0;
int g = 0;
int b = 0;
byte x;
int y;
float t;
byte recArray[10];
int receivedARry[5];
void setup() {
  //Startar kommunikation med serial monitor för att kunna visa felkoder
  dht.begin();
  delay(2000);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    delay(1000);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    delay(1000);
     // Don't proceed, loop forever
  }
  }
  pinMode(A7,INPUT);
  float batteri = analogRead(A7);
  float batteriprocent = (batteri * 100) /1100;
  int batteriet = (int(batteriprocent) - 60)* 2.5 ;


  display.clearDisplay();
  display.setTextSize(1); //Bestämmer storlek på texten
  display.setTextColor(WHITE);//Väljer färg vit
  display.setCursor(20, 10); //sätter vart texten ska komma fram
  display.println("Batteri:");
  display.display();
  display.fillRect(18,20,batteriet,40,WHITE);
  display.fillRect(35,20,5,40,BLACK);
  display.fillRect(55,20,5,40,BLACK);
  display.fillRect(75,20,5,40,BLACK);
  display.fillRect(95,20,5,40,BLACK);
  display.display();
  delay(2500);
  display.clearDisplay();

  //digital output som pratar med andra arduino
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 151);
  analogWrite(PIN_BLUE,  157);

  Serial.print("Startar");
  //startar I2C transfer med andra arduino
  Wire.begin(9);
  Wire.onReceive(receiveData);

  display.display();

  display.clearDisplay();
  //display.drawBitmap(0, 0, epd_bitmap_Darecloud, 128, 64, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawBitmap(0, 0, epd_bitmap_M_ta, 128, 64, WHITE);
  display.display();
  int inputState = digitalRead(7); // knappens interface i arduinot
  int rad; //variabel som bestämmer vilken meny som visas
  float gas;
  digitalWrite(4,LOW);
}

void loop() {
  t = dht.readTemperature();
  Serial.println(t);
  //ankallar funktionen som bestämmer vad som visas på skärmen
 gas = analogRead(A2);
  if(menu == 0){
    showBitmap();}
  //Serial.println(gas);
  if(digitalRead(3) == HIGH){
    menu = 1;
  };
  if(digitalRead(3) == HIGH){
    if(rad == 0){
      mata();
    }
    if(rad == 1){
      historik();
    };
  }
 // aqua
  

  //väntar lite för att inte loopen ska gå för snabbt
  delay(100);
  digitalWrite(4,LOW);

}

void showBitmap() {
  //läser av ifall knappen trycks och gör så att den switchas beroende på vad som nyss visades på skärmen, vilket ger en meny liknande UI
  if(digitalRead(SENSOR_PIN) == HIGH){
    if( rad == 1){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.drawBitmap(0, 0, epd_bitmap_M_ta, 128, 64, WHITE);
    display.display();
    rad=0;
    delay(500);
    }
    //nästa skärm
    else if(rad == 0){
    display.clearDisplay(); //ta bort allt på skärmen
    display.setTextSize(2); //Bestämmer storlek på texten
    display.setTextColor(WHITE);//Väljer färg vit
    display.setCursor(0, 0); //sätter vart texten ska komma fram
    display.drawBitmap(0, 0, epd_bitmap_historik, 128, 64, WHITE); // byta bitmap
    display.display(); //Initierar att skärmen ska displaya det som är skriver
    rad=1; //Byter till nästa val vid nästa knapptryck
    delay(500);
    }
    

  }
  
  
}
void mata(){
  mataklick();
  int timer = 0;
  digitalWrite(4,HIGH);
  delay(500);
  delay(8);
  digitalWrite(4,LOW);
  before = analogRead(A2);
  while (timer <70){
  gas = analogRead(A2);
  display.clearDisplay();
  display.setTextSize(2); //Bestämmer storlek på texten
  display.setTextColor(WHITE);//Väljer färg vit
  display.setCursor(20, 28); //sätter vart texten ska komma fram
  display.println(gas);
  display.display();
  delay(50);
  timer= timer +1;
  }
  resultat = analogRead(A2);
  
  menu = 0;
  resultatf();
}
void historik(){
  digitalWrite(5,HIGH);
  delay(500);
  digitalWrite(5,LOW);
  display.clearDisplay();
  display.setTextSize(2);
  display.print("Getting");
  display.setCursor(0,20);
  display.println("History");
  display.display();
  delay(2000);
  
  receiveData(10); 

  if(digitalRead(3)==HIGH){
    menu = 0;
  }
  menu = 0;
}
void mataklick(){
  display.clearDisplay();
  display.setTextSize(2); //Bestämmer storlek på texten
  display.setTextColor(WHITE);//Väljer färg vit
  display.setCursor(0, 0); //sätter vart texten ska komma fram
  display.println("Mater om");
  display.setTextSize(4);
  display.setCursor(58,28);
  display.println("3");
  setColor(255, 0, 0);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0); //sätter vart texten ska komma fram
  display.println("Mater om");
  display.setTextSize(4);
  display.setCursor(58,28);
  display.setTextColor(WHITE);
  display.println("2");
  setColor(252, 236, 3);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0); //sätter vart texten ska komma fram
  display.println("Mater om");
  display.setTextSize(4);
  display.setCursor(58,28);
  display.setTextColor(WHITE);
  display.println("1");
  setColor(0, 255,0);
  display.display();
  delay(100);
    
}
void receiveData(int byteCount) {
  if (byteCount == sizeof(int) * 5) {
    int receivedData[5];

    for (int i = 0; i < 5; i++) {
      receivedData[i] = Wire.read();
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    for (int i = 0; i < 5; i++) {
      display.setCursor(0, i * 10);
      display.print("");
      x = i+1;
      display.print(x);
      display.print(": ");
      display.println(receivedData[i]);
    }

    display.display();
  } else {
    // Handle error if the received data size is incorrect
    Serial.println("Received data size incorrect");
  }
}
void resultatf(){
  display.clearDisplay();
  svar = resultat-before;
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0); //sätter vart texten ska komma fram
  display.println("Svar:");
  display.setTextSize(2);
  display.setCursor(30,28);
  display.setTextColor(WHITE);
  if(svar <20 ){
  display.println(" <0,2");
  setColor(0,255,0);
  }
  else if (svar < 150){
    display.println(" 0,2< > 0,6");
    setColor(252,236,3);
  }
  else{
    display.println(" 0,6< ");
   setColor(255,0,0);
  }
  display.display();
  delay(6000);
  display.display();
  Serial.println(x);
  display.clearDisplay();
  
  display.drawBitmap(0, 0, epd_bitmap_M_ta, 128, 64, WHITE);
  display.display();


}
void setColor(int r,int g,int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b); 
}