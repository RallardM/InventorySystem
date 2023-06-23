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
		NAVIGATION,
		EDITION,
		COUNT
	};

	e_inputMode m_currentInputMode = NAVIGATION;


};

