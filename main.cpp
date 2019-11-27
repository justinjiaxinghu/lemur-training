#include "mbed.h" 
#include "uLCD_4DGL.h"
#include "cstdlib"
#include "PinDetect.h"
#include "Speaker.h"

Timer t;
uLCD_4DGL uLCD(p9, p10, p11); // create a global lcd object
PinDetect pb1(p21);
PinDetect pb2(p22); 
PinDetect pb3(p23);
Speaker mySpeaker(p24);

int totalCorrect = 0;
int trialNumber = 0;
int leftCount = 0;
int rightCount = 0;

void playMusic(Speaker&);
void createGame();
void rightButton();
void leftButton();

void playMusic(Speaker & mySpeaker)
{
    mySpeaker.PlayNote(200.0,0.3,0.1);
    mySpeaker.PlayNote(300.0,0.3,0.1);
    mySpeaker.PlayNote(400.0,0.3,0.1);
    mySpeaker.PlayNote(350.0,0.3,0.1);
    mySpeaker.PlayNote(150.0,0.3,0.1);
    mySpeaker.PlayNote(250.0,0.3,0.1);
    mySpeaker.PlayNote(280.0,0.3,0.1);
    
}

void rightButton() {
    t.stop();
    int timeElapsed = t.read_ms();
    uLCD.cls(); 
    if (rightCount <= leftCount) {
        totalCorrect++;
        uLCD.printf("\nCorrect!\n");
        uLCD.printf("Trial Number: \n");
        uLCD.printf("%d\n", trialNumber);
        uLCD.printf("Percent correct: \n");
        uLCD.printf("%f\n", totalCorrect*1.0/trialNumber * 100);
        uLCD.printf("Time taken: \n");
        uLCD.printf("%d\n", timeElapsed);
    } else {
        uLCD.printf("\nIncorrect!\n");
        uLCD.printf("Trial Number: \n");
        uLCD.printf("%d\n", trialNumber);
        uLCD.printf("Percent correct: \n");
        uLCD.printf("%f\n", totalCorrect*1.0/trialNumber * 100);
        uLCD.printf("Time taken: \n");
        uLCD.printf("%d\n", timeElapsed);
    }
    t.reset();
    wait(3);
    createGame();
}

void leftButton() {
    t.stop();
    int timeElapsed = t.read_ms();
    uLCD.cls();
    if (leftCount <= rightCount) {
        totalCorrect++;
        uLCD.printf("\nCorrect!\n");
        uLCD.printf("Trial Number: \n");
        uLCD.printf("%d\n", trialNumber);
        uLCD.printf("Percent correct: \n");
        uLCD.printf("%f\n", totalCorrect*1.0/trialNumber * 100);
        uLCD.printf("Time taken: \n");
        uLCD.printf("%d\n", timeElapsed);
    } else {
        uLCD.printf("\nIncorrect!\n");
        uLCD.printf("Trial Number: \n");
        uLCD.printf("%d\n", trialNumber);
        uLCD.printf("Percent correct: \n");
        uLCD.printf("%f\n", totalCorrect*1.0/trialNumber * 100);
        uLCD.printf("Time taken: \n");
        uLCD.printf("%d\n", timeElapsed);
    }
    t.reset();
    wait(3);
    createGame();
}

void createGame()
{
    uLCD.cls();
    uLCD.rectangle(0, 0, 60, 120, WHITE);
    uLCD.rectangle(67, 0, 127, 120, WHITE);
    
    int tri = 1;
    int sq = 2; 
    int circ = 3;
    
    int leftArray[6][3] = {   {0,0,0},
                        {0,0,0},
                        {0,0,0},
                        {0,0,0},
                        {0,0,0},
                        {0,0,0}};
    int rightArray[6][3] = {   {0,0,0},
                        {0,0,0},
                        {0,0,0},
                        {0,0,0},
                        {0,0,0},
                        {0,0,0}};
                        
    int randNumShapes = rand() % 15 + 1;
    int randNumShapes2 = rand() % 15 + 1;
    leftCount = randNumShapes;
    rightCount = randNumShapes2;
    int xCenterLeft[] = {10, 30, 50};
    int xCenterRight[] = {77, 97, 117};
    int yCenter[] = {10, 30, 50, 70, 90, 110};
    
    for (int i = 1; i < randNumShapes; i++) {
         
         int xCenterLeftIndex = rand() % 3;
         int yCenterIndex = rand() % 6;
         int randomXLeft = xCenterLeft[xCenterLeftIndex];
         int randomY = yCenter[yCenterIndex];
         int randomRadius = rand() % 8 + 1;
         
         while (leftArray[yCenterIndex][xCenterLeftIndex] != 0) {
             xCenterLeftIndex = rand() % 3;
             yCenterIndex = rand() % 6;
             randomXLeft = xCenterLeft[xCenterLeftIndex];
             randomY = yCenter[yCenterIndex];
         }
         
         leftArray[yCenterIndex][xCenterLeftIndex] = 1;
         int randShape = rand() % 3 + 1;
         if (randShape == 1) {
             uLCD.triangle(randomXLeft-randomRadius, randomY+randomRadius/2, randomXLeft+randomRadius, randomY+randomRadius/2, randomXLeft, randomY-randomRadius/2, RED);
         } else if (randShape == 2) {
             uLCD.rectangle(randomXLeft-randomRadius, randomY+randomRadius/2, randomXLeft+randomRadius, randomY-randomRadius/2, RED);
             uLCD.filled_rectangle(randomXLeft-randomRadius, randomY+randomRadius/2, randomXLeft+randomRadius, randomY-randomRadius/2, RED);
         } else {
             uLCD.circle(randomXLeft, randomY, randomRadius, RED);
             uLCD.filled_circle(randomXLeft, randomY, randomRadius, RED); 
         }
    }
    
    for (int i = 1; i < randNumShapes2; i++) {
        int xCenterRightIndex = rand() % 3;
        int yCenterIndex = rand() % 6;
        int randomXRight = xCenterRight[xCenterRightIndex];
        int randomY = yCenter[yCenterIndex];
        int randomRadius = rand() % 8 + 1;
        while (rightArray[yCenterIndex][xCenterRightIndex] != 0) {
             xCenterRightIndex = rand() % 3;
             yCenterIndex = rand() % 6;
             randomXRight = xCenterRight[xCenterRightIndex];
             randomY = yCenter[yCenterIndex];
         }
         
         rightArray[yCenterIndex][xCenterRightIndex] = 1;
         int randShape = rand() % 3 + 1;
         if (randShape == 1) {
             uLCD.triangle(randomXRight-randomRadius, randomY+randomRadius/2, randomXRight+randomRadius, randomY+randomRadius/2, randomXRight, randomY-randomRadius/2, RED);
         } else if (randShape == 2) {
             uLCD.rectangle(randomXRight-randomRadius, randomY+randomRadius/2, randomXRight+randomRadius, randomY-randomRadius/2, RED);
             uLCD.filled_rectangle(randomXRight-randomRadius, randomY+randomRadius/2, randomXRight+randomRadius, randomY-randomRadius/2, RED);
         } else {
             uLCD.circle(randomXRight, randomY, randomRadius, RED);
             uLCD.filled_circle(randomXRight, randomY, randomRadius, RED); 
         }
    }
    trialNumber++;
    t.start();
}

int main() 
{
    uLCD.printf("\nHow To Train Your Lemur\n"); 
    playMusic(mySpeaker);
//    mySpeaker.PlayNote(200.0,0.3,0.1);
//    mySpeaker.PlayNote(300.0,0.3,0.1);
//    mySpeaker.PlayNote(400.0,0.3,0.1);
//    mySpeaker.PlayNote(350.0,0.3,0.1);
//    mySpeaker.PlayNote(150.0,0.3,0.1);
//    mySpeaker.PlayNote(250.0,0.3,0.1);
//    mySpeaker.PlayNote(280.0,0.3,0.1);
    uLCD.cls();
    uLCD.background_color(BLACK);
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    srand(time(0)); //seed randomly
    createGame();
    bool exited = false;
    while (!exited) {
        if(!pb2) {
            rightButton();
        }
        if(!pb3) {
            leftButton();
        }
        if(!pb1) {
            exited = true;
        }
    }
    uLCD.cls();
    uLCD.printf("\nTake a break, lemur!\n"); 
}

