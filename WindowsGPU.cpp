/**
 * @file WindowsGPU.cpp
 * @brief Exports the NVIDIA and AMD high performance GPU flags for Windows.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

// TODO: when we implement the IPlatform paradigm, we should move this to the Windows specific class.

#if defined(_WIN32) || defined(_WIN64)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// NVIDIA
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

// AMD
extern "C" __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#endif
