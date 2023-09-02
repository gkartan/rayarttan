///////////////////////////////////////////
////Code provenant de codeguru.com
inline bool createDirectory(CString wsPath)
{ 
	
	char SLASH='\\'; 
	DWORD attr; 
	int pos; 
	bool result = true; 
	
	// Check for trailing slash: 
	pos = wsPath.ReverseFind(SLASH); 
	
	if (wsPath.GetLength() == pos + 1) // last character is "\" 
	{ 
		wsPath = wsPath.Left(pos); 
	} 
	
	// Look for existing object: 
	attr = GetFileAttributes(LPCTSTR(wsPath)); 
	if (0xFFFFFFFF == attr) // doesn't exist yet - create it! 
	{ 
		pos = wsPath.ReverseFind(SLASH); 
		if (0 < pos) 
		{ 
			// Create parent dirs: 
			result = createDirectory(wsPath.Left(pos)); 
		} 
		// Create node: 
		result = result & CreateDirectory(LPCTSTR(wsPath), NULL); 
		//result = result; 
	} 
	else if (! (GetFileAttributes(LPCTSTR(wsPath)) & FILE_ATTRIBUTE_DIRECTORY)) 
	{ // object already exists, but is not a dir 
		SetLastError(ERROR_FILE_EXISTS); 
		result = false; 
	} 
	return result; 
} 


inline void ExtractName(const CString &Path,CString &Name) 
{
	int Begin=Path.ReverseFind('\\');
	int End=Path.ReverseFind('.');

	Name=Path.Mid(Begin+1,End-Begin-1);
}


//*********************************************************************************
// Function name		- GetFolder
// Description			- Get a folder path
// In					-
//						  strSelectedFolder - reference to string for store folder path
// Out				-
//						  lpszTitle - title for caption
//						  hwndOwner - reference to parent window 
//						  strRootFolder - root folder 
//						  strStartFolder - current foldet
// Return				- TRUE if user select OK, else FALSE.
//*********************************************************************************

static CString strTmpPath;

inline int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	TCHAR szDir[MAX_PATH];
	switch(uMsg){
	case BFFM_INITIALIZED:
		if (lpData){
			strcpy(szDir, strTmpPath.GetBuffer(strTmpPath.GetLength()));
			SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
		}
		break;
	case BFFM_SELCHANGED: {
	   if (SHGetPathFromIDList((LPITEMIDLIST) lParam ,szDir)){
		  SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
	   }
	   break;
	}
	default:
	   break;
	}
         
	return 0;
}

inline BOOL GetFolder(CString* strSelectedFolder,
				   const char* lpszTitle,
				   const HWND hwndOwner, 
				   const char* strRootFolder, 
				   const char* strStartFolder)
{
	char pszDisplayName[MAX_PATH];
	LPITEMIDLIST lpID;
	BROWSEINFOA bi;
	
	bi.hwndOwner = hwndOwner;
	if (strRootFolder == NULL){
		bi.pidlRoot = NULL;
	}else{
	   LPITEMIDLIST  pIdl = NULL;
	   IShellFolder* pDesktopFolder;
	   char          szPath[MAX_PATH];
	   OLECHAR       olePath[MAX_PATH];
	   ULONG         chEaten;
	   ULONG         dwAttributes;

	   strcpy(szPath, (LPCTSTR)strRootFolder);
	   if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
	   {
		   MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szPath, -1, olePath, MAX_PATH);
		   pDesktopFolder->ParseDisplayName(NULL, NULL, olePath, &chEaten, &pIdl, &dwAttributes);
		   pDesktopFolder->Release();
	   }
	   bi.pidlRoot = pIdl;
	}
	bi.pszDisplayName = pszDisplayName;
	bi.lpszTitle = lpszTitle;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpfn = BrowseCallbackProc;
	if (strStartFolder == NULL){
		bi.lParam = FALSE;
	}else{
		strTmpPath.Format("%s", strStartFolder);
		bi.lParam = TRUE;
	}
	bi.iImage = NULL;
	lpID = SHBrowseForFolderA(&bi);
	if (lpID != NULL){
		BOOL b = SHGetPathFromIDList(lpID, pszDisplayName);

		LPMALLOC pMalloc = NULL; 
		HRESULT hResult = SHGetMalloc (&pMalloc); 
		if (hResult == NOERROR && pMalloc) 
		pMalloc->Free (lpID); 
		pMalloc->Release(); 

		if (b == TRUE){
			strSelectedFolder->Format("%s",pszDisplayName);
			return TRUE;
		}
	}else{
		strSelectedFolder->Empty();
	}
	return FALSE;
}
