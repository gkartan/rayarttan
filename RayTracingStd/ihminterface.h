#pragma warning(disable : 4530)

#include "BaseColor.h"

typedef CBaseColor<unsigned char> BaseColorChar;
class CIhmInterface 
{
public:
	CIhmInterface();           // protected constructor used by dynamic creation
	virtual ~CIhmInterface();

private:
	CMap<CString,LPCTSTR,CMultiDocTemplate*,CMultiDocTemplate*> m_Template;
	
public:
	void			InitIhm();
	void			OpenView(CString);

	CView*			GetCurrentView(CDocument *pDoc);
	CView*			GetPVisu(CString);
	bool			ExisteDoc(CString nameWnd);
	void			CloseView(CString nameWnd);
	void			SendMessage(UINT ,WPARAM, LPARAM);
	void			InitControlBar(CString);
	void			HideControlBar(CString);
	void			ShowControlBar(CString);
	void			InitControlBar(CDialogBar*,UINT);
	void			HideControlBar(CControlBar *pCtrlBar);
	void			ShowControlBar(CControlBar *pCtrlBar,DWORD,CControlBar *pCtrlBarNext=NULL);
	void			CreateToolBar(CToolBar *pToolBar,UINT IdToolBar);
	void			CreateToolBar(CString);
	CControlBar*	GetControlBar(CString);
	void			SaveAllCtrlBar();
	void			HideAll();
	void			ShowAll();

	void			SetColor(CView *,unsigned long y,
							 std::list<BaseColorChar>&);
};