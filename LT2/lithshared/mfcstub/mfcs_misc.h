// mfcs_misc.h - Misc. types and defines for the MFC stub

#ifndef __MFCS_MISC_H__
#define __MFCS_MISC_H__

// Note : Trace would be much better off with an actual implementation...
inline void MFCStubTrace(const char *pFormat, ...) {}
#define TRACE MFCStubTrace

#define DEBUG_NEW new

#endif // __MFCS_MISC_H__