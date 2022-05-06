#include "VoxReader.h"
#include "polygonize.h"
#include <napi.h>

static Napi::Value vox2obj(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "Expected exactly one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[0].IsArrayBuffer()) {
        Napi::Error::New(info.Env(), "Expected an ArrayBuffer").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();

    VoxReader reader;
    reader.loadVoxelsData(reinterpret_cast<uint8_t*>(buf.Data()), buf.ByteLength() / sizeof(int8_t));

    std::vector<VoxelGroup> meshList;

    polygonize(meshList, reader.getVoxelScene());
    std::string obj(returnOBJ(meshList[0]));
    return Napi::String::New(env, obj);
}

static Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["vox2obj"] = Napi::Function::New(env, vox2obj);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)