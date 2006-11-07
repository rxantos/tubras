namespace Tubras
{
    class TObject;

    class TDelegate
    {
    protected:
        TObject*            m_instance;
        int                 m_priority;
        bool                m_enabled;


    public:
        TDelegate(TObject* instance) : m_instance(instance), m_priority(0), m_enabled(true) {};

        int getPriority() {return m_priority;};
        void setPriority(int value) {m_priority = value;};
        bool getEnabled() {return m_enabled;};
        void setEnabled(bool value) {m_enabled = value;};

        void* getInstance() {return m_instance;};
    };

}