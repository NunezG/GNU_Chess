#ifndef ANDROIDFILEINTERFACE_H
#define ANDROIDFILEINTERFACE_H

// ANDROID
#include <android/asset_manager.h>
#include <android/log.h>

// ROCKET
#include <Rocket/Core/FileInterface.h>

// STL
#include <map>


struct AndroidFilePointer
{
    AAsset* asset;
    int offset;
};

class AndroidFileInterface : public Rocket::Core::FileInterface
{
public:
    AndroidFileInterface(AAssetManager* assetMgr)
    {
        mAssetMgr = assetMgr;
    }

    // Opens a file.
    virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path)
    {

        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, (Rocket::Core::String("Rocket::Core::FileHandle Open: ") + path).CString());
        AAsset* asset = AAssetManager_open(mAssetMgr, path.CString(), AASSET_MODE_BUFFER);
        if(asset)
        {
            AndroidFilePointer* afp = new AndroidFilePointer();
            afp->asset = asset;
            afp->offset = 0;
            Rocket::Core::FileHandle membuf = (Rocket::Core::FileHandle) afp;
            return membuf;
        }
        return NULL;
    }

    // Closes a previously opened file.
    virtual void Close(Rocket::Core::FileHandle file)
    {

        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Rocket::Core::FileHandle Close");
        if(file)
        {
            AndroidFilePointer* afp = (AndroidFilePointer*) file;
            AAsset* asset = afp->asset;
            AAsset_close(asset);
            delete afp;
        }
    }

    // Reads data from a previously opened file.
    virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file) {

        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Rocket::Core::FileHandle Read %d ...", size);
        if(!file) return 0;
        AndroidFilePointer* afp = (AndroidFilePointer*) file;
        AAsset* asset = afp->asset;
        off_t length = AAsset_getLength(asset);
        char const* assetBuffer = (char*) AAsset_getBuffer(asset);
        if((afp->offset + size) <= length)
        {
            memcpy(buffer, assetBuffer + afp->offset, size);
            afp->offset += size;
            //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "... (afp->offset + size) <= length: read %d", size);
            return size;
        }
        else
        {
            int s = (length - afp->offset);
            memcpy(buffer, assetBuffer + afp->offset, s);
            afp->offset += s;
            //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "... (afp->offset + size) > length: read %d", s);
            return s;
        }
    }

    // Seeks to a point in a previously opened file.
    virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin) {

        AndroidFilePointer* afp = (AndroidFilePointer*) file;
        AAsset* asset = afp->asset;
        off_t length = AAsset_getLength(asset);

        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Rocket::Core::FileHandle Seek origin: %d offset %d, afp_offset %d...", origin, offset, afp->offset);

        if(SEEK_SET == origin)
        {
            off_t pointer = offset;
            //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "... SEEK_SET == origin %d", pointer);
            if(pointer > length)
                return false;
            if(pointer < 0)
                return false;

            afp->offset = pointer;
            return true;
        }
        else if(SEEK_CUR == origin)
        {
            off_t pointer = afp->offset + offset;
            //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "... SEEK_CUR == origin %d", pointer);
            if(pointer > length)
                return false;
            if(pointer < 0)
                return false;

            afp->offset = pointer;
            return true;
        }
        else
        {
            off_t pointer = length + offset;
            //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "... SEEK_END == origin %d", pointer);
            if(pointer > length)
                return false;
            if(pointer < 0)
                return false;

            afp->offset = pointer;
            return true;
        }
    }

    // Returns the current position of the file pointer.
    virtual size_t Tell(Rocket::Core::FileHandle file)
    {

        AndroidFilePointer* afp = (AndroidFilePointer*) file;
        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Rocket::Core::FileHandle Tell Offset %d", afp->offset);
        return afp->offset;
    }

private:
    AAssetManager* mAssetMgr;
};

#endif
