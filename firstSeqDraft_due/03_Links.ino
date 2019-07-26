

//---------------------------------------------------------------
//   MOVE TO GLOBAL
//---------------------------------------------------------------

enum GLOBALMODE {PERFORM, LIVEPATCH, EDITPATCH }
GLOBALMODE currentGlobalMode = PERFORM;

const int buttonsMax = 304;

//---------------------------------------------------------------
//   VARIABLES
//---------------------------------------------------------------
const int linksMax = 128;

struct link {
  int sender;
  int receiver;
};

link links[linksMax];
link newLinkBuffer = {999, 999};
int activeLinkCount = 0;

bool readyForNextFlag = true;
int simultaneousHold = 0;

//---------------------------------------------------------------
//   FUNCTIONS
//---------------------------------------------------------------

void linksInit() {
  for (int i = 0; i < linkagesMax; i++){
    links[i] = {999, 999};
  }
}

void linksUpdate() {
  readButtons();
  scanButtonsForNewLink();
  writeToStatesFromLinks();
}

//---------------------------------------------------------------
//   INTERNAL FUNCTIONS
//---------------------------------------------------------------

void readButtons() {

  if (currentGlobalMode == PATCHLIVE) {
    simultaneousHold = 0;

    for (int i = 0; i < buttonsMax; i++) {
      
      if (buttons.vals[i] == 1){
        simultaneousHold++;
      }
      
      if (readyForNextFlag){
      
        if (isNodeInput(i)) {
          if (newLinkBuffer.receiver == 999 && buttons.vals[i] == 1) {       // if reciever is empty, store new input based on first held input
            newLinkBuffer.reciever == i;
          }
          else if (newLinkBuffer.receiver == i && buttons.vals[i] == 0) {    // if reciever is filled and button is released, clear it
            newLinkBuffer.receiver == 999;
          }
        }
        else if (isNodeOutput(i)) {
          if (newLinkBuffer.sender == 999 && buttons.vals[i] == 1) {       // if sender is empty, store new output based on first held input
            newLinkBuffer.sender == i;
          }
          else if (newLinkBuffer.sender == i && buttons.vals[i] == 0) {    // if sender is filled and button is released, clear it
            newLinkBuffer.sender == 999;
          }
        }
      }

      if (!readyForNextFlag && simultaneousHold < 2)
        readyForNextFlag = true;
    }
  }
  else if (currentGlobalMode == PATCHEDIT) {
    //TBD
  }   
  else {
    clearNewLinkBuffer();
  }
}


void scanButtonsForNewLink() {
  if (isLinkFilled(newLinkBuffer)) {

    readyForNextFlag = false;

    bool linkAlreadyExists = false;                             // primes system so that a scan of all stored links can be compared to the newly filled link

    for (int i = 0; i < activeLinkCount; i++) {                 // scans all links to newly filled buffer
      if (areLinksSame(newLinkBuffer, links[i])){
        linkAlreadyExists = true;
      }
    }

    if (linkAlreadyExists == true) 
      removeLink(newLinkBuffer);
    
    else 
      addLink(newLinkBuffer);
    
  
  clearNewLinkBuffer();
  }
}

void writeToStatesFromLinks(){

    for (int i = 0; i < activeLinkCount; i++) {

    bool receiverState  = nodes[links[i].receiver].state;
    bool senderState  = nodes[links[i].sender].state;

    if (receiverState == 1 || senderState == 1)
      nodes[links[i].receiver].state = 1;
    else
      nodes[links[i].receiver].state = 0;

  }
}

void isNodeInput(int pressIndex) {
  if (nodes[pressIndex].type == 1 || nodes[pressIndex].type == 2)
    return true;
  else return false;
}

void isNodeOutput(int pressIndex) {
  if (nodes[pressIndex].type == 3)
    return true;
  else return false;
}

// add type 0 detection for error message to screen

bool isLinkFilled(link l) {
  if (l.sender != 999 && l.receiver != 999)
    return true;
  else return false;
}

bool areLinksSame(link linkA, link linkB) {
  if (linkA.sender == linkB.sender && linkA.receiver == linkB.receiver)
    return true;
  else return false;
}

void addLink(link l){
  // consider node type special for toggling amPatched or unPatched for module reference
}

void removeLink(link l){
    // consider node type special for toggling amPatched or unPatched for module reference
}
void clearNewLinkBuffer() {
  newLinkBuffer = {999, 999};
}
