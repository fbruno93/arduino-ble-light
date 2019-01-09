#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define PIN      6
#define NUMPIXELS 12
#define ADDRMODE 0
#define ADDRRED 1
#define ADDRGREEN 2
#define ADDRBLUE 3
#define ADDRSPEED 4
#define ADDRLED 5
#define ADDRBRIGHT 6
// UUID 0xB2F0
// CHAR 0xB2F1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial my(2, 3); // Rx Tx

byte mode,
	red,
	green,
	blue,
	s,
	leds,
	bright,
	lingth_on;

int j = 0;
long last_time;
byte buff[7];
int arr[12][3] = {
	{255, 000, 000},
	{255, 128, 000},
	{255, 255, 000},
	{128, 255, 000},
	{000, 255, 000},
	{000, 255, 128},
	{000, 255, 255},
	{000, 128, 255},
	{000, 000, 255},
	{128, 000, 255},
	{255, 000, 255},
	{255, 000, 128}
};

void colorWheel(int spee);
void multi(int spee);
void blinking(int r, int g, int b, int spee);
void counter(int r, int g, int b, int total);
void snake(int r, int g, int b, int leds, int spee);
void color(int r, int g, int b);
void stoping();

void setup() {

	my.begin(9600);
	
	#ifdef DEBUG	
		Serial.begin(9600);
		while (!Serial) {}	
		Serial.println("START");
	#endif
	pixels.begin();

	delay(250);
	
	mode = EEPROM.read(ADDRMODE);
	red = EEPROM.read(ADDRRED);
	green = EEPROM.read(ADDRGREEN);
	blue = EEPROM.read(ADDRBLUE);
	s = EEPROM.read(ADDRSPEED);
	leds = EEPROM.read(ADDRLED);
	bright = EEPROM.read(ADDRBRIGHT);
	
	if (bright == 0) {
		bright = 5;
	}

	pixels.setBrightness(bright);
	
	#ifdef DEBUG
		Serial.println(mode, DEC);
		Serial.println(red, DEC);
		Serial.println(green, DEC);
		Serial.println(blue, DEC);
		Serial.println(s, DEC);
		Serial.println(leds, DEC);
		Serial.println(bright, DEC);
	#endif
	delay(250);
}


void loop() {
	if (my.available()) {
		my.readBytes(buff, 6);
		
		#ifdef DEBUG
			Serial.println("Datas coming");
			for (int i = 0 ; i < 6 ; i++) {
				Serial.print(buff[i], DEC);
				Serial.print(" ");
			}
			Serial.println("");
		#endif

		j = 0;
		mode = buff[0];
		red = buff[1];
		green = buff[2];
		blue = buff[3];
		s = buff[4];
		leds = buff[5];

		pixels.setBrightness(buff[6])

		EEPROM.write(ADDRMODE, mode);
		EEPROM.write(ADDRRED, red);
		EEPROM.write(ADDRGREEN, green);
		EEPROM.write(ADDRBLUE, blue);
		EEPROM.write(ADDRSPEED, s);
		EEPROM.write(ADDRLED, leds);
		EEPROM.write(ADDRBRIGHT, buff[6]);

		lingth_on = NUMPIXELS;
		last_time = millis();
	}

	switch(mode) {
		case 0:
			color(red, green, blue);
		break;
		case 1:
			multi(s);
		break;
		case 2:
			blinking(red, green, blue, s);
		break;
		case 3:
			counter(red, green, blue, s);
		break;
		case 4:
			snake(red, green, blue, leds, s);
		break;
		case 5:
			stoping();
		break;
		case 6:
			colorWheel(s);
		break;
	}
}

void colorWheel(int spee) {
	j = (j == NUMPIXELS) ? 0 : (j + 1);
	
	for (int i = 0 ; i < NUMPIXELS ; i++) {
		int diff = 0;
		if ( i < j) {
			diff = NUMPIXELS - j + i;
		}

		if (i > j) {
			diff = i - j;
		}

		pixels.setPixelColor(i, pixels.Color(arr[diff][0], arr[diff][1], arr[diff][2]));
	}

	pixels.show();
	delay(spee);
}

void multi(int spee) {
	j = (j == NUMPIXELS) ? 0 : (j + 1);
	
	for (int i = 0 ; i < NUMPIXELS ; i++) {
		int diff = i + j;
		pixels.setPixelColor(i, pixels.Color(arr[j][0], arr[j][1], arr[j][2]));
	}
	
	pixels.show();
	delay(spee);
}

void blinking(int r, int g, int b, int tim) {
	for (int i = 0 ; i < NUMPIXELS ; i++)
		pixels.setPixelColor(i, pixels.Color(r, g, b));

	pixels.show();

	delay(tim);

	for (int i = 0 ; i < NUMPIXELS ; i++)
		pixels.setPixelColor(i, pixels.Color(0,0,2));

	pixels.show();
	delay(tim);
}

void counter(int r, int g, int b, int total) {
	long current_time = millis();
	int moyen = total / NUMPIXELS;

	if (current_time - last_time > moyen * 1000) {

		for (int i = 0 ; i < lingth_on ; i++)
			pixels.setPixelColor(i, pixels.Color(r,g,b));

		pixels.show();

		for (int i = 11 ; i >= lingth_on ; i--) {
			// delay(moyen * 1000);
			pixels.setPixelColor(i, pixels.Color(0,0,0));
			pixels.show();
		}
		lingth_on--;
		last_time = millis();
	}
	
}

void snake(int r, int g, int b, int leds, int spee) {
	for(int i = 0 ; i < NUMPIXELS ; i++){
		pixels.setPixelColor(i, pixels.Color(r,g,b));    
		
		if (i >= leds)
			pixels.setPixelColor(i - leds, pixels.Color(0,0,0));
		
		if (i < leds)
			pixels.setPixelColor(NUMPIXELS - leds + i, pixels.Color(0,0,0));
		
		pixels.show();
		delay(spee);
	}
}

void color(int r, int g, int b) {
	for(int i = 0 ; i < NUMPIXELS ; i++)
		pixels.setPixelColor(i, pixels.Color(r,g,b));    

	pixels.show();
}

void stoping() {
	byte pxs[12];
	
	for (int i = 0 ; i < NUMPIXELS ; i++)
		pxs[i] = pixels.getPixelColor(i);
	
	for (int i = 0 ; i < NUMPIXELS ; i++)
		pixels.setPixelColor(i, pxs[i]);
	
		pixels.show();
}
