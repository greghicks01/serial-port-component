//---------------------------------------------------------------------------

#ifndef FileBaseH
#define FileBaseH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
/*
 *                          Department of Defence
 *                                  © 2006
 *                            Software Engineer
 *                             Gregory Hicks
 *
 *    Component base for file reading/writing.
 *    Automatically opens valid files,
 *    Close previous file if open or if blank filename sent
 *    Events Open,Close,BOF,EOF and Fail
 *
 *    $Log: FileBase.h $
 *    Revision 1.1  2006/09/21 02:46:40  Administrator
 *    Initial revision
 *
 *
*/
class /*PACKAGE*/ TFileBase : public TComponent
{
        typedef TComponent Inherited ;
public:
        __fastcall      TFileBase ( TComponent * ) ;
        void __fastcall TestOpen  ( ) ;
        typedef AnsiString __fastcall ( __closure * TCallBack ) ( int ) ;
        typedef void __fastcall ( __closure * TCallBackSR ) ( TSearchRec ) ;

private:
        TNotifyEvent FOnEOF   ;
        TNotifyEvent FOnBOF   ;
        TNotifyEvent FOnFail  ;
        TNotifyEvent FOnClose ;
        TNotifyEvent FOnOpen  ;

        AnsiString FFileName    ;
        int        FFileLength  ;
        int        FFmConst     ;
        int        FFileHandle  ;
        bool       FSuccess     ;
        AnsiString FPath        ;
        AnsiString FFilePattern ;
        bool       FAutoCreate  ;

        void __fastcall Open   ( ) ;
        void __fastcall SetFPath ( AnsiString ) ;

        void __fastcall     SetFileName ( AnsiString ) ;
        void __fastcall     SetFMConst  ( int ) ;

        bool __fastcall GetEOF ( ) ;
        bool __fastcall GetBOF ( ) ;

protected:
        virtual __fastcall ~TFileBase ( ) { Close ( ) ; } 
        void __fastcall Close  ( ) ; 
        void __fastcall Reset  ( ) ;

        static const AnsiString pathDelim ;

__published:
        __property TNotifyEvent OnBOF   = { read = FOnBOF    , write = FOnBOF   } ;
        __property TNotifyEvent OnEOF   = { read = FOnEOF    , write = FOnEOF   } ;
        __property TNotifyEvent OnFail  = { read = FOnFail   , write = FOnFail  } ;
        __property TNotifyEvent OnOpen  = { read = FOnOpen   , write = FOnOpen  } ;
        __property TNotifyEvent OnClose = { read = FOnClose  , write = FOnClose } ;

        __property bool BOF   = { read = GetBOF } ;
        __property bool EOF   = { read = GetEOF } ;

        __property AnsiString FileName      = { read = FFileName , write = SetFileName } ;
        __property int        FileOpenConst = { read = FFmConst  , write = SetFMConst  } ;

        __property bool Success             = { read = FSuccess    } ;
        __property int FileHandle           = { read = FFileHandle } ;
        __property AnsiString Path          = { read = FPath        , write = SetFPath     } ;
        __property AnsiString FilePattern   = { read = FFilePattern , write = FFilePattern } ;
        __property bool AutoCreate          = { read = FAutoCreate  , write = FAutoCreate  } ;

};
//---------------------------------------------------------------------------
#endif
 