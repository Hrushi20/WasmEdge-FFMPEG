// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2023 Second State INC

#include "ffmpeg_module.h"
#include "ffmpeg_func.h"

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

#include <memory>

namespace WasmEdge {
namespace Host {

WasmEdgeFfmpegModule::WasmEdgeFfmpegModule()
    : ModuleInstance("wasmedge_ffmpeg") {

    addHostFunc("wasmedge_ffmpeg_avformatAllocContext",
              std::make_unique<WasmEdgeFfmpegAvformatAllocContext>(Env));

    addHostFunc("wasmedge_ffmpeg_avformatOpenInput",
              std::make_unique<WasmEdgeFfmpegAvformatOpenInput>(Env));

    addHostFunc("wasmedge_ffmpeg_avformatFindStreamInfo",
              std::make_unique<WasmEdgeFfmpegAvformatFindStreamInfo>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecParameters",
              std::make_unique<WasmEdgeFfmpegAvCodecParameters>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecFindDecoder",
              std::make_unique<WasmEdgeFfmpegAvcodecFindDecoder>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecAllocContext3",
              std::make_unique<WasmEdgeFfmpegAvcodecAllocContext3>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecParametersToContext",
              std::make_unique<WasmEdgeFfmpegAvcodecParametersToContext>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecOpen2",
              std::make_unique<WasmEdgeFfmpegAvcodecOpen2>(Env));

    addHostFunc("wasmedge_ffmpeg_avFrameAlloc",
              std::make_unique<WasmEdgeFfmpegAvFrameAlloc>(Env));

    addHostFunc("wasmedge_ffmpeg_avPacketAlloc",
              std::make_unique<WasmEdgeFfmpegAvPacketAlloc>(Env));

    addHostFunc("wasmedge_ffmpeg_avReadFrame",
              std::make_unique<WasmEdgeFfmpegAvReadFrame>(Env));

    addHostFunc("wasmedge_ffmpeg_getStreamIndex",
              std::make_unique<WasmEdgeFfmpegGetStreamIndex>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecSendPacket",
              std::make_unique<WasmEdgeFfmpegAvcodecSendPacket>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecReceiveFrame",
              std::make_unique<WasmEdgeFfmpegAvcodecReceiveFrame>(Env));

    addHostFunc("wasmedge_ffmpeg_avPacketUnref",
              std::make_unique<WasmEdgeFfmpegAvPacketUnref>(Env));

    addHostFunc("wasmedge_ffmpeg_frameData",
              std::make_unique<WasmEdgeFfmpegFrameData>(Env));

    addHostFunc("wasmedge_ffmpeg_frameDimensions",
              std::make_unique<WasmEdgeFfmpegFrameDimension>(Env));

    addHostFunc("wasmedge_ffmpeg_avformatCloseInput",
              std::make_unique<WasmEdgeFfmpegAvformatCloseInput>(Env));

    addHostFunc("wasmedge_ffmpeg_avPacketFree",
              std::make_unique<WasmEdgeFfmpegAvPacketFree>(Env));

    addHostFunc("wasmedge_ffmpeg_avFrameFree",
              std::make_unique<WasmEdgeFfmpegAvFrameFree>(Env));

    addHostFunc("wasmedge_ffmpeg_avcodecFreeContext",
              std::make_unique<WasmEdgeFfmpegAvcodecFreeContext>(Env));
}

} // namespace Host
} // namespace WasmEdge
