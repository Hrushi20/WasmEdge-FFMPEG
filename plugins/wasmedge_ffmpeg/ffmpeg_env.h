#pragma once

#include "plugin/plugin.h"
extern "C" {
    #include "libavformat/avformat.h"
}

namespace WasmEdge {
namespace Host {

class WasmEdgeFfmpegEnvironmet {
public:
    WasmEdgeFfmpegEnvironmet() noexcept;

    AVFormatContext* ctx;
    static Plugin::PluginRegister Register;

    // void setCtx(AVFormatContext** avFormatContext){
    //     ctx = *avFormatContext;
    // }

    AVFormatContext* getCtx(){
        return ctx;
    }

};
} // namespace Host
} // namespace WasmEdge