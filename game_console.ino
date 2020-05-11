// =======================================================================================
//            ND Game Control Starting Sketch for Notre Dame Droid Class
// =======================================================================================
//                          Last Revised Date: 03/15/2020
//                             Revised By: Prof McLaughlin
// =======================================================================================
// ---------------------------------------------------------------------------------------
//                          Libraries
// ---------------------------------------------------------------------------------------
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------------------------------------------------------------------------------
//                  Declare Scren (OLED) Items
// ---------------------------------------------------------------------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Intialize the Display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// ---------------------------------------------------------------------------------------
//                 Declare Buzzer (Sound) Items
// ---------------------------------------------------------------------------------------
const int buzzer = A2; //buzzer to arduino pin A2
long sound_millis = millis();
long previous_millis = millis();

// ---------------------------------------------------------------------------------------
//                 Declare Gamepad Button Items
// ---------------------------------------------------------------------------------------
const int up_button = 2;
const int right_button = 3;
const int down_button = 4;
const int left_button = 5;
const int start_button = 6;
const int select_button = 7;
const int joystick_button = 8;
const int joystick_x = A0;
const int joystick_y = A1;

// BUZZER
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_B3  247
#define NOTE_DS8 4978
int sounds[ 4 ][ 2 ] = { { NOTE_C4, 100 }, { NOTE_G3, 100 },{ NOTE_B3, 100 }, { NOTE_DS8, 100 } };
int toneLength;
int toneValue;

static int starting_song = 1;
static int educational_starting_song = 1;

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

int counter = 0;

// ---------------------------------------------------------------------------------------
//                 Display Routine Variable
// ---------------------------------------------------------------------------------------
char* current_screen = "INTRO";
char* educational_screen;
char* fun_screen;

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

const char* game_select[2] = {"Fun", "Educational"};

int game_number = 0;

//PING PONG
int control_input_y = 0;
int r_up_button = 0;
int r_down_button = 0;

//Screen Size Parameters
int x_pixels = 128;
int y_pixels = 32;

//Paddle Parameters
int left_paddle_height = 13;
int right_paddle_height = 13;
int paddle_width = 3;

// Ball velocities:
static int x_vel = 4;
static int y_vel = 4;

// Ball position:
static int x_pos = 5;
static int y_pos = 32;

// Paddle positions:
static int l_pos = 0;
static int r_pos = 0;

// Player scores
static int l_score = 0;
static int r_score = 0;
int paddle_height_list[4] = {13,11,9,7};
static int height_number = 0;

//Synonyms
int synonym_count = 1;
int option_number = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  

  // Set pin mode for the buzzer
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output

  // Setup Gamepad Inputs
  pinMode(up_button, INPUT);
  pinMode(down_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(select_button, INPUT);
  pinMode(start_button, INPUT);
  pinMode(joystick_button, INPUT);

// Initialize the Display - Show Splash Screen
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(x_pixels/2-20,10);
  display.println("LeT's PlAy!!");
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 4,
    0,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();

  delay(5000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("Which game do you want to play?");
  display.setCursor(13,24);
  display.println("Fun");
  display.setCursor(60,24);
  display.println("Educational");
  display.display();

}

void loop() {
  if(current_screen == "INTRO"){
    choose_game();
  }
  
  if(current_screen == "FUN"){
    play_fun_game();
  }

  if(current_screen == "EDUCATIONAL"){
    play_educational_game();
  }

  // Print to the Serial Monitor all the gamepad inputs
  output_gamepad_inputs();
  
}

void choose_game(){
  
  for(int i =0; i<2; i++){
    display.clearDisplay();
    
    
    if(game_number % 2 ==0){
      
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(20,0);
      display.println("Which game do you want to play?");
      display.setCursor(13,24);
      display.println("Fun");
      display.setCursor(60,24);
      display.println("Educational");
      display.setCursor(0,24);
      display.println(">>");
      display.display();
    
      if(!digitalRead(joystick_button)){
        display.clearDisplay();
        current_screen = "FUN";
        play_fun_game();
      }
    }
    else{
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(20,0);
      display.println("Which game do you want to play?");
      display.setCursor(13,24);
      display.println("Fun");
      display.setCursor(60,24);
      display.println("Educational");
      display.setCursor(0,24);
      display.setCursor(47,24);
      display.println(">>");
      display.display();
    
      if(!digitalRead(joystick_button)){
        display.clearDisplay();
        current_screen = "EDUCATIONAL";
        educational_screen = "SYNONYMS_INTRO";
        play_educational_game();
      }
    }
    if(analogRead(joystick_x) > 400){
      if ((previous_millis + 300) < millis()){
        game_number += 1;
        previous_millis = millis();
      }
      
    }
    if(analogRead(joystick_x) < 200){
      if ((previous_millis + 300) < millis()){
        game_number -= 1;
        previous_millis = millis();
      }
    }
  }
    
  if(starting_song){
    firstSection();
  } 
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzer, note, duration);

  if(counter % 2 == 0)
    delay(duration);
  else
    delay(duration);
  
  //Stop tone on buzzerPin
  noTone(buzzer);
 
  delay(50);
  counter++;
}
 
void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
  
  starting_song = 0;
}

void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  educational_starting_song = 0;
}

void output_gamepad_inputs() {
  int control_input = 0;
  
  control_input = digitalRead(up_button);
  if (control_input != 1) {
    Serial.println("Up Button not Pushed");    
  }
  
  control_input = digitalRead(down_button);
  if (control_input != 1) {
    Serial.println("Down Button not Pushed");    
  }

  control_input = digitalRead(left_button);
  if (control_input != 1) {
    Serial.println("Left Button not Pushed");    
  }

  control_input = digitalRead(right_button);
  if (control_input != 1) {
    Serial.println("Right Button not Pushed");    
  }

  control_input = digitalRead(select_button);
  if (control_input != 1) {
    Serial.println("Select Button not Pushed");    
  }

  control_input = digitalRead(start_button);
  if (control_input != 1) {
    Serial.println("Start Button not Pushed");    
  }

  control_input = digitalRead(joystick_button);
  if (control_input != 1) {
    Serial.println("Joystick Button not Pushed");
  }

  control_input = analogRead(joystick_x);

  if ((previous_millis + 1000) < millis()){
    if (control_input < 500 || control_input > 515) {
      Serial.println("Josystick X Value: " + String(control_input));
    }
  
    control_input = analogRead(joystick_y);
    if (control_input < 500 || control_input > 515) {
      Serial.println("Josystick Y Value: " + String(control_input));
    }
    previous_millis = millis();
  }
}

void play_fun_game(){
  starting_song = 0;
  control_input_y = analogRead(joystick_y);
  
  if(current_screen == "FUN"){
    paddle_position(control_input_y);
    ball_hit();
    diplay_elements();
    ball_paddles_hit();
    level_up();
  }
  if(fun_screen == "RESULT"){
    level_up();
  }
}

void level_up(){
  if(!digitalRead(joystick_button)){
    current_screen = "INTRO";
  }

  if (l_score == 2){
    height_number = 1;
    left_paddle_height = paddle_height_list[height_number];
  }
  if (l_score == 4){
    height_number = 2;
    left_paddle_height = paddle_height_list[height_number];
  }
  if (l_score == 6){
    height_number = 3;
    left_paddle_height = paddle_height_list[height_number];
  }
  if (r_score == 2){
    height_number = 1;
    right_paddle_height = paddle_height_list[height_number];
  }
  if (r_score == 4){
    height_number = 2;
    right_paddle_height = paddle_height_list[height_number];
  }
  if (r_score == 6){
    height_number = 3;
    right_paddle_height = paddle_height_list[height_number];
  }

  if (l_score == 8){
    display.clearDisplay();
    fun_screen = "RESULT";
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(display.width()/6,10);
    display.println("left player won");
    display.display();
    
    delay(2000);
    l_score = 0;
    r_score = 0;
    left_paddle_height = paddle_height_list[0];
    right_paddle_height = paddle_height_list[0];
    fun_screen = "GAME_OVER";
    current_screen = "INTRO";
  }

  if (r_score == 8){
    display.clearDisplay();
    fun_screen = "RESULT";
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(display.width()/6,10);
    display.println("right player won");
    display.display();
    
    delay(2000);
    l_score = 0;
    r_score = 0;
    left_paddle_height = paddle_height_list[0];
    right_paddle_height = paddle_height_list[0];
    fun_screen = "GAME_OVER";
    current_screen = "INTRO";
    }
}
int paddle_position(int control_input_y){
   
  // Update position of left paddle:
  if (digitalRead(up_button) && r_pos < (y_pixels - right_paddle_height)){r_pos += 3;}
  if (digitalRead(down_button) && r_pos > 0){r_pos -= 3;}
  
  //right paddle:
  if (control_input_y < 300 && l_pos < (y_pixels - left_paddle_height)){l_pos += 3;}
  else if (control_input_y > 415 && l_pos > 0){l_pos -= 3;}
}

void ball_hit(void){
  // Check for ball hitting a wall:
  
  if (x_pos > x_pixels-1){
    ball_reset(false);
    l_score += 1;
    tone(buzzer, 50, 100);
    delay(50);
    tone(buzzer, 50, 100);
    }  
  
  else if(x_pos < 0){
    ball_reset(true);
    r_score +=1;
    tone(buzzer, 50, 100);
    delay(50);
    tone(buzzer, 50, 100);
    }

  // Check for ball bouncing off ceiling:
    
  if (y_pos > y_pixels-1 || y_pos < 0){y_vel = -y_vel;}

  // Update ball position:
  x_pos+=x_vel;
  y_pos+=y_vel;
}

void diplay_elements(void){

  // Draw pong elements to display:
  display.clearDisplay();
  display.drawPixel(x_pos, y_pos, WHITE);
  display.fillRect(12, l_pos, paddle_width, left_paddle_height, WHITE); //x,y,w,h
  display.fillRect(x_pixels-paddle_width-12 ,r_pos, paddle_width, right_paddle_height, WHITE);

  // Display scores
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(display.width()/4,0);
  display.println(l_score);
  display.setCursor(display.width()*3/4,0);
  display.println(r_score);

  // Display all elements
  display.display();
}


void ball_paddles_hit(void){
   // Check for ball bouncing off paddles:
  if (ball_on_right_paddle()){
    x_vel = -1*x_vel;
    tone(buzzer, 300, 100);
  }
  else if (ball_on_left_paddle()){
    x_vel = -1*x_vel;
    tone(buzzer, 250, 100);
  }
}


bool ball_on_right_paddle(){
// If ball is heading towards paddle and is at the surface of paddle between the top and bottom of the paddle, then it's a hit
  return(x_pos <= (x_pixels-paddle_width-6) && x_pos >= (x_pixels-paddle_width-13) && y_pos >= r_pos && y_pos <= (r_pos + right_paddle_height) && x_vel > 0);
}

bool ball_on_left_paddle(){
  return(x_pos <= (paddle_width+13) && x_pos >= (paddle_width+6) && y_pos >= l_pos && y_pos <= (l_pos + left_paddle_height) && x_vel < 0);
}

void ball_reset(bool left){
//If left is true, then ball should launch from the left, otherwise launch from the right
//Ball should launch at a random Y location and at a random Y velocity

  y_pos = random(display.height());
  if(random(2)>0){
    y_vel = 4;
  }
  else{
    y_vel = -4;
  }

  if (left){
  x_vel = 4;
  x_pos = paddle_width+1;
  }
  
  else{
  x_vel = -4;
  x_pos = display.width()-paddle_width-2;  
  }
}


//EDUCATIONAL GAME - FIND SYNONYMS -
void play_educational_game(){
  starting_song = 0;
  
  if(educational_screen == "SYNONYMS_INTRO"){
    synonyms_intro();
  }
  if(educational_screen == "SYNONYMS-1"){
    synonym_count =1;
    synonyms_1();
  }
  if(educational_screen == "SYNONYMS-2"){
    synonym_count =2;
    synonyms_2();
  }
  if(educational_screen == "SYNONYMS-3"){
    synonym_count =3;
    synonyms_3();
  }
  if(educational_screen == "SYNONYMS-4"){
    synonym_count =4;
    synonyms_4();
  }

  if(educational_screen == "INCORRECT_ANS"){
    incorrect_ans();
  }
  if(educational_screen == "CORRECT_ANS"){
    correct_ans();
  }
  
}

void synonyms_intro(){
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(10,7);
  display.println("Find the synonym");
  display.display();
  
  if(educational_starting_song){
    secondSection();
  } 
  
  educational_screen = "SYNONYMS-1";
}

void synonyms_1(){
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.println("Whimsical");
   
    if(option_number == -1){
      option_number = 2;
    }
    
    if(option_number % 3 ==0){
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Whimsical");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Malevolent");
      display.setCursor(45,19);
      display.println("Playful");
      display.setCursor(86,10);
      display.println("Adamant");
      
      display.setCursor(6,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    else if(option_number % 3 ==1){
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Whimsical");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Malevolent");
      display.setCursor(45,19);
      display.println("Playful");
      display.setCursor(86,10);
      display.println("Adamant");
      
      display.setCursor(50,28);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone( buzzer, 2000, 100);
        delay(200);
        tone( buzzer, 5000, 400);
        display.clearDisplay();
        educational_screen = "CORRECT_ANS";
        correct_ans();
      }
    }
    else{
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Whimsical");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Malevolent");
      display.setCursor(45,19);
      display.println("Playful");
      display.setCursor(86,10);
      display.println("Adamant");
      
      display.setCursor(95,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }

    if(analogRead(joystick_x) > 400){
      if ((previous_millis + 300) < millis()){
        option_number += 1;
        previous_millis = millis();
      }
    }
    if(analogRead(joystick_x) < 300){
      if ((previous_millis + 300) < millis()){
        option_number -= 1;
        previous_millis = millis();
      }
    }
  
}

void synonyms_2(){
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.println("Laconic");
     
  if(option_number == -1){
        option_number = 2;
      }
    
    if(option_number % 3 ==0){
      
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Laconic");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Brief");
      display.setCursor(45,19);
      display.println("Verbose");
      display.setCursor(86,10);
      display.println("Strict");
      
      display.setCursor(6,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone( buzzer, 2000, 100);
        delay(200);
        tone( buzzer, 5000, 400);
        display.clearDisplay();
        educational_screen = "CORRECT_ANS";
        correct_ans();
      }
    }
    else if(option_number % 3 ==1){
      
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Laconic");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Brief");
      display.setCursor(45,19);
      display.println("Verbose");
      display.setCursor(86,10);
      display.println("Strict");
      
      display.setCursor(50,28);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    else{
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Laconic");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Brief");
      display.setCursor(45,19);
      display.println("Verbose");
      display.setCursor(86,10);
      display.println("Strict");
      
      display.setCursor(95,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    
    if(analogRead(joystick_x) > 400){
      if ((previous_millis + 300) < millis()){
        option_number += 1;
        previous_millis = millis();
      }
    }
    if(analogRead(joystick_x) < 300){
      if ((previous_millis + 300) < millis()){
        option_number -= 1;
        previous_millis = millis();
      }
    }
  
}

void synonyms_3(){
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.println("Abate");

  if(option_number == -1){
      option_number = 2;
    }

    
    if(option_number % 3 ==0){
      
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Abate");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Brash");
      display.setCursor(45,19);
      display.println("Ease");
      display.setCursor(86,10);
      display.println("Gaudy");
      
      display.setCursor(6,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    else if(option_number % 3 ==1){
      
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Abate");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Brash");
      display.setCursor(45,19);
      display.println("Ease");
      display.setCursor(86,10);
      display.println("Gaudy");
      
      display.setCursor(50,28);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone( buzzer, 2000, 100);
        delay(200);
        tone( buzzer, 5000, 400);
        display.clearDisplay();
        educational_screen = "CORRECT_ANS";
        correct_ans();
      }
    }
    else{
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Abate");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Brash");
      display.setCursor(45,19);
      display.println("Ease");
      display.setCursor(86,10);
      display.println("Gaudy");
      
      display.setCursor(95,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    
    if(analogRead(joystick_x) > 400){
      if ((previous_millis + 300) < millis()){
        option_number += 1;
        previous_millis = millis();
      }
    }
    if(analogRead(joystick_x) < 300){
      if ((previous_millis + 300) < millis()){
        option_number -= 1;
        previous_millis = millis();
      }
    }
  
}

void synonyms_4(){
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.println("Abysmal");

  if(option_number == -1){
      option_number = 2;
    }

    
    if(option_number % 3 ==0){
      
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Abysmal");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Bounded");
      display.setCursor(38,19);
      display.println("Euphoric");
      display.setCursor(73,10);
      display.println("Appalling");
      
      display.setCursor(6,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    else if(option_number % 3 ==1){
      
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Abysmal");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Bounded");
      display.setCursor(38,19);
      display.println("Euphoric");
      display.setCursor(73,10);
      display.println("Appalling");
      
      display.setCursor(50,28);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone(buzzer, sounds[0][1], sounds[0][0]);
        display.clearDisplay();
        educational_screen = "INCORRECT_ANS";
        incorrect_ans();
      }
    }
    else{
      display.setTextSize(0.5);
      display.setTextColor(WHITE);
      display.setCursor(40,0);
      display.println("Abysmal");
      
      display.setTextSize(0.1);
      display.setCursor(0,10);
      display.println("Bounded");
      display.setCursor(38,19);
      display.println("Euphoric");
      display.setCursor(73,10);
      display.println("Appalling");
      
      display.setCursor(100,20);
      display.println("^");
      
      display.display();
    
      if(!digitalRead(joystick_button)){
        tone( buzzer, 2000, 100);
        delay(200);
        tone( buzzer, 5000, 400);
        display.clearDisplay();
        educational_screen = "CORRECT_ANS";
        correct_ans();
      }
    }
    
    if(analogRead(joystick_x) > 400){
      if ((previous_millis + 300) < millis()){
        option_number += 1;
        previous_millis = millis();
      }
    }
    if(analogRead(joystick_x) < 300){
      if ((previous_millis + 300) < millis()){
        option_number -= 1;
        previous_millis = millis();
      }
    }
  
}

void correct_ans(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,10);
  display.println("CORRECT ANSWER!! :D");
  display.display();
  delay(2000);
  if(synonym_count==1)
    educational_screen = "SYNONYMS-2";

  else if(synonym_count==2)
    educational_screen = "SYNONYMS-3";
    
  else if(synonym_count==3)
    educational_screen = "SYNONYMS-4";
  
  else
    current_screen = "INTRO";
}

void incorrect_ans(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4,5);
  display.println("INCORRECT ANSWER :(");
  if(synonym_count==1){
    display.setCursor(4,17);
    display.println("It's Playful");
    display.display();
    educational_screen = "SYNONYMS-2";
  }
  else if(synonym_count==2){
    display.setCursor(4,17);
    display.println("It's Brief");
    display.display();
    educational_screen = "SYNONYMS-3";
  }
  else if(synonym_count==3){
    display.setCursor(4,17);
    display.println("It's Ease");
    display.display();
    educational_screen = "SYNONYMS-4";
  }
  else{
    display.setCursor(4,17);
    display.println("It's Appalling");
    display.display();
    current_screen = "INTRO";
  }
  delay(2000);
}
