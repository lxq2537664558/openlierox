/////////////////////////////////////////
//
//             OpenLieroX
//
// code under LGPL, based on JasonBs work,
// enhanced by Dark Charlie and Albert Zeyer
//
//
/////////////////////////////////////////


// Chat Box class
// Created 26/8/03
// Jason Boettcher


#include "LieroX.h"
#include "StringUtils.h"
#include "CChatBox.h"


///////////////////
// Clear the chatbox
void CChatBox::Clear(void)
{
	Lines.clear();
	WrappedLines.clear();
	NewLines.clear();
	nWidth = 500;
}


///////////////////
// Add a line of text to the chat box
void CChatBox::AddText(const std::string& txt, int colour, float time)
{
	if (txt == "")
		return;

	// Create a new line and copy the info
	line_t newline;

	newline.fTime = time;
	newline.iColour = colour;
	newline.strLine = txt;
	newline.iID = Lines.size();

	// Add to lines
	Lines.push_back(newline);

	// Add to wrapped lines
	AddWrapped(txt,colour,time,WrappedLines,true);
}


////////////////////
// Adds the text to wrapped lines
void CChatBox::AddWrapped(const std::string& txt, Uint32 colour, float time, ct_lines_t &lines, bool mark_as_new)
{
	// Split it to the lines
	const std::vector<std::string>& tmp = splitstring(txt, (size_t)-1, nWidth, tLX->cFont);

	// Add the lines
	for (std::vector<std::string>::const_iterator it = tmp.begin(); it != tmp.end(); it++)  {
		line_t newline;
		newline.fTime = time;
		newline.iColour = colour;
		newline.strLine = *it;
		newline.iID = WrappedLines.size();

		// Add and mark as new if needed
		lines.push_back(newline);
		if (mark_as_new)
			NewLines.push_back(newline);
	}
}

///////////////////
// Set the chatbox width
void CChatBox::setWidth(int w)
{
	nWidth = w;
	WrappedLines.clear();
	NewLines.clear();

	ct_lines_t::const_iterator i;

	// Recalculate the wrapped lines
	for (i=Lines.begin();i!=Lines.end();i++)
		AddWrapped(i->strLine,i->iColour,i->fTime, WrappedLines, false);

	// Recalculate new lines
	if (!NewLines.empty())  {
		ct_lines_t wrapped_newlines;
		for (i=NewLines.begin();i!=NewLines.end();i++)
			AddWrapped(i->strLine, i->iColour, i->fTime, wrapped_newlines, false);
		NewLines.clear();
		NewLines = wrapped_newlines;
	}
}

///////////////////
// Get a line from chatbox
line_t *CChatBox::GetLine(int n)
{
	lines_iterator it = WrappedLines.begin();
	for (int i = 0 ; i <= n && it != WrappedLines.end(); it++, i++) {}

	if (it == WrappedLines.end())
		return NULL;

	// Remove from new lines
	lines_iterator it2 = NewLines.begin();
	for (; it2 != NewLines.end(); it2++)
		if (it2->iID == it->iID)  {
			NewLines.erase(it2);
			break;
		}

	return &(*it);
}

/////////////////////
// Get a new line from the chatbox
// WARNING: not threadsafe
line_t *CChatBox::GetNewLine(void)
{
	if (NewLines.empty())
		return NULL;

	static line_t result; // We're giving a pointer to it, must always exist
	result = *NewLines.begin();
	NewLines.erase(NewLines.begin());

	return &result;
}

////////////////////
// Convert the index to iterator
lines_iterator CChatBox::At(int i)  {
	// Checks
	if (i <= 0)
		return WrappedLines.begin();

	if (i >= (int)WrappedLines.size())
		return WrappedLines.end();

	// Go to the right iterator
	lines_iterator it = WrappedLines.begin();
	while (i)  {
		it++;
		i--;
	}

	return it;
}
