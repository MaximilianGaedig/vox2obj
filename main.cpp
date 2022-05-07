#include "VoxReader.h"
#include "polygonize.h"
#include <iostream>
#include <napi.h>

static Napi::Value vox2obj(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "Expected exactly one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    // if (!info[0].IsArray()) {
    //     Napi::Error::New(info.Env(), "Expected an Array").ThrowAsJavaScriptException();
    //     return env.Undefined();
    // }

    Napi::Uint8Array buf = info[0].As<Napi::Uint8Array>(); // uint8_t*
    VoxReader reader;
    uint8_t* test = reinterpret_cast<uint8_t*>(buf.Data());
    reader.loadVoxelsData(test, buf.ByteLength());

    std::vector<VoxelGroup> meshList;

    polygonize(meshList, reader.getVoxelScene());
    std::string obj(returnOBJ(meshList[0]));
    return Napi::String::New(env, obj);
    return env.Undefined();
}

static Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["vox2obj"] = Napi::Function::New(env, vox2obj);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)