#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif 
#include <string.h>

int board[3][3];
int player; //vez do jogador
int turnCounter = 0 /*contador de jogadas*/, victory /*checka quem ganhou*/;

void initBoard();
int checkBoard();

enum {
	Bola = 2,
	Cruz = 1,

	ID_NewGame = 1,
	ID_Color = 2,
	ID_MainWindow = 3
};

void initBoard()
{
	int i, j;

	player = Cruz;
	turnCounter = 0;
	victory = 0;

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			board[i][j] = 0;
		}
	}
}

int checkBoard()
{
	int i, j;
	int p1, p2;
	//verificar as linhas

	
	for (i = 0; i < 3; ++i)
	{
		p1 = 0;
		p2 = 0;
		for (j = 0; j < 3; ++j)
		{
			if (board[i][j] == Cruz)
			{
				++p1;
			}
			else if(board[i][j] == Bola)
			{
				++p2;
			}
		}
		if (p1 == 3)
		{
			return Cruz;
		}
		else if (p2 == 3)
		{
			return Bola;
		}
	}

	//verificar colunas
	
	for (j = 0; j < 3; ++j)
	{
		p1 = 0;
		p2 = 0;
		for (i = 0; i < 3; ++i)
		{
			if (board[i][j] == Cruz)
			{
				++p1;
			}
			else if (board[i][j] == Bola)
			{
				++p2;
			}
		}
		if (p1 == 3)
		{
			return Cruz;
		}
		else if (p2 == 3)
		{
			return Bola;
		}
	}

	//check coluna diagonal 1
	p1 = 0;
	p2 = 0;
	for (i = 0; i < 3; i++)
	{
		if (board[i][i] == Cruz) p1++;
		else if (board[i][i] == Bola) p2++;
	}
	if (p1 == 3)
	{
		return Cruz;
	}
	else if (p2 == 3)
	{
		return Bola;
	}


	//check coluna diagonal 2
	p1 = 0;
	p2 = 0;
	 j = 2;

	for (i = 0; i < 3; ++i)
	{
		if (board[i][j] == Cruz) p1++;
		else if (board[i][j] == Bola) p2++;
		j--;
	}

	if (p1 == 3)
	{
		return Cruz;
	}
	else if (p2 == 3)
	{
		return Bola;
	}

	//se ninguem ganhou
	return 0;
}

class wxwidgets_test : public wxApp {
public:
	virtual bool OnInit();
};

class MainFrame: public wxFrame {
public:
	MainFrame();

	
protected:
	wxMenuBar* m_mainMenuBar;
	wxMenu* m_MenuGame;
	wxMenu* m_menuHelp;
	wxMenu* m_menuColor;

	//butões do lado esquerdo
	wxButton* m_BtnLeftUpper;
	wxButton* m_BtnLeftDown;
	wxButton* m_BtnLeftCenter;

	//butões do lado direito
	wxButton* m_BtnRightUpper;
	wxButton* m_BtnRightDown;
	wxButton* m_BtnRightCenter;

	//butões do centro
	wxButton* m_BtnCenterUpper;
	wxButton* m_BtnCenterDown;
	wxButton* m_BtnCenterCenter;

	wxStatusBar* m_StatusBar;

	char m_msgStatusBar[200];

private:
	void OnNewGame(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnBckColor(wxCommandEvent& event);

	void EndGame();
	void EnableGrid();
	void DisableGrid();

	void OnBtnLeftUpperClick(wxCommandEvent& event);
	void OnBtnLeftDownClick(wxCommandEvent& event);
	void OnBtnLeftCenterClick(wxCommandEvent& event);

	void OnBtnRightUpperClick(wxCommandEvent& event);
	void OnBtnRightDownClick(wxCommandEvent& event);
	void OnBtnRightCenterClick(wxCommandEvent& event);

	void OnBtnCenterUpperClick(wxCommandEvent& event);
	void OnBtnCenterDownClick(wxCommandEvent& event);
	void OnBtnCenterCenterClick(wxCommandEvent& event);

	void OnBtnLeftUpperEnterWindow(wxCommandEvent& event);
	void OnBtnLeftDownEnterWindow(wxCommandEvent& event);
	void OnBtnLeftCenterEnterWindow(wxCommandEvent& event);

	void OnBtnRightUpperEnterWindow(wxCommandEvent& event);
	void OnBtnRightDownEnterWindow(wxCommandEvent& event);
	void OnBtnRightCenterEnterWindow(wxCommandEvent& event);

	void OnBtnCenterUpperEnterWindow(wxCommandEvent& event);
	void OnBtnCenterDownEnterWindow(wxCommandEvent& event);
	void OnBtnCenterCenterEnterWindow(wxCommandEvent& event);

	void OnBtnLeftUpperLeaveWindow(wxCommandEvent& event);
	void OnBtnLeftDownLeaveWindow(wxCommandEvent& event);
	void OnBtnLeftCenterLeaveWindow(wxCommandEvent& event);

	void OnBtnRightUpperLeaveWindow(wxCommandEvent& event);
	void OnBtnRightDownLeaveWindow(wxCommandEvent& event);
	void OnBtnRightCenterLeaveWindow(wxCommandEvent& event);

	void OnBtnCenterUpperLeaveWindow(wxCommandEvent& event);
	void OnBtnCenterDownLeaveWindow(wxCommandEvent& event);
	void OnBtnCenterCenterLeaveWindow(wxCommandEvent& event);

	
};

bool wxwidgets_test::OnInit() {
	MainFrame* frame = new MainFrame();
	frame->Show();

	initBoard();

	return true;
};



MainFrame::MainFrame() : wxFrame(NULL, ID_MainWindow, "Jogo do Galo")
{
	this->SetSizeHints(600, 600); 

	
	m_mainMenuBar = new wxMenuBar(0);
	m_MenuGame = new wxMenu();
	m_menuHelp = new wxMenu();
	m_menuColor = new wxMenu();
	

	m_mainMenuBar->Append(m_MenuGame, "Game");
	m_mainMenuBar->Append(m_menuHelp, "Help");
	m_mainMenuBar->Append(m_menuColor, "Color");

	m_MenuGame->Append(ID_NewGame, "&New Game\tCtrl-N" , "Start a new match!");
	m_MenuGame->AppendSeparator();
	m_MenuGame->Append(wxID_EXIT);

	m_menuHelp->Append(wxID_ABOUT);

	m_menuColor->Append(ID_Color, "&Color Settings\tCtrl-E", "Change the color of the background", "Change the color of the background");

	wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, false);
	

	this->SetMenuBar(m_mainMenuBar);

	wxGridSizer* gBoard = new wxGridSizer(3, 3, 0, 0);
	gBoard->SetMinSize(wxSize( 500, 500));

	//butões do lado esquerdo
	 m_BtnLeftUpper = new wxButton(this, wxID_ANY, wxEmptyString , wxDefaultPosition , wxSize(40,40), 0);
	 m_BtnLeftUpper->SetFont(font);

	 m_BtnLeftDown = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnLeftDown->SetFont(font);

	m_BtnLeftCenter = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_BtnLeftCenter->SetFont(font);

	//butões do lado direito
	 m_BtnRightUpper= new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnRightUpper->SetFont(font);

	 m_BtnRightDown = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnRightDown->SetFont(font);
	
	 m_BtnRightCenter = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnRightCenter->SetFont(font);
	
	//butões do centro
	 m_BtnCenterUpper = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnCenterUpper->SetFont(font);
	
	 m_BtnCenterDown = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnCenterDown->SetFont(font);
	
	 m_BtnCenterCenter = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	 m_BtnCenterCenter->SetFont(font);
	 

	 //metendo os butoes direito
	 gBoard->Add(m_BtnLeftUpper, 0, wxALL | wxEXPAND, 5);
	 gBoard->Add(m_BtnCenterUpper, 0, wxALL | wxEXPAND, 5);
	 gBoard->Add(m_BtnRightUpper, 0, wxALL | wxEXPAND, 5);

	 gBoard->Add(m_BtnLeftCenter, 0, wxALL | wxEXPAND, 5);
	 gBoard->Add(m_BtnCenterCenter, 0, wxALL | wxEXPAND, 5);
	 gBoard->Add(m_BtnRightCenter, 0, wxALL | wxEXPAND, 5);

	 gBoard->Add(m_BtnLeftDown, 0, wxALL | wxEXPAND, 5);
	 gBoard->Add(m_BtnCenterDown, 0, wxALL | wxEXPAND, 5);
	 gBoard->Add(m_BtnRightDown, 0, wxALL | wxEXPAND, 5);


	 this->SetSizer(gBoard);
	 this->Layout();
	
	 m_StatusBar = this -> CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	 this->Centre(wxBOTH);

	 DisableGrid();
	 SetStatusText("Vá a novo jogo para começar um novo jogo");

	 SetBackgroundColour(wxColour(*wxBLUE));

	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnNewGame, this , ID_NewGame);
	Bind(wxEVT_MENU, &MainFrame::OnBckColor, this, ID_Color);

	m_BtnLeftUpper->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLeftUpperClick), NULL, this);
	m_BtnLeftDown->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLeftDownClick), NULL, this);
	m_BtnLeftCenter->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLeftCenterClick), NULL, this);

	m_BtnRightUpper->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnRightUpperClick), NULL, this);
	m_BtnRightDown->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnRightDownClick), NULL, this);
	m_BtnRightCenter->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnRightCenterClick), NULL, this);

	m_BtnCenterUpper->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnCenterUpperClick), NULL, this);
	m_BtnCenterDown->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnCenterDownClick), NULL, this);
	m_BtnCenterCenter->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnCenterCenterClick), NULL, this);


	m_BtnLeftUpper->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLeftUpperEnterWindow), NULL, this);
	m_BtnLeftDown->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLeftDownEnterWindow), NULL, this);
	m_BtnLeftCenter->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLeftCenterEnterWindow), NULL, this);

	m_BtnRightUpper->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnRightUpperEnterWindow), NULL, this);
	m_BtnRightDown->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnRightDownEnterWindow), NULL, this);
	m_BtnRightCenter->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnRightCenterEnterWindow), NULL, this);

	m_BtnCenterUpper->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnCenterUpperEnterWindow), NULL, this);
	m_BtnCenterDown->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnCenterDownEnterWindow), NULL, this);
	m_BtnCenterCenter->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnCenterCenterEnterWindow), NULL, this);

	m_BtnLeftUpper->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLeftUpperLeaveWindow), NULL, this);
	m_BtnLeftDown->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLeftDownLeaveWindow), NULL, this);
	m_BtnLeftCenter->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLeftCenterLeaveWindow), NULL, this);

	m_BtnRightUpper->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnRightUpperLeaveWindow), NULL, this);
	m_BtnRightDown->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnRightDownLeaveWindow), NULL, this);
	m_BtnRightCenter->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnRightCenterLeaveWindow), NULL, this);

	m_BtnCenterUpper->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnCenterUpperLeaveWindow), NULL, this);
	m_BtnCenterDown->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnCenterDownLeaveWindow), NULL, this);
	m_BtnCenterCenter->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnCenterCenterLeaveWindow), NULL, this);



}

wxIMPLEMENT_APP(wxwidgets_test);



void  MainFrame::EndGame() 
{
	char mensagem[200] = "";
	if (victory == 0)
	{
		strcpy(mensagem, "Tied match!");
	}
	else if (victory == Cruz)
	{
		strcpy(mensagem, "Cruz - Player 1 ganhou!");
	}
	else if (victory == Bola)
	{
		strcpy(mensagem, "Bola - Player 2 ganhou!");
	}

	strcat(mensagem, "\t Jogar de novo?");
	if (wxMessageBox(mensagem, "Fim de partida", wxYES_NO | wxICON_INFORMATION) == wxYES)
	{
		initBoard();
		EnableGrid();
	}
	else
	{
		wxExit();
	}
}
void  MainFrame::EnableGrid()
{
	
	 m_BtnLeftUpper->Enable();
	 m_BtnLeftDown->Enable();
	 m_BtnLeftCenter->Enable();

	 m_BtnRightUpper->Enable();
	 m_BtnRightDown->Enable();
	 m_BtnRightCenter->Enable();

	 m_BtnCenterUpper->Enable();
	 m_BtnCenterDown->Enable();
	 m_BtnCenterCenter->Enable();

	 m_BtnLeftUpper->SetLabelText("");
	 m_BtnLeftDown->SetLabelText("");
	 m_BtnLeftCenter->SetLabelText("");

	 m_BtnRightUpper->SetLabelText("");
	 m_BtnRightDown->SetLabelText("");
	 m_BtnRightCenter->SetLabelText("");

		 m_BtnCenterUpper->SetLabelText("");
	 m_BtnCenterDown->SetLabelText("");
	 m_BtnCenterCenter->SetLabelText("");

}
void  MainFrame::DisableGrid()
{
	m_BtnLeftUpper->Disable();
	m_BtnLeftDown->Disable();
	m_BtnLeftCenter->Disable();

	m_BtnRightUpper->Disable();
	m_BtnRightDown->Disable();
	m_BtnRightCenter->Disable();

	m_BtnCenterUpper->Disable();
	m_BtnCenterDown->Disable();
	m_BtnCenterCenter->Disable();

	m_BtnLeftUpper->SetLabelText("");
	m_BtnLeftDown->SetLabelText("");
	m_BtnLeftCenter->SetLabelText("");

	m_BtnRightUpper->SetLabelText("");
	m_BtnRightDown->SetLabelText("");
	m_BtnRightCenter->SetLabelText("");

	m_BtnCenterUpper->SetLabelText("");
	m_BtnCenterDown->SetLabelText("");
	m_BtnCenterCenter->SetLabelText("");
}

void MainFrame::OnNewGame(wxCommandEvent& event)
{
	EnableGrid();
	initBoard();
	SetStatusText("Vez do Jogador 1");
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	wxExit();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Criado por: Rodrigo Casanova\t v:2021.1.0", "About", wxOK | wxICON_QUESTION);
}

void MainFrame::OnBckColor(wxCommandEvent& event) //change background
{
		wxPanel* panel = new wxPanel( this , ID_MainWindow, wxDefaultPosition, wxSize(600, 600));
		panel->SetBackgroundColour(wxColour(*wxRED));
}


void  MainFrame::OnBtnLeftUpperClick(wxCommandEvent& event)
{
	if (m_BtnLeftUpper->IsEnabled())
	{
		board[0][0] = player;
		m_BtnLeftUpper->Disable();
		if (player == Cruz)
		{
			m_BtnLeftUpper->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnLeftUpper->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}
void  MainFrame::OnBtnLeftDownClick(wxCommandEvent& event)
{
	if (m_BtnLeftDown->IsEnabled())
	{
		board[2][0] = player;
		m_BtnLeftDown->Disable();
		if (player == Cruz)
		{
			m_BtnLeftDown->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnLeftDown->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}
void  MainFrame::OnBtnLeftCenterClick(wxCommandEvent& event)
{
	if (m_BtnLeftCenter->IsEnabled())
	{
		board[1][0] = player;
		m_BtnLeftCenter->Disable();
		if (player == Cruz)
		{
			m_BtnLeftCenter->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnLeftCenter->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}


void  MainFrame::OnBtnRightUpperClick(wxCommandEvent& event)
{
	if (m_BtnRightUpper->IsEnabled())
	{
		board[0][2] = player;
		m_BtnRightUpper->Disable();
		if (player == Cruz)
		{
			m_BtnRightUpper->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnRightUpper->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}
void  MainFrame::OnBtnRightDownClick(wxCommandEvent& event)
{
	if (m_BtnRightDown->IsEnabled())
	{
		board[2][2] = player;
		m_BtnRightDown->Disable();
		if (player == Cruz)
		{
			m_BtnRightDown->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnRightDown->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}
void  MainFrame::OnBtnRightCenterClick(wxCommandEvent& event)
{
	if (m_BtnRightCenter->IsEnabled())
	{
		board[1][2] = player;
		m_BtnRightCenter->Disable();
		if (player == Cruz)
		{
			m_BtnRightCenter->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnRightCenter->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}


void  MainFrame::OnBtnCenterUpperClick(wxCommandEvent& event)
{
	if (m_BtnCenterUpper->IsEnabled())
	{
		board[0][1] = player;
		m_BtnCenterUpper->Disable();
		if (player == Cruz)
		{
			m_BtnCenterUpper->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnCenterUpper->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}
void  MainFrame::OnBtnCenterDownClick(wxCommandEvent& event)
{
	if (m_BtnCenterDown->IsEnabled())
	{
		board[2][1] = player;
		m_BtnCenterDown->Disable();
		if (player == Cruz)
		{
			m_BtnCenterDown->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnCenterDown->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}
void  MainFrame::OnBtnCenterCenterClick(wxCommandEvent& event)
{
	if (m_BtnCenterCenter->IsEnabled())
	{
		board[1][1] = player;
		m_BtnCenterCenter->Disable();
		if (player == Cruz)
		{
			m_BtnCenterCenter->SetLabelText("X");
			player = Bola;
		}
		else if (player == Bola)
		{
			m_BtnCenterCenter->SetLabelText("O");
			player = Cruz;
		}
		turnCounter++;
		victory = checkBoard();
	}
	if (victory != 0 || turnCounter >= 9)
	{
		EndGame();
	}
}

void MainFrame::OnBtnLeftUpperEnterWindow(wxCommandEvent& event)
{
	if (m_BtnLeftUpper->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLeftDownEnterWindow(wxCommandEvent& event)
{
	if (m_BtnLeftDown->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLeftCenterEnterWindow(wxCommandEvent& event)
{
	if (m_BtnLeftCenter->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnRightUpperEnterWindow(wxCommandEvent& event)
{
	if (m_BtnRightUpper->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnRightDownEnterWindow(wxCommandEvent& event)
{
	if (m_BtnRightDown->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnRightCenterEnterWindow(wxCommandEvent& event)
{
	if (m_BtnRightCenter->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnCenterUpperEnterWindow(wxCommandEvent& event)
{
	if (m_BtnCenterUpper->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnCenterDownEnterWindow(wxCommandEvent& event)
{
	if (m_BtnCenterDown->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnCenterCenterEnterWindow(wxCommandEvent& event)
{
	if (m_BtnCenterCenter->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "Y");
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnLeftUpperLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnLeftUpper->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnBtnLeftDownLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnLeftDown->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLeftCenterLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnLeftCenter->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnRightUpperLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnRightUpper->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnRightDownLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnRightDown->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnBtnRightCenterLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnRightCenter->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnCenterUpperLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnCenterUpper->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnCenterDownLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnCenterDown->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnCenterCenterLeaveWindow(wxCommandEvent& event)
{
	if (m_BtnCenterCenter->IsEnabled())
	{
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Pressione para jogar um/a ");
		if (player == Cruz)
		{
			strcat(m_msgStatusBar, "X");
		}
		else if (player == Bola)
		{
			strcat(m_msgStatusBar, "O");
		}
	}
	SetStatusText(m_msgStatusBar);
}