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
int linkCount = 0;

int activeNode = 999;


//---------------------------------------------------------------
//   FUNCTIONS
//---------------------------------------------------------------

void linksInit() {

    for (int i = 0; i < linksMax; i++)
        links[i] = {999, 999};

}


void linkStateUpdate(){

    for (int i = 0; i < linkCount; i++) {

        bool senderState = nodes[links[i].sender].state;

        if (senderState == 1)
            nodes[links[i].receiver].state = 1;
        else if (senderState == 0)   
            nodes[links[i].receiver].state = orGate(i);

    }
}


bool orGate(int index) {
    
    for (int i = 0; i < index; i++) 
        if (links[i].receiver == links[index].receiver) 
            if (nodes[links[i].sender].state == 1)
                return 1;

    return 0;

}

//---------------------------------------------------------------
//   INTERNAL FUNCTIONS
//---------------------------------------------------------------

void readButtons() {

    if (activeNode != 999) 
        displayActiveNodeLinks();


    if (currentGlobalMode == LIVEPATCH) {

        for (int i = 0; i < buttonsMax; i++) {    

            if (buttons.hasChanged(i)) {

                // Set an Active Node --------------------------------------------------------
                if (activeNode == 999 && buttons.risingEdge(i) && nodes[i].type != 0) {

                    activeNode = i;

                    if (isNodeOutput(i)) 
                        newLinkBuffer.sender = i;  
                    else if (isNodeInput(i)) 
                        newLinkBuffer.receiver = i;

                    Serial.println("on");

                }
                else if (activeNode != 999 && buttons.fallingEdge(activeNode)) {

                    activeNode = 999;
                    leds.fillScreen(0);
                    Serial.println("off");

                    for (int i = 0; i < buttonsMax; i++) 
                        leds.drawPixel(nodes[i].ledx, nodes[i].ledy, nodes[i].state);

                }

                // When Active Node is Set ---------------------------------------------------
                if (activeNode != 999) {

                    if (buttons.risingEdge(i)) {

                        if (isNodeOutput(activeNode) && isNodeInput(i)) {

                            if (linkExists(activeNode, i)) 
                                removeLink(activeNode, i);
                            else
                                addLink(activeNode, i);  

                        }
                        else if (isNodeOutput(i) && isNodeInput(activeNode)) {

                            if (linkExists(i, activeNode)) 
                                removeLink(i, activeNode);
                            else
                                addLink(i, activeNode);

                        }           
                    }
                }       
            }
        }
    }
}


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


void addLink(int nodeA, int nodeB) {

    links[linkCount].sender   = nodeA;
    links[linkCount].receiver = nodeB;

    linkCount++;

    screenPrint(linkCount);
    screen.writeDigitAscii(0, 'L');
    screen.writeDisplay();

    if (linkCount >= linksMax) {      
        linkCount = 127;
        screenPrint("LMAX");
    }

}


void removeLink(int nodeA, int nodeB) {

    int indexToRemove = 999;

    for (int i = 0; i < linkCount; i++) 
        if (links[i].sender == nodeA && links[i].receiver == nodeB)  
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

    screenPrint(linkCount);
    screen.writeDigitAscii(0, 'L');
    screen.writeDisplay();

}


void displayActiveNodeLinks() {

    leds.fillScreen(0);

    byte x = nodes[activeNode].ledx;
    byte y = nodes[activeNode].ledy;
    leds.drawPixel(x, y, HIGH);

    if (isNodeOutput(activeNode)) {

        for (int i = 0; i < linkCount; i++) {

            if (links[i].sender == activeNode) {

                x = nodes[links[i].receiver].ledx;
                y = nodes[links[i].receiver].ledy;
                leds.drawPixel(x, y, HIGH);

            }
        }
    } 
    else if (isNodeInput(activeNode)) {

        for (int i = 0; i < linkCount; i++) {

            if (links[i].receiver == activeNode) {

                x = nodes[links[i].sender].ledx;
                y = nodes[links[i].sender].ledy;
                leds.drawPixel(x, y, HIGH);

            }
        }
    }
}
