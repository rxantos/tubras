namespace Tubras
{
    class TObject;


    typedef void (TObject::*TFuncIntDelegateFunction)(double T, void* userData);

    class TFuncIntDelegate : public TDelegate
    {
    protected:
        TFuncIntDelegateFunction  pFunction;

    public:
        TFuncIntDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TFuncIntDelegate(TObject* instance,
            TFuncIntDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual void Execute(double T, void* userData) const;

        void SetCallback (TObject  *instance,
            TFuncIntDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}