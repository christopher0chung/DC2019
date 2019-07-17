//---------------------------------------------------------------
//  Variables
//---------------------------------------------------------------
enum driverStates {noDrive, driveLow, driveHigh};

struct link {
  int driverIndex;
  int bufferIndex;
  bool filled()
  {
    if (driverIndex != 999 && bufferIndex != 999)
      return true;
    else return false;
  };
};

link newLinkBuffer = {999, 999};

const int linkagesMax = 128;

link linkages[linkagesMax];

const int buttonsMax = 304;

driverStates buffers[buttonsMax];

int activeLinkageCount = 0;

//---------------------------------------------------------------
//  Functions
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
//  Internal Functions
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
        linkAlreadExists = true;
      }
    }
    if (linkAlreadyExists == true)
      removeLink();
    else
      addLink();
  }
}

void readLink() {
  if (buttons.vals[299] == 1) {   /*patch mode and perform mode -- not holding patch down*/
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

bool inputCheck(byte index) {
  /*if (index == 4 || index ==... */
  return true;
}

bool outputCheck(byte index) {
  return true;
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
    if (linkages[i].driverIndex == newLinkbuffer.driverIndex && linkages[i].bufferIndex == newLinkBuffer.bufferIndex)
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

driverStates indexToState(int index)
{
  if (index == 24){
    if (keys[24].lastState == 0 && keys[24].state == 1)
    return driveHigh;
    else if (... drive Low
    else noDrive;
  }
  
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
