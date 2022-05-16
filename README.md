# Houdini Integration Test

An attempt to integrate HDK to poke around.

## Building

First install required tools explained in [docs](https://www.sidefx.com/docs/hdk/_h_d_k__intro__getting_started.html#HDK_Intro_Compiling_Intro_Windows).
Brief version: `cmake`, `Microsoft Visual C++`. Also install `make`.

Run `make build` to generate build system in `/build` folder. Open `/build/Plugin.sln` that launches VS and build `ALL_BUILD` project.

## Troubleshooting

- Set `HOUDINI_DSO_ERROR` to 1-4 to see errors if plugins couldn't be loaded;
- set `MSVCDir` environment variable to the MSVC folder. MSVC version must be the one used to compile Houdini (see [docs, Windows section](https://www.sidefx.com/docs/hdk/_h_d_k__intro__getting_started.html)).
  Use `Visual Studio Installer` to install MSVC with that version (currently, last version is `vc142`);
- set `HOUDINI_VEX_DSO_PATH` to your plugins folder (on Windows, most likely - `C:\Users\{yourself}\Documents\houdini{version}\dso`);
- make sure that `ALL_BUILD` and other projects have `Platform Toolset` field set to the required version (`vc142` for example).