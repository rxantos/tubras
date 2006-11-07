#include "tubras.h"

namespace Tubras
{

    int TEventDelegate::Execute(TSEvent Param) const
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