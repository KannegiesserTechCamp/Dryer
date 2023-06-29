#include <Arduino.h>
#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#include "LED.h"

// Defines 
#define LED_DATA_PIN 26

// Private variables
NeoPixelBus<NeoGrbFeature, NeoWs2811Method> LedStreifen(AnzahlLeds, LED_DATA_PIN);
RgbColor AktuelleFarben[AnzahlLeds];

// Private functions
RgbColor GetRgbColor(Farbe Farbe, uint8_t Helligkeit)
{
    if(Helligkeit > 100)
    {
        Helligkeit = 100;
    }
    uint8_t ui8Helligkeit = (uint8_t)(Helligkeit * 2.55);

    switch (Farbe)
    {
        case schwarz:
            return RgbColor(0, 0, 0);
        
        case weiss:
            return RgbColor(ui8Helligkeit, ui8Helligkeit, ui8Helligkeit);

        case rot:
            return RgbColor(ui8Helligkeit, 0, 0);

        case gruen:
            return RgbColor(0, ui8Helligkeit, 0);
            
        case blau:
            return RgbColor(0, 0, ui8Helligkeit);
            
        case gelb:
            return RgbColor(ui8Helligkeit, ui8Helligkeit, 0);

        case cyan:
            return RgbColor(0, ui8Helligkeit, ui8Helligkeit);
        
        case magenta:
            return RgbColor(ui8Helligkeit, 0, ui8Helligkeit);

        default:
            return RgbColor(0, 0, 0);
    }
}

// Public functions
void LedInitialisierung()
{
    for (int i = 0; i < AnzahlLeds; i++)
    {
        AktuelleFarben[i] = RgbColor(0, 0, 0);
    }

    LedStreifen.Begin();
    LedStreifen.Show();
}

void LedEinzelFarbeHelligkeit(uint8_t LedNummer, Farbe Farbe, uint8_t Helligkeit)
{
    if(LedNummer < AnzahlLeds)
    {
        RgbColor color = GetRgbColor(Farbe, Helligkeit);
        LedStreifen.SetPixelColor(LedNummer, color);
        AktuelleFarben[LedNummer] = color;
    }
    LedStreifen.Show();
}

void LedEinzelRGB(uint8_t LedNummer, uint8_t Rot, uint8_t Gruen, uint8_t Blau)
{
    if(LedNummer < AnzahlLeds)
    {
        RgbColor color = RgbColor(Rot, Gruen, Blau);
        LedStreifen.SetPixelColor(LedNummer, color);
        AktuelleFarben[LedNummer] = color;
    }
    LedStreifen.Show();
}

void LedLeisteFarbeHelligkeit(Farbe Farbe, uint8_t Helligkeit)
{
    RgbColor color = GetRgbColor(Farbe, Helligkeit);
    for (int i = 0; i < AnzahlLeds; i++)
    {
        LedStreifen.SetPixelColor(i, color);
        AktuelleFarben[i] = color;
    }
    LedStreifen.Show();
}

void LedLeisteRGB(uint8_t Rot, uint8_t Gruen, uint8_t Blau)
{
    RgbColor color = RgbColor(Rot, Gruen, Blau);
    for (int i = 0; i < AnzahlLeds; i++)
    {
        LedStreifen.SetPixelColor(i, color);
        AktuelleFarben[i] = color;
    }
    LedStreifen.Show();
}

void LedLeisteEin()
{
    for (int i = 0; i < AnzahlLeds; i++)
    {
        RgbColor color = AktuelleFarben[i];
        LedStreifen.SetPixelColor(i, color);
    }
    LedStreifen.Show();
}

void LedLeisteAus()
{
    for (int i = 0; i < AnzahlLeds; i++)
    {
        LedStreifen.SetPixelColor(i, RgbColor(0, 0, 0));
    }
    LedStreifen.Show();
}

void LedLeisteLoeschen()
{
    for (int i = 0; i < AnzahlLeds; i++)
    {
        RgbColor color = RgbColor(0, 0, 0);
        LedStreifen.SetPixelColor(i, color);
        AktuelleFarben[i] = color;
    }
    LedStreifen.Show();
}
