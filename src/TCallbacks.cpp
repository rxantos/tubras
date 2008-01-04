#include "tubras.h"

namespace Tubras
{

    int TEventCallback::Execute(TEvent Param) const
    {
        {
            if (pFunction) 
            {
                return (cInst->*pFunction)(Param);
            }
            else 
            {
                return 0;
            }
        }
    }

    class TMgr
    {
       
        std::list<TEventCallback*>   cbList;

    public:
        void addCallBack(TEventCallback* pcb)
        {
            cbList.push_back(pcb);
        }

        void test()
        {
            std::list<TEventCallback*>::iterator itr;

            itr = cbList.begin();
            TEvent e("test");

            int rc = (*itr)->Execute(e);
        
        }

    };

    TMgr mgr;

    class TTest : public TObject
    {
    TEventCallback*    pcb;

    public:

        int cb1(TEvent e)
        {
            return 0;
        }
        int initialize()
        {
            pcb = new TEventCallback(this,(TEventCallbackFunction)&TTest::cb1);

            //pcb->SetCallback(this,(TEventCallbackFunction)&TTest::cb1);

            mgr.addCallBack((TEventCallback*) pcb);
            return 0;
        }
    };


    void testCallBack()
    {
        TTest   test;
        test.initialize();
        mgr.test();
    }


}