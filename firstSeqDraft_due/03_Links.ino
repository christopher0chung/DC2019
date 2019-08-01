//---------------------------------------------------------------
//   VARIABLES
//---------------------------------------------------------------

const int linksMax = 128;

struct link {
    int sender;
    int receiver;
};

link links[linksMax];
link undoBuffer = {999, 999};
int linkCount = 0;

int activeNode = 999;


//---------------------------------------------------------------
//   MAIN FUNCTIONS
//---------------------------------------------------------------

void linksInit() {

    for (int i = 0; i < linksMax; i++)
        links[i] = {999, 999};

}


void patch(int index) {

    // Undo Function -------------------------------------------------------------
    // if (buttons.risingEdge(295))
    //     undoLastLink(); 


    // Set an Active Node --------------------------------------------------------

    if (activeNode == 999 && buttons.risingEdge(index) && nodes[index].type != 0)
        activeNode = index;  
    else if (activeNode != 999 && buttons.fallingEdge(activeNode)) 
        activeNode = 999;


    // When Active Node is Set ---------------------------------------------------

    if (activeNode != 999) {

        if (buttons.risingEdge(index)) {

            if (isNodeOutput(activeNode) && isNodeInput(index)) {

                if (linkExists(activeNode, index)) 
                    removeLink(activeNode, index);
                else
                    addLink(activeNode, index);  

            }
            else if (isNodeOutput(index) && isNodeInput(activeNode)) {

                if (linkExists(index, activeNode)) 
                    removeLink(index, activeNode);
                else
                    addLink(index, activeNode);

            }           
        }
    }       
}


void  displayLinks() {

    if (userMode == 1 || userMode == 0)
        if (activeNode != 999) 
            ledsActiveNodeLinks();

}


//---------------------------------------------------------------
//   CHECK FUNCTIONS
//---------------------------------------------------------------

bool isNodeInput(int index) {

    if (nodes[index].type == 1 || nodes[index].type == 2)
        return true;
    else return false;

}


bool isNodeOutput(int index) {

    if (nodes[index].type == 3)
        return true;
    else return false;

}


bool linkExists(int nodeA, int nodeB) {

    for (int i = 0; i < linkCount; i++)            
        if (links[i].sender == nodeA && links[i].receiver == nodeB) 
            return true;
        
    return false;

}


//---------------------------------------------------------------
//   MAKE AND UNMAKE LINK FUNCTIONS
//---------------------------------------------------------------

void addLink(int nodeS, int nodeR) {

    links[linkCount].sender   = nodeS;
    links[linkCount].receiver = nodeR;

    linkCount++;
    screenLinkCount();

    if (linkCount >= linksMax) {      
        linkCount = 127;
        screenPrint("LMAX");
    }
}


void removeLink(int nodeS, int nodeR) {

    nodes[nodeR].state = 0; 
    int indexToRemove = 999;

    for (int i = 0; i < linkCount; i++) 
        if (links[i].sender == nodeS && links[i].receiver == nodeR)  
            indexToRemove = i;   

    for (int i=indexToRemove; i < linksMax; i++) {
        
        if (i == linksMax - 1) {
            links[i].sender   = 999;
            links[i].receiver = 999;
        }
        else 
            links[i] = links[i+1];

    }     

    linkCount--;
    screenLinkCount();

}


void undoLastLink() {

    if (linkCount > 0) {

        int currentIndex = linkCount - 1;
        int nodeR = links[currentIndex].receiver;

        nodes[nodeR].state = 0;
        links[currentIndex].sender   = 999;
        links[currentIndex].receiver = 999;

        linkCount--;
        screenLinkCount();

    }
}


//---------------------------------------------------------------
//   DISPLAY FUNCTIONS
//---------------------------------------------------------------

void screenLinkCount() {

    screenPrint(linkCount);
    screen.writeDigitAscii(0, 'L');
    screen.writeDisplay();

}


void ledsAllLinks() {

    ledsClearLinks();

    byte x;
    byte y;

    for (int i = 0; i < linkCount; i++) {

        x = nodes[links[i].receiver].ledx;
        y = nodes[links[i].receiver].ledy;
        leds.drawPixel(x, y, 1);

        x = nodes[links[i].sender].ledx;
        y = nodes[links[i].sender].ledy;
        leds.drawPixel(x, y, 1);

    }
}


void ledsActiveNodeLinks() {

    ledsClearLinks();

    byte x = nodes[activeNode].ledx;
    byte y = nodes[activeNode].ledy;
    leds.drawPixel(x, y, 1);

    if (isNodeOutput(activeNode)) {

        for (int i = 0; i < linkCount; i++) {

            if (links[i].sender == activeNode) {

                x = nodes[links[i].receiver].ledx;
                y = nodes[links[i].receiver].ledy;
                leds.drawPixel(x, y, 1);

            }
        }
    } 
    else if (isNodeInput(activeNode)) {

        for (int i = 0; i < linkCount; i++) {

            if (links[i].receiver == activeNode) {

                x = nodes[links[i].sender].ledx;
                y = nodes[links[i].sender].ledy;
                leds.drawPixel(x, y, 1);

            }
        }
    }
}


void ledsClearLinks() {

    leds.fillScreen(0);
    leds.drawPixel(nodes[userModeNode].ledx, nodes[userModeNode].ledy, nodes[userModeNode].state);
    leds.drawPixel(nodes[comCtrlModeNode].ledx, nodes[comCtrlModeNode].ledy, nodes[comCtrlModeNode].state);   

}

//---------------------------------------------------------------
//   UPDATE STATES FUNCTIONS
//---------------------------------------------------------------

void linkStateUpdate(){

    for (int i = 0; i < linkCount; i++) {

        byte x = nodes[links[i].receiver].ledx;
        byte y = nodes[links[i].receiver].ledy;
        bool senderState = nodes[links[i].sender].state;

        if (senderState == 1) 
            nodes[links[i].receiver].state = 1;    
        else if (senderState == 0 && buttons.vals[links[i].receiver] != 1)  
            nodes[links[i].receiver].state = orGate(i);

        leds.drawPixel(x, y, nodes[links[i].receiver].state);

    }
}


bool orGate(int index) {
    
    for (int i = 0; i < index; i++) 
        if (links[i].receiver == links[index].receiver) 
            if (nodes[links[i].sender].state == 1)
                return 1;

    return 0;

}
