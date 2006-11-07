namespace Tubras
{
    class TTask;
    class TObject;


    typedef int (TObject::*TTaskDelegateFunction)(TTask* Param);

    class TTaskDelegate : public TDelegate
    {
    protected:
        TTaskDelegateFunction  pFunction;

    public:
        TTaskDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TTaskDelegate(TObject* instance,
            TTaskDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(TTask* Param) const;

        void SetCallback (TObject  *instance,
            TTaskDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}