#include "SubGUIClass.h"
#include <vector>

SubGUIClass::SubGUIClass(wxWindow* parent) : GUIClass(parent) {
}
std::string turn = "O";

void SubGUIClass::OnExitMenuSelect(wxCommandEvent& event){
    int answer = wxMessageBox("Quit program?", "Confirm", wxYES_NO, this);
    if (answer == wxYES) { Close(); }
}

void SubGUIClass::OnResetMenuSelect(wxCommandEvent& event) {
    int answer = wxMessageBox("Reset game?", "Confirm", wxYES_NO, this);
    if (answer == wxYES) { reset(); }
}

void SubGUIClass::reset() {
    std::vector<wxButton*> allButtons = { TL, TM, TR, ML, MM, MR, BL, BM, BR };
    for (wxButton* button : allButtons) { button->SetLabel(""); } //uses vector of pointers to loop and clear labels
    turn = "O";
}

void SubGUIClass::OnButtonClicked(wxCommandEvent& event){
    wxObject* obj = event.GetEventObject();
    wxButton* button = (wxButton*)obj;
    if (button->GetLabel() == "") { //only executes if the box is empty
        button->SetLabel(turn); //labels button
        if (CheckWinConditions()){ //win check
            int answer = wxMessageBox(turn + " wins. Play again?", "Confirm", wxYES_NO, this);
            if (answer == wxYES) { reset(); }
            else if (answer == wxNO) { OnExitMenuSelect(event); }
            reset();
        }
        else if(CheckTieCondition()) { //tie check
               int answer = wxMessageBox("Tie game. Play again?", "Confirm", wxYES_NO, this);
               if (answer == wxYES) { reset(); }
               else if (answer == wxNO) { OnExitMenuSelect(event); }
        }
        else{ //no win or draw, proceed next move
            if (turn == "O") { turn = "X"; } //flips turn to other player
            else { turn = "O"; }
            statusBar->SetStatusText(turn + "'s turn"); //updates status bar
        }
    }
}

void SubGUIClass::StatusBarMessage(wxActivateEvent& event) {
    statusBar->SetStatusText(turn + "'s turn"); //displays the turn before moves begin
}

bool SubGUIClass::CheckWinConditions() {
    std::vector<std::vector<wxButton*>> allWinConditions = { {TL, TM, TR}, {ML, MM, MR}, {BL, BM, BR}, //row wins
                                                             {TL, ML, BL}, {TM, MM, BM}, {TR, MR, BR}, //column wins
                                                             {TL, MM, BR}, {TR, MM, BL} };             //diagonal wins
    for (std::vector<wxButton*> v : allWinConditions) {
        if (v.at(0)->GetLabel() == v.at(1)->GetLabel() && v.at(1)->GetLabel() == v.at(2)->GetLabel() && v.at(2)->GetLabel() == turn) {
            return true; //checks equality of 3 buttons in all 8 possible win conditions
        }
    }
    return false;
}

bool SubGUIClass::CheckTieCondition() {
    std::vector<wxButton*> allButtons = { TL, TM, TR, ML, MM, MR, BL, BM, BR };
    for (wxButton* button : allButtons) { //checks all buttons
        if (button->GetLabel() == "") {
            return false; //no tie if a single blank is detected
        }
    }
    return true; //if all labels are full and this is only executed when there is no win condition, then it must be a tie
}