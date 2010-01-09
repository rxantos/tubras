//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TNULLSOUNDMANAGER_H_
#define _TNULLSOUNDMANAGER_H_

namespace Tubras
{
    class TNullSoundManager : public TSoundManager {

    public:
        TNullSoundManager();
        virtual ~TNullSoundManager();

        virtual bool isValid();

        virtual TSound* getSound(const TString& file_name, bool positional = false);
        virtual void uncacheSound(const TString&);
        virtual void clearCache();
        virtual void setCacheLimit(unsigned int);
        virtual unsigned int getCacheLimit() const;

        virtual void setVolume(float);
        virtual float getVolume() const;

        virtual void setplayRate(float);
        virtual float getplayRate() const;

        virtual void setActive(bool);
        virtual bool getActive() const;

        virtual void setConcurrentSoundLimit(unsigned int limit);
        virtual unsigned int getConcurrentSoundLimit() const;

        virtual void reduceSoundsPlayingTo(unsigned int count);

        virtual void stopAllSounds();

    };
}

#endif

