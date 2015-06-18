//////////////////////////////////////////////////////////
//        +--------------------------------+            //
//        |   0000  0000   0000      0000  |            //
//        |   0  0  0   0  0  0 0000   0   |            //
//        |   0000  0   0  0000       0    |            //
//        +--------------------------------+            //
//          a one-handed semabic keyboard               //
//                                                      //
//           inspired by the Microwriter                //
//                                                      //
//           implemented by Jens Kaufmann               //
//     based on the Stenogloves code by Ross Goodwin    //
//                   Version 0.1                        //
//////////////////////////////////////////////////////////

int pins[7] = {2, 3, 4, 5, 6, 7, 8};            //Pins The buttons are attached to in the following order 2=C, 3=N, 4=I, 5=M, 6=R, 7=P, 8=F
int keyStatus[8]= {0, 0, 0, 0, 0, 0, 0, 0};     // Bufferarray one 
int keyStatus2[8] = {0, 0, 0, 0, 0, 0, 0, 0};   // Bufferarray two
boolean waiting = false;


char ctrlKey = KEY_LEFT_CTRL;    // Character to be send for holding down "Control"
char shiftKey = KEY_LEFT_SHIFT;  // Character to be send for holding down "shift"  
char altKey = KEY_LEFT_ALT;      // Character to be send for holding down "alt"
char guiKey = KEY_LEFT_GUI;      // Character to be send for holding down "Command"
char winKey = 0x80;              // Character to be send for holding down "Win"



// ---Modifiers---
//boolean state_ctrl=false;
//boolean state_alt=false;
//boolean pressed_alt_gr=false;
//boolean state_shift=false;
//boolean state_CMD=false;    




int chords[128] = { // KeyMap Modified Microwriter
   
  
//  Char    	    F  C  N    I  M  R  P    Description 
      0,  	//  -  -  -    -  -  -  -    "Nothing"
    117,	//  -  -  -    -  -  -  +    key_u
    115,	//  -  -  -    -  -  +  -    key_s
    103,	//  -  -  -    -  -  +  +    key_g
    111,	//  -  -  -    -  +  -  -    key_o
    113,	//  -  -  -    -  +  -  +    key_q
    110,	//  -  -  -    -  +  +  -    key_n
     98,	//  -  -  -    -  +  +  +    key_b
    101,	//  -  -  -    +  -  -  -    key_e 
    118,	//  -  -  -    +  -  -  +    key_v
    116,	//  -  -  -    +  -  +  -    key_t
     44,	//  -  -  -    +  -  +  +    key_comma
     97,	//  -  -  -    +  +  -  -    key_a
     64,	//  -  -  -    +  +  -  +    "key_@"
     46,	//  -  -  -    +  +  +  -    key_fullstop
    109,	//  -  -  -    +  +  +  +    key_m
  	
      8,  	//  -  -  +    -  -  -  -    "Backspace"
     56,        //  -  -  +    -  -  -  +    "8"
     52,	//  -  -  +    -  -  +  -    "4"
     43,	//  -  -  +    -  -  +  +    "+"
     50,	//  -  -  +    -  +  -  -    "2"
     48,	//  -  -  +    -  +  -  +    "0"
     54,	//  -  -  +    -  +  +  -    "6"
     45,	//  -  -  +    -  +  +  +    "-"
     49,	//  -  -  +    +  -  -  -    "1" 
     57,	//  -  -  +    +  -  -  +    "9"
     53,	//  -  -  +    +  -  +  -    "5"
     42,	//  -  -  +    +  -  +  +    "*"
     51,	//  -  -  +    +  +  -  -    "3"
     47,	//  -  -  +    +  +  -  +    "/"
     55,	//  -  -  +    +  +  +  -    "7"
    176,	//  -  -  +    +  +  +  +    Return

     32,  	//  -  +  -    -  -  -  -    key_space
    104,	//  -  +  -    -  -  -  +    key_h
    107,	//  -  +  -    -  -  +  -    key_k
    106,	//  -  +  -    -  -  +  +    key_j
     99,	//  -  +  -    -  +  -  -    key_c
    122,	//  -  +  -    -  +  -  +    key_z
    121,	//  -  +  -    -  +  +  -    key_y
    120,	//  -  +  -    -  +  +  +    key_x
    105,	//  -  +  -    +  -  -  -    key_i 
    108,	//  -  +  -    +  -  -  +    key_l
    114,	//  -  +  -    +  -  +  -    key_r
    119,	//  -  +  -    +  -  +  +    key_w
    100,	//  -  +  -    +  +  -  -    key_d
     39,	//  -  +  -    +  +  -  +    key_Apostrophe
    102,	//  -  +  -    +  +  +  -    key_f
    112,	//  -  +  -    +  +  +  +    key_p
  	
    177,  	//  -  +  +    -  -  -  -    "ESC"
     33,	//  -  +  +    -  -  -  +    key_!
     63,	//  -  +  +    -  -  +  -    key_?
     61,	//  -  +  +    -  -  +  +    key_=
     95,	//  -  +  +    -  +  -  -    key__
     34,	//  -  +  +    -  +  -  +    key_"
     35,	//  -  +  +    -  +  +  -    key_#  
     91,	//  -  +  +    -  +  +  +    key_[
     40,	//  -  +  +    +  -  -  -    key_( 
     41,	//  -  +  +    +  -  -  +    key_)
    125,	//  -  +  +    +  -  +  -    key_}
    156,	//  -  +  +    +  -  +  +    key_pound
    123,	//  -  +  +    +  +  -  -    key_{
     92,	//  -  +  +    +  +  -  +    key_\
     93,	//  -  +  +    +  +  +  -    key_]
     38,	//  -  +  +    +  +  +  +    key_&
  	  
    500,  	//  +  -  -    -  -  -  -    "Shift_pressed"
    217,	//  +  -  -    -  -  -  +    "Arrow_DOWN"
    218,	//  +  -  -    -  -  +  -    "Arrow_UP"
    212,	//  +  -  -    -  -  +  +    "Delete" 
    216,	//  +  -  -    -  +  -  -    "Arrow_LEFT"
    214,	//  +  -  -    -  +  -  +    "Page_down"
    179,	//  +  -  -    -  +  +  -    "Tab"
    176,	//  +  -  -    -  +  +  +    "Return"
    215,	//  +  -  -    +  -  -  -    "Arrow_RIGHT" 
    504,	//  +  -  -    +  -  -  +    "Win_key"
    211,	//  +  -  -    +  -  +  -    "Page_up"
    213,	//  +  -  -    +  -  +  +    "End"
    502,	//  +  -  -    +  +  -  -    "Alt_pressed"
    210,	//  +  -  -    +  +  -  +    "Home"  
    503,	//  +  -  -    +  +  +  -    "CMD/WIN_pressed"
    501,	//  +  -  -    +  +  +  +    "Ctrl_pressed"
  	
      0,  	//  +  -  +    -  -  -  -    ""
    000,	//  +  -  +    -  -  -  +    key_
    000,	//  +  -  +    -  -  +  -    key_
    000,	//  +  -  +    -  -  +  +    key_
    000,	//  +  -  +    -  +  -  -    key_
    000,	//  +  -  +    -  +  -  +    key_
    000,	//  +  -  +    -  +  +  -    key_
    000,	//  +  -  +    -  +  +  +    key_
    000,	//  +  -  +    +  -  -  -    key_ 
    000,	//  +  -  +    +  -  -  +    key_
    000,	//  +  -  +    +  -  +  -    key_
    000,	//  +  -  +    +  -  +  +    key_
    000,	//  +  -  +    +  +  -  -    key_
    000,	//  +  -  +    +  +  -  +    key_
    000,	//  +  -  +    +  +  +  -    key_
    000,	//  +  -  +    +  +  +  +    key_
    
     0,  	//  +  +  -    -  -  -  -    ""
     36,	//  +  +  -    -  -  -  +    key_$
     37,	//  +  +  -    -  -  +  -    key_%
     94,	//  +  +  -    -  -  +  +    key_^
     60,	//  +  +  -    -  +  -  -    key_<
    126,	//  +  +  -    -  +  -  +    key_~
     62,	//  +  +  -    -  +  +  -    key_>
    000,	//  +  +  -    -  +  +  +    key_
     59,	//  +  +  -    +  -  -  -    key_; 
     94,	//  +  +  -    +  -  -  +    key_^
    000,	//  +  +  -    +  -  +  -    key_
    000,	//  +  +  -    +  -  +  +    key_
     58,	//  +  +  -    +  +  -  -    key_:
     96,	//  +  +  -    +  +  -  +    key_`
    000,	//  +  +  -    +  +  +  -    key_
    124,	//  +  +  -    +  +  +  +    key_|
    
    0,  	//  +  +  +    -  -  -  -    ""
    000,	//  +  +  +    -  -  -  +    key_
    000,	//  +  +  +    -  -  +  -    key_
    000,	//  +  +  +    -  -  +  +    key_
    000,	//  +  +  +    -  +  -  -    key_
    000,	//  +  +  +    -  +  -  +    key_
    000,	//  +  +  +    -  +  +  -    key_
    000,	//  +  +  +    -  +  +  +    key_
    000,	//  +  +  +    +  -  -  -    key_ 
    000,	//  +  +  +    +  -  -  +    key_
    000,	//  +  +  +    +  -  +  -    key_
    000,	//  +  +  +    +  -  +  +    key_
    000,	//  +  +  +    +  +  -  -    key_
    000,	//  +  +  +    +  +  -  +    key_
    000,	//  +  +  +    +  +  +  -    key_
    000,	//  +  +  +    +  +  +  +    key_
  
};

void setup() {
  for (int i=0; i<=6; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
  Keyboard.begin();
  // Serial.begin(9600);
  // Serial.println("setup() finished!");
}

void loop() {
  checkKeys();
  if (keyPressed()) {
    waitForRelease();
  } else {
    waiting = true;
  }
  
}

void checkKeys() {
  for (int i=0; i<=6; i++) {
    int keyState = digitalRead(pins[i]);
    if (keyState == HIGH) {
      keyStatus[i] = 0;
    } else {
      keyStatus[i] = 1;
    }
  }
}

void checkKeys2() {
  for (int i=0; i<=6; i++) {
    int keyState = digitalRead(pins[i]);
    if (keyState == HIGH) {
      keyStatus2[i] = 0;
    } else {
      keyStatus2[i] = 1;
    }
  }
}

void waitForRelease() {
  checkKeys();
  delay(10);
  checkKeys2();
  boolean released = oneToZero();
  while (!released) {
    checkKeys();
    delay(10);
    checkKeys2();
    released = oneToZero();
  }
  if (waiting) recordChord();
  waiting = false;
  delay(10);
}

void recordChord() {
  int ch = convert_bin2dec();
  int toType = chords[ch];
  if (toType < 256) {
    Keyboard.write(toType);
    Keyboard.releaseAll();
  } else {
    
    if (toType == 500) {
      Keyboard.press(shiftKey);
      //delay(100);
      //Keyboard.releaseAll();
    }
   
   if (toType == 501) {
      Keyboard.press(ctrlKey);
    }  
   
   if (toType == 502) {
      Keyboard.press(altKey);
    }  
   
   if (toType == 503) {
      Keyboard.press(guiKey);
    } 
    
   if (toType == 504) {
      Keyboard.press(winKey);
    } 
  }
}

boolean keyPressed() {
  boolean kp = false;
  for (int i=0; i<=6; i++) {
    if (keyStatus[i] == 1) kp = true;
  }
  return kp;
}

boolean oneToZero() {
  boolean released = false;
  for (int i=0; i<=6; i++) {
    if (keyStatus[i] == 1 && keyStatus2[i] == 0) {
      released = true;
    }
  }
  return released;
}

int convert_bin2dec() {
    int val = 0;
    for ( int i = 0; i<=6 ; ++i ) {
        val = (val << 1) | keyStatus[i];
    }
    return val;
}
