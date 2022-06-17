//---------------------------------------------------------------------------

#ifndef FileCopyH
#define FileCopyH

#include "fileread.h"
//---------------------------------------------------------------------------

class PACKAGE TFileCopy : public TFileRead
{
        typedef TFileRead Inherited ;
        typedef TCallBack TLineChange ;
        typedef TCallBackSR TFileSR ;

private:
        TLineChange   FLineAlter ;
        TLineChange   FScanFile  ;
        TStringList * FFileList  ;
        AnsiString    FPattern   ;
        TFileSR       FListFile  ;
        TLineChange   FWriteFile ;

        void __fastcall SetCopy  ( ) ;
        void __fastcall FileScan ( ) ;
        void __fastcall ListFile ( ) ;
        void __fastcall DelFile  ( ) ;

        AnsiString FileRename    ( ) ;
        void FileLineCopy        ( ) ;
        void ScanFileAll         ( ) ;
        void WriteLine           ( ) ;

public:
        __fastcall TFileCopy ( TComponent * ) ;
        virtual __fastcall ~TFileCopy ( ) ;

        void FileRename ( AnsiString ) ;

__published:
        __property int Copy   = { read = SetCopy  } ;
        __property int Scan   = { read = FileScan } ;
        __property int List   = { read = ListFile } ;
        __property int Delete = { read = DelFile  } ;

        __property TLineChange LineAlter     = { read = FLineAlter , write = FLineAlter } ;
        __property TLineChange ScanFile      = { read = FScanFile  , write = FScanFile  } ;
        __property AnsiString  Pattern       = { read = FPattern   , write = FPattern   } ;
        __property TFileSR     ListFiles     = { read = FListFile  , write = FListFile  } ;
        __property TLineChange WriteFileCBF  = { read = FWriteFile , write = FWriteFile } ;
        __property TStringList * FileList    = { read = FFileList  , write = FFileList  } ;

} ;

#endif
