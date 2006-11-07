namespace Tubras
{
    class TEvent;
    class TObject;
    typedef Ogre::SharedPtr<TEvent> TSEvent;


    typedef int (TObject::*TEventDelegateFunction)(TSEvent Param);

    class TEventDelegate : public TDelegate
    {
    protected:
        TEventDelegateFunction  pFunction;

    public:
        TEventDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TEventDelegate(TObject* instance,
            TEventDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(TSEvent Param) const;

        void SetCallback (TObject  *instance,
            TEventDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}