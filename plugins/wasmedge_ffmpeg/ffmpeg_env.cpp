// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2023 Second State INC

#include "ffmpeg_env.h"
#include "ffmpeg_module.h"

namespace WasmEdge {
namespace Host {

WasmEdgeFfmpegEnvironmet::WasmEdgeFfmpegEnvironmet() noexcept {}

namespace {

Runtime::Instance::ModuleInstance *
create(const Plugin::PluginModule::ModuleDescriptor *) noexcept {
  return new WasmEdgeFfmpegModule();
}

Plugin::Plugin::PluginDescriptor Descriptor{
    .Name = "wasmedge_ffmpeg",
    .Description = "",
    .APIVersion = Plugin::Plugin::CurrentAPIVersion,
    .Version = {0, 1, 0, 0},
    .ModuleCount = 1,
    .ModuleDescriptions =
        (Plugin::PluginModule::ModuleDescriptor[]){
            {
                .Name = "wasmedge_ffmpeg",
                .Description = "",
                .Create = create,
            },
        },
    .AddOptions = nullptr,
};

} // namespace

Plugin::PluginRegister WasmEdgeFfmpegEnvironmet::Register(&Descriptor);

} // namespace Host
} // namespace WasmEdge
