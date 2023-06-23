#pragma once
class Input
{
// Methods
public:
	void GetInput();
private:
	void GetNavigationInput();
	void GetEditionInput();

// Member variables
public:
private:

	enum e_inputMode
	{
		Navigation,
		Edition
	};

	e_inputMode m_currentInputMode = Navigation;


};

