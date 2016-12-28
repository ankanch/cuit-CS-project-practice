

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Dec 28 17:04:15 2016
 */
/* Compiler settings for mypad.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __mypad_h_h__
#define __mypad_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Imypad_FWD_DEFINED__
#define __Imypad_FWD_DEFINED__
typedef interface Imypad Imypad;

#endif 	/* __Imypad_FWD_DEFINED__ */


#ifndef __mypad_FWD_DEFINED__
#define __mypad_FWD_DEFINED__

#ifdef __cplusplus
typedef class mypad mypad;
#else
typedef struct mypad mypad;
#endif /* __cplusplus */

#endif 	/* __mypad_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __mypad_LIBRARY_DEFINED__
#define __mypad_LIBRARY_DEFINED__

/* library mypad */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_mypad;

#ifndef __Imypad_DISPINTERFACE_DEFINED__
#define __Imypad_DISPINTERFACE_DEFINED__

/* dispinterface Imypad */
/* [uuid] */ 


EXTERN_C const IID DIID_Imypad;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EA04B42F-9750-4F0C-928C-271FA4902396")
    Imypad : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ImypadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Imypad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Imypad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Imypad * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Imypad * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Imypad * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Imypad * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Imypad * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ImypadVtbl;

    interface Imypad
    {
        CONST_VTBL struct ImypadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Imypad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Imypad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Imypad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Imypad_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Imypad_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Imypad_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Imypad_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Imypad_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_mypad;

#ifdef __cplusplus

class DECLSPEC_UUID("D73F77BF-CD7F-49B2-888B-0F303438D597")
mypad;
#endif
#endif /* __mypad_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


