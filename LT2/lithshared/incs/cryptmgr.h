#if !defined(_CRYPTMGR_H_)
#define _CRYPTMGR_H_

#include "iostream.h"


#ifndef NO_PRAGMA_LIBS
	#if defined(_DEBUG) && defined(_AFXDLL)
		#pragma comment (lib, "\\Proj\\Libs\\Debug\\CryptMgrMfcDll.lib")
	#elif defined(_DEBUG) && !defined(_AFXDLL)
		#pragma comment (lib, "\\Proj\\Libs\\Debug\\CryptMgr.lib")
	#elif !defined(_DEBUG) && defined(_AFXDLL)
		#pragma comment (lib, "\\Proj\\Libs\\Release\\CryptMgrMfcDll.lib")
	#elif !defined(_DEBUG) && !defined(_AFXDLL)
		#pragma comment (lib, "\\Proj\\Libs\\Release\\CryptMgr.lib")
	#endif
#endif



class CCryptMgr
{
public:

	CCryptMgr();
	CCryptMgr(char* key);
	~CCryptMgr();

	void SetKey(const char* key);  // Max of 56 characters

	// if using fstreams be sure to open them in binary mode
	void Encrypt(istream& is, ostream& os);

	// if using fstreams be sure to open them in binary mode
	void Decrypt(istream& is, ostream& os);

};






#endif