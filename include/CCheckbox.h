/////////////////////////////////////////
//
//             OpenLieroX
//
// code under LGPL, based on JasonBs work,
// enhanced by Dark Charlie and Albert Zeyer
//
//
/////////////////////////////////////////


// Checkbox
// Created 30/7/02
// Jason Boettcher


#ifndef __CCHECKBOX_H__
#define __CCHECKBOX_H__


#include "InputEvents.h"


// Checkbox events
enum {
	CHK_NONE=-1,
	CHK_CHANGED
};

// Checkbox messages
enum {
	CKM_SETCHECK=0,
	CKM_GETCHECK
};


class CCheckbox : public CWidget {
public:
	// Constructor
	CCheckbox(int val) {
		iValue = val;
        bmpImage = NULL;
		iType = wid_Checkbox;
	}


private:
	// Attributes

	int			iValue;
	SDL_Surface	*bmpImage;


public:
	// Methods

	void	Create(void);
	void	Destroy(void) { }

	//These events return an event id, otherwise they return -1
	int		MouseOver(mouse_t *tMouse)			{ return CHK_NONE; }
	int		MouseUp(mouse_t *tMouse, int nDown)		{ iValue = !iValue;		return CHK_CHANGED; }
	int		MouseDown(mouse_t *tMouse, int nDown)	{ return CHK_NONE; }
	int		MouseWheelDown(mouse_t *tMouse)		{ return CHK_NONE; }
	int		MouseWheelUp(mouse_t *tMouse)		{ return CHK_NONE; }
	int		KeyDown(UnicodeChar c, int keysym)	{ return CHK_NONE; }
	int		KeyUp(UnicodeChar c, int keysym)	{ return CHK_NONE; }
	

	// Process a message sent
	DWORD SendMessage(int iMsg, DWORD Param1, DWORD Param2) {

				switch(iMsg) {
					case CKM_SETCHECK:
						iValue = Param1;
						return 0;
					case CKM_GETCHECK:
						return iValue;
				}

				return 0;
			}
	DWORD SendMessage(int iMsg, const std::string& sStr, DWORD Param) { return 0; }
	DWORD SendMessage(int iMsg, std::string *sStr, DWORD Param)  { return 0; }
		

	// Draw the title button
	void	Draw(SDL_Surface *bmpDest);

	void	LoadStyle(void);


	int		getValue(void)						{ return iValue; }

};



#endif  //  __CCHECKBOX_H__
