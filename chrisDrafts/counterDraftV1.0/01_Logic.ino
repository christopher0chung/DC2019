// NOTES
//------------------------------------------------
// 0 - Forward
// 1 - Ping-pong
// 2 - Brownian
// 3 - Rand w/o replace

// 4 - Two
// 5 - Three
// 6 - Four
// 7 - Rand sel stacked dice thingy

// 8 - Squared
// 9 - Even
//10 - Cubed
//11 - Odd

// 12 - Squared
// 13 - Cubed
// 14 - Prime
// 15 - Seidel

// TEMP GLOBALS
//------------------------------------------------

int counterIndicies0 [22] = {138, 147, 159, 146, 135, 145, 127, 123, 137, 143, 131, 151, 139, 153, 125, 126, 122, 121, 155, 130, 129, 154};
int counterIndicies1 [22] = {134, 120, 133, 136, 140, 152, 156, 149, 150, 128, 132, 158, 142, 141, 157, 124, 144, 148,  88,  96, 101, 102};
int counterIndicies2 [22] = {110, 116, 108,  80,  92, 109,  93, 112, 100, 104,  84, 117, 118,  94, 305, 305, 305, 305, 305, 305, 305, 305};

// STRUCT
//------------------------------------------------
struct counter {
  int myCounterIndicies [22];
  int myCounterPotIndex;

  int myCounterModeTop;
  int myCounterModeBot;

  int myModuloTop;
  int myModuloBot;

  int myCounterValTop;
  int myCounterValBot;

  int selectModeLeftTop = 0;
  int selectModeRightTop = 0;
  int modeTop = 0;

  int selectModeLeftBot = 0;
  int selectModeRightBot = 0;
  int modeBot = 0;

  void indexInit(int newIndicies[]) {
    for (int i = 0; i < 22; i++)
      myCounterIndicies[i] = newIndicies[i];
  }

  void potInit(int potIndex){
    
  }

  // LOGIC
  //------------------------------------------------
  void counterButtonRead() {
    if (buttons.vals[290]) {
      for (int i = 6; i <= 9; i++) {
        if (buttons.risingEdge(myIndicies[i])) selectModeLeftTop = i - 6;
        modeTop = calcMode(selectModeLeftTop, selectModeRightTop);
        modeToModulo();
      }
      for (int i = 10; i <= 13; i++) {
        if (buttons.risingEdge(myIndicies[i])) selectModeRightTop = i - 10;
        modeTop = calcMode(selectModeLeftTop, selectModeRightTop);
        modeToModulo();
      }
      for (int i = 14; i <= 17; i++) {
        if (buttons.risingEdge(myIndicies[i])) selectModeLeftBot = i - 14;
        modeBot = calcMode(selectModeLeftBot, selectModeRightBot);
        modeToModulo();
      }
      for (int i = 18; i <= 21; i++) {
        if (buttons.risingEdge(myIndicies[i])) selectModeRightBot = i - 18;
        modeBot = calcMode(selectModeLeftBot, selectModeRightBot);
        modeToModulo();
      }
    }
  }

  void counterPotRead(){
    
  }

  void counterUpdate(){

  }

  // HELPER FUNCTIONS
  //------------------------------------------------
  int calcMode(int left, int right) {
    return left * 4 + right;
  }

  void modeToModulo() {
    if (modeTop == modeBot) {

      if (modeTop == 0) {
        myModuloTop = 16;
        myModuloBot = 16;
      }
      else if (modeTop == 1) {
        myModuloTop = 30;
        myModuloBot = 30;
      }
      else if (modeTop == 2) {
        myModuloTop = 16;
        myModuloBot = 16;
      }
      else if (modeTop == 3) {
        myModuloTop = 16;
        myModuloBot = 16;
      }
      else if (modeTop == 4) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 5) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 6) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 7) {
        myModuloTop = 8;
        myModuloBot = 8;
      }
      else if (modeTop == 8) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 9) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 10) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 11) {
        myModuloTop = 999;
        myModuloBot = 999;
      }
      else if (modeTop == 12) {
        myModuloTop = 256;
        myModuloBot = 256;
      }
      else if (modeTop == 13) {
        myModuloTop = 256;
        myModuloBot = 256;
      }
      else if (modeTop == 14) {
        myModuloTop = 256;
        myModuloBot = 256;
      }
      else if (modeTop == 15) {
        myModuloTop = 256;
        myModuloBot = 256;
      }
    }
    else if (modeTop != modeBot) {

      if (modeTop == 0) myModuloTop = 8;
      else if (modeTop == 1) myModuloTop = 14;
      else if (modeTop == 2) myModuloTop = 8;
      else if (modeTop == 3) myModuloTop = 8;
      else if (modeTop == 4) myModuloTop = 999;
      else if (modeTop == 5) myModuloTop = 999;
      else if (modeTop == 6) myModuloTop = 999;
      else if (modeTop == 7) myModuloTop = 8;
      else if (modeTop == 8) myModuloTop = 999;
      else if (modeTop == 9) myModuloTop = 999;
      else if (modeTop == 10) myModuloTop = 999;
      else if (modeTop == 11) myModuloTop = 999;
      else if (modeTop == 12) myModuloTop = 256;
      else if (modeTop == 13) myModuloTop = 256;
      else if (modeTop == 14) myModuloTop = 256;
      else if (modeTop == 15) myModuloTop = 256;

      if (modeBot == 0) myModuloBot = 8;
      else if (modeBot == 1) myModuloBot = 14;
      else if (modeBot == 2) myModuloBot = 8;
      else if (modeBot == 3) myModuloBot = 8;
      else if (modeBot == 4) myModuloBot = 999;
      else if (modeBot == 5) myModuloBot = 999;
      else if (modeBot == 6) myModuloBot = 999;
      else if (modeBot == 7) myModuloBot = 8;
      else if (modeBot == 8) myModuloBot = 999;
      else if (modeBot == 9) myModuloBot = 999;
      else if (modeBot == 10) myModuloBot = 999;
      else if (modeBot == 11) myModuloBot = 999;
      else if (modeBot == 12) myModuloBot = 256;
      else if (modeBot == 13) myModuloBot = 256;
      else if (modeBot == 14) myModuloBot = 256;
      else if (modeBot == 15) myModuloBot = 256;
    }
  }
};
