//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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

