//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "ComDataTree.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TComDataTree *)
{
        new TComDataTree(NULL);
}
//---------------------------------------------------------------------------
__fastcall TComDataTree::TComDataTree(TComponent* Owner)
        : TTreeView(Owner)
{
}
//---------------------------------------------------------------------------
namespace Comdatatree
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TComDataTree)};
                 RegisterComponents("GHComPort", classes, 0);
        }
}
//---------------------------------------------------------------------------
 