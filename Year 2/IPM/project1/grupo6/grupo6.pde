// Bakeoff #2 - Seleção de Alvos e Fatores Humanos
// IPM 2019-20, Semestre 2
// Bake-off: durante a aula de lab da semana de 20 de Abril
// Submissão via Twitter: exclusivamente no dia 24 de Abril, até às 23h59

// Processing reference: https://processing.org/reference/

import java.util.Collections;

// Target properties
float PPI, PPCM;
float SCALE_FACTOR;
float TARGET_SIZE;
float TARGET_PADDING, MARGIN, LEFT_PADDING, TOP_PADDING;
float raioo;  //mouse radius
float ConDi;  //distance to contain closest target
float IntDj;  //distance to intersect 2nd closest target

// Study properties
ArrayList<Integer> trials  = new ArrayList<Integer>();    // contains the order of targets that activate in the test
int trialNum               = 0;                           // the current trial number (indexes into trials array above)
final int NUM_REPEATS      = 3;                           // sets the number of times each target repeats in the test - FOR THE BAKEOFF NEEDS TO BE 3!
boolean ended              = false;
ArrayList<Float> fits      = new ArrayList<Float>();
int newTrial               = 0;

// Performance variables
int startTime              = 0;      // time starts when the first click is captured
int finishTime             = 0;      // records the time of the final click
int hits                   = 0;      // number of successful clicks
int misses                 = 0;      // number of missed clicks
PFont f;

// Class used to store properties of a target
class Target
{
  int x, y;
  float w;
  
  Target(int posx, int posy, float twidth) 
  {
    x = posx;
    y = posy;
    w = twidth;
  }
}
Target closestTarget;
// Setup window and vars - runs once
void setup()
{
  //size(900, 900);    // window size in px (use for debugging)
  fullScreen();   // USE THIS DURING THE BAKEOFF!
  
  // The text from the file is loaded into an array. 
  SCALE_FACTOR    = 1.0 / displayDensity();            // scale factor for high-density displays
  String[] ppi_string = loadStrings("ppi.txt");
  PPI = float(ppi_string[1]);      // set PPI, we assume the ppi value is in the second line of the .txt
  PPCM           = PPI / 2.54 * SCALE_FACTOR;     // do not change this!
  TARGET_SIZE    = 1.5 * PPCM;     // set the target size in cm; do not change this!
  TARGET_PADDING = 1.5 * PPCM;     // set the padding around the targets in cm; do not change this!
  MARGIN         = 1.5 * PPCM;     // set the margin around the targets in cm; do not change this!
  LEFT_PADDING   = width/2 - TARGET_SIZE - 1.5*TARGET_PADDING - 1.5*MARGIN;        // set the margin of the grid of targets to the left of the canvas; do not change this!
  TOP_PADDING    = height/2 - TARGET_SIZE - 1.5*TARGET_PADDING - 1.5*MARGIN;       // set the margin of the grid of targets to the top of the canvas; do not change this!
  
  noStroke();        // draw shapes without outlines
  frameRate(144);     // set frame rat
  
  // Text and font setup
  f = createFont("Arial", 16);
  textFont(createFont("Arial", 16));    // sets the font to Arial size 16
  textAlign(CENTER);                    // align text
  
  randomizeTrials();    // randomize the trial order for each participant
  cursor(CROSS);
  drawCursor();
}

// Updates UI - this method is constantly being called and drawing targets
void draw()
{
  if(hasEnded()) return; // nothing else to do; study is over
    
  background(0);       // set background to black

  // Print trial count
  fill(255);          // set text fill color to white
  text("Trial " + (trialNum + 1) + " of " + trials.size(), 50, 20);    // display what trial the participant is on (the top-left corner)
  
  // Draw targets
  for (int i = 0; i < 16; i++) {
    drawTarget(i);
    drawText(i);
  }
  noCursor();
  drawCursor();

}

boolean hasEnded() {
  if(ended) return true;    // returns if test has ended before
   
  // Check if the study is over
  if (trialNum >= trials.size())
  {
    float timeTaken = (finishTime-startTime) / 1000f;     // convert to seconds - DO NOT CHANGE!
    float penalty = constrain(((95f-((float)hits*100f/(float)(hits+misses)))*.2f),0,100);    // calculate penalty - DO NOT CHANGE!
    
    printResults(timeTaken, penalty);    // prints study results on-screen
    ended = true;
  }
  
  return ended;
}

// Randomize the order in the targets to be selected
// DO NOT CHANGE THIS METHOD!
void randomizeTrials()
{
  for (int i = 0; i < 16; i++)             // 4 rows times 4 columns = 16 target
    for (int k = 0; k < NUM_REPEATS; k++)  // each target will repeat 'NUM_REPEATS' times
      trials.add(i);
  Collections.shuffle(trials);             // randomize the trial order
  
  System.out.println("trial order: " + trials);    // prints trial order - for debug purposes
}




// Print results at the end of the study
void printResults(float timeTaken, float penalty)
{
  background(0);       // clears screen
  
  fill(255);    //set text fill color to white
  text(day() + "/" + month() + "/" + year() + "  " + hour() + ":" + minute() + ":" + second() , 100, 20);   // display time on screen
  textFont(createFont("Arial", 20));
  text("Finished!", width / 2, 20); 
  text("Hits: " + hits, width / 2, 40);
  text("Misses: " + misses, width / 2, 60);
  text("Accuracy: " + (float)hits*100f/(float)(hits+misses) +"%", width / 2, 80);
  text("Total time taken: " + timeTaken + " sec", width / 2, 100);
  text("Average time for each target: " + nf((timeTaken)/(float)(hits+misses),0,3) + " sec", width / 2, 120);
  text("Average time for each target + penalty: " + nf(((timeTaken)/(float)(hits+misses) + penalty),0,3) + " sec", width / 2, 140);
  text("Target 1: ---", width/4, 200);
  int i;
  for(i = 2; i <= 24; i++) {
    if(fits.get(i-2) == 1000.0) {
      text("Target " + i + ": " + "MISSED", width/4, 200 + 20*(i-1));
    } 
    else
    text("Target " + i + ": " + fits.get(i-2), width/4, 200 + 20*(i-1));
  }
  
  for(i = 25; i <= 48; i++) {
    if(fits.get(i-2) == 1000.0) {
      text("Target " + i + ": " + "MISSED", 3*width/4, 200 + 20*(i-24));
    } 
    else
    text("Target " + i + ": " + fits.get(i-2), 3*width/4, 200 + 20*(i-24));
  }
  
  
  
  saveFrame("results-######.png");    // saves screenshot in current folder
}

// Mouse button was released - lets test to see if hit was in the correct target
void mousePressed() 
{
  if (trialNum >= trials.size()) return;      // if study is over, just return
  if (trialNum == 0) startTime = millis();    // check if first click, if so, start timer
  if (trialNum == trials.size() - 1)          // check if final click
  {
    finishTime = millis();    // save final timestamp
    println("We're done!");
  }
  
  Target target = getTargetBounds(trials.get(trialNum));    // get the location and size for the target in the current trial

  // Check to see if mouse cursor is inside the target bounds
  int distance = 0;
  if(ConDi > IntDj) {
    distance = 5;
  }
  if(dist(target.x, target.y, mouseX, mouseY) < raioo + target.w/2 + distance)
  {
    System.out.println("HIT! " + trialNum + " " + (millis() - startTime));     // success - hit!
    hits++; // increases hits counter
    if(trialNum < 47) {
      target = getTargetBounds(trials.get(trialNum+1));
      fits.add(log2(((dist(mouseX, mouseY, target.x, target.y)) / target.w) + 1));
    }
  }
  else
  {
    System.out.println("MISSED! " + trialNum + " " + (millis() - startTime));  // fail
    misses++;   // increases misses counter
    if(trialNum < 47) {
      fits.add(1000.0);
    }
  }

  trialNum++;   // move on to the next trial; UI will be updated on the next draw() cycle


}  

// For a given target ID, returns its location and size
Target getTargetBounds(int i)
{
  int x = (int)LEFT_PADDING + (int)((i % 4) * (TARGET_SIZE + TARGET_PADDING) + MARGIN);
  int y = (int)TOP_PADDING + (int)((i / 4) * (TARGET_SIZE + TARGET_PADDING) + MARGIN);
  
  return new Target(x, y, TARGET_SIZE);
}

void drawText(int i) {
      Target target = getTargetBounds(i);
      
      if(trialNum < 47) {
        if (trials.get(trialNum) == i) { 
          if (trials.get(trialNum+1) == i){
              textFont(f, 16);
              fill(255);
              textAlign(CENTER);
              text("AQUI 2x", target.x, target.y + 50);
          }
          else {
              textFont(f, 16);
              fill(255);
              textAlign(CENTER);
              text("AQUI", target.x, target.y + 50);
          }   
        }
        else if (trials.get(trialNum+1) == i) {
              textFont(f, 16);
              fill(255);
              textAlign(CENTER);
              text("PRÓXIMO", target.x, target.y + 50);
        }
      }
      
      else { 
        if (trials.get(trialNum) == i){
          textFont(f, 16);
          fill(0);
          textAlign(CENTER);
          text("AQUI", target.x, target.y + 50);
        }  
      }

  }   

// Draw target on-screen
// This method is called in every draw cycle; you can update the target's UI here
void drawTarget(int i) {
  Target target = getTargetBounds(i);   // get the location and size for the circle with ID:i
  Target correctTarget = getTargetBounds(trials.get(trialNum));
  noStroke();
  fill(120, 120, 120);

  if(target.x == closestTarget.x && target.y == closestTarget.y)
  {
    strokeWeight(3);
    stroke(255);
  }
  
  if(trialNum < 47) {
    if (trials.get(trialNum+1) == i) { 
      if(trials.get(trialNum) == i) {
        strokeWeight(4);
        stroke(255,0,0);
      }
      else {
         fill(255, 0, 0);
      }   
    }
  }
  if (trials.get(trialNum) == i) { 
        fill(0, 255, 0);
  }
  
  circle(target.x, target.y, target.w);   // draw target
  if(trialNum < 47) {
      Target nextTarget = getTargetBounds(trials.get(trialNum+1));
      drawArrow(correctTarget.x, correctTarget.y, nextTarget.x, nextTarget.y);
      if(trialNum > newTrial){
        fill(255,255,255);
        ellipse(nextTarget.x, nextTarget.y, correctTarget.w *3, correctTarget.w *3);
        newTrial++;
  }  
}
         
  
  noStroke();    // next targets won't have stroke (unless it is the intended target)
}

void drawCursor() {
  noStroke();
  closestTarget = getTargetBounds(0);
  Target secondClosest = getTargetBounds(1);
  Target correctTarget = getTargetBounds(trials.get(trialNum));
  float a = dist(mouseX, mouseY, closestTarget.x, closestTarget.y);
  float s = dist(mouseX, mouseY, secondClosest.x, secondClosest.y);
  for(int i = 1; i < 16; i++) {
    Target tempTarget = getTargetBounds(i);
    float d = dist(mouseX, mouseY, tempTarget.x, tempTarget.y);
    if(a > d) {
      s = a;
      a = d;
      secondClosest.x = closestTarget.x;
      secondClosest.y = closestTarget.y;
      closestTarget.x = tempTarget.x;
      closestTarget.y = tempTarget.y;
    }
    else if (s > d) {
      s = d;
      secondClosest.x = tempTarget.x;
      secondClosest.y = tempTarget.y;
    }
  }
  

  ConDi = dist(mouseX, mouseY, closestTarget.x, closestTarget.y) + closestTarget.w/2;
  IntDj = dist(mouseX, mouseY, secondClosest.x, secondClosest.y) - secondClosest.w/2 - 5;
  
  
  fill(0,0,255, 120);

  
  if(ConDi < IntDj) {
    raioo = ConDi;
  }
  else {
    raioo = IntDj;
  }

  circle(mouseX, mouseY, raioo*2);
  if(correctTarget.x == closestTarget.x && correctTarget.y == closestTarget.y) {
    fill(255,255,255);
    circle(mouseX, mouseY, raioo*2);
     fill(0, 255,0);
    circle(closestTarget.x, closestTarget.y, closestTarget.w);
  }
  circle(closestTarget.x, closestTarget.y, closestTarget.w + 10);
  
  strokeWeight(2);
  stroke(255);
  line(mouseX-10, mouseY, mouseX+10, mouseY);
  line(mouseX, mouseY-10, mouseX, mouseY+10);
}

void drawArrow(float x1, float y1, float x2, float y2) {
  strokeWeight(1);
  stroke(0, 255, 0);
  fill(0, 255, 0);
  float a = 7;
  pushMatrix();
  translate(x2, y2);
  rotate(atan2(y2 - y1, x2 - x1));
  triangle(- a * 2 , - a, 0, 0, - a * 2, a);
  popMatrix();
  line(x1, y1, x2, y2);  
} //<>//


float log2 (float x) {
  return (log(x) / log(2));
}
