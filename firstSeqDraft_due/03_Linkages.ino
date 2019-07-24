//---------------------------------------------------------------
//   VARIABLES
//---------------------------------------------------------------
const int linkagesMax = 128;
const int buttonsMax = 304;
const int numInputs = 165;
const int numOutputs = 98;

int inputs[numInputs] = {
  /* Counter I*/            138,  147,  159,  146,  135,  145,
  /* Counter II */          134,  120,  133,  136,  140,  152,
  /* Counter III */         110,  116,  108,   80,   92,  109,
  /* Multiplexer Out I */   210,  203,  211,  218,  235,  225,  224,
  /* Multiplexer Out II */  215,  201,  226,  234,  237,  222,  200,
  /* Multiplexer In I */    233,  209,  239,  213,  236,  221,  216,  232,  208,  229,
  /* Multiplexer In II */   231,  227,  207,  228,  205,  220,  230,  204,  212,  206,
  /* Burst & Delay */       164,  174,  175,  190,  166,  167,  163,  165,
  /* Logic */               182,  185,  178,  160,  191,  169,  198,  193,  183,  180,  195,  199,
  /* Splitter */            276,  253,  271,  254,  273,  266,  262,  260,
  /* Metroplexer A */       264,  269,  278,  270,  250,  255,  241,  247,
  /* Metroplexer B */       261,  268,  252,  246,    0,   29,   37,   24,   38,   36,   30,   21,
  /* Command I Red */       113,  115,   43,   75,   66,   71,   61,   48,   62,
  /* Command I Yel */       106,   89,   79,   49,   58,   67,   64,   60,   46,
  /* Command I Key A */      85,   95,   86,   82,   91,   87,   90,   81,   83,  105,   55,   50,
  /* Command I Key B */      47,   57,   74,   65,   41,   51,   63,   59,   68,   72,   70,   77,  78,
  /* Command III Top */      26,   17,   19,   31,    9,    1,   10,   11,
  /* Command III Bot */      69,   56,   76,   40,   53,   45,   54,   52,   44,    3,    7,   15,   2,   23
};

int outputs[numOutputs] = {
  /* Counter I A */         127,  123,  137,  143,  131,  151,  139,  153,
  /* Counter I B */         125,  126,  122,  121,  155,  130,  129,  154,
  /* Counter II A */        156,  149,  150,  128,  132,  158,  142,  141,
  /* Counter II B */        157,  124,  144,  148,   88,   96,  101,  102,
  /* Counter III */          93,  112,  100,  104,   84,  117,  118,   94,
  /* Multiplexer Out I */   219,  214,  238,  194,
  /* Multiplexer Out II */  223,  202,  217,  161,
  /* Multiplexer In I */    171,
  /* Multiplexer In II */   179,
  /* Burst & Delay */       172,  181,  168,  173,  162,  176,  189,  188,  196,  184,  197,  192,
  /* Logic */               177,  187,  186,  170,
  /* Splitter A */          272,  240,  275,  263,  258,  277,  256,  248,  243,  267,
  /* Splitter B */          245,  244,  257,  279,  265,  259,
  /* Metroplexer P.I */     249,  251,  242,  274,    8,   13,   28,   12,
  /* Metroplexer P.II */      4,   14,   20,   22,   32,    6,   16,    5,
};

struct link {
  int driverIndex;
  int bufferIndex;
  bool filled() {
    if (driverIndex != 999 && bufferIndex != 999)
      return true;
    else return false;
  };
};

link linkages[linkagesMax];
link newLinkBuffer = {999, 999};
int activeLinkageCount = 0;

enum driverStates {noDrive, driveLow, driveHigh};
driverStates indexToState(int index);
driverStates buffers[buttonsMax];

//---------------------------------------------------------------
//   FUNCTIONS
//---------------------------------------------------------------
void linkageInit() {                             /*  Called once */
  for (int i = 0; i < linkagesMax; i++) {
    linkages[i] = {999, 999};
  }
  for (int i = 0; i < buttonsMax; i++) {
    buffers[i] = noDrive;
  }
}

void linkageUpdate() {
  bufferClear();
  linkInputCheck();
  writeToBuffer();
  applyBuffer();
}

//---------------------------------------------------------------
//   INTERNAL FUNCTIONS
//---------------------------------------------------------------
void bufferClear() {
  for (int i = 0; i < buttonsMax; i++) {
    buffers[i] = noDrive;
  }
}

void linkInputCheck() {
  readLink();

  if (newLinkBuffer.filled()) {
    bool linkAlreadyExists = false;
    for (int i = 0; i < activeLinkageCount; i++) {
      if (linkages[i].driverIndex == newLinkBuffer.driverIndex && linkages[i].bufferIndex == newLinkBuffer.bufferIndex) {
        linkAlreadyExists = true;
      }
    }
    if (linkAlreadyExists == true)
      removeLink();
    else
      addLink();
  }
}

void readLink() {
//  if (buttons.vals[299] == 1) {   /*patch mode and perform mode -- not holding patch down*/
    for (int i = 0; i < buttonsMax; i++)
    {
      if (buttons.vals[i] == 0)
        continue;
      else {
        if (inputCheck(i))
          newLinkBuffer.bufferIndex = i;
        else if (outputCheck(i))
          newLinkBuffer.driverIndex = i;
      }
    }
  }
  else {
    clearNewLinkBuffer();
  }
}

bool inputCheck(int index) {
  for (int i = 0; i < numInputs; i++) {
    if (index == inputs[i]) {
      return true;
    }
  }
  return false;
}

bool outputCheck(int index) {
  for (int i = 0; i < numOutputs; i++) {
    if (index == outputs[i]) {
      return true;
    }
  }
  return false;
}

void clearNewLinkBuffer() {
  newLinkBuffer = {999, 999};
}

void addLink() {
  activeLinkageCount++;
  linkages[activeLinkageCount - 1] = newLinkBuffer;
  clearNewLinkBuffer();
}

void removeLink() {
  int indexToClear = 999;
  for (int i = 0; i < activeLinkageCount; i++) {
    if (linkages[i].driverIndex == newLinkBuffer.driverIndex && linkages[i].bufferIndex == newLinkBuffer.bufferIndex)
      indexToClear = i;
  }

  for (int i = indexToClear; i < linkagesMax; i++) {
    if (i == linkagesMax - 1)
      linkages[i] = {999, 999};
    else
      linkages[i] = linkages[i + 1];
  }
  activeLinkageCount--;
  clearNewLinkBuffer();
}

void writeToBuffer() {
  // only do this is activeLinkageCount > 1 otherwise error
  for (int i = 0; i < activeLinkageCount; i++) {
    if (indexToState(linkages[i].bufferIndex) == noDrive)
      continue;
    else if (indexToState(linkages[i].bufferIndex == driveLow)) {
      if (buffers[linkages[i].bufferIndex] == noDrive)
        buffers[linkages[i].bufferIndex] = driveLow;
    }
    else {
      if (buffers[linkages[i].bufferIndex] == noDrive || buffers[linkages[i].bufferIndex] == driveLow)
        buffers[linkages[i].bufferIndex] = driveHigh;
    }
  }
}

driverStates indexToState(int index) {
  for (int i = 0; i<25; i++) {
    if (index == piano[i].index) {
      if (piano[index].state == 1 && piano[index].lastState == 0) {
        return driveHigh;
      }
      else if (piano[index].state == 0 && piano[index].lastState == 1) {
        return driveLow;
      }
      else noDrive;
    }
  }

  for (int i=0; i<
  
  return noDrive;
}

void applyBuffer() {
  for (int i = 0; i < buttonsMax; i++) {
    if (buffers[i] == driveHigh) {
      // change state to 1
    }
    else if (buffers[i] == driveLow) {
      // change state to 0
    }
    else {
      // do nothing
    }
  }
}
