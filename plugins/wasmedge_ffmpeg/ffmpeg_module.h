// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2023 Second State INC

#pragma once

#include "ffmpeg_env.h"

#include "runtime/instance/module.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeFfmpegModule : public Runtime::Instance::ModuleInstance {
public:
  WasmEdgeFfmpegModule();

  WasmEdgeFfmpegEnvironmet &getEnv() { return Env; }

private:
  WasmEdgeFfmpegEnvironmet Env;
};

} // namespace Host
} // namespace WasmEdge
