namespace Tubras
{
    class TEvent;
    class TObject;


    typedef int (TObject::*TEventCallbackFunction)(TEvent Param);

    class TEventCallback 
    {
    public:
        TEventCallback()    
        {
            pFunction = 0;
        }

        TEventCallback(TObject* cInstancePointer,
            TEventCallbackFunction pFunctionPointer)    
        {
            cInst = cInstancePointer;
            pFunction = pFunctionPointer;
        }

        virtual int Execute(TEvent Param) const;

        void SetCallback (TObject  *cInstancePointer,
            TEventCallbackFunction   pFunctionPointer)
        {
            cInst     = cInstancePointer;
            pFunction = pFunctionPointer;
        }

    private:
        TObject   *cInst;
        TEventCallbackFunction  pFunction;
    };

    void testCallBack();
}