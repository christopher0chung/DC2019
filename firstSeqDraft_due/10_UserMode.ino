//---------------------------------------------------------------
//   VARIABLES
//---------------------------------------------------------------

String screenUserMode[3] = {"EDIT", "LINK", "PLAY"};


//---------------------------------------------------------------
//   FUNCTIONS
//---------------------------------------------------------------

void userModeSelect() {

	int userModeInputs[3] = {298, 299, 287};

	for (int i = 0; i < 3; i++) {

		if (buttons.risingEdge(userModeInputs[i])) {

			nodes[userModeInputs[userMode]].state = 0;

			userMode = i;

			nodes[userModeInputs[i]].state = 1;
			userModeNode = userModeInputs[i];
			screenPrint(screenUserMode[i]);

		}
	}
}
