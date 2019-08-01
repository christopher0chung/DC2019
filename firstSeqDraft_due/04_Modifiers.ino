// Temp Global
const int muteNode = 283;
const int togNode = 282;
const int invertNode = 289;

// External Functions
void modifiersRead(int i){

	if (buttons.vals[muteNode])		{
		if (buttons.risingEdge(i) && nodes[i].type != 0)
			nodes[i].muteState = !nodes[i].muteState;
	}
	else if (buttons.vals[togNode]){
		if (buttons.risingEdge(i) && nodes[i].type != 0)
			nodes[i].togState = !nodes[i].togState;
	}
	else if (buttons.vals[invertNode]){
		if (buttons.risingEdge(i) && nodes[i].type != 0)
			nodes[i].invertState = !nodes[i].invertState; 
	}

}

void modifiersUpdate(int i){
	applyInvert(i);
	applyToggle(i);
	applyMute(i);
}

// Internal Functions
void applyInvert(int index){
	if (nodes[index].invertState){
		if (nodes[index].state == 1)
			nodes[index].state = 0;
		else nodes[index].state = 1;
	}
}

void applyToggle(int index){
	//TBD
}

void applyMute(int index){
	if (nodes[index].muteState)
		nodes[index].state = 0;
}