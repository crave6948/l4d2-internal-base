#pragma once

#include "RenderView.h"

// enum ButtonCode_t
// {
// 	KEY_SPACE = 65,
// 	KEY_ESCAPE = 70,
// 	KEY_UP = 88, 
// 	KEY_LEFT,
// 	KEY_DOWN,
// 	KEY_RIGHT,
// 	MOUSE_LEFT = 107
// };

typedef ButtonCode_t MouseCode;
typedef ButtonCode_t KeyCode;

class IVGuiInput
{
public:
	virtual ~IVGuiInput();
	virtual void SetMouseFocus(void);;
	virtual void SetMouseCapture(void);
	virtual void GetKeyCodeText(ButtonCode_t, char *, int);
	virtual void GetFocus(void);
	virtual void GetCalculatedFocus(void);
	virtual void GetMouseOver(void);
	virtual void SetCursorPos(int, int);
	virtual void GetCursorPos(int &, int &);
	virtual void WasMousePressed(ButtonCode_t);
	virtual void WasMouseDoublePressed(ButtonCode_t);
	virtual void IsMouseDown(ButtonCode_t);
	virtual void SetCursorOveride(void);
	virtual void GetCursorOveride(void);
	virtual void WasMouseReleased(ButtonCode_t);
	virtual void WasKeyPressed(ButtonCode_t);
	virtual void IsKeyDown(ButtonCode_t);
	virtual void WasKeyTyped(ButtonCode_t);
	virtual void WasKeyReleased(ButtonCode_t);
	virtual void GetAppModalSurface(void);
	virtual void SetAppModalSurface(void);
	virtual void ReleaseAppModalSurface(void);
	virtual void GetCursorPosition(int &, int &);
	virtual void SetIMEWindow(void *);
	virtual void GetIMEWindow(void);
	virtual void OnChangeIME(bool);
	virtual void GetCurrentIMEHandle(void);
	virtual void GetEnglishIMEHandle(void);
	virtual void GetIMELanguageName(wchar_t *, int);
	virtual void GetIMELanguageShortCode(wchar_t *, int);
	virtual void GetIMELanguageList(void);
	virtual void GetIMEConversionModes(void);
	virtual void GetIMESentenceModes(void);
	virtual void OnChangeIMEByHandle(int);
	virtual void OnChangeIMEConversionModeByHandle(int);
	virtual void OnChangeIMESentenceModeByHandle(int);
	virtual void OnInputLanguageChanged(void);
	virtual void OnIMEStartComposition(void);
	virtual void OnIMEComposition(int);
	virtual void OnIMEEndCompositionEv(void);;
	virtual void OnIMEShowCandidates(void);
	virtual void OnIMEChangeCandidates(void);
	virtual void OnIMECloseCandidates(void);
	virtual void OnIMERecomputeModes(void);
	virtual void GetCandidateListCount(void);
	virtual void GetCandidate(int, wchar_t *, int);
	virtual void GetCandidateListSelectedItem(void);
	virtual void GetCandidateListPageSize(void);
	virtual void GetCandidateListPageStart(void);
	virtual void SetCandidateWindowPos(int, int);
	virtual void GetShouldInvertCompositionString(void);
	virtual void CandidateListStartsAtOne(void);
	virtual void SetCandidateListPageStart(int);
	virtual void SetMouseCaptureEx(void);
	virtual void RegisterKeyCodeUnhandledListener(void);
	virtual void UnregisterKeyCodeUnhandledListener(void);
	virtual void OnKeyCodeUnhandled(void);
	virtual void SetModalSubTree(void);
	virtual void ReleaseModalSubTree(void);
	virtual void GetModalSubTree(void);
	virtual void SetModalSubTreeReceiveMessages(bool);
	virtual void ShouldModalSubTreeReceiveMessages(void);
	virtual void GetMouseCapture(void);
	virtual void GetMouseFocus(void);
	virtual void RunFrame(void);
	virtual void UpdateMouseFocus(int, int);
	virtual void PanelDeleted(void);
	virtual void InternalCursorMoved(void);
	virtual void InternalMousePressed(ButtonCode_t);
	virtual void InternalMouseDoublePressed(ButtonCode_t);
	virtual void InternalMouseReleased(ButtonCode_t);
	virtual void InternalMouseWheeled(int);
	virtual void InternalKeyCodePressed(KeyCode);
	virtual void InternalKeyCodeTyped(KeyCode code);
	virtual void InternalKeyTyped(void);
	virtual void InternalKeyCodeReleased(KeyCode code);
	virtual void CreateInputContext(void);
	virtual void DestroyInputContext(int);
	virtual void AssociatePanelWithInputContext(void);
	virtual void ActivateInputContext(int);
	virtual void PostCursorMessageEv(void);
	virtual void UpdateCursorPosInternal(int, int);
	virtual void HandleExplicitSetCursor(void);
	virtual void SetKeyCodeState(ButtonCode_t, bool);
	virtual void SetMouseCodeState(void);
	virtual void UpdateButtonState(void);
	virtual void ResetInputContext(int);
	virtual void IsChildOfModalPanel(void);
};

namespace I { inline IVGuiInput* VGuiInput = nullptr; }