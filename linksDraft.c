

const int linksMax = 128;

struct link {
	int sender;
	int receiver;
};

link links[linksMax];
link newLinkBuffer = {999, 999};
int activeLinkCount = 0; 


//---------------------------------------------------------------
//   FUNCTIONS
//---------------------------------------------------------------

void linksInit() {                             
	for (int i = 0; i < linkagesMax; i++)
    	links[i] = {999, 999};
}

void linksUpdate() {

	for (int i=0; i<activeLinkCount; i++) {

		bool receiverState	= nodes[links[i].receiver].state;
		bool senderState 	= nodes[links[i].sender].state;

		if (receiverState == 1 || senderState == 1)
			nodes[links[i].receiver].state = 1;
		else 
			nodes[links[i].receiver].state = 0;

	}
}

//---------------------------------------------------------------
//   INTERNAL FUNCTIONS
//---------------------------------------------------------------

void linkInputCheck(int pressIndex) {



}

//


      switch (nodes[i].type) {
        case 0:
          patchType = "non-patch";
        case 1:
          patchType = "input";
        case 2:
          patchType = "special input";
        case 3:
          patchType = "output";

      }