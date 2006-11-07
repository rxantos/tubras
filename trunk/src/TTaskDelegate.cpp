#include "tubras.h"

namespace Tubras
{

    int TTaskDelegate::Execute(TTask* Param) const
    {
        {
            if (pFunction) 
            {
                return (m_instance->*pFunction)(Param);
            }
            else 
            {
                return 0;
            }
        }
    }
}