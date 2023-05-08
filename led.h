#include <FastLED.h>

#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS 22
#define LED_PIN 5
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 200
#define UPDATES_PER_SECOND 45

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void FillLEDsFromPaletteColors( uint8_t colorIndex) //Fills LED's from palette
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void setAllLEDs(int red, int green, int blue) {
    currentBlending = NOBLEND;

    CRGB color = CRGB(red, green, blue);
    Serial.println(color);
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
    FastLED.show();
}

void northernLightsV2(uint8_t index) {
    currentBlending = LINEARBLEND;

    // This is where you can make up your own colors to play with. Look-up 'CHSV' to understand what the color's 3 values represent.
    CRGB purple = CHSV( 195, 255, 255);
    CRGB green  = CHSV( 100, 255, 255);
    CRGB graqua  = CHSV( 114, 255, 255);
    CRGB aqua  = CHSV( 110, 255, 255);
    CRGB teal = CHSV( 136, 255, 255);
    CRGB blue = CHSV( 160, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16( // This is where you decide the order of the colors you created above. They are assigned to 16 LED's at a time, in the following order:
                                   green,  green,  aqua,  aqua,
                                   green,  green,   green, green,
                                   green, green, aqua,  aqua,
                                  green,   green,   green,  aqua);
    
    FillLEDsFromPaletteColors(index);
        
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void AuroraPalette_green_blue_purple() // Custom color palette for LED's. Here, you can experiment with your own colors for the LED's.
{
    // This is where you can make up your own colors to play with. Look-up 'CHSV' to understand what the color's 3 values represent.
    CRGB purple = CHSV( 195, 255, 255);
    CRGB green  = CHSV( 100, 255, 255);
    CRGB graqua  = CHSV( 114, 255, 255);
    CRGB aqua  = CHSV( 110, 255, 255);
    CRGB teal = CHSV( 136, 255, 255);
    CRGB blue = CHSV( 160, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16( // This is where you decide the order of the colors you created above. They are assigned to 16 LED's at a time, in the following order:
                                   green,  green,  aqua,  aqua,
                                   green,  green,   green, green,
                                   green, green, aqua,  aqua,
                                  green,   green,   green,  aqua);
}
void AuroraPalette_green_blue() // Custom color palette for LED's. Here, you can experiment with your own colors for the LED's.
{
    // This is where you can make up your own colors to play with. Look-up 'CHSV' to understand what the color's 3 values represent.
    CRGB purple = CHSV( 195, 255, 255);
    CRGB green  = CHSV( 100, 255, 255);
    CRGB graqua  = CHSV( 114, 255, 255);
    CRGB aqua  = CHSV( 110, 255, 255);
    CRGB teal = CHSV( 136, 255, 255);
    CRGB blue = CHSV( 160, 255, 255);
    CRGB red = CHSV( 255, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16( // This is where you decide the order of the colors you created above. They are assigned to 16 LED's at a time, in the following order:
                                   red,  green,  aqua,  aqua,
                                   green,  green,   green, green,
                                   green, green, aqua,  aqua,
                                  green,   green,   green,  aqua);
}

void northernLights(uint8_t index)
{
  AuroraPalette_green_blue_purple();
  AuroraPalette_green_blue();
  FillLEDsFromPaletteColors(index);
    
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void setupLED() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    setAllLEDs(0, 0, 0);
    FastLED.setBrightness(BRIGHTNESS);
}
