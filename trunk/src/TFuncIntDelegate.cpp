#include "tubras.h"

namespace Tubras
{

    void TFuncIntDelegate::Execute(double T, void* userData) const
    {
        {
            if (pFunction) 
            {
                (m_instance->*pFunction)(T,userData);
            }
        }
    }
}