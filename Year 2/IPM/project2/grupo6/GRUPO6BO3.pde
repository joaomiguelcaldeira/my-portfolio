// Bakeoff #3 - Escrita de Texto em Smartwatches
// IPM 2019-20, Semestre 2
// Entrega: exclusivamente no dia 22 de Maio, até às 23h59, via Discord

// Processing reference: https://processing.org/reference/
import java.io.*;
import java.util.*;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;
import processing.sound.*;


//current keyboard
int keyboard = 1;
PImage arrow;
int ARROW_SIZE;
PImage backspace;
int BACK_SIZE;
PImage tick;
int TICK_SIZE;
PImage keyBrd;
int KEY_SIZE;
PImage leftArrow;
int LEFT_SIZE;
PImage rightArrow;
int RIGHT_SIZE;
float pressedW = 0;
float pressedH = 0;
SoundFile file;
String[] words;
int firstTap = 0;
String suggestion;
float position;
boolean pressedKey = false;
boolean mouseDragged = false;
boolean changedScreenOnce = false;
String left;
String right;
ArrayList<String> pLetters;
String prevWord;

// Screen resolution vars;
float PPI, PPCM;
float SCALE_FACTOR;

// Finger parameters
PImage fingerOcclusion;
int FINGER_SIZE;
int FINGER_OFFSET;

// Arm/watch parameters
PImage arm;
int ARM_LENGTH;
int ARM_HEIGHT;


// Study properties
String[] phrases;                   // contains all the phrases that can be tested
int NUM_REPEATS            = 2;     // the total number of phrases to be tested
int currTrialNum           = 0;     // the current trial number (indexes into phrases array above)
String currentPhrase       = "";    // the current target phrase
String currentTyped        = "";    // what the user has typed so far
String currentWord         = "";    // current word being typed
String[] typed = new String[NUM_REPEATS];

// Performance variables
float startTime            = 0;     // time starts when the user clicks for the first time
float finishTime           = 0;     // records the time of when the final trial ends
float lastTime             = 0;     // the timestamp of when the last trial was completed
float lettersEnteredTotal  = 0;     // a running total of the number of letters the user has entered (need this for final WPM computation)
float lettersExpectedTotal = 0;     // a running total of the number of letters expected (correct phrases)
float errorsTotal          = 0;     // a running total of the number of errors (when hitting next)



//Setup window and vars - runs once
void setup()
{
  //size(900, 900);
  fullScreen();
  textFont(createFont("Arial", 24));  // set the font to arial 24
  noCursor();                         // hides the cursor to emulate a watch environment
  
  // Load images
  arm = loadImage("arm_watch.png");
  fingerOcclusion = loadImage("finger.png");
  arrow = loadImage("back_arrow.png");
  backspace = loadImage("backspace.png");
  tick = loadImage("tick.png");
  keyBrd = loadImage("keyboard.png");
  rightArrow = loadImage("rightArrow.png");
  leftArrow = loadImage("leftArrow.png");
  
  // Load phrases
  phrases = loadStrings("phrases.txt");                       // load the phrase set into memory
  Collections.shuffle(Arrays.asList(phrases), new Random());  // randomize the order of the phrases with no seed
  
  // Scale targets and imagens to match screen resolution
  SCALE_FACTOR = 1.0 / displayDensity();          // scale factor for high-density displays
  String[] ppi_string = loadStrings("ppi.txt");   // the text from the file is loaded into an array.
  PPI = float(ppi_string[1]);                     // set PPI, we assume the ppi value is in the second line of the .txt
  PPCM = PPI / 2.54 * SCALE_FACTOR;               // do not change this!
  
  FINGER_SIZE = (int)(11 * PPCM);
  FINGER_OFFSET = (int)(0.8 * PPCM);
  ARM_LENGTH = (int)(19 * PPCM);
  ARM_HEIGHT = (int)(11.2 * PPCM);
  ARROW_SIZE = (int)(0.9 * PPCM);
  BACK_SIZE  = (int)(0.9 * PPCM);
  TICK_SIZE  = (int)(0.8 * PPCM);
  KEY_SIZE   = (int)(1.2 * PPCM);
  RIGHT_SIZE   = (int)(0.4 * PPCM);
  LEFT_SIZE   = (int)(0.4 * PPCM);
  file = new SoundFile(this, "click.mp3");
  words = loadStrings("words.txt");
  suggestion = words[0];
  currentPhrase       = "";    // the current target phrase
  currentTyped        = "";    // what the user has typed so far
  currentWord         = "";    // current word being typed
  prevWord            = "";
  pLetters = possibleLetters(currentWord);
}

void draw()
{ 
  // Check if we have reached the end of the study
  if (finishTime != 0)  return;
 
  background(255);                                                         // clear background
  
  // Draw arm and watch background
  imageMode(CENTER);
  image(arm, width/2, height/2, ARM_LENGTH, ARM_HEIGHT);
  
  // Check if we just started the application
  if (startTime == 0 && !mousePressed)
  {
    fill(0);
    textAlign(CENTER);
    text("Tap to start time!", width/2, height/2);
  }
  else if (startTime == 0 && mousePressed) nextTrial();                    // show next sentence
 
  // Check if we are in the middle of a trial
  else if (startTime != 0)
  {
    textAlign(LEFT);
    fill(100);
    text("Phrase " + (currTrialNum + 1) + " of " + NUM_REPEATS, width/2 - 4.0*PPCM, height/2 - 8.1*PPCM);   // write the trial count
    text("Target:    " + currentPhrase, width/2 - 4.0*PPCM, height/2 -7.1*PPCM);                           // draw the target string
    fill(0);
    text("Entered:  " + currentTyped + "|", width/2 - 4.0*PPCM, height/2 - 6.1*PPCM);                      // draw what the user has entered thus far 
    
    // Draw very basic ACCEPT button - do not change this!
    textAlign(CENTER);
    noStroke();
    fill(0, 250, 0);
    rect(width/2 - 2*PPCM, height/2 - 5.1*PPCM, 4.0*PPCM, 2.0*PPCM);
    fill(0);
    text("ACCEPT >", width/2, height/2 - 4.1*PPCM);
    
    // Draw screen areas
    // simulates text box - not interactive
    noStroke();

    fill(255);
    rect(width/2 - 2.0*PPCM, height/2 - 2.0*PPCM, 4.0*PPCM, 1.0*PPCM);

    textAlign(CENTER);
    fill(0);

    
    if (keyboard == 1) {
      right = "B - L";
      left  = "M - Z";
    }
    if (keyboard == 2) {
      right = "M - Z";
      left  = "HOME";
    }
    if (keyboard == 3) {
      right = "HOME";
      left  = "B - L";
    }
    textAlign(CENTER);
    textFont(createFont("Arial", 12 * PPCM * 0.03));
    text(left, width/2 - 1.25*PPCM, height/2 - 1.08*PPCM);
    text(right, width/2 + 1.25*PPCM, height/2 - 1.08*PPCM);
    image(leftArrow, width/2 - 1.85 * PPCM, height/2 - 1.2 * PPCM, LEFT_SIZE, LEFT_SIZE);
    image(rightArrow, width/2 + 1.85 * PPCM, height/2 - 1.2 * PPCM, RIGHT_SIZE, RIGHT_SIZE);
    textFont(createFont("Arial", 16 * PPCM * 0.03));
    text(suggestion,  width/2, height/2 - 1.5 * PPCM);
    //text(currentTyped, width/2 - 1.95 * PPCM, height/2 - 1.65 * PPCM);   //writes typed text in textbox
    
    // THIS IS THE ONLY INTERACTIVE AREA (4cm x 4cm); do not change size
    

    fill(255);
    rect(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 4.0*PPCM, 3.0*PPCM);
    if(!mouseDragged && mousePressed && didMouseClick(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 4.0*PPCM, 3.0*PPCM)) {
      fill(120);
      rect(pressedW, pressedH, PPCM, PPCM);
      imageMode(CORNER);
      image(fingerOcclusion, mouseX - FINGER_OFFSET, mouseY - FINGER_OFFSET, FINGER_SIZE, FINGER_SIZE);
      pressedKey = false;
    }
    stroke(0, 0, 0);
    imageMode(CENTER);
    //draw table where characters will be
    //horizontal lines
    strokeWeight(2);
    line(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, width/2 + 2.0*PPCM, height/2 - 1.0*PPCM);
    line(width/2 - 2.0*PPCM, height/2 + 1.0*PPCM, width/2 + 2.0*PPCM, height/2+1.0*PPCM);
    line(width/2 - 2.0*PPCM, height/2, width/2 + 2.0*PPCM, height/2);
    line(width/2 - 2.0*PPCM, height/2 + 2.0*PPCM, width/2 + 2.0*PPCM, height/2 + 2.0*PPCM);
    //vertical lines
    line(width/2 - 2*PPCM, height/2 - 1*PPCM, width/2 - 2*PPCM, height/2 + 2.0*PPCM);
    line(width/2 - 1*PPCM, height/2 - 1*PPCM, width/2 - 1*PPCM, height/2 + 2.0*PPCM);
    line(width/2, height/2 - 1*PPCM, width/2, height/2 + 2.0*PPCM);
    line(width/2 + 1*PPCM, height/2 - 1*PPCM, width/2 + 1*PPCM, height/2 + 2.0*PPCM);
    line(width/2 + 2*PPCM, height/2 - 1*PPCM, width/2 + 2*PPCM, height/2 + 2.0*PPCM);
    stroke(51, 153, 255);
    strokeWeight(2);
    line(width/2 - 2.0*PPCM, height/2 - 2.0*PPCM, width/2 + 2.0*PPCM, height/2 - 2.0*PPCM);
    textAlign(CENTER);
    if(keyboard == 1) {
      //draw keyboard letters
      fill(0);
      textFont(createFont("Arial", 68 * PPCM * 0.01));
      image(tick, width/2 - 0.5*PPCM, height/2 - 0.45 * PPCM, TICK_SIZE, TICK_SIZE);
      /*image(keyBrd , width/2 - 1.5*PPCM, height/2 - 0.5 * PPCM, KEY_SIZE, KEY_SIZE);*/
      text("_", width/2 + 0.5*PPCM, height/2 - 0.35 * PPCM);
      image(backspace, width/2 + 1.5*PPCM, height/2 - 0.45 * PPCM, BACK_SIZE, BACK_SIZE);
      drawLetter("E", width/2 - 1.5*PPCM, height/2 + 0.75 * PPCM);
      drawLetter("T", width/2 - 0.5*PPCM, height/2 + 0.75 * PPCM);
      drawLetter("A", width/2 + 0.5*PPCM, height/2 + 0.75 * PPCM);
      drawLetter("O", width/2 + 1.5*PPCM, height/2 + 0.75 * PPCM);
      drawLetter("I", width/2 - 1.5*PPCM, height/2 + 1.75 * PPCM);
      drawLetter("N", width/2 - 0.5*PPCM, height/2 + 1.75 * PPCM);
      drawLetter("S", width/2 + 0.5*PPCM, height/2 + 1.75 * PPCM);
      drawLetter("R", width/2 + 1.5*PPCM, height/2 + 1.75 * PPCM);
      textFont(createFont("Arial", 24));  // set the font to arial 24
    }

    if(keyboard == 2 || keyboard == 3) {
      //draw keyboard letters
      /*imageMode(CENTER);
      image(arrow, width/2 + 1.5*PPCM, height/2 - 0.5*PPCM, ARROW_SIZE, ARROW_SIZE);*/
      fill(0);
      
      textFont(createFont("Arial", 68 * PPCM * 0.01));
      /*image(keyBrd , width/2 - 1.5*PPCM, height/2 - 0.5 * PPCM, KEY_SIZE, KEY_SIZE);*/
      text("_", width/2 + 0.5*PPCM, height/2 - 0.35 * PPCM);
      image(backspace, width/2 + 1.5*PPCM, height/2 - 0.45 * PPCM, BACK_SIZE, BACK_SIZE);
      image(tick, width/2 - 0.5*PPCM, height/2 - 0.45 * PPCM, TICK_SIZE, TICK_SIZE);
     

      if(keyboard == 2) {
        drawLetter("B", width/2 - 1.5*PPCM, height/2 - 0.25 * PPCM);
        drawLetter("C", width/2 - 1.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("D", width/2 - 0.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("F", width/2 + 0.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("G", width/2 + 1.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("H", width/2 - 1.5*PPCM, height/2 + 1.75 * PPCM);
        drawLetter("J", width/2 - 0.5*PPCM, height/2 + 1.75 * PPCM);
        drawLetter("K", width/2 + 0.5*PPCM, height/2 + 1.75 * PPCM);
        drawLetter("L", width/2 + 1.5*PPCM, height/2 + 1.75 * PPCM);
      }
      if(keyboard == 3) {
        drawLetter("M", width/2 - 1.5*PPCM, height/2 - 0.25 * PPCM);
        drawLetter("P", width/2 - 1.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("Q", width/2 - 0.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("U", width/2 + 0.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("V", width/2 + 1.5*PPCM, height/2 + 0.75 * PPCM);
        drawLetter("W", width/2 - 1.5*PPCM, height/2 + 1.75 * PPCM);
        drawLetter("X", width/2 - 0.5*PPCM, height/2 + 1.75 * PPCM);
        drawLetter("Y", width/2 + 0.5*PPCM, height/2 + 1.75 * PPCM);
        drawLetter("Z", width/2 + 1.5*PPCM, height/2 + 1.75 * PPCM);
      }  

      textFont(createFont("Arial", 24));  // set the font to arial 24
    }  
  }
  
  // Draw the user finger to illustrate the issues with occlusion (the fat finger problem)
  noStroke();
  imageMode(CORNER);
  image(fingerOcclusion, mouseX - FINGER_OFFSET, mouseY - FINGER_OFFSET, FINGER_SIZE, FINGER_SIZE);
}


void drawLetter(String letter, float width, float height) {
  fill(155);

  if(pLetters.contains(letter.toLowerCase()) || currentWord == "") {
      fill(0);
  }  

  text(letter, width, height);
}






// Check if mouse click was within certain bounds
boolean didMouseClick(float x, float y, float w, float h)
{
  return (mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h);
}



void mouseReleased()
{
  if (didMouseClick(width/2 - 2*PPCM, height/2 - 5.1*PPCM, 4.0*PPCM, 2.0*PPCM)) nextTrial();                         // Test click on 'accept' button - do not change this!
  else if(!mouseDragged && firstTap == 1 && didMouseClick(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 4.0*PPCM, 3.0*PPCM))  // Test click on 'keyboard' area - do not change this condition! 
  {
    pressedKey = true;

    // FIRST ROW OF KEYS
    if(didMouseClick(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      if(keyboard == 3) {
        typeLetter("m");
      }  
      if(keyboard == 2) {
        typeLetter("b");
      }

    }
    if(didMouseClick(width/2 - 1.0*PPCM, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {

      currentTyped  = currentTyped.substring(0, currentTyped.length() - currentWord.length());
      currentTyped += suggestion + " ";
      prevWord = suggestion;
      currentWord = "";
      
    }
    if(didMouseClick(width/2, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
        currentTyped += " ";
        prevWord = currentWord;
        currentWord  =  "";
        
    }    
    
    if(didMouseClick(width/2 + 1.0*PPCM, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      if(currentTyped.length() > 0) {
        currentTyped = currentTyped.substring(0, currentTyped.length() - 1);
        if(currentWord.length() > 0) {
           currentWord = currentWord.substring(0, currentWord.length() -1);
        }
        else currentWord = prevWord;
      }
    }
    
    // SECOND ROW OF KEYS
    if(didMouseClick(width/2 - 2.0*PPCM, height/2, 1*PPCM, 1*PPCM)) {
      if(keyboard == 3) {
        typeLetter("p");
      }  
      if(keyboard == 2) {
        typeLetter("c");
      } 
      if(keyboard == 1) {
        typeLetter("e");
      }
    }
    if(didMouseClick(width/2 - 1.0*PPCM, height/2, 1*PPCM, 1*PPCM)) {
      if(keyboard == 3) {
        typeLetter("q"); 
      }  
      if(keyboard == 2) {
        typeLetter("d");
      }      
      if(keyboard == 1) {
        typeLetter("t");
      }  
    }
    if(didMouseClick(width/2, height/2, 1*PPCM, 1*PPCM)) { 
      if(keyboard == 3) {
        typeLetter("u"); 
      }  
      if(keyboard == 2) {
        typeLetter("f");
      }
      if(keyboard == 1) {
        typeLetter("a");
      }
    }    
    if(didMouseClick(width/2 + 1.0*PPCM, height/2, 1*PPCM, 1*PPCM)) {     
      if(keyboard == 3) {
        typeLetter("v");
      }
      if(keyboard == 2) {
        typeLetter("g");
      }
      if(keyboard == 1) {
        typeLetter("o");
      }  

    }
    
    // THIRD ROW OF KEYS
    if(didMouseClick(width/2 - 2.0*PPCM, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {        
      if(keyboard == 1) {
        typeLetter("i");
      }
      if(keyboard == 3) {
        typeLetter("w");
      }
      if(keyboard == 2) {
        typeLetter("h");
      }
    }
    if(didMouseClick(width/2 - 1.0*PPCM, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {        

      if(keyboard == 1) {
        typeLetter("n");
      }
      if(keyboard == 3) {
        typeLetter("x");
      }  
      if(keyboard == 2) {
        typeLetter("j");
      }
    }
    if(didMouseClick(width/2, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {      

      if(keyboard == 1) {
        typeLetter("s");
      }
      if(keyboard == 3) {
        typeLetter("y");
      }
      if(keyboard == 2) {
        typeLetter("k");
      }  
    }    
    if(didMouseClick(width/2 + 1.0*PPCM, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {    
      if(keyboard == 1) {
        typeLetter("r");
      }  
      if(keyboard == 3) {
        typeLetter("z");
      }
      if(keyboard == 2) {
        typeLetter("l");
      }    
    }

    suggestion = predict(currentWord);
    pLetters = possibleLetters(currentWord);

    
  }
  else System.out.println("debug: CLICK NOT ACCEPTED");
  mouseDragged = false;
  firstTap = 1;
}

void mousePressed() {
  changedScreenOnce = false;
  if(!mouseDragged && firstTap == 1 && didMouseClick(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 4.0*PPCM, 3.0*PPCM))  // Test click on 'keyboard' area - do not change this condition! 
  {
    pressedKey = true;

    // FIRST ROW OF KEYS
    if(didMouseClick(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 - 2.0*PPCM;
      pressedH = height/2 - 1.0*PPCM;
    }
    if(didMouseClick(width/2 - 1.0*PPCM, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 - 1.0*PPCM;
      pressedH = height/2 - 1.0*PPCM;
    }
    if(didMouseClick(width/2, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2;
      pressedH = height/2 - 1.0*PPCM;
    }    
    if(didMouseClick(width/2 + 1.0*PPCM, height/2 - 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 + 1.0*PPCM;
      pressedH = height/2 - 1.0*PPCM;
      /**/

    }
    
    // SECOND ROW OF KEYS
    if(didMouseClick(width/2 - 2.0*PPCM, height/2, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 - 2.0*PPCM;
      pressedH = height/2;
    }
    if(didMouseClick(width/2 - 1.0*PPCM, height/2, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 - 1.0*PPCM;
      pressedH = height/2;
    }
    if(didMouseClick(width/2, height/2, 1*PPCM, 1*PPCM)) {
      pressedW = width/2;
      pressedH = height/2;   
    }    
    if(didMouseClick(width/2 + 1.0*PPCM, height/2, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 + 1.0*PPCM;
      pressedH = height/2;      
    }
    
    // THIRD ROW OF KEYS
    if(didMouseClick(width/2 - 2.0*PPCM, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 - 2.0*PPCM;
      pressedH = height/2 + 1.0*PPCM;         
    }
    if(didMouseClick(width/2 - 1.0*PPCM, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 - 1.0*PPCM;
      pressedH = height/2 + 1.0*PPCM;        
    }
    if(didMouseClick(width/2, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2;
      pressedH = height/2 + 1.0*PPCM;        
    }    
    if(didMouseClick(width/2 + 1.0*PPCM, height/2 + 1.0*PPCM, 1*PPCM, 1*PPCM)) {
      pressedW = width/2 + 1.0*PPCM;
      pressedH = height/2 + 1.0*PPCM;        
    }
    
  }
  position = mouseX;
}

void mouseDragged() {
     if(didMouseClick(width/2 - 2.0*PPCM, height/2 - 1.0*PPCM, 4.0*PPCM, 3.0*PPCM)) {
      
      if (mouseX < position - 1 * PPCM ) {
         if (!changedScreenOnce) {
            if(keyboard == 3) keyboard = 1;
            else keyboard++;
            mouseDragged = true;
            changedScreenOnce = true;
         }
      } 
      else if (mouseX > position + 1 * PPCM) {
         if (!changedScreenOnce) {
            if(keyboard == 1) keyboard = 3;
            else keyboard--;
            mouseDragged = true;
            changedScreenOnce = true;
         }
      }
     } 
}

void nextTrial()
{
  if (currTrialNum >= NUM_REPEATS) return;                                            // check to see if experiment is done
  
  // Check if we're in the middle of the tests
  else if (startTime != 0 && finishTime == 0)                                         
  {
    System.out.println("==================");
    System.out.println("Phrase " + (currTrialNum+1) + " of " + NUM_REPEATS);
    System.out.println("Target phrase: " + currentPhrase);
    System.out.println("Phrase length: " + currentPhrase.length());
    System.out.println("User typed: " + currentTyped);
    System.out.println("User typed length: " + currentTyped.length());
    System.out.println("Number of errors: " + computeLevenshteinDistance(currentTyped.trim(), currentPhrase.trim()));
    System.out.println("Time taken on this trial: " + (millis() - lastTime));
    System.out.println("Time taken since beginning: " + (millis() - startTime));
    System.out.println("==================");
    lettersExpectedTotal += currentPhrase.trim().length();
    lettersEnteredTotal += currentTyped.trim().length();
    errorsTotal += computeLevenshteinDistance(currentTyped.trim(), currentPhrase.trim());
    typed[currTrialNum] = currentTyped;
  }
  
  // Check to see if experiment just finished
  if (currTrialNum == NUM_REPEATS - 1)                                           
  {
    finishTime = millis();
    System.out.println("==================");
    System.out.println("Trials complete!"); //output
    System.out.println("Total time taken: " + (finishTime - startTime));
    System.out.println("Total letters entered: " + lettersEnteredTotal);
    System.out.println("Total letters expected: " + lettersExpectedTotal);
    System.out.println("Total errors entered: " + errorsTotal);

    float wpm = (lettersEnteredTotal / 5.0f) / ((finishTime - startTime) / 60000f);   // FYI - 60K is number of milliseconds in minute
    float cps = (lettersEnteredTotal) / ((finishTime - startTime) / 1000f);
    float freebieErrors = lettersExpectedTotal * .05;                                 // no penalty if errors are under 5% of chars
   float penalty = max(0, (errorsTotal - freebieErrors) / ((finishTime - startTime) / 60000f));
    
    System.out.println("Raw WPM: " + wpm);
    System.out.println("Freebie errors: " + freebieErrors);
    System.out.println("Penalty: " + penalty);
    System.out.println("WPM w/ penalty: " + (wpm - penalty));                         // yes, minus, because higher WPM is better
    System.out.println("Raw CPS: " + cps);
    System.out.println("==================");
    
    printResults(wpm, cps, freebieErrors, penalty);
    
    currTrialNum++;                                                                   // increment by one so this mesage only appears once when all trials are done
    return;
  }

  else if (startTime == 0)                                                            // first trial starting now
  {
    System.out.println("Trials beginning! Starting timer...");
    startTime = millis();                                                             // start the timer!
  } 
  else currTrialNum++;                                                                // increment trial number

  lastTime = millis();                                                                // record the time of when this trial ended
  currentTyped = "";                                                                  // clear what is currently typed preparing for next trial
  currentWord  = "";
  suggestion = predict(currentWord);
  currentPhrase = phrases[currTrialNum];                                              // load the next phrase!
}

// Print results at the end of the study
void printResults(float wpm, float cps, float freebieErrors, float penalty) {
  background(0);       // clears screen
  
  textFont(createFont("Arial", 16));    // sets the font to Arial size 16
  fill(255);    //set text fill color to white
  text(day() + "/" + month() + "/" + year() + "  " + hour() + ":" + minute() + ":" + second(), 100, 20);   // display time on screen
  
  text("Finished!", width / 2, height / 2); 
  
  int h = 20;
  for(int i = 0; i < NUM_REPEATS; i++, h += 40 ) {
    text("Target phrase " + (i+1) + ": " + phrases[i], width / 2, height / 2 + h);
    text("User typed " + (i+1) + ": " + typed[i], width / 2, height / 2 + h+20);
  }
  
  text("Raw WPM: " + wpm, width / 2, height / 2 + h + 20);
  text("Freebie errors: " + freebieErrors, width / 2, height / 2 + h + 40);
  text("Penalty: " + penalty, width / 2, height / 2 + h + 60);
  text("WPM with penalty: " + max(wpm - penalty, 0), width / 2, height / 2 + h + 80);
  text("Raw CPS: " + cps, width/2, height/2 + h + 100);

  saveFrame("results-######.png");    // saves screenshot in current folder    
}

// This computes the error between two strings (i.e., original phrase and user input)
int computeLevenshteinDistance(String phrase1, String phrase2)
{
  int[][] distance = new int[phrase1.length() + 1][phrase2.length() + 1];

  for (int i = 0; i <= phrase1.length(); i++) distance[i][0] = i;
  for (int j = 1; j <= phrase2.length(); j++) distance[0][j] = j;

  for (int i = 1; i <= phrase1.length(); i++)
    for (int j = 1; j <= phrase2.length(); j++)
      distance[i][j] = min(min(distance[i - 1][j] + 1, distance[i][j - 1] + 1), distance[i - 1][j - 1] + ((phrase1.charAt(i - 1) == phrase2.charAt(j - 1)) ? 0 : 1));

  return distance[phrase1.length()][phrase2.length()];
}

String predict(String theWord) {
    for(int i = 0; i < words.length; i++) {
       if (words[i].startsWith(theWord) && !split(words[i], '\t')[0].equals(theWord)) {
          String[] word = split(words[i], '\t');
          return word[0];
       }
    }
    return "";
}

ArrayList<String> possibleLetters(String theWord) {
  ArrayList<String> pLetters = new ArrayList<String>();
  String[] pWords = new String[words.length];
  int numberWords = 0;

  for(int i = 0; i < words.length; i++) {
     if (words[i].startsWith(theWord) && !split(words[i], '\t').equals(theWord)) {
        pWords[numberWords++] = words[i];
     }
  }
  int wordLength = theWord.length();
  for(int i = 0; i < numberWords; i++) {
    if(theWord != "" && !pLetters.contains(pWords[i].substring(wordLength, wordLength + 1))) {
       pLetters.add(pWords[i].substring(wordLength, wordLength + 1));
    }
  }
  return pLetters;
}

void typeLetter(String letter) {
  if(pLetters.size() == 0 || pLetters.contains(letter.toLowerCase())) {
    currentTyped += letter;
    currentWord  += letter;
    file.play();
  }
}
