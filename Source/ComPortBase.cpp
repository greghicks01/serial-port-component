//---------------------------------------------------------------------------

#include <basepch.h>

#pragma hdrstop

#include "ComPortBase.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TComPortBase *)
{
        new TComPortBase(NULL);
}
//---------------------------------------------------------------------------
__fastcall TComPortBase::TComPortBase(TComponent* Owner)
        : TComponent(Owner)
{
}
//---------------------------------------------------------------------------
namespace Comportbase
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TComPortBase)};
                 RegisterComponents("GHComPort", classes, 0);
        }
}
//---------------------------------------------------------------------------
 