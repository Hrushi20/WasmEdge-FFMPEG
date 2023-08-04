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
  addHostFunc("wasmedge_ffmpeg_avFormatOpenInput",
              std::make_unique<WasmEdgeFfmpegAvFormatOpenInput>(Env));


}

} // namespace Host
} // namespace WasmEdge
