#include <iostream>
using namespace std;
#pragma once
#ifndef _NEWER_
#define _NEWER_
#ifndef RC_INVOKED
#include <exception>
#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#if !defined(__CRTDECL)
#if defined(_M_CEE_PURE)
#define __CRTDECL
#else
#define __CRTDECL   __cdecl
#endif
#endif

_STD_BEGIN

#if !defined(_INC_NEW) || !defined(_MSC_EXTENSIONS)
#ifdef _M_CEE_PURE
typedef void (__clrcall * new_handler) ();
#else
typedef void (__cdecl * new_handler) ();
#endif
#endif

#ifndef __NOTHROW_T_DEFINED
struct nothrow_t {
	extern const nothrow_t nothrow;	// constant for placement new tag
#endif 

_CRTIMP2 new_handler __cdecl set_new_handler(_In_opt_ new_handler)
	_THROW0();
_STD_END

void __CRTDECL operator delete(void *) _THROW0();
#pragma warning (suppress: 4985)
_Ret_bytecap_(_Size) void *__CRTDECL operator new(size_t _Size) _THROW1(_STD bad_alloc);

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void *__CRTDECL operator new(size_t, void *_Where) _THROW0()
	{
	cout << "New!\n";
	return (_Where);
	}

inline void __CRTDECL operator delete(void *, void *) _THROW0()
	{
		cout << "Delete!\n";
	}
#endif

#ifndef __PLACEMENT_VEC_NEW_INLINE
#define __PLACEMENT_VEC_NEW_INLINE
inline void *__CRTDECL operator new[](size_t, void *_Where) _THROW0()
	{
	cout << "New!\n";
	return (_Where);
	}

inline void __CRTDECL operator delete[](void *, void *) _THROW0()
	{
		cout << "Delete!\n";
	}
#endif

void __CRTDECL operator delete[](void *) _THROW0();

_Ret_bytecap_(_Size) void *__CRTDECL operator new[](size_t _Size)
	_THROW1(_STD bad_alloc);

#ifndef __NOTHROW_T_DEFINED
#define __NOTHROW_T_DEFINED
_Ret_opt_bytecap_(_Size) void *__CRTDECL operator new(size_t _Size, const _STD nothrow_t&)
	_THROW0();

_Ret_opt_bytecap_(_Size) void *__CRTDECL operator new[](size_t _Size, const _STD nothrow_t&)
	_THROW0();

void __CRTDECL operator delete(void *, const _STD nothrow_t&)
	_THROW0();

void __CRTDECL operator delete[](void *, const _STD nothrow_t&)
	_THROW0();
#endif


#if !defined(_INC_NEW) || !defined(_MSC_EXTENSIONS)
using _STD new_handler;
#endif 

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)

#endif
#endif
