#pragma once

#include "plugin/plugin.h"
extern "C" {
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
}

namespace WasmEdge {
namespace Host {

class WasmEdgeFfmpegEnvironmet {
public:
    WasmEdgeFfmpegEnvironmet() noexcept;

    std::vector<AVFormatContext*> avFormatContextArr;
    std::vector<AVCodecParameters* > avCodecParameters;
    std::vector<const AVCodec* > avCodec;
    std::vector<AVCodecContext* >codecCtx;
    std::vector<AVPacket* > packet;
    std::vector<AVFrame* > frame;

    static Plugin::PluginRegister Register;

    // void setCtx(AVFormatContext** avFormatContext){
    //     ctx = *avFormatContext;
    // }

};
} // namespace Host
} // namespace WasmEdge