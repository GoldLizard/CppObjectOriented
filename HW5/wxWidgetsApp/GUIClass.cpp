///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUIClass.h"

///////////////////////////////////////////////////////////////////////////

GUIClass::GUIClass( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	menuBar = new wxMenuBar( 0 );
	menu = new wxMenu();
	wxMenuItem* exitMenu;
	exitMenu = new wxMenuItem( menu, wxID_ANY, wxString( wxT("Exit") ) + wxT('\t') + wxT("ALT-F4"), wxEmptyString, wxITEM_NORMAL );
	menu->Append( exitMenu );
	
	menuBar->Append( menu, wxT("File") ); 
	
	this->SetMenuBar( menuBar );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* TopRow;
	TopRow = new wxBoxSizer( wxHORIZONTAL );
	
	TL = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	TopRow->Add( TL, 0, wxALL, 5 );
	
	TM = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	TopRow->Add( TM, 0, wxALL, 5 );
	
	TR = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	TopRow->Add( TR, 0, wxALL, 5 );
	
	bSizer3->Add( TopRow, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* MiddleRow;
	MiddleRow = new wxBoxSizer( wxHORIZONTAL );
	
	ML = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	MiddleRow->Add( ML, 0, wxALL, 5 );
	
	MM = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	MiddleRow->Add( MM, 0, wxALL, 5 );
	
	MR = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	MiddleRow->Add( MR, 0, wxALL, 5 );
	
	bSizer3->Add( MiddleRow, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* BottomRow;
	BottomRow = new wxBoxSizer( wxHORIZONTAL );
	
	BL = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	BottomRow->Add( BL, 0, wxALL, 5 );
	
	BM = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	BottomRow->Add( BM, 0, wxALL, 5 );
	
	BR = new wxButton( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	BottomRow->Add( BR, 0, wxALL, 5 );
	
	bSizer3->Add( BottomRow, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* Options;
	Options = new wxBoxSizer( wxHORIZONTAL );
	
	resetButton = new wxButton( m_panel1, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	Options->Add( resetButton, 0, wxALL, 5 );
	
	exitButton = new wxButton( m_panel1, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	Options->Add( exitButton, 0, wxALL, 5 );
	
	bSizer3->Add( Options, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel1->SetSizer( bSizer3 );
	m_panel1->Layout();
	bSizer3->Fit( m_panel1 );
	bSizer2->Add( m_panel1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( GUIClass::StatusBarMessage ) );
	this->Connect( exitMenu->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIClass::OnExitMenuSelect ) );
	TL->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	TM->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	TR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	ML->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	MM->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	MR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	BL->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	BM->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	BR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	resetButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnResetMenuSelect ), NULL, this );
	exitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnExitMenuSelect ), NULL, this );
}

GUIClass::~GUIClass()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( GUIClass::StatusBarMessage ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIClass::OnExitMenuSelect ) );
	TL->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	TM->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	TR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	ML->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	MM->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	MR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	BL->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	BM->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	BR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnButtonClicked ), NULL, this );
	resetButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnResetMenuSelect ), NULL, this );
	exitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIClass::OnExitMenuSelect ), NULL, this );
	
}
