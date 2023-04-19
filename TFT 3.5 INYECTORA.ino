// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>



// les meves variables


int Inici;
int LongBarra;
int Tinjec;int TinjecP;
int TRefre;int TRefreP;
int NumPeces;int NumPecesP;
int Tplastic;
int TFusor;


// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
//#define LCD_CS A3 // Chip Select goes to Analog 3
//#define LCD_CD A2 // Command/Data goes to Analog 2
//#define LCD_WR A1 // LCD Write goes to Analog 1
//#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_CS A3
#define LCD_RST A4
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0
#define SD_SS 10
#define SD_DI 11
#define SD_DO 12
#define ESD_SCK 13
#define LCD_D0 8
#define LCD_D1 9
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define F_CS A5

//#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

/******************* UI details */
#define BUTTON_X 52
#define BUTTON_Y 150
#define BUTTON_W 80
#define BUTTON_H 45
#define BUTTON_SPACING_X 26
#define BUTTON_SPACING_Y 30
#define BUTTON_TEXTSIZE 3


#define MINPRESSURE 10
#define MAXPRESSURE 1000


// text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 300
#define TEXT_H 50
#define TEXT_TSIZE 2
#define TEXT_TCOLOR ILI9341_MAGENTA
// the data (phone #) we store in the textfield
#define TEXT_LEN 16
char textfield[TEXT_LEN+1] = "";
uint8_t textfield_i=0;

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define TS_MINX 130
#define TS_MAXX 905

#define TS_MINY 75
#define TS_MAXY 930
// We have a status line for like, is FONA working
#define STATUS_X 10
#define STATUS_Y 65

Adafruit_GFX_Button buttons[15];
/* create 15 buttons, in classic candybar phone style */
char buttonlabels[15][5] = {"Run", "Mate", "Stop", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#" };
uint16_t buttoncolors[15] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_RED, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,ILI9341_ORANGE, ILI9341_BLUE, ILI9341_ORANGE};
                             
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

int entrada; int aaa; int bbb;
int Barra1En;

String MissatgeVellP2;



void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
  
  tft.reset();

  uint16_t identifier = tft.readID();
  
  if(identifier == 0x9325) {Serial.println(F("Found ILI9325 LCD driver"));}
  else if(identifier == 0x9328) {Serial.println(F("Found ILI9328 LCD driver"));} 
  else if(identifier == 0x4535) {Serial.println(F("Found LGDP4535 LCD driver"));}
  else if(identifier == 0x7575) {Serial.println(F("Found HX8347G LCD driver"));} 
  else if(identifier == 0x9341) {Serial.println(F("Found ILI9341 LCD driver"));}
  else if(identifier == 0x7783) {Serial.println(F("Found ST7781 LCD driver"));}
  else if(identifier == 0x8230) {Serial.println(F("Found UC8230 LCD driver"));}
  else if(identifier == 0x8357) {Serial.println(F("Found HX8357D LCD driver"));}
  else if(identifier==0x0101)   {identifier=0x9341;Serial.println(F("Found 0x9341 LCD driver"));}
  else if(identifier==0x9481){Serial.println(F("Found 0x9481 LCD driver"));}
  else if(identifier==0x9486){Serial.println(F("Found 0x9486 LCD driver"));}
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial.")); identifier=0x9486; 
  }
  tft.begin(identifier);
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

}



void loop(void) {
  
Barra1En= 190;
Tinjec= 4;TinjecP= 0;
TRefre= 8;TRefreP= 0;
NumPeces= 1;NumPecesP= 0;
Tplastic = 230;TFusor= 120;

Ppresentacio();
}

void Ppresentacio(){
        // prepara el color del fons de la pantalla
      tft.fillScreen(BLACK);  
      
      // Missatge presetacio pantalla
      tft.setCursor(30, 20); tft.setTextColor(GREEN); tft.setTextSize(3);tft.println("I.E.S. MARIANAO");
      tft.setCursor(50, 60); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Dept. Fabr. Mecanica");
      tft.setCursor(45, 100); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Sant Boi de Llobregat");


float k = 2 * 3.1416 / 360 ;
byte n = 5 ; 
byte p = 3 ;



n =  random(2,  8); 
p =  random(n+1,  12); 


byte fase = 0 ;

float x0, y0 ;
bool inicio = true ;

 for ( long  i = 0 ; i <= 360 ; i++)
         {  float y = 300 + cos( p * i * k + fase) * 120 ;
            float x = 160 + sin( n * i * k + fase) * 110 ;
            if (inicio)      // No dibujes la linea del primer punto
               { x0 = x ; y0 = y ;
                 inicio = false ;
               }
            //Tft.setPixel(x, y, CYAN);
            tft.drawLine(x0,y0,x,y, BLUE);
            x0 = x ; y0 = y ;            // Guardamos x,y para luego
          }

tft.setCursor(210, 470); tft.setTextColor(GREEN); tft.setTextSize(1);tft.println("vers. 1.0  12/18");
tft.setCursor(10, 460); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println("X. PUBILL");
delay(500);
tft.setCursor(10, 460); tft.setTextColor(BLUE); tft.setTextSize(2);tft.println("X. PUBILL");
delay(500);
tft.setCursor(10, 460); tft.setTextColor(RED); tft.setTextSize(2);tft.println("X. PUBILL");
delay(500);
tft.setCursor(10, 460); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println("X. PUBILL");
delay(500);
 
delay(2000);
Pprincipal();
  
}


void Pprincipal(){ 
      // prepara el color del fons de la pantalla
      tft.fillScreen(BLACK);
      
      // creacio rectangle missatges a peu pantalla
      tft.drawRect(20, 420, 280, 40, ILI9341_WHITE);
      tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Selecciona el MODE");MissatgeVellP2="Selecciona el MODE";
      
      // Missatge presetacio pantalla
      tft.setCursor(65, 25); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("SELECCIONA OPCIO");
      

      // menus de la pantalla
      buttons[1].initButton(&tft, 280,  80, 60, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_WHITE,"--->", 2);  buttons[1].drawButton();
      buttons[2].initButton(&tft, 120, 125,200, BUTTON_H, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_BLACK,"MANUAL", 3);  buttons[2].drawButton();
      buttons[3].initButton(&tft, 120, 200,200, BUTTON_H, ILI9341_WHITE, ILI9341_RED, ILI9341_BLACK,"AUTOMATIC", 3);  buttons[3].drawButton();
      buttons[4].initButton(&tft, 120, 275,200, BUTTON_H, ILI9341_WHITE, ILI9341_ORANGE, ILI9341_BLACK,"PARAMETRES", 3);  buttons[4].drawButton();
      buttons[5].initButton(&tft, 120, 350,200, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_BLACK,"---------", 3);  buttons[5].drawButton();

    TSPoint p = ts.getPoint(); pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);
    // Scale from ~0->4000 to tft.width using the calibration #'s
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  {p.x = p.x + p.y;p.y = p.x - p.y;p.x = p.x - p.y;p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));}

Serial.println("entro en el bucle");
for(aaa=0;aaa<9999;aaa++)
  {for(bbb=0;bbb< 9999;bbb++)
  { 

// Scale from ~0->4000 to tft.width using the calibration #'s
  TSPoint p = ts.getPoint(); pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  {p.x = p.x + p.y;p.y = p.x - p.y;p.x = p.x - p.y;p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));}

// go thru all the buttons, checking if they were pressed

  int i;
  for (i = 1; i < 6; i++) { //  el valor de i permite definir el grosor de la linea
  if ((buttons[i].contains(p.x, p.y))&&p.x>10) { buttons[i].press(true);} else {buttons[i].press(false);}
  if (buttons[i].justReleased()) {buttons[i].drawButton();}}  // draw normal

    
if (buttons[1].justPressed()) {buttons[1].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Sortir");Serial.println("apretat boto sortida");MissatgeVellP2="Sortir";Ppresentacio(); }

if (buttons[2].justPressed()) {buttons[2].drawButton(true); // draw invert!
  tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);
  tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Manual");
  MissatgeVellP2="Obrir Motlle";Manual();}

if (buttons[3].justPressed()) {buttons[3].drawButton(true); // draw invert!
  tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);
  tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Automatic");
  MissatgeVellP2="Automatic";Automatic();}

if (buttons[4].justPressed()) {buttons[4].drawButton(true); // draw invert!
  tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);
  tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("PARAMETRES");
  MissatgeVellP2="PARAMETRES";}

if (buttons[5].justPressed()) {buttons[5].drawButton(true); // draw invert!
  tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);
  tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("---------");
  MissatgeVellP2="---------";}
     
}}}


void Manual(){  // modo manual

      // prepara el color del fons de la pantalla
      tft.fillScreen(BLACK);
      
      // creacio rectangle missatges a peu pantalla
      tft.drawRect(20, 420, 280, 40, ILI9341_WHITE);
      tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Selecciona el moviment");MissatgeVellP2="Selecciona el moviment";
      
      // Missatge presetacio pantalla
      tft.setCursor(75, 25); tft.setTextColor(GREEN); tft.setTextSize(3);tft.println("MODE MANUAL");
      
      // menus de la pantalla
      String Ret2; 
      Ret2="Obrir Motlle";
      
      buttons[1].initButton(&tft, 280,  80, 60, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_WHITE,"--->", 2);  buttons[1].drawButton();
      buttons[2].initButton(&tft, 120, 100,180, BUTTON_H, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_BLACK, "Obrir Motlle", 2);  buttons[2].drawButton();
      buttons[3].initButton(&tft, 120, 160,180, BUTTON_H, ILI9341_WHITE, ILI9341_RED, ILI9341_BLACK,"Tancar Motlle", 2);  buttons[3].drawButton();
      buttons[4].initButton(&tft, 120, 220,180, BUTTON_H, ILI9341_WHITE, ILI9341_ORANGE, ILI9341_BLACK,"Injectar", 2);  buttons[4].drawButton();
      buttons[5].initButton(&tft, 120, 280,180, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_BLACK,"At. injectada", 2);  buttons[5].drawButton();


     // Control de temperatura
      tft.setCursor(10, 350); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Tempe inj");
      buttons[6].initButton(&tft, 180, 350,20, BUTTON_H, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_WHITE,"+", 2);  buttons[6].drawButton();
      buttons[7].initButton(&tft, 150, 350,20, BUTTON_H, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_WHITE,"-", 2);  buttons[7].drawButton();
      tft.setCursor(260, 365); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
      tft.setCursor(210, 365); tft.setTextColor(BLUE); tft.setTextSize(2);tft.println(TFusor);    // temperatura actual del fusor

     

    TSPoint p = ts.getPoint(); pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);
    // Scale from ~0->4000 to tft.width using the calibration #'s
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  {p.x = p.x + p.y;p.y = p.x - p.y;p.x = p.x - p.y;p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));}


Barra1En=400;

DibujaBarra1 ();
TempBarra1 ();
LongBarra=175;
DibujaTriangle1 ();


Serial.println("entro en el bucle");
for(aaa=0;aaa<9999;aaa++)
  {for(bbb=0;bbb< 9999;bbb++)
  { 

// Scale from ~0->4000 to tft.width using the calibration #'s
  TSPoint p = ts.getPoint(); pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  {p.x = p.x + p.y;p.y = p.x - p.y;p.x = p.x - p.y;p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));}

// go thru all the buttons, checking if they were pressed

  int i;
  for (i = 1; i < 6; i++) { //  el valor de i permite definir el grosor de la linea
  if ((buttons[i].contains(p.x, p.y))&&p.x>10) { buttons[i].press(true);} else {buttons[i].press(false);}
  if (buttons[i].justReleased()) {buttons[i].drawButton();}}  // draw normal
      
  if (buttons[1].justPressed()) {buttons[1].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Sortir");Serial.println("apretat boto sortida");MissatgeVellP2="Sortir";;Pprincipal(); }
  if (buttons[2].justPressed()) {buttons[2].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Obrir Motlle");MissatgeVellP2="Obrir Motlle";}
  if (buttons[3].justPressed()) {buttons[3].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Tancar Motlle");MissatgeVellP2="Tancar Motlle";}
  if (buttons[4].justPressed()) {buttons[4].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Injectar");MissatgeVellP2="Injectar";}
  if (buttons[5].justPressed()) {buttons[5].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Aturar Injectada");MissatgeVellP2="Aturar Injectada";}
     
   // control de la temperatura

     if ((buttons[6].contains(p.x, p.y))&&p.x>10) { buttons[6].press(true);} else {buttons[6].press(false);}
      if ((buttons[7].contains(p.x, p.y))&&p.x>10) { buttons[7].press(true);} else {buttons[7].press(false);}
      if (buttons[6].justReleased()) {buttons[6].drawButton();}  // draw normal
      if (buttons[7].justReleased()) {buttons[7].drawButton();}  // draw normal
  

        if (buttons[6].justPressed()) {buttons[6].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); 
            tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);
            BorraTriangle1 ();
            tft.setCursor(260, 365); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
            Tplastic=Tplastic+10;
            if (Tplastic>300){Tplastic=300 ;}
            tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
            tft.println("Pujar Temperatura");
            tft.setCursor(260, 365); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
            MissatgeVellP2=Tplastic;
            DibujaTriangle1 ();
            MissatgeVellP2="Pujar Temperatura";
        }
        
        if (buttons[7].justPressed()) {buttons[7].drawButton(true); tft.setCursor(30, 430); tft.setTextColor(BLACK);
            tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2); 
            BorraTriangle1 ();
            tft.setCursor(260, 365); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
            if (Tplastic<10){Tplastic=10 ;}
            Tplastic=Tplastic-10;
            tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE);tft.setTextSize(2);
            tft.println("Baixar  Temperatura");
            tft.setCursor(260, 365); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
            MissatgeVellP2=Tplastic;
            DibujaTriangle1 ();
            MissatgeVellP2="Baixar  Temperatura";
        }   
}}}


void Automatic(){ 

      Barra1En= 190;
  
      tft.fillScreen(BLACK);     // prepara el color del fons de la pantalla
      
      // creacio rectangle missatges a peu pantalla
      tft.drawRect(20, 420, 280, 40, ILI9341_WHITE);
      tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Defin. i activa");MissatgeVellP2="Defin. i activa";
      
      tft.setCursor(55, 15); tft.setTextColor(GREEN); tft.setTextSize(3);tft.println("M. AUTOMATIC");    // Missatge presetacio pantalla

      tft.setCursor(210, 150); tft.setTextColor(BLUE); tft.setTextSize(2);tft.println(TFusor);    // temperatura actual del fusor
      tft.setCursor(260, 150); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
      tft.setCursor(270, 240); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(Tinjec);    // Temps injeccio
      tft.setCursor(270, 300); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(TRefre);    // Temps refredament
      tft.setCursor(270, 360); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(NumPeces);    // Peces

      tft.setCursor(220, 240); tft.setTextColor(BLUE); tft.setTextSize(3);tft.println(TinjecP);    // Temps injeccio
      tft.setCursor(220, 300); tft.setTextColor(BLUE); tft.setTextSize(3);tft.println(TRefreP);    // Temps refredament
      tft.setCursor(220, 360); tft.setTextColor(BLUE); tft.setTextSize(3);tft.println(NumPecesP);    // Peces
       
      // Missatges de configuracio
      tft.setCursor(10, 135); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Tempe inj");
      tft.setCursor(10, 240); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Temps Inj");
      tft.setCursor(10, 300); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Temps refr");
      tft.setCursor(10, 360); tft.setTextColor(GREEN); tft.setTextSize(2);tft.println("Peces");
      
      // menus de la pantalla
      
      buttons[1].initButton(&tft, 280,  80, 60, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_WHITE,"--->", 2);  buttons[1].drawButton();
      
      buttons[2].initButton(&tft, 180, 140,20, BUTTON_H, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_WHITE,"+", 2);  buttons[2].drawButton();
      buttons[3].initButton(&tft, 180, 250,20, BUTTON_H, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE,"+", 2);  buttons[3].drawButton();
      buttons[4].initButton(&tft, 180, 310,20, BUTTON_H, ILI9341_WHITE, ILI9341_ORANGE, ILI9341_WHITE,"+", 2);  buttons[4].drawButton();
      buttons[5].initButton(&tft, 180, 370,20, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_WHITE,"+", 2);  buttons[5].drawButton();

      buttons[6].initButton(&tft, 150, 140,20, BUTTON_H, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_WHITE,"-", 2);  buttons[6].drawButton();
      buttons[7].initButton(&tft, 150, 250,20, BUTTON_H, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE,"-", 2);  buttons[7].drawButton();
      buttons[8].initButton(&tft, 150, 310,20, BUTTON_H, ILI9341_WHITE, ILI9341_ORANGE, ILI9341_WHITE,"-", 2);  buttons[8].drawButton();
      buttons[9].initButton(&tft, 150, 370,20, BUTTON_H, ILI9341_WHITE, ILI9341_BLUE, ILI9341_WHITE,"-", 2);  buttons[9].drawButton();

      buttons[10].initButton(&tft, 60, 80,100, BUTTON_H, ILI9341_WHITE, ILI9341_GREEN, ILI9341_BLACK,"Inicia", 2);  buttons[10].drawButton();
      buttons[11].initButton(&tft, 180, 80,100, BUTTON_H, ILI9341_WHITE, ILI9341_RED, ILI9341_BLACK,"Atura", 2);  buttons[11].drawButton();

    TSPoint p = ts.getPoint(); pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);
    // Scale from ~0->4000 to tft.width using the calibration #'s
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  {p.x = p.x + p.y;p.y = p.x - p.y;p.x = p.x - p.y;p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));}

Serial.println("entro en el bucle");


DibujaBarra1 ();
TempBarra1 ();
LongBarra=175;
DibujaTriangle1 ();

for(aaa=0;aaa<9999;aaa++)
  {for(bbb=0;bbb< 9999;bbb++)
  { 

// Scale from ~0->4000 to tft.width using the calibration #'s
  TSPoint p = ts.getPoint(); pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  {p.x = p.x + p.y;p.y = p.x - p.y;p.x = p.x - p.y;p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));}

// go thru all the buttons, checking if they were pressed

  int i;
  for (i = 1; i < 12; i++) { //  el valor de i permite definir el grosor de la linea
  if ((buttons[i].contains(p.x, p.y))&&p.x>10) { buttons[i].press(true);} else {buttons[i].press(false);}
  if (buttons[i].justReleased()) {buttons[i].drawButton();}}  // draw normal
 


      
  if (buttons[1].justPressed()) {buttons[1].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);tft.println("Sortir");Serial.println("apretat boto sortida");MissatgeVellP2="Sortir";;Pprincipal(); }


// botons de temperatura
  if (buttons[2].justPressed()) {buttons[2].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); 
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2);
      BorraTriangle1 ();
      tft.setCursor(260, 150); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
      Tplastic=Tplastic+10;
      if (Tplastic>300){Tplastic=300 ;}
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.println("Pujar Temperatura");
      tft.setCursor(260, 150); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
      MissatgeVellP2=Tplastic;
      DibujaTriangle1 ();
      MissatgeVellP2="Pujar Temperatura";
  }
  
  if (buttons[6].justPressed()) {buttons[6].drawButton(true); tft.setCursor(30, 430); tft.setTextColor(BLACK);
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(BLACK); tft.setTextSize(2); 
      BorraTriangle1 ();
      tft.setCursor(260, 150); tft.setTextColor(BLACK); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
      if (Tplastic<10){Tplastic=10 ;}
      Tplastic=Tplastic-10;
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE);tft.setTextSize(2);
      tft.println("Baixar  Temperatura");
      tft.setCursor(260, 150); tft.setTextColor(YELLOW); tft.setTextSize(2);tft.println(Tplastic);    // Temperatura que necessita el plastic
      MissatgeVellP2=Tplastic;
      DibujaTriangle1 ();
      MissatgeVellP2="Baixar  Temperatura";
  }
    
  if (buttons[3].justPressed()) {buttons[3].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); 
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(270, 240); tft.setTextColor(BLACK); tft.setTextSize(3);tft.println(Tinjec);    // Temps injeccio
      Tinjec=Tinjec+1;
      tft.setCursor(270, 240); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(Tinjec);    // Temps injeccio
      tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Puja Temps Injec");MissatgeVellP2="Puja Temps Injec";
  }
  
  if (buttons[4].justPressed()) {buttons[4].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK);
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(270, 300); tft.setTextColor(BLACK); tft.setTextSize(3);tft.println(TRefre);    // Temps refredament
      TRefre=TRefre+1;
      tft.setCursor(270, 300); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(TRefre);    // Temps refredament
      tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Puja Temps Refredat");MissatgeVellP2="Puja Temps Refredat";
  }
  
  if (buttons[5].justPressed()) {buttons[5].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK);
    tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.setCursor(270, 360); tft.setTextColor(BLACK); tft.setTextSize(3);tft.println(NumPeces);    // Peces
    NumPeces=NumPeces+1;
    tft.setCursor(270, 360); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(NumPeces);    // Peces
    tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Mes Peces");MissatgeVellP2="Mes Peces";
  }



  if (buttons[7].justPressed()) {buttons[7].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK); 
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(270, 240); tft.setTextColor(BLACK); tft.setTextSize(3);tft.println(Tinjec);    // Temps injeccio
      Tinjec=Tinjec-1;
      if (Tinjec<1){Tinjec=1 ;}
      tft.setCursor(270, 240); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(Tinjec);    // Temps injeccio
      tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Baixa Temps Injec");MissatgeVellP2="Baixa Temps Injec";
  }
  if (buttons[8].justPressed()) {buttons[8].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK);
      tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(270, 300); tft.setTextColor(BLACK); tft.setTextSize(3);tft.println(TRefre);    // Temps refredament
      TRefre=TRefre-1;
      if (TRefre<1){TRefre=1 ;}
      tft.setCursor(270, 300); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(TRefre);    // Temps refredament
      tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Baixa Temps Refredat");MissatgeVellP2="Baixa Temps Refredat";
  }
  
  if (buttons[9].justPressed()) {buttons[9].drawButton(true);tft.setCursor(30, 430); tft.setTextColor(BLACK);
    tft.setTextSize(2);tft.println(MissatgeVellP2);tft.setCursor(30, 430); tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.setCursor(270, 360); tft.setTextColor(BLACK); tft.setTextSize(3);tft.println(NumPeces);    // Peces
    NumPeces=NumPeces-1;
    if (NumPeces<1){NumPeces=1 ;}
    tft.setCursor(270, 360); tft.setTextColor(YELLOW); tft.setTextSize(3);tft.println(NumPeces);    // Peces
    tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Menys Peces");MissatgeVellP2="Menys Peces";
  }

  if (buttons[10].justPressed()) {
    buttons[10].drawButton(true);
    tft.setCursor(30, 430); tft.setTextColor(BLACK);tft.setTextSize(2);tft.println(MissatgeVellP2);
    tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Inici Produccio");MissatgeVellP2="Inici Produccio";
  }

  if (buttons[11].justPressed()) {
    buttons[11].drawButton(true);
    tft.setCursor(30, 430); tft.setTextColor(BLACK);tft.setTextSize(2);tft.println(MissatgeVellP2);
    tft.setCursor(30, 430);tft.setTextColor(WHITE);tft.setTextSize(2);tft.println("Atura");MissatgeVellP2="Atura";
  }
       
}}}


void DibujaBarra1 (){ 
  int i;
  for (i = 0; i < 8; i++) { //  el valor de i permite definir el grosor de la linea
  tft.drawLine(10, Barra1En+i, 300, Barra1En+i, ILI9341_LIGHTGREY);} }

void TempBarra1 (){ 
  int i;
  for (i = 0; i < 8; i++) { //  el valor de i permite definir el grosor de la linea
  tft.drawLine(10, Barra1En+i, 120, Barra1En+i, ILI9341_NAVY); } }

void DibujaTriangle1 (){ 
  int i;
  for (i = 0; i < 12; i++) { //  el valor de i permite definir el grosor de la linea
  tft.drawLine(Tplastic, Barra1En-5, Tplastic, Barra1En-5, ILI9341_YELLOW);
  tft.drawLine(Tplastic-i, Barra1En-5-i, Tplastic+i, Barra1En-5-i, ILI9341_YELLOW); } }

void BorraTriangle1 (){ 
  int i;
  for (i = 0; i < 12; i++) { //  el valor de i permite definir el grosor de la linea
  tft.drawLine(Tplastic, Barra1En-5, Tplastic, Barra1En-5, ILI9341_BLACK);
  tft.drawLine(Tplastic-i, Barra1En-5-i, Tplastic+i, Barra1En-5-i, ILI9341_BLACK);} }
