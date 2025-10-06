// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See loader_extension_generator.py for modifications

/*
 * Copyright (c) 2015-2025 The Khronos Group Inc.
 * Copyright (c) 2015-2025 Valve Corporation
 * Copyright (c) 2015-2025 LunarG, Inc.
 * Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * Copyright (c) 2023-2023 RasterGrid Kft.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Mark Young <marky@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

// clang-format off
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "vk_loader_extensions.h"
#include <vulkan/vk_icd.h>
#include "wsi.h"
#include "debug_utils.h"
#include "extension_manual.h"
#include "vk_command_name_hashes.h"
#include "vk_extension_name_hashes.h"

// Device extension error function
VKAPI_ATTR VkResult VKAPI_CALL vkDevExtError(VkDevice dev) {
    struct loader_device *found_dev;
    // The device going in is a trampoline device
    struct loader_icd_term *icd_term = loader_get_icd_and_device(dev, &found_dev);

    if (icd_term)
        loader_log(icd_term->this_instance, VULKAN_LOADER_ERROR_BIT, 0,
                   "Bad destination in loader trampoline dispatch,"
                   "Are layers and extensions that you are calling enabled?");
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

VKAPI_ATTR bool VKAPI_CALL loader_icd_init_entries(struct loader_instance* inst, struct loader_icd_term *icd_term) {
    const PFN_vkGetInstanceProcAddr fp_gipa = icd_term->scanned_icd->GetInstanceProcAddr;

#define LOOKUP_GIPA(func) icd_term->dispatch.func = (PFN_vk##func)fp_gipa(icd_term->instance, "vk" #func);

#define LOOKUP_REQUIRED_GIPA(func)                                                      \
    do {                                                                                \
        LOOKUP_GIPA(func);                                                              \
        if (!icd_term->dispatch.func) {                                                 \
            loader_log(inst, VULKAN_LOADER_WARN_BIT, 0, "Unable to load %s from ICD %s",\
                       "vk"#func, icd_term->scanned_icd->lib_name);                     \
            return false;                                                               \
        }                                                                               \
    } while (0)


    // ---- Core Vulkan 1.0
    LOOKUP_REQUIRED_GIPA(DestroyInstance);
    LOOKUP_REQUIRED_GIPA(EnumeratePhysicalDevices);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceFeatures);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceFormatProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceImageFormatProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceQueueFamilyProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceMemoryProperties);
    LOOKUP_REQUIRED_GIPA(GetDeviceProcAddr);
    LOOKUP_REQUIRED_GIPA(CreateDevice);
    LOOKUP_REQUIRED_GIPA(EnumerateDeviceExtensionProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceSparseImageFormatProperties);

    // ---- Core Vulkan 1.1
    LOOKUP_GIPA(EnumeratePhysicalDeviceGroups);
    LOOKUP_GIPA(GetPhysicalDeviceFeatures2);
    LOOKUP_GIPA(GetPhysicalDeviceProperties2);
    LOOKUP_GIPA(GetPhysicalDeviceFormatProperties2);
    LOOKUP_GIPA(GetPhysicalDeviceImageFormatProperties2);
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyProperties2);
    LOOKUP_GIPA(GetPhysicalDeviceMemoryProperties2);
    LOOKUP_GIPA(GetPhysicalDeviceSparseImageFormatProperties2);
    LOOKUP_GIPA(GetPhysicalDeviceExternalBufferProperties);
    LOOKUP_GIPA(GetPhysicalDeviceExternalFenceProperties);
    LOOKUP_GIPA(GetPhysicalDeviceExternalSemaphoreProperties);

    // ---- Core Vulkan 1.3
    LOOKUP_GIPA(GetPhysicalDeviceToolProperties);

    // ---- VK_KHR_surface extension commands
    LOOKUP_GIPA(DestroySurfaceKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceSupportKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceCapabilitiesKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceFormatsKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfacePresentModesKHR);

    // ---- VK_KHR_swapchain extension commands
    LOOKUP_GIPA(GetPhysicalDevicePresentRectanglesKHR);

    // ---- VK_KHR_display extension commands
    LOOKUP_GIPA(GetPhysicalDeviceDisplayPropertiesKHR);
    LOOKUP_GIPA(GetPhysicalDeviceDisplayPlanePropertiesKHR);
    LOOKUP_GIPA(GetDisplayPlaneSupportedDisplaysKHR);
    LOOKUP_GIPA(GetDisplayModePropertiesKHR);
    LOOKUP_GIPA(CreateDisplayModeKHR);
    LOOKUP_GIPA(GetDisplayPlaneCapabilitiesKHR);
    LOOKUP_GIPA(CreateDisplayPlaneSurfaceKHR);

    // ---- VK_KHR_xlib_surface extension commands
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    LOOKUP_GIPA(CreateXlibSurfaceKHR);
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    LOOKUP_GIPA(GetPhysicalDeviceXlibPresentationSupportKHR);
#endif // VK_USE_PLATFORM_XLIB_KHR

    // ---- VK_KHR_xcb_surface extension commands
#if defined(VK_USE_PLATFORM_XCB_KHR)
    LOOKUP_GIPA(CreateXcbSurfaceKHR);
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    LOOKUP_GIPA(GetPhysicalDeviceXcbPresentationSupportKHR);
#endif // VK_USE_PLATFORM_XCB_KHR

    // ---- VK_KHR_wayland_surface extension commands
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    LOOKUP_GIPA(CreateWaylandSurfaceKHR);
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    LOOKUP_GIPA(GetPhysicalDeviceWaylandPresentationSupportKHR);
#endif // VK_USE_PLATFORM_WAYLAND_KHR

    // ---- VK_KHR_android_surface extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    LOOKUP_GIPA(CreateAndroidSurfaceKHR);
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_KHR_win32_surface extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(CreateWin32SurfaceKHR);
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(GetPhysicalDeviceWin32PresentationSupportKHR);
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_video_queue extension commands
    LOOKUP_GIPA(GetPhysicalDeviceVideoCapabilitiesKHR);
    LOOKUP_GIPA(GetPhysicalDeviceVideoFormatPropertiesKHR);

    // ---- VK_KHR_get_physical_device_properties2 extension commands
    LOOKUP_GIPA(GetPhysicalDeviceFeatures2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceFormatProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceImageFormatProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceMemoryProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceSparseImageFormatProperties2KHR);

    // ---- VK_KHR_device_group_creation extension commands
    LOOKUP_GIPA(EnumeratePhysicalDeviceGroupsKHR);

    // ---- VK_KHR_external_memory_capabilities extension commands
    LOOKUP_GIPA(GetPhysicalDeviceExternalBufferPropertiesKHR);

    // ---- VK_KHR_external_semaphore_capabilities extension commands
    LOOKUP_GIPA(GetPhysicalDeviceExternalSemaphorePropertiesKHR);

    // ---- VK_KHR_external_fence_capabilities extension commands
    LOOKUP_GIPA(GetPhysicalDeviceExternalFencePropertiesKHR);

    // ---- VK_KHR_performance_query extension commands
    LOOKUP_GIPA(EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceCapabilities2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceFormats2KHR);

    // ---- VK_KHR_get_display_properties2 extension commands
    LOOKUP_GIPA(GetPhysicalDeviceDisplayProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceDisplayPlaneProperties2KHR);
    LOOKUP_GIPA(GetDisplayModeProperties2KHR);
    LOOKUP_GIPA(GetDisplayPlaneCapabilities2KHR);

    // ---- VK_KHR_fragment_shading_rate extension commands
    LOOKUP_GIPA(GetPhysicalDeviceFragmentShadingRatesKHR);

    // ---- VK_KHR_video_encode_queue extension commands
    LOOKUP_GIPA(GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR);

    // ---- VK_KHR_cooperative_matrix extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCooperativeMatrixPropertiesKHR);

    // ---- VK_KHR_calibrated_timestamps extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCalibrateableTimeDomainsKHR);

    // ---- VK_EXT_debug_report extension commands
    LOOKUP_GIPA(CreateDebugReportCallbackEXT);
    LOOKUP_GIPA(DestroyDebugReportCallbackEXT);
    LOOKUP_GIPA(DebugReportMessageEXT);

    // ---- VK_GGP_stream_descriptor_surface extension commands
#if defined(VK_USE_PLATFORM_GGP)
    LOOKUP_GIPA(CreateStreamDescriptorSurfaceGGP);
#endif // VK_USE_PLATFORM_GGP

    // ---- VK_NV_external_memory_capabilities extension commands
    LOOKUP_GIPA(GetPhysicalDeviceExternalImageFormatPropertiesNV);

    // ---- VK_NN_vi_surface extension commands
#if defined(VK_USE_PLATFORM_VI_NN)
    LOOKUP_GIPA(CreateViSurfaceNN);
#endif // VK_USE_PLATFORM_VI_NN

    // ---- VK_EXT_direct_mode_display extension commands
    LOOKUP_GIPA(ReleaseDisplayEXT);

    // ---- VK_EXT_acquire_xlib_display extension commands
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    LOOKUP_GIPA(AcquireXlibDisplayEXT);
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    LOOKUP_GIPA(GetRandROutputDisplayEXT);
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT

    // ---- VK_EXT_display_surface_counter extension commands
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceCapabilities2EXT);

    // ---- VK_MVK_ios_surface extension commands
#if defined(VK_USE_PLATFORM_IOS_MVK)
    LOOKUP_GIPA(CreateIOSSurfaceMVK);
#endif // VK_USE_PLATFORM_IOS_MVK

    // ---- VK_MVK_macos_surface extension commands
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    LOOKUP_GIPA(CreateMacOSSurfaceMVK);
#endif // VK_USE_PLATFORM_MACOS_MVK

    // ---- VK_EXT_debug_utils extension commands
    LOOKUP_GIPA(CreateDebugUtilsMessengerEXT);
    LOOKUP_GIPA(DestroyDebugUtilsMessengerEXT);
    LOOKUP_GIPA(SubmitDebugUtilsMessageEXT);

    // ---- VK_EXT_descriptor_heap extension commands
    LOOKUP_GIPA(GetPhysicalDeviceDescriptorSizeEXT);

    // ---- VK_EXT_sample_locations extension commands
    LOOKUP_GIPA(GetPhysicalDeviceMultisamplePropertiesEXT);

    // ---- VK_EXT_calibrated_timestamps extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCalibrateableTimeDomainsEXT);

    // ---- VK_FUCHSIA_imagepipe_surface extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    LOOKUP_GIPA(CreateImagePipeSurfaceFUCHSIA);
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_EXT_metal_surface extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    LOOKUP_GIPA(CreateMetalSurfaceEXT);
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_tooling_info extension commands
    LOOKUP_GIPA(GetPhysicalDeviceToolPropertiesEXT);

    // ---- VK_NV_cooperative_matrix extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCooperativeMatrixPropertiesNV);

    // ---- VK_NV_coverage_reduction_mode extension commands
    LOOKUP_GIPA(GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV);

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(GetPhysicalDeviceSurfacePresentModes2EXT);
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_headless_surface extension commands
    LOOKUP_GIPA(CreateHeadlessSurfaceEXT);

    // ---- VK_EXT_acquire_drm_display extension commands
    LOOKUP_GIPA(AcquireDrmDisplayEXT);
    LOOKUP_GIPA(GetDrmDisplayEXT);

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(AcquireWinrtDisplayNV);
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(GetWinrtDisplayNV);
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_directfb_surface extension commands
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    LOOKUP_GIPA(CreateDirectFBSurfaceEXT);
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    LOOKUP_GIPA(GetPhysicalDeviceDirectFBPresentationSupportEXT);
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

    // ---- VK_QNX_screen_surface extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    LOOKUP_GIPA(CreateScreenSurfaceQNX);
#endif // VK_USE_PLATFORM_SCREEN_QNX
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    LOOKUP_GIPA(GetPhysicalDeviceScreenPresentationSupportQNX);
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_ARM_tensors extension commands
    LOOKUP_GIPA(GetPhysicalDeviceExternalTensorPropertiesARM);

    // ---- VK_NV_optical_flow extension commands
    LOOKUP_GIPA(GetPhysicalDeviceOpticalFlowImageFormatsNV);

    // ---- VK_NV_cooperative_vector extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCooperativeVectorPropertiesNV);

    // ---- VK_ARM_data_graph extension commands
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM);
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM);

    // ---- VK_ARM_data_graph_instruction_set_tosa extension commands
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM);

    // ---- VK_OHOS_surface extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    LOOKUP_GIPA(CreateSurfaceOHOS);
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_NV_cooperative_matrix2 extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV);

    // ---- VK_ARM_performance_counters_by_region extension commands
    LOOKUP_GIPA(EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM);

    // ---- VK_ARM_shader_instrumentation extension commands
    LOOKUP_GIPA(EnumeratePhysicalDeviceShaderInstrumentationMetricsARM);

    // ---- VK_ARM_data_graph_optical_flow extension commands
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM);

    // ---- VK_SEC_ubm_surface extension commands
#if defined(VK_USE_PLATFORM_UBM_SEC)
    LOOKUP_GIPA(CreateUbmSurfaceSEC);
#endif // VK_USE_PLATFORM_UBM_SEC
#if defined(VK_USE_PLATFORM_UBM_SEC)
    LOOKUP_GIPA(GetPhysicalDeviceUbmPresentationSupportSEC);
#endif // VK_USE_PLATFORM_UBM_SEC

#undef LOOKUP_REQUIRED_GIPA
#undef LOOKUP_GIPA

    return true;
};

// Init Device function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_device_dispatch_table(struct loader_dev_dispatch_table *dev_table, PFN_vkGetDeviceProcAddr gpa,
                                                             VkDevice dev) {
    VkLayerDispatchTable *table = &dev_table->core_dispatch;
    if (table->magic != DEVICE_DISP_TABLE_MAGIC_NUMBER) { abort(); }
    for (uint32_t i = 0; i < MAX_NUM_UNKNOWN_EXTS; i++) dev_table->ext_dispatch[i] = (PFN_vkDevExt)vkDevExtError;

    // ---- Core Vulkan 1.0 commands
    table->GetDeviceProcAddr = gpa;
    table->DestroyDevice = (PFN_vkDestroyDevice)gpa(dev, "vkDestroyDevice");
    table->GetDeviceQueue = (PFN_vkGetDeviceQueue)gpa(dev, "vkGetDeviceQueue");
    table->QueueSubmit = (PFN_vkQueueSubmit)gpa(dev, "vkQueueSubmit");
    table->QueueWaitIdle = (PFN_vkQueueWaitIdle)gpa(dev, "vkQueueWaitIdle");
    table->DeviceWaitIdle = (PFN_vkDeviceWaitIdle)gpa(dev, "vkDeviceWaitIdle");
    table->AllocateMemory = (PFN_vkAllocateMemory)gpa(dev, "vkAllocateMemory");
    table->FreeMemory = (PFN_vkFreeMemory)gpa(dev, "vkFreeMemory");
    table->MapMemory = (PFN_vkMapMemory)gpa(dev, "vkMapMemory");
    table->UnmapMemory = (PFN_vkUnmapMemory)gpa(dev, "vkUnmapMemory");
    table->FlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)gpa(dev, "vkFlushMappedMemoryRanges");
    table->InvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)gpa(dev, "vkInvalidateMappedMemoryRanges");
    table->GetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)gpa(dev, "vkGetDeviceMemoryCommitment");
    table->BindBufferMemory = (PFN_vkBindBufferMemory)gpa(dev, "vkBindBufferMemory");
    table->BindImageMemory = (PFN_vkBindImageMemory)gpa(dev, "vkBindImageMemory");
    table->GetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)gpa(dev, "vkGetBufferMemoryRequirements");
    table->GetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)gpa(dev, "vkGetImageMemoryRequirements");
    table->GetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements)gpa(dev, "vkGetImageSparseMemoryRequirements");
    table->QueueBindSparse = (PFN_vkQueueBindSparse)gpa(dev, "vkQueueBindSparse");
    table->CreateFence = (PFN_vkCreateFence)gpa(dev, "vkCreateFence");
    table->DestroyFence = (PFN_vkDestroyFence)gpa(dev, "vkDestroyFence");
    table->ResetFences = (PFN_vkResetFences)gpa(dev, "vkResetFences");
    table->GetFenceStatus = (PFN_vkGetFenceStatus)gpa(dev, "vkGetFenceStatus");
    table->WaitForFences = (PFN_vkWaitForFences)gpa(dev, "vkWaitForFences");
    table->CreateSemaphore = (PFN_vkCreateSemaphore)gpa(dev, "vkCreateSemaphore");
    table->DestroySemaphore = (PFN_vkDestroySemaphore)gpa(dev, "vkDestroySemaphore");
    table->CreateQueryPool = (PFN_vkCreateQueryPool)gpa(dev, "vkCreateQueryPool");
    table->DestroyQueryPool = (PFN_vkDestroyQueryPool)gpa(dev, "vkDestroyQueryPool");
    table->GetQueryPoolResults = (PFN_vkGetQueryPoolResults)gpa(dev, "vkGetQueryPoolResults");
    table->CreateBuffer = (PFN_vkCreateBuffer)gpa(dev, "vkCreateBuffer");
    table->DestroyBuffer = (PFN_vkDestroyBuffer)gpa(dev, "vkDestroyBuffer");
    table->CreateImage = (PFN_vkCreateImage)gpa(dev, "vkCreateImage");
    table->DestroyImage = (PFN_vkDestroyImage)gpa(dev, "vkDestroyImage");
    table->GetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)gpa(dev, "vkGetImageSubresourceLayout");
    table->CreateImageView = (PFN_vkCreateImageView)gpa(dev, "vkCreateImageView");
    table->DestroyImageView = (PFN_vkDestroyImageView)gpa(dev, "vkDestroyImageView");
    table->CreateCommandPool = (PFN_vkCreateCommandPool)gpa(dev, "vkCreateCommandPool");
    table->DestroyCommandPool = (PFN_vkDestroyCommandPool)gpa(dev, "vkDestroyCommandPool");
    table->ResetCommandPool = (PFN_vkResetCommandPool)gpa(dev, "vkResetCommandPool");
    table->AllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)gpa(dev, "vkAllocateCommandBuffers");
    table->FreeCommandBuffers = (PFN_vkFreeCommandBuffers)gpa(dev, "vkFreeCommandBuffers");
    table->BeginCommandBuffer = (PFN_vkBeginCommandBuffer)gpa(dev, "vkBeginCommandBuffer");
    table->EndCommandBuffer = (PFN_vkEndCommandBuffer)gpa(dev, "vkEndCommandBuffer");
    table->ResetCommandBuffer = (PFN_vkResetCommandBuffer)gpa(dev, "vkResetCommandBuffer");
    table->CmdCopyBuffer = (PFN_vkCmdCopyBuffer)gpa(dev, "vkCmdCopyBuffer");
    table->CmdCopyImage = (PFN_vkCmdCopyImage)gpa(dev, "vkCmdCopyImage");
    table->CmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)gpa(dev, "vkCmdCopyBufferToImage");
    table->CmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)gpa(dev, "vkCmdCopyImageToBuffer");
    table->CmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)gpa(dev, "vkCmdUpdateBuffer");
    table->CmdFillBuffer = (PFN_vkCmdFillBuffer)gpa(dev, "vkCmdFillBuffer");
    table->CmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)gpa(dev, "vkCmdPipelineBarrier");
    table->CmdBeginQuery = (PFN_vkCmdBeginQuery)gpa(dev, "vkCmdBeginQuery");
    table->CmdEndQuery = (PFN_vkCmdEndQuery)gpa(dev, "vkCmdEndQuery");
    table->CmdResetQueryPool = (PFN_vkCmdResetQueryPool)gpa(dev, "vkCmdResetQueryPool");
    table->CmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)gpa(dev, "vkCmdWriteTimestamp");
    table->CmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)gpa(dev, "vkCmdCopyQueryPoolResults");
    table->CmdExecuteCommands = (PFN_vkCmdExecuteCommands)gpa(dev, "vkCmdExecuteCommands");
    table->CreateEvent = (PFN_vkCreateEvent)gpa(dev, "vkCreateEvent");
    table->DestroyEvent = (PFN_vkDestroyEvent)gpa(dev, "vkDestroyEvent");
    table->GetEventStatus = (PFN_vkGetEventStatus)gpa(dev, "vkGetEventStatus");
    table->SetEvent = (PFN_vkSetEvent)gpa(dev, "vkSetEvent");
    table->ResetEvent = (PFN_vkResetEvent)gpa(dev, "vkResetEvent");
    table->CreateBufferView = (PFN_vkCreateBufferView)gpa(dev, "vkCreateBufferView");
    table->DestroyBufferView = (PFN_vkDestroyBufferView)gpa(dev, "vkDestroyBufferView");
    table->CreateShaderModule = (PFN_vkCreateShaderModule)gpa(dev, "vkCreateShaderModule");
    table->DestroyShaderModule = (PFN_vkDestroyShaderModule)gpa(dev, "vkDestroyShaderModule");
    table->CreatePipelineCache = (PFN_vkCreatePipelineCache)gpa(dev, "vkCreatePipelineCache");
    table->DestroyPipelineCache = (PFN_vkDestroyPipelineCache)gpa(dev, "vkDestroyPipelineCache");
    table->GetPipelineCacheData = (PFN_vkGetPipelineCacheData)gpa(dev, "vkGetPipelineCacheData");
    table->MergePipelineCaches = (PFN_vkMergePipelineCaches)gpa(dev, "vkMergePipelineCaches");
    table->CreateComputePipelines = (PFN_vkCreateComputePipelines)gpa(dev, "vkCreateComputePipelines");
    table->DestroyPipeline = (PFN_vkDestroyPipeline)gpa(dev, "vkDestroyPipeline");
    table->CreatePipelineLayout = (PFN_vkCreatePipelineLayout)gpa(dev, "vkCreatePipelineLayout");
    table->DestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)gpa(dev, "vkDestroyPipelineLayout");
    table->CreateSampler = (PFN_vkCreateSampler)gpa(dev, "vkCreateSampler");
    table->DestroySampler = (PFN_vkDestroySampler)gpa(dev, "vkDestroySampler");
    table->CreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)gpa(dev, "vkCreateDescriptorSetLayout");
    table->DestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)gpa(dev, "vkDestroyDescriptorSetLayout");
    table->CreateDescriptorPool = (PFN_vkCreateDescriptorPool)gpa(dev, "vkCreateDescriptorPool");
    table->DestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)gpa(dev, "vkDestroyDescriptorPool");
    table->ResetDescriptorPool = (PFN_vkResetDescriptorPool)gpa(dev, "vkResetDescriptorPool");
    table->AllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)gpa(dev, "vkAllocateDescriptorSets");
    table->FreeDescriptorSets = (PFN_vkFreeDescriptorSets)gpa(dev, "vkFreeDescriptorSets");
    table->UpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)gpa(dev, "vkUpdateDescriptorSets");
    table->CmdBindPipeline = (PFN_vkCmdBindPipeline)gpa(dev, "vkCmdBindPipeline");
    table->CmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)gpa(dev, "vkCmdBindDescriptorSets");
    table->CmdClearColorImage = (PFN_vkCmdClearColorImage)gpa(dev, "vkCmdClearColorImage");
    table->CmdDispatch = (PFN_vkCmdDispatch)gpa(dev, "vkCmdDispatch");
    table->CmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)gpa(dev, "vkCmdDispatchIndirect");
    table->CmdSetEvent = (PFN_vkCmdSetEvent)gpa(dev, "vkCmdSetEvent");
    table->CmdResetEvent = (PFN_vkCmdResetEvent)gpa(dev, "vkCmdResetEvent");
    table->CmdWaitEvents = (PFN_vkCmdWaitEvents)gpa(dev, "vkCmdWaitEvents");
    table->CmdPushConstants = (PFN_vkCmdPushConstants)gpa(dev, "vkCmdPushConstants");
    table->CreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)gpa(dev, "vkCreateGraphicsPipelines");
    table->CreateFramebuffer = (PFN_vkCreateFramebuffer)gpa(dev, "vkCreateFramebuffer");
    table->DestroyFramebuffer = (PFN_vkDestroyFramebuffer)gpa(dev, "vkDestroyFramebuffer");
    table->CreateRenderPass = (PFN_vkCreateRenderPass)gpa(dev, "vkCreateRenderPass");
    table->DestroyRenderPass = (PFN_vkDestroyRenderPass)gpa(dev, "vkDestroyRenderPass");
    table->GetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)gpa(dev, "vkGetRenderAreaGranularity");
    table->CmdSetViewport = (PFN_vkCmdSetViewport)gpa(dev, "vkCmdSetViewport");
    table->CmdSetScissor = (PFN_vkCmdSetScissor)gpa(dev, "vkCmdSetScissor");
    table->CmdSetLineWidth = (PFN_vkCmdSetLineWidth)gpa(dev, "vkCmdSetLineWidth");
    table->CmdSetDepthBias = (PFN_vkCmdSetDepthBias)gpa(dev, "vkCmdSetDepthBias");
    table->CmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)gpa(dev, "vkCmdSetBlendConstants");
    table->CmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)gpa(dev, "vkCmdSetDepthBounds");
    table->CmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)gpa(dev, "vkCmdSetStencilCompareMask");
    table->CmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)gpa(dev, "vkCmdSetStencilWriteMask");
    table->CmdSetStencilReference = (PFN_vkCmdSetStencilReference)gpa(dev, "vkCmdSetStencilReference");
    table->CmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)gpa(dev, "vkCmdBindIndexBuffer");
    table->CmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)gpa(dev, "vkCmdBindVertexBuffers");
    table->CmdDraw = (PFN_vkCmdDraw)gpa(dev, "vkCmdDraw");
    table->CmdDrawIndexed = (PFN_vkCmdDrawIndexed)gpa(dev, "vkCmdDrawIndexed");
    table->CmdDrawIndirect = (PFN_vkCmdDrawIndirect)gpa(dev, "vkCmdDrawIndirect");
    table->CmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)gpa(dev, "vkCmdDrawIndexedIndirect");
    table->CmdBlitImage = (PFN_vkCmdBlitImage)gpa(dev, "vkCmdBlitImage");
    table->CmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)gpa(dev, "vkCmdClearDepthStencilImage");
    table->CmdClearAttachments = (PFN_vkCmdClearAttachments)gpa(dev, "vkCmdClearAttachments");
    table->CmdResolveImage = (PFN_vkCmdResolveImage)gpa(dev, "vkCmdResolveImage");
    table->CmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)gpa(dev, "vkCmdBeginRenderPass");
    table->CmdNextSubpass = (PFN_vkCmdNextSubpass)gpa(dev, "vkCmdNextSubpass");
    table->CmdEndRenderPass = (PFN_vkCmdEndRenderPass)gpa(dev, "vkCmdEndRenderPass");

    // ---- Core Vulkan 1.1 commands
    table->BindBufferMemory2 = (PFN_vkBindBufferMemory2)gpa(dev, "vkBindBufferMemory2");
    table->BindImageMemory2 = (PFN_vkBindImageMemory2)gpa(dev, "vkBindImageMemory2");
    table->GetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)gpa(dev, "vkGetDeviceGroupPeerMemoryFeatures");
    table->CmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)gpa(dev, "vkCmdSetDeviceMask");
    table->GetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)gpa(dev, "vkGetImageMemoryRequirements2");
    table->GetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)gpa(dev, "vkGetBufferMemoryRequirements2");
    table->GetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)gpa(dev, "vkGetImageSparseMemoryRequirements2");
    table->TrimCommandPool = (PFN_vkTrimCommandPool)gpa(dev, "vkTrimCommandPool");
    table->GetDeviceQueue2 = (PFN_vkGetDeviceQueue2)gpa(dev, "vkGetDeviceQueue2");
    table->CmdDispatchBase = (PFN_vkCmdDispatchBase)gpa(dev, "vkCmdDispatchBase");
    table->CreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)gpa(dev, "vkCreateDescriptorUpdateTemplate");
    table->DestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)gpa(dev, "vkDestroyDescriptorUpdateTemplate");
    table->UpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)gpa(dev, "vkUpdateDescriptorSetWithTemplate");
    table->GetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)gpa(dev, "vkGetDescriptorSetLayoutSupport");
    table->CreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)gpa(dev, "vkCreateSamplerYcbcrConversion");
    table->DestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)gpa(dev, "vkDestroySamplerYcbcrConversion");

    // ---- Core Vulkan 1.2 commands
    table->ResetQueryPool = (PFN_vkResetQueryPool)gpa(dev, "vkResetQueryPool");
    table->GetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)gpa(dev, "vkGetSemaphoreCounterValue");
    table->WaitSemaphores = (PFN_vkWaitSemaphores)gpa(dev, "vkWaitSemaphores");
    table->SignalSemaphore = (PFN_vkSignalSemaphore)gpa(dev, "vkSignalSemaphore");
    table->GetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)gpa(dev, "vkGetBufferDeviceAddress");
    table->GetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)gpa(dev, "vkGetBufferOpaqueCaptureAddress");
    table->GetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)gpa(dev, "vkGetDeviceMemoryOpaqueCaptureAddress");
    table->CmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)gpa(dev, "vkCmdDrawIndirectCount");
    table->CmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)gpa(dev, "vkCmdDrawIndexedIndirectCount");
    table->CreateRenderPass2 = (PFN_vkCreateRenderPass2)gpa(dev, "vkCreateRenderPass2");
    table->CmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)gpa(dev, "vkCmdBeginRenderPass2");
    table->CmdNextSubpass2 = (PFN_vkCmdNextSubpass2)gpa(dev, "vkCmdNextSubpass2");
    table->CmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)gpa(dev, "vkCmdEndRenderPass2");

    // ---- Core Vulkan 1.3 commands
    table->CreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)gpa(dev, "vkCreatePrivateDataSlot");
    table->DestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)gpa(dev, "vkDestroyPrivateDataSlot");
    table->SetPrivateData = (PFN_vkSetPrivateData)gpa(dev, "vkSetPrivateData");
    table->GetPrivateData = (PFN_vkGetPrivateData)gpa(dev, "vkGetPrivateData");
    table->CmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)gpa(dev, "vkCmdPipelineBarrier2");
    table->CmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)gpa(dev, "vkCmdWriteTimestamp2");
    table->QueueSubmit2 = (PFN_vkQueueSubmit2)gpa(dev, "vkQueueSubmit2");
    table->CmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)gpa(dev, "vkCmdCopyBuffer2");
    table->CmdCopyImage2 = (PFN_vkCmdCopyImage2)gpa(dev, "vkCmdCopyImage2");
    table->CmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)gpa(dev, "vkCmdCopyBufferToImage2");
    table->CmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)gpa(dev, "vkCmdCopyImageToBuffer2");
    table->GetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)gpa(dev, "vkGetDeviceBufferMemoryRequirements");
    table->GetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)gpa(dev, "vkGetDeviceImageMemoryRequirements");
    table->GetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)gpa(dev, "vkGetDeviceImageSparseMemoryRequirements");
    table->CmdSetEvent2 = (PFN_vkCmdSetEvent2)gpa(dev, "vkCmdSetEvent2");
    table->CmdResetEvent2 = (PFN_vkCmdResetEvent2)gpa(dev, "vkCmdResetEvent2");
    table->CmdWaitEvents2 = (PFN_vkCmdWaitEvents2)gpa(dev, "vkCmdWaitEvents2");
    table->CmdBlitImage2 = (PFN_vkCmdBlitImage2)gpa(dev, "vkCmdBlitImage2");
    table->CmdResolveImage2 = (PFN_vkCmdResolveImage2)gpa(dev, "vkCmdResolveImage2");
    table->CmdBeginRendering = (PFN_vkCmdBeginRendering)gpa(dev, "vkCmdBeginRendering");
    table->CmdEndRendering = (PFN_vkCmdEndRendering)gpa(dev, "vkCmdEndRendering");
    table->CmdSetCullMode = (PFN_vkCmdSetCullMode)gpa(dev, "vkCmdSetCullMode");
    table->CmdSetFrontFace = (PFN_vkCmdSetFrontFace)gpa(dev, "vkCmdSetFrontFace");
    table->CmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)gpa(dev, "vkCmdSetPrimitiveTopology");
    table->CmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)gpa(dev, "vkCmdSetViewportWithCount");
    table->CmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)gpa(dev, "vkCmdSetScissorWithCount");
    table->CmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)gpa(dev, "vkCmdBindVertexBuffers2");
    table->CmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)gpa(dev, "vkCmdSetDepthTestEnable");
    table->CmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)gpa(dev, "vkCmdSetDepthWriteEnable");
    table->CmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)gpa(dev, "vkCmdSetDepthCompareOp");
    table->CmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)gpa(dev, "vkCmdSetDepthBoundsTestEnable");
    table->CmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)gpa(dev, "vkCmdSetStencilTestEnable");
    table->CmdSetStencilOp = (PFN_vkCmdSetStencilOp)gpa(dev, "vkCmdSetStencilOp");
    table->CmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)gpa(dev, "vkCmdSetRasterizerDiscardEnable");
    table->CmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)gpa(dev, "vkCmdSetDepthBiasEnable");
    table->CmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)gpa(dev, "vkCmdSetPrimitiveRestartEnable");

    // ---- Core Vulkan 1.4 commands
    table->MapMemory2 = (PFN_vkMapMemory2)gpa(dev, "vkMapMemory2");
    table->UnmapMemory2 = (PFN_vkUnmapMemory2)gpa(dev, "vkUnmapMemory2");
    table->GetDeviceImageSubresourceLayout = (PFN_vkGetDeviceImageSubresourceLayout)gpa(dev, "vkGetDeviceImageSubresourceLayout");
    table->GetImageSubresourceLayout2 = (PFN_vkGetImageSubresourceLayout2)gpa(dev, "vkGetImageSubresourceLayout2");
    table->CopyMemoryToImage = (PFN_vkCopyMemoryToImage)gpa(dev, "vkCopyMemoryToImage");
    table->CopyImageToMemory = (PFN_vkCopyImageToMemory)gpa(dev, "vkCopyImageToMemory");
    table->CopyImageToImage = (PFN_vkCopyImageToImage)gpa(dev, "vkCopyImageToImage");
    table->TransitionImageLayout = (PFN_vkTransitionImageLayout)gpa(dev, "vkTransitionImageLayout");
    table->CmdPushDescriptorSet = (PFN_vkCmdPushDescriptorSet)gpa(dev, "vkCmdPushDescriptorSet");
    table->CmdPushDescriptorSetWithTemplate = (PFN_vkCmdPushDescriptorSetWithTemplate)gpa(dev, "vkCmdPushDescriptorSetWithTemplate");
    table->CmdBindDescriptorSets2 = (PFN_vkCmdBindDescriptorSets2)gpa(dev, "vkCmdBindDescriptorSets2");
    table->CmdPushConstants2 = (PFN_vkCmdPushConstants2)gpa(dev, "vkCmdPushConstants2");
    table->CmdPushDescriptorSet2 = (PFN_vkCmdPushDescriptorSet2)gpa(dev, "vkCmdPushDescriptorSet2");
    table->CmdPushDescriptorSetWithTemplate2 = (PFN_vkCmdPushDescriptorSetWithTemplate2)gpa(dev, "vkCmdPushDescriptorSetWithTemplate2");
    table->CmdSetLineStipple = (PFN_vkCmdSetLineStipple)gpa(dev, "vkCmdSetLineStipple");
    table->CmdBindIndexBuffer2 = (PFN_vkCmdBindIndexBuffer2)gpa(dev, "vkCmdBindIndexBuffer2");
    table->GetRenderingAreaGranularity = (PFN_vkGetRenderingAreaGranularity)gpa(dev, "vkGetRenderingAreaGranularity");
    table->CmdSetRenderingAttachmentLocations = (PFN_vkCmdSetRenderingAttachmentLocations)gpa(dev, "vkCmdSetRenderingAttachmentLocations");
    table->CmdSetRenderingInputAttachmentIndices = (PFN_vkCmdSetRenderingInputAttachmentIndices)gpa(dev, "vkCmdSetRenderingInputAttachmentIndices");
}

// Init Device function pointer dispatch table with extension commands
VKAPI_ATTR void VKAPI_CALL loader_init_device_extension_dispatch_table(struct loader_dev_dispatch_table *dev_table,
                                                                       PFN_vkGetInstanceProcAddr gipa,
                                                                       PFN_vkGetDeviceProcAddr gdpa,
                                                                       VkInstance inst,
                                                                       VkDevice dev) {
    VkLayerDispatchTable *table = &dev_table->core_dispatch;
    table->magic = DEVICE_DISP_TABLE_MAGIC_NUMBER;

    // ---- VK_KHR_swapchain extension commands
    table->CreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)gdpa(dev, "vkCreateSwapchainKHR");
    table->DestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)gdpa(dev, "vkDestroySwapchainKHR");
    table->GetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)gdpa(dev, "vkGetSwapchainImagesKHR");
    table->AcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)gdpa(dev, "vkAcquireNextImageKHR");
    table->QueuePresentKHR = (PFN_vkQueuePresentKHR)gdpa(dev, "vkQueuePresentKHR");
    table->GetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)gdpa(dev, "vkGetDeviceGroupPresentCapabilitiesKHR");
    table->GetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)gdpa(dev, "vkGetDeviceGroupSurfacePresentModesKHR");
    table->AcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)gdpa(dev, "vkAcquireNextImage2KHR");

    // ---- VK_KHR_display_swapchain extension commands
    table->CreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)gdpa(dev, "vkCreateSharedSwapchainsKHR");

    // ---- VK_KHR_video_queue extension commands
    table->CreateVideoSessionKHR = (PFN_vkCreateVideoSessionKHR)gdpa(dev, "vkCreateVideoSessionKHR");
    table->DestroyVideoSessionKHR = (PFN_vkDestroyVideoSessionKHR)gdpa(dev, "vkDestroyVideoSessionKHR");
    table->GetVideoSessionMemoryRequirementsKHR = (PFN_vkGetVideoSessionMemoryRequirementsKHR)gdpa(dev, "vkGetVideoSessionMemoryRequirementsKHR");
    table->BindVideoSessionMemoryKHR = (PFN_vkBindVideoSessionMemoryKHR)gdpa(dev, "vkBindVideoSessionMemoryKHR");
    table->CreateVideoSessionParametersKHR = (PFN_vkCreateVideoSessionParametersKHR)gdpa(dev, "vkCreateVideoSessionParametersKHR");
    table->UpdateVideoSessionParametersKHR = (PFN_vkUpdateVideoSessionParametersKHR)gdpa(dev, "vkUpdateVideoSessionParametersKHR");
    table->DestroyVideoSessionParametersKHR = (PFN_vkDestroyVideoSessionParametersKHR)gdpa(dev, "vkDestroyVideoSessionParametersKHR");
    table->CmdBeginVideoCodingKHR = (PFN_vkCmdBeginVideoCodingKHR)gdpa(dev, "vkCmdBeginVideoCodingKHR");
    table->CmdEndVideoCodingKHR = (PFN_vkCmdEndVideoCodingKHR)gdpa(dev, "vkCmdEndVideoCodingKHR");
    table->CmdControlVideoCodingKHR = (PFN_vkCmdControlVideoCodingKHR)gdpa(dev, "vkCmdControlVideoCodingKHR");

    // ---- VK_KHR_video_decode_queue extension commands
    table->CmdDecodeVideoKHR = (PFN_vkCmdDecodeVideoKHR)gdpa(dev, "vkCmdDecodeVideoKHR");

    // ---- VK_KHR_dynamic_rendering extension commands
    table->CmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)gdpa(dev, "vkCmdBeginRenderingKHR");
    table->CmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)gdpa(dev, "vkCmdEndRenderingKHR");

    // ---- VK_KHR_device_group extension commands
    table->GetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)gdpa(dev, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
    table->CmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR)gdpa(dev, "vkCmdSetDeviceMaskKHR");
    table->CmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR)gdpa(dev, "vkCmdDispatchBaseKHR");

    // ---- VK_KHR_maintenance1 extension commands
    table->TrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR)gdpa(dev, "vkTrimCommandPoolKHR");

    // ---- VK_KHR_external_memory_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetMemoryWin32HandleKHR = (PFN_vkGetMemoryWin32HandleKHR)gdpa(dev, "vkGetMemoryWin32HandleKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetMemoryWin32HandlePropertiesKHR = (PFN_vkGetMemoryWin32HandlePropertiesKHR)gdpa(dev, "vkGetMemoryWin32HandlePropertiesKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_memory_fd extension commands
    table->GetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)gdpa(dev, "vkGetMemoryFdKHR");
    table->GetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR)gdpa(dev, "vkGetMemoryFdPropertiesKHR");

    // ---- VK_KHR_external_semaphore_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->ImportSemaphoreWin32HandleKHR = (PFN_vkImportSemaphoreWin32HandleKHR)gdpa(dev, "vkImportSemaphoreWin32HandleKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetSemaphoreWin32HandleKHR = (PFN_vkGetSemaphoreWin32HandleKHR)gdpa(dev, "vkGetSemaphoreWin32HandleKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_semaphore_fd extension commands
    table->ImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR)gdpa(dev, "vkImportSemaphoreFdKHR");
    table->GetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)gdpa(dev, "vkGetSemaphoreFdKHR");

    // ---- VK_KHR_push_descriptor extension commands
    table->CmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR)gdpa(dev, "vkCmdPushDescriptorSetKHR");
    table->CmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR)gdpa(dev, "vkCmdPushDescriptorSetWithTemplateKHR");

    // ---- VK_KHR_descriptor_update_template extension commands
    table->CreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR)gdpa(dev, "vkCreateDescriptorUpdateTemplateKHR");
    table->DestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR)gdpa(dev, "vkDestroyDescriptorUpdateTemplateKHR");
    table->UpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR)gdpa(dev, "vkUpdateDescriptorSetWithTemplateKHR");

    // ---- VK_KHR_create_renderpass2 extension commands
    table->CreateRenderPass2KHR = (PFN_vkCreateRenderPass2KHR)gdpa(dev, "vkCreateRenderPass2KHR");
    table->CmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR)gdpa(dev, "vkCmdBeginRenderPass2KHR");
    table->CmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR)gdpa(dev, "vkCmdNextSubpass2KHR");
    table->CmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR)gdpa(dev, "vkCmdEndRenderPass2KHR");

    // ---- VK_KHR_shared_presentable_image extension commands
    table->GetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR)gdpa(dev, "vkGetSwapchainStatusKHR");

    // ---- VK_KHR_external_fence_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->ImportFenceWin32HandleKHR = (PFN_vkImportFenceWin32HandleKHR)gdpa(dev, "vkImportFenceWin32HandleKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetFenceWin32HandleKHR = (PFN_vkGetFenceWin32HandleKHR)gdpa(dev, "vkGetFenceWin32HandleKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_fence_fd extension commands
    table->ImportFenceFdKHR = (PFN_vkImportFenceFdKHR)gdpa(dev, "vkImportFenceFdKHR");
    table->GetFenceFdKHR = (PFN_vkGetFenceFdKHR)gdpa(dev, "vkGetFenceFdKHR");

    // ---- VK_KHR_performance_query extension commands
    table->AcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR)gdpa(dev, "vkAcquireProfilingLockKHR");
    table->ReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR)gdpa(dev, "vkReleaseProfilingLockKHR");

    // ---- VK_KHR_get_memory_requirements2 extension commands
    table->GetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)gdpa(dev, "vkGetImageMemoryRequirements2KHR");
    table->GetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)gdpa(dev, "vkGetBufferMemoryRequirements2KHR");
    table->GetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)gdpa(dev, "vkGetImageSparseMemoryRequirements2KHR");

    // ---- VK_KHR_sampler_ycbcr_conversion extension commands
    table->CreateSamplerYcbcrConversionKHR = (PFN_vkCreateSamplerYcbcrConversionKHR)gdpa(dev, "vkCreateSamplerYcbcrConversionKHR");
    table->DestroySamplerYcbcrConversionKHR = (PFN_vkDestroySamplerYcbcrConversionKHR)gdpa(dev, "vkDestroySamplerYcbcrConversionKHR");

    // ---- VK_KHR_bind_memory2 extension commands
    table->BindBufferMemory2KHR = (PFN_vkBindBufferMemory2KHR)gdpa(dev, "vkBindBufferMemory2KHR");
    table->BindImageMemory2KHR = (PFN_vkBindImageMemory2KHR)gdpa(dev, "vkBindImageMemory2KHR");

    // ---- VK_KHR_maintenance3 extension commands
    table->GetDescriptorSetLayoutSupportKHR = (PFN_vkGetDescriptorSetLayoutSupportKHR)gdpa(dev, "vkGetDescriptorSetLayoutSupportKHR");

    // ---- VK_KHR_draw_indirect_count extension commands
    table->CmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)gdpa(dev, "vkCmdDrawIndirectCountKHR");
    table->CmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)gdpa(dev, "vkCmdDrawIndexedIndirectCountKHR");

    // ---- VK_KHR_timeline_semaphore extension commands
    table->GetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)gdpa(dev, "vkGetSemaphoreCounterValueKHR");
    table->WaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)gdpa(dev, "vkWaitSemaphoresKHR");
    table->SignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)gdpa(dev, "vkSignalSemaphoreKHR");

    // ---- VK_KHR_fragment_shading_rate extension commands
    table->CmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)gdpa(dev, "vkCmdSetFragmentShadingRateKHR");

    // ---- VK_KHR_dynamic_rendering_local_read extension commands
    table->CmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR)gdpa(dev, "vkCmdSetRenderingAttachmentLocationsKHR");
    table->CmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR)gdpa(dev, "vkCmdSetRenderingInputAttachmentIndicesKHR");

    // ---- VK_KHR_present_wait extension commands
    table->WaitForPresentKHR = (PFN_vkWaitForPresentKHR)gdpa(dev, "vkWaitForPresentKHR");

    // ---- VK_KHR_buffer_device_address extension commands
    table->GetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)gdpa(dev, "vkGetBufferDeviceAddressKHR");
    table->GetBufferOpaqueCaptureAddressKHR = (PFN_vkGetBufferOpaqueCaptureAddressKHR)gdpa(dev, "vkGetBufferOpaqueCaptureAddressKHR");
    table->GetDeviceMemoryOpaqueCaptureAddressKHR = (PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR)gdpa(dev, "vkGetDeviceMemoryOpaqueCaptureAddressKHR");

    // ---- VK_KHR_deferred_host_operations extension commands
    table->CreateDeferredOperationKHR = (PFN_vkCreateDeferredOperationKHR)gdpa(dev, "vkCreateDeferredOperationKHR");
    table->DestroyDeferredOperationKHR = (PFN_vkDestroyDeferredOperationKHR)gdpa(dev, "vkDestroyDeferredOperationKHR");
    table->GetDeferredOperationMaxConcurrencyKHR = (PFN_vkGetDeferredOperationMaxConcurrencyKHR)gdpa(dev, "vkGetDeferredOperationMaxConcurrencyKHR");
    table->GetDeferredOperationResultKHR = (PFN_vkGetDeferredOperationResultKHR)gdpa(dev, "vkGetDeferredOperationResultKHR");
    table->DeferredOperationJoinKHR = (PFN_vkDeferredOperationJoinKHR)gdpa(dev, "vkDeferredOperationJoinKHR");

    // ---- VK_KHR_pipeline_executable_properties extension commands
    table->GetPipelineExecutablePropertiesKHR = (PFN_vkGetPipelineExecutablePropertiesKHR)gdpa(dev, "vkGetPipelineExecutablePropertiesKHR");
    table->GetPipelineExecutableStatisticsKHR = (PFN_vkGetPipelineExecutableStatisticsKHR)gdpa(dev, "vkGetPipelineExecutableStatisticsKHR");
    table->GetPipelineExecutableInternalRepresentationsKHR = (PFN_vkGetPipelineExecutableInternalRepresentationsKHR)gdpa(dev, "vkGetPipelineExecutableInternalRepresentationsKHR");

    // ---- VK_KHR_map_memory2 extension commands
    table->MapMemory2KHR = (PFN_vkMapMemory2KHR)gdpa(dev, "vkMapMemory2KHR");
    table->UnmapMemory2KHR = (PFN_vkUnmapMemory2KHR)gdpa(dev, "vkUnmapMemory2KHR");

    // ---- VK_KHR_video_encode_queue extension commands
    table->GetEncodedVideoSessionParametersKHR = (PFN_vkGetEncodedVideoSessionParametersKHR)gdpa(dev, "vkGetEncodedVideoSessionParametersKHR");
    table->CmdEncodeVideoKHR = (PFN_vkCmdEncodeVideoKHR)gdpa(dev, "vkCmdEncodeVideoKHR");

    // ---- VK_KHR_synchronization2 extension commands
    table->CmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)gdpa(dev, "vkCmdSetEvent2KHR");
    table->CmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)gdpa(dev, "vkCmdResetEvent2KHR");
    table->CmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)gdpa(dev, "vkCmdWaitEvents2KHR");
    table->CmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)gdpa(dev, "vkCmdPipelineBarrier2KHR");
    table->CmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)gdpa(dev, "vkCmdWriteTimestamp2KHR");
    table->QueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)gdpa(dev, "vkQueueSubmit2KHR");

    // ---- VK_KHR_device_address_commands extension commands
    table->CmdBindIndexBuffer3KHR = (PFN_vkCmdBindIndexBuffer3KHR)gdpa(dev, "vkCmdBindIndexBuffer3KHR");
    table->CmdBindVertexBuffers3KHR = (PFN_vkCmdBindVertexBuffers3KHR)gdpa(dev, "vkCmdBindVertexBuffers3KHR");
    table->CmdDrawIndirect2KHR = (PFN_vkCmdDrawIndirect2KHR)gdpa(dev, "vkCmdDrawIndirect2KHR");
    table->CmdDrawIndexedIndirect2KHR = (PFN_vkCmdDrawIndexedIndirect2KHR)gdpa(dev, "vkCmdDrawIndexedIndirect2KHR");
    table->CmdDispatchIndirect2KHR = (PFN_vkCmdDispatchIndirect2KHR)gdpa(dev, "vkCmdDispatchIndirect2KHR");
    table->CmdCopyMemoryKHR = (PFN_vkCmdCopyMemoryKHR)gdpa(dev, "vkCmdCopyMemoryKHR");
    table->CmdCopyMemoryToImageKHR = (PFN_vkCmdCopyMemoryToImageKHR)gdpa(dev, "vkCmdCopyMemoryToImageKHR");
    table->CmdCopyImageToMemoryKHR = (PFN_vkCmdCopyImageToMemoryKHR)gdpa(dev, "vkCmdCopyImageToMemoryKHR");
    table->CmdUpdateMemoryKHR = (PFN_vkCmdUpdateMemoryKHR)gdpa(dev, "vkCmdUpdateMemoryKHR");
    table->CmdFillMemoryKHR = (PFN_vkCmdFillMemoryKHR)gdpa(dev, "vkCmdFillMemoryKHR");
    table->CmdCopyQueryPoolResultsToMemoryKHR = (PFN_vkCmdCopyQueryPoolResultsToMemoryKHR)gdpa(dev, "vkCmdCopyQueryPoolResultsToMemoryKHR");
    table->CmdDrawIndirectCount2KHR = (PFN_vkCmdDrawIndirectCount2KHR)gdpa(dev, "vkCmdDrawIndirectCount2KHR");
    table->CmdDrawIndexedIndirectCount2KHR = (PFN_vkCmdDrawIndexedIndirectCount2KHR)gdpa(dev, "vkCmdDrawIndexedIndirectCount2KHR");
    table->CmdBeginConditionalRendering2EXT = (PFN_vkCmdBeginConditionalRendering2EXT)gdpa(dev, "vkCmdBeginConditionalRendering2EXT");
    table->CmdBindTransformFeedbackBuffers2EXT = (PFN_vkCmdBindTransformFeedbackBuffers2EXT)gdpa(dev, "vkCmdBindTransformFeedbackBuffers2EXT");
    table->CmdBeginTransformFeedback2EXT = (PFN_vkCmdBeginTransformFeedback2EXT)gdpa(dev, "vkCmdBeginTransformFeedback2EXT");
    table->CmdEndTransformFeedback2EXT = (PFN_vkCmdEndTransformFeedback2EXT)gdpa(dev, "vkCmdEndTransformFeedback2EXT");
    table->CmdDrawIndirectByteCount2EXT = (PFN_vkCmdDrawIndirectByteCount2EXT)gdpa(dev, "vkCmdDrawIndirectByteCount2EXT");
    table->CmdDrawMeshTasksIndirect2EXT = (PFN_vkCmdDrawMeshTasksIndirect2EXT)gdpa(dev, "vkCmdDrawMeshTasksIndirect2EXT");
    table->CmdDrawMeshTasksIndirectCount2EXT = (PFN_vkCmdDrawMeshTasksIndirectCount2EXT)gdpa(dev, "vkCmdDrawMeshTasksIndirectCount2EXT");
    table->CmdWriteMarkerToMemoryAMD = (PFN_vkCmdWriteMarkerToMemoryAMD)gdpa(dev, "vkCmdWriteMarkerToMemoryAMD");
    table->CreateAccelerationStructure2KHR = (PFN_vkCreateAccelerationStructure2KHR)gdpa(dev, "vkCreateAccelerationStructure2KHR");

    // ---- VK_KHR_copy_commands2 extension commands
    table->CmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)gdpa(dev, "vkCmdCopyBuffer2KHR");
    table->CmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)gdpa(dev, "vkCmdCopyImage2KHR");
    table->CmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)gdpa(dev, "vkCmdCopyBufferToImage2KHR");
    table->CmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)gdpa(dev, "vkCmdCopyImageToBuffer2KHR");
    table->CmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)gdpa(dev, "vkCmdBlitImage2KHR");
    table->CmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)gdpa(dev, "vkCmdResolveImage2KHR");

    // ---- VK_KHR_ray_tracing_maintenance1 extension commands
    table->CmdTraceRaysIndirect2KHR = (PFN_vkCmdTraceRaysIndirect2KHR)gdpa(dev, "vkCmdTraceRaysIndirect2KHR");

    // ---- VK_KHR_maintenance4 extension commands
    table->GetDeviceBufferMemoryRequirementsKHR = (PFN_vkGetDeviceBufferMemoryRequirementsKHR)gdpa(dev, "vkGetDeviceBufferMemoryRequirementsKHR");
    table->GetDeviceImageMemoryRequirementsKHR = (PFN_vkGetDeviceImageMemoryRequirementsKHR)gdpa(dev, "vkGetDeviceImageMemoryRequirementsKHR");
    table->GetDeviceImageSparseMemoryRequirementsKHR = (PFN_vkGetDeviceImageSparseMemoryRequirementsKHR)gdpa(dev, "vkGetDeviceImageSparseMemoryRequirementsKHR");

    // ---- VK_KHR_maintenance5 extension commands
    table->CmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR)gdpa(dev, "vkCmdBindIndexBuffer2KHR");
    table->GetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)gdpa(dev, "vkGetRenderingAreaGranularityKHR");
    table->GetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)gdpa(dev, "vkGetDeviceImageSubresourceLayoutKHR");
    table->GetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)gdpa(dev, "vkGetImageSubresourceLayout2KHR");

    // ---- VK_KHR_present_wait2 extension commands
    table->WaitForPresent2KHR = (PFN_vkWaitForPresent2KHR)gdpa(dev, "vkWaitForPresent2KHR");

    // ---- VK_KHR_pipeline_binary extension commands
    table->CreatePipelineBinariesKHR = (PFN_vkCreatePipelineBinariesKHR)gdpa(dev, "vkCreatePipelineBinariesKHR");
    table->DestroyPipelineBinaryKHR = (PFN_vkDestroyPipelineBinaryKHR)gdpa(dev, "vkDestroyPipelineBinaryKHR");
    table->GetPipelineKeyKHR = (PFN_vkGetPipelineKeyKHR)gdpa(dev, "vkGetPipelineKeyKHR");
    table->GetPipelineBinaryDataKHR = (PFN_vkGetPipelineBinaryDataKHR)gdpa(dev, "vkGetPipelineBinaryDataKHR");
    table->ReleaseCapturedPipelineDataKHR = (PFN_vkReleaseCapturedPipelineDataKHR)gdpa(dev, "vkReleaseCapturedPipelineDataKHR");

    // ---- VK_KHR_swapchain_maintenance1 extension commands
    table->ReleaseSwapchainImagesKHR = (PFN_vkReleaseSwapchainImagesKHR)gdpa(dev, "vkReleaseSwapchainImagesKHR");

    // ---- VK_KHR_line_rasterization extension commands
    table->CmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)gdpa(dev, "vkCmdSetLineStippleKHR");

    // ---- VK_KHR_calibrated_timestamps extension commands
    table->GetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR)gdpa(dev, "vkGetCalibratedTimestampsKHR");

    // ---- VK_KHR_maintenance6 extension commands
    table->CmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR)gdpa(dev, "vkCmdBindDescriptorSets2KHR");
    table->CmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR)gdpa(dev, "vkCmdPushConstants2KHR");
    table->CmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR)gdpa(dev, "vkCmdPushDescriptorSet2KHR");
    table->CmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR)gdpa(dev, "vkCmdPushDescriptorSetWithTemplate2KHR");
    table->CmdSetDescriptorBufferOffsets2EXT = (PFN_vkCmdSetDescriptorBufferOffsets2EXT)gdpa(dev, "vkCmdSetDescriptorBufferOffsets2EXT");
    table->CmdBindDescriptorBufferEmbeddedSamplers2EXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT)gdpa(dev, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT");

    // ---- VK_KHR_copy_memory_indirect extension commands
    table->CmdCopyMemoryIndirectKHR = (PFN_vkCmdCopyMemoryIndirectKHR)gdpa(dev, "vkCmdCopyMemoryIndirectKHR");
    table->CmdCopyMemoryToImageIndirectKHR = (PFN_vkCmdCopyMemoryToImageIndirectKHR)gdpa(dev, "vkCmdCopyMemoryToImageIndirectKHR");

    // ---- VK_KHR_device_fault extension commands
    table->GetDeviceFaultReportsKHR = (PFN_vkGetDeviceFaultReportsKHR)gdpa(dev, "vkGetDeviceFaultReportsKHR");
    table->GetDeviceFaultDebugInfoKHR = (PFN_vkGetDeviceFaultDebugInfoKHR)gdpa(dev, "vkGetDeviceFaultDebugInfoKHR");

    // ---- VK_KHR_maintenance10 extension commands
    table->CmdEndRendering2KHR = (PFN_vkCmdEndRendering2KHR)gdpa(dev, "vkCmdEndRendering2KHR");

    // ---- VK_EXT_debug_marker extension commands
    table->DebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)gdpa(dev, "vkDebugMarkerSetObjectTagEXT");
    table->DebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)gdpa(dev, "vkDebugMarkerSetObjectNameEXT");
    table->CmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT)gdpa(dev, "vkCmdDebugMarkerBeginEXT");
    table->CmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT)gdpa(dev, "vkCmdDebugMarkerEndEXT");
    table->CmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT)gdpa(dev, "vkCmdDebugMarkerInsertEXT");

    // ---- VK_EXT_transform_feedback extension commands
    table->CmdBindTransformFeedbackBuffersEXT = (PFN_vkCmdBindTransformFeedbackBuffersEXT)gdpa(dev, "vkCmdBindTransformFeedbackBuffersEXT");
    table->CmdBeginTransformFeedbackEXT = (PFN_vkCmdBeginTransformFeedbackEXT)gdpa(dev, "vkCmdBeginTransformFeedbackEXT");
    table->CmdEndTransformFeedbackEXT = (PFN_vkCmdEndTransformFeedbackEXT)gdpa(dev, "vkCmdEndTransformFeedbackEXT");
    table->CmdBeginQueryIndexedEXT = (PFN_vkCmdBeginQueryIndexedEXT)gdpa(dev, "vkCmdBeginQueryIndexedEXT");
    table->CmdEndQueryIndexedEXT = (PFN_vkCmdEndQueryIndexedEXT)gdpa(dev, "vkCmdEndQueryIndexedEXT");
    table->CmdDrawIndirectByteCountEXT = (PFN_vkCmdDrawIndirectByteCountEXT)gdpa(dev, "vkCmdDrawIndirectByteCountEXT");

    // ---- VK_NVX_binary_import extension commands
    table->CreateCuModuleNVX = (PFN_vkCreateCuModuleNVX)gdpa(dev, "vkCreateCuModuleNVX");
    table->CreateCuFunctionNVX = (PFN_vkCreateCuFunctionNVX)gdpa(dev, "vkCreateCuFunctionNVX");
    table->DestroyCuModuleNVX = (PFN_vkDestroyCuModuleNVX)gdpa(dev, "vkDestroyCuModuleNVX");
    table->DestroyCuFunctionNVX = (PFN_vkDestroyCuFunctionNVX)gdpa(dev, "vkDestroyCuFunctionNVX");
    table->CmdCuLaunchKernelNVX = (PFN_vkCmdCuLaunchKernelNVX)gdpa(dev, "vkCmdCuLaunchKernelNVX");

    // ---- VK_NVX_image_view_handle extension commands
    table->GetImageViewHandleNVX = (PFN_vkGetImageViewHandleNVX)gdpa(dev, "vkGetImageViewHandleNVX");
    table->GetImageViewHandle64NVX = (PFN_vkGetImageViewHandle64NVX)gdpa(dev, "vkGetImageViewHandle64NVX");
    table->GetImageViewAddressNVX = (PFN_vkGetImageViewAddressNVX)gdpa(dev, "vkGetImageViewAddressNVX");
    table->GetDeviceCombinedImageSamplerIndexNVX = (PFN_vkGetDeviceCombinedImageSamplerIndexNVX)gdpa(dev, "vkGetDeviceCombinedImageSamplerIndexNVX");

    // ---- VK_AMD_draw_indirect_count extension commands
    table->CmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)gdpa(dev, "vkCmdDrawIndirectCountAMD");
    table->CmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)gdpa(dev, "vkCmdDrawIndexedIndirectCountAMD");

    // ---- VK_AMD_shader_info extension commands
    table->GetShaderInfoAMD = (PFN_vkGetShaderInfoAMD)gdpa(dev, "vkGetShaderInfoAMD");

    // ---- VK_NV_external_memory_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV)gdpa(dev, "vkGetMemoryWin32HandleNV");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_conditional_rendering extension commands
    table->CmdBeginConditionalRenderingEXT = (PFN_vkCmdBeginConditionalRenderingEXT)gdpa(dev, "vkCmdBeginConditionalRenderingEXT");
    table->CmdEndConditionalRenderingEXT = (PFN_vkCmdEndConditionalRenderingEXT)gdpa(dev, "vkCmdEndConditionalRenderingEXT");

    // ---- VK_NV_clip_space_w_scaling extension commands
    table->CmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV)gdpa(dev, "vkCmdSetViewportWScalingNV");

    // ---- VK_EXT_display_control extension commands
    table->DisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT)gdpa(dev, "vkDisplayPowerControlEXT");
    table->RegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT)gdpa(dev, "vkRegisterDeviceEventEXT");
    table->RegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT)gdpa(dev, "vkRegisterDisplayEventEXT");
    table->GetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT)gdpa(dev, "vkGetSwapchainCounterEXT");

    // ---- VK_GOOGLE_display_timing extension commands
    table->GetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE)gdpa(dev, "vkGetRefreshCycleDurationGOOGLE");
    table->GetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE)gdpa(dev, "vkGetPastPresentationTimingGOOGLE");

    // ---- VK_EXT_discard_rectangles extension commands
    table->CmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)gdpa(dev, "vkCmdSetDiscardRectangleEXT");
    table->CmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)gdpa(dev, "vkCmdSetDiscardRectangleEnableEXT");
    table->CmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)gdpa(dev, "vkCmdSetDiscardRectangleModeEXT");

    // ---- VK_EXT_hdr_metadata extension commands
    table->SetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT)gdpa(dev, "vkSetHdrMetadataEXT");

    // ---- VK_EXT_debug_utils extension commands
    table->SetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)gipa(inst, "vkSetDebugUtilsObjectNameEXT");
    table->SetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)gipa(inst, "vkSetDebugUtilsObjectTagEXT");
    table->QueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)gipa(inst, "vkQueueBeginDebugUtilsLabelEXT");
    table->QueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)gipa(inst, "vkQueueEndDebugUtilsLabelEXT");
    table->QueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)gipa(inst, "vkQueueInsertDebugUtilsLabelEXT");
    table->CmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)gipa(inst, "vkCmdBeginDebugUtilsLabelEXT");
    table->CmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)gipa(inst, "vkCmdEndDebugUtilsLabelEXT");
    table->CmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)gipa(inst, "vkCmdInsertDebugUtilsLabelEXT");

    // ---- VK_ANDROID_external_memory_android_hardware_buffer extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    table->GetAndroidHardwareBufferPropertiesANDROID = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)gdpa(dev, "vkGetAndroidHardwareBufferPropertiesANDROID");
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    table->GetMemoryAndroidHardwareBufferANDROID = (PFN_vkGetMemoryAndroidHardwareBufferANDROID)gdpa(dev, "vkGetMemoryAndroidHardwareBufferANDROID");
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_AMD_gpa_interface extension commands
    table->CreateGpaSessionAMD = (PFN_vkCreateGpaSessionAMD)gdpa(dev, "vkCreateGpaSessionAMD");
    table->DestroyGpaSessionAMD = (PFN_vkDestroyGpaSessionAMD)gdpa(dev, "vkDestroyGpaSessionAMD");
    table->SetGpaDeviceClockModeAMD = (PFN_vkSetGpaDeviceClockModeAMD)gdpa(dev, "vkSetGpaDeviceClockModeAMD");
    table->GetGpaDeviceClockInfoAMD = (PFN_vkGetGpaDeviceClockInfoAMD)gdpa(dev, "vkGetGpaDeviceClockInfoAMD");
    table->CmdBeginGpaSessionAMD = (PFN_vkCmdBeginGpaSessionAMD)gdpa(dev, "vkCmdBeginGpaSessionAMD");
    table->CmdEndGpaSessionAMD = (PFN_vkCmdEndGpaSessionAMD)gdpa(dev, "vkCmdEndGpaSessionAMD");
    table->CmdBeginGpaSampleAMD = (PFN_vkCmdBeginGpaSampleAMD)gdpa(dev, "vkCmdBeginGpaSampleAMD");
    table->CmdEndGpaSampleAMD = (PFN_vkCmdEndGpaSampleAMD)gdpa(dev, "vkCmdEndGpaSampleAMD");
    table->GetGpaSessionStatusAMD = (PFN_vkGetGpaSessionStatusAMD)gdpa(dev, "vkGetGpaSessionStatusAMD");
    table->GetGpaSessionResultsAMD = (PFN_vkGetGpaSessionResultsAMD)gdpa(dev, "vkGetGpaSessionResultsAMD");
    table->ResetGpaSessionAMD = (PFN_vkResetGpaSessionAMD)gdpa(dev, "vkResetGpaSessionAMD");
    table->CmdCopyGpaSessionResultsAMD = (PFN_vkCmdCopyGpaSessionResultsAMD)gdpa(dev, "vkCmdCopyGpaSessionResultsAMD");

    // ---- VK_AMDX_shader_enqueue extension commands
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CreateExecutionGraphPipelinesAMDX = (PFN_vkCreateExecutionGraphPipelinesAMDX)gdpa(dev, "vkCreateExecutionGraphPipelinesAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->GetExecutionGraphPipelineScratchSizeAMDX = (PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)gdpa(dev, "vkGetExecutionGraphPipelineScratchSizeAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->GetExecutionGraphPipelineNodeIndexAMDX = (PFN_vkGetExecutionGraphPipelineNodeIndexAMDX)gdpa(dev, "vkGetExecutionGraphPipelineNodeIndexAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CmdInitializeGraphScratchMemoryAMDX = (PFN_vkCmdInitializeGraphScratchMemoryAMDX)gdpa(dev, "vkCmdInitializeGraphScratchMemoryAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CmdDispatchGraphAMDX = (PFN_vkCmdDispatchGraphAMDX)gdpa(dev, "vkCmdDispatchGraphAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CmdDispatchGraphIndirectAMDX = (PFN_vkCmdDispatchGraphIndirectAMDX)gdpa(dev, "vkCmdDispatchGraphIndirectAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CmdDispatchGraphIndirectCountAMDX = (PFN_vkCmdDispatchGraphIndirectCountAMDX)gdpa(dev, "vkCmdDispatchGraphIndirectCountAMDX");
#endif // VK_ENABLE_BETA_EXTENSIONS

    // ---- VK_EXT_descriptor_heap extension commands
    table->WriteSamplerDescriptorsEXT = (PFN_vkWriteSamplerDescriptorsEXT)gdpa(dev, "vkWriteSamplerDescriptorsEXT");
    table->WriteResourceDescriptorsEXT = (PFN_vkWriteResourceDescriptorsEXT)gdpa(dev, "vkWriteResourceDescriptorsEXT");
    table->CmdBindSamplerHeapEXT = (PFN_vkCmdBindSamplerHeapEXT)gdpa(dev, "vkCmdBindSamplerHeapEXT");
    table->CmdBindResourceHeapEXT = (PFN_vkCmdBindResourceHeapEXT)gdpa(dev, "vkCmdBindResourceHeapEXT");
    table->CmdPushDataEXT = (PFN_vkCmdPushDataEXT)gdpa(dev, "vkCmdPushDataEXT");
    table->GetImageOpaqueCaptureDataEXT = (PFN_vkGetImageOpaqueCaptureDataEXT)gdpa(dev, "vkGetImageOpaqueCaptureDataEXT");
    table->RegisterCustomBorderColorEXT = (PFN_vkRegisterCustomBorderColorEXT)gdpa(dev, "vkRegisterCustomBorderColorEXT");
    table->UnregisterCustomBorderColorEXT = (PFN_vkUnregisterCustomBorderColorEXT)gdpa(dev, "vkUnregisterCustomBorderColorEXT");
    table->GetTensorOpaqueCaptureDataARM = (PFN_vkGetTensorOpaqueCaptureDataARM)gdpa(dev, "vkGetTensorOpaqueCaptureDataARM");

    // ---- VK_EXT_sample_locations extension commands
    table->CmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)gdpa(dev, "vkCmdSetSampleLocationsEXT");

    // ---- VK_EXT_image_drm_format_modifier extension commands
    table->GetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT)gdpa(dev, "vkGetImageDrmFormatModifierPropertiesEXT");

    // ---- VK_EXT_validation_cache extension commands
    table->CreateValidationCacheEXT = (PFN_vkCreateValidationCacheEXT)gdpa(dev, "vkCreateValidationCacheEXT");
    table->DestroyValidationCacheEXT = (PFN_vkDestroyValidationCacheEXT)gdpa(dev, "vkDestroyValidationCacheEXT");
    table->MergeValidationCachesEXT = (PFN_vkMergeValidationCachesEXT)gdpa(dev, "vkMergeValidationCachesEXT");
    table->GetValidationCacheDataEXT = (PFN_vkGetValidationCacheDataEXT)gdpa(dev, "vkGetValidationCacheDataEXT");

    // ---- VK_NV_shading_rate_image extension commands
    table->CmdBindShadingRateImageNV = (PFN_vkCmdBindShadingRateImageNV)gdpa(dev, "vkCmdBindShadingRateImageNV");
    table->CmdSetViewportShadingRatePaletteNV = (PFN_vkCmdSetViewportShadingRatePaletteNV)gdpa(dev, "vkCmdSetViewportShadingRatePaletteNV");
    table->CmdSetCoarseSampleOrderNV = (PFN_vkCmdSetCoarseSampleOrderNV)gdpa(dev, "vkCmdSetCoarseSampleOrderNV");

    // ---- VK_NV_ray_tracing extension commands
    table->CreateAccelerationStructureNV = (PFN_vkCreateAccelerationStructureNV)gdpa(dev, "vkCreateAccelerationStructureNV");
    table->DestroyAccelerationStructureNV = (PFN_vkDestroyAccelerationStructureNV)gdpa(dev, "vkDestroyAccelerationStructureNV");
    table->GetAccelerationStructureMemoryRequirementsNV = (PFN_vkGetAccelerationStructureMemoryRequirementsNV)gdpa(dev, "vkGetAccelerationStructureMemoryRequirementsNV");
    table->BindAccelerationStructureMemoryNV = (PFN_vkBindAccelerationStructureMemoryNV)gdpa(dev, "vkBindAccelerationStructureMemoryNV");
    table->CmdBuildAccelerationStructureNV = (PFN_vkCmdBuildAccelerationStructureNV)gdpa(dev, "vkCmdBuildAccelerationStructureNV");
    table->CmdCopyAccelerationStructureNV = (PFN_vkCmdCopyAccelerationStructureNV)gdpa(dev, "vkCmdCopyAccelerationStructureNV");
    table->CmdTraceRaysNV = (PFN_vkCmdTraceRaysNV)gdpa(dev, "vkCmdTraceRaysNV");
    table->CreateRayTracingPipelinesNV = (PFN_vkCreateRayTracingPipelinesNV)gdpa(dev, "vkCreateRayTracingPipelinesNV");

    // ---- VK_KHR_ray_tracing_pipeline extension commands
    table->GetRayTracingShaderGroupHandlesKHR = (PFN_vkGetRayTracingShaderGroupHandlesKHR)gdpa(dev, "vkGetRayTracingShaderGroupHandlesKHR");

    // ---- VK_NV_ray_tracing extension commands
    table->GetRayTracingShaderGroupHandlesNV = (PFN_vkGetRayTracingShaderGroupHandlesNV)gdpa(dev, "vkGetRayTracingShaderGroupHandlesNV");
    table->GetAccelerationStructureHandleNV = (PFN_vkGetAccelerationStructureHandleNV)gdpa(dev, "vkGetAccelerationStructureHandleNV");
    table->CmdWriteAccelerationStructuresPropertiesNV = (PFN_vkCmdWriteAccelerationStructuresPropertiesNV)gdpa(dev, "vkCmdWriteAccelerationStructuresPropertiesNV");
    table->CompileDeferredNV = (PFN_vkCompileDeferredNV)gdpa(dev, "vkCompileDeferredNV");

    // ---- VK_EXT_external_memory_host extension commands
    table->GetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT)gdpa(dev, "vkGetMemoryHostPointerPropertiesEXT");

    // ---- VK_AMD_buffer_marker extension commands
    table->CmdWriteBufferMarkerAMD = (PFN_vkCmdWriteBufferMarkerAMD)gdpa(dev, "vkCmdWriteBufferMarkerAMD");
    table->CmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD)gdpa(dev, "vkCmdWriteBufferMarker2AMD");

    // ---- VK_EXT_calibrated_timestamps extension commands
    table->GetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)gdpa(dev, "vkGetCalibratedTimestampsEXT");

    // ---- VK_NV_mesh_shader extension commands
    table->CmdDrawMeshTasksNV = (PFN_vkCmdDrawMeshTasksNV)gdpa(dev, "vkCmdDrawMeshTasksNV");
    table->CmdDrawMeshTasksIndirectNV = (PFN_vkCmdDrawMeshTasksIndirectNV)gdpa(dev, "vkCmdDrawMeshTasksIndirectNV");
    table->CmdDrawMeshTasksIndirectCountNV = (PFN_vkCmdDrawMeshTasksIndirectCountNV)gdpa(dev, "vkCmdDrawMeshTasksIndirectCountNV");

    // ---- VK_NV_scissor_exclusive extension commands
    table->CmdSetExclusiveScissorEnableNV = (PFN_vkCmdSetExclusiveScissorEnableNV)gdpa(dev, "vkCmdSetExclusiveScissorEnableNV");
    table->CmdSetExclusiveScissorNV = (PFN_vkCmdSetExclusiveScissorNV)gdpa(dev, "vkCmdSetExclusiveScissorNV");

    // ---- VK_NV_device_diagnostic_checkpoints extension commands
    table->CmdSetCheckpointNV = (PFN_vkCmdSetCheckpointNV)gdpa(dev, "vkCmdSetCheckpointNV");
    table->GetQueueCheckpointDataNV = (PFN_vkGetQueueCheckpointDataNV)gdpa(dev, "vkGetQueueCheckpointDataNV");
    table->GetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV)gdpa(dev, "vkGetQueueCheckpointData2NV");

    // ---- VK_EXT_present_timing extension commands
    table->SetSwapchainPresentTimingQueueSizeEXT = (PFN_vkSetSwapchainPresentTimingQueueSizeEXT)gdpa(dev, "vkSetSwapchainPresentTimingQueueSizeEXT");
    table->GetSwapchainTimingPropertiesEXT = (PFN_vkGetSwapchainTimingPropertiesEXT)gdpa(dev, "vkGetSwapchainTimingPropertiesEXT");
    table->GetSwapchainTimeDomainPropertiesEXT = (PFN_vkGetSwapchainTimeDomainPropertiesEXT)gdpa(dev, "vkGetSwapchainTimeDomainPropertiesEXT");
    table->GetPastPresentationTimingEXT = (PFN_vkGetPastPresentationTimingEXT)gdpa(dev, "vkGetPastPresentationTimingEXT");

    // ---- VK_INTEL_performance_query extension commands
    table->InitializePerformanceApiINTEL = (PFN_vkInitializePerformanceApiINTEL)gdpa(dev, "vkInitializePerformanceApiINTEL");
    table->UninitializePerformanceApiINTEL = (PFN_vkUninitializePerformanceApiINTEL)gdpa(dev, "vkUninitializePerformanceApiINTEL");
    table->CmdSetPerformanceMarkerINTEL = (PFN_vkCmdSetPerformanceMarkerINTEL)gdpa(dev, "vkCmdSetPerformanceMarkerINTEL");
    table->CmdSetPerformanceStreamMarkerINTEL = (PFN_vkCmdSetPerformanceStreamMarkerINTEL)gdpa(dev, "vkCmdSetPerformanceStreamMarkerINTEL");
    table->CmdSetPerformanceOverrideINTEL = (PFN_vkCmdSetPerformanceOverrideINTEL)gdpa(dev, "vkCmdSetPerformanceOverrideINTEL");
    table->AcquirePerformanceConfigurationINTEL = (PFN_vkAcquirePerformanceConfigurationINTEL)gdpa(dev, "vkAcquirePerformanceConfigurationINTEL");
    table->ReleasePerformanceConfigurationINTEL = (PFN_vkReleasePerformanceConfigurationINTEL)gdpa(dev, "vkReleasePerformanceConfigurationINTEL");
    table->QueueSetPerformanceConfigurationINTEL = (PFN_vkQueueSetPerformanceConfigurationINTEL)gdpa(dev, "vkQueueSetPerformanceConfigurationINTEL");
    table->GetPerformanceParameterINTEL = (PFN_vkGetPerformanceParameterINTEL)gdpa(dev, "vkGetPerformanceParameterINTEL");

    // ---- VK_AMD_display_native_hdr extension commands
    table->SetLocalDimmingAMD = (PFN_vkSetLocalDimmingAMD)gdpa(dev, "vkSetLocalDimmingAMD");

    // ---- VK_EXT_buffer_device_address extension commands
    table->GetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)gdpa(dev, "vkGetBufferDeviceAddressEXT");

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->AcquireFullScreenExclusiveModeEXT = (PFN_vkAcquireFullScreenExclusiveModeEXT)gdpa(dev, "vkAcquireFullScreenExclusiveModeEXT");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->ReleaseFullScreenExclusiveModeEXT = (PFN_vkReleaseFullScreenExclusiveModeEXT)gdpa(dev, "vkReleaseFullScreenExclusiveModeEXT");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)gdpa(dev, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_line_rasterization extension commands
    table->CmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)gdpa(dev, "vkCmdSetLineStippleEXT");

    // ---- VK_EXT_host_query_reset extension commands
    table->ResetQueryPoolEXT = (PFN_vkResetQueryPoolEXT)gdpa(dev, "vkResetQueryPoolEXT");

    // ---- VK_EXT_extended_dynamic_state extension commands
    table->CmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)gdpa(dev, "vkCmdSetCullModeEXT");
    table->CmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)gdpa(dev, "vkCmdSetFrontFaceEXT");
    table->CmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)gdpa(dev, "vkCmdSetPrimitiveTopologyEXT");
    table->CmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)gdpa(dev, "vkCmdSetViewportWithCountEXT");
    table->CmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)gdpa(dev, "vkCmdSetScissorWithCountEXT");
    table->CmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)gdpa(dev, "vkCmdBindVertexBuffers2EXT");
    table->CmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)gdpa(dev, "vkCmdSetDepthTestEnableEXT");
    table->CmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)gdpa(dev, "vkCmdSetDepthWriteEnableEXT");
    table->CmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)gdpa(dev, "vkCmdSetDepthCompareOpEXT");
    table->CmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)gdpa(dev, "vkCmdSetDepthBoundsTestEnableEXT");
    table->CmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)gdpa(dev, "vkCmdSetStencilTestEnableEXT");
    table->CmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)gdpa(dev, "vkCmdSetStencilOpEXT");

    // ---- VK_EXT_host_image_copy extension commands
    table->CopyMemoryToImageEXT = (PFN_vkCopyMemoryToImageEXT)gdpa(dev, "vkCopyMemoryToImageEXT");
    table->CopyImageToMemoryEXT = (PFN_vkCopyImageToMemoryEXT)gdpa(dev, "vkCopyImageToMemoryEXT");
    table->CopyImageToImageEXT = (PFN_vkCopyImageToImageEXT)gdpa(dev, "vkCopyImageToImageEXT");
    table->TransitionImageLayoutEXT = (PFN_vkTransitionImageLayoutEXT)gdpa(dev, "vkTransitionImageLayoutEXT");
    table->GetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)gdpa(dev, "vkGetImageSubresourceLayout2EXT");

    // ---- VK_EXT_swapchain_maintenance1 extension commands
    table->ReleaseSwapchainImagesEXT = (PFN_vkReleaseSwapchainImagesEXT)gdpa(dev, "vkReleaseSwapchainImagesEXT");

    // ---- VK_NV_device_generated_commands extension commands
    table->GetGeneratedCommandsMemoryRequirementsNV = (PFN_vkGetGeneratedCommandsMemoryRequirementsNV)gdpa(dev, "vkGetGeneratedCommandsMemoryRequirementsNV");
    table->CmdPreprocessGeneratedCommandsNV = (PFN_vkCmdPreprocessGeneratedCommandsNV)gdpa(dev, "vkCmdPreprocessGeneratedCommandsNV");
    table->CmdExecuteGeneratedCommandsNV = (PFN_vkCmdExecuteGeneratedCommandsNV)gdpa(dev, "vkCmdExecuteGeneratedCommandsNV");
    table->CmdBindPipelineShaderGroupNV = (PFN_vkCmdBindPipelineShaderGroupNV)gdpa(dev, "vkCmdBindPipelineShaderGroupNV");
    table->CreateIndirectCommandsLayoutNV = (PFN_vkCreateIndirectCommandsLayoutNV)gdpa(dev, "vkCreateIndirectCommandsLayoutNV");
    table->DestroyIndirectCommandsLayoutNV = (PFN_vkDestroyIndirectCommandsLayoutNV)gdpa(dev, "vkDestroyIndirectCommandsLayoutNV");

    // ---- VK_EXT_depth_bias_control extension commands
    table->CmdSetDepthBias2EXT = (PFN_vkCmdSetDepthBias2EXT)gdpa(dev, "vkCmdSetDepthBias2EXT");

    // ---- VK_EXT_private_data extension commands
    table->CreatePrivateDataSlotEXT = (PFN_vkCreatePrivateDataSlotEXT)gdpa(dev, "vkCreatePrivateDataSlotEXT");
    table->DestroyPrivateDataSlotEXT = (PFN_vkDestroyPrivateDataSlotEXT)gdpa(dev, "vkDestroyPrivateDataSlotEXT");
    table->SetPrivateDataEXT = (PFN_vkSetPrivateDataEXT)gdpa(dev, "vkSetPrivateDataEXT");
    table->GetPrivateDataEXT = (PFN_vkGetPrivateDataEXT)gdpa(dev, "vkGetPrivateDataEXT");

    // ---- VK_QCOM_queue_perf_hint extension commands
    table->QueueSetPerfHintQCOM = (PFN_vkQueueSetPerfHintQCOM)gdpa(dev, "vkQueueSetPerfHintQCOM");

    // ---- VK_NV_cuda_kernel_launch extension commands
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CreateCudaModuleNV = (PFN_vkCreateCudaModuleNV)gdpa(dev, "vkCreateCudaModuleNV");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->GetCudaModuleCacheNV = (PFN_vkGetCudaModuleCacheNV)gdpa(dev, "vkGetCudaModuleCacheNV");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CreateCudaFunctionNV = (PFN_vkCreateCudaFunctionNV)gdpa(dev, "vkCreateCudaFunctionNV");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->DestroyCudaModuleNV = (PFN_vkDestroyCudaModuleNV)gdpa(dev, "vkDestroyCudaModuleNV");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->DestroyCudaFunctionNV = (PFN_vkDestroyCudaFunctionNV)gdpa(dev, "vkDestroyCudaFunctionNV");
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    table->CmdCudaLaunchKernelNV = (PFN_vkCmdCudaLaunchKernelNV)gdpa(dev, "vkCmdCudaLaunchKernelNV");
#endif // VK_ENABLE_BETA_EXTENSIONS

    // ---- VK_QCOM_tile_shading extension commands
    table->CmdDispatchTileQCOM = (PFN_vkCmdDispatchTileQCOM)gdpa(dev, "vkCmdDispatchTileQCOM");
    table->CmdBeginPerTileExecutionQCOM = (PFN_vkCmdBeginPerTileExecutionQCOM)gdpa(dev, "vkCmdBeginPerTileExecutionQCOM");
    table->CmdEndPerTileExecutionQCOM = (PFN_vkCmdEndPerTileExecutionQCOM)gdpa(dev, "vkCmdEndPerTileExecutionQCOM");

    // ---- VK_NV_low_latency extension commands
    table->SetLatencySleepModeLegacyNV = (PFN_vkSetLatencySleepModeLegacyNV)gdpa(dev, "vkSetLatencySleepModeLegacyNV");
    table->LatencySleepLegacyNV = (PFN_vkLatencySleepLegacyNV)gdpa(dev, "vkLatencySleepLegacyNV");
    table->SetLatencyMarkerLegacyNV = (PFN_vkSetLatencyMarkerLegacyNV)gdpa(dev, "vkSetLatencyMarkerLegacyNV");
    table->GetLatencyTimingsLegacyNV = (PFN_vkGetLatencyTimingsLegacyNV)gdpa(dev, "vkGetLatencyTimingsLegacyNV");
    table->QueueNotifyOutOfBandLegacyNV = (PFN_vkQueueNotifyOutOfBandLegacyNV)gdpa(dev, "vkQueueNotifyOutOfBandLegacyNV");
    table->GetSleepStatusLegacyNV = (PFN_vkGetSleepStatusLegacyNV)gdpa(dev, "vkGetSleepStatusLegacyNV");
    table->ShutdownLatencyDeviceLegacyNV = (PFN_vkShutdownLatencyDeviceLegacyNV)gdpa(dev, "vkShutdownLatencyDeviceLegacyNV");

    // ---- VK_EXT_metal_objects extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    table->ExportMetalObjectsEXT = (PFN_vkExportMetalObjectsEXT)gdpa(dev, "vkExportMetalObjectsEXT");
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_descriptor_buffer extension commands
    table->GetDescriptorSetLayoutSizeEXT = (PFN_vkGetDescriptorSetLayoutSizeEXT)gdpa(dev, "vkGetDescriptorSetLayoutSizeEXT");
    table->GetDescriptorSetLayoutBindingOffsetEXT = (PFN_vkGetDescriptorSetLayoutBindingOffsetEXT)gdpa(dev, "vkGetDescriptorSetLayoutBindingOffsetEXT");
    table->GetDescriptorEXT = (PFN_vkGetDescriptorEXT)gdpa(dev, "vkGetDescriptorEXT");
    table->CmdBindDescriptorBuffersEXT = (PFN_vkCmdBindDescriptorBuffersEXT)gdpa(dev, "vkCmdBindDescriptorBuffersEXT");
    table->CmdSetDescriptorBufferOffsetsEXT = (PFN_vkCmdSetDescriptorBufferOffsetsEXT)gdpa(dev, "vkCmdSetDescriptorBufferOffsetsEXT");
    table->CmdBindDescriptorBufferEmbeddedSamplersEXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT)gdpa(dev, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT");
    table->GetBufferOpaqueCaptureDescriptorDataEXT = (PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT)gdpa(dev, "vkGetBufferOpaqueCaptureDescriptorDataEXT");
    table->GetImageOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageOpaqueCaptureDescriptorDataEXT)gdpa(dev, "vkGetImageOpaqueCaptureDescriptorDataEXT");
    table->GetImageViewOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT)gdpa(dev, "vkGetImageViewOpaqueCaptureDescriptorDataEXT");
    table->GetSamplerOpaqueCaptureDescriptorDataEXT = (PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT)gdpa(dev, "vkGetSamplerOpaqueCaptureDescriptorDataEXT");
    table->GetAccelerationStructureOpaqueCaptureDescriptorDataEXT = (PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT)gdpa(dev, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT");

    // ---- VK_NV_fragment_shading_rate_enums extension commands
    table->CmdSetFragmentShadingRateEnumNV = (PFN_vkCmdSetFragmentShadingRateEnumNV)gdpa(dev, "vkCmdSetFragmentShadingRateEnumNV");

    // ---- VK_EXT_device_fault extension commands
    table->GetDeviceFaultInfoEXT = (PFN_vkGetDeviceFaultInfoEXT)gdpa(dev, "vkGetDeviceFaultInfoEXT");

    // ---- VK_EXT_vertex_input_dynamic_state extension commands
    table->CmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)gdpa(dev, "vkCmdSetVertexInputEXT");

    // ---- VK_FUCHSIA_external_memory extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->GetMemoryZirconHandleFUCHSIA = (PFN_vkGetMemoryZirconHandleFUCHSIA)gdpa(dev, "vkGetMemoryZirconHandleFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->GetMemoryZirconHandlePropertiesFUCHSIA = (PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)gdpa(dev, "vkGetMemoryZirconHandlePropertiesFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_FUCHSIA_external_semaphore extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->ImportSemaphoreZirconHandleFUCHSIA = (PFN_vkImportSemaphoreZirconHandleFUCHSIA)gdpa(dev, "vkImportSemaphoreZirconHandleFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->GetSemaphoreZirconHandleFUCHSIA = (PFN_vkGetSemaphoreZirconHandleFUCHSIA)gdpa(dev, "vkGetSemaphoreZirconHandleFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_FUCHSIA_buffer_collection extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->CreateBufferCollectionFUCHSIA = (PFN_vkCreateBufferCollectionFUCHSIA)gdpa(dev, "vkCreateBufferCollectionFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->SetBufferCollectionImageConstraintsFUCHSIA = (PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)gdpa(dev, "vkSetBufferCollectionImageConstraintsFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->SetBufferCollectionBufferConstraintsFUCHSIA = (PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)gdpa(dev, "vkSetBufferCollectionBufferConstraintsFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->DestroyBufferCollectionFUCHSIA = (PFN_vkDestroyBufferCollectionFUCHSIA)gdpa(dev, "vkDestroyBufferCollectionFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->GetBufferCollectionPropertiesFUCHSIA = (PFN_vkGetBufferCollectionPropertiesFUCHSIA)gdpa(dev, "vkGetBufferCollectionPropertiesFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_HUAWEI_subpass_shading extension commands
    table->GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = (PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)gdpa(dev, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI");
    table->CmdSubpassShadingHUAWEI = (PFN_vkCmdSubpassShadingHUAWEI)gdpa(dev, "vkCmdSubpassShadingHUAWEI");

    // ---- VK_HUAWEI_invocation_mask extension commands
    table->CmdBindInvocationMaskHUAWEI = (PFN_vkCmdBindInvocationMaskHUAWEI)gdpa(dev, "vkCmdBindInvocationMaskHUAWEI");

    // ---- VK_NV_external_memory_rdma extension commands
    table->GetMemoryRemoteAddressNV = (PFN_vkGetMemoryRemoteAddressNV)gdpa(dev, "vkGetMemoryRemoteAddressNV");

    // ---- VK_EXT_pipeline_properties extension commands
    table->GetPipelinePropertiesEXT = (PFN_vkGetPipelinePropertiesEXT)gdpa(dev, "vkGetPipelinePropertiesEXT");

    // ---- VK_EXT_extended_dynamic_state2 extension commands
    table->CmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)gdpa(dev, "vkCmdSetPatchControlPointsEXT");
    table->CmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)gdpa(dev, "vkCmdSetRasterizerDiscardEnableEXT");
    table->CmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)gdpa(dev, "vkCmdSetDepthBiasEnableEXT");
    table->CmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)gdpa(dev, "vkCmdSetLogicOpEXT");
    table->CmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)gdpa(dev, "vkCmdSetPrimitiveRestartEnableEXT");

    // ---- VK_EXT_color_write_enable extension commands
    table->CmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)gdpa(dev, "vkCmdSetColorWriteEnableEXT");

    // ---- VK_EXT_multi_draw extension commands
    table->CmdDrawMultiEXT = (PFN_vkCmdDrawMultiEXT)gdpa(dev, "vkCmdDrawMultiEXT");
    table->CmdDrawMultiIndexedEXT = (PFN_vkCmdDrawMultiIndexedEXT)gdpa(dev, "vkCmdDrawMultiIndexedEXT");

    // ---- VK_EXT_opacity_micromap extension commands
    table->CreateMicromapEXT = (PFN_vkCreateMicromapEXT)gdpa(dev, "vkCreateMicromapEXT");
    table->DestroyMicromapEXT = (PFN_vkDestroyMicromapEXT)gdpa(dev, "vkDestroyMicromapEXT");
    table->CmdBuildMicromapsEXT = (PFN_vkCmdBuildMicromapsEXT)gdpa(dev, "vkCmdBuildMicromapsEXT");
    table->BuildMicromapsEXT = (PFN_vkBuildMicromapsEXT)gdpa(dev, "vkBuildMicromapsEXT");
    table->CopyMicromapEXT = (PFN_vkCopyMicromapEXT)gdpa(dev, "vkCopyMicromapEXT");
    table->CopyMicromapToMemoryEXT = (PFN_vkCopyMicromapToMemoryEXT)gdpa(dev, "vkCopyMicromapToMemoryEXT");
    table->CopyMemoryToMicromapEXT = (PFN_vkCopyMemoryToMicromapEXT)gdpa(dev, "vkCopyMemoryToMicromapEXT");
    table->WriteMicromapsPropertiesEXT = (PFN_vkWriteMicromapsPropertiesEXT)gdpa(dev, "vkWriteMicromapsPropertiesEXT");
    table->CmdCopyMicromapEXT = (PFN_vkCmdCopyMicromapEXT)gdpa(dev, "vkCmdCopyMicromapEXT");
    table->CmdCopyMicromapToMemoryEXT = (PFN_vkCmdCopyMicromapToMemoryEXT)gdpa(dev, "vkCmdCopyMicromapToMemoryEXT");
    table->CmdCopyMemoryToMicromapEXT = (PFN_vkCmdCopyMemoryToMicromapEXT)gdpa(dev, "vkCmdCopyMemoryToMicromapEXT");
    table->CmdWriteMicromapsPropertiesEXT = (PFN_vkCmdWriteMicromapsPropertiesEXT)gdpa(dev, "vkCmdWriteMicromapsPropertiesEXT");
    table->GetDeviceMicromapCompatibilityEXT = (PFN_vkGetDeviceMicromapCompatibilityEXT)gdpa(dev, "vkGetDeviceMicromapCompatibilityEXT");
    table->GetMicromapBuildSizesEXT = (PFN_vkGetMicromapBuildSizesEXT)gdpa(dev, "vkGetMicromapBuildSizesEXT");

    // ---- VK_HUAWEI_cluster_culling_shader extension commands
    table->CmdDrawClusterHUAWEI = (PFN_vkCmdDrawClusterHUAWEI)gdpa(dev, "vkCmdDrawClusterHUAWEI");
    table->CmdDrawClusterIndirectHUAWEI = (PFN_vkCmdDrawClusterIndirectHUAWEI)gdpa(dev, "vkCmdDrawClusterIndirectHUAWEI");

    // ---- VK_EXT_pageable_device_local_memory extension commands
    table->SetDeviceMemoryPriorityEXT = (PFN_vkSetDeviceMemoryPriorityEXT)gdpa(dev, "vkSetDeviceMemoryPriorityEXT");

    // ---- VK_ARM_scheduling_controls extension commands
    table->CmdSetDispatchParametersARM = (PFN_vkCmdSetDispatchParametersARM)gdpa(dev, "vkCmdSetDispatchParametersARM");

    // ---- VK_VALVE_descriptor_set_host_mapping extension commands
    table->GetDescriptorSetLayoutHostMappingInfoVALVE = (PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE)gdpa(dev, "vkGetDescriptorSetLayoutHostMappingInfoVALVE");
    table->GetDescriptorSetHostMappingVALVE = (PFN_vkGetDescriptorSetHostMappingVALVE)gdpa(dev, "vkGetDescriptorSetHostMappingVALVE");

    // ---- VK_NV_copy_memory_indirect extension commands
    table->CmdCopyMemoryIndirectNV = (PFN_vkCmdCopyMemoryIndirectNV)gdpa(dev, "vkCmdCopyMemoryIndirectNV");
    table->CmdCopyMemoryToImageIndirectNV = (PFN_vkCmdCopyMemoryToImageIndirectNV)gdpa(dev, "vkCmdCopyMemoryToImageIndirectNV");

    // ---- VK_NV_memory_decompression extension commands
    table->CmdDecompressMemoryNV = (PFN_vkCmdDecompressMemoryNV)gdpa(dev, "vkCmdDecompressMemoryNV");
    table->CmdDecompressMemoryIndirectCountNV = (PFN_vkCmdDecompressMemoryIndirectCountNV)gdpa(dev, "vkCmdDecompressMemoryIndirectCountNV");

    // ---- VK_NV_device_generated_commands_compute extension commands
    table->GetPipelineIndirectMemoryRequirementsNV = (PFN_vkGetPipelineIndirectMemoryRequirementsNV)gdpa(dev, "vkGetPipelineIndirectMemoryRequirementsNV");
    table->CmdUpdatePipelineIndirectBufferNV = (PFN_vkCmdUpdatePipelineIndirectBufferNV)gdpa(dev, "vkCmdUpdatePipelineIndirectBufferNV");
    table->GetPipelineIndirectDeviceAddressNV = (PFN_vkGetPipelineIndirectDeviceAddressNV)gdpa(dev, "vkGetPipelineIndirectDeviceAddressNV");

    // ---- VK_OHOS_external_memory extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    table->GetNativeBufferPropertiesOHOS = (PFN_vkGetNativeBufferPropertiesOHOS)gdpa(dev, "vkGetNativeBufferPropertiesOHOS");
#endif // VK_USE_PLATFORM_OHOS
#if defined(VK_USE_PLATFORM_OHOS)
    table->GetMemoryNativeBufferOHOS = (PFN_vkGetMemoryNativeBufferOHOS)gdpa(dev, "vkGetMemoryNativeBufferOHOS");
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_EXT_extended_dynamic_state3 extension commands
    table->CmdSetDepthClampEnableEXT = (PFN_vkCmdSetDepthClampEnableEXT)gdpa(dev, "vkCmdSetDepthClampEnableEXT");
    table->CmdSetPolygonModeEXT = (PFN_vkCmdSetPolygonModeEXT)gdpa(dev, "vkCmdSetPolygonModeEXT");
    table->CmdSetRasterizationSamplesEXT = (PFN_vkCmdSetRasterizationSamplesEXT)gdpa(dev, "vkCmdSetRasterizationSamplesEXT");
    table->CmdSetSampleMaskEXT = (PFN_vkCmdSetSampleMaskEXT)gdpa(dev, "vkCmdSetSampleMaskEXT");
    table->CmdSetAlphaToCoverageEnableEXT = (PFN_vkCmdSetAlphaToCoverageEnableEXT)gdpa(dev, "vkCmdSetAlphaToCoverageEnableEXT");
    table->CmdSetAlphaToOneEnableEXT = (PFN_vkCmdSetAlphaToOneEnableEXT)gdpa(dev, "vkCmdSetAlphaToOneEnableEXT");
    table->CmdSetLogicOpEnableEXT = (PFN_vkCmdSetLogicOpEnableEXT)gdpa(dev, "vkCmdSetLogicOpEnableEXT");
    table->CmdSetColorBlendEnableEXT = (PFN_vkCmdSetColorBlendEnableEXT)gdpa(dev, "vkCmdSetColorBlendEnableEXT");
    table->CmdSetColorBlendEquationEXT = (PFN_vkCmdSetColorBlendEquationEXT)gdpa(dev, "vkCmdSetColorBlendEquationEXT");
    table->CmdSetColorWriteMaskEXT = (PFN_vkCmdSetColorWriteMaskEXT)gdpa(dev, "vkCmdSetColorWriteMaskEXT");
    table->CmdSetTessellationDomainOriginEXT = (PFN_vkCmdSetTessellationDomainOriginEXT)gdpa(dev, "vkCmdSetTessellationDomainOriginEXT");
    table->CmdSetRasterizationStreamEXT = (PFN_vkCmdSetRasterizationStreamEXT)gdpa(dev, "vkCmdSetRasterizationStreamEXT");
    table->CmdSetConservativeRasterizationModeEXT = (PFN_vkCmdSetConservativeRasterizationModeEXT)gdpa(dev, "vkCmdSetConservativeRasterizationModeEXT");
    table->CmdSetExtraPrimitiveOverestimationSizeEXT = (PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT)gdpa(dev, "vkCmdSetExtraPrimitiveOverestimationSizeEXT");
    table->CmdSetDepthClipEnableEXT = (PFN_vkCmdSetDepthClipEnableEXT)gdpa(dev, "vkCmdSetDepthClipEnableEXT");
    table->CmdSetSampleLocationsEnableEXT = (PFN_vkCmdSetSampleLocationsEnableEXT)gdpa(dev, "vkCmdSetSampleLocationsEnableEXT");
    table->CmdSetColorBlendAdvancedEXT = (PFN_vkCmdSetColorBlendAdvancedEXT)gdpa(dev, "vkCmdSetColorBlendAdvancedEXT");
    table->CmdSetProvokingVertexModeEXT = (PFN_vkCmdSetProvokingVertexModeEXT)gdpa(dev, "vkCmdSetProvokingVertexModeEXT");
    table->CmdSetLineRasterizationModeEXT = (PFN_vkCmdSetLineRasterizationModeEXT)gdpa(dev, "vkCmdSetLineRasterizationModeEXT");
    table->CmdSetLineStippleEnableEXT = (PFN_vkCmdSetLineStippleEnableEXT)gdpa(dev, "vkCmdSetLineStippleEnableEXT");
    table->CmdSetDepthClipNegativeOneToOneEXT = (PFN_vkCmdSetDepthClipNegativeOneToOneEXT)gdpa(dev, "vkCmdSetDepthClipNegativeOneToOneEXT");
    table->CmdSetViewportWScalingEnableNV = (PFN_vkCmdSetViewportWScalingEnableNV)gdpa(dev, "vkCmdSetViewportWScalingEnableNV");
    table->CmdSetViewportSwizzleNV = (PFN_vkCmdSetViewportSwizzleNV)gdpa(dev, "vkCmdSetViewportSwizzleNV");
    table->CmdSetCoverageToColorEnableNV = (PFN_vkCmdSetCoverageToColorEnableNV)gdpa(dev, "vkCmdSetCoverageToColorEnableNV");
    table->CmdSetCoverageToColorLocationNV = (PFN_vkCmdSetCoverageToColorLocationNV)gdpa(dev, "vkCmdSetCoverageToColorLocationNV");
    table->CmdSetCoverageModulationModeNV = (PFN_vkCmdSetCoverageModulationModeNV)gdpa(dev, "vkCmdSetCoverageModulationModeNV");
    table->CmdSetCoverageModulationTableEnableNV = (PFN_vkCmdSetCoverageModulationTableEnableNV)gdpa(dev, "vkCmdSetCoverageModulationTableEnableNV");
    table->CmdSetCoverageModulationTableNV = (PFN_vkCmdSetCoverageModulationTableNV)gdpa(dev, "vkCmdSetCoverageModulationTableNV");
    table->CmdSetShadingRateImageEnableNV = (PFN_vkCmdSetShadingRateImageEnableNV)gdpa(dev, "vkCmdSetShadingRateImageEnableNV");
    table->CmdSetRepresentativeFragmentTestEnableNV = (PFN_vkCmdSetRepresentativeFragmentTestEnableNV)gdpa(dev, "vkCmdSetRepresentativeFragmentTestEnableNV");
    table->CmdSetCoverageReductionModeNV = (PFN_vkCmdSetCoverageReductionModeNV)gdpa(dev, "vkCmdSetCoverageReductionModeNV");

    // ---- VK_ARM_tensors extension commands
    table->CreateTensorARM = (PFN_vkCreateTensorARM)gdpa(dev, "vkCreateTensorARM");
    table->DestroyTensorARM = (PFN_vkDestroyTensorARM)gdpa(dev, "vkDestroyTensorARM");
    table->CreateTensorViewARM = (PFN_vkCreateTensorViewARM)gdpa(dev, "vkCreateTensorViewARM");
    table->DestroyTensorViewARM = (PFN_vkDestroyTensorViewARM)gdpa(dev, "vkDestroyTensorViewARM");
    table->GetTensorMemoryRequirementsARM = (PFN_vkGetTensorMemoryRequirementsARM)gdpa(dev, "vkGetTensorMemoryRequirementsARM");
    table->BindTensorMemoryARM = (PFN_vkBindTensorMemoryARM)gdpa(dev, "vkBindTensorMemoryARM");
    table->GetDeviceTensorMemoryRequirementsARM = (PFN_vkGetDeviceTensorMemoryRequirementsARM)gdpa(dev, "vkGetDeviceTensorMemoryRequirementsARM");
    table->CmdCopyTensorARM = (PFN_vkCmdCopyTensorARM)gdpa(dev, "vkCmdCopyTensorARM");
    table->GetTensorOpaqueCaptureDescriptorDataARM = (PFN_vkGetTensorOpaqueCaptureDescriptorDataARM)gdpa(dev, "vkGetTensorOpaqueCaptureDescriptorDataARM");
    table->GetTensorViewOpaqueCaptureDescriptorDataARM = (PFN_vkGetTensorViewOpaqueCaptureDescriptorDataARM)gdpa(dev, "vkGetTensorViewOpaqueCaptureDescriptorDataARM");

    // ---- VK_EXT_shader_module_identifier extension commands
    table->GetShaderModuleIdentifierEXT = (PFN_vkGetShaderModuleIdentifierEXT)gdpa(dev, "vkGetShaderModuleIdentifierEXT");
    table->GetShaderModuleCreateInfoIdentifierEXT = (PFN_vkGetShaderModuleCreateInfoIdentifierEXT)gdpa(dev, "vkGetShaderModuleCreateInfoIdentifierEXT");

    // ---- VK_NV_optical_flow extension commands
    table->CreateOpticalFlowSessionNV = (PFN_vkCreateOpticalFlowSessionNV)gdpa(dev, "vkCreateOpticalFlowSessionNV");
    table->DestroyOpticalFlowSessionNV = (PFN_vkDestroyOpticalFlowSessionNV)gdpa(dev, "vkDestroyOpticalFlowSessionNV");
    table->BindOpticalFlowSessionImageNV = (PFN_vkBindOpticalFlowSessionImageNV)gdpa(dev, "vkBindOpticalFlowSessionImageNV");
    table->CmdOpticalFlowExecuteNV = (PFN_vkCmdOpticalFlowExecuteNV)gdpa(dev, "vkCmdOpticalFlowExecuteNV");

    // ---- VK_AMD_anti_lag extension commands
    table->AntiLagUpdateAMD = (PFN_vkAntiLagUpdateAMD)gdpa(dev, "vkAntiLagUpdateAMD");

    // ---- VK_EXT_shader_object extension commands
    table->CreateShadersEXT = (PFN_vkCreateShadersEXT)gdpa(dev, "vkCreateShadersEXT");
    table->DestroyShaderEXT = (PFN_vkDestroyShaderEXT)gdpa(dev, "vkDestroyShaderEXT");
    table->GetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT)gdpa(dev, "vkGetShaderBinaryDataEXT");
    table->CmdBindShadersEXT = (PFN_vkCmdBindShadersEXT)gdpa(dev, "vkCmdBindShadersEXT");
    table->CmdSetDepthClampRangeEXT = (PFN_vkCmdSetDepthClampRangeEXT)gdpa(dev, "vkCmdSetDepthClampRangeEXT");

    // ---- VK_QCOM_tile_properties extension commands
    table->GetFramebufferTilePropertiesQCOM = (PFN_vkGetFramebufferTilePropertiesQCOM)gdpa(dev, "vkGetFramebufferTilePropertiesQCOM");
    table->GetDynamicRenderingTilePropertiesQCOM = (PFN_vkGetDynamicRenderingTilePropertiesQCOM)gdpa(dev, "vkGetDynamicRenderingTilePropertiesQCOM");

    // ---- VK_NV_cooperative_vector extension commands
    table->ConvertCooperativeVectorMatrixNV = (PFN_vkConvertCooperativeVectorMatrixNV)gdpa(dev, "vkConvertCooperativeVectorMatrixNV");
    table->CmdConvertCooperativeVectorMatrixNV = (PFN_vkCmdConvertCooperativeVectorMatrixNV)gdpa(dev, "vkCmdConvertCooperativeVectorMatrixNV");

    // ---- VK_NV_low_latency2 extension commands
    table->SetLatencySleepModeNV = (PFN_vkSetLatencySleepModeNV)gdpa(dev, "vkSetLatencySleepModeNV");
    table->LatencySleepNV = (PFN_vkLatencySleepNV)gdpa(dev, "vkLatencySleepNV");
    table->SetLatencyMarkerNV = (PFN_vkSetLatencyMarkerNV)gdpa(dev, "vkSetLatencyMarkerNV");
    table->GetLatencyTimingsNV = (PFN_vkGetLatencyTimingsNV)gdpa(dev, "vkGetLatencyTimingsNV");
    table->QueueNotifyOutOfBandNV = (PFN_vkQueueNotifyOutOfBandNV)gdpa(dev, "vkQueueNotifyOutOfBandNV");

    // ---- VK_ARM_data_graph extension commands
    table->CreateDataGraphPipelinesARM = (PFN_vkCreateDataGraphPipelinesARM)gdpa(dev, "vkCreateDataGraphPipelinesARM");
    table->CreateDataGraphPipelineSessionARM = (PFN_vkCreateDataGraphPipelineSessionARM)gdpa(dev, "vkCreateDataGraphPipelineSessionARM");
    table->GetDataGraphPipelineSessionBindPointRequirementsARM = (PFN_vkGetDataGraphPipelineSessionBindPointRequirementsARM)gdpa(dev, "vkGetDataGraphPipelineSessionBindPointRequirementsARM");
    table->GetDataGraphPipelineSessionMemoryRequirementsARM = (PFN_vkGetDataGraphPipelineSessionMemoryRequirementsARM)gdpa(dev, "vkGetDataGraphPipelineSessionMemoryRequirementsARM");
    table->BindDataGraphPipelineSessionMemoryARM = (PFN_vkBindDataGraphPipelineSessionMemoryARM)gdpa(dev, "vkBindDataGraphPipelineSessionMemoryARM");
    table->DestroyDataGraphPipelineSessionARM = (PFN_vkDestroyDataGraphPipelineSessionARM)gdpa(dev, "vkDestroyDataGraphPipelineSessionARM");
    table->CmdDispatchDataGraphARM = (PFN_vkCmdDispatchDataGraphARM)gdpa(dev, "vkCmdDispatchDataGraphARM");
    table->GetDataGraphPipelineAvailablePropertiesARM = (PFN_vkGetDataGraphPipelineAvailablePropertiesARM)gdpa(dev, "vkGetDataGraphPipelineAvailablePropertiesARM");
    table->GetDataGraphPipelinePropertiesARM = (PFN_vkGetDataGraphPipelinePropertiesARM)gdpa(dev, "vkGetDataGraphPipelinePropertiesARM");

    // ---- VK_EXT_attachment_feedback_loop_dynamic_state extension commands
    table->CmdSetAttachmentFeedbackLoopEnableEXT = (PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT)gdpa(dev, "vkCmdSetAttachmentFeedbackLoopEnableEXT");

    // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    table->GetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX)gdpa(dev, "vkGetScreenBufferPropertiesQNX");
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_QCOM_tile_memory_heap extension commands
    table->CmdBindTileMemoryQCOM = (PFN_vkCmdBindTileMemoryQCOM)gdpa(dev, "vkCmdBindTileMemoryQCOM");

    // ---- VK_EXT_memory_decompression extension commands
    table->CmdDecompressMemoryEXT = (PFN_vkCmdDecompressMemoryEXT)gdpa(dev, "vkCmdDecompressMemoryEXT");
    table->CmdDecompressMemoryIndirectCountEXT = (PFN_vkCmdDecompressMemoryIndirectCountEXT)gdpa(dev, "vkCmdDecompressMemoryIndirectCountEXT");

    // ---- VK_NV_external_compute_queue extension commands
    table->CreateExternalComputeQueueNV = (PFN_vkCreateExternalComputeQueueNV)gdpa(dev, "vkCreateExternalComputeQueueNV");
    table->DestroyExternalComputeQueueNV = (PFN_vkDestroyExternalComputeQueueNV)gdpa(dev, "vkDestroyExternalComputeQueueNV");
    table->GetExternalComputeQueueDataNV = (PFN_vkGetExternalComputeQueueDataNV)gdpa(dev, "vkGetExternalComputeQueueDataNV");

    // ---- VK_NV_cluster_acceleration_structure extension commands
    table->GetClusterAccelerationStructureBuildSizesNV = (PFN_vkGetClusterAccelerationStructureBuildSizesNV)gdpa(dev, "vkGetClusterAccelerationStructureBuildSizesNV");
    table->CmdBuildClusterAccelerationStructureIndirectNV = (PFN_vkCmdBuildClusterAccelerationStructureIndirectNV)gdpa(dev, "vkCmdBuildClusterAccelerationStructureIndirectNV");

    // ---- VK_NV_partitioned_acceleration_structure extension commands
    table->GetPartitionedAccelerationStructuresBuildSizesNV = (PFN_vkGetPartitionedAccelerationStructuresBuildSizesNV)gdpa(dev, "vkGetPartitionedAccelerationStructuresBuildSizesNV");
    table->CmdBuildPartitionedAccelerationStructuresNV = (PFN_vkCmdBuildPartitionedAccelerationStructuresNV)gdpa(dev, "vkCmdBuildPartitionedAccelerationStructuresNV");

    // ---- VK_EXT_device_generated_commands extension commands
    table->GetGeneratedCommandsMemoryRequirementsEXT = (PFN_vkGetGeneratedCommandsMemoryRequirementsEXT)gdpa(dev, "vkGetGeneratedCommandsMemoryRequirementsEXT");
    table->CmdPreprocessGeneratedCommandsEXT = (PFN_vkCmdPreprocessGeneratedCommandsEXT)gdpa(dev, "vkCmdPreprocessGeneratedCommandsEXT");
    table->CmdExecuteGeneratedCommandsEXT = (PFN_vkCmdExecuteGeneratedCommandsEXT)gdpa(dev, "vkCmdExecuteGeneratedCommandsEXT");
    table->CreateIndirectCommandsLayoutEXT = (PFN_vkCreateIndirectCommandsLayoutEXT)gdpa(dev, "vkCreateIndirectCommandsLayoutEXT");
    table->DestroyIndirectCommandsLayoutEXT = (PFN_vkDestroyIndirectCommandsLayoutEXT)gdpa(dev, "vkDestroyIndirectCommandsLayoutEXT");
    table->CreateIndirectExecutionSetEXT = (PFN_vkCreateIndirectExecutionSetEXT)gdpa(dev, "vkCreateIndirectExecutionSetEXT");
    table->DestroyIndirectExecutionSetEXT = (PFN_vkDestroyIndirectExecutionSetEXT)gdpa(dev, "vkDestroyIndirectExecutionSetEXT");
    table->UpdateIndirectExecutionSetPipelineEXT = (PFN_vkUpdateIndirectExecutionSetPipelineEXT)gdpa(dev, "vkUpdateIndirectExecutionSetPipelineEXT");
    table->UpdateIndirectExecutionSetShaderEXT = (PFN_vkUpdateIndirectExecutionSetShaderEXT)gdpa(dev, "vkUpdateIndirectExecutionSetShaderEXT");

    // ---- VK_EXT_external_memory_metal extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    table->GetMemoryMetalHandleEXT = (PFN_vkGetMemoryMetalHandleEXT)gdpa(dev, "vkGetMemoryMetalHandleEXT");
#endif // VK_USE_PLATFORM_METAL_EXT
#if defined(VK_USE_PLATFORM_METAL_EXT)
    table->GetMemoryMetalHandlePropertiesEXT = (PFN_vkGetMemoryMetalHandlePropertiesEXT)gdpa(dev, "vkGetMemoryMetalHandlePropertiesEXT");
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_ARM_shader_instrumentation extension commands
    table->CreateShaderInstrumentationARM = (PFN_vkCreateShaderInstrumentationARM)gdpa(dev, "vkCreateShaderInstrumentationARM");
    table->DestroyShaderInstrumentationARM = (PFN_vkDestroyShaderInstrumentationARM)gdpa(dev, "vkDestroyShaderInstrumentationARM");
    table->CmdBeginShaderInstrumentationARM = (PFN_vkCmdBeginShaderInstrumentationARM)gdpa(dev, "vkCmdBeginShaderInstrumentationARM");
    table->CmdEndShaderInstrumentationARM = (PFN_vkCmdEndShaderInstrumentationARM)gdpa(dev, "vkCmdEndShaderInstrumentationARM");
    table->GetShaderInstrumentationValuesARM = (PFN_vkGetShaderInstrumentationValuesARM)gdpa(dev, "vkGetShaderInstrumentationValuesARM");
    table->ClearShaderInstrumentationMetricsARM = (PFN_vkClearShaderInstrumentationMetricsARM)gdpa(dev, "vkClearShaderInstrumentationMetricsARM");

    // ---- VK_EXT_fragment_density_map_offset extension commands
    table->CmdEndRendering2EXT = (PFN_vkCmdEndRendering2EXT)gdpa(dev, "vkCmdEndRendering2EXT");

    // ---- VK_EXT_custom_resolve extension commands
    table->CmdBeginCustomResolveEXT = (PFN_vkCmdBeginCustomResolveEXT)gdpa(dev, "vkCmdBeginCustomResolveEXT");

    // ---- VK_NV_compute_occupancy_priority extension commands
    table->CmdSetComputeOccupancyPriorityNV = (PFN_vkCmdSetComputeOccupancyPriorityNV)gdpa(dev, "vkCmdSetComputeOccupancyPriorityNV");

    // ---- VK_EXT_primitive_restart_index extension commands
    table->CmdSetPrimitiveRestartIndexEXT = (PFN_vkCmdSetPrimitiveRestartIndexEXT)gdpa(dev, "vkCmdSetPrimitiveRestartIndexEXT");

    // ---- VK_KHR_acceleration_structure extension commands
    table->CreateAccelerationStructureKHR = (PFN_vkCreateAccelerationStructureKHR)gdpa(dev, "vkCreateAccelerationStructureKHR");
    table->DestroyAccelerationStructureKHR = (PFN_vkDestroyAccelerationStructureKHR)gdpa(dev, "vkDestroyAccelerationStructureKHR");
    table->CmdBuildAccelerationStructuresKHR = (PFN_vkCmdBuildAccelerationStructuresKHR)gdpa(dev, "vkCmdBuildAccelerationStructuresKHR");
    table->CmdBuildAccelerationStructuresIndirectKHR = (PFN_vkCmdBuildAccelerationStructuresIndirectKHR)gdpa(dev, "vkCmdBuildAccelerationStructuresIndirectKHR");
    table->BuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)gdpa(dev, "vkBuildAccelerationStructuresKHR");
    table->CopyAccelerationStructureKHR = (PFN_vkCopyAccelerationStructureKHR)gdpa(dev, "vkCopyAccelerationStructureKHR");
    table->CopyAccelerationStructureToMemoryKHR = (PFN_vkCopyAccelerationStructureToMemoryKHR)gdpa(dev, "vkCopyAccelerationStructureToMemoryKHR");
    table->CopyMemoryToAccelerationStructureKHR = (PFN_vkCopyMemoryToAccelerationStructureKHR)gdpa(dev, "vkCopyMemoryToAccelerationStructureKHR");
    table->WriteAccelerationStructuresPropertiesKHR = (PFN_vkWriteAccelerationStructuresPropertiesKHR)gdpa(dev, "vkWriteAccelerationStructuresPropertiesKHR");
    table->CmdCopyAccelerationStructureKHR = (PFN_vkCmdCopyAccelerationStructureKHR)gdpa(dev, "vkCmdCopyAccelerationStructureKHR");
    table->CmdCopyAccelerationStructureToMemoryKHR = (PFN_vkCmdCopyAccelerationStructureToMemoryKHR)gdpa(dev, "vkCmdCopyAccelerationStructureToMemoryKHR");
    table->CmdCopyMemoryToAccelerationStructureKHR = (PFN_vkCmdCopyMemoryToAccelerationStructureKHR)gdpa(dev, "vkCmdCopyMemoryToAccelerationStructureKHR");
    table->GetAccelerationStructureDeviceAddressKHR = (PFN_vkGetAccelerationStructureDeviceAddressKHR)gdpa(dev, "vkGetAccelerationStructureDeviceAddressKHR");
    table->CmdWriteAccelerationStructuresPropertiesKHR = (PFN_vkCmdWriteAccelerationStructuresPropertiesKHR)gdpa(dev, "vkCmdWriteAccelerationStructuresPropertiesKHR");
    table->GetDeviceAccelerationStructureCompatibilityKHR = (PFN_vkGetDeviceAccelerationStructureCompatibilityKHR)gdpa(dev, "vkGetDeviceAccelerationStructureCompatibilityKHR");
    table->GetAccelerationStructureBuildSizesKHR = (PFN_vkGetAccelerationStructureBuildSizesKHR)gdpa(dev, "vkGetAccelerationStructureBuildSizesKHR");

    // ---- VK_KHR_ray_tracing_pipeline extension commands
    table->CmdTraceRaysKHR = (PFN_vkCmdTraceRaysKHR)gdpa(dev, "vkCmdTraceRaysKHR");
    table->CreateRayTracingPipelinesKHR = (PFN_vkCreateRayTracingPipelinesKHR)gdpa(dev, "vkCreateRayTracingPipelinesKHR");
    table->GetRayTracingCaptureReplayShaderGroupHandlesKHR = (PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)gdpa(dev, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR");
    table->CmdTraceRaysIndirectKHR = (PFN_vkCmdTraceRaysIndirectKHR)gdpa(dev, "vkCmdTraceRaysIndirectKHR");
    table->GetRayTracingShaderGroupStackSizeKHR = (PFN_vkGetRayTracingShaderGroupStackSizeKHR)gdpa(dev, "vkGetRayTracingShaderGroupStackSizeKHR");
    table->CmdSetRayTracingPipelineStackSizeKHR = (PFN_vkCmdSetRayTracingPipelineStackSizeKHR)gdpa(dev, "vkCmdSetRayTracingPipelineStackSizeKHR");

    // ---- VK_EXT_mesh_shader extension commands
    table->CmdDrawMeshTasksEXT = (PFN_vkCmdDrawMeshTasksEXT)gdpa(dev, "vkCmdDrawMeshTasksEXT");
    table->CmdDrawMeshTasksIndirectEXT = (PFN_vkCmdDrawMeshTasksIndirectEXT)gdpa(dev, "vkCmdDrawMeshTasksIndirectEXT");
    table->CmdDrawMeshTasksIndirectCountEXT = (PFN_vkCmdDrawMeshTasksIndirectCountEXT)gdpa(dev, "vkCmdDrawMeshTasksIndirectCountEXT");
}

// Init Instance function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_instance_core_dispatch_table(VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa,
                                                                    VkInstance inst) {

    // ---- Core Vulkan 1.0 commands
    table->DestroyInstance = (PFN_vkDestroyInstance)gpa(inst, "vkDestroyInstance");
    table->EnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)gpa(inst, "vkEnumeratePhysicalDevices");
    table->GetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)gpa(inst, "vkGetPhysicalDeviceFeatures");
    table->GetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)gpa(inst, "vkGetPhysicalDeviceFormatProperties");
    table->GetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)gpa(inst, "vkGetPhysicalDeviceImageFormatProperties");
    table->GetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)gpa(inst, "vkGetPhysicalDeviceProperties");
    table->GetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)gpa(inst, "vkGetPhysicalDeviceQueueFamilyProperties");
    table->GetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)gpa(inst, "vkGetPhysicalDeviceMemoryProperties");
    table->GetInstanceProcAddr = gpa;
    table->EnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)gpa(inst, "vkEnumerateDeviceExtensionProperties");
    table->EnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)gpa(inst, "vkEnumerateDeviceLayerProperties");
    table->GetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)gpa(inst, "vkGetPhysicalDeviceSparseImageFormatProperties");

    // ---- Core Vulkan 1.1 commands
    table->EnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)gpa(inst, "vkEnumeratePhysicalDeviceGroups");
    table->GetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)gpa(inst, "vkGetPhysicalDeviceFeatures2");
    table->GetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)gpa(inst, "vkGetPhysicalDeviceProperties2");
    table->GetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)gpa(inst, "vkGetPhysicalDeviceFormatProperties2");
    table->GetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)gpa(inst, "vkGetPhysicalDeviceImageFormatProperties2");
    table->GetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)gpa(inst, "vkGetPhysicalDeviceQueueFamilyProperties2");
    table->GetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)gpa(inst, "vkGetPhysicalDeviceMemoryProperties2");
    table->GetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)gpa(inst, "vkGetPhysicalDeviceSparseImageFormatProperties2");
    table->GetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)gpa(inst, "vkGetPhysicalDeviceExternalBufferProperties");
    table->GetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)gpa(inst, "vkGetPhysicalDeviceExternalFenceProperties");
    table->GetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)gpa(inst, "vkGetPhysicalDeviceExternalSemaphoreProperties");

    // ---- Core Vulkan 1.3 commands
    table->GetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)gpa(inst, "vkGetPhysicalDeviceToolProperties");
}

// Init Instance function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_instance_extension_dispatch_table(VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa,
                                                                        VkInstance inst) {

    // ---- VK_KHR_surface extension commands
    table->DestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)gpa(inst, "vkDestroySurfaceKHR");
    table->GetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)gpa(inst, "vkGetPhysicalDeviceSurfaceSupportKHR");
    table->GetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)gpa(inst, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    table->GetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)gpa(inst, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    table->GetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)gpa(inst, "vkGetPhysicalDeviceSurfacePresentModesKHR");

    // ---- VK_KHR_swapchain extension commands
    table->GetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR)gpa(inst, "vkGetPhysicalDevicePresentRectanglesKHR");

    // ---- VK_KHR_display extension commands
    table->GetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)gpa(inst, "vkGetPhysicalDeviceDisplayPropertiesKHR");
    table->GetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)gpa(inst, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
    table->GetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)gpa(inst, "vkGetDisplayPlaneSupportedDisplaysKHR");
    table->GetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR)gpa(inst, "vkGetDisplayModePropertiesKHR");
    table->CreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR)gpa(inst, "vkCreateDisplayModeKHR");
    table->GetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR)gpa(inst, "vkGetDisplayPlaneCapabilitiesKHR");
    table->CreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR)gpa(inst, "vkCreateDisplayPlaneSurfaceKHR");

    // ---- VK_KHR_xlib_surface extension commands
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    table->CreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR)gpa(inst, "vkCreateXlibSurfaceKHR");
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    table->GetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)gpa(inst, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif // VK_USE_PLATFORM_XLIB_KHR

    // ---- VK_KHR_xcb_surface extension commands
#if defined(VK_USE_PLATFORM_XCB_KHR)
    table->CreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR)gpa(inst, "vkCreateXcbSurfaceKHR");
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    table->GetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)gpa(inst, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif // VK_USE_PLATFORM_XCB_KHR

    // ---- VK_KHR_wayland_surface extension commands
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    table->CreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR)gpa(inst, "vkCreateWaylandSurfaceKHR");
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    table->GetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)gpa(inst, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif // VK_USE_PLATFORM_WAYLAND_KHR

    // ---- VK_KHR_android_surface extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    table->CreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR)gpa(inst, "vkCreateAndroidSurfaceKHR");
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_KHR_win32_surface extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)gpa(inst, "vkCreateWin32SurfaceKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)gpa(inst, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_video_queue extension commands
    table->GetPhysicalDeviceVideoCapabilitiesKHR = (PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR)gpa(inst, "vkGetPhysicalDeviceVideoCapabilitiesKHR");
    table->GetPhysicalDeviceVideoFormatPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR)gpa(inst, "vkGetPhysicalDeviceVideoFormatPropertiesKHR");

    // ---- VK_KHR_get_physical_device_properties2 extension commands
    table->GetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR)gpa(inst, "vkGetPhysicalDeviceFeatures2KHR");
    table->GetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR)gpa(inst, "vkGetPhysicalDeviceProperties2KHR");
    table->GetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR)gpa(inst, "vkGetPhysicalDeviceFormatProperties2KHR");
    table->GetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR)gpa(inst, "vkGetPhysicalDeviceImageFormatProperties2KHR");
    table->GetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR)gpa(inst, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
    table->GetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR)gpa(inst, "vkGetPhysicalDeviceMemoryProperties2KHR");
    table->GetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR)gpa(inst, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");

    // ---- VK_KHR_device_group_creation extension commands
    table->EnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR)gpa(inst, "vkEnumeratePhysicalDeviceGroupsKHR");

    // ---- VK_KHR_external_memory_capabilities extension commands
    table->GetPhysicalDeviceExternalBufferPropertiesKHR = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR)gpa(inst, "vkGetPhysicalDeviceExternalBufferPropertiesKHR");

    // ---- VK_KHR_external_semaphore_capabilities extension commands
    table->GetPhysicalDeviceExternalSemaphorePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)gpa(inst, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");

    // ---- VK_KHR_external_fence_capabilities extension commands
    table->GetPhysicalDeviceExternalFencePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR)gpa(inst, "vkGetPhysicalDeviceExternalFencePropertiesKHR");

    // ---- VK_KHR_performance_query extension commands
    table->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)gpa(inst, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    table->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)gpa(inst, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    table->GetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR)gpa(inst, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
    table->GetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR)gpa(inst, "vkGetPhysicalDeviceSurfaceFormats2KHR");

    // ---- VK_KHR_get_display_properties2 extension commands
    table->GetPhysicalDeviceDisplayProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayProperties2KHR)gpa(inst, "vkGetPhysicalDeviceDisplayProperties2KHR");
    table->GetPhysicalDeviceDisplayPlaneProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR)gpa(inst, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
    table->GetDisplayModeProperties2KHR = (PFN_vkGetDisplayModeProperties2KHR)gpa(inst, "vkGetDisplayModeProperties2KHR");
    table->GetDisplayPlaneCapabilities2KHR = (PFN_vkGetDisplayPlaneCapabilities2KHR)gpa(inst, "vkGetDisplayPlaneCapabilities2KHR");

    // ---- VK_KHR_fragment_shading_rate extension commands
    table->GetPhysicalDeviceFragmentShadingRatesKHR = (PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR)gpa(inst, "vkGetPhysicalDeviceFragmentShadingRatesKHR");

    // ---- VK_KHR_video_encode_queue extension commands
    table->GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR)gpa(inst, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");

    // ---- VK_KHR_cooperative_matrix extension commands
    table->GetPhysicalDeviceCooperativeMatrixPropertiesKHR = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR)gpa(inst, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR");

    // ---- VK_KHR_calibrated_timestamps extension commands
    table->GetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)gpa(inst, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");

    // ---- VK_EXT_debug_report extension commands
    table->CreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)gpa(inst, "vkCreateDebugReportCallbackEXT");
    table->DestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)gpa(inst, "vkDestroyDebugReportCallbackEXT");
    table->DebugReportMessageEXT = (PFN_vkDebugReportMessageEXT)gpa(inst, "vkDebugReportMessageEXT");

    // ---- VK_GGP_stream_descriptor_surface extension commands
#if defined(VK_USE_PLATFORM_GGP)
    table->CreateStreamDescriptorSurfaceGGP = (PFN_vkCreateStreamDescriptorSurfaceGGP)gpa(inst, "vkCreateStreamDescriptorSurfaceGGP");
#endif // VK_USE_PLATFORM_GGP

    // ---- VK_NV_external_memory_capabilities extension commands
    table->GetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV)gpa(inst, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV");

    // ---- VK_NN_vi_surface extension commands
#if defined(VK_USE_PLATFORM_VI_NN)
    table->CreateViSurfaceNN = (PFN_vkCreateViSurfaceNN)gpa(inst, "vkCreateViSurfaceNN");
#endif // VK_USE_PLATFORM_VI_NN

    // ---- VK_EXT_direct_mode_display extension commands
    table->ReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT)gpa(inst, "vkReleaseDisplayEXT");

    // ---- VK_EXT_acquire_xlib_display extension commands
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    table->AcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT)gpa(inst, "vkAcquireXlibDisplayEXT");
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    table->GetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT)gpa(inst, "vkGetRandROutputDisplayEXT");
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT

    // ---- VK_EXT_display_surface_counter extension commands
    table->GetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)gpa(inst, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");

    // ---- VK_MVK_ios_surface extension commands
#if defined(VK_USE_PLATFORM_IOS_MVK)
    table->CreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK)gpa(inst, "vkCreateIOSSurfaceMVK");
#endif // VK_USE_PLATFORM_IOS_MVK

    // ---- VK_MVK_macos_surface extension commands
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    table->CreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK)gpa(inst, "vkCreateMacOSSurfaceMVK");
#endif // VK_USE_PLATFORM_MACOS_MVK

    // ---- VK_EXT_debug_utils extension commands
    table->CreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)gpa(inst, "vkCreateDebugUtilsMessengerEXT");
    table->DestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)gpa(inst, "vkDestroyDebugUtilsMessengerEXT");
    table->SubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT)gpa(inst, "vkSubmitDebugUtilsMessageEXT");

    // ---- VK_EXT_descriptor_heap extension commands
    table->GetPhysicalDeviceDescriptorSizeEXT = (PFN_vkGetPhysicalDeviceDescriptorSizeEXT)gpa(inst, "vkGetPhysicalDeviceDescriptorSizeEXT");

    // ---- VK_EXT_sample_locations extension commands
    table->GetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)gpa(inst, "vkGetPhysicalDeviceMultisamplePropertiesEXT");

    // ---- VK_EXT_calibrated_timestamps extension commands
    table->GetPhysicalDeviceCalibrateableTimeDomainsEXT = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT)gpa(inst, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");

    // ---- VK_FUCHSIA_imagepipe_surface extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    table->CreateImagePipeSurfaceFUCHSIA = (PFN_vkCreateImagePipeSurfaceFUCHSIA)gpa(inst, "vkCreateImagePipeSurfaceFUCHSIA");
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_EXT_metal_surface extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    table->CreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT)gpa(inst, "vkCreateMetalSurfaceEXT");
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_tooling_info extension commands
    table->GetPhysicalDeviceToolPropertiesEXT = (PFN_vkGetPhysicalDeviceToolPropertiesEXT)gpa(inst, "vkGetPhysicalDeviceToolPropertiesEXT");

    // ---- VK_NV_cooperative_matrix extension commands
    table->GetPhysicalDeviceCooperativeMatrixPropertiesNV = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV)gpa(inst, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV");

    // ---- VK_NV_coverage_reduction_mode extension commands
    table->GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = (PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV)gpa(inst, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetPhysicalDeviceSurfacePresentModes2EXT = (PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)gpa(inst, "vkGetPhysicalDeviceSurfacePresentModes2EXT");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_headless_surface extension commands
    table->CreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)gpa(inst, "vkCreateHeadlessSurfaceEXT");

    // ---- VK_EXT_acquire_drm_display extension commands
    table->AcquireDrmDisplayEXT = (PFN_vkAcquireDrmDisplayEXT)gpa(inst, "vkAcquireDrmDisplayEXT");
    table->GetDrmDisplayEXT = (PFN_vkGetDrmDisplayEXT)gpa(inst, "vkGetDrmDisplayEXT");

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->AcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV)gpa(inst, "vkAcquireWinrtDisplayNV");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV)gpa(inst, "vkGetWinrtDisplayNV");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_directfb_surface extension commands
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    table->CreateDirectFBSurfaceEXT = (PFN_vkCreateDirectFBSurfaceEXT)gpa(inst, "vkCreateDirectFBSurfaceEXT");
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    table->GetPhysicalDeviceDirectFBPresentationSupportEXT = (PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)gpa(inst, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT");
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

    // ---- VK_QNX_screen_surface extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    table->CreateScreenSurfaceQNX = (PFN_vkCreateScreenSurfaceQNX)gpa(inst, "vkCreateScreenSurfaceQNX");
#endif // VK_USE_PLATFORM_SCREEN_QNX
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    table->GetPhysicalDeviceScreenPresentationSupportQNX = (PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)gpa(inst, "vkGetPhysicalDeviceScreenPresentationSupportQNX");
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_ARM_tensors extension commands
    table->GetPhysicalDeviceExternalTensorPropertiesARM = (PFN_vkGetPhysicalDeviceExternalTensorPropertiesARM)gpa(inst, "vkGetPhysicalDeviceExternalTensorPropertiesARM");

    // ---- VK_NV_optical_flow extension commands
    table->GetPhysicalDeviceOpticalFlowImageFormatsNV = (PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV)gpa(inst, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV");

    // ---- VK_NV_cooperative_vector extension commands
    table->GetPhysicalDeviceCooperativeVectorPropertiesNV = (PFN_vkGetPhysicalDeviceCooperativeVectorPropertiesNV)gpa(inst, "vkGetPhysicalDeviceCooperativeVectorPropertiesNV");

    // ---- VK_ARM_data_graph extension commands
    table->GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM = (PFN_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM)gpa(inst, "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM");
    table->GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM = (PFN_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM)gpa(inst, "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM");

    // ---- VK_ARM_data_graph_instruction_set_tosa extension commands
    table->GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM = (PFN_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM)gpa(inst, "vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM");

    // ---- VK_OHOS_surface extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    table->CreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS)gpa(inst, "vkCreateSurfaceOHOS");
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_NV_cooperative_matrix2 extension commands
    table->GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV = (PFN_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV)gpa(inst, "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV");

    // ---- VK_ARM_performance_counters_by_region extension commands
    table->EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM)gpa(inst, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM");

    // ---- VK_ARM_shader_instrumentation extension commands
    table->EnumeratePhysicalDeviceShaderInstrumentationMetricsARM = (PFN_vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM)gpa(inst, "vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM");

    // ---- VK_ARM_data_graph_optical_flow extension commands
    table->GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM = (PFN_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM)gpa(inst, "vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM");

    // ---- VK_SEC_ubm_surface extension commands
#if defined(VK_USE_PLATFORM_UBM_SEC)
    table->CreateUbmSurfaceSEC = (PFN_vkCreateUbmSurfaceSEC)gpa(inst, "vkCreateUbmSurfaceSEC");
#endif // VK_USE_PLATFORM_UBM_SEC
#if defined(VK_USE_PLATFORM_UBM_SEC)
    table->GetPhysicalDeviceUbmPresentationSupportSEC = (PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)gpa(inst, "vkGetPhysicalDeviceUbmPresentationSupportSEC");
#endif // VK_USE_PLATFORM_UBM_SEC
}

// Functions that required a terminator need to have a separate dispatch table which contains their corresponding
// device function. This is used in the terminators themselves.
void init_extension_device_proc_terminator_dispatch(struct loader_device *dev) {
    struct loader_device_terminator_dispatch* dispatch = &dev->loader_dispatch.extension_terminator_dispatch;
    PFN_vkGetDeviceProcAddr gpda = (PFN_vkGetDeviceProcAddr)dev->phys_dev_term->this_icd_term->dispatch.GetDeviceProcAddr;

    // ---- VK_KHR_swapchain extension commands
    if (dev->driver_extensions.khr_swapchain_enabled)
       dispatch->CreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)gpda(dev->icd_device, "vkCreateSwapchainKHR");
    if (dev->driver_extensions.khr_swapchain_enabled || dev->driver_extensions.khr_device_group_enabled)
       dispatch->GetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)gpda(dev->icd_device, "vkGetDeviceGroupSurfacePresentModesKHR");

    // ---- VK_KHR_display_swapchain extension commands
    if (dev->driver_extensions.khr_display_swapchain_enabled)
       dispatch->CreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)gpda(dev->icd_device, "vkCreateSharedSwapchainsKHR");

    // ---- VK_EXT_debug_marker extension commands
    if (dev->driver_extensions.ext_debug_marker_enabled)
       dispatch->DebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)gpda(dev->icd_device, "vkDebugMarkerSetObjectTagEXT");
    if (dev->driver_extensions.ext_debug_marker_enabled)
       dispatch->DebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)gpda(dev->icd_device, "vkDebugMarkerSetObjectNameEXT");

    // ---- VK_EXT_debug_utils extension commands
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->SetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)gpda(dev->icd_device, "vkSetDebugUtilsObjectNameEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->SetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)gpda(dev->icd_device, "vkSetDebugUtilsObjectTagEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->QueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)gpda(dev->icd_device, "vkQueueBeginDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->QueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)gpda(dev->icd_device, "vkQueueEndDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->QueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)gpda(dev->icd_device, "vkQueueInsertDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->CmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)gpda(dev->icd_device, "vkCmdBeginDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->CmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)gpda(dev->icd_device, "vkCmdEndDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->CmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)gpda(dev->icd_device, "vkCmdInsertDebugUtilsLabelEXT");
#if defined(VK_USE_PLATFORM_WIN32_KHR)

    // ---- VK_EXT_full_screen_exclusive extension commands
    if (dev->driver_extensions.ext_full_screen_exclusive_enabled)
       dispatch->GetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)gpda(dev->icd_device, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif // VK_USE_PLATFORM_WIN32_KHR
}

// These are prototypes for functions that need their trampoline called in all circumstances.
// They are used in loader_lookup_device_dispatch_table but are defined afterwards.

    // ---- VK_EXT_debug_marker extension commands
VKAPI_ATTR VkResult VKAPI_CALL DebugMarkerSetObjectTagEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectTagInfoEXT*        pTagInfo);
VKAPI_ATTR VkResult VKAPI_CALL DebugMarkerSetObjectNameEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectNameInfoEXT*       pNameInfo);

    // ---- VK_EXT_debug_utils extension commands
VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo);
VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo);

// Device command lookup function
VKAPI_ATTR void* VKAPI_CALL loader_lookup_device_dispatch_table(const VkLayerDispatchTable *table, const char *name, uint64_t nameHash, bool* found_name) {
    if (!name || name[0] != 'v' || name[1] != 'k') {
        *found_name = false;
        return NULL;
    }

    *found_name = true;
    struct loader_device* dev = (struct loader_device *)table;
    const struct loader_instance* inst = dev->phys_dev_term->this_icd_term->this_instance;
    uint32_t api_version = VK_MAKE_API_VERSION(0, inst->app_api_version.major, inst->app_api_version.minor, inst->app_api_version.patch);


    // ---- Core Vulkan 1.0 commands
    if (nameHash == XXH3_vkGetDeviceProcAddr && !strcmp(name, "vkGetDeviceProcAddr")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceProcAddr;
    }
    if (nameHash == XXH3_vkDestroyDevice && !strcmp(name, "vkDestroyDevice")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyDevice;
    }
    if (nameHash == XXH3_vkGetDeviceQueue && !strcmp(name, "vkGetDeviceQueue")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceQueue;
    }
    if (nameHash == XXH3_vkQueueSubmit && !strcmp(name, "vkQueueSubmit")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->QueueSubmit;
    }
    if (nameHash == XXH3_vkQueueWaitIdle && !strcmp(name, "vkQueueWaitIdle")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->QueueWaitIdle;
    }
    if (nameHash == XXH3_vkDeviceWaitIdle && !strcmp(name, "vkDeviceWaitIdle")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DeviceWaitIdle;
    }
    if (nameHash == XXH3_vkAllocateMemory && !strcmp(name, "vkAllocateMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->AllocateMemory;
    }
    if (nameHash == XXH3_vkFreeMemory && !strcmp(name, "vkFreeMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FreeMemory;
    }
    if (nameHash == XXH3_vkMapMemory && !strcmp(name, "vkMapMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->MapMemory;
    }
    if (nameHash == XXH3_vkUnmapMemory && !strcmp(name, "vkUnmapMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->UnmapMemory;
    }
    if (nameHash == XXH3_vkFlushMappedMemoryRanges && !strcmp(name, "vkFlushMappedMemoryRanges")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FlushMappedMemoryRanges;
    }
    if (nameHash == XXH3_vkInvalidateMappedMemoryRanges && !strcmp(name, "vkInvalidateMappedMemoryRanges")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->InvalidateMappedMemoryRanges;
    }
    if (nameHash == XXH3_vkGetDeviceMemoryCommitment && !strcmp(name, "vkGetDeviceMemoryCommitment")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceMemoryCommitment;
    }
    if (nameHash == XXH3_vkBindBufferMemory && !strcmp(name, "vkBindBufferMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BindBufferMemory;
    }
    if (nameHash == XXH3_vkBindImageMemory && !strcmp(name, "vkBindImageMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BindImageMemory;
    }
    if (nameHash == XXH3_vkGetBufferMemoryRequirements && !strcmp(name, "vkGetBufferMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetBufferMemoryRequirements;
    }
    if (nameHash == XXH3_vkGetImageMemoryRequirements && !strcmp(name, "vkGetImageMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetImageMemoryRequirements;
    }
    if (nameHash == XXH3_vkGetImageSparseMemoryRequirements && !strcmp(name, "vkGetImageSparseMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetImageSparseMemoryRequirements;
    }
    if (nameHash == XXH3_vkQueueBindSparse && !strcmp(name, "vkQueueBindSparse")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->QueueBindSparse;
    }
    if (nameHash == XXH3_vkCreateFence && !strcmp(name, "vkCreateFence")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateFence;
    }
    if (nameHash == XXH3_vkDestroyFence && !strcmp(name, "vkDestroyFence")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyFence;
    }
    if (nameHash == XXH3_vkResetFences && !strcmp(name, "vkResetFences")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetFences;
    }
    if (nameHash == XXH3_vkGetFenceStatus && !strcmp(name, "vkGetFenceStatus")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetFenceStatus;
    }
    if (nameHash == XXH3_vkWaitForFences && !strcmp(name, "vkWaitForFences")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->WaitForFences;
    }
    if (nameHash == XXH3_vkCreateSemaphore && !strcmp(name, "vkCreateSemaphore")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateSemaphore;
    }
    if (nameHash == XXH3_vkDestroySemaphore && !strcmp(name, "vkDestroySemaphore")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroySemaphore;
    }
    if (nameHash == XXH3_vkCreateQueryPool && !strcmp(name, "vkCreateQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateQueryPool;
    }
    if (nameHash == XXH3_vkDestroyQueryPool && !strcmp(name, "vkDestroyQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyQueryPool;
    }
    if (nameHash == XXH3_vkGetQueryPoolResults && !strcmp(name, "vkGetQueryPoolResults")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetQueryPoolResults;
    }
    if (nameHash == XXH3_vkCreateBuffer && !strcmp(name, "vkCreateBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateBuffer;
    }
    if (nameHash == XXH3_vkDestroyBuffer && !strcmp(name, "vkDestroyBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyBuffer;
    }
    if (nameHash == XXH3_vkCreateImage && !strcmp(name, "vkCreateImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateImage;
    }
    if (nameHash == XXH3_vkDestroyImage && !strcmp(name, "vkDestroyImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyImage;
    }
    if (nameHash == XXH3_vkGetImageSubresourceLayout && !strcmp(name, "vkGetImageSubresourceLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetImageSubresourceLayout;
    }
    if (nameHash == XXH3_vkCreateImageView && !strcmp(name, "vkCreateImageView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateImageView;
    }
    if (nameHash == XXH3_vkDestroyImageView && !strcmp(name, "vkDestroyImageView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyImageView;
    }
    if (nameHash == XXH3_vkCreateCommandPool && !strcmp(name, "vkCreateCommandPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateCommandPool;
    }
    if (nameHash == XXH3_vkDestroyCommandPool && !strcmp(name, "vkDestroyCommandPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyCommandPool;
    }
    if (nameHash == XXH3_vkResetCommandPool && !strcmp(name, "vkResetCommandPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetCommandPool;
    }
    if (nameHash == XXH3_vkAllocateCommandBuffers && !strcmp(name, "vkAllocateCommandBuffers")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->AllocateCommandBuffers;
    }
    if (nameHash == XXH3_vkFreeCommandBuffers && !strcmp(name, "vkFreeCommandBuffers")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FreeCommandBuffers;
    }
    if (nameHash == XXH3_vkBeginCommandBuffer && !strcmp(name, "vkBeginCommandBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BeginCommandBuffer;
    }
    if (nameHash == XXH3_vkEndCommandBuffer && !strcmp(name, "vkEndCommandBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->EndCommandBuffer;
    }
    if (nameHash == XXH3_vkResetCommandBuffer && !strcmp(name, "vkResetCommandBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetCommandBuffer;
    }
    if (nameHash == XXH3_vkCmdCopyBuffer && !strcmp(name, "vkCmdCopyBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyBuffer;
    }
    if (nameHash == XXH3_vkCmdCopyImage && !strcmp(name, "vkCmdCopyImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyImage;
    }
    if (nameHash == XXH3_vkCmdCopyBufferToImage && !strcmp(name, "vkCmdCopyBufferToImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyBufferToImage;
    }
    if (nameHash == XXH3_vkCmdCopyImageToBuffer && !strcmp(name, "vkCmdCopyImageToBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyImageToBuffer;
    }
    if (nameHash == XXH3_vkCmdUpdateBuffer && !strcmp(name, "vkCmdUpdateBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdUpdateBuffer;
    }
    if (nameHash == XXH3_vkCmdFillBuffer && !strcmp(name, "vkCmdFillBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdFillBuffer;
    }
    if (nameHash == XXH3_vkCmdPipelineBarrier && !strcmp(name, "vkCmdPipelineBarrier")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdPipelineBarrier;
    }
    if (nameHash == XXH3_vkCmdBeginQuery && !strcmp(name, "vkCmdBeginQuery")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBeginQuery;
    }
    if (nameHash == XXH3_vkCmdEndQuery && !strcmp(name, "vkCmdEndQuery")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdEndQuery;
    }
    if (nameHash == XXH3_vkCmdResetQueryPool && !strcmp(name, "vkCmdResetQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdResetQueryPool;
    }
    if (nameHash == XXH3_vkCmdWriteTimestamp && !strcmp(name, "vkCmdWriteTimestamp")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdWriteTimestamp;
    }
    if (nameHash == XXH3_vkCmdCopyQueryPoolResults && !strcmp(name, "vkCmdCopyQueryPoolResults")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyQueryPoolResults;
    }
    if (nameHash == XXH3_vkCmdExecuteCommands && !strcmp(name, "vkCmdExecuteCommands")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdExecuteCommands;
    }
    if (nameHash == XXH3_vkCreateEvent && !strcmp(name, "vkCreateEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateEvent;
    }
    if (nameHash == XXH3_vkDestroyEvent && !strcmp(name, "vkDestroyEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyEvent;
    }
    if (nameHash == XXH3_vkGetEventStatus && !strcmp(name, "vkGetEventStatus")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetEventStatus;
    }
    if (nameHash == XXH3_vkSetEvent && !strcmp(name, "vkSetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->SetEvent;
    }
    if (nameHash == XXH3_vkResetEvent && !strcmp(name, "vkResetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetEvent;
    }
    if (nameHash == XXH3_vkCreateBufferView && !strcmp(name, "vkCreateBufferView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateBufferView;
    }
    if (nameHash == XXH3_vkDestroyBufferView && !strcmp(name, "vkDestroyBufferView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyBufferView;
    }
    if (nameHash == XXH3_vkCreateShaderModule && !strcmp(name, "vkCreateShaderModule")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateShaderModule;
    }
    if (nameHash == XXH3_vkDestroyShaderModule && !strcmp(name, "vkDestroyShaderModule")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyShaderModule;
    }
    if (nameHash == XXH3_vkCreatePipelineCache && !strcmp(name, "vkCreatePipelineCache")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreatePipelineCache;
    }
    if (nameHash == XXH3_vkDestroyPipelineCache && !strcmp(name, "vkDestroyPipelineCache")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyPipelineCache;
    }
    if (nameHash == XXH3_vkGetPipelineCacheData && !strcmp(name, "vkGetPipelineCacheData")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetPipelineCacheData;
    }
    if (nameHash == XXH3_vkMergePipelineCaches && !strcmp(name, "vkMergePipelineCaches")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->MergePipelineCaches;
    }
    if (nameHash == XXH3_vkCreateComputePipelines && !strcmp(name, "vkCreateComputePipelines")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateComputePipelines;
    }
    if (nameHash == XXH3_vkDestroyPipeline && !strcmp(name, "vkDestroyPipeline")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyPipeline;
    }
    if (nameHash == XXH3_vkCreatePipelineLayout && !strcmp(name, "vkCreatePipelineLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreatePipelineLayout;
    }
    if (nameHash == XXH3_vkDestroyPipelineLayout && !strcmp(name, "vkDestroyPipelineLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyPipelineLayout;
    }
    if (nameHash == XXH3_vkCreateSampler && !strcmp(name, "vkCreateSampler")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateSampler;
    }
    if (nameHash == XXH3_vkDestroySampler && !strcmp(name, "vkDestroySampler")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroySampler;
    }
    if (nameHash == XXH3_vkCreateDescriptorSetLayout && !strcmp(name, "vkCreateDescriptorSetLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateDescriptorSetLayout;
    }
    if (nameHash == XXH3_vkDestroyDescriptorSetLayout && !strcmp(name, "vkDestroyDescriptorSetLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyDescriptorSetLayout;
    }
    if (nameHash == XXH3_vkCreateDescriptorPool && !strcmp(name, "vkCreateDescriptorPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateDescriptorPool;
    }
    if (nameHash == XXH3_vkDestroyDescriptorPool && !strcmp(name, "vkDestroyDescriptorPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyDescriptorPool;
    }
    if (nameHash == XXH3_vkResetDescriptorPool && !strcmp(name, "vkResetDescriptorPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetDescriptorPool;
    }
    if (nameHash == XXH3_vkAllocateDescriptorSets && !strcmp(name, "vkAllocateDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->AllocateDescriptorSets;
    }
    if (nameHash == XXH3_vkFreeDescriptorSets && !strcmp(name, "vkFreeDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FreeDescriptorSets;
    }
    if (nameHash == XXH3_vkUpdateDescriptorSets && !strcmp(name, "vkUpdateDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->UpdateDescriptorSets;
    }
    if (nameHash == XXH3_vkCmdBindPipeline && !strcmp(name, "vkCmdBindPipeline")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindPipeline;
    }
    if (nameHash == XXH3_vkCmdBindDescriptorSets && !strcmp(name, "vkCmdBindDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindDescriptorSets;
    }
    if (nameHash == XXH3_vkCmdClearColorImage && !strcmp(name, "vkCmdClearColorImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdClearColorImage;
    }
    if (nameHash == XXH3_vkCmdDispatch && !strcmp(name, "vkCmdDispatch")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDispatch;
    }
    if (nameHash == XXH3_vkCmdDispatchIndirect && !strcmp(name, "vkCmdDispatchIndirect")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDispatchIndirect;
    }
    if (nameHash == XXH3_vkCmdSetEvent && !strcmp(name, "vkCmdSetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetEvent;
    }
    if (nameHash == XXH3_vkCmdResetEvent && !strcmp(name, "vkCmdResetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdResetEvent;
    }
    if (nameHash == XXH3_vkCmdWaitEvents && !strcmp(name, "vkCmdWaitEvents")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdWaitEvents;
    }
    if (nameHash == XXH3_vkCmdPushConstants && !strcmp(name, "vkCmdPushConstants")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdPushConstants;
    }
    if (nameHash == XXH3_vkCreateGraphicsPipelines && !strcmp(name, "vkCreateGraphicsPipelines")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateGraphicsPipelines;
    }
    if (nameHash == XXH3_vkCreateFramebuffer && !strcmp(name, "vkCreateFramebuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateFramebuffer;
    }
    if (nameHash == XXH3_vkDestroyFramebuffer && !strcmp(name, "vkDestroyFramebuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyFramebuffer;
    }
    if (nameHash == XXH3_vkCreateRenderPass && !strcmp(name, "vkCreateRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateRenderPass;
    }
    if (nameHash == XXH3_vkDestroyRenderPass && !strcmp(name, "vkDestroyRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyRenderPass;
    }
    if (nameHash == XXH3_vkGetRenderAreaGranularity && !strcmp(name, "vkGetRenderAreaGranularity")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetRenderAreaGranularity;
    }
    if (nameHash == XXH3_vkCmdSetViewport && !strcmp(name, "vkCmdSetViewport")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetViewport;
    }
    if (nameHash == XXH3_vkCmdSetScissor && !strcmp(name, "vkCmdSetScissor")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetScissor;
    }
    if (nameHash == XXH3_vkCmdSetLineWidth && !strcmp(name, "vkCmdSetLineWidth")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetLineWidth;
    }
    if (nameHash == XXH3_vkCmdSetDepthBias && !strcmp(name, "vkCmdSetDepthBias")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetDepthBias;
    }
    if (nameHash == XXH3_vkCmdSetBlendConstants && !strcmp(name, "vkCmdSetBlendConstants")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetBlendConstants;
    }
    if (nameHash == XXH3_vkCmdSetDepthBounds && !strcmp(name, "vkCmdSetDepthBounds")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetDepthBounds;
    }
    if (nameHash == XXH3_vkCmdSetStencilCompareMask && !strcmp(name, "vkCmdSetStencilCompareMask")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetStencilCompareMask;
    }
    if (nameHash == XXH3_vkCmdSetStencilWriteMask && !strcmp(name, "vkCmdSetStencilWriteMask")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetStencilWriteMask;
    }
    if (nameHash == XXH3_vkCmdSetStencilReference && !strcmp(name, "vkCmdSetStencilReference")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetStencilReference;
    }
    if (nameHash == XXH3_vkCmdBindIndexBuffer && !strcmp(name, "vkCmdBindIndexBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindIndexBuffer;
    }
    if (nameHash == XXH3_vkCmdBindVertexBuffers && !strcmp(name, "vkCmdBindVertexBuffers")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindVertexBuffers;
    }
    if (nameHash == XXH3_vkCmdDraw && !strcmp(name, "vkCmdDraw")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDraw;
    }
    if (nameHash == XXH3_vkCmdDrawIndexed && !strcmp(name, "vkCmdDrawIndexed")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndexed;
    }
    if (nameHash == XXH3_vkCmdDrawIndirect && !strcmp(name, "vkCmdDrawIndirect")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndirect;
    }
    if (nameHash == XXH3_vkCmdDrawIndexedIndirect && !strcmp(name, "vkCmdDrawIndexedIndirect")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndexedIndirect;
    }
    if (nameHash == XXH3_vkCmdBlitImage && !strcmp(name, "vkCmdBlitImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBlitImage;
    }
    if (nameHash == XXH3_vkCmdClearDepthStencilImage && !strcmp(name, "vkCmdClearDepthStencilImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdClearDepthStencilImage;
    }
    if (nameHash == XXH3_vkCmdClearAttachments && !strcmp(name, "vkCmdClearAttachments")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdClearAttachments;
    }
    if (nameHash == XXH3_vkCmdResolveImage && !strcmp(name, "vkCmdResolveImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdResolveImage;
    }
    if (nameHash == XXH3_vkCmdBeginRenderPass && !strcmp(name, "vkCmdBeginRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBeginRenderPass;
    }
    if (nameHash == XXH3_vkCmdNextSubpass && !strcmp(name, "vkCmdNextSubpass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdNextSubpass;
    }
    if (nameHash == XXH3_vkCmdEndRenderPass && !strcmp(name, "vkCmdEndRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdEndRenderPass;
    }

    // ---- Core Vulkan 1.1 commands
    if (nameHash == XXH3_vkBindBufferMemory2 && !strcmp(name, "vkBindBufferMemory2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->BindBufferMemory2;
    }
    if (nameHash == XXH3_vkBindImageMemory2 && !strcmp(name, "vkBindImageMemory2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->BindImageMemory2;
    }
    if (nameHash == XXH3_vkGetDeviceGroupPeerMemoryFeatures && !strcmp(name, "vkGetDeviceGroupPeerMemoryFeatures")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->GetDeviceGroupPeerMemoryFeatures;
    }
    if (nameHash == XXH3_vkCmdSetDeviceMask && !strcmp(name, "vkCmdSetDeviceMask")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->CmdSetDeviceMask;
    }
    if (nameHash == XXH3_vkGetImageMemoryRequirements2 && !strcmp(name, "vkGetImageMemoryRequirements2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->GetImageMemoryRequirements2;
    }
    if (nameHash == XXH3_vkGetBufferMemoryRequirements2 && !strcmp(name, "vkGetBufferMemoryRequirements2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->GetBufferMemoryRequirements2;
    }
    if (nameHash == XXH3_vkGetImageSparseMemoryRequirements2 && !strcmp(name, "vkGetImageSparseMemoryRequirements2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->GetImageSparseMemoryRequirements2;
    }
    if (nameHash == XXH3_vkTrimCommandPool && !strcmp(name, "vkTrimCommandPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->TrimCommandPool;
    }
    if (nameHash == XXH3_vkGetDeviceQueue2 && !strcmp(name, "vkGetDeviceQueue2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->GetDeviceQueue2;
    }
    if (nameHash == XXH3_vkCmdDispatchBase && !strcmp(name, "vkCmdDispatchBase")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->CmdDispatchBase;
    }
    if (nameHash == XXH3_vkCreateDescriptorUpdateTemplate && !strcmp(name, "vkCreateDescriptorUpdateTemplate")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->CreateDescriptorUpdateTemplate;
    }
    if (nameHash == XXH3_vkDestroyDescriptorUpdateTemplate && !strcmp(name, "vkDestroyDescriptorUpdateTemplate")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->DestroyDescriptorUpdateTemplate;
    }
    if (nameHash == XXH3_vkUpdateDescriptorSetWithTemplate && !strcmp(name, "vkUpdateDescriptorSetWithTemplate")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->UpdateDescriptorSetWithTemplate;
    }
    if (nameHash == XXH3_vkGetDescriptorSetLayoutSupport && !strcmp(name, "vkGetDescriptorSetLayoutSupport")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->GetDescriptorSetLayoutSupport;
    }
    if (nameHash == XXH3_vkCreateSamplerYcbcrConversion && !strcmp(name, "vkCreateSamplerYcbcrConversion")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->CreateSamplerYcbcrConversion;
    }
    if (nameHash == XXH3_vkDestroySamplerYcbcrConversion && !strcmp(name, "vkDestroySamplerYcbcrConversion")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_1) return NULL;
        return (void *)table->DestroySamplerYcbcrConversion;
    }

    // ---- Core Vulkan 1.2 commands
    if (nameHash == XXH3_vkResetQueryPool && !strcmp(name, "vkResetQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->ResetQueryPool;
    }
    if (nameHash == XXH3_vkGetSemaphoreCounterValue && !strcmp(name, "vkGetSemaphoreCounterValue")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->GetSemaphoreCounterValue;
    }
    if (nameHash == XXH3_vkWaitSemaphores && !strcmp(name, "vkWaitSemaphores")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->WaitSemaphores;
    }
    if (nameHash == XXH3_vkSignalSemaphore && !strcmp(name, "vkSignalSemaphore")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->SignalSemaphore;
    }
    if (nameHash == XXH3_vkGetBufferDeviceAddress && !strcmp(name, "vkGetBufferDeviceAddress")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->GetBufferDeviceAddress;
    }
    if (nameHash == XXH3_vkGetBufferOpaqueCaptureAddress && !strcmp(name, "vkGetBufferOpaqueCaptureAddress")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->GetBufferOpaqueCaptureAddress;
    }
    if (nameHash == XXH3_vkGetDeviceMemoryOpaqueCaptureAddress && !strcmp(name, "vkGetDeviceMemoryOpaqueCaptureAddress")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->GetDeviceMemoryOpaqueCaptureAddress;
    }
    if (nameHash == XXH3_vkCmdDrawIndirectCount && !strcmp(name, "vkCmdDrawIndirectCount")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->CmdDrawIndirectCount;
    }
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCount && !strcmp(name, "vkCmdDrawIndexedIndirectCount")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->CmdDrawIndexedIndirectCount;
    }
    if (nameHash == XXH3_vkCreateRenderPass2 && !strcmp(name, "vkCreateRenderPass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->CreateRenderPass2;
    }
    if (nameHash == XXH3_vkCmdBeginRenderPass2 && !strcmp(name, "vkCmdBeginRenderPass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->CmdBeginRenderPass2;
    }
    if (nameHash == XXH3_vkCmdNextSubpass2 && !strcmp(name, "vkCmdNextSubpass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->CmdNextSubpass2;
    }
    if (nameHash == XXH3_vkCmdEndRenderPass2 && !strcmp(name, "vkCmdEndRenderPass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_2) return NULL;
        return (void *)table->CmdEndRenderPass2;
    }

    // ---- Core Vulkan 1.3 commands
    if (nameHash == XXH3_vkCreatePrivateDataSlot && !strcmp(name, "vkCreatePrivateDataSlot")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CreatePrivateDataSlot;
    }
    if (nameHash == XXH3_vkDestroyPrivateDataSlot && !strcmp(name, "vkDestroyPrivateDataSlot")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->DestroyPrivateDataSlot;
    }
    if (nameHash == XXH3_vkSetPrivateData && !strcmp(name, "vkSetPrivateData")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->SetPrivateData;
    }
    if (nameHash == XXH3_vkGetPrivateData && !strcmp(name, "vkGetPrivateData")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->GetPrivateData;
    }
    if (nameHash == XXH3_vkCmdPipelineBarrier2 && !strcmp(name, "vkCmdPipelineBarrier2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdPipelineBarrier2;
    }
    if (nameHash == XXH3_vkCmdWriteTimestamp2 && !strcmp(name, "vkCmdWriteTimestamp2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdWriteTimestamp2;
    }
    if (nameHash == XXH3_vkQueueSubmit2 && !strcmp(name, "vkQueueSubmit2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->QueueSubmit2;
    }
    if (nameHash == XXH3_vkCmdCopyBuffer2 && !strcmp(name, "vkCmdCopyBuffer2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdCopyBuffer2;
    }
    if (nameHash == XXH3_vkCmdCopyImage2 && !strcmp(name, "vkCmdCopyImage2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdCopyImage2;
    }
    if (nameHash == XXH3_vkCmdCopyBufferToImage2 && !strcmp(name, "vkCmdCopyBufferToImage2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdCopyBufferToImage2;
    }
    if (nameHash == XXH3_vkCmdCopyImageToBuffer2 && !strcmp(name, "vkCmdCopyImageToBuffer2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdCopyImageToBuffer2;
    }
    if (nameHash == XXH3_vkGetDeviceBufferMemoryRequirements && !strcmp(name, "vkGetDeviceBufferMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->GetDeviceBufferMemoryRequirements;
    }
    if (nameHash == XXH3_vkGetDeviceImageMemoryRequirements && !strcmp(name, "vkGetDeviceImageMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->GetDeviceImageMemoryRequirements;
    }
    if (nameHash == XXH3_vkGetDeviceImageSparseMemoryRequirements && !strcmp(name, "vkGetDeviceImageSparseMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->GetDeviceImageSparseMemoryRequirements;
    }
    if (nameHash == XXH3_vkCmdSetEvent2 && !strcmp(name, "vkCmdSetEvent2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetEvent2;
    }
    if (nameHash == XXH3_vkCmdResetEvent2 && !strcmp(name, "vkCmdResetEvent2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdResetEvent2;
    }
    if (nameHash == XXH3_vkCmdWaitEvents2 && !strcmp(name, "vkCmdWaitEvents2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdWaitEvents2;
    }
    if (nameHash == XXH3_vkCmdBlitImage2 && !strcmp(name, "vkCmdBlitImage2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdBlitImage2;
    }
    if (nameHash == XXH3_vkCmdResolveImage2 && !strcmp(name, "vkCmdResolveImage2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdResolveImage2;
    }
    if (nameHash == XXH3_vkCmdBeginRendering && !strcmp(name, "vkCmdBeginRendering")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdBeginRendering;
    }
    if (nameHash == XXH3_vkCmdEndRendering && !strcmp(name, "vkCmdEndRendering")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdEndRendering;
    }
    if (nameHash == XXH3_vkCmdSetCullMode && !strcmp(name, "vkCmdSetCullMode")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetCullMode;
    }
    if (nameHash == XXH3_vkCmdSetFrontFace && !strcmp(name, "vkCmdSetFrontFace")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetFrontFace;
    }
    if (nameHash == XXH3_vkCmdSetPrimitiveTopology && !strcmp(name, "vkCmdSetPrimitiveTopology")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetPrimitiveTopology;
    }
    if (nameHash == XXH3_vkCmdSetViewportWithCount && !strcmp(name, "vkCmdSetViewportWithCount")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetViewportWithCount;
    }
    if (nameHash == XXH3_vkCmdSetScissorWithCount && !strcmp(name, "vkCmdSetScissorWithCount")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetScissorWithCount;
    }
    if (nameHash == XXH3_vkCmdBindVertexBuffers2 && !strcmp(name, "vkCmdBindVertexBuffers2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdBindVertexBuffers2;
    }
    if (nameHash == XXH3_vkCmdSetDepthTestEnable && !strcmp(name, "vkCmdSetDepthTestEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetDepthTestEnable;
    }
    if (nameHash == XXH3_vkCmdSetDepthWriteEnable && !strcmp(name, "vkCmdSetDepthWriteEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetDepthWriteEnable;
    }
    if (nameHash == XXH3_vkCmdSetDepthCompareOp && !strcmp(name, "vkCmdSetDepthCompareOp")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetDepthCompareOp;
    }
    if (nameHash == XXH3_vkCmdSetDepthBoundsTestEnable && !strcmp(name, "vkCmdSetDepthBoundsTestEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetDepthBoundsTestEnable;
    }
    if (nameHash == XXH3_vkCmdSetStencilTestEnable && !strcmp(name, "vkCmdSetStencilTestEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetStencilTestEnable;
    }
    if (nameHash == XXH3_vkCmdSetStencilOp && !strcmp(name, "vkCmdSetStencilOp")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetStencilOp;
    }
    if (nameHash == XXH3_vkCmdSetRasterizerDiscardEnable && !strcmp(name, "vkCmdSetRasterizerDiscardEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetRasterizerDiscardEnable;
    }
    if (nameHash == XXH3_vkCmdSetDepthBiasEnable && !strcmp(name, "vkCmdSetDepthBiasEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetDepthBiasEnable;
    }
    if (nameHash == XXH3_vkCmdSetPrimitiveRestartEnable && !strcmp(name, "vkCmdSetPrimitiveRestartEnable")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
        return (void *)table->CmdSetPrimitiveRestartEnable;
    }

    // ---- Core Vulkan 1.4 commands
    if (nameHash == XXH3_vkMapMemory2 && !strcmp(name, "vkMapMemory2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->MapMemory2;
    }
    if (nameHash == XXH3_vkUnmapMemory2 && !strcmp(name, "vkUnmapMemory2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->UnmapMemory2;
    }
    if (nameHash == XXH3_vkGetDeviceImageSubresourceLayout && !strcmp(name, "vkGetDeviceImageSubresourceLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->GetDeviceImageSubresourceLayout;
    }
    if (nameHash == XXH3_vkGetImageSubresourceLayout2 && !strcmp(name, "vkGetImageSubresourceLayout2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->GetImageSubresourceLayout2;
    }
    if (nameHash == XXH3_vkCopyMemoryToImage && !strcmp(name, "vkCopyMemoryToImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CopyMemoryToImage;
    }
    if (nameHash == XXH3_vkCopyImageToMemory && !strcmp(name, "vkCopyImageToMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CopyImageToMemory;
    }
    if (nameHash == XXH3_vkCopyImageToImage && !strcmp(name, "vkCopyImageToImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CopyImageToImage;
    }
    if (nameHash == XXH3_vkTransitionImageLayout && !strcmp(name, "vkTransitionImageLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->TransitionImageLayout;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSet && !strcmp(name, "vkCmdPushDescriptorSet")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdPushDescriptorSet;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplate && !strcmp(name, "vkCmdPushDescriptorSetWithTemplate")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdPushDescriptorSetWithTemplate;
    }
    if (nameHash == XXH3_vkCmdBindDescriptorSets2 && !strcmp(name, "vkCmdBindDescriptorSets2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdBindDescriptorSets2;
    }
    if (nameHash == XXH3_vkCmdPushConstants2 && !strcmp(name, "vkCmdPushConstants2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdPushConstants2;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSet2 && !strcmp(name, "vkCmdPushDescriptorSet2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdPushDescriptorSet2;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplate2 && !strcmp(name, "vkCmdPushDescriptorSetWithTemplate2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdPushDescriptorSetWithTemplate2;
    }
    if (nameHash == XXH3_vkCmdSetLineStipple && !strcmp(name, "vkCmdSetLineStipple")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdSetLineStipple;
    }
    if (nameHash == XXH3_vkCmdBindIndexBuffer2 && !strcmp(name, "vkCmdBindIndexBuffer2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdBindIndexBuffer2;
    }
    if (nameHash == XXH3_vkGetRenderingAreaGranularity && !strcmp(name, "vkGetRenderingAreaGranularity")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->GetRenderingAreaGranularity;
    }
    if (nameHash == XXH3_vkCmdSetRenderingAttachmentLocations && !strcmp(name, "vkCmdSetRenderingAttachmentLocations")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdSetRenderingAttachmentLocations;
    }
    if (nameHash == XXH3_vkCmdSetRenderingInputAttachmentIndices && !strcmp(name, "vkCmdSetRenderingInputAttachmentIndices")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
        return (void *)table->CmdSetRenderingInputAttachmentIndices;
    }

    // ---- VK_KHR_swapchain extension commands
    if (nameHash == XXH3_vkCreateSwapchainKHR && !strcmp(name, "vkCreateSwapchainKHR")) return (void *)table->CreateSwapchainKHR;
    if (nameHash == XXH3_vkDestroySwapchainKHR && !strcmp(name, "vkDestroySwapchainKHR")) return (void *)table->DestroySwapchainKHR;
    if (nameHash == XXH3_vkGetSwapchainImagesKHR && !strcmp(name, "vkGetSwapchainImagesKHR")) return (void *)table->GetSwapchainImagesKHR;
    if (nameHash == XXH3_vkAcquireNextImageKHR && !strcmp(name, "vkAcquireNextImageKHR")) return (void *)table->AcquireNextImageKHR;
    if (nameHash == XXH3_vkQueuePresentKHR && !strcmp(name, "vkQueuePresentKHR")) return (void *)table->QueuePresentKHR;
    if (nameHash == XXH3_vkGetDeviceGroupPresentCapabilitiesKHR && !strcmp(name, "vkGetDeviceGroupPresentCapabilitiesKHR")) return (void *)table->GetDeviceGroupPresentCapabilitiesKHR;
    if (nameHash == XXH3_vkGetDeviceGroupSurfacePresentModesKHR && !strcmp(name, "vkGetDeviceGroupSurfacePresentModesKHR")) return (void *)table->GetDeviceGroupSurfacePresentModesKHR;
    if (nameHash == XXH3_vkAcquireNextImage2KHR && !strcmp(name, "vkAcquireNextImage2KHR")) return (void *)table->AcquireNextImage2KHR;

    // ---- VK_KHR_display_swapchain extension commands
    if (nameHash == XXH3_vkCreateSharedSwapchainsKHR && !strcmp(name, "vkCreateSharedSwapchainsKHR")) return (void *)table->CreateSharedSwapchainsKHR;

    // ---- VK_KHR_video_queue extension commands
    if (nameHash == XXH3_vkCreateVideoSessionKHR && !strcmp(name, "vkCreateVideoSessionKHR")) return (void *)table->CreateVideoSessionKHR;
    if (nameHash == XXH3_vkDestroyVideoSessionKHR && !strcmp(name, "vkDestroyVideoSessionKHR")) return (void *)table->DestroyVideoSessionKHR;
    if (nameHash == XXH3_vkGetVideoSessionMemoryRequirementsKHR && !strcmp(name, "vkGetVideoSessionMemoryRequirementsKHR")) return (void *)table->GetVideoSessionMemoryRequirementsKHR;
    if (nameHash == XXH3_vkBindVideoSessionMemoryKHR && !strcmp(name, "vkBindVideoSessionMemoryKHR")) return (void *)table->BindVideoSessionMemoryKHR;
    if (nameHash == XXH3_vkCreateVideoSessionParametersKHR && !strcmp(name, "vkCreateVideoSessionParametersKHR")) return (void *)table->CreateVideoSessionParametersKHR;
    if (nameHash == XXH3_vkUpdateVideoSessionParametersKHR && !strcmp(name, "vkUpdateVideoSessionParametersKHR")) return (void *)table->UpdateVideoSessionParametersKHR;
    if (nameHash == XXH3_vkDestroyVideoSessionParametersKHR && !strcmp(name, "vkDestroyVideoSessionParametersKHR")) return (void *)table->DestroyVideoSessionParametersKHR;
    if (nameHash == XXH3_vkCmdBeginVideoCodingKHR && !strcmp(name, "vkCmdBeginVideoCodingKHR")) return (void *)table->CmdBeginVideoCodingKHR;
    if (nameHash == XXH3_vkCmdEndVideoCodingKHR && !strcmp(name, "vkCmdEndVideoCodingKHR")) return (void *)table->CmdEndVideoCodingKHR;
    if (nameHash == XXH3_vkCmdControlVideoCodingKHR && !strcmp(name, "vkCmdControlVideoCodingKHR")) return (void *)table->CmdControlVideoCodingKHR;

    // ---- VK_KHR_video_decode_queue extension commands
    if (nameHash == XXH3_vkCmdDecodeVideoKHR && !strcmp(name, "vkCmdDecodeVideoKHR")) return (void *)table->CmdDecodeVideoKHR;

    // ---- VK_KHR_dynamic_rendering extension commands
    if (nameHash == XXH3_vkCmdBeginRenderingKHR && !strcmp(name, "vkCmdBeginRenderingKHR")) return (void *)table->CmdBeginRenderingKHR;
    if (nameHash == XXH3_vkCmdEndRenderingKHR && !strcmp(name, "vkCmdEndRenderingKHR")) return (void *)table->CmdEndRenderingKHR;

    // ---- VK_KHR_device_group extension commands
    if (nameHash == XXH3_vkGetDeviceGroupPeerMemoryFeaturesKHR && !strcmp(name, "vkGetDeviceGroupPeerMemoryFeaturesKHR")) return (void *)table->GetDeviceGroupPeerMemoryFeaturesKHR;
    if (nameHash == XXH3_vkCmdSetDeviceMaskKHR && !strcmp(name, "vkCmdSetDeviceMaskKHR")) return (void *)table->CmdSetDeviceMaskKHR;
    if (nameHash == XXH3_vkCmdDispatchBaseKHR && !strcmp(name, "vkCmdDispatchBaseKHR")) return (void *)table->CmdDispatchBaseKHR;

    // ---- VK_KHR_maintenance1 extension commands
    if (nameHash == XXH3_vkTrimCommandPoolKHR && !strcmp(name, "vkTrimCommandPoolKHR")) return (void *)table->TrimCommandPoolKHR;

    // ---- VK_KHR_external_memory_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetMemoryWin32HandleKHR && !strcmp(name, "vkGetMemoryWin32HandleKHR")) return (void *)table->GetMemoryWin32HandleKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetMemoryWin32HandlePropertiesKHR && !strcmp(name, "vkGetMemoryWin32HandlePropertiesKHR")) return (void *)table->GetMemoryWin32HandlePropertiesKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_memory_fd extension commands
    if (nameHash == XXH3_vkGetMemoryFdKHR && !strcmp(name, "vkGetMemoryFdKHR")) return (void *)table->GetMemoryFdKHR;
    if (nameHash == XXH3_vkGetMemoryFdPropertiesKHR && !strcmp(name, "vkGetMemoryFdPropertiesKHR")) return (void *)table->GetMemoryFdPropertiesKHR;

    // ---- VK_KHR_external_semaphore_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkImportSemaphoreWin32HandleKHR && !strcmp(name, "vkImportSemaphoreWin32HandleKHR")) return (void *)table->ImportSemaphoreWin32HandleKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetSemaphoreWin32HandleKHR && !strcmp(name, "vkGetSemaphoreWin32HandleKHR")) return (void *)table->GetSemaphoreWin32HandleKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_semaphore_fd extension commands
    if (nameHash == XXH3_vkImportSemaphoreFdKHR && !strcmp(name, "vkImportSemaphoreFdKHR")) return (void *)table->ImportSemaphoreFdKHR;
    if (nameHash == XXH3_vkGetSemaphoreFdKHR && !strcmp(name, "vkGetSemaphoreFdKHR")) return (void *)table->GetSemaphoreFdKHR;

    // ---- VK_KHR_push_descriptor extension commands
    if (nameHash == XXH3_vkCmdPushDescriptorSetKHR && !strcmp(name, "vkCmdPushDescriptorSetKHR")) return (void *)table->CmdPushDescriptorSetKHR;
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplateKHR && !strcmp(name, "vkCmdPushDescriptorSetWithTemplateKHR")) return (void *)table->CmdPushDescriptorSetWithTemplateKHR;

    // ---- VK_KHR_descriptor_update_template extension commands
    if (nameHash == XXH3_vkCreateDescriptorUpdateTemplateKHR && !strcmp(name, "vkCreateDescriptorUpdateTemplateKHR")) return (void *)table->CreateDescriptorUpdateTemplateKHR;
    if (nameHash == XXH3_vkDestroyDescriptorUpdateTemplateKHR && !strcmp(name, "vkDestroyDescriptorUpdateTemplateKHR")) return (void *)table->DestroyDescriptorUpdateTemplateKHR;
    if (nameHash == XXH3_vkUpdateDescriptorSetWithTemplateKHR && !strcmp(name, "vkUpdateDescriptorSetWithTemplateKHR")) return (void *)table->UpdateDescriptorSetWithTemplateKHR;

    // ---- VK_KHR_create_renderpass2 extension commands
    if (nameHash == XXH3_vkCreateRenderPass2KHR && !strcmp(name, "vkCreateRenderPass2KHR")) return (void *)table->CreateRenderPass2KHR;
    if (nameHash == XXH3_vkCmdBeginRenderPass2KHR && !strcmp(name, "vkCmdBeginRenderPass2KHR")) return (void *)table->CmdBeginRenderPass2KHR;
    if (nameHash == XXH3_vkCmdNextSubpass2KHR && !strcmp(name, "vkCmdNextSubpass2KHR")) return (void *)table->CmdNextSubpass2KHR;
    if (nameHash == XXH3_vkCmdEndRenderPass2KHR && !strcmp(name, "vkCmdEndRenderPass2KHR")) return (void *)table->CmdEndRenderPass2KHR;

    // ---- VK_KHR_shared_presentable_image extension commands
    if (nameHash == XXH3_vkGetSwapchainStatusKHR && !strcmp(name, "vkGetSwapchainStatusKHR")) return (void *)table->GetSwapchainStatusKHR;

    // ---- VK_KHR_external_fence_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkImportFenceWin32HandleKHR && !strcmp(name, "vkImportFenceWin32HandleKHR")) return (void *)table->ImportFenceWin32HandleKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetFenceWin32HandleKHR && !strcmp(name, "vkGetFenceWin32HandleKHR")) return (void *)table->GetFenceWin32HandleKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_fence_fd extension commands
    if (nameHash == XXH3_vkImportFenceFdKHR && !strcmp(name, "vkImportFenceFdKHR")) return (void *)table->ImportFenceFdKHR;
    if (nameHash == XXH3_vkGetFenceFdKHR && !strcmp(name, "vkGetFenceFdKHR")) return (void *)table->GetFenceFdKHR;

    // ---- VK_KHR_performance_query extension commands
    if (nameHash == XXH3_vkAcquireProfilingLockKHR && !strcmp(name, "vkAcquireProfilingLockKHR")) return (void *)table->AcquireProfilingLockKHR;
    if (nameHash == XXH3_vkReleaseProfilingLockKHR && !strcmp(name, "vkReleaseProfilingLockKHR")) return (void *)table->ReleaseProfilingLockKHR;

    // ---- VK_KHR_get_memory_requirements2 extension commands
    if (nameHash == XXH3_vkGetImageMemoryRequirements2KHR && !strcmp(name, "vkGetImageMemoryRequirements2KHR")) return (void *)table->GetImageMemoryRequirements2KHR;
    if (nameHash == XXH3_vkGetBufferMemoryRequirements2KHR && !strcmp(name, "vkGetBufferMemoryRequirements2KHR")) return (void *)table->GetBufferMemoryRequirements2KHR;
    if (nameHash == XXH3_vkGetImageSparseMemoryRequirements2KHR && !strcmp(name, "vkGetImageSparseMemoryRequirements2KHR")) return (void *)table->GetImageSparseMemoryRequirements2KHR;

    // ---- VK_KHR_sampler_ycbcr_conversion extension commands
    if (nameHash == XXH3_vkCreateSamplerYcbcrConversionKHR && !strcmp(name, "vkCreateSamplerYcbcrConversionKHR")) return (void *)table->CreateSamplerYcbcrConversionKHR;
    if (nameHash == XXH3_vkDestroySamplerYcbcrConversionKHR && !strcmp(name, "vkDestroySamplerYcbcrConversionKHR")) return (void *)table->DestroySamplerYcbcrConversionKHR;

    // ---- VK_KHR_bind_memory2 extension commands
    if (nameHash == XXH3_vkBindBufferMemory2KHR && !strcmp(name, "vkBindBufferMemory2KHR")) return (void *)table->BindBufferMemory2KHR;
    if (nameHash == XXH3_vkBindImageMemory2KHR && !strcmp(name, "vkBindImageMemory2KHR")) return (void *)table->BindImageMemory2KHR;

    // ---- VK_KHR_maintenance3 extension commands
    if (nameHash == XXH3_vkGetDescriptorSetLayoutSupportKHR && !strcmp(name, "vkGetDescriptorSetLayoutSupportKHR")) return (void *)table->GetDescriptorSetLayoutSupportKHR;

    // ---- VK_KHR_draw_indirect_count extension commands
    if (nameHash == XXH3_vkCmdDrawIndirectCountKHR && !strcmp(name, "vkCmdDrawIndirectCountKHR")) return (void *)table->CmdDrawIndirectCountKHR;
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCountKHR && !strcmp(name, "vkCmdDrawIndexedIndirectCountKHR")) return (void *)table->CmdDrawIndexedIndirectCountKHR;

    // ---- VK_KHR_timeline_semaphore extension commands
    if (nameHash == XXH3_vkGetSemaphoreCounterValueKHR && !strcmp(name, "vkGetSemaphoreCounterValueKHR")) return (void *)table->GetSemaphoreCounterValueKHR;
    if (nameHash == XXH3_vkWaitSemaphoresKHR && !strcmp(name, "vkWaitSemaphoresKHR")) return (void *)table->WaitSemaphoresKHR;
    if (nameHash == XXH3_vkSignalSemaphoreKHR && !strcmp(name, "vkSignalSemaphoreKHR")) return (void *)table->SignalSemaphoreKHR;

    // ---- VK_KHR_fragment_shading_rate extension commands
    if (nameHash == XXH3_vkCmdSetFragmentShadingRateKHR && !strcmp(name, "vkCmdSetFragmentShadingRateKHR")) return (void *)table->CmdSetFragmentShadingRateKHR;

    // ---- VK_KHR_dynamic_rendering_local_read extension commands
    if (nameHash == XXH3_vkCmdSetRenderingAttachmentLocationsKHR && !strcmp(name, "vkCmdSetRenderingAttachmentLocationsKHR")) return (void *)table->CmdSetRenderingAttachmentLocationsKHR;
    if (nameHash == XXH3_vkCmdSetRenderingInputAttachmentIndicesKHR && !strcmp(name, "vkCmdSetRenderingInputAttachmentIndicesKHR")) return (void *)table->CmdSetRenderingInputAttachmentIndicesKHR;

    // ---- VK_KHR_present_wait extension commands
    if (nameHash == XXH3_vkWaitForPresentKHR && !strcmp(name, "vkWaitForPresentKHR")) return (void *)table->WaitForPresentKHR;

    // ---- VK_KHR_buffer_device_address extension commands
    if (nameHash == XXH3_vkGetBufferDeviceAddressKHR && !strcmp(name, "vkGetBufferDeviceAddressKHR")) return (void *)table->GetBufferDeviceAddressKHR;
    if (nameHash == XXH3_vkGetBufferOpaqueCaptureAddressKHR && !strcmp(name, "vkGetBufferOpaqueCaptureAddressKHR")) return (void *)table->GetBufferOpaqueCaptureAddressKHR;
    if (nameHash == XXH3_vkGetDeviceMemoryOpaqueCaptureAddressKHR && !strcmp(name, "vkGetDeviceMemoryOpaqueCaptureAddressKHR")) return (void *)table->GetDeviceMemoryOpaqueCaptureAddressKHR;

    // ---- VK_KHR_deferred_host_operations extension commands
    if (nameHash == XXH3_vkCreateDeferredOperationKHR && !strcmp(name, "vkCreateDeferredOperationKHR")) return (void *)table->CreateDeferredOperationKHR;
    if (nameHash == XXH3_vkDestroyDeferredOperationKHR && !strcmp(name, "vkDestroyDeferredOperationKHR")) return (void *)table->DestroyDeferredOperationKHR;
    if (nameHash == XXH3_vkGetDeferredOperationMaxConcurrencyKHR && !strcmp(name, "vkGetDeferredOperationMaxConcurrencyKHR")) return (void *)table->GetDeferredOperationMaxConcurrencyKHR;
    if (nameHash == XXH3_vkGetDeferredOperationResultKHR && !strcmp(name, "vkGetDeferredOperationResultKHR")) return (void *)table->GetDeferredOperationResultKHR;
    if (nameHash == XXH3_vkDeferredOperationJoinKHR && !strcmp(name, "vkDeferredOperationJoinKHR")) return (void *)table->DeferredOperationJoinKHR;

    // ---- VK_KHR_pipeline_executable_properties extension commands
    if (nameHash == XXH3_vkGetPipelineExecutablePropertiesKHR && !strcmp(name, "vkGetPipelineExecutablePropertiesKHR")) return (void *)table->GetPipelineExecutablePropertiesKHR;
    if (nameHash == XXH3_vkGetPipelineExecutableStatisticsKHR && !strcmp(name, "vkGetPipelineExecutableStatisticsKHR")) return (void *)table->GetPipelineExecutableStatisticsKHR;
    if (nameHash == XXH3_vkGetPipelineExecutableInternalRepresentationsKHR && !strcmp(name, "vkGetPipelineExecutableInternalRepresentationsKHR")) return (void *)table->GetPipelineExecutableInternalRepresentationsKHR;

    // ---- VK_KHR_map_memory2 extension commands
    if (nameHash == XXH3_vkMapMemory2KHR && !strcmp(name, "vkMapMemory2KHR")) return (void *)table->MapMemory2KHR;
    if (nameHash == XXH3_vkUnmapMemory2KHR && !strcmp(name, "vkUnmapMemory2KHR")) return (void *)table->UnmapMemory2KHR;

    // ---- VK_KHR_video_encode_queue extension commands
    if (nameHash == XXH3_vkGetEncodedVideoSessionParametersKHR && !strcmp(name, "vkGetEncodedVideoSessionParametersKHR")) return (void *)table->GetEncodedVideoSessionParametersKHR;
    if (nameHash == XXH3_vkCmdEncodeVideoKHR && !strcmp(name, "vkCmdEncodeVideoKHR")) return (void *)table->CmdEncodeVideoKHR;

    // ---- VK_KHR_synchronization2 extension commands
    if (nameHash == XXH3_vkCmdSetEvent2KHR && !strcmp(name, "vkCmdSetEvent2KHR")) return (void *)table->CmdSetEvent2KHR;
    if (nameHash == XXH3_vkCmdResetEvent2KHR && !strcmp(name, "vkCmdResetEvent2KHR")) return (void *)table->CmdResetEvent2KHR;
    if (nameHash == XXH3_vkCmdWaitEvents2KHR && !strcmp(name, "vkCmdWaitEvents2KHR")) return (void *)table->CmdWaitEvents2KHR;
    if (nameHash == XXH3_vkCmdPipelineBarrier2KHR && !strcmp(name, "vkCmdPipelineBarrier2KHR")) return (void *)table->CmdPipelineBarrier2KHR;
    if (nameHash == XXH3_vkCmdWriteTimestamp2KHR && !strcmp(name, "vkCmdWriteTimestamp2KHR")) return (void *)table->CmdWriteTimestamp2KHR;
    if (nameHash == XXH3_vkQueueSubmit2KHR && !strcmp(name, "vkQueueSubmit2KHR")) return (void *)table->QueueSubmit2KHR;

    // ---- VK_KHR_device_address_commands extension commands
    if (nameHash == XXH3_vkCmdBindIndexBuffer3KHR && !strcmp(name, "vkCmdBindIndexBuffer3KHR")) return (void *)table->CmdBindIndexBuffer3KHR;
    if (nameHash == XXH3_vkCmdBindVertexBuffers3KHR && !strcmp(name, "vkCmdBindVertexBuffers3KHR")) return (void *)table->CmdBindVertexBuffers3KHR;
    if (nameHash == XXH3_vkCmdDrawIndirect2KHR && !strcmp(name, "vkCmdDrawIndirect2KHR")) return (void *)table->CmdDrawIndirect2KHR;
    if (nameHash == XXH3_vkCmdDrawIndexedIndirect2KHR && !strcmp(name, "vkCmdDrawIndexedIndirect2KHR")) return (void *)table->CmdDrawIndexedIndirect2KHR;
    if (nameHash == XXH3_vkCmdDispatchIndirect2KHR && !strcmp(name, "vkCmdDispatchIndirect2KHR")) return (void *)table->CmdDispatchIndirect2KHR;
    if (nameHash == XXH3_vkCmdCopyMemoryKHR && !strcmp(name, "vkCmdCopyMemoryKHR")) return (void *)table->CmdCopyMemoryKHR;
    if (nameHash == XXH3_vkCmdCopyMemoryToImageKHR && !strcmp(name, "vkCmdCopyMemoryToImageKHR")) return (void *)table->CmdCopyMemoryToImageKHR;
    if (nameHash == XXH3_vkCmdCopyImageToMemoryKHR && !strcmp(name, "vkCmdCopyImageToMemoryKHR")) return (void *)table->CmdCopyImageToMemoryKHR;
    if (nameHash == XXH3_vkCmdUpdateMemoryKHR && !strcmp(name, "vkCmdUpdateMemoryKHR")) return (void *)table->CmdUpdateMemoryKHR;
    if (nameHash == XXH3_vkCmdFillMemoryKHR && !strcmp(name, "vkCmdFillMemoryKHR")) return (void *)table->CmdFillMemoryKHR;
    if (nameHash == XXH3_vkCmdCopyQueryPoolResultsToMemoryKHR && !strcmp(name, "vkCmdCopyQueryPoolResultsToMemoryKHR")) return (void *)table->CmdCopyQueryPoolResultsToMemoryKHR;
    if (nameHash == XXH3_vkCmdDrawIndirectCount2KHR && !strcmp(name, "vkCmdDrawIndirectCount2KHR")) return (void *)table->CmdDrawIndirectCount2KHR;
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCount2KHR && !strcmp(name, "vkCmdDrawIndexedIndirectCount2KHR")) return (void *)table->CmdDrawIndexedIndirectCount2KHR;
    if (nameHash == XXH3_vkCmdBeginConditionalRendering2EXT && !strcmp(name, "vkCmdBeginConditionalRendering2EXT")) return (void *)table->CmdBeginConditionalRendering2EXT;
    if (nameHash == XXH3_vkCmdBindTransformFeedbackBuffers2EXT && !strcmp(name, "vkCmdBindTransformFeedbackBuffers2EXT")) return (void *)table->CmdBindTransformFeedbackBuffers2EXT;
    if (nameHash == XXH3_vkCmdBeginTransformFeedback2EXT && !strcmp(name, "vkCmdBeginTransformFeedback2EXT")) return (void *)table->CmdBeginTransformFeedback2EXT;
    if (nameHash == XXH3_vkCmdEndTransformFeedback2EXT && !strcmp(name, "vkCmdEndTransformFeedback2EXT")) return (void *)table->CmdEndTransformFeedback2EXT;
    if (nameHash == XXH3_vkCmdDrawIndirectByteCount2EXT && !strcmp(name, "vkCmdDrawIndirectByteCount2EXT")) return (void *)table->CmdDrawIndirectByteCount2EXT;
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirect2EXT && !strcmp(name, "vkCmdDrawMeshTasksIndirect2EXT")) return (void *)table->CmdDrawMeshTasksIndirect2EXT;
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectCount2EXT && !strcmp(name, "vkCmdDrawMeshTasksIndirectCount2EXT")) return (void *)table->CmdDrawMeshTasksIndirectCount2EXT;
    if (nameHash == XXH3_vkCmdWriteMarkerToMemoryAMD && !strcmp(name, "vkCmdWriteMarkerToMemoryAMD")) return (void *)table->CmdWriteMarkerToMemoryAMD;
    if (nameHash == XXH3_vkCreateAccelerationStructure2KHR && !strcmp(name, "vkCreateAccelerationStructure2KHR")) return (void *)table->CreateAccelerationStructure2KHR;

    // ---- VK_KHR_copy_commands2 extension commands
    if (nameHash == XXH3_vkCmdCopyBuffer2KHR && !strcmp(name, "vkCmdCopyBuffer2KHR")) return (void *)table->CmdCopyBuffer2KHR;
    if (nameHash == XXH3_vkCmdCopyImage2KHR && !strcmp(name, "vkCmdCopyImage2KHR")) return (void *)table->CmdCopyImage2KHR;
    if (nameHash == XXH3_vkCmdCopyBufferToImage2KHR && !strcmp(name, "vkCmdCopyBufferToImage2KHR")) return (void *)table->CmdCopyBufferToImage2KHR;
    if (nameHash == XXH3_vkCmdCopyImageToBuffer2KHR && !strcmp(name, "vkCmdCopyImageToBuffer2KHR")) return (void *)table->CmdCopyImageToBuffer2KHR;
    if (nameHash == XXH3_vkCmdBlitImage2KHR && !strcmp(name, "vkCmdBlitImage2KHR")) return (void *)table->CmdBlitImage2KHR;
    if (nameHash == XXH3_vkCmdResolveImage2KHR && !strcmp(name, "vkCmdResolveImage2KHR")) return (void *)table->CmdResolveImage2KHR;

    // ---- VK_KHR_ray_tracing_maintenance1 extension commands
    if (nameHash == XXH3_vkCmdTraceRaysIndirect2KHR && !strcmp(name, "vkCmdTraceRaysIndirect2KHR")) return (void *)table->CmdTraceRaysIndirect2KHR;

    // ---- VK_KHR_maintenance4 extension commands
    if (nameHash == XXH3_vkGetDeviceBufferMemoryRequirementsKHR && !strcmp(name, "vkGetDeviceBufferMemoryRequirementsKHR")) return (void *)table->GetDeviceBufferMemoryRequirementsKHR;
    if (nameHash == XXH3_vkGetDeviceImageMemoryRequirementsKHR && !strcmp(name, "vkGetDeviceImageMemoryRequirementsKHR")) return (void *)table->GetDeviceImageMemoryRequirementsKHR;
    if (nameHash == XXH3_vkGetDeviceImageSparseMemoryRequirementsKHR && !strcmp(name, "vkGetDeviceImageSparseMemoryRequirementsKHR")) return (void *)table->GetDeviceImageSparseMemoryRequirementsKHR;

    // ---- VK_KHR_maintenance5 extension commands
    if (nameHash == XXH3_vkCmdBindIndexBuffer2KHR && !strcmp(name, "vkCmdBindIndexBuffer2KHR")) return (void *)table->CmdBindIndexBuffer2KHR;
    if (nameHash == XXH3_vkGetRenderingAreaGranularityKHR && !strcmp(name, "vkGetRenderingAreaGranularityKHR")) return (void *)table->GetRenderingAreaGranularityKHR;
    if (nameHash == XXH3_vkGetDeviceImageSubresourceLayoutKHR && !strcmp(name, "vkGetDeviceImageSubresourceLayoutKHR")) return (void *)table->GetDeviceImageSubresourceLayoutKHR;
    if (nameHash == XXH3_vkGetImageSubresourceLayout2KHR && !strcmp(name, "vkGetImageSubresourceLayout2KHR")) return (void *)table->GetImageSubresourceLayout2KHR;

    // ---- VK_KHR_present_wait2 extension commands
    if (nameHash == XXH3_vkWaitForPresent2KHR && !strcmp(name, "vkWaitForPresent2KHR")) return (void *)table->WaitForPresent2KHR;

    // ---- VK_KHR_pipeline_binary extension commands
    if (nameHash == XXH3_vkCreatePipelineBinariesKHR && !strcmp(name, "vkCreatePipelineBinariesKHR")) return (void *)table->CreatePipelineBinariesKHR;
    if (nameHash == XXH3_vkDestroyPipelineBinaryKHR && !strcmp(name, "vkDestroyPipelineBinaryKHR")) return (void *)table->DestroyPipelineBinaryKHR;
    if (nameHash == XXH3_vkGetPipelineKeyKHR && !strcmp(name, "vkGetPipelineKeyKHR")) return (void *)table->GetPipelineKeyKHR;
    if (nameHash == XXH3_vkGetPipelineBinaryDataKHR && !strcmp(name, "vkGetPipelineBinaryDataKHR")) return (void *)table->GetPipelineBinaryDataKHR;
    if (nameHash == XXH3_vkReleaseCapturedPipelineDataKHR && !strcmp(name, "vkReleaseCapturedPipelineDataKHR")) return (void *)table->ReleaseCapturedPipelineDataKHR;

    // ---- VK_KHR_swapchain_maintenance1 extension commands
    if (nameHash == XXH3_vkReleaseSwapchainImagesKHR && !strcmp(name, "vkReleaseSwapchainImagesKHR")) return (void *)table->ReleaseSwapchainImagesKHR;

    // ---- VK_KHR_line_rasterization extension commands
    if (nameHash == XXH3_vkCmdSetLineStippleKHR && !strcmp(name, "vkCmdSetLineStippleKHR")) return (void *)table->CmdSetLineStippleKHR;

    // ---- VK_KHR_calibrated_timestamps extension commands
    if (nameHash == XXH3_vkGetCalibratedTimestampsKHR && !strcmp(name, "vkGetCalibratedTimestampsKHR")) return (void *)table->GetCalibratedTimestampsKHR;

    // ---- VK_KHR_maintenance6 extension commands
    if (nameHash == XXH3_vkCmdBindDescriptorSets2KHR && !strcmp(name, "vkCmdBindDescriptorSets2KHR")) return (void *)table->CmdBindDescriptorSets2KHR;
    if (nameHash == XXH3_vkCmdPushConstants2KHR && !strcmp(name, "vkCmdPushConstants2KHR")) return (void *)table->CmdPushConstants2KHR;
    if (nameHash == XXH3_vkCmdPushDescriptorSet2KHR && !strcmp(name, "vkCmdPushDescriptorSet2KHR")) return (void *)table->CmdPushDescriptorSet2KHR;
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplate2KHR && !strcmp(name, "vkCmdPushDescriptorSetWithTemplate2KHR")) return (void *)table->CmdPushDescriptorSetWithTemplate2KHR;
    if (nameHash == XXH3_vkCmdSetDescriptorBufferOffsets2EXT && !strcmp(name, "vkCmdSetDescriptorBufferOffsets2EXT")) return (void *)table->CmdSetDescriptorBufferOffsets2EXT;
    if (nameHash == XXH3_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT && !strcmp(name, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT")) return (void *)table->CmdBindDescriptorBufferEmbeddedSamplers2EXT;

    // ---- VK_KHR_copy_memory_indirect extension commands
    if (nameHash == XXH3_vkCmdCopyMemoryIndirectKHR && !strcmp(name, "vkCmdCopyMemoryIndirectKHR")) return (void *)table->CmdCopyMemoryIndirectKHR;
    if (nameHash == XXH3_vkCmdCopyMemoryToImageIndirectKHR && !strcmp(name, "vkCmdCopyMemoryToImageIndirectKHR")) return (void *)table->CmdCopyMemoryToImageIndirectKHR;

    // ---- VK_KHR_device_fault extension commands
    if (nameHash == XXH3_vkGetDeviceFaultReportsKHR && !strcmp(name, "vkGetDeviceFaultReportsKHR")) return (void *)table->GetDeviceFaultReportsKHR;
    if (nameHash == XXH3_vkGetDeviceFaultDebugInfoKHR && !strcmp(name, "vkGetDeviceFaultDebugInfoKHR")) return (void *)table->GetDeviceFaultDebugInfoKHR;

    // ---- VK_KHR_maintenance10 extension commands
    if (nameHash == XXH3_vkCmdEndRendering2KHR && !strcmp(name, "vkCmdEndRendering2KHR")) return (void *)table->CmdEndRendering2KHR;

    // ---- VK_EXT_debug_marker extension commands
    if (nameHash == XXH3_vkDebugMarkerSetObjectTagEXT && !strcmp(name, "vkDebugMarkerSetObjectTagEXT")) return dev->layer_extensions.ext_debug_marker_enabled ? (void *)DebugMarkerSetObjectTagEXT : NULL;
    if (nameHash == XXH3_vkDebugMarkerSetObjectNameEXT && !strcmp(name, "vkDebugMarkerSetObjectNameEXT")) return dev->layer_extensions.ext_debug_marker_enabled ? (void *)DebugMarkerSetObjectNameEXT : NULL;
    if (nameHash == XXH3_vkCmdDebugMarkerBeginEXT && !strcmp(name, "vkCmdDebugMarkerBeginEXT")) return (void *)table->CmdDebugMarkerBeginEXT;
    if (nameHash == XXH3_vkCmdDebugMarkerEndEXT && !strcmp(name, "vkCmdDebugMarkerEndEXT")) return (void *)table->CmdDebugMarkerEndEXT;
    if (nameHash == XXH3_vkCmdDebugMarkerInsertEXT && !strcmp(name, "vkCmdDebugMarkerInsertEXT")) return (void *)table->CmdDebugMarkerInsertEXT;

    // ---- VK_EXT_transform_feedback extension commands
    if (nameHash == XXH3_vkCmdBindTransformFeedbackBuffersEXT && !strcmp(name, "vkCmdBindTransformFeedbackBuffersEXT")) return (void *)table->CmdBindTransformFeedbackBuffersEXT;
    if (nameHash == XXH3_vkCmdBeginTransformFeedbackEXT && !strcmp(name, "vkCmdBeginTransformFeedbackEXT")) return (void *)table->CmdBeginTransformFeedbackEXT;
    if (nameHash == XXH3_vkCmdEndTransformFeedbackEXT && !strcmp(name, "vkCmdEndTransformFeedbackEXT")) return (void *)table->CmdEndTransformFeedbackEXT;
    if (nameHash == XXH3_vkCmdBeginQueryIndexedEXT && !strcmp(name, "vkCmdBeginQueryIndexedEXT")) return (void *)table->CmdBeginQueryIndexedEXT;
    if (nameHash == XXH3_vkCmdEndQueryIndexedEXT && !strcmp(name, "vkCmdEndQueryIndexedEXT")) return (void *)table->CmdEndQueryIndexedEXT;
    if (nameHash == XXH3_vkCmdDrawIndirectByteCountEXT && !strcmp(name, "vkCmdDrawIndirectByteCountEXT")) return (void *)table->CmdDrawIndirectByteCountEXT;

    // ---- VK_NVX_binary_import extension commands
    if (nameHash == XXH3_vkCreateCuModuleNVX && !strcmp(name, "vkCreateCuModuleNVX")) return (void *)table->CreateCuModuleNVX;
    if (nameHash == XXH3_vkCreateCuFunctionNVX && !strcmp(name, "vkCreateCuFunctionNVX")) return (void *)table->CreateCuFunctionNVX;
    if (nameHash == XXH3_vkDestroyCuModuleNVX && !strcmp(name, "vkDestroyCuModuleNVX")) return (void *)table->DestroyCuModuleNVX;
    if (nameHash == XXH3_vkDestroyCuFunctionNVX && !strcmp(name, "vkDestroyCuFunctionNVX")) return (void *)table->DestroyCuFunctionNVX;
    if (nameHash == XXH3_vkCmdCuLaunchKernelNVX && !strcmp(name, "vkCmdCuLaunchKernelNVX")) return (void *)table->CmdCuLaunchKernelNVX;

    // ---- VK_NVX_image_view_handle extension commands
    if (nameHash == XXH3_vkGetImageViewHandleNVX && !strcmp(name, "vkGetImageViewHandleNVX")) return (void *)table->GetImageViewHandleNVX;
    if (nameHash == XXH3_vkGetImageViewHandle64NVX && !strcmp(name, "vkGetImageViewHandle64NVX")) return (void *)table->GetImageViewHandle64NVX;
    if (nameHash == XXH3_vkGetImageViewAddressNVX && !strcmp(name, "vkGetImageViewAddressNVX")) return (void *)table->GetImageViewAddressNVX;
    if (nameHash == XXH3_vkGetDeviceCombinedImageSamplerIndexNVX && !strcmp(name, "vkGetDeviceCombinedImageSamplerIndexNVX")) return (void *)table->GetDeviceCombinedImageSamplerIndexNVX;

    // ---- VK_AMD_draw_indirect_count extension commands
    if (nameHash == XXH3_vkCmdDrawIndirectCountAMD && !strcmp(name, "vkCmdDrawIndirectCountAMD")) return (void *)table->CmdDrawIndirectCountAMD;
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCountAMD && !strcmp(name, "vkCmdDrawIndexedIndirectCountAMD")) return (void *)table->CmdDrawIndexedIndirectCountAMD;

    // ---- VK_AMD_shader_info extension commands
    if (nameHash == XXH3_vkGetShaderInfoAMD && !strcmp(name, "vkGetShaderInfoAMD")) return (void *)table->GetShaderInfoAMD;

    // ---- VK_NV_external_memory_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetMemoryWin32HandleNV && !strcmp(name, "vkGetMemoryWin32HandleNV")) return (void *)table->GetMemoryWin32HandleNV;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_conditional_rendering extension commands
    if (nameHash == XXH3_vkCmdBeginConditionalRenderingEXT && !strcmp(name, "vkCmdBeginConditionalRenderingEXT")) return (void *)table->CmdBeginConditionalRenderingEXT;
    if (nameHash == XXH3_vkCmdEndConditionalRenderingEXT && !strcmp(name, "vkCmdEndConditionalRenderingEXT")) return (void *)table->CmdEndConditionalRenderingEXT;

    // ---- VK_NV_clip_space_w_scaling extension commands
    if (nameHash == XXH3_vkCmdSetViewportWScalingNV && !strcmp(name, "vkCmdSetViewportWScalingNV")) return (void *)table->CmdSetViewportWScalingNV;

    // ---- VK_EXT_display_control extension commands
    if (nameHash == XXH3_vkDisplayPowerControlEXT && !strcmp(name, "vkDisplayPowerControlEXT")) return (void *)table->DisplayPowerControlEXT;
    if (nameHash == XXH3_vkRegisterDeviceEventEXT && !strcmp(name, "vkRegisterDeviceEventEXT")) return (void *)table->RegisterDeviceEventEXT;
    if (nameHash == XXH3_vkRegisterDisplayEventEXT && !strcmp(name, "vkRegisterDisplayEventEXT")) return (void *)table->RegisterDisplayEventEXT;
    if (nameHash == XXH3_vkGetSwapchainCounterEXT && !strcmp(name, "vkGetSwapchainCounterEXT")) return (void *)table->GetSwapchainCounterEXT;

    // ---- VK_GOOGLE_display_timing extension commands
    if (nameHash == XXH3_vkGetRefreshCycleDurationGOOGLE && !strcmp(name, "vkGetRefreshCycleDurationGOOGLE")) return (void *)table->GetRefreshCycleDurationGOOGLE;
    if (nameHash == XXH3_vkGetPastPresentationTimingGOOGLE && !strcmp(name, "vkGetPastPresentationTimingGOOGLE")) return (void *)table->GetPastPresentationTimingGOOGLE;

    // ---- VK_EXT_discard_rectangles extension commands
    if (nameHash == XXH3_vkCmdSetDiscardRectangleEXT && !strcmp(name, "vkCmdSetDiscardRectangleEXT")) return (void *)table->CmdSetDiscardRectangleEXT;
    if (nameHash == XXH3_vkCmdSetDiscardRectangleEnableEXT && !strcmp(name, "vkCmdSetDiscardRectangleEnableEXT")) return (void *)table->CmdSetDiscardRectangleEnableEXT;
    if (nameHash == XXH3_vkCmdSetDiscardRectangleModeEXT && !strcmp(name, "vkCmdSetDiscardRectangleModeEXT")) return (void *)table->CmdSetDiscardRectangleModeEXT;

    // ---- VK_EXT_hdr_metadata extension commands
    if (nameHash == XXH3_vkSetHdrMetadataEXT && !strcmp(name, "vkSetHdrMetadataEXT")) return (void *)table->SetHdrMetadataEXT;

    // ---- VK_EXT_debug_utils extension commands
    if (nameHash == XXH3_vkSetDebugUtilsObjectNameEXT && !strcmp(name, "vkSetDebugUtilsObjectNameEXT")) return dev->layer_extensions.ext_debug_utils_enabled ? (void *)SetDebugUtilsObjectNameEXT : NULL;
    if (nameHash == XXH3_vkSetDebugUtilsObjectTagEXT && !strcmp(name, "vkSetDebugUtilsObjectTagEXT")) return dev->layer_extensions.ext_debug_utils_enabled ? (void *)SetDebugUtilsObjectTagEXT : NULL;
    if (nameHash == XXH3_vkQueueBeginDebugUtilsLabelEXT && !strcmp(name, "vkQueueBeginDebugUtilsLabelEXT")) return (void *)table->QueueBeginDebugUtilsLabelEXT;
    if (nameHash == XXH3_vkQueueEndDebugUtilsLabelEXT && !strcmp(name, "vkQueueEndDebugUtilsLabelEXT")) return (void *)table->QueueEndDebugUtilsLabelEXT;
    if (nameHash == XXH3_vkQueueInsertDebugUtilsLabelEXT && !strcmp(name, "vkQueueInsertDebugUtilsLabelEXT")) return (void *)table->QueueInsertDebugUtilsLabelEXT;
    if (nameHash == XXH3_vkCmdBeginDebugUtilsLabelEXT && !strcmp(name, "vkCmdBeginDebugUtilsLabelEXT")) return (void *)table->CmdBeginDebugUtilsLabelEXT;
    if (nameHash == XXH3_vkCmdEndDebugUtilsLabelEXT && !strcmp(name, "vkCmdEndDebugUtilsLabelEXT")) return (void *)table->CmdEndDebugUtilsLabelEXT;
    if (nameHash == XXH3_vkCmdInsertDebugUtilsLabelEXT && !strcmp(name, "vkCmdInsertDebugUtilsLabelEXT")) return (void *)table->CmdInsertDebugUtilsLabelEXT;

    // ---- VK_ANDROID_external_memory_android_hardware_buffer extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    if (nameHash == XXH3_vkGetAndroidHardwareBufferPropertiesANDROID && !strcmp(name, "vkGetAndroidHardwareBufferPropertiesANDROID")) return (void *)table->GetAndroidHardwareBufferPropertiesANDROID;
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    if (nameHash == XXH3_vkGetMemoryAndroidHardwareBufferANDROID && !strcmp(name, "vkGetMemoryAndroidHardwareBufferANDROID")) return (void *)table->GetMemoryAndroidHardwareBufferANDROID;
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_AMD_gpa_interface extension commands
    if (nameHash == XXH3_vkCreateGpaSessionAMD && !strcmp(name, "vkCreateGpaSessionAMD")) return (void *)table->CreateGpaSessionAMD;
    if (nameHash == XXH3_vkDestroyGpaSessionAMD && !strcmp(name, "vkDestroyGpaSessionAMD")) return (void *)table->DestroyGpaSessionAMD;
    if (nameHash == XXH3_vkSetGpaDeviceClockModeAMD && !strcmp(name, "vkSetGpaDeviceClockModeAMD")) return (void *)table->SetGpaDeviceClockModeAMD;
    if (nameHash == XXH3_vkGetGpaDeviceClockInfoAMD && !strcmp(name, "vkGetGpaDeviceClockInfoAMD")) return (void *)table->GetGpaDeviceClockInfoAMD;
    if (nameHash == XXH3_vkCmdBeginGpaSessionAMD && !strcmp(name, "vkCmdBeginGpaSessionAMD")) return (void *)table->CmdBeginGpaSessionAMD;
    if (nameHash == XXH3_vkCmdEndGpaSessionAMD && !strcmp(name, "vkCmdEndGpaSessionAMD")) return (void *)table->CmdEndGpaSessionAMD;
    if (nameHash == XXH3_vkCmdBeginGpaSampleAMD && !strcmp(name, "vkCmdBeginGpaSampleAMD")) return (void *)table->CmdBeginGpaSampleAMD;
    if (nameHash == XXH3_vkCmdEndGpaSampleAMD && !strcmp(name, "vkCmdEndGpaSampleAMD")) return (void *)table->CmdEndGpaSampleAMD;
    if (nameHash == XXH3_vkGetGpaSessionStatusAMD && !strcmp(name, "vkGetGpaSessionStatusAMD")) return (void *)table->GetGpaSessionStatusAMD;
    if (nameHash == XXH3_vkGetGpaSessionResultsAMD && !strcmp(name, "vkGetGpaSessionResultsAMD")) return (void *)table->GetGpaSessionResultsAMD;
    if (nameHash == XXH3_vkResetGpaSessionAMD && !strcmp(name, "vkResetGpaSessionAMD")) return (void *)table->ResetGpaSessionAMD;
    if (nameHash == XXH3_vkCmdCopyGpaSessionResultsAMD && !strcmp(name, "vkCmdCopyGpaSessionResultsAMD")) return (void *)table->CmdCopyGpaSessionResultsAMD;

    // ---- VK_AMDX_shader_enqueue extension commands
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCreateExecutionGraphPipelinesAMDX && !strcmp(name, "vkCreateExecutionGraphPipelinesAMDX")) return (void *)table->CreateExecutionGraphPipelinesAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkGetExecutionGraphPipelineScratchSizeAMDX && !strcmp(name, "vkGetExecutionGraphPipelineScratchSizeAMDX")) return (void *)table->GetExecutionGraphPipelineScratchSizeAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkGetExecutionGraphPipelineNodeIndexAMDX && !strcmp(name, "vkGetExecutionGraphPipelineNodeIndexAMDX")) return (void *)table->GetExecutionGraphPipelineNodeIndexAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdInitializeGraphScratchMemoryAMDX && !strcmp(name, "vkCmdInitializeGraphScratchMemoryAMDX")) return (void *)table->CmdInitializeGraphScratchMemoryAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdDispatchGraphAMDX && !strcmp(name, "vkCmdDispatchGraphAMDX")) return (void *)table->CmdDispatchGraphAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdDispatchGraphIndirectAMDX && !strcmp(name, "vkCmdDispatchGraphIndirectAMDX")) return (void *)table->CmdDispatchGraphIndirectAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdDispatchGraphIndirectCountAMDX && !strcmp(name, "vkCmdDispatchGraphIndirectCountAMDX")) return (void *)table->CmdDispatchGraphIndirectCountAMDX;
#endif // VK_ENABLE_BETA_EXTENSIONS

    // ---- VK_EXT_descriptor_heap extension commands
    if (nameHash == XXH3_vkWriteSamplerDescriptorsEXT && !strcmp(name, "vkWriteSamplerDescriptorsEXT")) return (void *)table->WriteSamplerDescriptorsEXT;
    if (nameHash == XXH3_vkWriteResourceDescriptorsEXT && !strcmp(name, "vkWriteResourceDescriptorsEXT")) return (void *)table->WriteResourceDescriptorsEXT;
    if (nameHash == XXH3_vkCmdBindSamplerHeapEXT && !strcmp(name, "vkCmdBindSamplerHeapEXT")) return (void *)table->CmdBindSamplerHeapEXT;
    if (nameHash == XXH3_vkCmdBindResourceHeapEXT && !strcmp(name, "vkCmdBindResourceHeapEXT")) return (void *)table->CmdBindResourceHeapEXT;
    if (nameHash == XXH3_vkCmdPushDataEXT && !strcmp(name, "vkCmdPushDataEXT")) return (void *)table->CmdPushDataEXT;
    if (nameHash == XXH3_vkGetImageOpaqueCaptureDataEXT && !strcmp(name, "vkGetImageOpaqueCaptureDataEXT")) return (void *)table->GetImageOpaqueCaptureDataEXT;
    if (nameHash == XXH3_vkRegisterCustomBorderColorEXT && !strcmp(name, "vkRegisterCustomBorderColorEXT")) return (void *)table->RegisterCustomBorderColorEXT;
    if (nameHash == XXH3_vkUnregisterCustomBorderColorEXT && !strcmp(name, "vkUnregisterCustomBorderColorEXT")) return (void *)table->UnregisterCustomBorderColorEXT;
    if (nameHash == XXH3_vkGetTensorOpaqueCaptureDataARM && !strcmp(name, "vkGetTensorOpaqueCaptureDataARM")) return (void *)table->GetTensorOpaqueCaptureDataARM;

    // ---- VK_EXT_sample_locations extension commands
    if (nameHash == XXH3_vkCmdSetSampleLocationsEXT && !strcmp(name, "vkCmdSetSampleLocationsEXT")) return (void *)table->CmdSetSampleLocationsEXT;

    // ---- VK_EXT_image_drm_format_modifier extension commands
    if (nameHash == XXH3_vkGetImageDrmFormatModifierPropertiesEXT && !strcmp(name, "vkGetImageDrmFormatModifierPropertiesEXT")) return (void *)table->GetImageDrmFormatModifierPropertiesEXT;

    // ---- VK_EXT_validation_cache extension commands
    if (nameHash == XXH3_vkCreateValidationCacheEXT && !strcmp(name, "vkCreateValidationCacheEXT")) return (void *)table->CreateValidationCacheEXT;
    if (nameHash == XXH3_vkDestroyValidationCacheEXT && !strcmp(name, "vkDestroyValidationCacheEXT")) return (void *)table->DestroyValidationCacheEXT;
    if (nameHash == XXH3_vkMergeValidationCachesEXT && !strcmp(name, "vkMergeValidationCachesEXT")) return (void *)table->MergeValidationCachesEXT;
    if (nameHash == XXH3_vkGetValidationCacheDataEXT && !strcmp(name, "vkGetValidationCacheDataEXT")) return (void *)table->GetValidationCacheDataEXT;

    // ---- VK_NV_shading_rate_image extension commands
    if (nameHash == XXH3_vkCmdBindShadingRateImageNV && !strcmp(name, "vkCmdBindShadingRateImageNV")) return (void *)table->CmdBindShadingRateImageNV;
    if (nameHash == XXH3_vkCmdSetViewportShadingRatePaletteNV && !strcmp(name, "vkCmdSetViewportShadingRatePaletteNV")) return (void *)table->CmdSetViewportShadingRatePaletteNV;
    if (nameHash == XXH3_vkCmdSetCoarseSampleOrderNV && !strcmp(name, "vkCmdSetCoarseSampleOrderNV")) return (void *)table->CmdSetCoarseSampleOrderNV;

    // ---- VK_NV_ray_tracing extension commands
    if (nameHash == XXH3_vkCreateAccelerationStructureNV && !strcmp(name, "vkCreateAccelerationStructureNV")) return (void *)table->CreateAccelerationStructureNV;
    if (nameHash == XXH3_vkDestroyAccelerationStructureNV && !strcmp(name, "vkDestroyAccelerationStructureNV")) return (void *)table->DestroyAccelerationStructureNV;
    if (nameHash == XXH3_vkGetAccelerationStructureMemoryRequirementsNV && !strcmp(name, "vkGetAccelerationStructureMemoryRequirementsNV")) return (void *)table->GetAccelerationStructureMemoryRequirementsNV;
    if (nameHash == XXH3_vkBindAccelerationStructureMemoryNV && !strcmp(name, "vkBindAccelerationStructureMemoryNV")) return (void *)table->BindAccelerationStructureMemoryNV;
    if (nameHash == XXH3_vkCmdBuildAccelerationStructureNV && !strcmp(name, "vkCmdBuildAccelerationStructureNV")) return (void *)table->CmdBuildAccelerationStructureNV;
    if (nameHash == XXH3_vkCmdCopyAccelerationStructureNV && !strcmp(name, "vkCmdCopyAccelerationStructureNV")) return (void *)table->CmdCopyAccelerationStructureNV;
    if (nameHash == XXH3_vkCmdTraceRaysNV && !strcmp(name, "vkCmdTraceRaysNV")) return (void *)table->CmdTraceRaysNV;
    if (nameHash == XXH3_vkCreateRayTracingPipelinesNV && !strcmp(name, "vkCreateRayTracingPipelinesNV")) return (void *)table->CreateRayTracingPipelinesNV;

    // ---- VK_KHR_ray_tracing_pipeline extension commands
    if (nameHash == XXH3_vkGetRayTracingShaderGroupHandlesKHR && !strcmp(name, "vkGetRayTracingShaderGroupHandlesKHR")) return (void *)table->GetRayTracingShaderGroupHandlesKHR;

    // ---- VK_NV_ray_tracing extension commands
    if (nameHash == XXH3_vkGetRayTracingShaderGroupHandlesNV && !strcmp(name, "vkGetRayTracingShaderGroupHandlesNV")) return (void *)table->GetRayTracingShaderGroupHandlesNV;
    if (nameHash == XXH3_vkGetAccelerationStructureHandleNV && !strcmp(name, "vkGetAccelerationStructureHandleNV")) return (void *)table->GetAccelerationStructureHandleNV;
    if (nameHash == XXH3_vkCmdWriteAccelerationStructuresPropertiesNV && !strcmp(name, "vkCmdWriteAccelerationStructuresPropertiesNV")) return (void *)table->CmdWriteAccelerationStructuresPropertiesNV;
    if (nameHash == XXH3_vkCompileDeferredNV && !strcmp(name, "vkCompileDeferredNV")) return (void *)table->CompileDeferredNV;

    // ---- VK_EXT_external_memory_host extension commands
    if (nameHash == XXH3_vkGetMemoryHostPointerPropertiesEXT && !strcmp(name, "vkGetMemoryHostPointerPropertiesEXT")) return (void *)table->GetMemoryHostPointerPropertiesEXT;

    // ---- VK_AMD_buffer_marker extension commands
    if (nameHash == XXH3_vkCmdWriteBufferMarkerAMD && !strcmp(name, "vkCmdWriteBufferMarkerAMD")) return (void *)table->CmdWriteBufferMarkerAMD;
    if (nameHash == XXH3_vkCmdWriteBufferMarker2AMD && !strcmp(name, "vkCmdWriteBufferMarker2AMD")) return (void *)table->CmdWriteBufferMarker2AMD;

    // ---- VK_EXT_calibrated_timestamps extension commands
    if (nameHash == XXH3_vkGetCalibratedTimestampsEXT && !strcmp(name, "vkGetCalibratedTimestampsEXT")) return (void *)table->GetCalibratedTimestampsEXT;

    // ---- VK_NV_mesh_shader extension commands
    if (nameHash == XXH3_vkCmdDrawMeshTasksNV && !strcmp(name, "vkCmdDrawMeshTasksNV")) return (void *)table->CmdDrawMeshTasksNV;
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectNV && !strcmp(name, "vkCmdDrawMeshTasksIndirectNV")) return (void *)table->CmdDrawMeshTasksIndirectNV;
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectCountNV && !strcmp(name, "vkCmdDrawMeshTasksIndirectCountNV")) return (void *)table->CmdDrawMeshTasksIndirectCountNV;

    // ---- VK_NV_scissor_exclusive extension commands
    if (nameHash == XXH3_vkCmdSetExclusiveScissorEnableNV && !strcmp(name, "vkCmdSetExclusiveScissorEnableNV")) return (void *)table->CmdSetExclusiveScissorEnableNV;
    if (nameHash == XXH3_vkCmdSetExclusiveScissorNV && !strcmp(name, "vkCmdSetExclusiveScissorNV")) return (void *)table->CmdSetExclusiveScissorNV;

    // ---- VK_NV_device_diagnostic_checkpoints extension commands
    if (nameHash == XXH3_vkCmdSetCheckpointNV && !strcmp(name, "vkCmdSetCheckpointNV")) return (void *)table->CmdSetCheckpointNV;
    if (nameHash == XXH3_vkGetQueueCheckpointDataNV && !strcmp(name, "vkGetQueueCheckpointDataNV")) return (void *)table->GetQueueCheckpointDataNV;
    if (nameHash == XXH3_vkGetQueueCheckpointData2NV && !strcmp(name, "vkGetQueueCheckpointData2NV")) return (void *)table->GetQueueCheckpointData2NV;

    // ---- VK_EXT_present_timing extension commands
    if (nameHash == XXH3_vkSetSwapchainPresentTimingQueueSizeEXT && !strcmp(name, "vkSetSwapchainPresentTimingQueueSizeEXT")) return (void *)table->SetSwapchainPresentTimingQueueSizeEXT;
    if (nameHash == XXH3_vkGetSwapchainTimingPropertiesEXT && !strcmp(name, "vkGetSwapchainTimingPropertiesEXT")) return (void *)table->GetSwapchainTimingPropertiesEXT;
    if (nameHash == XXH3_vkGetSwapchainTimeDomainPropertiesEXT && !strcmp(name, "vkGetSwapchainTimeDomainPropertiesEXT")) return (void *)table->GetSwapchainTimeDomainPropertiesEXT;
    if (nameHash == XXH3_vkGetPastPresentationTimingEXT && !strcmp(name, "vkGetPastPresentationTimingEXT")) return (void *)table->GetPastPresentationTimingEXT;

    // ---- VK_INTEL_performance_query extension commands
    if (nameHash == XXH3_vkInitializePerformanceApiINTEL && !strcmp(name, "vkInitializePerformanceApiINTEL")) return (void *)table->InitializePerformanceApiINTEL;
    if (nameHash == XXH3_vkUninitializePerformanceApiINTEL && !strcmp(name, "vkUninitializePerformanceApiINTEL")) return (void *)table->UninitializePerformanceApiINTEL;
    if (nameHash == XXH3_vkCmdSetPerformanceMarkerINTEL && !strcmp(name, "vkCmdSetPerformanceMarkerINTEL")) return (void *)table->CmdSetPerformanceMarkerINTEL;
    if (nameHash == XXH3_vkCmdSetPerformanceStreamMarkerINTEL && !strcmp(name, "vkCmdSetPerformanceStreamMarkerINTEL")) return (void *)table->CmdSetPerformanceStreamMarkerINTEL;
    if (nameHash == XXH3_vkCmdSetPerformanceOverrideINTEL && !strcmp(name, "vkCmdSetPerformanceOverrideINTEL")) return (void *)table->CmdSetPerformanceOverrideINTEL;
    if (nameHash == XXH3_vkAcquirePerformanceConfigurationINTEL && !strcmp(name, "vkAcquirePerformanceConfigurationINTEL")) return (void *)table->AcquirePerformanceConfigurationINTEL;
    if (nameHash == XXH3_vkReleasePerformanceConfigurationINTEL && !strcmp(name, "vkReleasePerformanceConfigurationINTEL")) return (void *)table->ReleasePerformanceConfigurationINTEL;
    if (nameHash == XXH3_vkQueueSetPerformanceConfigurationINTEL && !strcmp(name, "vkQueueSetPerformanceConfigurationINTEL")) return (void *)table->QueueSetPerformanceConfigurationINTEL;
    if (nameHash == XXH3_vkGetPerformanceParameterINTEL && !strcmp(name, "vkGetPerformanceParameterINTEL")) return (void *)table->GetPerformanceParameterINTEL;

    // ---- VK_AMD_display_native_hdr extension commands
    if (nameHash == XXH3_vkSetLocalDimmingAMD && !strcmp(name, "vkSetLocalDimmingAMD")) return (void *)table->SetLocalDimmingAMD;

    // ---- VK_EXT_buffer_device_address extension commands
    if (nameHash == XXH3_vkGetBufferDeviceAddressEXT && !strcmp(name, "vkGetBufferDeviceAddressEXT")) return (void *)table->GetBufferDeviceAddressEXT;

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkAcquireFullScreenExclusiveModeEXT && !strcmp(name, "vkAcquireFullScreenExclusiveModeEXT")) return (void *)table->AcquireFullScreenExclusiveModeEXT;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkReleaseFullScreenExclusiveModeEXT && !strcmp(name, "vkReleaseFullScreenExclusiveModeEXT")) return (void *)table->ReleaseFullScreenExclusiveModeEXT;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetDeviceGroupSurfacePresentModes2EXT && !strcmp(name, "vkGetDeviceGroupSurfacePresentModes2EXT")) return (void *)table->GetDeviceGroupSurfacePresentModes2EXT;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_line_rasterization extension commands
    if (nameHash == XXH3_vkCmdSetLineStippleEXT && !strcmp(name, "vkCmdSetLineStippleEXT")) return (void *)table->CmdSetLineStippleEXT;

    // ---- VK_EXT_host_query_reset extension commands
    if (nameHash == XXH3_vkResetQueryPoolEXT && !strcmp(name, "vkResetQueryPoolEXT")) return (void *)table->ResetQueryPoolEXT;

    // ---- VK_EXT_extended_dynamic_state extension commands
    if (nameHash == XXH3_vkCmdSetCullModeEXT && !strcmp(name, "vkCmdSetCullModeEXT")) return (void *)table->CmdSetCullModeEXT;
    if (nameHash == XXH3_vkCmdSetFrontFaceEXT && !strcmp(name, "vkCmdSetFrontFaceEXT")) return (void *)table->CmdSetFrontFaceEXT;
    if (nameHash == XXH3_vkCmdSetPrimitiveTopologyEXT && !strcmp(name, "vkCmdSetPrimitiveTopologyEXT")) return (void *)table->CmdSetPrimitiveTopologyEXT;
    if (nameHash == XXH3_vkCmdSetViewportWithCountEXT && !strcmp(name, "vkCmdSetViewportWithCountEXT")) return (void *)table->CmdSetViewportWithCountEXT;
    if (nameHash == XXH3_vkCmdSetScissorWithCountEXT && !strcmp(name, "vkCmdSetScissorWithCountEXT")) return (void *)table->CmdSetScissorWithCountEXT;
    if (nameHash == XXH3_vkCmdBindVertexBuffers2EXT && !strcmp(name, "vkCmdBindVertexBuffers2EXT")) return (void *)table->CmdBindVertexBuffers2EXT;
    if (nameHash == XXH3_vkCmdSetDepthTestEnableEXT && !strcmp(name, "vkCmdSetDepthTestEnableEXT")) return (void *)table->CmdSetDepthTestEnableEXT;
    if (nameHash == XXH3_vkCmdSetDepthWriteEnableEXT && !strcmp(name, "vkCmdSetDepthWriteEnableEXT")) return (void *)table->CmdSetDepthWriteEnableEXT;
    if (nameHash == XXH3_vkCmdSetDepthCompareOpEXT && !strcmp(name, "vkCmdSetDepthCompareOpEXT")) return (void *)table->CmdSetDepthCompareOpEXT;
    if (nameHash == XXH3_vkCmdSetDepthBoundsTestEnableEXT && !strcmp(name, "vkCmdSetDepthBoundsTestEnableEXT")) return (void *)table->CmdSetDepthBoundsTestEnableEXT;
    if (nameHash == XXH3_vkCmdSetStencilTestEnableEXT && !strcmp(name, "vkCmdSetStencilTestEnableEXT")) return (void *)table->CmdSetStencilTestEnableEXT;
    if (nameHash == XXH3_vkCmdSetStencilOpEXT && !strcmp(name, "vkCmdSetStencilOpEXT")) return (void *)table->CmdSetStencilOpEXT;

    // ---- VK_EXT_host_image_copy extension commands
    if (nameHash == XXH3_vkCopyMemoryToImageEXT && !strcmp(name, "vkCopyMemoryToImageEXT")) return (void *)table->CopyMemoryToImageEXT;
    if (nameHash == XXH3_vkCopyImageToMemoryEXT && !strcmp(name, "vkCopyImageToMemoryEXT")) return (void *)table->CopyImageToMemoryEXT;
    if (nameHash == XXH3_vkCopyImageToImageEXT && !strcmp(name, "vkCopyImageToImageEXT")) return (void *)table->CopyImageToImageEXT;
    if (nameHash == XXH3_vkTransitionImageLayoutEXT && !strcmp(name, "vkTransitionImageLayoutEXT")) return (void *)table->TransitionImageLayoutEXT;
    if (nameHash == XXH3_vkGetImageSubresourceLayout2EXT && !strcmp(name, "vkGetImageSubresourceLayout2EXT")) return (void *)table->GetImageSubresourceLayout2EXT;

    // ---- VK_EXT_swapchain_maintenance1 extension commands
    if (nameHash == XXH3_vkReleaseSwapchainImagesEXT && !strcmp(name, "vkReleaseSwapchainImagesEXT")) return (void *)table->ReleaseSwapchainImagesEXT;

    // ---- VK_NV_device_generated_commands extension commands
    if (nameHash == XXH3_vkGetGeneratedCommandsMemoryRequirementsNV && !strcmp(name, "vkGetGeneratedCommandsMemoryRequirementsNV")) return (void *)table->GetGeneratedCommandsMemoryRequirementsNV;
    if (nameHash == XXH3_vkCmdPreprocessGeneratedCommandsNV && !strcmp(name, "vkCmdPreprocessGeneratedCommandsNV")) return (void *)table->CmdPreprocessGeneratedCommandsNV;
    if (nameHash == XXH3_vkCmdExecuteGeneratedCommandsNV && !strcmp(name, "vkCmdExecuteGeneratedCommandsNV")) return (void *)table->CmdExecuteGeneratedCommandsNV;
    if (nameHash == XXH3_vkCmdBindPipelineShaderGroupNV && !strcmp(name, "vkCmdBindPipelineShaderGroupNV")) return (void *)table->CmdBindPipelineShaderGroupNV;
    if (nameHash == XXH3_vkCreateIndirectCommandsLayoutNV && !strcmp(name, "vkCreateIndirectCommandsLayoutNV")) return (void *)table->CreateIndirectCommandsLayoutNV;
    if (nameHash == XXH3_vkDestroyIndirectCommandsLayoutNV && !strcmp(name, "vkDestroyIndirectCommandsLayoutNV")) return (void *)table->DestroyIndirectCommandsLayoutNV;

    // ---- VK_EXT_depth_bias_control extension commands
    if (nameHash == XXH3_vkCmdSetDepthBias2EXT && !strcmp(name, "vkCmdSetDepthBias2EXT")) return (void *)table->CmdSetDepthBias2EXT;

    // ---- VK_EXT_private_data extension commands
    if (nameHash == XXH3_vkCreatePrivateDataSlotEXT && !strcmp(name, "vkCreatePrivateDataSlotEXT")) return (void *)table->CreatePrivateDataSlotEXT;
    if (nameHash == XXH3_vkDestroyPrivateDataSlotEXT && !strcmp(name, "vkDestroyPrivateDataSlotEXT")) return (void *)table->DestroyPrivateDataSlotEXT;
    if (nameHash == XXH3_vkSetPrivateDataEXT && !strcmp(name, "vkSetPrivateDataEXT")) return (void *)table->SetPrivateDataEXT;
    if (nameHash == XXH3_vkGetPrivateDataEXT && !strcmp(name, "vkGetPrivateDataEXT")) return (void *)table->GetPrivateDataEXT;

    // ---- VK_QCOM_queue_perf_hint extension commands
    if (nameHash == XXH3_vkQueueSetPerfHintQCOM && !strcmp(name, "vkQueueSetPerfHintQCOM")) return (void *)table->QueueSetPerfHintQCOM;

    // ---- VK_NV_cuda_kernel_launch extension commands
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCreateCudaModuleNV && !strcmp(name, "vkCreateCudaModuleNV")) return (void *)table->CreateCudaModuleNV;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkGetCudaModuleCacheNV && !strcmp(name, "vkGetCudaModuleCacheNV")) return (void *)table->GetCudaModuleCacheNV;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCreateCudaFunctionNV && !strcmp(name, "vkCreateCudaFunctionNV")) return (void *)table->CreateCudaFunctionNV;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkDestroyCudaModuleNV && !strcmp(name, "vkDestroyCudaModuleNV")) return (void *)table->DestroyCudaModuleNV;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkDestroyCudaFunctionNV && !strcmp(name, "vkDestroyCudaFunctionNV")) return (void *)table->DestroyCudaFunctionNV;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdCudaLaunchKernelNV && !strcmp(name, "vkCmdCudaLaunchKernelNV")) return (void *)table->CmdCudaLaunchKernelNV;
#endif // VK_ENABLE_BETA_EXTENSIONS

    // ---- VK_QCOM_tile_shading extension commands
    if (nameHash == XXH3_vkCmdDispatchTileQCOM && !strcmp(name, "vkCmdDispatchTileQCOM")) return (void *)table->CmdDispatchTileQCOM;
    if (nameHash == XXH3_vkCmdBeginPerTileExecutionQCOM && !strcmp(name, "vkCmdBeginPerTileExecutionQCOM")) return (void *)table->CmdBeginPerTileExecutionQCOM;
    if (nameHash == XXH3_vkCmdEndPerTileExecutionQCOM && !strcmp(name, "vkCmdEndPerTileExecutionQCOM")) return (void *)table->CmdEndPerTileExecutionQCOM;

    // ---- VK_NV_low_latency extension commands
    if (nameHash == XXH3_vkSetLatencySleepModeLegacyNV && !strcmp(name, "vkSetLatencySleepModeLegacyNV")) return (void *)table->SetLatencySleepModeLegacyNV;
    if (nameHash == XXH3_vkLatencySleepLegacyNV && !strcmp(name, "vkLatencySleepLegacyNV")) return (void *)table->LatencySleepLegacyNV;
    if (nameHash == XXH3_vkSetLatencyMarkerLegacyNV && !strcmp(name, "vkSetLatencyMarkerLegacyNV")) return (void *)table->SetLatencyMarkerLegacyNV;
    if (nameHash == XXH3_vkGetLatencyTimingsLegacyNV && !strcmp(name, "vkGetLatencyTimingsLegacyNV")) return (void *)table->GetLatencyTimingsLegacyNV;
    if (nameHash == XXH3_vkQueueNotifyOutOfBandLegacyNV && !strcmp(name, "vkQueueNotifyOutOfBandLegacyNV")) return (void *)table->QueueNotifyOutOfBandLegacyNV;
    if (nameHash == XXH3_vkGetSleepStatusLegacyNV && !strcmp(name, "vkGetSleepStatusLegacyNV")) return (void *)table->GetSleepStatusLegacyNV;
    if (nameHash == XXH3_vkShutdownLatencyDeviceLegacyNV && !strcmp(name, "vkShutdownLatencyDeviceLegacyNV")) return (void *)table->ShutdownLatencyDeviceLegacyNV;

    // ---- VK_EXT_metal_objects extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkExportMetalObjectsEXT && !strcmp(name, "vkExportMetalObjectsEXT")) return (void *)table->ExportMetalObjectsEXT;
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_descriptor_buffer extension commands
    if (nameHash == XXH3_vkGetDescriptorSetLayoutSizeEXT && !strcmp(name, "vkGetDescriptorSetLayoutSizeEXT")) return (void *)table->GetDescriptorSetLayoutSizeEXT;
    if (nameHash == XXH3_vkGetDescriptorSetLayoutBindingOffsetEXT && !strcmp(name, "vkGetDescriptorSetLayoutBindingOffsetEXT")) return (void *)table->GetDescriptorSetLayoutBindingOffsetEXT;
    if (nameHash == XXH3_vkGetDescriptorEXT && !strcmp(name, "vkGetDescriptorEXT")) return (void *)table->GetDescriptorEXT;
    if (nameHash == XXH3_vkCmdBindDescriptorBuffersEXT && !strcmp(name, "vkCmdBindDescriptorBuffersEXT")) return (void *)table->CmdBindDescriptorBuffersEXT;
    if (nameHash == XXH3_vkCmdSetDescriptorBufferOffsetsEXT && !strcmp(name, "vkCmdSetDescriptorBufferOffsetsEXT")) return (void *)table->CmdSetDescriptorBufferOffsetsEXT;
    if (nameHash == XXH3_vkCmdBindDescriptorBufferEmbeddedSamplersEXT && !strcmp(name, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT")) return (void *)table->CmdBindDescriptorBufferEmbeddedSamplersEXT;
    if (nameHash == XXH3_vkGetBufferOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetBufferOpaqueCaptureDescriptorDataEXT")) return (void *)table->GetBufferOpaqueCaptureDescriptorDataEXT;
    if (nameHash == XXH3_vkGetImageOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetImageOpaqueCaptureDescriptorDataEXT")) return (void *)table->GetImageOpaqueCaptureDescriptorDataEXT;
    if (nameHash == XXH3_vkGetImageViewOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetImageViewOpaqueCaptureDescriptorDataEXT")) return (void *)table->GetImageViewOpaqueCaptureDescriptorDataEXT;
    if (nameHash == XXH3_vkGetSamplerOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetSamplerOpaqueCaptureDescriptorDataEXT")) return (void *)table->GetSamplerOpaqueCaptureDescriptorDataEXT;
    if (nameHash == XXH3_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT")) return (void *)table->GetAccelerationStructureOpaqueCaptureDescriptorDataEXT;

    // ---- VK_NV_fragment_shading_rate_enums extension commands
    if (nameHash == XXH3_vkCmdSetFragmentShadingRateEnumNV && !strcmp(name, "vkCmdSetFragmentShadingRateEnumNV")) return (void *)table->CmdSetFragmentShadingRateEnumNV;

    // ---- VK_EXT_device_fault extension commands
    if (nameHash == XXH3_vkGetDeviceFaultInfoEXT && !strcmp(name, "vkGetDeviceFaultInfoEXT")) return (void *)table->GetDeviceFaultInfoEXT;

    // ---- VK_EXT_vertex_input_dynamic_state extension commands
    if (nameHash == XXH3_vkCmdSetVertexInputEXT && !strcmp(name, "vkCmdSetVertexInputEXT")) return (void *)table->CmdSetVertexInputEXT;

    // ---- VK_FUCHSIA_external_memory extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetMemoryZirconHandleFUCHSIA && !strcmp(name, "vkGetMemoryZirconHandleFUCHSIA")) return (void *)table->GetMemoryZirconHandleFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetMemoryZirconHandlePropertiesFUCHSIA && !strcmp(name, "vkGetMemoryZirconHandlePropertiesFUCHSIA")) return (void *)table->GetMemoryZirconHandlePropertiesFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_FUCHSIA_external_semaphore extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkImportSemaphoreZirconHandleFUCHSIA && !strcmp(name, "vkImportSemaphoreZirconHandleFUCHSIA")) return (void *)table->ImportSemaphoreZirconHandleFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetSemaphoreZirconHandleFUCHSIA && !strcmp(name, "vkGetSemaphoreZirconHandleFUCHSIA")) return (void *)table->GetSemaphoreZirconHandleFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_FUCHSIA_buffer_collection extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkCreateBufferCollectionFUCHSIA && !strcmp(name, "vkCreateBufferCollectionFUCHSIA")) return (void *)table->CreateBufferCollectionFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkSetBufferCollectionImageConstraintsFUCHSIA && !strcmp(name, "vkSetBufferCollectionImageConstraintsFUCHSIA")) return (void *)table->SetBufferCollectionImageConstraintsFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkSetBufferCollectionBufferConstraintsFUCHSIA && !strcmp(name, "vkSetBufferCollectionBufferConstraintsFUCHSIA")) return (void *)table->SetBufferCollectionBufferConstraintsFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkDestroyBufferCollectionFUCHSIA && !strcmp(name, "vkDestroyBufferCollectionFUCHSIA")) return (void *)table->DestroyBufferCollectionFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetBufferCollectionPropertiesFUCHSIA && !strcmp(name, "vkGetBufferCollectionPropertiesFUCHSIA")) return (void *)table->GetBufferCollectionPropertiesFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_HUAWEI_subpass_shading extension commands
    if (nameHash == XXH3_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI && !strcmp(name, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI")) return (void *)table->GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI;
    if (nameHash == XXH3_vkCmdSubpassShadingHUAWEI && !strcmp(name, "vkCmdSubpassShadingHUAWEI")) return (void *)table->CmdSubpassShadingHUAWEI;

    // ---- VK_HUAWEI_invocation_mask extension commands
    if (nameHash == XXH3_vkCmdBindInvocationMaskHUAWEI && !strcmp(name, "vkCmdBindInvocationMaskHUAWEI")) return (void *)table->CmdBindInvocationMaskHUAWEI;

    // ---- VK_NV_external_memory_rdma extension commands
    if (nameHash == XXH3_vkGetMemoryRemoteAddressNV && !strcmp(name, "vkGetMemoryRemoteAddressNV")) return (void *)table->GetMemoryRemoteAddressNV;

    // ---- VK_EXT_pipeline_properties extension commands
    if (nameHash == XXH3_vkGetPipelinePropertiesEXT && !strcmp(name, "vkGetPipelinePropertiesEXT")) return (void *)table->GetPipelinePropertiesEXT;

    // ---- VK_EXT_extended_dynamic_state2 extension commands
    if (nameHash == XXH3_vkCmdSetPatchControlPointsEXT && !strcmp(name, "vkCmdSetPatchControlPointsEXT")) return (void *)table->CmdSetPatchControlPointsEXT;
    if (nameHash == XXH3_vkCmdSetRasterizerDiscardEnableEXT && !strcmp(name, "vkCmdSetRasterizerDiscardEnableEXT")) return (void *)table->CmdSetRasterizerDiscardEnableEXT;
    if (nameHash == XXH3_vkCmdSetDepthBiasEnableEXT && !strcmp(name, "vkCmdSetDepthBiasEnableEXT")) return (void *)table->CmdSetDepthBiasEnableEXT;
    if (nameHash == XXH3_vkCmdSetLogicOpEXT && !strcmp(name, "vkCmdSetLogicOpEXT")) return (void *)table->CmdSetLogicOpEXT;
    if (nameHash == XXH3_vkCmdSetPrimitiveRestartEnableEXT && !strcmp(name, "vkCmdSetPrimitiveRestartEnableEXT")) return (void *)table->CmdSetPrimitiveRestartEnableEXT;

    // ---- VK_EXT_color_write_enable extension commands
    if (nameHash == XXH3_vkCmdSetColorWriteEnableEXT && !strcmp(name, "vkCmdSetColorWriteEnableEXT")) return (void *)table->CmdSetColorWriteEnableEXT;

    // ---- VK_EXT_multi_draw extension commands
    if (nameHash == XXH3_vkCmdDrawMultiEXT && !strcmp(name, "vkCmdDrawMultiEXT")) return (void *)table->CmdDrawMultiEXT;
    if (nameHash == XXH3_vkCmdDrawMultiIndexedEXT && !strcmp(name, "vkCmdDrawMultiIndexedEXT")) return (void *)table->CmdDrawMultiIndexedEXT;

    // ---- VK_EXT_opacity_micromap extension commands
    if (nameHash == XXH3_vkCreateMicromapEXT && !strcmp(name, "vkCreateMicromapEXT")) return (void *)table->CreateMicromapEXT;
    if (nameHash == XXH3_vkDestroyMicromapEXT && !strcmp(name, "vkDestroyMicromapEXT")) return (void *)table->DestroyMicromapEXT;
    if (nameHash == XXH3_vkCmdBuildMicromapsEXT && !strcmp(name, "vkCmdBuildMicromapsEXT")) return (void *)table->CmdBuildMicromapsEXT;
    if (nameHash == XXH3_vkBuildMicromapsEXT && !strcmp(name, "vkBuildMicromapsEXT")) return (void *)table->BuildMicromapsEXT;
    if (nameHash == XXH3_vkCopyMicromapEXT && !strcmp(name, "vkCopyMicromapEXT")) return (void *)table->CopyMicromapEXT;
    if (nameHash == XXH3_vkCopyMicromapToMemoryEXT && !strcmp(name, "vkCopyMicromapToMemoryEXT")) return (void *)table->CopyMicromapToMemoryEXT;
    if (nameHash == XXH3_vkCopyMemoryToMicromapEXT && !strcmp(name, "vkCopyMemoryToMicromapEXT")) return (void *)table->CopyMemoryToMicromapEXT;
    if (nameHash == XXH3_vkWriteMicromapsPropertiesEXT && !strcmp(name, "vkWriteMicromapsPropertiesEXT")) return (void *)table->WriteMicromapsPropertiesEXT;
    if (nameHash == XXH3_vkCmdCopyMicromapEXT && !strcmp(name, "vkCmdCopyMicromapEXT")) return (void *)table->CmdCopyMicromapEXT;
    if (nameHash == XXH3_vkCmdCopyMicromapToMemoryEXT && !strcmp(name, "vkCmdCopyMicromapToMemoryEXT")) return (void *)table->CmdCopyMicromapToMemoryEXT;
    if (nameHash == XXH3_vkCmdCopyMemoryToMicromapEXT && !strcmp(name, "vkCmdCopyMemoryToMicromapEXT")) return (void *)table->CmdCopyMemoryToMicromapEXT;
    if (nameHash == XXH3_vkCmdWriteMicromapsPropertiesEXT && !strcmp(name, "vkCmdWriteMicromapsPropertiesEXT")) return (void *)table->CmdWriteMicromapsPropertiesEXT;
    if (nameHash == XXH3_vkGetDeviceMicromapCompatibilityEXT && !strcmp(name, "vkGetDeviceMicromapCompatibilityEXT")) return (void *)table->GetDeviceMicromapCompatibilityEXT;
    if (nameHash == XXH3_vkGetMicromapBuildSizesEXT && !strcmp(name, "vkGetMicromapBuildSizesEXT")) return (void *)table->GetMicromapBuildSizesEXT;

    // ---- VK_HUAWEI_cluster_culling_shader extension commands
    if (nameHash == XXH3_vkCmdDrawClusterHUAWEI && !strcmp(name, "vkCmdDrawClusterHUAWEI")) return (void *)table->CmdDrawClusterHUAWEI;
    if (nameHash == XXH3_vkCmdDrawClusterIndirectHUAWEI && !strcmp(name, "vkCmdDrawClusterIndirectHUAWEI")) return (void *)table->CmdDrawClusterIndirectHUAWEI;

    // ---- VK_EXT_pageable_device_local_memory extension commands
    if (nameHash == XXH3_vkSetDeviceMemoryPriorityEXT && !strcmp(name, "vkSetDeviceMemoryPriorityEXT")) return (void *)table->SetDeviceMemoryPriorityEXT;

    // ---- VK_ARM_scheduling_controls extension commands
    if (nameHash == XXH3_vkCmdSetDispatchParametersARM && !strcmp(name, "vkCmdSetDispatchParametersARM")) return (void *)table->CmdSetDispatchParametersARM;

    // ---- VK_VALVE_descriptor_set_host_mapping extension commands
    if (nameHash == XXH3_vkGetDescriptorSetLayoutHostMappingInfoVALVE && !strcmp(name, "vkGetDescriptorSetLayoutHostMappingInfoVALVE")) return (void *)table->GetDescriptorSetLayoutHostMappingInfoVALVE;
    if (nameHash == XXH3_vkGetDescriptorSetHostMappingVALVE && !strcmp(name, "vkGetDescriptorSetHostMappingVALVE")) return (void *)table->GetDescriptorSetHostMappingVALVE;

    // ---- VK_NV_copy_memory_indirect extension commands
    if (nameHash == XXH3_vkCmdCopyMemoryIndirectNV && !strcmp(name, "vkCmdCopyMemoryIndirectNV")) return (void *)table->CmdCopyMemoryIndirectNV;
    if (nameHash == XXH3_vkCmdCopyMemoryToImageIndirectNV && !strcmp(name, "vkCmdCopyMemoryToImageIndirectNV")) return (void *)table->CmdCopyMemoryToImageIndirectNV;

    // ---- VK_NV_memory_decompression extension commands
    if (nameHash == XXH3_vkCmdDecompressMemoryNV && !strcmp(name, "vkCmdDecompressMemoryNV")) return (void *)table->CmdDecompressMemoryNV;
    if (nameHash == XXH3_vkCmdDecompressMemoryIndirectCountNV && !strcmp(name, "vkCmdDecompressMemoryIndirectCountNV")) return (void *)table->CmdDecompressMemoryIndirectCountNV;

    // ---- VK_NV_device_generated_commands_compute extension commands
    if (nameHash == XXH3_vkGetPipelineIndirectMemoryRequirementsNV && !strcmp(name, "vkGetPipelineIndirectMemoryRequirementsNV")) return (void *)table->GetPipelineIndirectMemoryRequirementsNV;
    if (nameHash == XXH3_vkCmdUpdatePipelineIndirectBufferNV && !strcmp(name, "vkCmdUpdatePipelineIndirectBufferNV")) return (void *)table->CmdUpdatePipelineIndirectBufferNV;
    if (nameHash == XXH3_vkGetPipelineIndirectDeviceAddressNV && !strcmp(name, "vkGetPipelineIndirectDeviceAddressNV")) return (void *)table->GetPipelineIndirectDeviceAddressNV;

    // ---- VK_OHOS_external_memory extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    if (nameHash == XXH3_vkGetNativeBufferPropertiesOHOS && !strcmp(name, "vkGetNativeBufferPropertiesOHOS")) return (void *)table->GetNativeBufferPropertiesOHOS;
#endif // VK_USE_PLATFORM_OHOS
#if defined(VK_USE_PLATFORM_OHOS)
    if (nameHash == XXH3_vkGetMemoryNativeBufferOHOS && !strcmp(name, "vkGetMemoryNativeBufferOHOS")) return (void *)table->GetMemoryNativeBufferOHOS;
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_EXT_extended_dynamic_state3 extension commands
    if (nameHash == XXH3_vkCmdSetDepthClampEnableEXT && !strcmp(name, "vkCmdSetDepthClampEnableEXT")) return (void *)table->CmdSetDepthClampEnableEXT;
    if (nameHash == XXH3_vkCmdSetPolygonModeEXT && !strcmp(name, "vkCmdSetPolygonModeEXT")) return (void *)table->CmdSetPolygonModeEXT;
    if (nameHash == XXH3_vkCmdSetRasterizationSamplesEXT && !strcmp(name, "vkCmdSetRasterizationSamplesEXT")) return (void *)table->CmdSetRasterizationSamplesEXT;
    if (nameHash == XXH3_vkCmdSetSampleMaskEXT && !strcmp(name, "vkCmdSetSampleMaskEXT")) return (void *)table->CmdSetSampleMaskEXT;
    if (nameHash == XXH3_vkCmdSetAlphaToCoverageEnableEXT && !strcmp(name, "vkCmdSetAlphaToCoverageEnableEXT")) return (void *)table->CmdSetAlphaToCoverageEnableEXT;
    if (nameHash == XXH3_vkCmdSetAlphaToOneEnableEXT && !strcmp(name, "vkCmdSetAlphaToOneEnableEXT")) return (void *)table->CmdSetAlphaToOneEnableEXT;
    if (nameHash == XXH3_vkCmdSetLogicOpEnableEXT && !strcmp(name, "vkCmdSetLogicOpEnableEXT")) return (void *)table->CmdSetLogicOpEnableEXT;
    if (nameHash == XXH3_vkCmdSetColorBlendEnableEXT && !strcmp(name, "vkCmdSetColorBlendEnableEXT")) return (void *)table->CmdSetColorBlendEnableEXT;
    if (nameHash == XXH3_vkCmdSetColorBlendEquationEXT && !strcmp(name, "vkCmdSetColorBlendEquationEXT")) return (void *)table->CmdSetColorBlendEquationEXT;
    if (nameHash == XXH3_vkCmdSetColorWriteMaskEXT && !strcmp(name, "vkCmdSetColorWriteMaskEXT")) return (void *)table->CmdSetColorWriteMaskEXT;
    if (nameHash == XXH3_vkCmdSetTessellationDomainOriginEXT && !strcmp(name, "vkCmdSetTessellationDomainOriginEXT")) return (void *)table->CmdSetTessellationDomainOriginEXT;
    if (nameHash == XXH3_vkCmdSetRasterizationStreamEXT && !strcmp(name, "vkCmdSetRasterizationStreamEXT")) return (void *)table->CmdSetRasterizationStreamEXT;
    if (nameHash == XXH3_vkCmdSetConservativeRasterizationModeEXT && !strcmp(name, "vkCmdSetConservativeRasterizationModeEXT")) return (void *)table->CmdSetConservativeRasterizationModeEXT;
    if (nameHash == XXH3_vkCmdSetExtraPrimitiveOverestimationSizeEXT && !strcmp(name, "vkCmdSetExtraPrimitiveOverestimationSizeEXT")) return (void *)table->CmdSetExtraPrimitiveOverestimationSizeEXT;
    if (nameHash == XXH3_vkCmdSetDepthClipEnableEXT && !strcmp(name, "vkCmdSetDepthClipEnableEXT")) return (void *)table->CmdSetDepthClipEnableEXT;
    if (nameHash == XXH3_vkCmdSetSampleLocationsEnableEXT && !strcmp(name, "vkCmdSetSampleLocationsEnableEXT")) return (void *)table->CmdSetSampleLocationsEnableEXT;
    if (nameHash == XXH3_vkCmdSetColorBlendAdvancedEXT && !strcmp(name, "vkCmdSetColorBlendAdvancedEXT")) return (void *)table->CmdSetColorBlendAdvancedEXT;
    if (nameHash == XXH3_vkCmdSetProvokingVertexModeEXT && !strcmp(name, "vkCmdSetProvokingVertexModeEXT")) return (void *)table->CmdSetProvokingVertexModeEXT;
    if (nameHash == XXH3_vkCmdSetLineRasterizationModeEXT && !strcmp(name, "vkCmdSetLineRasterizationModeEXT")) return (void *)table->CmdSetLineRasterizationModeEXT;
    if (nameHash == XXH3_vkCmdSetLineStippleEnableEXT && !strcmp(name, "vkCmdSetLineStippleEnableEXT")) return (void *)table->CmdSetLineStippleEnableEXT;
    if (nameHash == XXH3_vkCmdSetDepthClipNegativeOneToOneEXT && !strcmp(name, "vkCmdSetDepthClipNegativeOneToOneEXT")) return (void *)table->CmdSetDepthClipNegativeOneToOneEXT;
    if (nameHash == XXH3_vkCmdSetViewportWScalingEnableNV && !strcmp(name, "vkCmdSetViewportWScalingEnableNV")) return (void *)table->CmdSetViewportWScalingEnableNV;
    if (nameHash == XXH3_vkCmdSetViewportSwizzleNV && !strcmp(name, "vkCmdSetViewportSwizzleNV")) return (void *)table->CmdSetViewportSwizzleNV;
    if (nameHash == XXH3_vkCmdSetCoverageToColorEnableNV && !strcmp(name, "vkCmdSetCoverageToColorEnableNV")) return (void *)table->CmdSetCoverageToColorEnableNV;
    if (nameHash == XXH3_vkCmdSetCoverageToColorLocationNV && !strcmp(name, "vkCmdSetCoverageToColorLocationNV")) return (void *)table->CmdSetCoverageToColorLocationNV;
    if (nameHash == XXH3_vkCmdSetCoverageModulationModeNV && !strcmp(name, "vkCmdSetCoverageModulationModeNV")) return (void *)table->CmdSetCoverageModulationModeNV;
    if (nameHash == XXH3_vkCmdSetCoverageModulationTableEnableNV && !strcmp(name, "vkCmdSetCoverageModulationTableEnableNV")) return (void *)table->CmdSetCoverageModulationTableEnableNV;
    if (nameHash == XXH3_vkCmdSetCoverageModulationTableNV && !strcmp(name, "vkCmdSetCoverageModulationTableNV")) return (void *)table->CmdSetCoverageModulationTableNV;
    if (nameHash == XXH3_vkCmdSetShadingRateImageEnableNV && !strcmp(name, "vkCmdSetShadingRateImageEnableNV")) return (void *)table->CmdSetShadingRateImageEnableNV;
    if (nameHash == XXH3_vkCmdSetRepresentativeFragmentTestEnableNV && !strcmp(name, "vkCmdSetRepresentativeFragmentTestEnableNV")) return (void *)table->CmdSetRepresentativeFragmentTestEnableNV;
    if (nameHash == XXH3_vkCmdSetCoverageReductionModeNV && !strcmp(name, "vkCmdSetCoverageReductionModeNV")) return (void *)table->CmdSetCoverageReductionModeNV;

    // ---- VK_ARM_tensors extension commands
    if (nameHash == XXH3_vkCreateTensorARM && !strcmp(name, "vkCreateTensorARM")) return (void *)table->CreateTensorARM;
    if (nameHash == XXH3_vkDestroyTensorARM && !strcmp(name, "vkDestroyTensorARM")) return (void *)table->DestroyTensorARM;
    if (nameHash == XXH3_vkCreateTensorViewARM && !strcmp(name, "vkCreateTensorViewARM")) return (void *)table->CreateTensorViewARM;
    if (nameHash == XXH3_vkDestroyTensorViewARM && !strcmp(name, "vkDestroyTensorViewARM")) return (void *)table->DestroyTensorViewARM;
    if (nameHash == XXH3_vkGetTensorMemoryRequirementsARM && !strcmp(name, "vkGetTensorMemoryRequirementsARM")) return (void *)table->GetTensorMemoryRequirementsARM;
    if (nameHash == XXH3_vkBindTensorMemoryARM && !strcmp(name, "vkBindTensorMemoryARM")) return (void *)table->BindTensorMemoryARM;
    if (nameHash == XXH3_vkGetDeviceTensorMemoryRequirementsARM && !strcmp(name, "vkGetDeviceTensorMemoryRequirementsARM")) return (void *)table->GetDeviceTensorMemoryRequirementsARM;
    if (nameHash == XXH3_vkCmdCopyTensorARM && !strcmp(name, "vkCmdCopyTensorARM")) return (void *)table->CmdCopyTensorARM;
    if (nameHash == XXH3_vkGetTensorOpaqueCaptureDescriptorDataARM && !strcmp(name, "vkGetTensorOpaqueCaptureDescriptorDataARM")) return (void *)table->GetTensorOpaqueCaptureDescriptorDataARM;
    if (nameHash == XXH3_vkGetTensorViewOpaqueCaptureDescriptorDataARM && !strcmp(name, "vkGetTensorViewOpaqueCaptureDescriptorDataARM")) return (void *)table->GetTensorViewOpaqueCaptureDescriptorDataARM;

    // ---- VK_EXT_shader_module_identifier extension commands
    if (nameHash == XXH3_vkGetShaderModuleIdentifierEXT && !strcmp(name, "vkGetShaderModuleIdentifierEXT")) return (void *)table->GetShaderModuleIdentifierEXT;
    if (nameHash == XXH3_vkGetShaderModuleCreateInfoIdentifierEXT && !strcmp(name, "vkGetShaderModuleCreateInfoIdentifierEXT")) return (void *)table->GetShaderModuleCreateInfoIdentifierEXT;

    // ---- VK_NV_optical_flow extension commands
    if (nameHash == XXH3_vkCreateOpticalFlowSessionNV && !strcmp(name, "vkCreateOpticalFlowSessionNV")) return (void *)table->CreateOpticalFlowSessionNV;
    if (nameHash == XXH3_vkDestroyOpticalFlowSessionNV && !strcmp(name, "vkDestroyOpticalFlowSessionNV")) return (void *)table->DestroyOpticalFlowSessionNV;
    if (nameHash == XXH3_vkBindOpticalFlowSessionImageNV && !strcmp(name, "vkBindOpticalFlowSessionImageNV")) return (void *)table->BindOpticalFlowSessionImageNV;
    if (nameHash == XXH3_vkCmdOpticalFlowExecuteNV && !strcmp(name, "vkCmdOpticalFlowExecuteNV")) return (void *)table->CmdOpticalFlowExecuteNV;

    // ---- VK_AMD_anti_lag extension commands
    if (nameHash == XXH3_vkAntiLagUpdateAMD && !strcmp(name, "vkAntiLagUpdateAMD")) return (void *)table->AntiLagUpdateAMD;

    // ---- VK_EXT_shader_object extension commands
    if (nameHash == XXH3_vkCreateShadersEXT && !strcmp(name, "vkCreateShadersEXT")) return (void *)table->CreateShadersEXT;
    if (nameHash == XXH3_vkDestroyShaderEXT && !strcmp(name, "vkDestroyShaderEXT")) return (void *)table->DestroyShaderEXT;
    if (nameHash == XXH3_vkGetShaderBinaryDataEXT && !strcmp(name, "vkGetShaderBinaryDataEXT")) return (void *)table->GetShaderBinaryDataEXT;
    if (nameHash == XXH3_vkCmdBindShadersEXT && !strcmp(name, "vkCmdBindShadersEXT")) return (void *)table->CmdBindShadersEXT;
    if (nameHash == XXH3_vkCmdSetDepthClampRangeEXT && !strcmp(name, "vkCmdSetDepthClampRangeEXT")) return (void *)table->CmdSetDepthClampRangeEXT;

    // ---- VK_QCOM_tile_properties extension commands
    if (nameHash == XXH3_vkGetFramebufferTilePropertiesQCOM && !strcmp(name, "vkGetFramebufferTilePropertiesQCOM")) return (void *)table->GetFramebufferTilePropertiesQCOM;
    if (nameHash == XXH3_vkGetDynamicRenderingTilePropertiesQCOM && !strcmp(name, "vkGetDynamicRenderingTilePropertiesQCOM")) return (void *)table->GetDynamicRenderingTilePropertiesQCOM;

    // ---- VK_NV_cooperative_vector extension commands
    if (nameHash == XXH3_vkConvertCooperativeVectorMatrixNV && !strcmp(name, "vkConvertCooperativeVectorMatrixNV")) return (void *)table->ConvertCooperativeVectorMatrixNV;
    if (nameHash == XXH3_vkCmdConvertCooperativeVectorMatrixNV && !strcmp(name, "vkCmdConvertCooperativeVectorMatrixNV")) return (void *)table->CmdConvertCooperativeVectorMatrixNV;

    // ---- VK_NV_low_latency2 extension commands
    if (nameHash == XXH3_vkSetLatencySleepModeNV && !strcmp(name, "vkSetLatencySleepModeNV")) return (void *)table->SetLatencySleepModeNV;
    if (nameHash == XXH3_vkLatencySleepNV && !strcmp(name, "vkLatencySleepNV")) return (void *)table->LatencySleepNV;
    if (nameHash == XXH3_vkSetLatencyMarkerNV && !strcmp(name, "vkSetLatencyMarkerNV")) return (void *)table->SetLatencyMarkerNV;
    if (nameHash == XXH3_vkGetLatencyTimingsNV && !strcmp(name, "vkGetLatencyTimingsNV")) return (void *)table->GetLatencyTimingsNV;
    if (nameHash == XXH3_vkQueueNotifyOutOfBandNV && !strcmp(name, "vkQueueNotifyOutOfBandNV")) return (void *)table->QueueNotifyOutOfBandNV;

    // ---- VK_ARM_data_graph extension commands
    if (nameHash == XXH3_vkCreateDataGraphPipelinesARM && !strcmp(name, "vkCreateDataGraphPipelinesARM")) return (void *)table->CreateDataGraphPipelinesARM;
    if (nameHash == XXH3_vkCreateDataGraphPipelineSessionARM && !strcmp(name, "vkCreateDataGraphPipelineSessionARM")) return (void *)table->CreateDataGraphPipelineSessionARM;
    if (nameHash == XXH3_vkGetDataGraphPipelineSessionBindPointRequirementsARM && !strcmp(name, "vkGetDataGraphPipelineSessionBindPointRequirementsARM")) return (void *)table->GetDataGraphPipelineSessionBindPointRequirementsARM;
    if (nameHash == XXH3_vkGetDataGraphPipelineSessionMemoryRequirementsARM && !strcmp(name, "vkGetDataGraphPipelineSessionMemoryRequirementsARM")) return (void *)table->GetDataGraphPipelineSessionMemoryRequirementsARM;
    if (nameHash == XXH3_vkBindDataGraphPipelineSessionMemoryARM && !strcmp(name, "vkBindDataGraphPipelineSessionMemoryARM")) return (void *)table->BindDataGraphPipelineSessionMemoryARM;
    if (nameHash == XXH3_vkDestroyDataGraphPipelineSessionARM && !strcmp(name, "vkDestroyDataGraphPipelineSessionARM")) return (void *)table->DestroyDataGraphPipelineSessionARM;
    if (nameHash == XXH3_vkCmdDispatchDataGraphARM && !strcmp(name, "vkCmdDispatchDataGraphARM")) return (void *)table->CmdDispatchDataGraphARM;
    if (nameHash == XXH3_vkGetDataGraphPipelineAvailablePropertiesARM && !strcmp(name, "vkGetDataGraphPipelineAvailablePropertiesARM")) return (void *)table->GetDataGraphPipelineAvailablePropertiesARM;
    if (nameHash == XXH3_vkGetDataGraphPipelinePropertiesARM && !strcmp(name, "vkGetDataGraphPipelinePropertiesARM")) return (void *)table->GetDataGraphPipelinePropertiesARM;

    // ---- VK_EXT_attachment_feedback_loop_dynamic_state extension commands
    if (nameHash == XXH3_vkCmdSetAttachmentFeedbackLoopEnableEXT && !strcmp(name, "vkCmdSetAttachmentFeedbackLoopEnableEXT")) return (void *)table->CmdSetAttachmentFeedbackLoopEnableEXT;

    // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (nameHash == XXH3_vkGetScreenBufferPropertiesQNX && !strcmp(name, "vkGetScreenBufferPropertiesQNX")) return (void *)table->GetScreenBufferPropertiesQNX;
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_QCOM_tile_memory_heap extension commands
    if (nameHash == XXH3_vkCmdBindTileMemoryQCOM && !strcmp(name, "vkCmdBindTileMemoryQCOM")) return (void *)table->CmdBindTileMemoryQCOM;

    // ---- VK_EXT_memory_decompression extension commands
    if (nameHash == XXH3_vkCmdDecompressMemoryEXT && !strcmp(name, "vkCmdDecompressMemoryEXT")) return (void *)table->CmdDecompressMemoryEXT;
    if (nameHash == XXH3_vkCmdDecompressMemoryIndirectCountEXT && !strcmp(name, "vkCmdDecompressMemoryIndirectCountEXT")) return (void *)table->CmdDecompressMemoryIndirectCountEXT;

    // ---- VK_NV_external_compute_queue extension commands
    if (nameHash == XXH3_vkCreateExternalComputeQueueNV && !strcmp(name, "vkCreateExternalComputeQueueNV")) return (void *)table->CreateExternalComputeQueueNV;
    if (nameHash == XXH3_vkDestroyExternalComputeQueueNV && !strcmp(name, "vkDestroyExternalComputeQueueNV")) return (void *)table->DestroyExternalComputeQueueNV;
    if (nameHash == XXH3_vkGetExternalComputeQueueDataNV && !strcmp(name, "vkGetExternalComputeQueueDataNV")) return (void *)table->GetExternalComputeQueueDataNV;

    // ---- VK_NV_cluster_acceleration_structure extension commands
    if (nameHash == XXH3_vkGetClusterAccelerationStructureBuildSizesNV && !strcmp(name, "vkGetClusterAccelerationStructureBuildSizesNV")) return (void *)table->GetClusterAccelerationStructureBuildSizesNV;
    if (nameHash == XXH3_vkCmdBuildClusterAccelerationStructureIndirectNV && !strcmp(name, "vkCmdBuildClusterAccelerationStructureIndirectNV")) return (void *)table->CmdBuildClusterAccelerationStructureIndirectNV;

    // ---- VK_NV_partitioned_acceleration_structure extension commands
    if (nameHash == XXH3_vkGetPartitionedAccelerationStructuresBuildSizesNV && !strcmp(name, "vkGetPartitionedAccelerationStructuresBuildSizesNV")) return (void *)table->GetPartitionedAccelerationStructuresBuildSizesNV;
    if (nameHash == XXH3_vkCmdBuildPartitionedAccelerationStructuresNV && !strcmp(name, "vkCmdBuildPartitionedAccelerationStructuresNV")) return (void *)table->CmdBuildPartitionedAccelerationStructuresNV;

    // ---- VK_EXT_device_generated_commands extension commands
    if (nameHash == XXH3_vkGetGeneratedCommandsMemoryRequirementsEXT && !strcmp(name, "vkGetGeneratedCommandsMemoryRequirementsEXT")) return (void *)table->GetGeneratedCommandsMemoryRequirementsEXT;
    if (nameHash == XXH3_vkCmdPreprocessGeneratedCommandsEXT && !strcmp(name, "vkCmdPreprocessGeneratedCommandsEXT")) return (void *)table->CmdPreprocessGeneratedCommandsEXT;
    if (nameHash == XXH3_vkCmdExecuteGeneratedCommandsEXT && !strcmp(name, "vkCmdExecuteGeneratedCommandsEXT")) return (void *)table->CmdExecuteGeneratedCommandsEXT;
    if (nameHash == XXH3_vkCreateIndirectCommandsLayoutEXT && !strcmp(name, "vkCreateIndirectCommandsLayoutEXT")) return (void *)table->CreateIndirectCommandsLayoutEXT;
    if (nameHash == XXH3_vkDestroyIndirectCommandsLayoutEXT && !strcmp(name, "vkDestroyIndirectCommandsLayoutEXT")) return (void *)table->DestroyIndirectCommandsLayoutEXT;
    if (nameHash == XXH3_vkCreateIndirectExecutionSetEXT && !strcmp(name, "vkCreateIndirectExecutionSetEXT")) return (void *)table->CreateIndirectExecutionSetEXT;
    if (nameHash == XXH3_vkDestroyIndirectExecutionSetEXT && !strcmp(name, "vkDestroyIndirectExecutionSetEXT")) return (void *)table->DestroyIndirectExecutionSetEXT;
    if (nameHash == XXH3_vkUpdateIndirectExecutionSetPipelineEXT && !strcmp(name, "vkUpdateIndirectExecutionSetPipelineEXT")) return (void *)table->UpdateIndirectExecutionSetPipelineEXT;
    if (nameHash == XXH3_vkUpdateIndirectExecutionSetShaderEXT && !strcmp(name, "vkUpdateIndirectExecutionSetShaderEXT")) return (void *)table->UpdateIndirectExecutionSetShaderEXT;

    // ---- VK_EXT_external_memory_metal extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkGetMemoryMetalHandleEXT && !strcmp(name, "vkGetMemoryMetalHandleEXT")) return (void *)table->GetMemoryMetalHandleEXT;
#endif // VK_USE_PLATFORM_METAL_EXT
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkGetMemoryMetalHandlePropertiesEXT && !strcmp(name, "vkGetMemoryMetalHandlePropertiesEXT")) return (void *)table->GetMemoryMetalHandlePropertiesEXT;
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_ARM_shader_instrumentation extension commands
    if (nameHash == XXH3_vkCreateShaderInstrumentationARM && !strcmp(name, "vkCreateShaderInstrumentationARM")) return (void *)table->CreateShaderInstrumentationARM;
    if (nameHash == XXH3_vkDestroyShaderInstrumentationARM && !strcmp(name, "vkDestroyShaderInstrumentationARM")) return (void *)table->DestroyShaderInstrumentationARM;
    if (nameHash == XXH3_vkCmdBeginShaderInstrumentationARM && !strcmp(name, "vkCmdBeginShaderInstrumentationARM")) return (void *)table->CmdBeginShaderInstrumentationARM;
    if (nameHash == XXH3_vkCmdEndShaderInstrumentationARM && !strcmp(name, "vkCmdEndShaderInstrumentationARM")) return (void *)table->CmdEndShaderInstrumentationARM;
    if (nameHash == XXH3_vkGetShaderInstrumentationValuesARM && !strcmp(name, "vkGetShaderInstrumentationValuesARM")) return (void *)table->GetShaderInstrumentationValuesARM;
    if (nameHash == XXH3_vkClearShaderInstrumentationMetricsARM && !strcmp(name, "vkClearShaderInstrumentationMetricsARM")) return (void *)table->ClearShaderInstrumentationMetricsARM;

    // ---- VK_EXT_fragment_density_map_offset extension commands
    if (nameHash == XXH3_vkCmdEndRendering2EXT && !strcmp(name, "vkCmdEndRendering2EXT")) return (void *)table->CmdEndRendering2EXT;

    // ---- VK_EXT_custom_resolve extension commands
    if (nameHash == XXH3_vkCmdBeginCustomResolveEXT && !strcmp(name, "vkCmdBeginCustomResolveEXT")) return (void *)table->CmdBeginCustomResolveEXT;

    // ---- VK_NV_compute_occupancy_priority extension commands
    if (nameHash == XXH3_vkCmdSetComputeOccupancyPriorityNV && !strcmp(name, "vkCmdSetComputeOccupancyPriorityNV")) return (void *)table->CmdSetComputeOccupancyPriorityNV;

    // ---- VK_EXT_primitive_restart_index extension commands
    if (nameHash == XXH3_vkCmdSetPrimitiveRestartIndexEXT && !strcmp(name, "vkCmdSetPrimitiveRestartIndexEXT")) return (void *)table->CmdSetPrimitiveRestartIndexEXT;

    // ---- VK_KHR_acceleration_structure extension commands
    if (nameHash == XXH3_vkCreateAccelerationStructureKHR && !strcmp(name, "vkCreateAccelerationStructureKHR")) return (void *)table->CreateAccelerationStructureKHR;
    if (nameHash == XXH3_vkDestroyAccelerationStructureKHR && !strcmp(name, "vkDestroyAccelerationStructureKHR")) return (void *)table->DestroyAccelerationStructureKHR;
    if (nameHash == XXH3_vkCmdBuildAccelerationStructuresKHR && !strcmp(name, "vkCmdBuildAccelerationStructuresKHR")) return (void *)table->CmdBuildAccelerationStructuresKHR;
    if (nameHash == XXH3_vkCmdBuildAccelerationStructuresIndirectKHR && !strcmp(name, "vkCmdBuildAccelerationStructuresIndirectKHR")) return (void *)table->CmdBuildAccelerationStructuresIndirectKHR;
    if (nameHash == XXH3_vkBuildAccelerationStructuresKHR && !strcmp(name, "vkBuildAccelerationStructuresKHR")) return (void *)table->BuildAccelerationStructuresKHR;
    if (nameHash == XXH3_vkCopyAccelerationStructureKHR && !strcmp(name, "vkCopyAccelerationStructureKHR")) return (void *)table->CopyAccelerationStructureKHR;
    if (nameHash == XXH3_vkCopyAccelerationStructureToMemoryKHR && !strcmp(name, "vkCopyAccelerationStructureToMemoryKHR")) return (void *)table->CopyAccelerationStructureToMemoryKHR;
    if (nameHash == XXH3_vkCopyMemoryToAccelerationStructureKHR && !strcmp(name, "vkCopyMemoryToAccelerationStructureKHR")) return (void *)table->CopyMemoryToAccelerationStructureKHR;
    if (nameHash == XXH3_vkWriteAccelerationStructuresPropertiesKHR && !strcmp(name, "vkWriteAccelerationStructuresPropertiesKHR")) return (void *)table->WriteAccelerationStructuresPropertiesKHR;
    if (nameHash == XXH3_vkCmdCopyAccelerationStructureKHR && !strcmp(name, "vkCmdCopyAccelerationStructureKHR")) return (void *)table->CmdCopyAccelerationStructureKHR;
    if (nameHash == XXH3_vkCmdCopyAccelerationStructureToMemoryKHR && !strcmp(name, "vkCmdCopyAccelerationStructureToMemoryKHR")) return (void *)table->CmdCopyAccelerationStructureToMemoryKHR;
    if (nameHash == XXH3_vkCmdCopyMemoryToAccelerationStructureKHR && !strcmp(name, "vkCmdCopyMemoryToAccelerationStructureKHR")) return (void *)table->CmdCopyMemoryToAccelerationStructureKHR;
    if (nameHash == XXH3_vkGetAccelerationStructureDeviceAddressKHR && !strcmp(name, "vkGetAccelerationStructureDeviceAddressKHR")) return (void *)table->GetAccelerationStructureDeviceAddressKHR;
    if (nameHash == XXH3_vkCmdWriteAccelerationStructuresPropertiesKHR && !strcmp(name, "vkCmdWriteAccelerationStructuresPropertiesKHR")) return (void *)table->CmdWriteAccelerationStructuresPropertiesKHR;
    if (nameHash == XXH3_vkGetDeviceAccelerationStructureCompatibilityKHR && !strcmp(name, "vkGetDeviceAccelerationStructureCompatibilityKHR")) return (void *)table->GetDeviceAccelerationStructureCompatibilityKHR;
    if (nameHash == XXH3_vkGetAccelerationStructureBuildSizesKHR && !strcmp(name, "vkGetAccelerationStructureBuildSizesKHR")) return (void *)table->GetAccelerationStructureBuildSizesKHR;

    // ---- VK_KHR_ray_tracing_pipeline extension commands
    if (nameHash == XXH3_vkCmdTraceRaysKHR && !strcmp(name, "vkCmdTraceRaysKHR")) return (void *)table->CmdTraceRaysKHR;
    if (nameHash == XXH3_vkCreateRayTracingPipelinesKHR && !strcmp(name, "vkCreateRayTracingPipelinesKHR")) return (void *)table->CreateRayTracingPipelinesKHR;
    if (nameHash == XXH3_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR && !strcmp(name, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR")) return (void *)table->GetRayTracingCaptureReplayShaderGroupHandlesKHR;
    if (nameHash == XXH3_vkCmdTraceRaysIndirectKHR && !strcmp(name, "vkCmdTraceRaysIndirectKHR")) return (void *)table->CmdTraceRaysIndirectKHR;
    if (nameHash == XXH3_vkGetRayTracingShaderGroupStackSizeKHR && !strcmp(name, "vkGetRayTracingShaderGroupStackSizeKHR")) return (void *)table->GetRayTracingShaderGroupStackSizeKHR;
    if (nameHash == XXH3_vkCmdSetRayTracingPipelineStackSizeKHR && !strcmp(name, "vkCmdSetRayTracingPipelineStackSizeKHR")) return (void *)table->CmdSetRayTracingPipelineStackSizeKHR;

    // ---- VK_EXT_mesh_shader extension commands
    if (nameHash == XXH3_vkCmdDrawMeshTasksEXT && !strcmp(name, "vkCmdDrawMeshTasksEXT")) return (void *)table->CmdDrawMeshTasksEXT;
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectEXT && !strcmp(name, "vkCmdDrawMeshTasksIndirectEXT")) return (void *)table->CmdDrawMeshTasksIndirectEXT;
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectCountEXT && !strcmp(name, "vkCmdDrawMeshTasksIndirectCountEXT")) return (void *)table->CmdDrawMeshTasksIndirectCountEXT;

    *found_name = false;
    return NULL;
}

// Instance command lookup function
VKAPI_ATTR void* VKAPI_CALL loader_lookup_instance_dispatch_table(const VkLayerInstanceDispatchTable *table, const char *name,
                                                                  uint64_t nameHash, bool *found_name) {
    if (!name || name[0] != 'v' || name[1] != 'k') {
        *found_name = false;
        return NULL;
    }

    *found_name = true;

    // ---- Core Vulkan 1.0 commands
    if (nameHash == XXH3_vkDestroyInstance && !strcmp(name, "vkDestroyInstance")) return (void *)table->DestroyInstance;
    if (nameHash == XXH3_vkEnumeratePhysicalDevices && !strcmp(name, "vkEnumeratePhysicalDevices")) return (void *)table->EnumeratePhysicalDevices;
    if (nameHash == XXH3_vkGetPhysicalDeviceFeatures && !strcmp(name, "vkGetPhysicalDeviceFeatures")) return (void *)table->GetPhysicalDeviceFeatures;
    if (nameHash == XXH3_vkGetPhysicalDeviceFormatProperties && !strcmp(name, "vkGetPhysicalDeviceFormatProperties")) return (void *)table->GetPhysicalDeviceFormatProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceImageFormatProperties && !strcmp(name, "vkGetPhysicalDeviceImageFormatProperties")) return (void *)table->GetPhysicalDeviceImageFormatProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceProperties && !strcmp(name, "vkGetPhysicalDeviceProperties")) return (void *)table->GetPhysicalDeviceProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyProperties && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyProperties")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceMemoryProperties && !strcmp(name, "vkGetPhysicalDeviceMemoryProperties")) return (void *)table->GetPhysicalDeviceMemoryProperties;
    if (nameHash == XXH3_vkGetInstanceProcAddr && !strcmp(name, "vkGetInstanceProcAddr")) return (void *)table->GetInstanceProcAddr;
    if (nameHash == XXH3_vkEnumerateDeviceExtensionProperties && !strcmp(name, "vkEnumerateDeviceExtensionProperties")) return (void *)table->EnumerateDeviceExtensionProperties;
    if (nameHash == XXH3_vkEnumerateDeviceLayerProperties && !strcmp(name, "vkEnumerateDeviceLayerProperties")) return (void *)table->EnumerateDeviceLayerProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceSparseImageFormatProperties && !strcmp(name, "vkGetPhysicalDeviceSparseImageFormatProperties")) return (void *)table->GetPhysicalDeviceSparseImageFormatProperties;

    // ---- Core Vulkan 1.1 commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceGroups && !strcmp(name, "vkEnumeratePhysicalDeviceGroups")) return (void *)table->EnumeratePhysicalDeviceGroups;
    if (nameHash == XXH3_vkGetPhysicalDeviceFeatures2 && !strcmp(name, "vkGetPhysicalDeviceFeatures2")) return (void *)table->GetPhysicalDeviceFeatures2;
    if (nameHash == XXH3_vkGetPhysicalDeviceProperties2 && !strcmp(name, "vkGetPhysicalDeviceProperties2")) return (void *)table->GetPhysicalDeviceProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceFormatProperties2 && !strcmp(name, "vkGetPhysicalDeviceFormatProperties2")) return (void *)table->GetPhysicalDeviceFormatProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceImageFormatProperties2 && !strcmp(name, "vkGetPhysicalDeviceImageFormatProperties2")) return (void *)table->GetPhysicalDeviceImageFormatProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyProperties2 && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyProperties2")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceMemoryProperties2 && !strcmp(name, "vkGetPhysicalDeviceMemoryProperties2")) return (void *)table->GetPhysicalDeviceMemoryProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceSparseImageFormatProperties2 && !strcmp(name, "vkGetPhysicalDeviceSparseImageFormatProperties2")) return (void *)table->GetPhysicalDeviceSparseImageFormatProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalBufferProperties && !strcmp(name, "vkGetPhysicalDeviceExternalBufferProperties")) return (void *)table->GetPhysicalDeviceExternalBufferProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalFenceProperties && !strcmp(name, "vkGetPhysicalDeviceExternalFenceProperties")) return (void *)table->GetPhysicalDeviceExternalFenceProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalSemaphoreProperties && !strcmp(name, "vkGetPhysicalDeviceExternalSemaphoreProperties")) return (void *)table->GetPhysicalDeviceExternalSemaphoreProperties;

    // ---- Core Vulkan 1.3 commands
    if (nameHash == XXH3_vkGetPhysicalDeviceToolProperties && !strcmp(name, "vkGetPhysicalDeviceToolProperties")) return (void *)table->GetPhysicalDeviceToolProperties;

    // ---- VK_KHR_surface extension commands
    if (nameHash == XXH3_vkDestroySurfaceKHR && !strcmp(name, "vkDestroySurfaceKHR")) return (void *)table->DestroySurfaceKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceSupportKHR && !strcmp(name, "vkGetPhysicalDeviceSurfaceSupportKHR")) return (void *)table->GetPhysicalDeviceSurfaceSupportKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceCapabilitiesKHR && !strcmp(name, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR")) return (void *)table->GetPhysicalDeviceSurfaceCapabilitiesKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceFormatsKHR && !strcmp(name, "vkGetPhysicalDeviceSurfaceFormatsKHR")) return (void *)table->GetPhysicalDeviceSurfaceFormatsKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfacePresentModesKHR && !strcmp(name, "vkGetPhysicalDeviceSurfacePresentModesKHR")) return (void *)table->GetPhysicalDeviceSurfacePresentModesKHR;

    // ---- VK_KHR_swapchain extension commands
    if (nameHash == XXH3_vkGetPhysicalDevicePresentRectanglesKHR && !strcmp(name, "vkGetPhysicalDevicePresentRectanglesKHR")) return (void *)table->GetPhysicalDevicePresentRectanglesKHR;

    // ---- VK_KHR_display extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceDisplayPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceDisplayPropertiesKHR")) return (void *)table->GetPhysicalDeviceDisplayPropertiesKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceDisplayPlanePropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR")) return (void *)table->GetPhysicalDeviceDisplayPlanePropertiesKHR;
    if (nameHash == XXH3_vkGetDisplayPlaneSupportedDisplaysKHR && !strcmp(name, "vkGetDisplayPlaneSupportedDisplaysKHR")) return (void *)table->GetDisplayPlaneSupportedDisplaysKHR;
    if (nameHash == XXH3_vkGetDisplayModePropertiesKHR && !strcmp(name, "vkGetDisplayModePropertiesKHR")) return (void *)table->GetDisplayModePropertiesKHR;
    if (nameHash == XXH3_vkCreateDisplayModeKHR && !strcmp(name, "vkCreateDisplayModeKHR")) return (void *)table->CreateDisplayModeKHR;
    if (nameHash == XXH3_vkGetDisplayPlaneCapabilitiesKHR && !strcmp(name, "vkGetDisplayPlaneCapabilitiesKHR")) return (void *)table->GetDisplayPlaneCapabilitiesKHR;
    if (nameHash == XXH3_vkCreateDisplayPlaneSurfaceKHR && !strcmp(name, "vkCreateDisplayPlaneSurfaceKHR")) return (void *)table->CreateDisplayPlaneSurfaceKHR;

    // ---- VK_KHR_xlib_surface extension commands
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    if (nameHash == XXH3_vkCreateXlibSurfaceKHR && !strcmp(name, "vkCreateXlibSurfaceKHR")) return (void *)table->CreateXlibSurfaceKHR;
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    if (nameHash == XXH3_vkGetPhysicalDeviceXlibPresentationSupportKHR && !strcmp(name, "vkGetPhysicalDeviceXlibPresentationSupportKHR")) return (void *)table->GetPhysicalDeviceXlibPresentationSupportKHR;
#endif // VK_USE_PLATFORM_XLIB_KHR

    // ---- VK_KHR_xcb_surface extension commands
#if defined(VK_USE_PLATFORM_XCB_KHR)
    if (nameHash == XXH3_vkCreateXcbSurfaceKHR && !strcmp(name, "vkCreateXcbSurfaceKHR")) return (void *)table->CreateXcbSurfaceKHR;
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    if (nameHash == XXH3_vkGetPhysicalDeviceXcbPresentationSupportKHR && !strcmp(name, "vkGetPhysicalDeviceXcbPresentationSupportKHR")) return (void *)table->GetPhysicalDeviceXcbPresentationSupportKHR;
#endif // VK_USE_PLATFORM_XCB_KHR

    // ---- VK_KHR_wayland_surface extension commands
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    if (nameHash == XXH3_vkCreateWaylandSurfaceKHR && !strcmp(name, "vkCreateWaylandSurfaceKHR")) return (void *)table->CreateWaylandSurfaceKHR;
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    if (nameHash == XXH3_vkGetPhysicalDeviceWaylandPresentationSupportKHR && !strcmp(name, "vkGetPhysicalDeviceWaylandPresentationSupportKHR")) return (void *)table->GetPhysicalDeviceWaylandPresentationSupportKHR;
#endif // VK_USE_PLATFORM_WAYLAND_KHR

    // ---- VK_KHR_android_surface extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    if (nameHash == XXH3_vkCreateAndroidSurfaceKHR && !strcmp(name, "vkCreateAndroidSurfaceKHR")) return (void *)table->CreateAndroidSurfaceKHR;
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_KHR_win32_surface extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkCreateWin32SurfaceKHR && !strcmp(name, "vkCreateWin32SurfaceKHR")) return (void *)table->CreateWin32SurfaceKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetPhysicalDeviceWin32PresentationSupportKHR && !strcmp(name, "vkGetPhysicalDeviceWin32PresentationSupportKHR")) return (void *)table->GetPhysicalDeviceWin32PresentationSupportKHR;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_video_queue extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceVideoCapabilitiesKHR && !strcmp(name, "vkGetPhysicalDeviceVideoCapabilitiesKHR")) return (void *)table->GetPhysicalDeviceVideoCapabilitiesKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceVideoFormatPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceVideoFormatPropertiesKHR")) return (void *)table->GetPhysicalDeviceVideoFormatPropertiesKHR;

    // ---- VK_KHR_get_physical_device_properties2 extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceFeatures2KHR && !strcmp(name, "vkGetPhysicalDeviceFeatures2KHR")) return (void *)table->GetPhysicalDeviceFeatures2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceProperties2KHR")) return (void *)table->GetPhysicalDeviceProperties2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceFormatProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceFormatProperties2KHR")) return (void *)table->GetPhysicalDeviceFormatProperties2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceImageFormatProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceImageFormatProperties2KHR")) return (void *)table->GetPhysicalDeviceImageFormatProperties2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyProperties2KHR")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceMemoryProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceMemoryProperties2KHR")) return (void *)table->GetPhysicalDeviceMemoryProperties2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceSparseImageFormatProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR")) return (void *)table->GetPhysicalDeviceSparseImageFormatProperties2KHR;

    // ---- VK_KHR_device_group_creation extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceGroupsKHR && !strcmp(name, "vkEnumeratePhysicalDeviceGroupsKHR")) return (void *)table->EnumeratePhysicalDeviceGroupsKHR;

    // ---- VK_KHR_external_memory_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalBufferPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceExternalBufferPropertiesKHR")) return (void *)table->GetPhysicalDeviceExternalBufferPropertiesKHR;

    // ---- VK_KHR_external_semaphore_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR")) return (void *)table->GetPhysicalDeviceExternalSemaphorePropertiesKHR;

    // ---- VK_KHR_external_fence_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalFencePropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceExternalFencePropertiesKHR")) return (void *)table->GetPhysicalDeviceExternalFencePropertiesKHR;

    // ---- VK_KHR_performance_query extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR && !strcmp(name, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR")) return (void *)table->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR")) return (void *)table->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceCapabilities2KHR && !strcmp(name, "vkGetPhysicalDeviceSurfaceCapabilities2KHR")) return (void *)table->GetPhysicalDeviceSurfaceCapabilities2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceFormats2KHR && !strcmp(name, "vkGetPhysicalDeviceSurfaceFormats2KHR")) return (void *)table->GetPhysicalDeviceSurfaceFormats2KHR;

    // ---- VK_KHR_get_display_properties2 extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceDisplayProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceDisplayProperties2KHR")) return (void *)table->GetPhysicalDeviceDisplayProperties2KHR;
    if (nameHash == XXH3_vkGetPhysicalDeviceDisplayPlaneProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR")) return (void *)table->GetPhysicalDeviceDisplayPlaneProperties2KHR;
    if (nameHash == XXH3_vkGetDisplayModeProperties2KHR && !strcmp(name, "vkGetDisplayModeProperties2KHR")) return (void *)table->GetDisplayModeProperties2KHR;
    if (nameHash == XXH3_vkGetDisplayPlaneCapabilities2KHR && !strcmp(name, "vkGetDisplayPlaneCapabilities2KHR")) return (void *)table->GetDisplayPlaneCapabilities2KHR;

    // ---- VK_KHR_fragment_shading_rate extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceFragmentShadingRatesKHR && !strcmp(name, "vkGetPhysicalDeviceFragmentShadingRatesKHR")) return (void *)table->GetPhysicalDeviceFragmentShadingRatesKHR;

    // ---- VK_KHR_video_encode_queue extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR")) return (void *)table->GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR;

    // ---- VK_KHR_cooperative_matrix extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR")) return (void *)table->GetPhysicalDeviceCooperativeMatrixPropertiesKHR;

    // ---- VK_KHR_calibrated_timestamps extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR && !strcmp(name, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR")) return (void *)table->GetPhysicalDeviceCalibrateableTimeDomainsKHR;

    // ---- VK_EXT_debug_report extension commands
    if (nameHash == XXH3_vkCreateDebugReportCallbackEXT && !strcmp(name, "vkCreateDebugReportCallbackEXT")) return (void *)table->CreateDebugReportCallbackEXT;
    if (nameHash == XXH3_vkDestroyDebugReportCallbackEXT && !strcmp(name, "vkDestroyDebugReportCallbackEXT")) return (void *)table->DestroyDebugReportCallbackEXT;
    if (nameHash == XXH3_vkDebugReportMessageEXT && !strcmp(name, "vkDebugReportMessageEXT")) return (void *)table->DebugReportMessageEXT;

    // ---- VK_GGP_stream_descriptor_surface extension commands
#if defined(VK_USE_PLATFORM_GGP)
    if (nameHash == XXH3_vkCreateStreamDescriptorSurfaceGGP && !strcmp(name, "vkCreateStreamDescriptorSurfaceGGP")) return (void *)table->CreateStreamDescriptorSurfaceGGP;
#endif // VK_USE_PLATFORM_GGP

    // ---- VK_NV_external_memory_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalImageFormatPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV")) return (void *)table->GetPhysicalDeviceExternalImageFormatPropertiesNV;

    // ---- VK_NN_vi_surface extension commands
#if defined(VK_USE_PLATFORM_VI_NN)
    if (nameHash == XXH3_vkCreateViSurfaceNN && !strcmp(name, "vkCreateViSurfaceNN")) return (void *)table->CreateViSurfaceNN;
#endif // VK_USE_PLATFORM_VI_NN

    // ---- VK_EXT_direct_mode_display extension commands
    if (nameHash == XXH3_vkReleaseDisplayEXT && !strcmp(name, "vkReleaseDisplayEXT")) return (void *)table->ReleaseDisplayEXT;

    // ---- VK_EXT_acquire_xlib_display extension commands
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    if (nameHash == XXH3_vkAcquireXlibDisplayEXT && !strcmp(name, "vkAcquireXlibDisplayEXT")) return (void *)table->AcquireXlibDisplayEXT;
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    if (nameHash == XXH3_vkGetRandROutputDisplayEXT && !strcmp(name, "vkGetRandROutputDisplayEXT")) return (void *)table->GetRandROutputDisplayEXT;
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT

    // ---- VK_EXT_display_surface_counter extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceCapabilities2EXT && !strcmp(name, "vkGetPhysicalDeviceSurfaceCapabilities2EXT")) return (void *)table->GetPhysicalDeviceSurfaceCapabilities2EXT;

    // ---- VK_MVK_ios_surface extension commands
#if defined(VK_USE_PLATFORM_IOS_MVK)
    if (nameHash == XXH3_vkCreateIOSSurfaceMVK && !strcmp(name, "vkCreateIOSSurfaceMVK")) return (void *)table->CreateIOSSurfaceMVK;
#endif // VK_USE_PLATFORM_IOS_MVK

    // ---- VK_MVK_macos_surface extension commands
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    if (nameHash == XXH3_vkCreateMacOSSurfaceMVK && !strcmp(name, "vkCreateMacOSSurfaceMVK")) return (void *)table->CreateMacOSSurfaceMVK;
#endif // VK_USE_PLATFORM_MACOS_MVK

    // ---- VK_EXT_debug_utils extension commands
    if (nameHash == XXH3_vkCreateDebugUtilsMessengerEXT && !strcmp(name, "vkCreateDebugUtilsMessengerEXT")) return (void *)table->CreateDebugUtilsMessengerEXT;
    if (nameHash == XXH3_vkDestroyDebugUtilsMessengerEXT && !strcmp(name, "vkDestroyDebugUtilsMessengerEXT")) return (void *)table->DestroyDebugUtilsMessengerEXT;
    if (nameHash == XXH3_vkSubmitDebugUtilsMessageEXT && !strcmp(name, "vkSubmitDebugUtilsMessageEXT")) return (void *)table->SubmitDebugUtilsMessageEXT;

    // ---- VK_EXT_descriptor_heap extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceDescriptorSizeEXT && !strcmp(name, "vkGetPhysicalDeviceDescriptorSizeEXT")) return (void *)table->GetPhysicalDeviceDescriptorSizeEXT;

    // ---- VK_EXT_sample_locations extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceMultisamplePropertiesEXT && !strcmp(name, "vkGetPhysicalDeviceMultisamplePropertiesEXT")) return (void *)table->GetPhysicalDeviceMultisamplePropertiesEXT;

    // ---- VK_EXT_calibrated_timestamps extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT && !strcmp(name, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT")) return (void *)table->GetPhysicalDeviceCalibrateableTimeDomainsEXT;

    // ---- VK_FUCHSIA_imagepipe_surface extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkCreateImagePipeSurfaceFUCHSIA && !strcmp(name, "vkCreateImagePipeSurfaceFUCHSIA")) return (void *)table->CreateImagePipeSurfaceFUCHSIA;
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_EXT_metal_surface extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkCreateMetalSurfaceEXT && !strcmp(name, "vkCreateMetalSurfaceEXT")) return (void *)table->CreateMetalSurfaceEXT;
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_tooling_info extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceToolPropertiesEXT && !strcmp(name, "vkGetPhysicalDeviceToolPropertiesEXT")) return (void *)table->GetPhysicalDeviceToolPropertiesEXT;

    // ---- VK_NV_cooperative_matrix extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV")) return (void *)table->GetPhysicalDeviceCooperativeMatrixPropertiesNV;

    // ---- VK_NV_coverage_reduction_mode extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV && !strcmp(name, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV")) return (void *)table->GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfacePresentModes2EXT && !strcmp(name, "vkGetPhysicalDeviceSurfacePresentModes2EXT")) return (void *)table->GetPhysicalDeviceSurfacePresentModes2EXT;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_headless_surface extension commands
    if (nameHash == XXH3_vkCreateHeadlessSurfaceEXT && !strcmp(name, "vkCreateHeadlessSurfaceEXT")) return (void *)table->CreateHeadlessSurfaceEXT;

    // ---- VK_EXT_acquire_drm_display extension commands
    if (nameHash == XXH3_vkAcquireDrmDisplayEXT && !strcmp(name, "vkAcquireDrmDisplayEXT")) return (void *)table->AcquireDrmDisplayEXT;
    if (nameHash == XXH3_vkGetDrmDisplayEXT && !strcmp(name, "vkGetDrmDisplayEXT")) return (void *)table->GetDrmDisplayEXT;

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkAcquireWinrtDisplayNV && !strcmp(name, "vkAcquireWinrtDisplayNV")) return (void *)table->AcquireWinrtDisplayNV;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetWinrtDisplayNV && !strcmp(name, "vkGetWinrtDisplayNV")) return (void *)table->GetWinrtDisplayNV;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_directfb_surface extension commands
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    if (nameHash == XXH3_vkCreateDirectFBSurfaceEXT && !strcmp(name, "vkCreateDirectFBSurfaceEXT")) return (void *)table->CreateDirectFBSurfaceEXT;
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    if (nameHash == XXH3_vkGetPhysicalDeviceDirectFBPresentationSupportEXT && !strcmp(name, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT")) return (void *)table->GetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

    // ---- VK_QNX_screen_surface extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (nameHash == XXH3_vkCreateScreenSurfaceQNX && !strcmp(name, "vkCreateScreenSurfaceQNX")) return (void *)table->CreateScreenSurfaceQNX;
#endif // VK_USE_PLATFORM_SCREEN_QNX
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (nameHash == XXH3_vkGetPhysicalDeviceScreenPresentationSupportQNX && !strcmp(name, "vkGetPhysicalDeviceScreenPresentationSupportQNX")) return (void *)table->GetPhysicalDeviceScreenPresentationSupportQNX;
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_ARM_tensors extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalTensorPropertiesARM && !strcmp(name, "vkGetPhysicalDeviceExternalTensorPropertiesARM")) return (void *)table->GetPhysicalDeviceExternalTensorPropertiesARM;

    // ---- VK_NV_optical_flow extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceOpticalFlowImageFormatsNV && !strcmp(name, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV")) return (void *)table->GetPhysicalDeviceOpticalFlowImageFormatsNV;

    // ---- VK_NV_cooperative_vector extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeVectorPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceCooperativeVectorPropertiesNV")) return (void *)table->GetPhysicalDeviceCooperativeVectorPropertiesNV;

    // ---- VK_ARM_data_graph extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM")) return (void *)table->GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM")) return (void *)table->GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM;

    // ---- VK_ARM_data_graph_instruction_set_tosa extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM")) return (void *)table->GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM;

    // ---- VK_OHOS_surface extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    if (nameHash == XXH3_vkCreateSurfaceOHOS && !strcmp(name, "vkCreateSurfaceOHOS")) return (void *)table->CreateSurfaceOHOS;
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_NV_cooperative_matrix2 extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV")) return (void *)table->GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV;

    // ---- VK_ARM_performance_counters_by_region extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM && !strcmp(name, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM")) return (void *)table->EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM;

    // ---- VK_ARM_shader_instrumentation extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM && !strcmp(name, "vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM")) return (void *)table->EnumeratePhysicalDeviceShaderInstrumentationMetricsARM;

    // ---- VK_ARM_data_graph_optical_flow extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM")) return (void *)table->GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM;

    // ---- VK_SEC_ubm_surface extension commands
#if defined(VK_USE_PLATFORM_UBM_SEC)
    if (nameHash == XXH3_vkCreateUbmSurfaceSEC && !strcmp(name, "vkCreateUbmSurfaceSEC")) return (void *)table->CreateUbmSurfaceSEC;
#endif // VK_USE_PLATFORM_UBM_SEC
#if defined(VK_USE_PLATFORM_UBM_SEC)
    if (nameHash == XXH3_vkGetPhysicalDeviceUbmPresentationSupportSEC && !strcmp(name, "vkGetPhysicalDeviceUbmPresentationSupportSEC")) return (void *)table->GetPhysicalDeviceUbmPresentationSupportSEC;
#endif // VK_USE_PLATFORM_UBM_SEC

    *found_name = false;
    return NULL;
}


// ---- VK_KHR_video_queue extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceVideoCapabilitiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkVideoProfileInfoKHR*                pVideoProfile,
    VkVideoCapabilitiesKHR*                     pCapabilities) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceVideoCapabilitiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceVideoCapabilitiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceVideoCapabilitiesKHR(unwrapped_phys_dev, pVideoProfile, pCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceVideoCapabilitiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkVideoProfileInfoKHR*                pVideoProfile,
    VkVideoCapabilitiesKHR*                     pCapabilities) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceVideoCapabilitiesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceVideoCapabilitiesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceVideoCapabilitiesKHR(phys_dev_term->phys_dev, pVideoProfile, pCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceVideoFormatPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceVideoFormatInfoKHR*   pVideoFormatInfo,
    uint32_t*                                   pVideoFormatPropertyCount,
    VkVideoFormatPropertiesKHR*                 pVideoFormatProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceVideoFormatPropertiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceVideoFormatPropertiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceVideoFormatPropertiesKHR(unwrapped_phys_dev, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceVideoFormatPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceVideoFormatInfoKHR*   pVideoFormatInfo,
    uint32_t*                                   pVideoFormatPropertyCount,
    VkVideoFormatPropertiesKHR*                 pVideoFormatProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceVideoFormatPropertiesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceVideoFormatPropertiesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceVideoFormatPropertiesKHR(phys_dev_term->phys_dev, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateVideoSessionKHR(
    VkDevice                                    device,
    const VkVideoSessionCreateInfoKHR*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkVideoSessionKHR*                          pVideoSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateVideoSessionKHR: Invalid device "
                   "[VUID-vkCreateVideoSessionKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateVideoSessionKHR(device, pCreateInfo, pAllocator, pVideoSession);
}

VKAPI_ATTR void VKAPI_CALL DestroyVideoSessionKHR(
    VkDevice                                    device,
    VkVideoSessionKHR                           videoSession,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyVideoSessionKHR: Invalid device "
                   "[VUID-vkDestroyVideoSessionKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyVideoSessionKHR(device, videoSession, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetVideoSessionMemoryRequirementsKHR(
    VkDevice                                    device,
    VkVideoSessionKHR                           videoSession,
    uint32_t*                                   pMemoryRequirementsCount,
    VkVideoSessionMemoryRequirementsKHR*        pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetVideoSessionMemoryRequirementsKHR: Invalid device "
                   "[VUID-vkGetVideoSessionMemoryRequirementsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetVideoSessionMemoryRequirementsKHR(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL BindVideoSessionMemoryKHR(
    VkDevice                                    device,
    VkVideoSessionKHR                           videoSession,
    uint32_t                                    bindSessionMemoryInfoCount,
    const VkBindVideoSessionMemoryInfoKHR*      pBindSessionMemoryInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindVideoSessionMemoryKHR: Invalid device "
                   "[VUID-vkBindVideoSessionMemoryKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindVideoSessionMemoryKHR(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateVideoSessionParametersKHR(
    VkDevice                                    device,
    const VkVideoSessionParametersCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkVideoSessionParametersKHR*                pVideoSessionParameters) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateVideoSessionParametersKHR: Invalid device "
                   "[VUID-vkCreateVideoSessionParametersKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateVideoSessionParametersKHR(device, pCreateInfo, pAllocator, pVideoSessionParameters);
}

VKAPI_ATTR VkResult VKAPI_CALL UpdateVideoSessionParametersKHR(
    VkDevice                                    device,
    VkVideoSessionParametersKHR                 videoSessionParameters,
    const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUpdateVideoSessionParametersKHR: Invalid device "
                   "[VUID-vkUpdateVideoSessionParametersKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->UpdateVideoSessionParametersKHR(device, videoSessionParameters, pUpdateInfo);
}

VKAPI_ATTR void VKAPI_CALL DestroyVideoSessionParametersKHR(
    VkDevice                                    device,
    VkVideoSessionParametersKHR                 videoSessionParameters,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyVideoSessionParametersKHR: Invalid device "
                   "[VUID-vkDestroyVideoSessionParametersKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyVideoSessionParametersKHR(device, videoSessionParameters, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginVideoCodingKHR(
    VkCommandBuffer                             commandBuffer,
    const VkVideoBeginCodingInfoKHR*            pBeginInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginVideoCodingKHR: Invalid commandBuffer "
                   "[VUID-vkCmdBeginVideoCodingKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginVideoCodingKHR(commandBuffer, pBeginInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndVideoCodingKHR(
    VkCommandBuffer                             commandBuffer,
    const VkVideoEndCodingInfoKHR*              pEndCodingInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndVideoCodingKHR: Invalid commandBuffer "
                   "[VUID-vkCmdEndVideoCodingKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndVideoCodingKHR(commandBuffer, pEndCodingInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdControlVideoCodingKHR(
    VkCommandBuffer                             commandBuffer,
    const VkVideoCodingControlInfoKHR*          pCodingControlInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdControlVideoCodingKHR: Invalid commandBuffer "
                   "[VUID-vkCmdControlVideoCodingKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdControlVideoCodingKHR(commandBuffer, pCodingControlInfo);
}


// ---- VK_KHR_video_decode_queue extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDecodeVideoKHR(
    VkCommandBuffer                             commandBuffer,
    const VkVideoDecodeInfoKHR*                 pDecodeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDecodeVideoKHR: Invalid commandBuffer "
                   "[VUID-vkCmdDecodeVideoKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDecodeVideoKHR(commandBuffer, pDecodeInfo);
}


// ---- VK_KHR_dynamic_rendering extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBeginRenderingKHR(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingInfo*                      pRenderingInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginRenderingKHR: Invalid commandBuffer "
                   "[VUID-vkCmdBeginRenderingKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginRenderingKHR(commandBuffer, pRenderingInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndRenderingKHR(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndRenderingKHR: Invalid commandBuffer "
                   "[VUID-vkCmdEndRenderingKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndRenderingKHR(commandBuffer);
}


// ---- VK_KHR_device_group extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetDeviceGroupPeerMemoryFeaturesKHR(
    VkDevice                                    device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    VkPeerMemoryFeatureFlags*                   pPeerMemoryFeatures) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupPeerMemoryFeaturesKHR: Invalid device "
                   "[VUID-vkGetDeviceGroupPeerMemoryFeaturesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDeviceMaskKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    deviceMask) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDeviceMaskKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetDeviceMaskKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDeviceMaskKHR(commandBuffer, deviceMask);
}

VKAPI_ATTR void VKAPI_CALL CmdDispatchBaseKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchBaseKHR: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchBaseKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}


// ---- VK_KHR_maintenance1 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL TrimCommandPoolKHR(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolTrimFlags                      flags) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkTrimCommandPoolKHR: Invalid device "
                   "[VUID-vkTrimCommandPoolKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->TrimCommandPoolKHR(device, commandPool, flags);
}


// ---- VK_KHR_external_memory_win32 extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryWin32HandleKHR(
    VkDevice                                    device,
    const VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryWin32HandleKHR: Invalid device "
                   "[VUID-vkGetMemoryWin32HandleKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryWin32HandlePropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    HANDLE                                      handle,
    VkMemoryWin32HandlePropertiesKHR*           pMemoryWin32HandleProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryWin32HandlePropertiesKHR: Invalid device "
                   "[VUID-vkGetMemoryWin32HandlePropertiesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryWin32HandlePropertiesKHR(device, handleType, handle, pMemoryWin32HandleProperties);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_KHR_external_memory_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryFdKHR(
    VkDevice                                    device,
    const VkMemoryGetFdInfoKHR*                 pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryFdKHR: Invalid device "
                   "[VUID-vkGetMemoryFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryFdKHR(device, pGetFdInfo, pFd);
}

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryFdPropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    VkMemoryFdPropertiesKHR*                    pMemoryFdProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryFdPropertiesKHR: Invalid device "
                   "[VUID-vkGetMemoryFdPropertiesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties);
}


// ---- VK_KHR_external_semaphore_win32 extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    const VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportSemaphoreWin32HandleKHR: Invalid device "
                   "[VUID-vkImportSemaphoreWin32HandleKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportSemaphoreWin32HandleKHR(device, pImportSemaphoreWin32HandleInfo);
}

#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    const VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSemaphoreWin32HandleKHR: Invalid device "
                   "[VUID-vkGetSemaphoreWin32HandleKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSemaphoreWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_KHR_external_semaphore_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreFdKHR(
    VkDevice                                    device,
    const VkImportSemaphoreFdInfoKHR*           pImportSemaphoreFdInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportSemaphoreFdKHR: Invalid device "
                   "[VUID-vkImportSemaphoreFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreFdKHR(
    VkDevice                                    device,
    const VkSemaphoreGetFdInfoKHR*              pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSemaphoreFdKHR: Invalid device "
                   "[VUID-vkGetSemaphoreFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSemaphoreFdKHR(device, pGetFdInfo, pFd);
}


// ---- VK_KHR_push_descriptor extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdPushDescriptorSetKHR(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    set,
    uint32_t                                    descriptorWriteCount,
    const VkWriteDescriptorSet*                 pDescriptorWrites) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPushDescriptorSetKHR: Invalid commandBuffer "
                   "[VUID-vkCmdPushDescriptorSetKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

VKAPI_ATTR void VKAPI_CALL CmdPushDescriptorSetWithTemplateKHR(
    VkCommandBuffer                             commandBuffer,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    VkPipelineLayout                            layout,
    uint32_t                                    set,
    const void*                                 pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPushDescriptorSetWithTemplateKHR: Invalid commandBuffer "
                   "[VUID-vkCmdPushDescriptorSetWithTemplateKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}


// ---- VK_KHR_descriptor_update_template extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateDescriptorUpdateTemplateKHR(
    VkDevice                                    device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorUpdateTemplate*                 pDescriptorUpdateTemplate) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDescriptorUpdateTemplateKHR: Invalid device "
                   "[VUID-vkCreateDescriptorUpdateTemplateKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

VKAPI_ATTR void VKAPI_CALL DestroyDescriptorUpdateTemplateKHR(
    VkDevice                                    device,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyDescriptorUpdateTemplateKHR: Invalid device "
                   "[VUID-vkDestroyDescriptorUpdateTemplateKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL UpdateDescriptorSetWithTemplateKHR(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const void*                                 pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUpdateDescriptorSetWithTemplateKHR: Invalid device "
                   "[VUID-vkUpdateDescriptorSetWithTemplateKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->UpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
}


// ---- VK_KHR_create_renderpass2 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateRenderPass2KHR(
    VkDevice                                    device,
    const VkRenderPassCreateInfo2*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateRenderPass2KHR: Invalid device "
                   "[VUID-vkCreateRenderPass2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginRenderPass2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    const VkSubpassBeginInfo*                   pSubpassBeginInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginRenderPass2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBeginRenderPass2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdNextSubpass2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassBeginInfo*                   pSubpassBeginInfo,
    const VkSubpassEndInfo*                     pSubpassEndInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdNextSubpass2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdNextSubpass2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndRenderPass2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassEndInfo*                     pSubpassEndInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndRenderPass2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdEndRenderPass2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo);
}


// ---- VK_KHR_shared_presentable_image extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainStatusKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainStatusKHR: Invalid device "
                   "[VUID-vkGetSwapchainStatusKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainStatusKHR(device, swapchain);
}


// ---- VK_KHR_external_fence_win32 extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL ImportFenceWin32HandleKHR(
    VkDevice                                    device,
    const VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportFenceWin32HandleKHR: Invalid device "
                   "[VUID-vkImportFenceWin32HandleKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportFenceWin32HandleKHR(device, pImportFenceWin32HandleInfo);
}

#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetFenceWin32HandleKHR(
    VkDevice                                    device,
    const VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetFenceWin32HandleKHR: Invalid device "
                   "[VUID-vkGetFenceWin32HandleKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetFenceWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_KHR_external_fence_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ImportFenceFdKHR(
    VkDevice                                    device,
    const VkImportFenceFdInfoKHR*               pImportFenceFdInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportFenceFdKHR: Invalid device "
                   "[VUID-vkImportFenceFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportFenceFdKHR(device, pImportFenceFdInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetFenceFdKHR(
    VkDevice                                    device,
    const VkFenceGetFdInfoKHR*                  pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetFenceFdKHR: Invalid device "
                   "[VUID-vkGetFenceFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetFenceFdKHR(device, pGetFdInfo, pFd);
}


// ---- VK_KHR_performance_query extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterKHR*                    pCounters,
    VkPerformanceCounterDescriptionKHR*         pCounterDescriptions) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR: Invalid physicalDevice "
                   "[VUID-vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(unwrapped_phys_dev, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterKHR*                    pCounters,
    VkPerformanceCounterDescriptionKHR*         pCounterDescriptions) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(phys_dev_term->phys_dev, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR*  pPerformanceQueryCreateInfo,
    uint32_t*                                   pNumPasses) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(unwrapped_phys_dev, pPerformanceQueryCreateInfo, pNumPasses);
}

VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR*  pPerformanceQueryCreateInfo,
    uint32_t*                                   pNumPasses) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    icd_term->dispatch.GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(phys_dev_term->phys_dev, pPerformanceQueryCreateInfo, pNumPasses);
}

VKAPI_ATTR VkResult VKAPI_CALL AcquireProfilingLockKHR(
    VkDevice                                    device,
    const VkAcquireProfilingLockInfoKHR*        pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireProfilingLockKHR: Invalid device "
                   "[VUID-vkAcquireProfilingLockKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->AcquireProfilingLockKHR(device, pInfo);
}

VKAPI_ATTR void VKAPI_CALL ReleaseProfilingLockKHR(
    VkDevice                                    device) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseProfilingLockKHR: Invalid device "
                   "[VUID-vkReleaseProfilingLockKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->ReleaseProfilingLockKHR(device);
}


// ---- VK_KHR_get_memory_requirements2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements2KHR(
    VkDevice                                    device,
    const VkImageMemoryRequirementsInfo2*       pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageMemoryRequirements2KHR: Invalid device "
                   "[VUID-vkGetImageMemoryRequirements2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetBufferMemoryRequirements2KHR(
    VkDevice                                    device,
    const VkBufferMemoryRequirementsInfo2*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetBufferMemoryRequirements2KHR: Invalid device "
                   "[VUID-vkGetBufferMemoryRequirements2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetImageSparseMemoryRequirements2KHR(
    VkDevice                                    device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageSparseMemoryRequirements2KHR: Invalid device "
                   "[VUID-vkGetImageSparseMemoryRequirements2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}


// ---- VK_KHR_sampler_ycbcr_conversion extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateSamplerYcbcrConversionKHR(
    VkDevice                                    device,
    const VkSamplerYcbcrConversionCreateInfo*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSamplerYcbcrConversion*                   pYcbcrConversion) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSamplerYcbcrConversionKHR: Invalid device "
                   "[VUID-vkCreateSamplerYcbcrConversionKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

VKAPI_ATTR void VKAPI_CALL DestroySamplerYcbcrConversionKHR(
    VkDevice                                    device,
    VkSamplerYcbcrConversion                    ycbcrConversion,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroySamplerYcbcrConversionKHR: Invalid device "
                   "[VUID-vkDestroySamplerYcbcrConversionKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator);
}


// ---- VK_KHR_bind_memory2 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL BindBufferMemory2KHR(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindBufferMemoryInfo*               pBindInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindBufferMemory2KHR: Invalid device "
                   "[VUID-vkBindBufferMemory2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindBufferMemory2KHR(device, bindInfoCount, pBindInfos);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory2KHR(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindImageMemoryInfo*                pBindInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindImageMemory2KHR: Invalid device "
                   "[VUID-vkBindImageMemory2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindImageMemory2KHR(device, bindInfoCount, pBindInfos);
}


// ---- VK_KHR_maintenance3 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetDescriptorSetLayoutSupportKHR(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    VkDescriptorSetLayoutSupport*               pSupport) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDescriptorSetLayoutSupportKHR: Invalid device "
                   "[VUID-vkGetDescriptorSetLayoutSupportKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport);
}


// ---- VK_KHR_draw_indirect_count extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDrawIndirectCountKHR(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndirectCountKHR: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndirectCountKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndexedIndirectCountKHR(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndexedIndirectCountKHR: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndexedIndirectCountKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndexedIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}


// ---- VK_KHR_timeline_semaphore extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreCounterValueKHR(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    uint64_t*                                   pValue) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSemaphoreCounterValueKHR: Invalid device "
                   "[VUID-vkGetSemaphoreCounterValueKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSemaphoreCounterValueKHR(device, semaphore, pValue);
}

VKAPI_ATTR VkResult VKAPI_CALL WaitSemaphoresKHR(
    VkDevice                                    device,
    const VkSemaphoreWaitInfo*                  pWaitInfo,
    uint64_t                                    timeout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWaitSemaphoresKHR: Invalid device "
                   "[VUID-vkWaitSemaphoresKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WaitSemaphoresKHR(device, pWaitInfo, timeout);
}

VKAPI_ATTR VkResult VKAPI_CALL SignalSemaphoreKHR(
    VkDevice                                    device,
    const VkSemaphoreSignalInfo*                pSignalInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSignalSemaphoreKHR: Invalid device "
                   "[VUID-vkSignalSemaphoreKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SignalSemaphoreKHR(device, pSignalInfo);
}


// ---- VK_KHR_fragment_shading_rate extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR*     pFragmentShadingRates) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceFragmentShadingRatesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceFragmentShadingRatesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceFragmentShadingRatesKHR(unwrapped_phys_dev, pFragmentShadingRateCount, pFragmentShadingRates);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR*     pFragmentShadingRates) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceFragmentShadingRatesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceFragmentShadingRatesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceFragmentShadingRatesKHR(phys_dev_term->phys_dev, pFragmentShadingRateCount, pFragmentShadingRates);
}

VKAPI_ATTR void VKAPI_CALL CmdSetFragmentShadingRateKHR(
    VkCommandBuffer                             commandBuffer,
    const VkExtent2D*                           pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetFragmentShadingRateKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetFragmentShadingRateKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps);
}


// ---- VK_KHR_dynamic_rendering_local_read extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetRenderingAttachmentLocationsKHR(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingAttachmentLocationInfo*    pLocationInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRenderingAttachmentLocationsKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetRenderingAttachmentLocationsKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRenderingAttachmentLocationsKHR(commandBuffer, pLocationInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRenderingInputAttachmentIndicesKHR(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingInputAttachmentIndexInfo*  pInputAttachmentIndexInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRenderingInputAttachmentIndicesKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetRenderingInputAttachmentIndicesKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRenderingInputAttachmentIndicesKHR(commandBuffer, pInputAttachmentIndexInfo);
}


// ---- VK_KHR_present_wait extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL WaitForPresentKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint64_t                                    presentId,
    uint64_t                                    timeout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWaitForPresentKHR: Invalid device "
                   "[VUID-vkWaitForPresentKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WaitForPresentKHR(device, swapchain, presentId, timeout);
}


// ---- VK_KHR_buffer_device_address extension trampoline/terminators

VKAPI_ATTR VkDeviceAddress VKAPI_CALL GetBufferDeviceAddressKHR(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetBufferDeviceAddressKHR: Invalid device "
                   "[VUID-vkGetBufferDeviceAddressKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetBufferDeviceAddressKHR(device, pInfo);
}

VKAPI_ATTR uint64_t VKAPI_CALL GetBufferOpaqueCaptureAddressKHR(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetBufferOpaqueCaptureAddressKHR: Invalid device "
                   "[VUID-vkGetBufferOpaqueCaptureAddressKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetBufferOpaqueCaptureAddressKHR(device, pInfo);
}

VKAPI_ATTR uint64_t VKAPI_CALL GetDeviceMemoryOpaqueCaptureAddressKHR(
    VkDevice                                    device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceMemoryOpaqueCaptureAddressKHR: Invalid device "
                   "[VUID-vkGetDeviceMemoryOpaqueCaptureAddressKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceMemoryOpaqueCaptureAddressKHR(device, pInfo);
}


// ---- VK_KHR_deferred_host_operations extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateDeferredOperationKHR(
    VkDevice                                    device,
    const VkAllocationCallbacks*                pAllocator,
    VkDeferredOperationKHR*                     pDeferredOperation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDeferredOperationKHR: Invalid device "
                   "[VUID-vkCreateDeferredOperationKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateDeferredOperationKHR(device, pAllocator, pDeferredOperation);
}

VKAPI_ATTR void VKAPI_CALL DestroyDeferredOperationKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyDeferredOperationKHR: Invalid device "
                   "[VUID-vkDestroyDeferredOperationKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyDeferredOperationKHR(device, operation, pAllocator);
}

VKAPI_ATTR uint32_t VKAPI_CALL GetDeferredOperationMaxConcurrencyKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeferredOperationMaxConcurrencyKHR: Invalid device "
                   "[VUID-vkGetDeferredOperationMaxConcurrencyKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeferredOperationMaxConcurrencyKHR(device, operation);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDeferredOperationResultKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeferredOperationResultKHR: Invalid device "
                   "[VUID-vkGetDeferredOperationResultKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeferredOperationResultKHR(device, operation);
}

VKAPI_ATTR VkResult VKAPI_CALL DeferredOperationJoinKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDeferredOperationJoinKHR: Invalid device "
                   "[VUID-vkDeferredOperationJoinKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->DeferredOperationJoinKHR(device, operation);
}


// ---- VK_KHR_pipeline_executable_properties extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPipelineExecutablePropertiesKHR(
    VkDevice                                    device,
    const VkPipelineInfoKHR*                    pPipelineInfo,
    uint32_t*                                   pExecutableCount,
    VkPipelineExecutablePropertiesKHR*          pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineExecutablePropertiesKHR: Invalid device "
                   "[VUID-vkGetPipelineExecutablePropertiesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPipelineExecutableStatisticsKHR(
    VkDevice                                    device,
    const VkPipelineExecutableInfoKHR*          pExecutableInfo,
    uint32_t*                                   pStatisticCount,
    VkPipelineExecutableStatisticKHR*           pStatistics) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineExecutableStatisticsKHR: Invalid device "
                   "[VUID-vkGetPipelineExecutableStatisticsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPipelineExecutableInternalRepresentationsKHR(
    VkDevice                                    device,
    const VkPipelineExecutableInfoKHR*          pExecutableInfo,
    uint32_t*                                   pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineExecutableInternalRepresentationsKHR: Invalid device "
                   "[VUID-vkGetPipelineExecutableInternalRepresentationsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
}


// ---- VK_KHR_map_memory2 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL MapMemory2KHR(
    VkDevice                                    device,
    const VkMemoryMapInfo*                      pMemoryMapInfo,
    void**                                      ppData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkMapMemory2KHR: Invalid device "
                   "[VUID-vkMapMemory2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->MapMemory2KHR(device, pMemoryMapInfo, ppData);
}

VKAPI_ATTR VkResult VKAPI_CALL UnmapMemory2KHR(
    VkDevice                                    device,
    const VkMemoryUnmapInfo*                    pMemoryUnmapInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUnmapMemory2KHR: Invalid device "
                   "[VUID-vkUnmapMemory2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->UnmapMemory2KHR(device, pMemoryUnmapInfo);
}


// ---- VK_KHR_video_encode_queue extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo,
    VkVideoEncodeQualityLevelPropertiesKHR*     pQualityLevelProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(unwrapped_phys_dev, pQualityLevelInfo, pQualityLevelProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo,
    VkVideoEncodeQualityLevelPropertiesKHR*     pQualityLevelProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(phys_dev_term->phys_dev, pQualityLevelInfo, pQualityLevelProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetEncodedVideoSessionParametersKHR(
    VkDevice                                    device,
    const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo,
    VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo,
    size_t*                                     pDataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetEncodedVideoSessionParametersKHR: Invalid device "
                   "[VUID-vkGetEncodedVideoSessionParametersKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetEncodedVideoSessionParametersKHR(device, pVideoSessionParametersInfo, pFeedbackInfo, pDataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL CmdEncodeVideoKHR(
    VkCommandBuffer                             commandBuffer,
    const VkVideoEncodeInfoKHR*                 pEncodeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEncodeVideoKHR: Invalid commandBuffer "
                   "[VUID-vkCmdEncodeVideoKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEncodeVideoKHR(commandBuffer, pEncodeInfo);
}


// ---- VK_KHR_synchronization2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetEvent2KHR(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    const VkDependencyInfo*                     pDependencyInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetEvent2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetEvent2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetEvent2KHR(commandBuffer, event, pDependencyInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdResetEvent2KHR(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags2                       stageMask) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdResetEvent2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdResetEvent2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdResetEvent2KHR(commandBuffer, event, stageMask);
}

VKAPI_ATTR void VKAPI_CALL CmdWaitEvents2KHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    const VkDependencyInfo*                     pDependencyInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWaitEvents2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdWaitEvents2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDependencyInfo*                     pDependencyInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPipelineBarrier2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdPipelineBarrier2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteTimestamp2KHR(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteTimestamp2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdWriteTimestamp2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
}

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit2KHR(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo2*                        pSubmits,
    VkFence                                     fence) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueSubmit2KHR: Invalid queue "
                   "[VUID-vkQueueSubmit2KHR-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->QueueSubmit2KHR(queue, submitCount, pSubmits, fence);
}


// ---- VK_KHR_device_address_commands extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindIndexBuffer3KHR(
    VkCommandBuffer                             commandBuffer,
    const VkBindIndexBuffer3InfoKHR*            pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindIndexBuffer3KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBindIndexBuffer3KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindIndexBuffer3KHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBindVertexBuffers3KHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBindVertexBuffer3InfoKHR*           pBindingInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindVertexBuffers3KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBindVertexBuffers3KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindVertexBuffers3KHR(commandBuffer, firstBinding, bindingCount, pBindingInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndirect2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDrawIndirect2InfoKHR*               pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndirect2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndirect2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndirect2KHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndexedIndirect2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDrawIndirect2InfoKHR*               pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndexedIndirect2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndexedIndirect2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndexedIndirect2KHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdDispatchIndirect2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDispatchIndirect2InfoKHR*           pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchIndirect2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchIndirect2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchIndirect2KHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyDeviceMemoryInfoKHR*            pCopyMemoryInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryKHR(commandBuffer, pCopyMemoryInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryToImageKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyDeviceMemoryImageInfoKHR*       pCopyMemoryInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryToImageKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryToImageKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryToImageKHR(commandBuffer, pCopyMemoryInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImageToMemoryKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyDeviceMemoryImageInfoKHR*       pCopyMemoryInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyImageToMemoryKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyImageToMemoryKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyImageToMemoryKHR(commandBuffer, pCopyMemoryInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdUpdateMemoryKHR(
    VkCommandBuffer                             commandBuffer,
    const VkDeviceAddressRangeKHR*              pDstRange,
    VkAddressCommandFlagsKHR                    dstFlags,
    VkDeviceSize                                dataSize,
    const void*                                 pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdUpdateMemoryKHR: Invalid commandBuffer "
                   "[VUID-vkCmdUpdateMemoryKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdUpdateMemoryKHR(commandBuffer, pDstRange, dstFlags, dataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL CmdFillMemoryKHR(
    VkCommandBuffer                             commandBuffer,
    const VkDeviceAddressRangeKHR*              pDstRange,
    VkAddressCommandFlagsKHR                    dstFlags,
    uint32_t                                    data) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdFillMemoryKHR: Invalid commandBuffer "
                   "[VUID-vkCmdFillMemoryKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdFillMemoryKHR(commandBuffer, pDstRange, dstFlags, data);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyQueryPoolResultsToMemoryKHR(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    const VkStridedDeviceAddressRangeKHR*       pDstRange,
    VkAddressCommandFlagsKHR                    dstFlags,
    VkQueryResultFlags                          queryResultFlags) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyQueryPoolResultsToMemoryKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyQueryPoolResultsToMemoryKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyQueryPoolResultsToMemoryKHR(commandBuffer, queryPool, firstQuery, queryCount, pDstRange, dstFlags, queryResultFlags);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndirectCount2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDrawIndirectCount2InfoKHR*          pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndirectCount2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndirectCount2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndirectCount2KHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndexedIndirectCount2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDrawIndirectCount2InfoKHR*          pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndexedIndirectCount2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndexedIndirectCount2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndexedIndirectCount2KHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginConditionalRendering2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkConditionalRenderingBeginInfo2EXT*  pConditionalRenderingBegin) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginConditionalRendering2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginConditionalRendering2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginConditionalRendering2EXT(commandBuffer, pConditionalRenderingBegin);
}

VKAPI_ATTR void VKAPI_CALL CmdBindTransformFeedbackBuffers2EXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBindTransformFeedbackBuffer2InfoEXT* pBindingInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindTransformFeedbackBuffers2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindTransformFeedbackBuffers2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindTransformFeedbackBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBindingInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginTransformFeedback2EXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterRange,
    uint32_t                                    counterRangeCount,
    const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginTransformFeedback2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginTransformFeedback2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginTransformFeedback2EXT(commandBuffer, firstCounterRange, counterRangeCount, pCounterInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdEndTransformFeedback2EXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterRange,
    uint32_t                                    counterRangeCount,
    const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndTransformFeedback2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndTransformFeedback2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndTransformFeedback2EXT(commandBuffer, firstCounterRange, counterRangeCount, pCounterInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndirectByteCount2EXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfo,
    uint32_t                                    counterOffset,
    uint32_t                                    vertexStride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndirectByteCount2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndirectByteCount2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndirectByteCount2EXT(commandBuffer, instanceCount, firstInstance, pCounterInfo, counterOffset, vertexStride);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksIndirect2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkDrawIndirect2InfoKHR*               pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksIndirect2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksIndirect2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksIndirect2EXT(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksIndirectCount2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkDrawIndirectCount2InfoKHR*          pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksIndirectCount2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksIndirectCount2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksIndirectCount2EXT(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteMarkerToMemoryAMD(
    VkCommandBuffer                             commandBuffer,
    const VkMemoryMarkerInfoAMD*                pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteMarkerToMemoryAMD: Invalid commandBuffer "
                   "[VUID-vkCmdWriteMarkerToMemoryAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteMarkerToMemoryAMD(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateAccelerationStructure2KHR(
    VkDevice                                    device,
    const VkAccelerationStructureCreateInfo2KHR* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkAccelerationStructureKHR*                 pAccelerationStructure) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateAccelerationStructure2KHR: Invalid device "
                   "[VUID-vkCreateAccelerationStructure2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateAccelerationStructure2KHR(device, pCreateInfo, pAllocator, pAccelerationStructure);
}


// ---- VK_KHR_copy_commands2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdCopyBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferInfo2*                    pCopyBufferInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyBuffer2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyBuffer2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageInfo2*                     pCopyImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyBufferToImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferToImageInfo2*             pCopyBufferToImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyBufferToImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyBufferToImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageToBufferInfo2*             pCopyImageToBufferInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyImageToBuffer2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyImageToBuffer2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBlitImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkBlitImageInfo2*                     pBlitImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBlitImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBlitImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdResolveImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkResolveImageInfo2*                  pResolveImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdResolveImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdResolveImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
}


// ---- VK_KHR_ray_tracing_maintenance1 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdTraceRaysIndirect2KHR(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             indirectDeviceAddress) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdTraceRaysIndirect2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdTraceRaysIndirect2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress);
}


// ---- VK_KHR_maintenance4 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetDeviceBufferMemoryRequirementsKHR(
    VkDevice                                    device,
    const VkDeviceBufferMemoryRequirements*     pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceBufferMemoryRequirementsKHR: Invalid device "
                   "[VUID-vkGetDeviceBufferMemoryRequirementsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceBufferMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceImageMemoryRequirementsKHR(
    VkDevice                                    device,
    const VkDeviceImageMemoryRequirements*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceImageMemoryRequirementsKHR: Invalid device "
                   "[VUID-vkGetDeviceImageMemoryRequirementsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceImageMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceImageSparseMemoryRequirementsKHR(
    VkDevice                                    device,
    const VkDeviceImageMemoryRequirements*      pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceImageSparseMemoryRequirementsKHR: Invalid device "
                   "[VUID-vkGetDeviceImageSparseMemoryRequirementsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceImageSparseMemoryRequirementsKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}


// ---- VK_KHR_maintenance5 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindIndexBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkIndexType                                 indexType) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindIndexBuffer2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBindIndexBuffer2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindIndexBuffer2KHR(commandBuffer, buffer, offset, size, indexType);
}

VKAPI_ATTR void VKAPI_CALL GetRenderingAreaGranularityKHR(
    VkDevice                                    device,
    const VkRenderingAreaInfo*                  pRenderingAreaInfo,
    VkExtent2D*                                 pGranularity) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRenderingAreaGranularityKHR: Invalid device "
                   "[VUID-vkGetRenderingAreaGranularityKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetRenderingAreaGranularityKHR(device, pRenderingAreaInfo, pGranularity);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceImageSubresourceLayoutKHR(
    VkDevice                                    device,
    const VkDeviceImageSubresourceInfo*         pInfo,
    VkSubresourceLayout2*                       pLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceImageSubresourceLayoutKHR: Invalid device "
                   "[VUID-vkGetDeviceImageSubresourceLayoutKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceImageSubresourceLayoutKHR(device, pInfo, pLayout);
}

VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout2KHR(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource2*                  pSubresource,
    VkSubresourceLayout2*                       pLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageSubresourceLayout2KHR: Invalid device "
                   "[VUID-vkGetImageSubresourceLayout2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetImageSubresourceLayout2KHR(device, image, pSubresource, pLayout);
}


// ---- VK_KHR_present_wait2 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL WaitForPresent2KHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkPresentWait2InfoKHR*                pPresentWait2Info) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWaitForPresent2KHR: Invalid device "
                   "[VUID-vkWaitForPresent2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WaitForPresent2KHR(device, swapchain, pPresentWait2Info);
}


// ---- VK_KHR_pipeline_binary extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineBinariesKHR(
    VkDevice                                    device,
    const VkPipelineBinaryCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineBinaryHandlesInfoKHR*             pBinaries) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreatePipelineBinariesKHR: Invalid device "
                   "[VUID-vkCreatePipelineBinariesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreatePipelineBinariesKHR(device, pCreateInfo, pAllocator, pBinaries);
}

VKAPI_ATTR void VKAPI_CALL DestroyPipelineBinaryKHR(
    VkDevice                                    device,
    VkPipelineBinaryKHR                         pipelineBinary,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyPipelineBinaryKHR: Invalid device "
                   "[VUID-vkDestroyPipelineBinaryKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyPipelineBinaryKHR(device, pipelineBinary, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPipelineKeyKHR(
    VkDevice                                    device,
    const VkPipelineCreateInfoKHR*              pPipelineCreateInfo,
    VkPipelineBinaryKeyKHR*                     pPipelineKey) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineKeyKHR: Invalid device "
                   "[VUID-vkGetPipelineKeyKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelineKeyKHR(device, pPipelineCreateInfo, pPipelineKey);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPipelineBinaryDataKHR(
    VkDevice                                    device,
    const VkPipelineBinaryDataInfoKHR*          pInfo,
    VkPipelineBinaryKeyKHR*                     pPipelineBinaryKey,
    size_t*                                     pPipelineBinaryDataSize,
    void*                                       pPipelineBinaryData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineBinaryDataKHR: Invalid device "
                   "[VUID-vkGetPipelineBinaryDataKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelineBinaryDataKHR(device, pInfo, pPipelineBinaryKey, pPipelineBinaryDataSize, pPipelineBinaryData);
}

VKAPI_ATTR VkResult VKAPI_CALL ReleaseCapturedPipelineDataKHR(
    VkDevice                                    device,
    const VkReleaseCapturedPipelineDataInfoKHR* pInfo,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseCapturedPipelineDataKHR: Invalid device "
                   "[VUID-vkReleaseCapturedPipelineDataKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ReleaseCapturedPipelineDataKHR(device, pInfo, pAllocator);
}


// ---- VK_KHR_swapchain_maintenance1 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ReleaseSwapchainImagesKHR(
    VkDevice                                    device,
    const VkReleaseSwapchainImagesInfoKHR*      pReleaseInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseSwapchainImagesKHR: Invalid device "
                   "[VUID-vkReleaseSwapchainImagesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ReleaseSwapchainImagesKHR(device, pReleaseInfo);
}


// ---- VK_KHR_cooperative_matrix extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesKHR*           pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(unwrapped_phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesKHR*           pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCooperativeMatrixPropertiesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCooperativeMatrixPropertiesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCooperativeMatrixPropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, pProperties);
}


// ---- VK_KHR_line_rasterization extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetLineStippleKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLineStippleKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetLineStippleKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLineStippleKHR(commandBuffer, lineStippleFactor, lineStipplePattern);
}


// ---- VK_KHR_calibrated_timestamps extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCalibrateableTimeDomainsKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCalibrateableTimeDomainsKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCalibrateableTimeDomainsKHR(unwrapped_phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCalibrateableTimeDomainsKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCalibrateableTimeDomainsKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsKHR(phys_dev_term->phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL GetCalibratedTimestampsKHR(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoKHR*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetCalibratedTimestampsKHR: Invalid device "
                   "[VUID-vkGetCalibratedTimestampsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetCalibratedTimestampsKHR(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}


// ---- VK_KHR_maintenance6 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindDescriptorSets2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkBindDescriptorSetsInfo*             pBindDescriptorSetsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindDescriptorSets2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBindDescriptorSets2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindDescriptorSets2KHR(commandBuffer, pBindDescriptorSetsInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdPushConstants2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkPushConstantsInfo*                  pPushConstantsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPushConstants2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdPushConstants2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPushConstants2KHR(commandBuffer, pPushConstantsInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdPushDescriptorSet2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkPushDescriptorSetInfo*              pPushDescriptorSetInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPushDescriptorSet2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdPushDescriptorSet2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPushDescriptorSet2KHR(commandBuffer, pPushDescriptorSetInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdPushDescriptorSetWithTemplate2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo*  pPushDescriptorSetWithTemplateInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPushDescriptorSetWithTemplate2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdPushDescriptorSetWithTemplate2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPushDescriptorSetWithTemplate2KHR(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDescriptorBufferOffsets2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT*  pSetDescriptorBufferOffsetsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDescriptorBufferOffsets2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDescriptorBufferOffsets2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDescriptorBufferOffsets2EXT(commandBuffer, pSetDescriptorBufferOffsetsInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBindDescriptorBufferEmbeddedSamplers2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindDescriptorBufferEmbeddedSamplers2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindDescriptorBufferEmbeddedSamplers2EXT(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
}


// ---- VK_KHR_copy_memory_indirect extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryIndirectKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMemoryIndirectInfoKHR*          pCopyMemoryIndirectInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryIndirectKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryIndirectKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryIndirectKHR(commandBuffer, pCopyMemoryIndirectInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryToImageIndirectKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMemoryToImageIndirectInfoKHR*   pCopyMemoryToImageIndirectInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryToImageIndirectKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryToImageIndirectKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryToImageIndirectKHR(commandBuffer, pCopyMemoryToImageIndirectInfo);
}


// ---- VK_KHR_device_fault extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetDeviceFaultReportsKHR(
    VkDevice                                    device,
    uint64_t                                    timeout,
    uint32_t*                                   pFaultCounts,
    VkDeviceFaultInfoKHR*                       pFaultInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceFaultReportsKHR: Invalid device "
                   "[VUID-vkGetDeviceFaultReportsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceFaultReportsKHR(device, timeout, pFaultCounts, pFaultInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDeviceFaultDebugInfoKHR(
    VkDevice                                    device,
    VkDeviceFaultDebugInfoKHR*                  pDebugInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceFaultDebugInfoKHR: Invalid device "
                   "[VUID-vkGetDeviceFaultDebugInfoKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceFaultDebugInfoKHR(device, pDebugInfo);
}


// ---- VK_KHR_maintenance10 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdEndRendering2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingEndInfoKHR*                pRenderingEndInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndRendering2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdEndRendering2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndRendering2KHR(commandBuffer, pRenderingEndInfo);
}


// ---- VK_EXT_debug_marker extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL DebugMarkerSetObjectTagEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectTagInfoEXT*        pTagInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDebugMarkerSetObjectTagEXT: Invalid device "
                   "[VUID-vkDebugMarkerSetObjectTagEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugMarkerObjectTagInfoEXT local_tag_info;
    memcpy(&local_tag_info, pTagInfo, sizeof(VkDebugMarkerObjectTagInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pTagInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT) {
        struct loader_physical_device_tramp *phys_dev_tramp = (struct loader_physical_device_tramp *)(uintptr_t)pTagInfo->object;
        local_tag_info.object = (uint64_t)(uintptr_t)phys_dev_tramp->phys_dev;
    }
    if (pTagInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT) {
        struct loader_instance* instance = (struct loader_instance *)(uintptr_t)pTagInfo->object;
        local_tag_info.object = (uint64_t)(uintptr_t)instance->instance;
    }
    return disp->DebugMarkerSetObjectTagEXT(device, &local_tag_info);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_DebugMarkerSetObjectTagEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectTagInfoEXT*        pTagInfo) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "DebugMarkerSetObjectTagEXT: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugMarkerObjectTagInfoEXT local_tag_info;
    memcpy(&local_tag_info, pTagInfo, sizeof(VkDebugMarkerObjectTagInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pTagInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT) {
        struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)(uintptr_t)pTagInfo->object;
        local_tag_info.object = (uint64_t)(uintptr_t)phys_dev_term->phys_dev;
    // If this is a KHR_surface, and the ICD has created its own, we have to replace it with the proper one for the next call.
    } else if (pTagInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT) {
        if (NULL != dev && NULL != dev->loader_dispatch.core_dispatch.CreateSwapchainKHR) {
            VkSurfaceKHR surface = (VkSurfaceKHR)(uintptr_t)pTagInfo->object;
            if (wsi_unwrap_icd_surface(icd_term, &surface) == VK_SUCCESS) {
                local_tag_info.object = (uint64_t)surface;
            }
        }
    // If this is an instance we have to replace it with the proper one for the next call.
    } else if (pTagInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT) {
        local_tag_info.object = (uint64_t)(uintptr_t)icd_term->instance;
    }
    // Exit early if the driver does not support the function - this can happen as a layer or the loader itself supports
    // debug utils but the driver does not.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.DebugMarkerSetObjectTagEXT)
        return VK_SUCCESS;
    return dev->loader_dispatch.extension_terminator_dispatch.DebugMarkerSetObjectTagEXT(device, &local_tag_info);
}

VKAPI_ATTR VkResult VKAPI_CALL DebugMarkerSetObjectNameEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectNameInfoEXT*       pNameInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDebugMarkerSetObjectNameEXT: Invalid device "
                   "[VUID-vkDebugMarkerSetObjectNameEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugMarkerObjectNameInfoEXT local_name_info;
    memcpy(&local_name_info, pNameInfo, sizeof(VkDebugMarkerObjectNameInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pNameInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT) {
        struct loader_physical_device_tramp *phys_dev_tramp = (struct loader_physical_device_tramp *)(uintptr_t)pNameInfo->object;
        local_name_info.object = (uint64_t)(uintptr_t)phys_dev_tramp->phys_dev;
    }
    if (pNameInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT) {
        struct loader_instance* instance = (struct loader_instance *)(uintptr_t)pNameInfo->object;
        local_name_info.object = (uint64_t)(uintptr_t)instance->instance;
    }
    return disp->DebugMarkerSetObjectNameEXT(device, &local_name_info);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_DebugMarkerSetObjectNameEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectNameInfoEXT*       pNameInfo) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "DebugMarkerSetObjectNameEXT: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugMarkerObjectNameInfoEXT local_name_info;
    memcpy(&local_name_info, pNameInfo, sizeof(VkDebugMarkerObjectNameInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pNameInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT) {
        struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)(uintptr_t)pNameInfo->object;
        local_name_info.object = (uint64_t)(uintptr_t)phys_dev_term->phys_dev;
    // If this is a KHR_surface, and the ICD has created its own, we have to replace it with the proper one for the next call.
    } else if (pNameInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT) {
        if (NULL != dev && NULL != dev->loader_dispatch.core_dispatch.CreateSwapchainKHR) {
            VkSurfaceKHR surface = (VkSurfaceKHR)(uintptr_t)pNameInfo->object;
            if (wsi_unwrap_icd_surface(icd_term, &surface) == VK_SUCCESS) {
                local_name_info.object = (uint64_t)surface;
            }
        }
    // If this is an instance we have to replace it with the proper one for the next call.
    } else if (pNameInfo->objectType == VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT) {
        local_name_info.object = (uint64_t)(uintptr_t)icd_term->instance;
    }
    // Exit early if the driver does not support the function - this can happen as a layer or the loader itself supports
    // debug utils but the driver does not.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.DebugMarkerSetObjectNameEXT)
        return VK_SUCCESS;
    return dev->loader_dispatch.extension_terminator_dispatch.DebugMarkerSetObjectNameEXT(device, &local_name_info);
}

VKAPI_ATTR void VKAPI_CALL CmdDebugMarkerBeginEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugMarkerMarkerInfoEXT*           pMarkerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDebugMarkerBeginEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDebugMarkerBeginEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdDebugMarkerEndEXT(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDebugMarkerEndEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDebugMarkerEndEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDebugMarkerEndEXT(commandBuffer);
}

VKAPI_ATTR void VKAPI_CALL CmdDebugMarkerInsertEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugMarkerMarkerInfoEXT*           pMarkerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDebugMarkerInsertEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDebugMarkerInsertEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
}


// ---- VK_EXT_transform_feedback extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindTransformFeedbackBuffersEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindTransformFeedbackBuffersEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindTransformFeedbackBuffersEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindTransformFeedbackBuffersEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginTransformFeedbackEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    const VkBuffer*                             pCounterBuffers,
    const VkDeviceSize*                         pCounterBufferOffsets) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginTransformFeedbackEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginTransformFeedbackEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

VKAPI_ATTR void VKAPI_CALL CmdEndTransformFeedbackEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    const VkBuffer*                             pCounterBuffers,
    const VkDeviceSize*                         pCounterBufferOffsets) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndTransformFeedbackEXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndTransformFeedbackEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginQueryIndexedEXT(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags,
    uint32_t                                    index) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginQueryIndexedEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginQueryIndexedEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginQueryIndexedEXT(commandBuffer, queryPool, query, flags, index);
}

VKAPI_ATTR void VKAPI_CALL CmdEndQueryIndexedEXT(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    uint32_t                                    index) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndQueryIndexedEXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndQueryIndexedEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndQueryIndexedEXT(commandBuffer, queryPool, query, index);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndirectByteCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    VkBuffer                                    counterBuffer,
    VkDeviceSize                                counterBufferOffset,
    uint32_t                                    counterOffset,
    uint32_t                                    vertexStride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndirectByteCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndirectByteCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndirectByteCountEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
}


// ---- VK_NVX_binary_import extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateCuModuleNVX(
    VkDevice                                    device,
    const VkCuModuleCreateInfoNVX*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCuModuleNVX*                              pModule) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateCuModuleNVX: Invalid device "
                   "[VUID-vkCreateCuModuleNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateCuModuleNVX(device, pCreateInfo, pAllocator, pModule);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateCuFunctionNVX(
    VkDevice                                    device,
    const VkCuFunctionCreateInfoNVX*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCuFunctionNVX*                            pFunction) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateCuFunctionNVX: Invalid device "
                   "[VUID-vkCreateCuFunctionNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateCuFunctionNVX(device, pCreateInfo, pAllocator, pFunction);
}

VKAPI_ATTR void VKAPI_CALL DestroyCuModuleNVX(
    VkDevice                                    device,
    VkCuModuleNVX                               module,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyCuModuleNVX: Invalid device "
                   "[VUID-vkDestroyCuModuleNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyCuModuleNVX(device, module, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL DestroyCuFunctionNVX(
    VkDevice                                    device,
    VkCuFunctionNVX                             function,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyCuFunctionNVX: Invalid device "
                   "[VUID-vkDestroyCuFunctionNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyCuFunctionNVX(device, function, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL CmdCuLaunchKernelNVX(
    VkCommandBuffer                             commandBuffer,
    const VkCuLaunchInfoNVX*                    pLaunchInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCuLaunchKernelNVX: Invalid commandBuffer "
                   "[VUID-vkCmdCuLaunchKernelNVX-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCuLaunchKernelNVX(commandBuffer, pLaunchInfo);
}


// ---- VK_NVX_image_view_handle extension trampoline/terminators

VKAPI_ATTR uint32_t VKAPI_CALL GetImageViewHandleNVX(
    VkDevice                                    device,
    const VkImageViewHandleInfoNVX*             pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageViewHandleNVX: Invalid device "
                   "[VUID-vkGetImageViewHandleNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageViewHandleNVX(device, pInfo);
}

VKAPI_ATTR uint64_t VKAPI_CALL GetImageViewHandle64NVX(
    VkDevice                                    device,
    const VkImageViewHandleInfoNVX*             pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageViewHandle64NVX: Invalid device "
                   "[VUID-vkGetImageViewHandle64NVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageViewHandle64NVX(device, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetImageViewAddressNVX(
    VkDevice                                    device,
    VkImageView                                 imageView,
    VkImageViewAddressPropertiesNVX*            pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageViewAddressNVX: Invalid device "
                   "[VUID-vkGetImageViewAddressNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageViewAddressNVX(device, imageView, pProperties);
}

VKAPI_ATTR uint64_t VKAPI_CALL GetDeviceCombinedImageSamplerIndexNVX(
    VkDevice                                    device,
    uint64_t                                    imageViewIndex,
    uint64_t                                    samplerIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceCombinedImageSamplerIndexNVX: Invalid device "
                   "[VUID-vkGetDeviceCombinedImageSamplerIndexNVX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceCombinedImageSamplerIndexNVX(device, imageViewIndex, samplerIndex);
}


// ---- VK_AMD_draw_indirect_count extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDrawIndirectCountAMD(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndirectCountAMD: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndirectCountAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndexedIndirectCountAMD(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawIndexedIndirectCountAMD: Invalid commandBuffer "
                   "[VUID-vkCmdDrawIndexedIndirectCountAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawIndexedIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}


// ---- VK_AMD_shader_info extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetShaderInfoAMD(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    VkShaderStageFlagBits                       shaderStage,
    VkShaderInfoTypeAMD                         infoType,
    size_t*                                     pInfoSize,
    void*                                       pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetShaderInfoAMD: Invalid device "
                   "[VUID-vkGetShaderInfoAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetShaderInfoAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo);
}


// ---- VK_NV_external_memory_win32 extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryWin32HandleNV(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkExternalMemoryHandleTypeFlagsNV           handleType,
    HANDLE*                                     pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryWin32HandleNV: Invalid device "
                   "[VUID-vkGetMemoryWin32HandleNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryWin32HandleNV(device, memory, handleType, pHandle);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_EXT_conditional_rendering extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBeginConditionalRenderingEXT(
    VkCommandBuffer                             commandBuffer,
    const VkConditionalRenderingBeginInfoEXT*   pConditionalRenderingBegin) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginConditionalRenderingEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginConditionalRenderingEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginConditionalRenderingEXT(commandBuffer, pConditionalRenderingBegin);
}

VKAPI_ATTR void VKAPI_CALL CmdEndConditionalRenderingEXT(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndConditionalRenderingEXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndConditionalRenderingEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndConditionalRenderingEXT(commandBuffer);
}


// ---- VK_NV_clip_space_w_scaling extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetViewportWScalingNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewportWScalingNV*                 pViewportWScalings) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetViewportWScalingNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetViewportWScalingNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetViewportWScalingNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
}


// ---- VK_EXT_display_control extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL DisplayPowerControlEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayPowerInfoEXT*                pDisplayPowerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDisplayPowerControlEXT: Invalid device "
                   "[VUID-vkDisplayPowerControlEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->DisplayPowerControlEXT(device, display, pDisplayPowerInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterDeviceEventEXT(
    VkDevice                                    device,
    const VkDeviceEventInfoEXT*                 pDeviceEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkRegisterDeviceEventEXT: Invalid device "
                   "[VUID-vkRegisterDeviceEventEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->RegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterDisplayEventEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayEventInfoEXT*                pDisplayEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkRegisterDisplayEventEXT: Invalid device "
                   "[VUID-vkRegisterDisplayEventEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->RegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainCounterEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    uint64_t*                                   pCounterValue) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainCounterEXT: Invalid device "
                   "[VUID-vkGetSwapchainCounterEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainCounterEXT(device, swapchain, counter, pCounterValue);
}


// ---- VK_GOOGLE_display_timing extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetRefreshCycleDurationGOOGLE(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkRefreshCycleDurationGOOGLE*               pDisplayTimingProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRefreshCycleDurationGOOGLE: Invalid device "
                   "[VUID-vkGetRefreshCycleDurationGOOGLE-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetRefreshCycleDurationGOOGLE(device, swapchain, pDisplayTimingProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPastPresentationTimingGOOGLE(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint32_t*                                   pPresentationTimingCount,
    VkPastPresentationTimingGOOGLE*             pPresentationTimings) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPastPresentationTimingGOOGLE: Invalid device "
                   "[VUID-vkGetPastPresentationTimingGOOGLE-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPastPresentationTimingGOOGLE(device, swapchain, pPresentationTimingCount, pPresentationTimings);
}


// ---- VK_EXT_discard_rectangles extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    const VkRect2D*                             pDiscardRectangles) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDiscardRectangleEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDiscardRectangleEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    discardRectangleEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDiscardRectangleEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDiscardRectangleEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkDiscardRectangleModeEXT                   discardRectangleMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDiscardRectangleModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDiscardRectangleModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode);
}


// ---- VK_EXT_hdr_metadata extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL SetHdrMetadataEXT(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainKHR*                       pSwapchains,
    const VkHdrMetadataEXT*                     pMetadata) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetHdrMetadataEXT: Invalid device "
                   "[VUID-vkSetHdrMetadataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
}


// ---- VK_EXT_debug_utils extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetDebugUtilsObjectNameEXT: Invalid device "
                   "[VUID-vkSetDebugUtilsObjectNameEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugUtilsObjectNameInfoEXT local_name_info;
    memcpy(&local_name_info, pNameInfo, sizeof(VkDebugUtilsObjectNameInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pNameInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_tramp *phys_dev_tramp = (struct loader_physical_device_tramp *)(uintptr_t)pNameInfo->objectHandle;
        local_name_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_tramp->phys_dev;
    }
    if (pNameInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        struct loader_instance* instance = (struct loader_instance *)(uintptr_t)pNameInfo->objectHandle;
        local_name_info.objectHandle = (uint64_t)(uintptr_t)instance->instance;
    }
    if (disp->SetDebugUtilsObjectNameEXT != NULL) {
        return disp->SetDebugUtilsObjectNameEXT(device, &local_name_info);
    } else {
        return VK_SUCCESS;
    }
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "SetDebugUtilsObjectNameEXT: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugUtilsObjectNameInfoEXT local_name_info;
    memcpy(&local_name_info, pNameInfo, sizeof(VkDebugUtilsObjectNameInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pNameInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)(uintptr_t)pNameInfo->objectHandle;
        local_name_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_term->phys_dev;
    // If this is a KHR_surface, and the ICD has created its own, we have to replace it with the proper one for the next call.
    } else if (pNameInfo->objectType == VK_OBJECT_TYPE_SURFACE_KHR) {
        if (NULL != dev && NULL != dev->loader_dispatch.core_dispatch.CreateSwapchainKHR) {
            VkSurfaceKHR surface = (VkSurfaceKHR)(uintptr_t)pNameInfo->objectHandle;
            if (wsi_unwrap_icd_surface(icd_term, &surface) == VK_SUCCESS) {
                local_name_info.objectHandle = (uint64_t)surface;
            }
        }
    // If this is an instance we have to replace it with the proper one for the next call.
    } else if (pNameInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        local_name_info.objectHandle = (uint64_t)(uintptr_t)icd_term->instance;
    }
    // Exit early if the driver does not support the function - this can happen as a layer or the loader itself supports
    // debug utils but the driver does not.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectNameEXT)
        return VK_SUCCESS;
    return dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectNameEXT(device, &local_name_info);
}

VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetDebugUtilsObjectTagEXT: Invalid device "
                   "[VUID-vkSetDebugUtilsObjectTagEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugUtilsObjectTagInfoEXT local_tag_info;
    memcpy(&local_tag_info, pTagInfo, sizeof(VkDebugUtilsObjectTagInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pTagInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_tramp *phys_dev_tramp = (struct loader_physical_device_tramp *)(uintptr_t)pTagInfo->objectHandle;
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_tramp->phys_dev;
    }
    if (pTagInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        struct loader_instance* instance = (struct loader_instance *)(uintptr_t)pTagInfo->objectHandle;
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)instance->instance;
    }
    if (disp->SetDebugUtilsObjectTagEXT != NULL) {
        return disp->SetDebugUtilsObjectTagEXT(device, &local_tag_info);
    } else {
        return VK_SUCCESS;
    }
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_SetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "SetDebugUtilsObjectTagEXT: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugUtilsObjectTagInfoEXT local_tag_info;
    memcpy(&local_tag_info, pTagInfo, sizeof(VkDebugUtilsObjectTagInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pTagInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)(uintptr_t)pTagInfo->objectHandle;
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_term->phys_dev;
    // If this is a KHR_surface, and the ICD has created its own, we have to replace it with the proper one for the next call.
    } else if (pTagInfo->objectType == VK_OBJECT_TYPE_SURFACE_KHR) {
        if (NULL != dev && NULL != dev->loader_dispatch.core_dispatch.CreateSwapchainKHR) {
            VkSurfaceKHR surface = (VkSurfaceKHR)(uintptr_t)pTagInfo->objectHandle;
            if (wsi_unwrap_icd_surface(icd_term, &surface) == VK_SUCCESS) {
                local_tag_info.objectHandle = (uint64_t)surface;
            }
        }
    // If this is an instance we have to replace it with the proper one for the next call.
    } else if (pTagInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)icd_term->instance;
    }
    // Exit early if the driver does not support the function - this can happen as a layer or the loader itself supports
    // debug utils but the driver does not.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectTagEXT)
        return VK_SUCCESS;
    return dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectTagEXT(device, &local_tag_info);
}

VKAPI_ATTR void VKAPI_CALL QueueBeginDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueBeginDebugUtilsLabelEXT: Invalid queue "
                   "[VUID-vkQueueBeginDebugUtilsLabelEXT-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (disp->QueueBeginDebugUtilsLabelEXT != NULL) {
        disp->QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_QueueBeginDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(queue);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.QueueBeginDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL QueueEndDebugUtilsLabelEXT(
    VkQueue                                     queue) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueEndDebugUtilsLabelEXT: Invalid queue "
                   "[VUID-vkQueueEndDebugUtilsLabelEXT-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (disp->QueueEndDebugUtilsLabelEXT != NULL) {
        disp->QueueEndDebugUtilsLabelEXT(queue);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_QueueEndDebugUtilsLabelEXT(
    VkQueue                                     queue) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(queue);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.QueueEndDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.QueueEndDebugUtilsLabelEXT(queue);
}

VKAPI_ATTR void VKAPI_CALL QueueInsertDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueInsertDebugUtilsLabelEXT: Invalid queue "
                   "[VUID-vkQueueInsertDebugUtilsLabelEXT-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (disp->QueueInsertDebugUtilsLabelEXT != NULL) {
        disp->QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_QueueInsertDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(queue);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.QueueInsertDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginDebugUtilsLabelEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginDebugUtilsLabelEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (disp->CmdBeginDebugUtilsLabelEXT != NULL) {
        disp->CmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_CmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(commandBuffer);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.CmdBeginDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.CmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndDebugUtilsLabelEXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndDebugUtilsLabelEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (disp->CmdEndDebugUtilsLabelEXT != NULL) {
        disp->CmdEndDebugUtilsLabelEXT(commandBuffer);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_CmdEndDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(commandBuffer);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.CmdEndDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.CmdEndDebugUtilsLabelEXT(commandBuffer);
}

VKAPI_ATTR void VKAPI_CALL CmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdInsertDebugUtilsLabelEXT: Invalid commandBuffer "
                   "[VUID-vkCmdInsertDebugUtilsLabelEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (disp->CmdInsertDebugUtilsLabelEXT != NULL) {
        disp->CmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_CmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(commandBuffer);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.CmdInsertDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.CmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}


// ---- VK_ANDROID_external_memory_android_hardware_buffer extension trampoline/terminators

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    const struct AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetAndroidHardwareBufferPropertiesANDROID: Invalid device "
                   "[VUID-vkGetAndroidHardwareBufferPropertiesANDROID-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetAndroidHardwareBufferPropertiesANDROID(device, buffer, pProperties);
}

#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    struct AHardwareBuffer**                    pBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryAndroidHardwareBufferANDROID: Invalid device "
                   "[VUID-vkGetMemoryAndroidHardwareBufferANDROID-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryAndroidHardwareBufferANDROID(device, pInfo, pBuffer);
}

#endif // VK_USE_PLATFORM_ANDROID_KHR

// ---- VK_AMD_gpa_interface extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateGpaSessionAMD(
    VkDevice                                    device,
    const VkGpaSessionCreateInfoAMD*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkGpaSessionAMD*                            pGpaSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateGpaSessionAMD: Invalid device "
                   "[VUID-vkCreateGpaSessionAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateGpaSessionAMD(device, pCreateInfo, pAllocator, pGpaSession);
}

VKAPI_ATTR void VKAPI_CALL DestroyGpaSessionAMD(
    VkDevice                                    device,
    VkGpaSessionAMD                             gpaSession,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyGpaSessionAMD: Invalid device "
                   "[VUID-vkDestroyGpaSessionAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyGpaSessionAMD(device, gpaSession, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL SetGpaDeviceClockModeAMD(
    VkDevice                                    device,
    VkGpaDeviceClockModeInfoAMD*                pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetGpaDeviceClockModeAMD: Invalid device "
                   "[VUID-vkSetGpaDeviceClockModeAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SetGpaDeviceClockModeAMD(device, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetGpaDeviceClockInfoAMD(
    VkDevice                                    device,
    VkGpaDeviceGetClockInfoAMD*                 pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetGpaDeviceClockInfoAMD: Invalid device "
                   "[VUID-vkGetGpaDeviceClockInfoAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetGpaDeviceClockInfoAMD(device, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CmdBeginGpaSessionAMD(
    VkCommandBuffer                             commandBuffer,
    VkGpaSessionAMD                             gpaSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginGpaSessionAMD: Invalid commandBuffer "
                   "[VUID-vkCmdBeginGpaSessionAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CmdBeginGpaSessionAMD(commandBuffer, gpaSession);
}

VKAPI_ATTR VkResult VKAPI_CALL CmdEndGpaSessionAMD(
    VkCommandBuffer                             commandBuffer,
    VkGpaSessionAMD                             gpaSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndGpaSessionAMD: Invalid commandBuffer "
                   "[VUID-vkCmdEndGpaSessionAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CmdEndGpaSessionAMD(commandBuffer, gpaSession);
}

VKAPI_ATTR VkResult VKAPI_CALL CmdBeginGpaSampleAMD(
    VkCommandBuffer                             commandBuffer,
    VkGpaSessionAMD                             gpaSession,
    const VkGpaSampleBeginInfoAMD*              pGpaSampleBeginInfo,
    uint32_t*                                   pSampleID) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginGpaSampleAMD: Invalid commandBuffer "
                   "[VUID-vkCmdBeginGpaSampleAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CmdBeginGpaSampleAMD(commandBuffer, gpaSession, pGpaSampleBeginInfo, pSampleID);
}

VKAPI_ATTR void VKAPI_CALL CmdEndGpaSampleAMD(
    VkCommandBuffer                             commandBuffer,
    VkGpaSessionAMD                             gpaSession,
    uint32_t                                    sampleID) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndGpaSampleAMD: Invalid commandBuffer "
                   "[VUID-vkCmdEndGpaSampleAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndGpaSampleAMD(commandBuffer, gpaSession, sampleID);
}

VKAPI_ATTR VkResult VKAPI_CALL GetGpaSessionStatusAMD(
    VkDevice                                    device,
    VkGpaSessionAMD                             gpaSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetGpaSessionStatusAMD: Invalid device "
                   "[VUID-vkGetGpaSessionStatusAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetGpaSessionStatusAMD(device, gpaSession);
}

VKAPI_ATTR VkResult VKAPI_CALL GetGpaSessionResultsAMD(
    VkDevice                                    device,
    VkGpaSessionAMD                             gpaSession,
    uint32_t                                    sampleID,
    size_t*                                     pSizeInBytes,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetGpaSessionResultsAMD: Invalid device "
                   "[VUID-vkGetGpaSessionResultsAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetGpaSessionResultsAMD(device, gpaSession, sampleID, pSizeInBytes, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL ResetGpaSessionAMD(
    VkDevice                                    device,
    VkGpaSessionAMD                             gpaSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkResetGpaSessionAMD: Invalid device "
                   "[VUID-vkResetGpaSessionAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ResetGpaSessionAMD(device, gpaSession);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyGpaSessionResultsAMD(
    VkCommandBuffer                             commandBuffer,
    VkGpaSessionAMD                             gpaSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyGpaSessionResultsAMD: Invalid commandBuffer "
                   "[VUID-vkCmdCopyGpaSessionResultsAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyGpaSessionResultsAMD(commandBuffer, gpaSession);
}


// ---- VK_AMDX_shader_enqueue extension trampoline/terminators

#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR VkResult VKAPI_CALL CreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateExecutionGraphPipelinesAMDX: Invalid device "
                   "[VUID-vkCreateExecutionGraphPipelinesAMDX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateExecutionGraphPipelinesAMDX(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR VkResult VKAPI_CALL GetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetExecutionGraphPipelineScratchSizeAMDX: Invalid device "
                   "[VUID-vkGetExecutionGraphPipelineScratchSizeAMDX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetExecutionGraphPipelineScratchSizeAMDX(device, executionGraph, pSizeInfo);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR VkResult VKAPI_CALL GetExecutionGraphPipelineNodeIndexAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    const VkPipelineShaderStageNodeCreateInfoAMDX* pNodeInfo,
    uint32_t*                                   pNodeIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetExecutionGraphPipelineNodeIndexAMDX: Invalid device "
                   "[VUID-vkGetExecutionGraphPipelineNodeIndexAMDX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetExecutionGraphPipelineNodeIndexAMDX(device, executionGraph, pNodeInfo, pNodeIndex);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL CmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdInitializeGraphScratchMemoryAMDX: Invalid commandBuffer "
                   "[VUID-vkCmdInitializeGraphScratchMemoryAMDX-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdInitializeGraphScratchMemoryAMDX(commandBuffer, executionGraph, scratch, scratchSize);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL CmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    const VkDispatchGraphCountInfoAMDX*         pCountInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchGraphAMDX: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchGraphAMDX-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchGraphAMDX(commandBuffer, scratch, scratchSize, pCountInfo);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL CmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    const VkDispatchGraphCountInfoAMDX*         pCountInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchGraphIndirectAMDX: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchGraphIndirectAMDX-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchGraphIndirectAMDX(commandBuffer, scratch, scratchSize, pCountInfo);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL CmdDispatchGraphIndirectCountAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             countInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchGraphIndirectCountAMDX: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchGraphIndirectCountAMDX-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchGraphIndirectCountAMDX(commandBuffer, scratch, scratchSize, countInfo);
}

#endif // VK_ENABLE_BETA_EXTENSIONS

// ---- VK_EXT_descriptor_heap extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL WriteSamplerDescriptorsEXT(
    VkDevice                                    device,
    uint32_t                                    samplerCount,
    const VkSamplerCreateInfo*                  pSamplers,
    const VkHostAddressRangeEXT*                pDescriptors) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWriteSamplerDescriptorsEXT: Invalid device "
                   "[VUID-vkWriteSamplerDescriptorsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WriteSamplerDescriptorsEXT(device, samplerCount, pSamplers, pDescriptors);
}

VKAPI_ATTR VkResult VKAPI_CALL WriteResourceDescriptorsEXT(
    VkDevice                                    device,
    uint32_t                                    resourceCount,
    const VkResourceDescriptorInfoEXT*          pResources,
    const VkHostAddressRangeEXT*                pDescriptors) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWriteResourceDescriptorsEXT: Invalid device "
                   "[VUID-vkWriteResourceDescriptorsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WriteResourceDescriptorsEXT(device, resourceCount, pResources, pDescriptors);
}

VKAPI_ATTR void VKAPI_CALL CmdBindSamplerHeapEXT(
    VkCommandBuffer                             commandBuffer,
    const VkBindHeapInfoEXT*                    pBindInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindSamplerHeapEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindSamplerHeapEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindSamplerHeapEXT(commandBuffer, pBindInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBindResourceHeapEXT(
    VkCommandBuffer                             commandBuffer,
    const VkBindHeapInfoEXT*                    pBindInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindResourceHeapEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindResourceHeapEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindResourceHeapEXT(commandBuffer, pBindInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdPushDataEXT(
    VkCommandBuffer                             commandBuffer,
    const VkPushDataInfoEXT*                    pPushDataInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPushDataEXT: Invalid commandBuffer "
                   "[VUID-vkCmdPushDataEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPushDataEXT(commandBuffer, pPushDataInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetImageOpaqueCaptureDataEXT(
    VkDevice                                    device,
    uint32_t                                    imageCount,
    const VkImage*                              pImages,
    VkHostAddressRangeEXT*                      pDatas) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageOpaqueCaptureDataEXT: Invalid device "
                   "[VUID-vkGetImageOpaqueCaptureDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageOpaqueCaptureDataEXT(device, imageCount, pImages, pDatas);
}

VKAPI_ATTR VkDeviceSize VKAPI_CALL GetPhysicalDeviceDescriptorSizeEXT(
    VkPhysicalDevice                            physicalDevice,
    VkDescriptorType                            descriptorType) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceDescriptorSizeEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceDescriptorSizeEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceDescriptorSizeEXT(unwrapped_phys_dev, descriptorType);
}

VKAPI_ATTR VkDeviceSize VKAPI_CALL terminator_GetPhysicalDeviceDescriptorSizeEXT(
    VkPhysicalDevice                            physicalDevice,
    VkDescriptorType                            descriptorType) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceDescriptorSizeEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceDescriptorSizeEXT");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceDescriptorSizeEXT(phys_dev_term->phys_dev, descriptorType);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterCustomBorderColorEXT(
    VkDevice                                    device,
    const VkSamplerCustomBorderColorCreateInfoEXT* pBorderColor,
    VkBool32                                    requestIndex,
    uint32_t*                                   pIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkRegisterCustomBorderColorEXT: Invalid device "
                   "[VUID-vkRegisterCustomBorderColorEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->RegisterCustomBorderColorEXT(device, pBorderColor, requestIndex, pIndex);
}

VKAPI_ATTR void VKAPI_CALL UnregisterCustomBorderColorEXT(
    VkDevice                                    device,
    uint32_t                                    index) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUnregisterCustomBorderColorEXT: Invalid device "
                   "[VUID-vkUnregisterCustomBorderColorEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->UnregisterCustomBorderColorEXT(device, index);
}

VKAPI_ATTR VkResult VKAPI_CALL GetTensorOpaqueCaptureDataARM(
    VkDevice                                    device,
    uint32_t                                    tensorCount,
    const VkTensorARM*                          pTensors,
    VkHostAddressRangeEXT*                      pDatas) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetTensorOpaqueCaptureDataARM: Invalid device "
                   "[VUID-vkGetTensorOpaqueCaptureDataARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetTensorOpaqueCaptureDataARM(device, tensorCount, pTensors, pDatas);
}


// ---- VK_EXT_sample_locations extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetSampleLocationsEXT(
    VkCommandBuffer                             commandBuffer,
    const VkSampleLocationsInfoEXT*             pSampleLocationsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetSampleLocationsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetSampleLocationsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceMultisamplePropertiesEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceMultisamplePropertiesEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceMultisamplePropertiesEXT(unwrapped_phys_dev, samples, pMultisampleProperties);
}

VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceMultisamplePropertiesEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceMultisamplePropertiesEXT");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    icd_term->dispatch.GetPhysicalDeviceMultisamplePropertiesEXT(phys_dev_term->phys_dev, samples, pMultisampleProperties);
}


// ---- VK_EXT_image_drm_format_modifier extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetImageDrmFormatModifierPropertiesEXT(
    VkDevice                                    device,
    VkImage                                     image,
    VkImageDrmFormatModifierPropertiesEXT*      pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageDrmFormatModifierPropertiesEXT: Invalid device "
                   "[VUID-vkGetImageDrmFormatModifierPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageDrmFormatModifierPropertiesEXT(device, image, pProperties);
}


// ---- VK_EXT_validation_cache extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateValidationCacheEXT(
    VkDevice                                    device,
    const VkValidationCacheCreateInfoEXT*       pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkValidationCacheEXT*                       pValidationCache) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateValidationCacheEXT: Invalid device "
                   "[VUID-vkCreateValidationCacheEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache);
}

VKAPI_ATTR void VKAPI_CALL DestroyValidationCacheEXT(
    VkDevice                                    device,
    VkValidationCacheEXT                        validationCache,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyValidationCacheEXT: Invalid device "
                   "[VUID-vkDestroyValidationCacheEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyValidationCacheEXT(device, validationCache, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL MergeValidationCachesEXT(
    VkDevice                                    device,
    VkValidationCacheEXT                        dstCache,
    uint32_t                                    srcCacheCount,
    const VkValidationCacheEXT*                 pSrcCaches) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkMergeValidationCachesEXT: Invalid device "
                   "[VUID-vkMergeValidationCachesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->MergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches);
}

VKAPI_ATTR VkResult VKAPI_CALL GetValidationCacheDataEXT(
    VkDevice                                    device,
    VkValidationCacheEXT                        validationCache,
    size_t*                                     pDataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetValidationCacheDataEXT: Invalid device "
                   "[VUID-vkGetValidationCacheDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetValidationCacheDataEXT(device, validationCache, pDataSize, pData);
}


// ---- VK_NV_shading_rate_image extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindShadingRateImageNV(
    VkCommandBuffer                             commandBuffer,
    VkImageView                                 imageView,
    VkImageLayout                               imageLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindShadingRateImageNV: Invalid commandBuffer "
                   "[VUID-vkCmdBindShadingRateImageNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindShadingRateImageNV(commandBuffer, imageView, imageLayout);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewportShadingRatePaletteNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkShadingRatePaletteNV*               pShadingRatePalettes) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetViewportShadingRatePaletteNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetViewportShadingRatePaletteNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetViewportShadingRatePaletteNV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoarseSampleOrderNV(
    VkCommandBuffer                             commandBuffer,
    VkCoarseSampleOrderTypeNV                   sampleOrderType,
    uint32_t                                    customSampleOrderCount,
    const VkCoarseSampleOrderCustomNV*          pCustomSampleOrders) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoarseSampleOrderNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoarseSampleOrderNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoarseSampleOrderNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
}


// ---- VK_NV_ray_tracing extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateAccelerationStructureNV(
    VkDevice                                    device,
    const VkAccelerationStructureCreateInfoNV*  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkAccelerationStructureNV*                  pAccelerationStructure) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateAccelerationStructureNV: Invalid device "
                   "[VUID-vkCreateAccelerationStructureNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateAccelerationStructureNV(device, pCreateInfo, pAllocator, pAccelerationStructure);
}

VKAPI_ATTR void VKAPI_CALL DestroyAccelerationStructureNV(
    VkDevice                                    device,
    VkAccelerationStructureNV                   accelerationStructure,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyAccelerationStructureNV: Invalid device "
                   "[VUID-vkDestroyAccelerationStructureNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyAccelerationStructureNV(device, accelerationStructure, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL GetAccelerationStructureMemoryRequirementsNV(
    VkDevice                                    device,
    const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetAccelerationStructureMemoryRequirementsNV: Invalid device "
                   "[VUID-vkGetAccelerationStructureMemoryRequirementsNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetAccelerationStructureMemoryRequirementsNV(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL BindAccelerationStructureMemoryNV(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindAccelerationStructureMemoryNV: Invalid device "
                   "[VUID-vkBindAccelerationStructureMemoryNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindAccelerationStructureMemoryNV(device, bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdBuildAccelerationStructureNV(
    VkCommandBuffer                             commandBuffer,
    const VkAccelerationStructureInfoNV*        pInfo,
    VkBuffer                                    instanceData,
    VkDeviceSize                                instanceOffset,
    VkBool32                                    update,
    VkAccelerationStructureNV                   dst,
    VkAccelerationStructureNV                   src,
    VkBuffer                                    scratch,
    VkDeviceSize                                scratchOffset) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBuildAccelerationStructureNV: Invalid commandBuffer "
                   "[VUID-vkCmdBuildAccelerationStructureNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBuildAccelerationStructureNV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyAccelerationStructureNV(
    VkCommandBuffer                             commandBuffer,
    VkAccelerationStructureNV                   dst,
    VkAccelerationStructureNV                   src,
    VkCopyAccelerationStructureModeKHR          mode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyAccelerationStructureNV: Invalid commandBuffer "
                   "[VUID-vkCmdCopyAccelerationStructureNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyAccelerationStructureNV(commandBuffer, dst, src, mode);
}

VKAPI_ATTR void VKAPI_CALL CmdTraceRaysNV(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    raygenShaderBindingTableBuffer,
    VkDeviceSize                                raygenShaderBindingOffset,
    VkBuffer                                    missShaderBindingTableBuffer,
    VkDeviceSize                                missShaderBindingOffset,
    VkDeviceSize                                missShaderBindingStride,
    VkBuffer                                    hitShaderBindingTableBuffer,
    VkDeviceSize                                hitShaderBindingOffset,
    VkDeviceSize                                hitShaderBindingStride,
    VkBuffer                                    callableShaderBindingTableBuffer,
    VkDeviceSize                                callableShaderBindingOffset,
    VkDeviceSize                                callableShaderBindingStride,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdTraceRaysNV: Invalid commandBuffer "
                   "[VUID-vkCmdTraceRaysNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdTraceRaysNV(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateRayTracingPipelinesNV(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkRayTracingPipelineCreateInfoNV*     pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateRayTracingPipelinesNV: Invalid device "
                   "[VUID-vkCreateRayTracingPipelinesNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateRayTracingPipelinesNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}


// ---- VK_KHR_ray_tracing_pipeline extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetRayTracingShaderGroupHandlesKHR(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRayTracingShaderGroupHandlesKHR: Invalid device "
                   "[VUID-vkGetRayTracingShaderGroupHandlesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetRayTracingShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
}


// ---- VK_NV_ray_tracing extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetRayTracingShaderGroupHandlesNV(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRayTracingShaderGroupHandlesNV: Invalid device "
                   "[VUID-vkGetRayTracingShaderGroupHandlesNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetRayTracingShaderGroupHandlesNV(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL GetAccelerationStructureHandleNV(
    VkDevice                                    device,
    VkAccelerationStructureNV                   accelerationStructure,
    size_t                                      dataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetAccelerationStructureHandleNV: Invalid device "
                   "[VUID-vkGetAccelerationStructureHandleNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetAccelerationStructureHandleNV(device, accelerationStructure, dataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteAccelerationStructuresPropertiesNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureNV*            pAccelerationStructures,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteAccelerationStructuresPropertiesNV: Invalid commandBuffer "
                   "[VUID-vkCmdWriteAccelerationStructuresPropertiesNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteAccelerationStructuresPropertiesNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

VKAPI_ATTR VkResult VKAPI_CALL CompileDeferredNV(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    shader) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCompileDeferredNV: Invalid device "
                   "[VUID-vkCompileDeferredNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CompileDeferredNV(device, pipeline, shader);
}


// ---- VK_EXT_external_memory_host extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryHostPointerPropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    const void*                                 pHostPointer,
    VkMemoryHostPointerPropertiesEXT*           pMemoryHostPointerProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryHostPointerPropertiesEXT: Invalid device "
                   "[VUID-vkGetMemoryHostPointerPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}


// ---- VK_AMD_buffer_marker extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdWriteBufferMarkerAMD(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteBufferMarkerAMD: Invalid commandBuffer "
                   "[VUID-vkCmdWriteBufferMarkerAMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteBufferMarkerAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteBufferMarker2AMD(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteBufferMarker2AMD: Invalid commandBuffer "
                   "[VUID-vkCmdWriteBufferMarker2AMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteBufferMarker2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker);
}


// ---- VK_EXT_calibrated_timestamps extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCalibrateableTimeDomainsEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCalibrateableTimeDomainsEXT(unwrapped_phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCalibrateableTimeDomainsEXT");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsEXT(phys_dev_term->phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL GetCalibratedTimestampsEXT(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoKHR*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetCalibratedTimestampsEXT: Invalid device "
                   "[VUID-vkGetCalibratedTimestampsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}


// ---- VK_NV_mesh_shader extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    taskCount,
    uint32_t                                    firstTask) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksNV: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksNV(commandBuffer, taskCount, firstTask);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksIndirectNV(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksIndirectNV: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksIndirectNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksIndirectNV(commandBuffer, buffer, offset, drawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksIndirectCountNV(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksIndirectCountNV: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksIndirectCountNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksIndirectCountNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}


// ---- VK_NV_scissor_exclusive extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetExclusiveScissorEnableNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    const VkBool32*                             pExclusiveScissorEnables) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetExclusiveScissorEnableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetExclusiveScissorEnableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetExclusiveScissorEnableNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables);
}

VKAPI_ATTR void VKAPI_CALL CmdSetExclusiveScissorNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    const VkRect2D*                             pExclusiveScissors) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetExclusiveScissorNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetExclusiveScissorNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetExclusiveScissorNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
}


// ---- VK_NV_device_diagnostic_checkpoints extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetCheckpointNV(
    VkCommandBuffer                             commandBuffer,
    const void*                                 pCheckpointMarker) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCheckpointNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCheckpointNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCheckpointNV(commandBuffer, pCheckpointMarker);
}

VKAPI_ATTR void VKAPI_CALL GetQueueCheckpointDataNV(
    VkQueue                                     queue,
    uint32_t*                                   pCheckpointDataCount,
    VkCheckpointDataNV*                         pCheckpointData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetQueueCheckpointDataNV: Invalid queue "
                   "[VUID-vkGetQueueCheckpointDataNV-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetQueueCheckpointDataNV(queue, pCheckpointDataCount, pCheckpointData);
}

VKAPI_ATTR void VKAPI_CALL GetQueueCheckpointData2NV(
    VkQueue                                     queue,
    uint32_t*                                   pCheckpointDataCount,
    VkCheckpointData2NV*                        pCheckpointData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetQueueCheckpointData2NV: Invalid queue "
                   "[VUID-vkGetQueueCheckpointData2NV-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetQueueCheckpointData2NV(queue, pCheckpointDataCount, pCheckpointData);
}


// ---- VK_EXT_present_timing extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL SetSwapchainPresentTimingQueueSizeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint32_t                                    size) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetSwapchainPresentTimingQueueSizeEXT: Invalid device "
                   "[VUID-vkSetSwapchainPresentTimingQueueSizeEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SetSwapchainPresentTimingQueueSizeEXT(device, swapchain, size);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainTimingPropertiesEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSwapchainTimingPropertiesEXT*             pSwapchainTimingProperties,
    uint64_t*                                   pSwapchainTimingPropertiesCounter) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainTimingPropertiesEXT: Invalid device "
                   "[VUID-vkGetSwapchainTimingPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainTimingPropertiesEXT(device, swapchain, pSwapchainTimingProperties, pSwapchainTimingPropertiesCounter);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainTimeDomainPropertiesEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSwapchainTimeDomainPropertiesEXT*         pSwapchainTimeDomainProperties,
    uint64_t*                                   pTimeDomainsCounter) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainTimeDomainPropertiesEXT: Invalid device "
                   "[VUID-vkGetSwapchainTimeDomainPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainTimeDomainPropertiesEXT(device, swapchain, pSwapchainTimeDomainProperties, pTimeDomainsCounter);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPastPresentationTimingEXT(
    VkDevice                                    device,
    const VkPastPresentationTimingInfoEXT*      pPastPresentationTimingInfo,
    VkPastPresentationTimingPropertiesEXT*      pPastPresentationTimingProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPastPresentationTimingEXT: Invalid device "
                   "[VUID-vkGetPastPresentationTimingEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPastPresentationTimingEXT(device, pPastPresentationTimingInfo, pPastPresentationTimingProperties);
}


// ---- VK_INTEL_performance_query extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL InitializePerformanceApiINTEL(
    VkDevice                                    device,
    const VkInitializePerformanceApiInfoINTEL*  pInitializeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkInitializePerformanceApiINTEL: Invalid device "
                   "[VUID-vkInitializePerformanceApiINTEL-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->InitializePerformanceApiINTEL(device, pInitializeInfo);
}

VKAPI_ATTR void VKAPI_CALL UninitializePerformanceApiINTEL(
    VkDevice                                    device) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUninitializePerformanceApiINTEL: Invalid device "
                   "[VUID-vkUninitializePerformanceApiINTEL-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->UninitializePerformanceApiINTEL(device);
}

VKAPI_ATTR VkResult VKAPI_CALL CmdSetPerformanceMarkerINTEL(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceMarkerInfoINTEL*         pMarkerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPerformanceMarkerINTEL: Invalid commandBuffer "
                   "[VUID-vkCmdSetPerformanceMarkerINTEL-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CmdSetPerformanceMarkerINTEL(commandBuffer, pMarkerInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CmdSetPerformanceStreamMarkerINTEL(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceStreamMarkerInfoINTEL*   pMarkerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPerformanceStreamMarkerINTEL: Invalid commandBuffer "
                   "[VUID-vkCmdSetPerformanceStreamMarkerINTEL-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CmdSetPerformanceStreamMarkerINTEL(commandBuffer, pMarkerInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CmdSetPerformanceOverrideINTEL(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceOverrideInfoINTEL*       pOverrideInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPerformanceOverrideINTEL: Invalid commandBuffer "
                   "[VUID-vkCmdSetPerformanceOverrideINTEL-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CmdSetPerformanceOverrideINTEL(commandBuffer, pOverrideInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL AcquirePerformanceConfigurationINTEL(
    VkDevice                                    device,
    const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo,
    VkPerformanceConfigurationINTEL*            pConfiguration) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquirePerformanceConfigurationINTEL: Invalid device "
                   "[VUID-vkAcquirePerformanceConfigurationINTEL-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->AcquirePerformanceConfigurationINTEL(device, pAcquireInfo, pConfiguration);
}

VKAPI_ATTR VkResult VKAPI_CALL ReleasePerformanceConfigurationINTEL(
    VkDevice                                    device,
    VkPerformanceConfigurationINTEL             configuration) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleasePerformanceConfigurationINTEL: Invalid device "
                   "[VUID-vkReleasePerformanceConfigurationINTEL-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ReleasePerformanceConfigurationINTEL(device, configuration);
}

VKAPI_ATTR VkResult VKAPI_CALL QueueSetPerformanceConfigurationINTEL(
    VkQueue                                     queue,
    VkPerformanceConfigurationINTEL             configuration) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueSetPerformanceConfigurationINTEL: Invalid queue "
                   "[VUID-vkQueueSetPerformanceConfigurationINTEL-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->QueueSetPerformanceConfigurationINTEL(queue, configuration);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPerformanceParameterINTEL(
    VkDevice                                    device,
    VkPerformanceParameterTypeINTEL             parameter,
    VkPerformanceValueINTEL*                    pValue) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPerformanceParameterINTEL: Invalid device "
                   "[VUID-vkGetPerformanceParameterINTEL-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPerformanceParameterINTEL(device, parameter, pValue);
}


// ---- VK_AMD_display_native_hdr extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL SetLocalDimmingAMD(
    VkDevice                                    device,
    VkSwapchainKHR                              swapChain,
    VkBool32                                    localDimmingEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetLocalDimmingAMD: Invalid device "
                   "[VUID-vkSetLocalDimmingAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetLocalDimmingAMD(device, swapChain, localDimmingEnable);
}


// ---- VK_EXT_buffer_device_address extension trampoline/terminators

VKAPI_ATTR VkDeviceAddress VKAPI_CALL GetBufferDeviceAddressEXT(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetBufferDeviceAddressEXT: Invalid device "
                   "[VUID-vkGetBufferDeviceAddressEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetBufferDeviceAddressEXT(device, pInfo);
}


// ---- VK_NV_cooperative_matrix extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCooperativeMatrixPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesNV*            pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCooperativeMatrixPropertiesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCooperativeMatrixPropertiesNV(unwrapped_phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCooperativeMatrixPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesNV*            pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCooperativeMatrixPropertiesNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCooperativeMatrixPropertiesNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCooperativeMatrixPropertiesNV(phys_dev_term->phys_dev, pPropertyCount, pProperties);
}


// ---- VK_NV_coverage_reduction_mode extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pCombinationCount,
    VkFramebufferMixedSamplesCombinationNV*     pCombinations) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(unwrapped_phys_dev, pCombinationCount, pCombinations);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pCombinationCount,
    VkFramebufferMixedSamplesCombinationNV*     pCombinations) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(phys_dev_term->phys_dev, pCombinationCount, pCombinations);
}


// ---- VK_EXT_full_screen_exclusive extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL AcquireFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireFullScreenExclusiveModeEXT: Invalid device "
                   "[VUID-vkAcquireFullScreenExclusiveModeEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->AcquireFullScreenExclusiveModeEXT(device, swapchain);
}

#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL ReleaseFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseFullScreenExclusiveModeEXT: Invalid device "
                   "[VUID-vkReleaseFullScreenExclusiveModeEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ReleaseFullScreenExclusiveModeEXT(device, swapchain);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_EXT_line_rasterization extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetLineStippleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLineStippleEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLineStippleEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
}


// ---- VK_EXT_host_query_reset extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL ResetQueryPoolEXT(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkResetQueryPoolEXT: Invalid device "
                   "[VUID-vkResetQueryPoolEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->ResetQueryPoolEXT(device, queryPool, firstQuery, queryCount);
}


// ---- VK_EXT_extended_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetCullModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkCullModeFlags                             cullMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCullModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetCullModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCullModeEXT(commandBuffer, cullMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetFrontFaceEXT(
    VkCommandBuffer                             commandBuffer,
    VkFrontFace                                 frontFace) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetFrontFaceEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetFrontFaceEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetFrontFaceEXT(commandBuffer, frontFace);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveTopologyEXT(
    VkCommandBuffer                             commandBuffer,
    VkPrimitiveTopology                         primitiveTopology) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPrimitiveTopologyEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPrimitiveTopologyEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewportWithCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetViewportWithCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetViewportWithCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
}

VKAPI_ATTR void VKAPI_CALL CmdSetScissorWithCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetScissorWithCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetScissorWithCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors);
}

VKAPI_ATTR void VKAPI_CALL CmdBindVertexBuffers2EXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes,
    const VkDeviceSize*                         pStrides) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindVertexBuffers2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindVertexBuffers2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthTestEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthTestEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthWriteEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthWriteEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthWriteEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthWriteEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthCompareOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkCompareOp                                 depthCompareOp) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthCompareOpEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthCompareOpEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBoundsTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBoundsTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthBoundsTestEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthBoundsTestEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetStencilTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stencilTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetStencilTestEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetStencilTestEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetStencilOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetStencilOpEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetStencilOpEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}


// ---- VK_EXT_host_image_copy extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CopyMemoryToImageEXT(
    VkDevice                                    device,
    const VkCopyMemoryToImageInfo*              pCopyMemoryToImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyMemoryToImageEXT: Invalid device "
                   "[VUID-vkCopyMemoryToImageEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyMemoryToImageEXT(device, pCopyMemoryToImageInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyImageToMemoryEXT(
    VkDevice                                    device,
    const VkCopyImageToMemoryInfo*              pCopyImageToMemoryInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyImageToMemoryEXT: Invalid device "
                   "[VUID-vkCopyImageToMemoryEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyImageToMemoryEXT(device, pCopyImageToMemoryInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyImageToImageEXT(
    VkDevice                                    device,
    const VkCopyImageToImageInfo*               pCopyImageToImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyImageToImageEXT: Invalid device "
                   "[VUID-vkCopyImageToImageEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyImageToImageEXT(device, pCopyImageToImageInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL TransitionImageLayoutEXT(
    VkDevice                                    device,
    uint32_t                                    transitionCount,
    const VkHostImageLayoutTransitionInfo*      pTransitions) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkTransitionImageLayoutEXT: Invalid device "
                   "[VUID-vkTransitionImageLayoutEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->TransitionImageLayoutEXT(device, transitionCount, pTransitions);
}

VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout2EXT(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource2*                  pSubresource,
    VkSubresourceLayout2*                       pLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageSubresourceLayout2EXT: Invalid device "
                   "[VUID-vkGetImageSubresourceLayout2EXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetImageSubresourceLayout2EXT(device, image, pSubresource, pLayout);
}


// ---- VK_EXT_swapchain_maintenance1 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ReleaseSwapchainImagesEXT(
    VkDevice                                    device,
    const VkReleaseSwapchainImagesInfoKHR*      pReleaseInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseSwapchainImagesEXT: Invalid device "
                   "[VUID-vkReleaseSwapchainImagesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ReleaseSwapchainImagesEXT(device, pReleaseInfo);
}


// ---- VK_NV_device_generated_commands extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetGeneratedCommandsMemoryRequirementsNV(
    VkDevice                                    device,
    const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetGeneratedCommandsMemoryRequirementsNV: Invalid device "
                   "[VUID-vkGetGeneratedCommandsMemoryRequirementsNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetGeneratedCommandsMemoryRequirementsNV(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL CmdPreprocessGeneratedCommandsNV(
    VkCommandBuffer                             commandBuffer,
    const VkGeneratedCommandsInfoNV*            pGeneratedCommandsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPreprocessGeneratedCommandsNV: Invalid commandBuffer "
                   "[VUID-vkCmdPreprocessGeneratedCommandsNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPreprocessGeneratedCommandsNV(commandBuffer, pGeneratedCommandsInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdExecuteGeneratedCommandsNV(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    isPreprocessed,
    const VkGeneratedCommandsInfoNV*            pGeneratedCommandsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdExecuteGeneratedCommandsNV: Invalid commandBuffer "
                   "[VUID-vkCmdExecuteGeneratedCommandsNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdExecuteGeneratedCommandsNV(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBindPipelineShaderGroupNV(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline,
    uint32_t                                    groupIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindPipelineShaderGroupNV: Invalid commandBuffer "
                   "[VUID-vkCmdBindPipelineShaderGroupNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindPipelineShaderGroupNV(commandBuffer, pipelineBindPoint, pipeline, groupIndex);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateIndirectCommandsLayoutNV(
    VkDevice                                    device,
    const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkIndirectCommandsLayoutNV*                 pIndirectCommandsLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateIndirectCommandsLayoutNV: Invalid device "
                   "[VUID-vkCreateIndirectCommandsLayoutNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateIndirectCommandsLayoutNV(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
}

VKAPI_ATTR void VKAPI_CALL DestroyIndirectCommandsLayoutNV(
    VkDevice                                    device,
    VkIndirectCommandsLayoutNV                  indirectCommandsLayout,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyIndirectCommandsLayoutNV: Invalid device "
                   "[VUID-vkDestroyIndirectCommandsLayoutNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyIndirectCommandsLayoutNV(device, indirectCommandsLayout, pAllocator);
}


// ---- VK_EXT_depth_bias_control extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBias2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkDepthBiasInfoEXT*                   pDepthBiasInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthBias2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthBias2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthBias2EXT(commandBuffer, pDepthBiasInfo);
}


// ---- VK_EXT_acquire_drm_display extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL AcquireDrmDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    int32_t                                     drmFd,
    VkDisplayKHR                                display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireDrmDisplayEXT: Invalid physicalDevice "
                   "[VUID-vkAcquireDrmDisplayEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->AcquireDrmDisplayEXT(unwrapped_phys_dev, drmFd, display);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_AcquireDrmDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    int32_t                                     drmFd,
    VkDisplayKHR                                display) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.AcquireDrmDisplayEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support AcquireDrmDisplayEXT");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    return icd_term->dispatch.AcquireDrmDisplayEXT(phys_dev_term->phys_dev, drmFd, display);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDrmDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    int32_t                                     drmFd,
    uint32_t                                    connectorId,
    VkDisplayKHR*                               display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDrmDisplayEXT: Invalid physicalDevice "
                   "[VUID-vkGetDrmDisplayEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetDrmDisplayEXT(unwrapped_phys_dev, drmFd, connectorId, display);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDrmDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    int32_t                                     drmFd,
    uint32_t                                    connectorId,
    VkDisplayKHR*                               display) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetDrmDisplayEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetDrmDisplayEXT");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    return icd_term->dispatch.GetDrmDisplayEXT(phys_dev_term->phys_dev, drmFd, connectorId, display);
}


// ---- VK_EXT_private_data extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreatePrivateDataSlotEXT(
    VkDevice                                    device,
    const VkPrivateDataSlotCreateInfo*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPrivateDataSlot*                          pPrivateDataSlot) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreatePrivateDataSlotEXT: Invalid device "
                   "[VUID-vkCreatePrivateDataSlotEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreatePrivateDataSlotEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

VKAPI_ATTR void VKAPI_CALL DestroyPrivateDataSlotEXT(
    VkDevice                                    device,
    VkPrivateDataSlot                           privateDataSlot,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyPrivateDataSlotEXT: Invalid device "
                   "[VUID-vkDestroyPrivateDataSlotEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyPrivateDataSlotEXT(device, privateDataSlot, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL SetPrivateDataEXT(
    VkDevice                                    device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    VkPrivateDataSlot                           privateDataSlot,
    uint64_t                                    data) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetPrivateDataEXT: Invalid device "
                   "[VUID-vkSetPrivateDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, data);
}

VKAPI_ATTR void VKAPI_CALL GetPrivateDataEXT(
    VkDevice                                    device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    VkPrivateDataSlot                           privateDataSlot,
    uint64_t*                                   pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPrivateDataEXT: Invalid device "
                   "[VUID-vkGetPrivateDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, pData);
}


// ---- VK_QCOM_queue_perf_hint extension trampoline/terminators

VKAPI_ATTR VkResult                   VKAPI_CALL QueueSetPerfHintQCOM(
    VkQueue                                     queue,
    const VkPerfHintInfoQCOM*                   pPerfHintInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueSetPerfHintQCOM: Invalid queue "
                   "[VUID-vkQueueSetPerfHintQCOM-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->QueueSetPerfHintQCOM(queue, pPerfHintInfo);
}


// ---- VK_NV_cuda_kernel_launch extension trampoline/terminators

#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR VkResult VKAPI_CALL CreateCudaModuleNV(
    VkDevice                                    device,
    const VkCudaModuleCreateInfoNV*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateCudaModuleNV: Invalid device "
                   "[VUID-vkCreateCudaModuleNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateCudaModuleNV(device, pCreateInfo, pAllocator, pModule);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR VkResult VKAPI_CALL GetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    void*                                       pCacheData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetCudaModuleCacheNV: Invalid device "
                   "[VUID-vkGetCudaModuleCacheNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetCudaModuleCacheNV(device, module, pCacheSize, pCacheData);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR VkResult VKAPI_CALL CreateCudaFunctionNV(
    VkDevice                                    device,
    const VkCudaFunctionCreateInfoNV*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateCudaFunctionNV: Invalid device "
                   "[VUID-vkCreateCudaFunctionNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateCudaFunctionNV(device, pCreateInfo, pAllocator, pFunction);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL DestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyCudaModuleNV: Invalid device "
                   "[VUID-vkDestroyCudaModuleNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyCudaModuleNV(device, module, pAllocator);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL DestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyCudaFunctionNV: Invalid device "
                   "[VUID-vkDestroyCudaFunctionNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyCudaFunctionNV(device, function, pAllocator);
}

#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
VKAPI_ATTR void VKAPI_CALL CmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    const VkCudaLaunchInfoNV*                   pLaunchInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCudaLaunchKernelNV: Invalid commandBuffer "
                   "[VUID-vkCmdCudaLaunchKernelNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCudaLaunchKernelNV(commandBuffer, pLaunchInfo);
}

#endif // VK_ENABLE_BETA_EXTENSIONS

// ---- VK_QCOM_tile_shading extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDispatchTileQCOM(
    VkCommandBuffer                             commandBuffer,
    const VkDispatchTileInfoQCOM*               pDispatchTileInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchTileQCOM: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchTileQCOM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchTileQCOM(commandBuffer, pDispatchTileInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginPerTileExecutionQCOM(
    VkCommandBuffer                             commandBuffer,
    const VkPerTileBeginInfoQCOM*               pPerTileBeginInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginPerTileExecutionQCOM: Invalid commandBuffer "
                   "[VUID-vkCmdBeginPerTileExecutionQCOM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginPerTileExecutionQCOM(commandBuffer, pPerTileBeginInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndPerTileExecutionQCOM(
    VkCommandBuffer                             commandBuffer,
    const VkPerTileEndInfoQCOM*                 pPerTileEndInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndPerTileExecutionQCOM: Invalid commandBuffer "
                   "[VUID-vkCmdEndPerTileExecutionQCOM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndPerTileExecutionQCOM(commandBuffer, pPerTileEndInfo);
}


// ---- VK_NV_low_latency extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL SetLatencySleepModeLegacyNV(
    VkDevice                                    device,
    VkBool32                                    lowLatencyMode,
    VkBool32                                    lowLatencyBoost,
    uint32_t                                    minimumIntervalUs) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetLatencySleepModeLegacyNV: Invalid device "
                   "[VUID-vkSetLatencySleepModeLegacyNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetLatencySleepModeLegacyNV(device, lowLatencyMode, lowLatencyBoost, minimumIntervalUs);
}

VKAPI_ATTR void VKAPI_CALL LatencySleepLegacyNV(
    VkDevice                                    device,
    VkSemaphore                                 signalSemaphore,
    uint64_t                                    value) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkLatencySleepLegacyNV: Invalid device "
                   "[VUID-vkLatencySleepLegacyNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->LatencySleepLegacyNV(device, signalSemaphore, value);
}

VKAPI_ATTR void VKAPI_CALL SetLatencyMarkerLegacyNV(
    VkDevice                                    device,
    uint64_t                                    frameID,
    uint32_t                                    marker) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetLatencyMarkerLegacyNV: Invalid device "
                   "[VUID-vkSetLatencyMarkerLegacyNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetLatencyMarkerLegacyNV(device, frameID, marker);
}

VKAPI_ATTR void VKAPI_CALL GetLatencyTimingsLegacyNV(
    VkDevice                                    device,
    void*                                       pTimings) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetLatencyTimingsLegacyNV: Invalid device "
                   "[VUID-vkGetLatencyTimingsLegacyNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetLatencyTimingsLegacyNV(device, pTimings);
}

VKAPI_ATTR void VKAPI_CALL QueueNotifyOutOfBandLegacyNV(
    VkQueue                                     queue,
    uint32_t                                    queueType) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueNotifyOutOfBandLegacyNV: Invalid queue "
                   "[VUID-vkQueueNotifyOutOfBandLegacyNV-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->QueueNotifyOutOfBandLegacyNV(queue, queueType);
}

VKAPI_ATTR void VKAPI_CALL GetSleepStatusLegacyNV(
    VkDevice                                    device,
    VkBool32*                                   pLowLatencyMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSleepStatusLegacyNV: Invalid device "
                   "[VUID-vkGetSleepStatusLegacyNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetSleepStatusLegacyNV(device, pLowLatencyMode);
}

VKAPI_ATTR void VKAPI_CALL ShutdownLatencyDeviceLegacyNV(
    VkDevice                                    device) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkShutdownLatencyDeviceLegacyNV: Invalid device "
                   "[VUID-vkShutdownLatencyDeviceLegacyNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->ShutdownLatencyDeviceLegacyNV(device);
}


// ---- VK_EXT_metal_objects extension trampoline/terminators

#if defined(VK_USE_PLATFORM_METAL_EXT)
VKAPI_ATTR void VKAPI_CALL ExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkExportMetalObjectsEXT: Invalid device "
                   "[VUID-vkExportMetalObjectsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->ExportMetalObjectsEXT(device, pMetalObjectsInfo);
}

#endif // VK_USE_PLATFORM_METAL_EXT

// ---- VK_EXT_descriptor_buffer extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetDescriptorSetLayoutSizeEXT(
    VkDevice                                    device,
    VkDescriptorSetLayout                       layout,
    VkDeviceSize*                               pLayoutSizeInBytes) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDescriptorSetLayoutSizeEXT: Invalid device "
                   "[VUID-vkGetDescriptorSetLayoutSizeEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDescriptorSetLayoutSizeEXT(device, layout, pLayoutSizeInBytes);
}

VKAPI_ATTR void VKAPI_CALL GetDescriptorSetLayoutBindingOffsetEXT(
    VkDevice                                    device,
    VkDescriptorSetLayout                       layout,
    uint32_t                                    binding,
    VkDeviceSize*                               pOffset) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDescriptorSetLayoutBindingOffsetEXT: Invalid device "
                   "[VUID-vkGetDescriptorSetLayoutBindingOffsetEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDescriptorSetLayoutBindingOffsetEXT(device, layout, binding, pOffset);
}

VKAPI_ATTR void VKAPI_CALL GetDescriptorEXT(
    VkDevice                                    device,
    const VkDescriptorGetInfoEXT*               pDescriptorInfo,
    size_t                                      dataSize,
    void*                                       pDescriptor) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDescriptorEXT: Invalid device "
                   "[VUID-vkGetDescriptorEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDescriptorEXT(device, pDescriptorInfo, dataSize, pDescriptor);
}

VKAPI_ATTR void VKAPI_CALL CmdBindDescriptorBuffersEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    bufferCount,
    const VkDescriptorBufferBindingInfoEXT*     pBindingInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindDescriptorBuffersEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindDescriptorBuffersEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindDescriptorBuffersEXT(commandBuffer, bufferCount, pBindingInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDescriptorBufferOffsetsEXT(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    firstSet,
    uint32_t                                    setCount,
    const uint32_t*                             pBufferIndices,
    const VkDeviceSize*                         pOffsets) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDescriptorBufferOffsetsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDescriptorBufferOffsetsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDescriptorBufferOffsetsEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
}

VKAPI_ATTR void VKAPI_CALL CmdBindDescriptorBufferEmbeddedSamplersEXT(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    set) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindDescriptorBufferEmbeddedSamplersEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindDescriptorBufferEmbeddedSamplersEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindDescriptorBufferEmbeddedSamplersEXT(commandBuffer, pipelineBindPoint, layout, set);
}

VKAPI_ATTR VkResult VKAPI_CALL GetBufferOpaqueCaptureDescriptorDataEXT(
    VkDevice                                    device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetBufferOpaqueCaptureDescriptorDataEXT: Invalid device "
                   "[VUID-vkGetBufferOpaqueCaptureDescriptorDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetBufferOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL GetImageOpaqueCaptureDescriptorDataEXT(
    VkDevice                                    device,
    const VkImageCaptureDescriptorDataInfoEXT*  pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageOpaqueCaptureDescriptorDataEXT: Invalid device "
                   "[VUID-vkGetImageOpaqueCaptureDescriptorDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL GetImageViewOpaqueCaptureDescriptorDataEXT(
    VkDevice                                    device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageViewOpaqueCaptureDescriptorDataEXT: Invalid device "
                   "[VUID-vkGetImageViewOpaqueCaptureDescriptorDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageViewOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSamplerOpaqueCaptureDescriptorDataEXT(
    VkDevice                                    device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSamplerOpaqueCaptureDescriptorDataEXT: Invalid device "
                   "[VUID-vkGetSamplerOpaqueCaptureDescriptorDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSamplerOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
    VkDevice                                    device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT: Invalid device "
                   "[VUID-vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}


// ---- VK_NV_fragment_shading_rate_enums extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetFragmentShadingRateEnumNV(
    VkCommandBuffer                             commandBuffer,
    VkFragmentShadingRateNV                     shadingRate,
    const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetFragmentShadingRateEnumNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetFragmentShadingRateEnumNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetFragmentShadingRateEnumNV(commandBuffer, shadingRate, combinerOps);
}


// ---- VK_EXT_device_fault extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetDeviceFaultInfoEXT(
    VkDevice                                    device,
    VkDeviceFaultCountsEXT*                     pFaultCounts,
    VkDeviceFaultInfoEXT*                       pFaultInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceFaultInfoEXT: Invalid device "
                   "[VUID-vkGetDeviceFaultInfoEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceFaultInfoEXT(device, pFaultCounts, pFaultInfo);
}


// ---- VK_NV_acquire_winrt_display extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL AcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireWinrtDisplayNV: Invalid physicalDevice "
                   "[VUID-vkAcquireWinrtDisplayNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->AcquireWinrtDisplayNV(unwrapped_phys_dev, display);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_AcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.AcquireWinrtDisplayNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support AcquireWinrtDisplayNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.AcquireWinrtDisplayNV(phys_dev_term->phys_dev, display);
}

#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetWinrtDisplayNV: Invalid physicalDevice "
                   "[VUID-vkGetWinrtDisplayNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetWinrtDisplayNV(unwrapped_phys_dev, deviceRelativeId, pDisplay);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetWinrtDisplayNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetWinrtDisplayNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetWinrtDisplayNV(phys_dev_term->phys_dev, deviceRelativeId, pDisplay);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_EXT_vertex_input_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetVertexInputEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT*  pVertexBindingDescriptions,
    uint32_t                                    vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetVertexInputEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetVertexInputEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}


// ---- VK_FUCHSIA_external_memory extension trampoline/terminators

#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    const VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryZirconHandleFUCHSIA: Invalid device "
                   "[VUID-vkGetMemoryZirconHandleFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryZirconHandleFUCHSIA(device, pGetZirconHandleInfo, pZirconHandle);
}

#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryZirconHandlePropertiesFUCHSIA(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    zx_handle_t                                 zirconHandle,
    VkMemoryZirconHandlePropertiesFUCHSIA*      pMemoryZirconHandleProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryZirconHandlePropertiesFUCHSIA: Invalid device "
                   "[VUID-vkGetMemoryZirconHandlePropertiesFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryZirconHandlePropertiesFUCHSIA(device, handleType, zirconHandle, pMemoryZirconHandleProperties);
}

#endif // VK_USE_PLATFORM_FUCHSIA

// ---- VK_FUCHSIA_external_semaphore extension trampoline/terminators

#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportSemaphoreZirconHandleFUCHSIA: Invalid device "
                   "[VUID-vkImportSemaphoreZirconHandleFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportSemaphoreZirconHandleFUCHSIA(device, pImportSemaphoreZirconHandleInfo);
}

#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSemaphoreZirconHandleFUCHSIA: Invalid device "
                   "[VUID-vkGetSemaphoreZirconHandleFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSemaphoreZirconHandleFUCHSIA(device, pGetZirconHandleInfo, pZirconHandle);
}

#endif // VK_USE_PLATFORM_FUCHSIA

// ---- VK_FUCHSIA_buffer_collection extension trampoline/terminators

#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL CreateBufferCollectionFUCHSIA(
    VkDevice                                    device,
    const VkBufferCollectionCreateInfoFUCHSIA*  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBufferCollectionFUCHSIA*                  pCollection) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateBufferCollectionFUCHSIA: Invalid device "
                   "[VUID-vkCreateBufferCollectionFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateBufferCollectionFUCHSIA(device, pCreateInfo, pAllocator, pCollection);
}

#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL SetBufferCollectionImageConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    const VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetBufferCollectionImageConstraintsFUCHSIA: Invalid device "
                   "[VUID-vkSetBufferCollectionImageConstraintsFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SetBufferCollectionImageConstraintsFUCHSIA(device, collection, pImageConstraintsInfo);
}

#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL SetBufferCollectionBufferConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    const VkBufferConstraintsInfoFUCHSIA*       pBufferConstraintsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetBufferCollectionBufferConstraintsFUCHSIA: Invalid device "
                   "[VUID-vkSetBufferCollectionBufferConstraintsFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SetBufferCollectionBufferConstraintsFUCHSIA(device, collection, pBufferConstraintsInfo);
}

#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR void VKAPI_CALL DestroyBufferCollectionFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyBufferCollectionFUCHSIA: Invalid device "
                   "[VUID-vkDestroyBufferCollectionFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyBufferCollectionFUCHSIA(device, collection, pAllocator);
}

#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
VKAPI_ATTR VkResult VKAPI_CALL GetBufferCollectionPropertiesFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    VkBufferCollectionPropertiesFUCHSIA*        pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetBufferCollectionPropertiesFUCHSIA: Invalid device "
                   "[VUID-vkGetBufferCollectionPropertiesFUCHSIA-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetBufferCollectionPropertiesFUCHSIA(device, collection, pProperties);
}

#endif // VK_USE_PLATFORM_FUCHSIA

// ---- VK_HUAWEI_subpass_shading extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(
    VkDevice                                    device,
    VkRenderPass                                renderpass,
    VkExtent2D*                                 pMaxWorkgroupSize) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI: Invalid device "
                   "[VUID-vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(device, renderpass, pMaxWorkgroupSize);
}

VKAPI_ATTR void VKAPI_CALL CmdSubpassShadingHUAWEI(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSubpassShadingHUAWEI: Invalid commandBuffer "
                   "[VUID-vkCmdSubpassShadingHUAWEI-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSubpassShadingHUAWEI(commandBuffer);
}


// ---- VK_HUAWEI_invocation_mask extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindInvocationMaskHUAWEI(
    VkCommandBuffer                             commandBuffer,
    VkImageView                                 imageView,
    VkImageLayout                               imageLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindInvocationMaskHUAWEI: Invalid commandBuffer "
                   "[VUID-vkCmdBindInvocationMaskHUAWEI-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindInvocationMaskHUAWEI(commandBuffer, imageView, imageLayout);
}


// ---- VK_NV_external_memory_rdma extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryRemoteAddressNV(
    VkDevice                                    device,
    const VkMemoryGetRemoteAddressInfoNV*       pMemoryGetRemoteAddressInfo,
    VkRemoteAddressNV*                          pAddress) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryRemoteAddressNV: Invalid device "
                   "[VUID-vkGetMemoryRemoteAddressNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryRemoteAddressNV(device, pMemoryGetRemoteAddressInfo, pAddress);
}


// ---- VK_EXT_pipeline_properties extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPipelinePropertiesEXT(
    VkDevice                                    device,
    const VkPipelineInfoKHR*                    pPipelineInfo,
    VkBaseOutStructure*                         pPipelineProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelinePropertiesEXT: Invalid device "
                   "[VUID-vkGetPipelinePropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelinePropertiesEXT(device, pPipelineInfo, pPipelineProperties);
}


// ---- VK_EXT_extended_dynamic_state2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetPatchControlPointsEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    patchControlPoints) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPatchControlPointsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPatchControlPointsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRasterizerDiscardEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    rasterizerDiscardEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRasterizerDiscardEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetRasterizerDiscardEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBiasEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBiasEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthBiasEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthBiasEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetLogicOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkLogicOp                                   logicOp) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLogicOpEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLogicOpEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLogicOpEXT(commandBuffer, logicOp);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveRestartEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    primitiveRestartEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPrimitiveRestartEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPrimitiveRestartEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
}


// ---- VK_EXT_color_write_enable extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetColorWriteEnableEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    attachmentCount,
    const VkBool32*                             pColorWriteEnables) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetColorWriteEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetColorWriteEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables);
}


// ---- VK_EXT_multi_draw extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDrawMultiEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    drawCount,
    const VkMultiDrawInfoEXT*                   pVertexInfo,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMultiEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMultiEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMultiEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMultiIndexedEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    drawCount,
    const VkMultiDrawIndexedInfoEXT*            pIndexInfo,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    uint32_t                                    stride,
    const int32_t*                              pVertexOffset) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMultiIndexedEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMultiIndexedEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMultiIndexedEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
}


// ---- VK_EXT_opacity_micromap extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateMicromapEXT(
    VkDevice                                    device,
    const VkMicromapCreateInfoEXT*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkMicromapEXT*                              pMicromap) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateMicromapEXT: Invalid device "
                   "[VUID-vkCreateMicromapEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateMicromapEXT(device, pCreateInfo, pAllocator, pMicromap);
}

VKAPI_ATTR void VKAPI_CALL DestroyMicromapEXT(
    VkDevice                                    device,
    VkMicromapEXT                               micromap,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyMicromapEXT: Invalid device "
                   "[VUID-vkDestroyMicromapEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyMicromapEXT(device, micromap, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL CmdBuildMicromapsEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkMicromapBuildInfoEXT*               pInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBuildMicromapsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBuildMicromapsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBuildMicromapsEXT(commandBuffer, infoCount, pInfos);
}

VKAPI_ATTR VkResult VKAPI_CALL BuildMicromapsEXT(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    uint32_t                                    infoCount,
    const VkMicromapBuildInfoEXT*               pInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBuildMicromapsEXT: Invalid device "
                   "[VUID-vkBuildMicromapsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BuildMicromapsEXT(device, deferredOperation, infoCount, pInfos);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyMicromapEXT(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMicromapInfoEXT*                pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyMicromapEXT: Invalid device "
                   "[VUID-vkCopyMicromapEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyMicromapEXT(device, deferredOperation, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyMicromapToMemoryEXT(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT*        pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyMicromapToMemoryEXT: Invalid device "
                   "[VUID-vkCopyMicromapToMemoryEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyMicromapToMemoryEXT(device, deferredOperation, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyMemoryToMicromapEXT(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT*        pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyMemoryToMicromapEXT: Invalid device "
                   "[VUID-vkCopyMemoryToMicromapEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyMemoryToMicromapEXT(device, deferredOperation, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL WriteMicromapsPropertiesEXT(
    VkDevice                                    device,
    uint32_t                                    micromapCount,
    const VkMicromapEXT*                        pMicromaps,
    VkQueryType                                 queryType,
    size_t                                      dataSize,
    void*                                       pData,
    size_t                                      stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWriteMicromapsPropertiesEXT: Invalid device "
                   "[VUID-vkWriteMicromapsPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WriteMicromapsPropertiesEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMicromapEXT(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMicromapInfoEXT*                pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMicromapEXT: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMicromapEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMicromapEXT(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMicromapToMemoryEXT(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT*        pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMicromapToMemoryEXT: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMicromapToMemoryEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMicromapToMemoryEXT(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryToMicromapEXT(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT*        pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryToMicromapEXT: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryToMicromapEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryToMicromapEXT(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteMicromapsPropertiesEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    micromapCount,
    const VkMicromapEXT*                        pMicromaps,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteMicromapsPropertiesEXT: Invalid commandBuffer "
                   "[VUID-vkCmdWriteMicromapsPropertiesEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteMicromapsPropertiesEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceMicromapCompatibilityEXT(
    VkDevice                                    device,
    const VkMicromapVersionInfoEXT*             pVersionInfo,
    VkAccelerationStructureCompatibilityKHR*    pCompatibility) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceMicromapCompatibilityEXT: Invalid device "
                   "[VUID-vkGetDeviceMicromapCompatibilityEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceMicromapCompatibilityEXT(device, pVersionInfo, pCompatibility);
}

VKAPI_ATTR void VKAPI_CALL GetMicromapBuildSizesEXT(
    VkDevice                                    device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    const VkMicromapBuildInfoEXT*               pBuildInfo,
    VkMicromapBuildSizesInfoEXT*                pSizeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMicromapBuildSizesEXT: Invalid device "
                   "[VUID-vkGetMicromapBuildSizesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetMicromapBuildSizesEXT(device, buildType, pBuildInfo, pSizeInfo);
}


// ---- VK_HUAWEI_cluster_culling_shader extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDrawClusterHUAWEI(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawClusterHUAWEI: Invalid commandBuffer "
                   "[VUID-vkCmdDrawClusterHUAWEI-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawClusterHUAWEI(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawClusterIndirectHUAWEI(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawClusterIndirectHUAWEI: Invalid commandBuffer "
                   "[VUID-vkCmdDrawClusterIndirectHUAWEI-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawClusterIndirectHUAWEI(commandBuffer, buffer, offset);
}


// ---- VK_EXT_pageable_device_local_memory extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL SetDeviceMemoryPriorityEXT(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    float                                       priority) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetDeviceMemoryPriorityEXT: Invalid device "
                   "[VUID-vkSetDeviceMemoryPriorityEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetDeviceMemoryPriorityEXT(device, memory, priority);
}


// ---- VK_ARM_scheduling_controls extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetDispatchParametersARM(
    VkCommandBuffer                             commandBuffer,
    const VkDispatchParametersARM*              pDispatchParameters) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDispatchParametersARM: Invalid commandBuffer "
                   "[VUID-vkCmdSetDispatchParametersARM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDispatchParametersARM(commandBuffer, pDispatchParameters);
}


// ---- VK_VALVE_descriptor_set_host_mapping extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetDescriptorSetLayoutHostMappingInfoVALVE(
    VkDevice                                    device,
    const VkDescriptorSetBindingReferenceVALVE* pBindingReference,
    VkDescriptorSetLayoutHostMappingInfoVALVE*  pHostMapping) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDescriptorSetLayoutHostMappingInfoVALVE: Invalid device "
                   "[VUID-vkGetDescriptorSetLayoutHostMappingInfoVALVE-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDescriptorSetLayoutHostMappingInfoVALVE(device, pBindingReference, pHostMapping);
}

VKAPI_ATTR void VKAPI_CALL GetDescriptorSetHostMappingVALVE(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    void**                                      ppData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDescriptorSetHostMappingVALVE: Invalid device "
                   "[VUID-vkGetDescriptorSetHostMappingVALVE-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDescriptorSetHostMappingVALVE(device, descriptorSet, ppData);
}


// ---- VK_NV_copy_memory_indirect extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryIndirectNV(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             copyBufferAddress,
    uint32_t                                    copyCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryIndirectNV: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryIndirectNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryToImageIndirectNV(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             copyBufferAddress,
    uint32_t                                    copyCount,
    uint32_t                                    stride,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    const VkImageSubresourceLayers*             pImageSubresources) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryToImageIndirectNV: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryToImageIndirectNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryToImageIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources);
}


// ---- VK_NV_memory_decompression extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDecompressMemoryNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    decompressRegionCount,
    const VkDecompressMemoryRegionNV*           pDecompressMemoryRegions) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDecompressMemoryNV: Invalid commandBuffer "
                   "[VUID-vkCmdDecompressMemoryNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDecompressMemoryNV(commandBuffer, decompressRegionCount, pDecompressMemoryRegions);
}

VKAPI_ATTR void VKAPI_CALL CmdDecompressMemoryIndirectCountNV(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             indirectCommandsAddress,
    VkDeviceAddress                             indirectCommandsCountAddress,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDecompressMemoryIndirectCountNV: Invalid commandBuffer "
                   "[VUID-vkCmdDecompressMemoryIndirectCountNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDecompressMemoryIndirectCountNV(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride);
}


// ---- VK_NV_device_generated_commands_compute extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetPipelineIndirectMemoryRequirementsNV(
    VkDevice                                    device,
    const VkComputePipelineCreateInfo*          pCreateInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineIndirectMemoryRequirementsNV: Invalid device "
                   "[VUID-vkGetPipelineIndirectMemoryRequirementsNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetPipelineIndirectMemoryRequirementsNV(device, pCreateInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL CmdUpdatePipelineIndirectBufferNV(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdUpdatePipelineIndirectBufferNV: Invalid commandBuffer "
                   "[VUID-vkCmdUpdatePipelineIndirectBufferNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdUpdatePipelineIndirectBufferNV(commandBuffer, pipelineBindPoint, pipeline);
}

VKAPI_ATTR VkDeviceAddress VKAPI_CALL GetPipelineIndirectDeviceAddressNV(
    VkDevice                                    device,
    const VkPipelineIndirectDeviceAddressInfoNV* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPipelineIndirectDeviceAddressNV: Invalid device "
                   "[VUID-vkGetPipelineIndirectDeviceAddressNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetPipelineIndirectDeviceAddressNV(device, pInfo);
}


// ---- VK_OHOS_external_memory extension trampoline/terminators

#if defined(VK_USE_PLATFORM_OHOS)
VKAPI_ATTR VkResult VKAPI_CALL GetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    const struct OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetNativeBufferPropertiesOHOS: Invalid device "
                   "[VUID-vkGetNativeBufferPropertiesOHOS-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetNativeBufferPropertiesOHOS(device, buffer, pProperties);
}

#endif // VK_USE_PLATFORM_OHOS
#if defined(VK_USE_PLATFORM_OHOS)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    const VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    struct OH_NativeBuffer**                    pBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryNativeBufferOHOS: Invalid device "
                   "[VUID-vkGetMemoryNativeBufferOHOS-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryNativeBufferOHOS(device, pInfo, pBuffer);
}

#endif // VK_USE_PLATFORM_OHOS

// ---- VK_EXT_extended_dynamic_state3 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetDepthClampEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthClampEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthClampEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthClampEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthClampEnableEXT(commandBuffer, depthClampEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPolygonModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkPolygonMode                               polygonMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPolygonModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPolygonModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPolygonModeEXT(commandBuffer, polygonMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRasterizationSamplesEXT(
    VkCommandBuffer                             commandBuffer,
    VkSampleCountFlagBits                       rasterizationSamples) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRasterizationSamplesEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetRasterizationSamplesEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRasterizationSamplesEXT(commandBuffer, rasterizationSamples);
}

VKAPI_ATTR void VKAPI_CALL CmdSetSampleMaskEXT(
    VkCommandBuffer                             commandBuffer,
    VkSampleCountFlagBits                       samples,
    const VkSampleMask*                         pSampleMask) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetSampleMaskEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetSampleMaskEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetSampleMaskEXT(commandBuffer, samples, pSampleMask);
}

VKAPI_ATTR void VKAPI_CALL CmdSetAlphaToCoverageEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    alphaToCoverageEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetAlphaToCoverageEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetAlphaToCoverageEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetAlphaToCoverageEnableEXT(commandBuffer, alphaToCoverageEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetAlphaToOneEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    alphaToOneEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetAlphaToOneEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetAlphaToOneEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetAlphaToOneEnableEXT(commandBuffer, alphaToOneEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetLogicOpEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    logicOpEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLogicOpEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLogicOpEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLogicOpEnableEXT(commandBuffer, logicOpEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetColorBlendEnableEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkBool32*                             pColorBlendEnables) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetColorBlendEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetColorBlendEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetColorBlendEnableEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
}

VKAPI_ATTR void VKAPI_CALL CmdSetColorBlendEquationEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkColorBlendEquationEXT*              pColorBlendEquations) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetColorBlendEquationEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetColorBlendEquationEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
}

VKAPI_ATTR void VKAPI_CALL CmdSetColorWriteMaskEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkColorComponentFlags*                pColorWriteMasks) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetColorWriteMaskEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetColorWriteMaskEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetColorWriteMaskEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
}

VKAPI_ATTR void VKAPI_CALL CmdSetTessellationDomainOriginEXT(
    VkCommandBuffer                             commandBuffer,
    VkTessellationDomainOrigin                  domainOrigin) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetTessellationDomainOriginEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetTessellationDomainOriginEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetTessellationDomainOriginEXT(commandBuffer, domainOrigin);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRasterizationStreamEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    rasterizationStream) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRasterizationStreamEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetRasterizationStreamEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRasterizationStreamEXT(commandBuffer, rasterizationStream);
}

VKAPI_ATTR void VKAPI_CALL CmdSetConservativeRasterizationModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkConservativeRasterizationModeEXT          conservativeRasterizationMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetConservativeRasterizationModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetConservativeRasterizationModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetConservativeRasterizationModeEXT(commandBuffer, conservativeRasterizationMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetExtraPrimitiveOverestimationSizeEXT(
    VkCommandBuffer                             commandBuffer,
    float                                       extraPrimitiveOverestimationSize) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetExtraPrimitiveOverestimationSizeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetExtraPrimitiveOverestimationSizeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, extraPrimitiveOverestimationSize);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthClipEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthClipEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthClipEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthClipEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthClipEnableEXT(commandBuffer, depthClipEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetSampleLocationsEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    sampleLocationsEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetSampleLocationsEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetSampleLocationsEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetSampleLocationsEnableEXT(commandBuffer, sampleLocationsEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetColorBlendAdvancedEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkColorBlendAdvancedEXT*              pColorBlendAdvanced) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetColorBlendAdvancedEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetColorBlendAdvancedEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetColorBlendAdvancedEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
}

VKAPI_ATTR void VKAPI_CALL CmdSetProvokingVertexModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkProvokingVertexModeEXT                    provokingVertexMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetProvokingVertexModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetProvokingVertexModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetProvokingVertexModeEXT(commandBuffer, provokingVertexMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetLineRasterizationModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkLineRasterizationModeEXT                  lineRasterizationMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLineRasterizationModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLineRasterizationModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLineRasterizationModeEXT(commandBuffer, lineRasterizationMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetLineStippleEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stippledLineEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLineStippleEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLineStippleEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLineStippleEnableEXT(commandBuffer, stippledLineEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthClipNegativeOneToOneEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    negativeOneToOne) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthClipNegativeOneToOneEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthClipNegativeOneToOneEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthClipNegativeOneToOneEXT(commandBuffer, negativeOneToOne);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewportWScalingEnableNV(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    viewportWScalingEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetViewportWScalingEnableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetViewportWScalingEnableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetViewportWScalingEnableNV(commandBuffer, viewportWScalingEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewportSwizzleNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewportSwizzleNV*                  pViewportSwizzles) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetViewportSwizzleNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetViewportSwizzleNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetViewportSwizzleNV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoverageToColorEnableNV(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    coverageToColorEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoverageToColorEnableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoverageToColorEnableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoverageToColorEnableNV(commandBuffer, coverageToColorEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoverageToColorLocationNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    coverageToColorLocation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoverageToColorLocationNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoverageToColorLocationNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoverageToColorLocationNV(commandBuffer, coverageToColorLocation);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoverageModulationModeNV(
    VkCommandBuffer                             commandBuffer,
    VkCoverageModulationModeNV                  coverageModulationMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoverageModulationModeNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoverageModulationModeNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoverageModulationModeNV(commandBuffer, coverageModulationMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoverageModulationTableEnableNV(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    coverageModulationTableEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoverageModulationTableEnableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoverageModulationTableEnableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoverageModulationTableEnableNV(commandBuffer, coverageModulationTableEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoverageModulationTableNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    coverageModulationTableCount,
    const float*                                pCoverageModulationTable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoverageModulationTableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoverageModulationTableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoverageModulationTableNV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetShadingRateImageEnableNV(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    shadingRateImageEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetShadingRateImageEnableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetShadingRateImageEnableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetShadingRateImageEnableNV(commandBuffer, shadingRateImageEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRepresentativeFragmentTestEnableNV(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    representativeFragmentTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRepresentativeFragmentTestEnableNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetRepresentativeFragmentTestEnableNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRepresentativeFragmentTestEnableNV(commandBuffer, representativeFragmentTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetCoverageReductionModeNV(
    VkCommandBuffer                             commandBuffer,
    VkCoverageReductionModeNV                   coverageReductionMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCoverageReductionModeNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetCoverageReductionModeNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCoverageReductionModeNV(commandBuffer, coverageReductionMode);
}


// ---- VK_ARM_tensors extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateTensorARM(
    VkDevice                                    device,
    const VkTensorCreateInfoARM*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkTensorARM*                                pTensor) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateTensorARM: Invalid device "
                   "[VUID-vkCreateTensorARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateTensorARM(device, pCreateInfo, pAllocator, pTensor);
}

VKAPI_ATTR void VKAPI_CALL DestroyTensorARM(
    VkDevice                                    device,
    VkTensorARM                                 tensor,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyTensorARM: Invalid device "
                   "[VUID-vkDestroyTensorARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyTensorARM(device, tensor, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateTensorViewARM(
    VkDevice                                    device,
    const VkTensorViewCreateInfoARM*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkTensorViewARM*                            pView) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateTensorViewARM: Invalid device "
                   "[VUID-vkCreateTensorViewARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateTensorViewARM(device, pCreateInfo, pAllocator, pView);
}

VKAPI_ATTR void VKAPI_CALL DestroyTensorViewARM(
    VkDevice                                    device,
    VkTensorViewARM                             tensorView,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyTensorViewARM: Invalid device "
                   "[VUID-vkDestroyTensorViewARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyTensorViewARM(device, tensorView, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL GetTensorMemoryRequirementsARM(
    VkDevice                                    device,
    const VkTensorMemoryRequirementsInfoARM*    pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetTensorMemoryRequirementsARM: Invalid device "
                   "[VUID-vkGetTensorMemoryRequirementsARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetTensorMemoryRequirementsARM(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL BindTensorMemoryARM(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindTensorMemoryInfoARM*            pBindInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindTensorMemoryARM: Invalid device "
                   "[VUID-vkBindTensorMemoryARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindTensorMemoryARM(device, bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceTensorMemoryRequirementsARM(
    VkDevice                                    device,
    const VkDeviceTensorMemoryRequirementsARM*  pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceTensorMemoryRequirementsARM: Invalid device "
                   "[VUID-vkGetDeviceTensorMemoryRequirementsARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceTensorMemoryRequirementsARM(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyTensorARM(
    VkCommandBuffer                             commandBuffer,
    const VkCopyTensorInfoARM*                  pCopyTensorInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyTensorARM: Invalid commandBuffer "
                   "[VUID-vkCmdCopyTensorARM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyTensorARM(commandBuffer, pCopyTensorInfo);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceExternalTensorPropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalTensorInfoARM* pExternalTensorInfo,
    VkExternalTensorPropertiesARM*              pExternalTensorProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceExternalTensorPropertiesARM: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceExternalTensorPropertiesARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceExternalTensorPropertiesARM(unwrapped_phys_dev, pExternalTensorInfo, pExternalTensorProperties);
}

VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceExternalTensorPropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalTensorInfoARM* pExternalTensorInfo,
    VkExternalTensorPropertiesARM*              pExternalTensorProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceExternalTensorPropertiesARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceExternalTensorPropertiesARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    icd_term->dispatch.GetPhysicalDeviceExternalTensorPropertiesARM(phys_dev_term->phys_dev, pExternalTensorInfo, pExternalTensorProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetTensorOpaqueCaptureDescriptorDataARM(
    VkDevice                                    device,
    const VkTensorCaptureDescriptorDataInfoARM* pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetTensorOpaqueCaptureDescriptorDataARM: Invalid device "
                   "[VUID-vkGetTensorOpaqueCaptureDescriptorDataARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetTensorOpaqueCaptureDescriptorDataARM(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL GetTensorViewOpaqueCaptureDescriptorDataARM(
    VkDevice                                    device,
    const VkTensorViewCaptureDescriptorDataInfoARM* pInfo,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetTensorViewOpaqueCaptureDescriptorDataARM: Invalid device "
                   "[VUID-vkGetTensorViewOpaqueCaptureDescriptorDataARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetTensorViewOpaqueCaptureDescriptorDataARM(device, pInfo, pData);
}


// ---- VK_EXT_shader_module_identifier extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetShaderModuleIdentifierEXT(
    VkDevice                                    device,
    VkShaderModule                              shaderModule,
    VkShaderModuleIdentifierEXT*                pIdentifier) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetShaderModuleIdentifierEXT: Invalid device "
                   "[VUID-vkGetShaderModuleIdentifierEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetShaderModuleIdentifierEXT(device, shaderModule, pIdentifier);
}

VKAPI_ATTR void VKAPI_CALL GetShaderModuleCreateInfoIdentifierEXT(
    VkDevice                                    device,
    const VkShaderModuleCreateInfo*             pCreateInfo,
    VkShaderModuleIdentifierEXT*                pIdentifier) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetShaderModuleCreateInfoIdentifierEXT: Invalid device "
                   "[VUID-vkGetShaderModuleCreateInfoIdentifierEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetShaderModuleCreateInfoIdentifierEXT(device, pCreateInfo, pIdentifier);
}


// ---- VK_NV_optical_flow extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceOpticalFlowImageFormatsNV(
    VkPhysicalDevice                            physicalDevice,
    const VkOpticalFlowImageFormatInfoNV*       pOpticalFlowImageFormatInfo,
    uint32_t*                                   pFormatCount,
    VkOpticalFlowImageFormatPropertiesNV*       pImageFormatProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceOpticalFlowImageFormatsNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceOpticalFlowImageFormatsNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceOpticalFlowImageFormatsNV(unwrapped_phys_dev, pOpticalFlowImageFormatInfo, pFormatCount, pImageFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceOpticalFlowImageFormatsNV(
    VkPhysicalDevice                            physicalDevice,
    const VkOpticalFlowImageFormatInfoNV*       pOpticalFlowImageFormatInfo,
    uint32_t*                                   pFormatCount,
    VkOpticalFlowImageFormatPropertiesNV*       pImageFormatProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceOpticalFlowImageFormatsNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceOpticalFlowImageFormatsNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceOpticalFlowImageFormatsNV(phys_dev_term->phys_dev, pOpticalFlowImageFormatInfo, pFormatCount, pImageFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateOpticalFlowSessionNV(
    VkDevice                                    device,
    const VkOpticalFlowSessionCreateInfoNV*     pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkOpticalFlowSessionNV*                     pSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateOpticalFlowSessionNV: Invalid device "
                   "[VUID-vkCreateOpticalFlowSessionNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateOpticalFlowSessionNV(device, pCreateInfo, pAllocator, pSession);
}

VKAPI_ATTR void VKAPI_CALL DestroyOpticalFlowSessionNV(
    VkDevice                                    device,
    VkOpticalFlowSessionNV                      session,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyOpticalFlowSessionNV: Invalid device "
                   "[VUID-vkDestroyOpticalFlowSessionNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyOpticalFlowSessionNV(device, session, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL BindOpticalFlowSessionImageNV(
    VkDevice                                    device,
    VkOpticalFlowSessionNV                      session,
    VkOpticalFlowSessionBindingPointNV          bindingPoint,
    VkImageView                                 view,
    VkImageLayout                               layout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindOpticalFlowSessionImageNV: Invalid device "
                   "[VUID-vkBindOpticalFlowSessionImageNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindOpticalFlowSessionImageNV(device, session, bindingPoint, view, layout);
}

VKAPI_ATTR void VKAPI_CALL CmdOpticalFlowExecuteNV(
    VkCommandBuffer                             commandBuffer,
    VkOpticalFlowSessionNV                      session,
    const VkOpticalFlowExecuteInfoNV*           pExecuteInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdOpticalFlowExecuteNV: Invalid commandBuffer "
                   "[VUID-vkCmdOpticalFlowExecuteNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdOpticalFlowExecuteNV(commandBuffer, session, pExecuteInfo);
}


// ---- VK_AMD_anti_lag extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL AntiLagUpdateAMD(
    VkDevice                                    device,
    const VkAntiLagDataAMD*                     pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAntiLagUpdateAMD: Invalid device "
                   "[VUID-vkAntiLagUpdateAMD-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->AntiLagUpdateAMD(device, pData);
}


// ---- VK_EXT_shader_object extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateShadersEXT(
    VkDevice                                    device,
    uint32_t                                    createInfoCount,
    const VkShaderCreateInfoEXT*                pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderEXT*                                pShaders) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateShadersEXT: Invalid device "
                   "[VUID-vkCreateShadersEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
}

VKAPI_ATTR void VKAPI_CALL DestroyShaderEXT(
    VkDevice                                    device,
    VkShaderEXT                                 shader,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyShaderEXT: Invalid device "
                   "[VUID-vkDestroyShaderEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyShaderEXT(device, shader, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetShaderBinaryDataEXT(
    VkDevice                                    device,
    VkShaderEXT                                 shader,
    size_t*                                     pDataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetShaderBinaryDataEXT: Invalid device "
                   "[VUID-vkGetShaderBinaryDataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetShaderBinaryDataEXT(device, shader, pDataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL CmdBindShadersEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    stageCount,
    const VkShaderStageFlagBits*                pStages,
    const VkShaderEXT*                          pShaders) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindShadersEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindShadersEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindShadersEXT(commandBuffer, stageCount, pStages, pShaders);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthClampRangeEXT(
    VkCommandBuffer                             commandBuffer,
    VkDepthClampModeEXT                         depthClampMode,
    const VkDepthClampRangeEXT*                 pDepthClampRange) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthClampRangeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthClampRangeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthClampRangeEXT(commandBuffer, depthClampMode, pDepthClampRange);
}


// ---- VK_QCOM_tile_properties extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetFramebufferTilePropertiesQCOM(
    VkDevice                                    device,
    VkFramebuffer                               framebuffer,
    uint32_t*                                   pPropertiesCount,
    VkTilePropertiesQCOM*                       pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetFramebufferTilePropertiesQCOM: Invalid device "
                   "[VUID-vkGetFramebufferTilePropertiesQCOM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetFramebufferTilePropertiesQCOM(device, framebuffer, pPropertiesCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDynamicRenderingTilePropertiesQCOM(
    VkDevice                                    device,
    const VkRenderingInfo*                      pRenderingInfo,
    VkTilePropertiesQCOM*                       pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDynamicRenderingTilePropertiesQCOM: Invalid device "
                   "[VUID-vkGetDynamicRenderingTilePropertiesQCOM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDynamicRenderingTilePropertiesQCOM(device, pRenderingInfo, pProperties);
}


// ---- VK_NV_cooperative_vector extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCooperativeVectorPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeVectorPropertiesNV*            pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCooperativeVectorPropertiesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCooperativeVectorPropertiesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCooperativeVectorPropertiesNV(unwrapped_phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCooperativeVectorPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeVectorPropertiesNV*            pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCooperativeVectorPropertiesNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCooperativeVectorPropertiesNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCooperativeVectorPropertiesNV(phys_dev_term->phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL ConvertCooperativeVectorMatrixNV(
    VkDevice                                    device,
    const VkConvertCooperativeVectorMatrixInfoNV* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkConvertCooperativeVectorMatrixNV: Invalid device "
                   "[VUID-vkConvertCooperativeVectorMatrixNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ConvertCooperativeVectorMatrixNV(device, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdConvertCooperativeVectorMatrixNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkConvertCooperativeVectorMatrixInfoNV* pInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdConvertCooperativeVectorMatrixNV: Invalid commandBuffer "
                   "[VUID-vkCmdConvertCooperativeVectorMatrixNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdConvertCooperativeVectorMatrixNV(commandBuffer, infoCount, pInfos);
}


// ---- VK_NV_low_latency2 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL SetLatencySleepModeNV(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkLatencySleepModeInfoNV*             pSleepModeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetLatencySleepModeNV: Invalid device "
                   "[VUID-vkSetLatencySleepModeNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->SetLatencySleepModeNV(device, swapchain, pSleepModeInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL LatencySleepNV(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkLatencySleepInfoNV*                 pSleepInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkLatencySleepNV: Invalid device "
                   "[VUID-vkLatencySleepNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->LatencySleepNV(device, swapchain, pSleepInfo);
}

VKAPI_ATTR void VKAPI_CALL SetLatencyMarkerNV(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkSetLatencyMarkerInfoNV*             pLatencyMarkerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetLatencyMarkerNV: Invalid device "
                   "[VUID-vkSetLatencyMarkerNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetLatencyMarkerNV(device, swapchain, pLatencyMarkerInfo);
}

VKAPI_ATTR void VKAPI_CALL GetLatencyTimingsNV(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkGetLatencyMarkerInfoNV*                   pLatencyMarkerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetLatencyTimingsNV: Invalid device "
                   "[VUID-vkGetLatencyTimingsNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetLatencyTimingsNV(device, swapchain, pLatencyMarkerInfo);
}

VKAPI_ATTR void VKAPI_CALL QueueNotifyOutOfBandNV(
    VkQueue                                     queue,
    const VkOutOfBandQueueTypeInfoNV*           pQueueTypeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueNotifyOutOfBandNV: Invalid queue "
                   "[VUID-vkQueueNotifyOutOfBandNV-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->QueueNotifyOutOfBandNV(queue, pQueueTypeInfo);
}


// ---- VK_ARM_data_graph extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateDataGraphPipelinesARM(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkDataGraphPipelineCreateInfoARM*     pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDataGraphPipelinesARM: Invalid device "
                   "[VUID-vkCreateDataGraphPipelinesARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateDataGraphPipelinesARM(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateDataGraphPipelineSessionARM(
    VkDevice                                    device,
    const VkDataGraphPipelineSessionCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDataGraphPipelineSessionARM*              pSession) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDataGraphPipelineSessionARM: Invalid device "
                   "[VUID-vkCreateDataGraphPipelineSessionARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateDataGraphPipelineSessionARM(device, pCreateInfo, pAllocator, pSession);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDataGraphPipelineSessionBindPointRequirementsARM(
    VkDevice                                    device,
    const VkDataGraphPipelineSessionBindPointRequirementsInfoARM* pInfo,
    uint32_t*                                   pBindPointRequirementCount,
    VkDataGraphPipelineSessionBindPointRequirementARM* pBindPointRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDataGraphPipelineSessionBindPointRequirementsARM: Invalid device "
                   "[VUID-vkGetDataGraphPipelineSessionBindPointRequirementsARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDataGraphPipelineSessionBindPointRequirementsARM(device, pInfo, pBindPointRequirementCount, pBindPointRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetDataGraphPipelineSessionMemoryRequirementsARM(
    VkDevice                                    device,
    const VkDataGraphPipelineSessionMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDataGraphPipelineSessionMemoryRequirementsARM: Invalid device "
                   "[VUID-vkGetDataGraphPipelineSessionMemoryRequirementsARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDataGraphPipelineSessionMemoryRequirementsARM(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL BindDataGraphPipelineSessionMemoryARM(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindDataGraphPipelineSessionMemoryInfoARM* pBindInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBindDataGraphPipelineSessionMemoryARM: Invalid device "
                   "[VUID-vkBindDataGraphPipelineSessionMemoryARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BindDataGraphPipelineSessionMemoryARM(device, bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL DestroyDataGraphPipelineSessionARM(
    VkDevice                                    device,
    VkDataGraphPipelineSessionARM               session,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyDataGraphPipelineSessionARM: Invalid device "
                   "[VUID-vkDestroyDataGraphPipelineSessionARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyDataGraphPipelineSessionARM(device, session, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL CmdDispatchDataGraphARM(
    VkCommandBuffer                             commandBuffer,
    VkDataGraphPipelineSessionARM               session,
    const VkDataGraphPipelineDispatchInfoARM*   pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDispatchDataGraphARM: Invalid commandBuffer "
                   "[VUID-vkCmdDispatchDataGraphARM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDispatchDataGraphARM(commandBuffer, session, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDataGraphPipelineAvailablePropertiesARM(
    VkDevice                                    device,
    const VkDataGraphPipelineInfoARM*           pPipelineInfo,
    uint32_t*                                   pPropertiesCount,
    VkDataGraphPipelinePropertyARM*             pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDataGraphPipelineAvailablePropertiesARM: Invalid device "
                   "[VUID-vkGetDataGraphPipelineAvailablePropertiesARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDataGraphPipelineAvailablePropertiesARM(device, pPipelineInfo, pPropertiesCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDataGraphPipelinePropertiesARM(
    VkDevice                                    device,
    const VkDataGraphPipelineInfoARM*           pPipelineInfo,
    uint32_t                                    propertiesCount,
    VkDataGraphPipelinePropertyQueryResultARM*  pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDataGraphPipelinePropertiesARM: Invalid device "
                   "[VUID-vkGetDataGraphPipelinePropertiesARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDataGraphPipelinePropertiesARM(device, pPipelineInfo, propertiesCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pQueueFamilyDataGraphPropertyCount,
    VkQueueFamilyDataGraphPropertiesARM*        pQueueFamilyDataGraphProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(unwrapped_phys_dev, queueFamilyIndex, pQueueFamilyDataGraphPropertyCount, pQueueFamilyDataGraphProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pQueueFamilyDataGraphPropertyCount,
    VkQueueFamilyDataGraphPropertiesARM*        pQueueFamilyDataGraphProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(phys_dev_term->phys_dev, queueFamilyIndex, pQueueFamilyDataGraphPropertyCount, pQueueFamilyDataGraphProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM* pQueueFamilyDataGraphProcessingEngineInfo,
    VkQueueFamilyDataGraphProcessingEnginePropertiesARM* pQueueFamilyDataGraphProcessingEngineProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(unwrapped_phys_dev, pQueueFamilyDataGraphProcessingEngineInfo, pQueueFamilyDataGraphProcessingEngineProperties);
}

VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM* pQueueFamilyDataGraphProcessingEngineInfo,
    VkQueueFamilyDataGraphProcessingEnginePropertiesARM* pQueueFamilyDataGraphProcessingEngineProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(phys_dev_term->phys_dev, pQueueFamilyDataGraphProcessingEngineInfo, pQueueFamilyDataGraphProcessingEngineProperties);
}


// ---- VK_ARM_data_graph_instruction_set_tosa extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    const VkQueueFamilyDataGraphPropertiesARM*  pQueueFamilyDataGraphProperties,
    VkBaseOutStructure*                         pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(unwrapped_phys_dev, queueFamilyIndex, pQueueFamilyDataGraphProperties, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    const VkQueueFamilyDataGraphPropertiesARM*  pQueueFamilyDataGraphProperties,
    VkBaseOutStructure*                         pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(phys_dev_term->phys_dev, queueFamilyIndex, pQueueFamilyDataGraphProperties, pProperties);
}


// ---- VK_EXT_attachment_feedback_loop_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetAttachmentFeedbackLoopEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkImageAspectFlags                          aspectMask) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetAttachmentFeedbackLoopEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetAttachmentFeedbackLoopEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetAttachmentFeedbackLoopEnableEXT(commandBuffer, aspectMask);
}


// ---- VK_QNX_external_memory_screen_buffer extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
VKAPI_ATTR VkResult VKAPI_CALL GetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    const struct _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetScreenBufferPropertiesQNX: Invalid device "
                   "[VUID-vkGetScreenBufferPropertiesQNX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetScreenBufferPropertiesQNX(device, buffer, pProperties);
}

#endif // VK_USE_PLATFORM_SCREEN_QNX

// ---- VK_QCOM_tile_memory_heap extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBindTileMemoryQCOM(
    VkCommandBuffer                             commandBuffer,
    const VkTileMemoryBindInfoQCOM*             pTileMemoryBindInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindTileMemoryQCOM: Invalid commandBuffer "
                   "[VUID-vkCmdBindTileMemoryQCOM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindTileMemoryQCOM(commandBuffer, pTileMemoryBindInfo);
}


// ---- VK_EXT_memory_decompression extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDecompressMemoryEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDecompressMemoryInfoEXT*            pDecompressMemoryInfoEXT) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDecompressMemoryEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDecompressMemoryEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDecompressMemoryEXT(commandBuffer, pDecompressMemoryInfoEXT);
}

VKAPI_ATTR void VKAPI_CALL CmdDecompressMemoryIndirectCountEXT(
    VkCommandBuffer                             commandBuffer,
    VkMemoryDecompressionMethodFlagsEXT         decompressionMethod,
    VkDeviceAddress                             indirectCommandsAddress,
    VkDeviceAddress                             indirectCommandsCountAddress,
    uint32_t                                    maxDecompressionCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDecompressMemoryIndirectCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDecompressMemoryIndirectCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDecompressMemoryIndirectCountEXT(commandBuffer, decompressionMethod, indirectCommandsAddress, indirectCommandsCountAddress, maxDecompressionCount, stride);
}


// ---- VK_NV_external_compute_queue extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateExternalComputeQueueNV(
    VkDevice                                    device,
    const VkExternalComputeQueueCreateInfoNV*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkExternalComputeQueueNV*                   pExternalQueue) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateExternalComputeQueueNV: Invalid device "
                   "[VUID-vkCreateExternalComputeQueueNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateExternalComputeQueueNV(device, pCreateInfo, pAllocator, pExternalQueue);
}

VKAPI_ATTR void VKAPI_CALL DestroyExternalComputeQueueNV(
    VkDevice                                    device,
    VkExternalComputeQueueNV                    externalQueue,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyExternalComputeQueueNV: Invalid device "
                   "[VUID-vkDestroyExternalComputeQueueNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyExternalComputeQueueNV(device, externalQueue, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL GetExternalComputeQueueDataNV(
    VkExternalComputeQueueNV                    externalQueue,
    VkExternalComputeQueueDataParamsNV*         params,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(externalQueue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetExternalComputeQueueDataNV: Invalid externalQueue "
                   "[VUID-vkGetExternalComputeQueueDataNV-externalQueue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetExternalComputeQueueDataNV(externalQueue, params, pData);
}


// ---- VK_NV_cluster_acceleration_structure extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetClusterAccelerationStructureBuildSizesNV(
    VkDevice                                    device,
    const VkClusterAccelerationStructureInputInfoNV* pInfo,
    VkAccelerationStructureBuildSizesInfoKHR*   pSizeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetClusterAccelerationStructureBuildSizesNV: Invalid device "
                   "[VUID-vkGetClusterAccelerationStructureBuildSizesNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetClusterAccelerationStructureBuildSizesNV(device, pInfo, pSizeInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBuildClusterAccelerationStructureIndirectNV(
    VkCommandBuffer                             commandBuffer,
    const VkClusterAccelerationStructureCommandsInfoNV* pCommandInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBuildClusterAccelerationStructureIndirectNV: Invalid commandBuffer "
                   "[VUID-vkCmdBuildClusterAccelerationStructureIndirectNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBuildClusterAccelerationStructureIndirectNV(commandBuffer, pCommandInfos);
}


// ---- VK_NV_partitioned_acceleration_structure extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetPartitionedAccelerationStructuresBuildSizesNV(
    VkDevice                                    device,
    const VkPartitionedAccelerationStructureInstancesInputNV* pInfo,
    VkAccelerationStructureBuildSizesInfoKHR*   pSizeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPartitionedAccelerationStructuresBuildSizesNV: Invalid device "
                   "[VUID-vkGetPartitionedAccelerationStructuresBuildSizesNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetPartitionedAccelerationStructuresBuildSizesNV(device, pInfo, pSizeInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBuildPartitionedAccelerationStructuresNV(
    VkCommandBuffer                             commandBuffer,
    const VkBuildPartitionedAccelerationStructureInfoNV* pBuildInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBuildPartitionedAccelerationStructuresNV: Invalid commandBuffer "
                   "[VUID-vkCmdBuildPartitionedAccelerationStructuresNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBuildPartitionedAccelerationStructuresNV(commandBuffer, pBuildInfo);
}


// ---- VK_EXT_device_generated_commands extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL GetGeneratedCommandsMemoryRequirementsEXT(
    VkDevice                                    device,
    const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetGeneratedCommandsMemoryRequirementsEXT: Invalid device "
                   "[VUID-vkGetGeneratedCommandsMemoryRequirementsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetGeneratedCommandsMemoryRequirementsEXT(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL CmdPreprocessGeneratedCommandsEXT(
    VkCommandBuffer                             commandBuffer,
    const VkGeneratedCommandsInfoEXT*           pGeneratedCommandsInfo,
    VkCommandBuffer                             stateCommandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPreprocessGeneratedCommandsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdPreprocessGeneratedCommandsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPreprocessGeneratedCommandsEXT(commandBuffer, pGeneratedCommandsInfo, stateCommandBuffer);
}

VKAPI_ATTR void VKAPI_CALL CmdExecuteGeneratedCommandsEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    isPreprocessed,
    const VkGeneratedCommandsInfoEXT*           pGeneratedCommandsInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdExecuteGeneratedCommandsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdExecuteGeneratedCommandsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdExecuteGeneratedCommandsEXT(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateIndirectCommandsLayoutEXT(
    VkDevice                                    device,
    const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkIndirectCommandsLayoutEXT*                pIndirectCommandsLayout) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateIndirectCommandsLayoutEXT: Invalid device "
                   "[VUID-vkCreateIndirectCommandsLayoutEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateIndirectCommandsLayoutEXT(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
}

VKAPI_ATTR void VKAPI_CALL DestroyIndirectCommandsLayoutEXT(
    VkDevice                                    device,
    VkIndirectCommandsLayoutEXT                 indirectCommandsLayout,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyIndirectCommandsLayoutEXT: Invalid device "
                   "[VUID-vkDestroyIndirectCommandsLayoutEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyIndirectCommandsLayoutEXT(device, indirectCommandsLayout, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateIndirectExecutionSetEXT(
    VkDevice                                    device,
    const VkIndirectExecutionSetCreateInfoEXT*  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkIndirectExecutionSetEXT*                  pIndirectExecutionSet) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateIndirectExecutionSetEXT: Invalid device "
                   "[VUID-vkCreateIndirectExecutionSetEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateIndirectExecutionSetEXT(device, pCreateInfo, pAllocator, pIndirectExecutionSet);
}

VKAPI_ATTR void VKAPI_CALL DestroyIndirectExecutionSetEXT(
    VkDevice                                    device,
    VkIndirectExecutionSetEXT                   indirectExecutionSet,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyIndirectExecutionSetEXT: Invalid device "
                   "[VUID-vkDestroyIndirectExecutionSetEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyIndirectExecutionSetEXT(device, indirectExecutionSet, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL UpdateIndirectExecutionSetPipelineEXT(
    VkDevice                                    device,
    VkIndirectExecutionSetEXT                   indirectExecutionSet,
    uint32_t                                    executionSetWriteCount,
    const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUpdateIndirectExecutionSetPipelineEXT: Invalid device "
                   "[VUID-vkUpdateIndirectExecutionSetPipelineEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->UpdateIndirectExecutionSetPipelineEXT(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
}

VKAPI_ATTR void VKAPI_CALL UpdateIndirectExecutionSetShaderEXT(
    VkDevice                                    device,
    VkIndirectExecutionSetEXT                   indirectExecutionSet,
    uint32_t                                    executionSetWriteCount,
    const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkUpdateIndirectExecutionSetShaderEXT: Invalid device "
                   "[VUID-vkUpdateIndirectExecutionSetShaderEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->UpdateIndirectExecutionSetShaderEXT(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
}


// ---- VK_OHOS_surface extension trampoline/terminators

#if defined(VK_USE_PLATFORM_OHOS)
VKAPI_ATTR VkResult VKAPI_CALL CreateSurfaceOHOS(
    VkInstance                                  instance,
    const VkSurfaceCreateInfoOHOS*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface) {
    struct loader_instance *inst = loader_get_instance(instance);
    if (NULL == inst) {
        loader_log(
            NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
            "vkCreateSurfaceOHOS: Invalid instance [VUID-vkCreateSurfaceOHOS-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
#error("Not implemented. Likely needs to be manually generated!");
    return inst->disp->CreateSurfaceOHOS(instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateSurfaceOHOS(
    VkInstance                                  instance,
    const VkSurfaceCreateInfoOHOS*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface) {
    struct loader_instance *inst = loader_get_instance(instance);
    if (NULL == inst) {
        loader_log(
            NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
            "vkCreateSurfaceOHOS: Invalid instance [VUID-vkCreateSurfaceOHOS-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
#error("Not implemented. Likely needs to be manually generated!");
}

#endif // VK_USE_PLATFORM_OHOS

// ---- VK_NV_cooperative_matrix2 extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixFlexibleDimensionsPropertiesNV* pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(unwrapped_phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixFlexibleDimensionsPropertiesNV* pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(phys_dev_term->phys_dev, pPropertyCount, pProperties);
}


// ---- VK_EXT_external_memory_metal extension trampoline/terminators

#if defined(VK_USE_PLATFORM_METAL_EXT)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryMetalHandleEXT(
    VkDevice                                    device,
    const VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    void**                                      pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryMetalHandleEXT: Invalid device "
                   "[VUID-vkGetMemoryMetalHandleEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryMetalHandleEXT(device, pGetMetalHandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_METAL_EXT
#if defined(VK_USE_PLATFORM_METAL_EXT)
VKAPI_ATTR VkResult VKAPI_CALL GetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    const void*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryMetalHandlePropertiesEXT: Invalid device "
                   "[VUID-vkGetMemoryMetalHandlePropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryMetalHandlePropertiesEXT(device, handleType, pHandle, pMemoryMetalHandleProperties);
}

#endif // VK_USE_PLATFORM_METAL_EXT

// ---- VK_ARM_performance_counters_by_region extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterARM*                    pCounters,
    VkPerformanceCounterDescriptionARM*         pCounterDescriptions) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM: Invalid physicalDevice "
                   "[VUID-vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(unwrapped_phys_dev, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterARM*                    pCounters,
    VkPerformanceCounterDescriptionARM*         pCounterDescriptions) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(phys_dev_term->phys_dev, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}


// ---- VK_ARM_shader_instrumentation extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDeviceShaderInstrumentationMetricsARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pDescriptionCount,
    VkShaderInstrumentationMetricDescriptionARM* pDescriptions) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM: Invalid physicalDevice "
                   "[VUID-vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->EnumeratePhysicalDeviceShaderInstrumentationMetricsARM(unwrapped_phys_dev, pDescriptionCount, pDescriptions);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumeratePhysicalDeviceShaderInstrumentationMetricsARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pDescriptionCount,
    VkShaderInstrumentationMetricDescriptionARM* pDescriptions) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.EnumeratePhysicalDeviceShaderInstrumentationMetricsARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support EnumeratePhysicalDeviceShaderInstrumentationMetricsARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.EnumeratePhysicalDeviceShaderInstrumentationMetricsARM(phys_dev_term->phys_dev, pDescriptionCount, pDescriptions);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateShaderInstrumentationARM(
    VkDevice                                    device,
    const VkShaderInstrumentationCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderInstrumentationARM*                 pInstrumentation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateShaderInstrumentationARM: Invalid device "
                   "[VUID-vkCreateShaderInstrumentationARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateShaderInstrumentationARM(device, pCreateInfo, pAllocator, pInstrumentation);
}

VKAPI_ATTR void VKAPI_CALL DestroyShaderInstrumentationARM(
    VkDevice                                    device,
    VkShaderInstrumentationARM                  instrumentation,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyShaderInstrumentationARM: Invalid device "
                   "[VUID-vkDestroyShaderInstrumentationARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyShaderInstrumentationARM(device, instrumentation, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginShaderInstrumentationARM(
    VkCommandBuffer                             commandBuffer,
    VkShaderInstrumentationARM                  instrumentation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginShaderInstrumentationARM: Invalid commandBuffer "
                   "[VUID-vkCmdBeginShaderInstrumentationARM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginShaderInstrumentationARM(commandBuffer, instrumentation);
}

VKAPI_ATTR void VKAPI_CALL CmdEndShaderInstrumentationARM(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndShaderInstrumentationARM: Invalid commandBuffer "
                   "[VUID-vkCmdEndShaderInstrumentationARM-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndShaderInstrumentationARM(commandBuffer);
}

VKAPI_ATTR VkResult VKAPI_CALL GetShaderInstrumentationValuesARM(
    VkDevice                                    device,
    VkShaderInstrumentationARM                  instrumentation,
    uint32_t*                                   pMetricBlockCount,
    void*                                       pMetricValues,
    VkShaderInstrumentationValuesFlagsARM       flags) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetShaderInstrumentationValuesARM: Invalid device "
                   "[VUID-vkGetShaderInstrumentationValuesARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetShaderInstrumentationValuesARM(device, instrumentation, pMetricBlockCount, pMetricValues, flags);
}

VKAPI_ATTR void VKAPI_CALL ClearShaderInstrumentationMetricsARM(
    VkDevice                                    device,
    VkShaderInstrumentationARM                  instrumentation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkClearShaderInstrumentationMetricsARM: Invalid device "
                   "[VUID-vkClearShaderInstrumentationMetricsARM-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->ClearShaderInstrumentationMetricsARM(device, instrumentation);
}


// ---- VK_EXT_fragment_density_map_offset extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdEndRendering2EXT(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingEndInfoKHR*                pRenderingEndInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndRendering2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndRendering2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdEndRendering2EXT(commandBuffer, pRenderingEndInfo);
}


// ---- VK_EXT_custom_resolve extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdBeginCustomResolveEXT(
    VkCommandBuffer                             commandBuffer,
    const VkBeginCustomResolveInfoEXT*          pBeginCustomResolveInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginCustomResolveEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginCustomResolveEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBeginCustomResolveEXT(commandBuffer, pBeginCustomResolveInfo);
}


// ---- VK_ARM_data_graph_optical_flow extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    const VkQueueFamilyDataGraphPropertiesARM*  pQueueFamilyDataGraphProperties,
    const VkDataGraphOpticalFlowImageFormatInfoARM* pOpticalFlowImageFormatInfo,
    uint32_t*                                   pFormatCount,
    VkDataGraphOpticalFlowImageFormatPropertiesARM* pImageFormatProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(unwrapped_phys_dev, queueFamilyIndex, pQueueFamilyDataGraphProperties, pOpticalFlowImageFormatInfo, pFormatCount, pImageFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    const VkQueueFamilyDataGraphPropertiesARM*  pQueueFamilyDataGraphProperties,
    const VkDataGraphOpticalFlowImageFormatInfoARM* pOpticalFlowImageFormatInfo,
    uint32_t*                                   pFormatCount,
    VkDataGraphOpticalFlowImageFormatPropertiesARM* pImageFormatProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(phys_dev_term->phys_dev, queueFamilyIndex, pQueueFamilyDataGraphProperties, pOpticalFlowImageFormatInfo, pFormatCount, pImageFormatProperties);
}


// ---- VK_NV_compute_occupancy_priority extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetComputeOccupancyPriorityNV(
    VkCommandBuffer                             commandBuffer,
    const VkComputeOccupancyPriorityParametersNV* pParameters) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetComputeOccupancyPriorityNV: Invalid commandBuffer "
                   "[VUID-vkCmdSetComputeOccupancyPriorityNV-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetComputeOccupancyPriorityNV(commandBuffer, pParameters);
}


// ---- VK_SEC_ubm_surface extension trampoline/terminators

#if defined(VK_USE_PLATFORM_UBM_SEC)
VKAPI_ATTR VkResult VKAPI_CALL CreateUbmSurfaceSEC(
    VkInstance                                  instance,
    const VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface) {
    struct loader_instance *inst = loader_get_instance(instance);
    if (NULL == inst) {
        loader_log(
            NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
            "vkCreateUbmSurfaceSEC: Invalid instance [VUID-vkCreateUbmSurfaceSEC-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
#error("Not implemented. Likely needs to be manually generated!");
    return inst->disp->CreateUbmSurfaceSEC(instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateUbmSurfaceSEC(
    VkInstance                                  instance,
    const VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface) {
    struct loader_instance *inst = loader_get_instance(instance);
    if (NULL == inst) {
        loader_log(
            NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
            "vkCreateUbmSurfaceSEC: Invalid instance [VUID-vkCreateUbmSurfaceSEC-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
#error("Not implemented. Likely needs to be manually generated!");
}

#endif // VK_USE_PLATFORM_UBM_SEC
#if defined(VK_USE_PLATFORM_UBM_SEC)
VKAPI_ATTR VkBool32 VKAPI_CALL GetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    struct ubm_device*                          device) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceUbmPresentationSupportSEC: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceUbmPresentationSupportSEC-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceUbmPresentationSupportSEC(unwrapped_phys_dev, queueFamilyIndex, device);
}

VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    struct ubm_device*                          device) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceUbmPresentationSupportSEC) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceUbmPresentationSupportSEC");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    return icd_term->dispatch.GetPhysicalDeviceUbmPresentationSupportSEC(phys_dev_term->phys_dev, queueFamilyIndex, device);
}

#endif // VK_USE_PLATFORM_UBM_SEC

// ---- VK_EXT_primitive_restart_index extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveRestartIndexEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    primitiveRestartIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPrimitiveRestartIndexEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPrimitiveRestartIndexEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPrimitiveRestartIndexEXT(commandBuffer, primitiveRestartIndex);
}


// ---- VK_KHR_acceleration_structure extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL CreateAccelerationStructureKHR(
    VkDevice                                    device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkAccelerationStructureKHR*                 pAccelerationStructure) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateAccelerationStructureKHR: Invalid device "
                   "[VUID-vkCreateAccelerationStructureKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateAccelerationStructureKHR(device, pCreateInfo, pAllocator, pAccelerationStructure);
}

VKAPI_ATTR void VKAPI_CALL DestroyAccelerationStructureKHR(
    VkDevice                                    device,
    VkAccelerationStructureKHR                  accelerationStructure,
    const VkAllocationCallbacks*                pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroyAccelerationStructureKHR: Invalid device "
                   "[VUID-vkDestroyAccelerationStructureKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroyAccelerationStructureKHR(device, accelerationStructure, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL CmdBuildAccelerationStructuresKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBuildAccelerationStructuresKHR: Invalid commandBuffer "
                   "[VUID-vkCmdBuildAccelerationStructuresKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBuildAccelerationStructuresKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdBuildAccelerationStructuresIndirectKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress*                      pIndirectDeviceAddresses,
    const uint32_t*                             pIndirectStrides,
    const uint32_t* const*                      ppMaxPrimitiveCounts) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBuildAccelerationStructuresIndirectKHR: Invalid commandBuffer "
                   "[VUID-vkCmdBuildAccelerationStructuresIndirectKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBuildAccelerationStructuresIndirectKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
}

VKAPI_ATTR VkResult VKAPI_CALL BuildAccelerationStructuresKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    uint32_t                                    infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkBuildAccelerationStructuresKHR: Invalid device "
                   "[VUID-vkBuildAccelerationStructuresKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->BuildAccelerationStructuresKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyAccelerationStructureKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyAccelerationStructureInfoKHR*   pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyAccelerationStructureKHR: Invalid device "
                   "[VUID-vkCopyAccelerationStructureKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyAccelerationStructureKHR(device, deferredOperation, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyAccelerationStructureToMemoryKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyAccelerationStructureToMemoryKHR: Invalid device "
                   "[VUID-vkCopyAccelerationStructureToMemoryKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyAccelerationStructureToMemoryKHR(device, deferredOperation, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CopyMemoryToAccelerationStructureKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCopyMemoryToAccelerationStructureKHR: Invalid device "
                   "[VUID-vkCopyMemoryToAccelerationStructureKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CopyMemoryToAccelerationStructureKHR(device, deferredOperation, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL WriteAccelerationStructuresPropertiesKHR(
    VkDevice                                    device,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureKHR*           pAccelerationStructures,
    VkQueryType                                 queryType,
    size_t                                      dataSize,
    void*                                       pData,
    size_t                                      stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkWriteAccelerationStructuresPropertiesKHR: Invalid device "
                   "[VUID-vkWriteAccelerationStructuresPropertiesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->WriteAccelerationStructuresPropertiesKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyAccelerationStructureKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyAccelerationStructureInfoKHR*   pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyAccelerationStructureKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyAccelerationStructureKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyAccelerationStructureKHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyAccelerationStructureToMemoryKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyAccelerationStructureToMemoryKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyAccelerationStructureToMemoryKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyMemoryToAccelerationStructureKHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyMemoryToAccelerationStructureKHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyMemoryToAccelerationStructureKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo);
}

VKAPI_ATTR VkDeviceAddress VKAPI_CALL GetAccelerationStructureDeviceAddressKHR(
    VkDevice                                    device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetAccelerationStructureDeviceAddressKHR: Invalid device "
                   "[VUID-vkGetAccelerationStructureDeviceAddressKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetAccelerationStructureDeviceAddressKHR(device, pInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteAccelerationStructuresPropertiesKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureKHR*           pAccelerationStructures,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteAccelerationStructuresPropertiesKHR: Invalid commandBuffer "
                   "[VUID-vkCmdWriteAccelerationStructuresPropertiesKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteAccelerationStructuresPropertiesKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceAccelerationStructureCompatibilityKHR(
    VkDevice                                    device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR*    pCompatibility) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceAccelerationStructureCompatibilityKHR: Invalid device "
                   "[VUID-vkGetDeviceAccelerationStructureCompatibilityKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetDeviceAccelerationStructureCompatibilityKHR(device, pVersionInfo, pCompatibility);
}

VKAPI_ATTR void VKAPI_CALL GetAccelerationStructureBuildSizesKHR(
    VkDevice                                    device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t*                             pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR*   pSizeInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetAccelerationStructureBuildSizesKHR: Invalid device "
                   "[VUID-vkGetAccelerationStructureBuildSizesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetAccelerationStructureBuildSizesKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
}


// ---- VK_KHR_ray_tracing_pipeline extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdTraceRaysKHR(
    VkCommandBuffer                             commandBuffer,
    const VkStridedDeviceAddressRegionKHR*      pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pCallableShaderBindingTable,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdTraceRaysKHR: Invalid commandBuffer "
                   "[VUID-vkCmdTraceRaysKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdTraceRaysKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateRayTracingPipelinesKHR(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR*    pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateRayTracingPipelinesKHR: Invalid device "
                   "[VUID-vkCreateRayTracingPipelinesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateRayTracingPipelinesKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VKAPI_ATTR VkResult VKAPI_CALL GetRayTracingCaptureReplayShaderGroupHandlesKHR(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR: Invalid device "
                   "[VUID-vkGetRayTracingCaptureReplayShaderGroupHandlesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetRayTracingCaptureReplayShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL CmdTraceRaysIndirectKHR(
    VkCommandBuffer                             commandBuffer,
    const VkStridedDeviceAddressRegionKHR*      pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pCallableShaderBindingTable,
    VkDeviceAddress                             indirectDeviceAddress) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdTraceRaysIndirectKHR: Invalid commandBuffer "
                   "[VUID-vkCmdTraceRaysIndirectKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdTraceRaysIndirectKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
}

VKAPI_ATTR VkDeviceSize VKAPI_CALL GetRayTracingShaderGroupStackSizeKHR(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    group,
    VkShaderGroupShaderKHR                      groupShader) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRayTracingShaderGroupStackSizeKHR: Invalid device "
                   "[VUID-vkGetRayTracingShaderGroupStackSizeKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetRayTracingShaderGroupStackSizeKHR(device, pipeline, group, groupShader);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRayTracingPipelineStackSizeKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    pipelineStackSize) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRayTracingPipelineStackSizeKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetRayTracingPipelineStackSizeKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRayTracingPipelineStackSizeKHR(commandBuffer, pipelineStackSize);
}


// ---- VK_EXT_mesh_shader extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksEXT(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksIndirectEXT(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksIndirectEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksIndirectEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksIndirectEXT(commandBuffer, buffer, offset, drawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawMeshTasksIndirectCountEXT(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdDrawMeshTasksIndirectCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdDrawMeshTasksIndirectCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdDrawMeshTasksIndirectCountEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

// GPA helpers for extensions
bool extension_instance_gpa(struct loader_instance *ptr_instance, const char *name, uint64_t nameHash, void **addr) {
    *addr = NULL;

    // ---- VK_KHR_video_queue extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceVideoCapabilitiesKHR && !strcmp(name, "vkGetPhysicalDeviceVideoCapabilitiesKHR")) {
        *addr = (void *)GetPhysicalDeviceVideoCapabilitiesKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceVideoFormatPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceVideoFormatPropertiesKHR")) {
        *addr = (void *)GetPhysicalDeviceVideoFormatPropertiesKHR;
        return true;
    }
    if (nameHash == XXH3_vkCreateVideoSessionKHR && !strcmp(name, "vkCreateVideoSessionKHR")) {
        *addr = (void *)CreateVideoSessionKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroyVideoSessionKHR && !strcmp(name, "vkDestroyVideoSessionKHR")) {
        *addr = (void *)DestroyVideoSessionKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetVideoSessionMemoryRequirementsKHR && !strcmp(name, "vkGetVideoSessionMemoryRequirementsKHR")) {
        *addr = (void *)GetVideoSessionMemoryRequirementsKHR;
        return true;
    }
    if (nameHash == XXH3_vkBindVideoSessionMemoryKHR && !strcmp(name, "vkBindVideoSessionMemoryKHR")) {
        *addr = (void *)BindVideoSessionMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCreateVideoSessionParametersKHR && !strcmp(name, "vkCreateVideoSessionParametersKHR")) {
        *addr = (void *)CreateVideoSessionParametersKHR;
        return true;
    }
    if (nameHash == XXH3_vkUpdateVideoSessionParametersKHR && !strcmp(name, "vkUpdateVideoSessionParametersKHR")) {
        *addr = (void *)UpdateVideoSessionParametersKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroyVideoSessionParametersKHR && !strcmp(name, "vkDestroyVideoSessionParametersKHR")) {
        *addr = (void *)DestroyVideoSessionParametersKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginVideoCodingKHR && !strcmp(name, "vkCmdBeginVideoCodingKHR")) {
        *addr = (void *)CmdBeginVideoCodingKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndVideoCodingKHR && !strcmp(name, "vkCmdEndVideoCodingKHR")) {
        *addr = (void *)CmdEndVideoCodingKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdControlVideoCodingKHR && !strcmp(name, "vkCmdControlVideoCodingKHR")) {
        *addr = (void *)CmdControlVideoCodingKHR;
        return true;
    }

    // ---- VK_KHR_video_decode_queue extension commands
    if (nameHash == XXH3_vkCmdDecodeVideoKHR && !strcmp(name, "vkCmdDecodeVideoKHR")) {
        *addr = (void *)CmdDecodeVideoKHR;
        return true;
    }

    // ---- VK_KHR_dynamic_rendering extension commands
    if (nameHash == XXH3_vkCmdBeginRenderingKHR && !strcmp(name, "vkCmdBeginRenderingKHR")) {
        *addr = (void *)CmdBeginRenderingKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndRenderingKHR && !strcmp(name, "vkCmdEndRenderingKHR")) {
        *addr = (void *)CmdEndRenderingKHR;
        return true;
    }

    // ---- VK_KHR_get_physical_device_properties2 extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceFeatures2KHR && !strcmp(name, "vkGetPhysicalDeviceFeatures2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceFeatures2
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceProperties2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceProperties2
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceFormatProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceFormatProperties2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceFormatProperties2
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceImageFormatProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceImageFormatProperties2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceImageFormatProperties2
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyProperties2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceQueueFamilyProperties2
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceMemoryProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceMemoryProperties2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceMemoryProperties2
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceSparseImageFormatProperties2KHR && !strcmp(name, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_get_physical_device_properties2 == 1)
                     ? (void *)vkGetPhysicalDeviceSparseImageFormatProperties2
                     : NULL;
        return true;
    }

    // ---- VK_KHR_device_group extension commands
    if (nameHash == XXH3_vkGetDeviceGroupPeerMemoryFeaturesKHR && !strcmp(name, "vkGetDeviceGroupPeerMemoryFeaturesKHR")) {
        *addr = (void *)GetDeviceGroupPeerMemoryFeaturesKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDeviceMaskKHR && !strcmp(name, "vkCmdSetDeviceMaskKHR")) {
        *addr = (void *)CmdSetDeviceMaskKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDispatchBaseKHR && !strcmp(name, "vkCmdDispatchBaseKHR")) {
        *addr = (void *)CmdDispatchBaseKHR;
        return true;
    }

    // ---- VK_KHR_maintenance1 extension commands
    if (nameHash == XXH3_vkTrimCommandPoolKHR && !strcmp(name, "vkTrimCommandPoolKHR")) {
        *addr = (void *)TrimCommandPoolKHR;
        return true;
    }

    // ---- VK_KHR_device_group_creation extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceGroupsKHR && !strcmp(name, "vkEnumeratePhysicalDeviceGroupsKHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_device_group_creation == 1)
                     ? (void *)vkEnumeratePhysicalDeviceGroups
                     : NULL;
        return true;
    }

    // ---- VK_KHR_external_memory_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalBufferPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceExternalBufferPropertiesKHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_external_memory_capabilities == 1)
                     ? (void *)vkGetPhysicalDeviceExternalBufferProperties
                     : NULL;
        return true;
    }

    // ---- VK_KHR_external_memory_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetMemoryWin32HandleKHR && !strcmp(name, "vkGetMemoryWin32HandleKHR")) {
        *addr = (void *)GetMemoryWin32HandleKHR;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetMemoryWin32HandlePropertiesKHR && !strcmp(name, "vkGetMemoryWin32HandlePropertiesKHR")) {
        *addr = (void *)GetMemoryWin32HandlePropertiesKHR;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_memory_fd extension commands
    if (nameHash == XXH3_vkGetMemoryFdKHR && !strcmp(name, "vkGetMemoryFdKHR")) {
        *addr = (void *)GetMemoryFdKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetMemoryFdPropertiesKHR && !strcmp(name, "vkGetMemoryFdPropertiesKHR")) {
        *addr = (void *)GetMemoryFdPropertiesKHR;
        return true;
    }

    // ---- VK_KHR_external_semaphore_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_external_semaphore_capabilities == 1)
                     ? (void *)vkGetPhysicalDeviceExternalSemaphoreProperties
                     : NULL;
        return true;
    }

    // ---- VK_KHR_external_semaphore_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkImportSemaphoreWin32HandleKHR && !strcmp(name, "vkImportSemaphoreWin32HandleKHR")) {
        *addr = (void *)ImportSemaphoreWin32HandleKHR;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetSemaphoreWin32HandleKHR && !strcmp(name, "vkGetSemaphoreWin32HandleKHR")) {
        *addr = (void *)GetSemaphoreWin32HandleKHR;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_semaphore_fd extension commands
    if (nameHash == XXH3_vkImportSemaphoreFdKHR && !strcmp(name, "vkImportSemaphoreFdKHR")) {
        *addr = (void *)ImportSemaphoreFdKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetSemaphoreFdKHR && !strcmp(name, "vkGetSemaphoreFdKHR")) {
        *addr = (void *)GetSemaphoreFdKHR;
        return true;
    }

    // ---- VK_KHR_push_descriptor extension commands
    if (nameHash == XXH3_vkCmdPushDescriptorSetKHR && !strcmp(name, "vkCmdPushDescriptorSetKHR")) {
        *addr = (void *)CmdPushDescriptorSetKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplateKHR && !strcmp(name, "vkCmdPushDescriptorSetWithTemplateKHR")) {
        *addr = (void *)CmdPushDescriptorSetWithTemplateKHR;
        return true;
    }

    // ---- VK_KHR_descriptor_update_template extension commands
    if (nameHash == XXH3_vkCreateDescriptorUpdateTemplateKHR && !strcmp(name, "vkCreateDescriptorUpdateTemplateKHR")) {
        *addr = (void *)CreateDescriptorUpdateTemplateKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroyDescriptorUpdateTemplateKHR && !strcmp(name, "vkDestroyDescriptorUpdateTemplateKHR")) {
        *addr = (void *)DestroyDescriptorUpdateTemplateKHR;
        return true;
    }
    if (nameHash == XXH3_vkUpdateDescriptorSetWithTemplateKHR && !strcmp(name, "vkUpdateDescriptorSetWithTemplateKHR")) {
        *addr = (void *)UpdateDescriptorSetWithTemplateKHR;
        return true;
    }

    // ---- VK_KHR_create_renderpass2 extension commands
    if (nameHash == XXH3_vkCreateRenderPass2KHR && !strcmp(name, "vkCreateRenderPass2KHR")) {
        *addr = (void *)CreateRenderPass2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginRenderPass2KHR && !strcmp(name, "vkCmdBeginRenderPass2KHR")) {
        *addr = (void *)CmdBeginRenderPass2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdNextSubpass2KHR && !strcmp(name, "vkCmdNextSubpass2KHR")) {
        *addr = (void *)CmdNextSubpass2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndRenderPass2KHR && !strcmp(name, "vkCmdEndRenderPass2KHR")) {
        *addr = (void *)CmdEndRenderPass2KHR;
        return true;
    }

    // ---- VK_KHR_shared_presentable_image extension commands
    if (nameHash == XXH3_vkGetSwapchainStatusKHR && !strcmp(name, "vkGetSwapchainStatusKHR")) {
        *addr = (void *)GetSwapchainStatusKHR;
        return true;
    }

    // ---- VK_KHR_external_fence_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalFencePropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceExternalFencePropertiesKHR")) {
        *addr = (ptr_instance->enabled_extensions.khr_external_fence_capabilities == 1)
                     ? (void *)vkGetPhysicalDeviceExternalFenceProperties
                     : NULL;
        return true;
    }

    // ---- VK_KHR_external_fence_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkImportFenceWin32HandleKHR && !strcmp(name, "vkImportFenceWin32HandleKHR")) {
        *addr = (void *)ImportFenceWin32HandleKHR;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetFenceWin32HandleKHR && !strcmp(name, "vkGetFenceWin32HandleKHR")) {
        *addr = (void *)GetFenceWin32HandleKHR;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_external_fence_fd extension commands
    if (nameHash == XXH3_vkImportFenceFdKHR && !strcmp(name, "vkImportFenceFdKHR")) {
        *addr = (void *)ImportFenceFdKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetFenceFdKHR && !strcmp(name, "vkGetFenceFdKHR")) {
        *addr = (void *)GetFenceFdKHR;
        return true;
    }

    // ---- VK_KHR_performance_query extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR && !strcmp(name, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR")) {
        *addr = (void *)EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR")) {
        *addr = (void *)GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
        return true;
    }
    if (nameHash == XXH3_vkAcquireProfilingLockKHR && !strcmp(name, "vkAcquireProfilingLockKHR")) {
        *addr = (void *)AcquireProfilingLockKHR;
        return true;
    }
    if (nameHash == XXH3_vkReleaseProfilingLockKHR && !strcmp(name, "vkReleaseProfilingLockKHR")) {
        *addr = (void *)ReleaseProfilingLockKHR;
        return true;
    }

    // ---- VK_KHR_get_memory_requirements2 extension commands
    if (nameHash == XXH3_vkGetImageMemoryRequirements2KHR && !strcmp(name, "vkGetImageMemoryRequirements2KHR")) {
        *addr = (void *)GetImageMemoryRequirements2KHR;
        return true;
    }
    if (nameHash == XXH3_vkGetBufferMemoryRequirements2KHR && !strcmp(name, "vkGetBufferMemoryRequirements2KHR")) {
        *addr = (void *)GetBufferMemoryRequirements2KHR;
        return true;
    }
    if (nameHash == XXH3_vkGetImageSparseMemoryRequirements2KHR && !strcmp(name, "vkGetImageSparseMemoryRequirements2KHR")) {
        *addr = (void *)GetImageSparseMemoryRequirements2KHR;
        return true;
    }

    // ---- VK_KHR_sampler_ycbcr_conversion extension commands
    if (nameHash == XXH3_vkCreateSamplerYcbcrConversionKHR && !strcmp(name, "vkCreateSamplerYcbcrConversionKHR")) {
        *addr = (void *)CreateSamplerYcbcrConversionKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroySamplerYcbcrConversionKHR && !strcmp(name, "vkDestroySamplerYcbcrConversionKHR")) {
        *addr = (void *)DestroySamplerYcbcrConversionKHR;
        return true;
    }

    // ---- VK_KHR_bind_memory2 extension commands
    if (nameHash == XXH3_vkBindBufferMemory2KHR && !strcmp(name, "vkBindBufferMemory2KHR")) {
        *addr = (void *)BindBufferMemory2KHR;
        return true;
    }
    if (nameHash == XXH3_vkBindImageMemory2KHR && !strcmp(name, "vkBindImageMemory2KHR")) {
        *addr = (void *)BindImageMemory2KHR;
        return true;
    }

    // ---- VK_KHR_maintenance3 extension commands
    if (nameHash == XXH3_vkGetDescriptorSetLayoutSupportKHR && !strcmp(name, "vkGetDescriptorSetLayoutSupportKHR")) {
        *addr = (void *)GetDescriptorSetLayoutSupportKHR;
        return true;
    }

    // ---- VK_KHR_draw_indirect_count extension commands
    if (nameHash == XXH3_vkCmdDrawIndirectCountKHR && !strcmp(name, "vkCmdDrawIndirectCountKHR")) {
        *addr = (void *)CmdDrawIndirectCountKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCountKHR && !strcmp(name, "vkCmdDrawIndexedIndirectCountKHR")) {
        *addr = (void *)CmdDrawIndexedIndirectCountKHR;
        return true;
    }

    // ---- VK_KHR_timeline_semaphore extension commands
    if (nameHash == XXH3_vkGetSemaphoreCounterValueKHR && !strcmp(name, "vkGetSemaphoreCounterValueKHR")) {
        *addr = (void *)GetSemaphoreCounterValueKHR;
        return true;
    }
    if (nameHash == XXH3_vkWaitSemaphoresKHR && !strcmp(name, "vkWaitSemaphoresKHR")) {
        *addr = (void *)WaitSemaphoresKHR;
        return true;
    }
    if (nameHash == XXH3_vkSignalSemaphoreKHR && !strcmp(name, "vkSignalSemaphoreKHR")) {
        *addr = (void *)SignalSemaphoreKHR;
        return true;
    }

    // ---- VK_KHR_fragment_shading_rate extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceFragmentShadingRatesKHR && !strcmp(name, "vkGetPhysicalDeviceFragmentShadingRatesKHR")) {
        *addr = (void *)GetPhysicalDeviceFragmentShadingRatesKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetFragmentShadingRateKHR && !strcmp(name, "vkCmdSetFragmentShadingRateKHR")) {
        *addr = (void *)CmdSetFragmentShadingRateKHR;
        return true;
    }

    // ---- VK_KHR_dynamic_rendering_local_read extension commands
    if (nameHash == XXH3_vkCmdSetRenderingAttachmentLocationsKHR && !strcmp(name, "vkCmdSetRenderingAttachmentLocationsKHR")) {
        *addr = (void *)CmdSetRenderingAttachmentLocationsKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetRenderingInputAttachmentIndicesKHR && !strcmp(name, "vkCmdSetRenderingInputAttachmentIndicesKHR")) {
        *addr = (void *)CmdSetRenderingInputAttachmentIndicesKHR;
        return true;
    }

    // ---- VK_KHR_present_wait extension commands
    if (nameHash == XXH3_vkWaitForPresentKHR && !strcmp(name, "vkWaitForPresentKHR")) {
        *addr = (void *)WaitForPresentKHR;
        return true;
    }

    // ---- VK_KHR_buffer_device_address extension commands
    if (nameHash == XXH3_vkGetBufferDeviceAddressKHR && !strcmp(name, "vkGetBufferDeviceAddressKHR")) {
        *addr = (void *)GetBufferDeviceAddressKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetBufferOpaqueCaptureAddressKHR && !strcmp(name, "vkGetBufferOpaqueCaptureAddressKHR")) {
        *addr = (void *)GetBufferOpaqueCaptureAddressKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceMemoryOpaqueCaptureAddressKHR && !strcmp(name, "vkGetDeviceMemoryOpaqueCaptureAddressKHR")) {
        *addr = (void *)GetDeviceMemoryOpaqueCaptureAddressKHR;
        return true;
    }

    // ---- VK_KHR_deferred_host_operations extension commands
    if (nameHash == XXH3_vkCreateDeferredOperationKHR && !strcmp(name, "vkCreateDeferredOperationKHR")) {
        *addr = (void *)CreateDeferredOperationKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroyDeferredOperationKHR && !strcmp(name, "vkDestroyDeferredOperationKHR")) {
        *addr = (void *)DestroyDeferredOperationKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeferredOperationMaxConcurrencyKHR && !strcmp(name, "vkGetDeferredOperationMaxConcurrencyKHR")) {
        *addr = (void *)GetDeferredOperationMaxConcurrencyKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeferredOperationResultKHR && !strcmp(name, "vkGetDeferredOperationResultKHR")) {
        *addr = (void *)GetDeferredOperationResultKHR;
        return true;
    }
    if (nameHash == XXH3_vkDeferredOperationJoinKHR && !strcmp(name, "vkDeferredOperationJoinKHR")) {
        *addr = (void *)DeferredOperationJoinKHR;
        return true;
    }

    // ---- VK_KHR_pipeline_executable_properties extension commands
    if (nameHash == XXH3_vkGetPipelineExecutablePropertiesKHR && !strcmp(name, "vkGetPipelineExecutablePropertiesKHR")) {
        *addr = (void *)GetPipelineExecutablePropertiesKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetPipelineExecutableStatisticsKHR && !strcmp(name, "vkGetPipelineExecutableStatisticsKHR")) {
        *addr = (void *)GetPipelineExecutableStatisticsKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetPipelineExecutableInternalRepresentationsKHR && !strcmp(name, "vkGetPipelineExecutableInternalRepresentationsKHR")) {
        *addr = (void *)GetPipelineExecutableInternalRepresentationsKHR;
        return true;
    }

    // ---- VK_KHR_map_memory2 extension commands
    if (nameHash == XXH3_vkMapMemory2KHR && !strcmp(name, "vkMapMemory2KHR")) {
        *addr = (void *)MapMemory2KHR;
        return true;
    }
    if (nameHash == XXH3_vkUnmapMemory2KHR && !strcmp(name, "vkUnmapMemory2KHR")) {
        *addr = (void *)UnmapMemory2KHR;
        return true;
    }

    // ---- VK_KHR_video_encode_queue extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR")) {
        *addr = (void *)GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetEncodedVideoSessionParametersKHR && !strcmp(name, "vkGetEncodedVideoSessionParametersKHR")) {
        *addr = (void *)GetEncodedVideoSessionParametersKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdEncodeVideoKHR && !strcmp(name, "vkCmdEncodeVideoKHR")) {
        *addr = (void *)CmdEncodeVideoKHR;
        return true;
    }

    // ---- VK_KHR_synchronization2 extension commands
    if (nameHash == XXH3_vkCmdSetEvent2KHR && !strcmp(name, "vkCmdSetEvent2KHR")) {
        *addr = (void *)CmdSetEvent2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdResetEvent2KHR && !strcmp(name, "vkCmdResetEvent2KHR")) {
        *addr = (void *)CmdResetEvent2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdWaitEvents2KHR && !strcmp(name, "vkCmdWaitEvents2KHR")) {
        *addr = (void *)CmdWaitEvents2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdPipelineBarrier2KHR && !strcmp(name, "vkCmdPipelineBarrier2KHR")) {
        *addr = (void *)CmdPipelineBarrier2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdWriteTimestamp2KHR && !strcmp(name, "vkCmdWriteTimestamp2KHR")) {
        *addr = (void *)CmdWriteTimestamp2KHR;
        return true;
    }
    if (nameHash == XXH3_vkQueueSubmit2KHR && !strcmp(name, "vkQueueSubmit2KHR")) {
        *addr = (void *)QueueSubmit2KHR;
        return true;
    }

    // ---- VK_KHR_device_address_commands extension commands
    if (nameHash == XXH3_vkCmdBindIndexBuffer3KHR && !strcmp(name, "vkCmdBindIndexBuffer3KHR")) {
        *addr = (void *)CmdBindIndexBuffer3KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindVertexBuffers3KHR && !strcmp(name, "vkCmdBindVertexBuffers3KHR")) {
        *addr = (void *)CmdBindVertexBuffers3KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndirect2KHR && !strcmp(name, "vkCmdDrawIndirect2KHR")) {
        *addr = (void *)CmdDrawIndirect2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndexedIndirect2KHR && !strcmp(name, "vkCmdDrawIndexedIndirect2KHR")) {
        *addr = (void *)CmdDrawIndexedIndirect2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDispatchIndirect2KHR && !strcmp(name, "vkCmdDispatchIndirect2KHR")) {
        *addr = (void *)CmdDispatchIndirect2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMemoryKHR && !strcmp(name, "vkCmdCopyMemoryKHR")) {
        *addr = (void *)CmdCopyMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMemoryToImageKHR && !strcmp(name, "vkCmdCopyMemoryToImageKHR")) {
        *addr = (void *)CmdCopyMemoryToImageKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyImageToMemoryKHR && !strcmp(name, "vkCmdCopyImageToMemoryKHR")) {
        *addr = (void *)CmdCopyImageToMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdUpdateMemoryKHR && !strcmp(name, "vkCmdUpdateMemoryKHR")) {
        *addr = (void *)CmdUpdateMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdFillMemoryKHR && !strcmp(name, "vkCmdFillMemoryKHR")) {
        *addr = (void *)CmdFillMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyQueryPoolResultsToMemoryKHR && !strcmp(name, "vkCmdCopyQueryPoolResultsToMemoryKHR")) {
        *addr = (void *)CmdCopyQueryPoolResultsToMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndirectCount2KHR && !strcmp(name, "vkCmdDrawIndirectCount2KHR")) {
        *addr = (void *)CmdDrawIndirectCount2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCount2KHR && !strcmp(name, "vkCmdDrawIndexedIndirectCount2KHR")) {
        *addr = (void *)CmdDrawIndexedIndirectCount2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginConditionalRendering2EXT && !strcmp(name, "vkCmdBeginConditionalRendering2EXT")) {
        *addr = (void *)CmdBeginConditionalRendering2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindTransformFeedbackBuffers2EXT && !strcmp(name, "vkCmdBindTransformFeedbackBuffers2EXT")) {
        *addr = (void *)CmdBindTransformFeedbackBuffers2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginTransformFeedback2EXT && !strcmp(name, "vkCmdBeginTransformFeedback2EXT")) {
        *addr = (void *)CmdBeginTransformFeedback2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndTransformFeedback2EXT && !strcmp(name, "vkCmdEndTransformFeedback2EXT")) {
        *addr = (void *)CmdEndTransformFeedback2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndirectByteCount2EXT && !strcmp(name, "vkCmdDrawIndirectByteCount2EXT")) {
        *addr = (void *)CmdDrawIndirectByteCount2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirect2EXT && !strcmp(name, "vkCmdDrawMeshTasksIndirect2EXT")) {
        *addr = (void *)CmdDrawMeshTasksIndirect2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectCount2EXT && !strcmp(name, "vkCmdDrawMeshTasksIndirectCount2EXT")) {
        *addr = (void *)CmdDrawMeshTasksIndirectCount2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdWriteMarkerToMemoryAMD && !strcmp(name, "vkCmdWriteMarkerToMemoryAMD")) {
        *addr = (void *)CmdWriteMarkerToMemoryAMD;
        return true;
    }
    if (nameHash == XXH3_vkCreateAccelerationStructure2KHR && !strcmp(name, "vkCreateAccelerationStructure2KHR")) {
        *addr = (void *)CreateAccelerationStructure2KHR;
        return true;
    }

    // ---- VK_KHR_copy_commands2 extension commands
    if (nameHash == XXH3_vkCmdCopyBuffer2KHR && !strcmp(name, "vkCmdCopyBuffer2KHR")) {
        *addr = (void *)CmdCopyBuffer2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyImage2KHR && !strcmp(name, "vkCmdCopyImage2KHR")) {
        *addr = (void *)CmdCopyImage2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyBufferToImage2KHR && !strcmp(name, "vkCmdCopyBufferToImage2KHR")) {
        *addr = (void *)CmdCopyBufferToImage2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyImageToBuffer2KHR && !strcmp(name, "vkCmdCopyImageToBuffer2KHR")) {
        *addr = (void *)CmdCopyImageToBuffer2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBlitImage2KHR && !strcmp(name, "vkCmdBlitImage2KHR")) {
        *addr = (void *)CmdBlitImage2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdResolveImage2KHR && !strcmp(name, "vkCmdResolveImage2KHR")) {
        *addr = (void *)CmdResolveImage2KHR;
        return true;
    }

    // ---- VK_KHR_ray_tracing_maintenance1 extension commands
    if (nameHash == XXH3_vkCmdTraceRaysIndirect2KHR && !strcmp(name, "vkCmdTraceRaysIndirect2KHR")) {
        *addr = (void *)CmdTraceRaysIndirect2KHR;
        return true;
    }

    // ---- VK_KHR_maintenance4 extension commands
    if (nameHash == XXH3_vkGetDeviceBufferMemoryRequirementsKHR && !strcmp(name, "vkGetDeviceBufferMemoryRequirementsKHR")) {
        *addr = (void *)GetDeviceBufferMemoryRequirementsKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceImageMemoryRequirementsKHR && !strcmp(name, "vkGetDeviceImageMemoryRequirementsKHR")) {
        *addr = (void *)GetDeviceImageMemoryRequirementsKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceImageSparseMemoryRequirementsKHR && !strcmp(name, "vkGetDeviceImageSparseMemoryRequirementsKHR")) {
        *addr = (void *)GetDeviceImageSparseMemoryRequirementsKHR;
        return true;
    }

    // ---- VK_KHR_maintenance5 extension commands
    if (nameHash == XXH3_vkCmdBindIndexBuffer2KHR && !strcmp(name, "vkCmdBindIndexBuffer2KHR")) {
        *addr = (void *)CmdBindIndexBuffer2KHR;
        return true;
    }
    if (nameHash == XXH3_vkGetRenderingAreaGranularityKHR && !strcmp(name, "vkGetRenderingAreaGranularityKHR")) {
        *addr = (void *)GetRenderingAreaGranularityKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceImageSubresourceLayoutKHR && !strcmp(name, "vkGetDeviceImageSubresourceLayoutKHR")) {
        *addr = (void *)GetDeviceImageSubresourceLayoutKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetImageSubresourceLayout2KHR && !strcmp(name, "vkGetImageSubresourceLayout2KHR")) {
        *addr = (void *)GetImageSubresourceLayout2KHR;
        return true;
    }

    // ---- VK_KHR_present_wait2 extension commands
    if (nameHash == XXH3_vkWaitForPresent2KHR && !strcmp(name, "vkWaitForPresent2KHR")) {
        *addr = (void *)WaitForPresent2KHR;
        return true;
    }

    // ---- VK_KHR_pipeline_binary extension commands
    if (nameHash == XXH3_vkCreatePipelineBinariesKHR && !strcmp(name, "vkCreatePipelineBinariesKHR")) {
        *addr = (void *)CreatePipelineBinariesKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroyPipelineBinaryKHR && !strcmp(name, "vkDestroyPipelineBinaryKHR")) {
        *addr = (void *)DestroyPipelineBinaryKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetPipelineKeyKHR && !strcmp(name, "vkGetPipelineKeyKHR")) {
        *addr = (void *)GetPipelineKeyKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetPipelineBinaryDataKHR && !strcmp(name, "vkGetPipelineBinaryDataKHR")) {
        *addr = (void *)GetPipelineBinaryDataKHR;
        return true;
    }
    if (nameHash == XXH3_vkReleaseCapturedPipelineDataKHR && !strcmp(name, "vkReleaseCapturedPipelineDataKHR")) {
        *addr = (void *)ReleaseCapturedPipelineDataKHR;
        return true;
    }

    // ---- VK_KHR_swapchain_maintenance1 extension commands
    if (nameHash == XXH3_vkReleaseSwapchainImagesKHR && !strcmp(name, "vkReleaseSwapchainImagesKHR")) {
        *addr = (void *)ReleaseSwapchainImagesKHR;
        return true;
    }

    // ---- VK_KHR_cooperative_matrix extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR && !strcmp(name, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR")) {
        *addr = (void *)GetPhysicalDeviceCooperativeMatrixPropertiesKHR;
        return true;
    }

    // ---- VK_KHR_line_rasterization extension commands
    if (nameHash == XXH3_vkCmdSetLineStippleKHR && !strcmp(name, "vkCmdSetLineStippleKHR")) {
        *addr = (void *)CmdSetLineStippleKHR;
        return true;
    }

    // ---- VK_KHR_calibrated_timestamps extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR && !strcmp(name, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR")) {
        *addr = (void *)GetPhysicalDeviceCalibrateableTimeDomainsKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetCalibratedTimestampsKHR && !strcmp(name, "vkGetCalibratedTimestampsKHR")) {
        *addr = (void *)GetCalibratedTimestampsKHR;
        return true;
    }

    // ---- VK_KHR_maintenance6 extension commands
    if (nameHash == XXH3_vkCmdBindDescriptorSets2KHR && !strcmp(name, "vkCmdBindDescriptorSets2KHR")) {
        *addr = (void *)CmdBindDescriptorSets2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdPushConstants2KHR && !strcmp(name, "vkCmdPushConstants2KHR")) {
        *addr = (void *)CmdPushConstants2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSet2KHR && !strcmp(name, "vkCmdPushDescriptorSet2KHR")) {
        *addr = (void *)CmdPushDescriptorSet2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplate2KHR && !strcmp(name, "vkCmdPushDescriptorSetWithTemplate2KHR")) {
        *addr = (void *)CmdPushDescriptorSetWithTemplate2KHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDescriptorBufferOffsets2EXT && !strcmp(name, "vkCmdSetDescriptorBufferOffsets2EXT")) {
        *addr = (void *)CmdSetDescriptorBufferOffsets2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT && !strcmp(name, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT")) {
        *addr = (void *)CmdBindDescriptorBufferEmbeddedSamplers2EXT;
        return true;
    }

    // ---- VK_KHR_copy_memory_indirect extension commands
    if (nameHash == XXH3_vkCmdCopyMemoryIndirectKHR && !strcmp(name, "vkCmdCopyMemoryIndirectKHR")) {
        *addr = (void *)CmdCopyMemoryIndirectKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMemoryToImageIndirectKHR && !strcmp(name, "vkCmdCopyMemoryToImageIndirectKHR")) {
        *addr = (void *)CmdCopyMemoryToImageIndirectKHR;
        return true;
    }

    // ---- VK_KHR_device_fault extension commands
    if (nameHash == XXH3_vkGetDeviceFaultReportsKHR && !strcmp(name, "vkGetDeviceFaultReportsKHR")) {
        *addr = (void *)GetDeviceFaultReportsKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceFaultDebugInfoKHR && !strcmp(name, "vkGetDeviceFaultDebugInfoKHR")) {
        *addr = (void *)GetDeviceFaultDebugInfoKHR;
        return true;
    }

    // ---- VK_KHR_maintenance10 extension commands
    if (nameHash == XXH3_vkCmdEndRendering2KHR && !strcmp(name, "vkCmdEndRendering2KHR")) {
        *addr = (void *)CmdEndRendering2KHR;
        return true;
    }

    // ---- VK_EXT_debug_marker extension commands
    if (nameHash == XXH3_vkDebugMarkerSetObjectTagEXT && !strcmp(name, "vkDebugMarkerSetObjectTagEXT")) {
        *addr = (void *)DebugMarkerSetObjectTagEXT;
        return true;
    }
    if (nameHash == XXH3_vkDebugMarkerSetObjectNameEXT && !strcmp(name, "vkDebugMarkerSetObjectNameEXT")) {
        *addr = (void *)DebugMarkerSetObjectNameEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDebugMarkerBeginEXT && !strcmp(name, "vkCmdDebugMarkerBeginEXT")) {
        *addr = (void *)CmdDebugMarkerBeginEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDebugMarkerEndEXT && !strcmp(name, "vkCmdDebugMarkerEndEXT")) {
        *addr = (void *)CmdDebugMarkerEndEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDebugMarkerInsertEXT && !strcmp(name, "vkCmdDebugMarkerInsertEXT")) {
        *addr = (void *)CmdDebugMarkerInsertEXT;
        return true;
    }

    // ---- VK_EXT_transform_feedback extension commands
    if (nameHash == XXH3_vkCmdBindTransformFeedbackBuffersEXT && !strcmp(name, "vkCmdBindTransformFeedbackBuffersEXT")) {
        *addr = (void *)CmdBindTransformFeedbackBuffersEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginTransformFeedbackEXT && !strcmp(name, "vkCmdBeginTransformFeedbackEXT")) {
        *addr = (void *)CmdBeginTransformFeedbackEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndTransformFeedbackEXT && !strcmp(name, "vkCmdEndTransformFeedbackEXT")) {
        *addr = (void *)CmdEndTransformFeedbackEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginQueryIndexedEXT && !strcmp(name, "vkCmdBeginQueryIndexedEXT")) {
        *addr = (void *)CmdBeginQueryIndexedEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndQueryIndexedEXT && !strcmp(name, "vkCmdEndQueryIndexedEXT")) {
        *addr = (void *)CmdEndQueryIndexedEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndirectByteCountEXT && !strcmp(name, "vkCmdDrawIndirectByteCountEXT")) {
        *addr = (void *)CmdDrawIndirectByteCountEXT;
        return true;
    }

    // ---- VK_NVX_binary_import extension commands
    if (nameHash == XXH3_vkCreateCuModuleNVX && !strcmp(name, "vkCreateCuModuleNVX")) {
        *addr = (void *)CreateCuModuleNVX;
        return true;
    }
    if (nameHash == XXH3_vkCreateCuFunctionNVX && !strcmp(name, "vkCreateCuFunctionNVX")) {
        *addr = (void *)CreateCuFunctionNVX;
        return true;
    }
    if (nameHash == XXH3_vkDestroyCuModuleNVX && !strcmp(name, "vkDestroyCuModuleNVX")) {
        *addr = (void *)DestroyCuModuleNVX;
        return true;
    }
    if (nameHash == XXH3_vkDestroyCuFunctionNVX && !strcmp(name, "vkDestroyCuFunctionNVX")) {
        *addr = (void *)DestroyCuFunctionNVX;
        return true;
    }
    if (nameHash == XXH3_vkCmdCuLaunchKernelNVX && !strcmp(name, "vkCmdCuLaunchKernelNVX")) {
        *addr = (void *)CmdCuLaunchKernelNVX;
        return true;
    }

    // ---- VK_NVX_image_view_handle extension commands
    if (nameHash == XXH3_vkGetImageViewHandleNVX && !strcmp(name, "vkGetImageViewHandleNVX")) {
        *addr = (void *)GetImageViewHandleNVX;
        return true;
    }
    if (nameHash == XXH3_vkGetImageViewHandle64NVX && !strcmp(name, "vkGetImageViewHandle64NVX")) {
        *addr = (void *)GetImageViewHandle64NVX;
        return true;
    }
    if (nameHash == XXH3_vkGetImageViewAddressNVX && !strcmp(name, "vkGetImageViewAddressNVX")) {
        *addr = (void *)GetImageViewAddressNVX;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceCombinedImageSamplerIndexNVX && !strcmp(name, "vkGetDeviceCombinedImageSamplerIndexNVX")) {
        *addr = (void *)GetDeviceCombinedImageSamplerIndexNVX;
        return true;
    }

    // ---- VK_AMD_draw_indirect_count extension commands
    if (nameHash == XXH3_vkCmdDrawIndirectCountAMD && !strcmp(name, "vkCmdDrawIndirectCountAMD")) {
        *addr = (void *)CmdDrawIndirectCountAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCountAMD && !strcmp(name, "vkCmdDrawIndexedIndirectCountAMD")) {
        *addr = (void *)CmdDrawIndexedIndirectCountAMD;
        return true;
    }

    // ---- VK_AMD_shader_info extension commands
    if (nameHash == XXH3_vkGetShaderInfoAMD && !strcmp(name, "vkGetShaderInfoAMD")) {
        *addr = (void *)GetShaderInfoAMD;
        return true;
    }

    // ---- VK_NV_external_memory_capabilities extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalImageFormatPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV")) {
        *addr = (ptr_instance->enabled_extensions.nv_external_memory_capabilities == 1)
                     ? (void *)GetPhysicalDeviceExternalImageFormatPropertiesNV
                     : NULL;
        return true;
    }

    // ---- VK_NV_external_memory_win32 extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetMemoryWin32HandleNV && !strcmp(name, "vkGetMemoryWin32HandleNV")) {
        *addr = (void *)GetMemoryWin32HandleNV;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_conditional_rendering extension commands
    if (nameHash == XXH3_vkCmdBeginConditionalRenderingEXT && !strcmp(name, "vkCmdBeginConditionalRenderingEXT")) {
        *addr = (void *)CmdBeginConditionalRenderingEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndConditionalRenderingEXT && !strcmp(name, "vkCmdEndConditionalRenderingEXT")) {
        *addr = (void *)CmdEndConditionalRenderingEXT;
        return true;
    }

    // ---- VK_NV_clip_space_w_scaling extension commands
    if (nameHash == XXH3_vkCmdSetViewportWScalingNV && !strcmp(name, "vkCmdSetViewportWScalingNV")) {
        *addr = (void *)CmdSetViewportWScalingNV;
        return true;
    }

    // ---- VK_EXT_direct_mode_display extension commands
    if (nameHash == XXH3_vkReleaseDisplayEXT && !strcmp(name, "vkReleaseDisplayEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_direct_mode_display == 1)
                     ? (void *)ReleaseDisplayEXT
                     : NULL;
        return true;
    }

    // ---- VK_EXT_acquire_xlib_display extension commands
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    if (nameHash == XXH3_vkAcquireXlibDisplayEXT && !strcmp(name, "vkAcquireXlibDisplayEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_acquire_xlib_display == 1)
                     ? (void *)AcquireXlibDisplayEXT
                     : NULL;
        return true;
    }
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    if (nameHash == XXH3_vkGetRandROutputDisplayEXT && !strcmp(name, "vkGetRandROutputDisplayEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_acquire_xlib_display == 1)
                     ? (void *)GetRandROutputDisplayEXT
                     : NULL;
        return true;
    }
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT

    // ---- VK_EXT_display_surface_counter extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfaceCapabilities2EXT && !strcmp(name, "vkGetPhysicalDeviceSurfaceCapabilities2EXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_display_surface_counter == 1)
                     ? (void *)GetPhysicalDeviceSurfaceCapabilities2EXT
                     : NULL;
        return true;
    }

    // ---- VK_EXT_display_control extension commands
    if (nameHash == XXH3_vkDisplayPowerControlEXT && !strcmp(name, "vkDisplayPowerControlEXT")) {
        *addr = (void *)DisplayPowerControlEXT;
        return true;
    }
    if (nameHash == XXH3_vkRegisterDeviceEventEXT && !strcmp(name, "vkRegisterDeviceEventEXT")) {
        *addr = (void *)RegisterDeviceEventEXT;
        return true;
    }
    if (nameHash == XXH3_vkRegisterDisplayEventEXT && !strcmp(name, "vkRegisterDisplayEventEXT")) {
        *addr = (void *)RegisterDisplayEventEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetSwapchainCounterEXT && !strcmp(name, "vkGetSwapchainCounterEXT")) {
        *addr = (void *)GetSwapchainCounterEXT;
        return true;
    }

    // ---- VK_GOOGLE_display_timing extension commands
    if (nameHash == XXH3_vkGetRefreshCycleDurationGOOGLE && !strcmp(name, "vkGetRefreshCycleDurationGOOGLE")) {
        *addr = (void *)GetRefreshCycleDurationGOOGLE;
        return true;
    }
    if (nameHash == XXH3_vkGetPastPresentationTimingGOOGLE && !strcmp(name, "vkGetPastPresentationTimingGOOGLE")) {
        *addr = (void *)GetPastPresentationTimingGOOGLE;
        return true;
    }

    // ---- VK_EXT_discard_rectangles extension commands
    if (nameHash == XXH3_vkCmdSetDiscardRectangleEXT && !strcmp(name, "vkCmdSetDiscardRectangleEXT")) {
        *addr = (void *)CmdSetDiscardRectangleEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDiscardRectangleEnableEXT && !strcmp(name, "vkCmdSetDiscardRectangleEnableEXT")) {
        *addr = (void *)CmdSetDiscardRectangleEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDiscardRectangleModeEXT && !strcmp(name, "vkCmdSetDiscardRectangleModeEXT")) {
        *addr = (void *)CmdSetDiscardRectangleModeEXT;
        return true;
    }

    // ---- VK_EXT_hdr_metadata extension commands
    if (nameHash == XXH3_vkSetHdrMetadataEXT && !strcmp(name, "vkSetHdrMetadataEXT")) {
        *addr = (void *)SetHdrMetadataEXT;
        return true;
    }

    // ---- VK_EXT_debug_utils extension commands
    if (nameHash == XXH3_vkSetDebugUtilsObjectNameEXT && !strcmp(name, "vkSetDebugUtilsObjectNameEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)SetDebugUtilsObjectNameEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkSetDebugUtilsObjectTagEXT && !strcmp(name, "vkSetDebugUtilsObjectTagEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)SetDebugUtilsObjectTagEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkQueueBeginDebugUtilsLabelEXT && !strcmp(name, "vkQueueBeginDebugUtilsLabelEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)QueueBeginDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkQueueEndDebugUtilsLabelEXT && !strcmp(name, "vkQueueEndDebugUtilsLabelEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)QueueEndDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkQueueInsertDebugUtilsLabelEXT && !strcmp(name, "vkQueueInsertDebugUtilsLabelEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)QueueInsertDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginDebugUtilsLabelEXT && !strcmp(name, "vkCmdBeginDebugUtilsLabelEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)CmdBeginDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndDebugUtilsLabelEXT && !strcmp(name, "vkCmdEndDebugUtilsLabelEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)CmdEndDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkCmdInsertDebugUtilsLabelEXT && !strcmp(name, "vkCmdInsertDebugUtilsLabelEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                     ? (void *)CmdInsertDebugUtilsLabelEXT
                     : NULL;
        return true;
    }

    // ---- VK_ANDROID_external_memory_android_hardware_buffer extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    if (nameHash == XXH3_vkGetAndroidHardwareBufferPropertiesANDROID && !strcmp(name, "vkGetAndroidHardwareBufferPropertiesANDROID")) {
        *addr = (void *)GetAndroidHardwareBufferPropertiesANDROID;
        return true;
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    if (nameHash == XXH3_vkGetMemoryAndroidHardwareBufferANDROID && !strcmp(name, "vkGetMemoryAndroidHardwareBufferANDROID")) {
        *addr = (void *)GetMemoryAndroidHardwareBufferANDROID;
        return true;
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_AMD_gpa_interface extension commands
    if (nameHash == XXH3_vkCreateGpaSessionAMD && !strcmp(name, "vkCreateGpaSessionAMD")) {
        *addr = (void *)CreateGpaSessionAMD;
        return true;
    }
    if (nameHash == XXH3_vkDestroyGpaSessionAMD && !strcmp(name, "vkDestroyGpaSessionAMD")) {
        *addr = (void *)DestroyGpaSessionAMD;
        return true;
    }
    if (nameHash == XXH3_vkSetGpaDeviceClockModeAMD && !strcmp(name, "vkSetGpaDeviceClockModeAMD")) {
        *addr = (void *)SetGpaDeviceClockModeAMD;
        return true;
    }
    if (nameHash == XXH3_vkGetGpaDeviceClockInfoAMD && !strcmp(name, "vkGetGpaDeviceClockInfoAMD")) {
        *addr = (void *)GetGpaDeviceClockInfoAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginGpaSessionAMD && !strcmp(name, "vkCmdBeginGpaSessionAMD")) {
        *addr = (void *)CmdBeginGpaSessionAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndGpaSessionAMD && !strcmp(name, "vkCmdEndGpaSessionAMD")) {
        *addr = (void *)CmdEndGpaSessionAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginGpaSampleAMD && !strcmp(name, "vkCmdBeginGpaSampleAMD")) {
        *addr = (void *)CmdBeginGpaSampleAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndGpaSampleAMD && !strcmp(name, "vkCmdEndGpaSampleAMD")) {
        *addr = (void *)CmdEndGpaSampleAMD;
        return true;
    }
    if (nameHash == XXH3_vkGetGpaSessionStatusAMD && !strcmp(name, "vkGetGpaSessionStatusAMD")) {
        *addr = (void *)GetGpaSessionStatusAMD;
        return true;
    }
    if (nameHash == XXH3_vkGetGpaSessionResultsAMD && !strcmp(name, "vkGetGpaSessionResultsAMD")) {
        *addr = (void *)GetGpaSessionResultsAMD;
        return true;
    }
    if (nameHash == XXH3_vkResetGpaSessionAMD && !strcmp(name, "vkResetGpaSessionAMD")) {
        *addr = (void *)ResetGpaSessionAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyGpaSessionResultsAMD && !strcmp(name, "vkCmdCopyGpaSessionResultsAMD")) {
        *addr = (void *)CmdCopyGpaSessionResultsAMD;
        return true;
    }

    // ---- VK_AMDX_shader_enqueue extension commands
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCreateExecutionGraphPipelinesAMDX && !strcmp(name, "vkCreateExecutionGraphPipelinesAMDX")) {
        *addr = (void *)CreateExecutionGraphPipelinesAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkGetExecutionGraphPipelineScratchSizeAMDX && !strcmp(name, "vkGetExecutionGraphPipelineScratchSizeAMDX")) {
        *addr = (void *)GetExecutionGraphPipelineScratchSizeAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkGetExecutionGraphPipelineNodeIndexAMDX && !strcmp(name, "vkGetExecutionGraphPipelineNodeIndexAMDX")) {
        *addr = (void *)GetExecutionGraphPipelineNodeIndexAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdInitializeGraphScratchMemoryAMDX && !strcmp(name, "vkCmdInitializeGraphScratchMemoryAMDX")) {
        *addr = (void *)CmdInitializeGraphScratchMemoryAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdDispatchGraphAMDX && !strcmp(name, "vkCmdDispatchGraphAMDX")) {
        *addr = (void *)CmdDispatchGraphAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdDispatchGraphIndirectAMDX && !strcmp(name, "vkCmdDispatchGraphIndirectAMDX")) {
        *addr = (void *)CmdDispatchGraphIndirectAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdDispatchGraphIndirectCountAMDX && !strcmp(name, "vkCmdDispatchGraphIndirectCountAMDX")) {
        *addr = (void *)CmdDispatchGraphIndirectCountAMDX;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS

    // ---- VK_EXT_descriptor_heap extension commands
    if (nameHash == XXH3_vkWriteSamplerDescriptorsEXT && !strcmp(name, "vkWriteSamplerDescriptorsEXT")) {
        *addr = (void *)WriteSamplerDescriptorsEXT;
        return true;
    }
    if (nameHash == XXH3_vkWriteResourceDescriptorsEXT && !strcmp(name, "vkWriteResourceDescriptorsEXT")) {
        *addr = (void *)WriteResourceDescriptorsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindSamplerHeapEXT && !strcmp(name, "vkCmdBindSamplerHeapEXT")) {
        *addr = (void *)CmdBindSamplerHeapEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindResourceHeapEXT && !strcmp(name, "vkCmdBindResourceHeapEXT")) {
        *addr = (void *)CmdBindResourceHeapEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdPushDataEXT && !strcmp(name, "vkCmdPushDataEXT")) {
        *addr = (void *)CmdPushDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetImageOpaqueCaptureDataEXT && !strcmp(name, "vkGetImageOpaqueCaptureDataEXT")) {
        *addr = (void *)GetImageOpaqueCaptureDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceDescriptorSizeEXT && !strcmp(name, "vkGetPhysicalDeviceDescriptorSizeEXT")) {
        *addr = (void *)GetPhysicalDeviceDescriptorSizeEXT;
        return true;
    }
    if (nameHash == XXH3_vkRegisterCustomBorderColorEXT && !strcmp(name, "vkRegisterCustomBorderColorEXT")) {
        *addr = (void *)RegisterCustomBorderColorEXT;
        return true;
    }
    if (nameHash == XXH3_vkUnregisterCustomBorderColorEXT && !strcmp(name, "vkUnregisterCustomBorderColorEXT")) {
        *addr = (void *)UnregisterCustomBorderColorEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetTensorOpaqueCaptureDataARM && !strcmp(name, "vkGetTensorOpaqueCaptureDataARM")) {
        *addr = (void *)GetTensorOpaqueCaptureDataARM;
        return true;
    }

    // ---- VK_EXT_sample_locations extension commands
    if (nameHash == XXH3_vkCmdSetSampleLocationsEXT && !strcmp(name, "vkCmdSetSampleLocationsEXT")) {
        *addr = (void *)CmdSetSampleLocationsEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceMultisamplePropertiesEXT && !strcmp(name, "vkGetPhysicalDeviceMultisamplePropertiesEXT")) {
        *addr = (void *)GetPhysicalDeviceMultisamplePropertiesEXT;
        return true;
    }

    // ---- VK_EXT_image_drm_format_modifier extension commands
    if (nameHash == XXH3_vkGetImageDrmFormatModifierPropertiesEXT && !strcmp(name, "vkGetImageDrmFormatModifierPropertiesEXT")) {
        *addr = (void *)GetImageDrmFormatModifierPropertiesEXT;
        return true;
    }

    // ---- VK_EXT_validation_cache extension commands
    if (nameHash == XXH3_vkCreateValidationCacheEXT && !strcmp(name, "vkCreateValidationCacheEXT")) {
        *addr = (void *)CreateValidationCacheEXT;
        return true;
    }
    if (nameHash == XXH3_vkDestroyValidationCacheEXT && !strcmp(name, "vkDestroyValidationCacheEXT")) {
        *addr = (void *)DestroyValidationCacheEXT;
        return true;
    }
    if (nameHash == XXH3_vkMergeValidationCachesEXT && !strcmp(name, "vkMergeValidationCachesEXT")) {
        *addr = (void *)MergeValidationCachesEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetValidationCacheDataEXT && !strcmp(name, "vkGetValidationCacheDataEXT")) {
        *addr = (void *)GetValidationCacheDataEXT;
        return true;
    }

    // ---- VK_NV_shading_rate_image extension commands
    if (nameHash == XXH3_vkCmdBindShadingRateImageNV && !strcmp(name, "vkCmdBindShadingRateImageNV")) {
        *addr = (void *)CmdBindShadingRateImageNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetViewportShadingRatePaletteNV && !strcmp(name, "vkCmdSetViewportShadingRatePaletteNV")) {
        *addr = (void *)CmdSetViewportShadingRatePaletteNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoarseSampleOrderNV && !strcmp(name, "vkCmdSetCoarseSampleOrderNV")) {
        *addr = (void *)CmdSetCoarseSampleOrderNV;
        return true;
    }

    // ---- VK_NV_ray_tracing extension commands
    if (nameHash == XXH3_vkCreateAccelerationStructureNV && !strcmp(name, "vkCreateAccelerationStructureNV")) {
        *addr = (void *)CreateAccelerationStructureNV;
        return true;
    }
    if (nameHash == XXH3_vkDestroyAccelerationStructureNV && !strcmp(name, "vkDestroyAccelerationStructureNV")) {
        *addr = (void *)DestroyAccelerationStructureNV;
        return true;
    }
    if (nameHash == XXH3_vkGetAccelerationStructureMemoryRequirementsNV && !strcmp(name, "vkGetAccelerationStructureMemoryRequirementsNV")) {
        *addr = (void *)GetAccelerationStructureMemoryRequirementsNV;
        return true;
    }
    if (nameHash == XXH3_vkBindAccelerationStructureMemoryNV && !strcmp(name, "vkBindAccelerationStructureMemoryNV")) {
        *addr = (void *)BindAccelerationStructureMemoryNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdBuildAccelerationStructureNV && !strcmp(name, "vkCmdBuildAccelerationStructureNV")) {
        *addr = (void *)CmdBuildAccelerationStructureNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyAccelerationStructureNV && !strcmp(name, "vkCmdCopyAccelerationStructureNV")) {
        *addr = (void *)CmdCopyAccelerationStructureNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdTraceRaysNV && !strcmp(name, "vkCmdTraceRaysNV")) {
        *addr = (void *)CmdTraceRaysNV;
        return true;
    }
    if (nameHash == XXH3_vkCreateRayTracingPipelinesNV && !strcmp(name, "vkCreateRayTracingPipelinesNV")) {
        *addr = (void *)CreateRayTracingPipelinesNV;
        return true;
    }

    // ---- VK_KHR_ray_tracing_pipeline extension commands
    if (nameHash == XXH3_vkGetRayTracingShaderGroupHandlesKHR && !strcmp(name, "vkGetRayTracingShaderGroupHandlesKHR")) {
        *addr = (void *)GetRayTracingShaderGroupHandlesKHR;
        return true;
    }

    // ---- VK_NV_ray_tracing extension commands
    if (nameHash == XXH3_vkGetRayTracingShaderGroupHandlesNV && !strcmp(name, "vkGetRayTracingShaderGroupHandlesNV")) {
        *addr = (void *)GetRayTracingShaderGroupHandlesNV;
        return true;
    }
    if (nameHash == XXH3_vkGetAccelerationStructureHandleNV && !strcmp(name, "vkGetAccelerationStructureHandleNV")) {
        *addr = (void *)GetAccelerationStructureHandleNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdWriteAccelerationStructuresPropertiesNV && !strcmp(name, "vkCmdWriteAccelerationStructuresPropertiesNV")) {
        *addr = (void *)CmdWriteAccelerationStructuresPropertiesNV;
        return true;
    }
    if (nameHash == XXH3_vkCompileDeferredNV && !strcmp(name, "vkCompileDeferredNV")) {
        *addr = (void *)CompileDeferredNV;
        return true;
    }

    // ---- VK_EXT_external_memory_host extension commands
    if (nameHash == XXH3_vkGetMemoryHostPointerPropertiesEXT && !strcmp(name, "vkGetMemoryHostPointerPropertiesEXT")) {
        *addr = (void *)GetMemoryHostPointerPropertiesEXT;
        return true;
    }

    // ---- VK_AMD_buffer_marker extension commands
    if (nameHash == XXH3_vkCmdWriteBufferMarkerAMD && !strcmp(name, "vkCmdWriteBufferMarkerAMD")) {
        *addr = (void *)CmdWriteBufferMarkerAMD;
        return true;
    }
    if (nameHash == XXH3_vkCmdWriteBufferMarker2AMD && !strcmp(name, "vkCmdWriteBufferMarker2AMD")) {
        *addr = (void *)CmdWriteBufferMarker2AMD;
        return true;
    }

    // ---- VK_EXT_calibrated_timestamps extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT && !strcmp(name, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT")) {
        *addr = (void *)GetPhysicalDeviceCalibrateableTimeDomainsEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetCalibratedTimestampsEXT && !strcmp(name, "vkGetCalibratedTimestampsEXT")) {
        *addr = (void *)GetCalibratedTimestampsEXT;
        return true;
    }

    // ---- VK_NV_mesh_shader extension commands
    if (nameHash == XXH3_vkCmdDrawMeshTasksNV && !strcmp(name, "vkCmdDrawMeshTasksNV")) {
        *addr = (void *)CmdDrawMeshTasksNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectNV && !strcmp(name, "vkCmdDrawMeshTasksIndirectNV")) {
        *addr = (void *)CmdDrawMeshTasksIndirectNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectCountNV && !strcmp(name, "vkCmdDrawMeshTasksIndirectCountNV")) {
        *addr = (void *)CmdDrawMeshTasksIndirectCountNV;
        return true;
    }

    // ---- VK_NV_scissor_exclusive extension commands
    if (nameHash == XXH3_vkCmdSetExclusiveScissorEnableNV && !strcmp(name, "vkCmdSetExclusiveScissorEnableNV")) {
        *addr = (void *)CmdSetExclusiveScissorEnableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetExclusiveScissorNV && !strcmp(name, "vkCmdSetExclusiveScissorNV")) {
        *addr = (void *)CmdSetExclusiveScissorNV;
        return true;
    }

    // ---- VK_NV_device_diagnostic_checkpoints extension commands
    if (nameHash == XXH3_vkCmdSetCheckpointNV && !strcmp(name, "vkCmdSetCheckpointNV")) {
        *addr = (void *)CmdSetCheckpointNV;
        return true;
    }
    if (nameHash == XXH3_vkGetQueueCheckpointDataNV && !strcmp(name, "vkGetQueueCheckpointDataNV")) {
        *addr = (void *)GetQueueCheckpointDataNV;
        return true;
    }
    if (nameHash == XXH3_vkGetQueueCheckpointData2NV && !strcmp(name, "vkGetQueueCheckpointData2NV")) {
        *addr = (void *)GetQueueCheckpointData2NV;
        return true;
    }

    // ---- VK_EXT_present_timing extension commands
    if (nameHash == XXH3_vkSetSwapchainPresentTimingQueueSizeEXT && !strcmp(name, "vkSetSwapchainPresentTimingQueueSizeEXT")) {
        *addr = (void *)SetSwapchainPresentTimingQueueSizeEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetSwapchainTimingPropertiesEXT && !strcmp(name, "vkGetSwapchainTimingPropertiesEXT")) {
        *addr = (void *)GetSwapchainTimingPropertiesEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetSwapchainTimeDomainPropertiesEXT && !strcmp(name, "vkGetSwapchainTimeDomainPropertiesEXT")) {
        *addr = (void *)GetSwapchainTimeDomainPropertiesEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetPastPresentationTimingEXT && !strcmp(name, "vkGetPastPresentationTimingEXT")) {
        *addr = (void *)GetPastPresentationTimingEXT;
        return true;
    }

    // ---- VK_INTEL_performance_query extension commands
    if (nameHash == XXH3_vkInitializePerformanceApiINTEL && !strcmp(name, "vkInitializePerformanceApiINTEL")) {
        *addr = (void *)InitializePerformanceApiINTEL;
        return true;
    }
    if (nameHash == XXH3_vkUninitializePerformanceApiINTEL && !strcmp(name, "vkUninitializePerformanceApiINTEL")) {
        *addr = (void *)UninitializePerformanceApiINTEL;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetPerformanceMarkerINTEL && !strcmp(name, "vkCmdSetPerformanceMarkerINTEL")) {
        *addr = (void *)CmdSetPerformanceMarkerINTEL;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetPerformanceStreamMarkerINTEL && !strcmp(name, "vkCmdSetPerformanceStreamMarkerINTEL")) {
        *addr = (void *)CmdSetPerformanceStreamMarkerINTEL;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetPerformanceOverrideINTEL && !strcmp(name, "vkCmdSetPerformanceOverrideINTEL")) {
        *addr = (void *)CmdSetPerformanceOverrideINTEL;
        return true;
    }
    if (nameHash == XXH3_vkAcquirePerformanceConfigurationINTEL && !strcmp(name, "vkAcquirePerformanceConfigurationINTEL")) {
        *addr = (void *)AcquirePerformanceConfigurationINTEL;
        return true;
    }
    if (nameHash == XXH3_vkReleasePerformanceConfigurationINTEL && !strcmp(name, "vkReleasePerformanceConfigurationINTEL")) {
        *addr = (void *)ReleasePerformanceConfigurationINTEL;
        return true;
    }
    if (nameHash == XXH3_vkQueueSetPerformanceConfigurationINTEL && !strcmp(name, "vkQueueSetPerformanceConfigurationINTEL")) {
        *addr = (void *)QueueSetPerformanceConfigurationINTEL;
        return true;
    }
    if (nameHash == XXH3_vkGetPerformanceParameterINTEL && !strcmp(name, "vkGetPerformanceParameterINTEL")) {
        *addr = (void *)GetPerformanceParameterINTEL;
        return true;
    }

    // ---- VK_AMD_display_native_hdr extension commands
    if (nameHash == XXH3_vkSetLocalDimmingAMD && !strcmp(name, "vkSetLocalDimmingAMD")) {
        *addr = (void *)SetLocalDimmingAMD;
        return true;
    }

    // ---- VK_EXT_buffer_device_address extension commands
    if (nameHash == XXH3_vkGetBufferDeviceAddressEXT && !strcmp(name, "vkGetBufferDeviceAddressEXT")) {
        *addr = (void *)GetBufferDeviceAddressEXT;
        return true;
    }

    // ---- VK_EXT_tooling_info extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceToolPropertiesEXT && !strcmp(name, "vkGetPhysicalDeviceToolPropertiesEXT")) {
        *addr = (void *)GetPhysicalDeviceToolPropertiesEXT;
        return true;
    }

    // ---- VK_NV_cooperative_matrix extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV")) {
        *addr = (void *)GetPhysicalDeviceCooperativeMatrixPropertiesNV;
        return true;
    }

    // ---- VK_NV_coverage_reduction_mode extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV && !strcmp(name, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV")) {
        *addr = (void *)GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
        return true;
    }

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetPhysicalDeviceSurfacePresentModes2EXT && !strcmp(name, "vkGetPhysicalDeviceSurfacePresentModes2EXT")) {
        *addr = (void *)GetPhysicalDeviceSurfacePresentModes2EXT;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkAcquireFullScreenExclusiveModeEXT && !strcmp(name, "vkAcquireFullScreenExclusiveModeEXT")) {
        *addr = (void *)AcquireFullScreenExclusiveModeEXT;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkReleaseFullScreenExclusiveModeEXT && !strcmp(name, "vkReleaseFullScreenExclusiveModeEXT")) {
        *addr = (void *)ReleaseFullScreenExclusiveModeEXT;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetDeviceGroupSurfacePresentModes2EXT && !strcmp(name, "vkGetDeviceGroupSurfacePresentModes2EXT")) {
        *addr = (void *)GetDeviceGroupSurfacePresentModes2EXT;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_line_rasterization extension commands
    if (nameHash == XXH3_vkCmdSetLineStippleEXT && !strcmp(name, "vkCmdSetLineStippleEXT")) {
        *addr = (void *)CmdSetLineStippleEXT;
        return true;
    }

    // ---- VK_EXT_host_query_reset extension commands
    if (nameHash == XXH3_vkResetQueryPoolEXT && !strcmp(name, "vkResetQueryPoolEXT")) {
        *addr = (void *)ResetQueryPoolEXT;
        return true;
    }

    // ---- VK_EXT_extended_dynamic_state extension commands
    if (nameHash == XXH3_vkCmdSetCullModeEXT && !strcmp(name, "vkCmdSetCullModeEXT")) {
        *addr = (void *)CmdSetCullModeEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetFrontFaceEXT && !strcmp(name, "vkCmdSetFrontFaceEXT")) {
        *addr = (void *)CmdSetFrontFaceEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetPrimitiveTopologyEXT && !strcmp(name, "vkCmdSetPrimitiveTopologyEXT")) {
        *addr = (void *)CmdSetPrimitiveTopologyEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetViewportWithCountEXT && !strcmp(name, "vkCmdSetViewportWithCountEXT")) {
        *addr = (void *)CmdSetViewportWithCountEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetScissorWithCountEXT && !strcmp(name, "vkCmdSetScissorWithCountEXT")) {
        *addr = (void *)CmdSetScissorWithCountEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindVertexBuffers2EXT && !strcmp(name, "vkCmdBindVertexBuffers2EXT")) {
        *addr = (void *)CmdBindVertexBuffers2EXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthTestEnableEXT && !strcmp(name, "vkCmdSetDepthTestEnableEXT")) {
        *addr = (void *)CmdSetDepthTestEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthWriteEnableEXT && !strcmp(name, "vkCmdSetDepthWriteEnableEXT")) {
        *addr = (void *)CmdSetDepthWriteEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthCompareOpEXT && !strcmp(name, "vkCmdSetDepthCompareOpEXT")) {
        *addr = (void *)CmdSetDepthCompareOpEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthBoundsTestEnableEXT && !strcmp(name, "vkCmdSetDepthBoundsTestEnableEXT")) {
        *addr = (void *)CmdSetDepthBoundsTestEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetStencilTestEnableEXT && !strcmp(name, "vkCmdSetStencilTestEnableEXT")) {
        *addr = (void *)CmdSetStencilTestEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetStencilOpEXT && !strcmp(name, "vkCmdSetStencilOpEXT")) {
        *addr = (void *)CmdSetStencilOpEXT;
        return true;
    }

    // ---- VK_EXT_host_image_copy extension commands
    if (nameHash == XXH3_vkCopyMemoryToImageEXT && !strcmp(name, "vkCopyMemoryToImageEXT")) {
        *addr = (void *)CopyMemoryToImageEXT;
        return true;
    }
    if (nameHash == XXH3_vkCopyImageToMemoryEXT && !strcmp(name, "vkCopyImageToMemoryEXT")) {
        *addr = (void *)CopyImageToMemoryEXT;
        return true;
    }
    if (nameHash == XXH3_vkCopyImageToImageEXT && !strcmp(name, "vkCopyImageToImageEXT")) {
        *addr = (void *)CopyImageToImageEXT;
        return true;
    }
    if (nameHash == XXH3_vkTransitionImageLayoutEXT && !strcmp(name, "vkTransitionImageLayoutEXT")) {
        *addr = (void *)TransitionImageLayoutEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetImageSubresourceLayout2EXT && !strcmp(name, "vkGetImageSubresourceLayout2EXT")) {
        *addr = (void *)GetImageSubresourceLayout2EXT;
        return true;
    }

    // ---- VK_EXT_swapchain_maintenance1 extension commands
    if (nameHash == XXH3_vkReleaseSwapchainImagesEXT && !strcmp(name, "vkReleaseSwapchainImagesEXT")) {
        *addr = (void *)ReleaseSwapchainImagesEXT;
        return true;
    }

    // ---- VK_NV_device_generated_commands extension commands
    if (nameHash == XXH3_vkGetGeneratedCommandsMemoryRequirementsNV && !strcmp(name, "vkGetGeneratedCommandsMemoryRequirementsNV")) {
        *addr = (void *)GetGeneratedCommandsMemoryRequirementsNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdPreprocessGeneratedCommandsNV && !strcmp(name, "vkCmdPreprocessGeneratedCommandsNV")) {
        *addr = (void *)CmdPreprocessGeneratedCommandsNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdExecuteGeneratedCommandsNV && !strcmp(name, "vkCmdExecuteGeneratedCommandsNV")) {
        *addr = (void *)CmdExecuteGeneratedCommandsNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindPipelineShaderGroupNV && !strcmp(name, "vkCmdBindPipelineShaderGroupNV")) {
        *addr = (void *)CmdBindPipelineShaderGroupNV;
        return true;
    }
    if (nameHash == XXH3_vkCreateIndirectCommandsLayoutNV && !strcmp(name, "vkCreateIndirectCommandsLayoutNV")) {
        *addr = (void *)CreateIndirectCommandsLayoutNV;
        return true;
    }
    if (nameHash == XXH3_vkDestroyIndirectCommandsLayoutNV && !strcmp(name, "vkDestroyIndirectCommandsLayoutNV")) {
        *addr = (void *)DestroyIndirectCommandsLayoutNV;
        return true;
    }

    // ---- VK_EXT_depth_bias_control extension commands
    if (nameHash == XXH3_vkCmdSetDepthBias2EXT && !strcmp(name, "vkCmdSetDepthBias2EXT")) {
        *addr = (void *)CmdSetDepthBias2EXT;
        return true;
    }

    // ---- VK_EXT_acquire_drm_display extension commands
    if (nameHash == XXH3_vkAcquireDrmDisplayEXT && !strcmp(name, "vkAcquireDrmDisplayEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_acquire_drm_display == 1)
                     ? (void *)AcquireDrmDisplayEXT
                     : NULL;
        return true;
    }
    if (nameHash == XXH3_vkGetDrmDisplayEXT && !strcmp(name, "vkGetDrmDisplayEXT")) {
        *addr = (ptr_instance->enabled_extensions.ext_acquire_drm_display == 1)
                     ? (void *)GetDrmDisplayEXT
                     : NULL;
        return true;
    }

    // ---- VK_EXT_private_data extension commands
    if (nameHash == XXH3_vkCreatePrivateDataSlotEXT && !strcmp(name, "vkCreatePrivateDataSlotEXT")) {
        *addr = (void *)CreatePrivateDataSlotEXT;
        return true;
    }
    if (nameHash == XXH3_vkDestroyPrivateDataSlotEXT && !strcmp(name, "vkDestroyPrivateDataSlotEXT")) {
        *addr = (void *)DestroyPrivateDataSlotEXT;
        return true;
    }
    if (nameHash == XXH3_vkSetPrivateDataEXT && !strcmp(name, "vkSetPrivateDataEXT")) {
        *addr = (void *)SetPrivateDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetPrivateDataEXT && !strcmp(name, "vkGetPrivateDataEXT")) {
        *addr = (void *)GetPrivateDataEXT;
        return true;
    }

    // ---- VK_QCOM_queue_perf_hint extension commands
    if (nameHash == XXH3_vkQueueSetPerfHintQCOM && !strcmp(name, "vkQueueSetPerfHintQCOM")) {
        *addr = (void *)QueueSetPerfHintQCOM;
        return true;
    }

    // ---- VK_NV_cuda_kernel_launch extension commands
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCreateCudaModuleNV && !strcmp(name, "vkCreateCudaModuleNV")) {
        *addr = (void *)CreateCudaModuleNV;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkGetCudaModuleCacheNV && !strcmp(name, "vkGetCudaModuleCacheNV")) {
        *addr = (void *)GetCudaModuleCacheNV;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCreateCudaFunctionNV && !strcmp(name, "vkCreateCudaFunctionNV")) {
        *addr = (void *)CreateCudaFunctionNV;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkDestroyCudaModuleNV && !strcmp(name, "vkDestroyCudaModuleNV")) {
        *addr = (void *)DestroyCudaModuleNV;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkDestroyCudaFunctionNV && !strcmp(name, "vkDestroyCudaFunctionNV")) {
        *addr = (void *)DestroyCudaFunctionNV;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    if (nameHash == XXH3_vkCmdCudaLaunchKernelNV && !strcmp(name, "vkCmdCudaLaunchKernelNV")) {
        *addr = (void *)CmdCudaLaunchKernelNV;
        return true;
    }
#endif // VK_ENABLE_BETA_EXTENSIONS

    // ---- VK_QCOM_tile_shading extension commands
    if (nameHash == XXH3_vkCmdDispatchTileQCOM && !strcmp(name, "vkCmdDispatchTileQCOM")) {
        *addr = (void *)CmdDispatchTileQCOM;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginPerTileExecutionQCOM && !strcmp(name, "vkCmdBeginPerTileExecutionQCOM")) {
        *addr = (void *)CmdBeginPerTileExecutionQCOM;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndPerTileExecutionQCOM && !strcmp(name, "vkCmdEndPerTileExecutionQCOM")) {
        *addr = (void *)CmdEndPerTileExecutionQCOM;
        return true;
    }

    // ---- VK_NV_low_latency extension commands
    if (nameHash == XXH3_vkSetLatencySleepModeLegacyNV && !strcmp(name, "vkSetLatencySleepModeLegacyNV")) {
        *addr = (void *)SetLatencySleepModeLegacyNV;
        return true;
    }
    if (nameHash == XXH3_vkLatencySleepLegacyNV && !strcmp(name, "vkLatencySleepLegacyNV")) {
        *addr = (void *)LatencySleepLegacyNV;
        return true;
    }
    if (nameHash == XXH3_vkSetLatencyMarkerLegacyNV && !strcmp(name, "vkSetLatencyMarkerLegacyNV")) {
        *addr = (void *)SetLatencyMarkerLegacyNV;
        return true;
    }
    if (nameHash == XXH3_vkGetLatencyTimingsLegacyNV && !strcmp(name, "vkGetLatencyTimingsLegacyNV")) {
        *addr = (void *)GetLatencyTimingsLegacyNV;
        return true;
    }
    if (nameHash == XXH3_vkQueueNotifyOutOfBandLegacyNV && !strcmp(name, "vkQueueNotifyOutOfBandLegacyNV")) {
        *addr = (void *)QueueNotifyOutOfBandLegacyNV;
        return true;
    }
    if (nameHash == XXH3_vkGetSleepStatusLegacyNV && !strcmp(name, "vkGetSleepStatusLegacyNV")) {
        *addr = (void *)GetSleepStatusLegacyNV;
        return true;
    }
    if (nameHash == XXH3_vkShutdownLatencyDeviceLegacyNV && !strcmp(name, "vkShutdownLatencyDeviceLegacyNV")) {
        *addr = (void *)ShutdownLatencyDeviceLegacyNV;
        return true;
    }

    // ---- VK_EXT_metal_objects extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkExportMetalObjectsEXT && !strcmp(name, "vkExportMetalObjectsEXT")) {
        *addr = (void *)ExportMetalObjectsEXT;
        return true;
    }
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_descriptor_buffer extension commands
    if (nameHash == XXH3_vkGetDescriptorSetLayoutSizeEXT && !strcmp(name, "vkGetDescriptorSetLayoutSizeEXT")) {
        *addr = (void *)GetDescriptorSetLayoutSizeEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetDescriptorSetLayoutBindingOffsetEXT && !strcmp(name, "vkGetDescriptorSetLayoutBindingOffsetEXT")) {
        *addr = (void *)GetDescriptorSetLayoutBindingOffsetEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetDescriptorEXT && !strcmp(name, "vkGetDescriptorEXT")) {
        *addr = (void *)GetDescriptorEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindDescriptorBuffersEXT && !strcmp(name, "vkCmdBindDescriptorBuffersEXT")) {
        *addr = (void *)CmdBindDescriptorBuffersEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDescriptorBufferOffsetsEXT && !strcmp(name, "vkCmdSetDescriptorBufferOffsetsEXT")) {
        *addr = (void *)CmdSetDescriptorBufferOffsetsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindDescriptorBufferEmbeddedSamplersEXT && !strcmp(name, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT")) {
        *addr = (void *)CmdBindDescriptorBufferEmbeddedSamplersEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetBufferOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetBufferOpaqueCaptureDescriptorDataEXT")) {
        *addr = (void *)GetBufferOpaqueCaptureDescriptorDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetImageOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetImageOpaqueCaptureDescriptorDataEXT")) {
        *addr = (void *)GetImageOpaqueCaptureDescriptorDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetImageViewOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetImageViewOpaqueCaptureDescriptorDataEXT")) {
        *addr = (void *)GetImageViewOpaqueCaptureDescriptorDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetSamplerOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetSamplerOpaqueCaptureDescriptorDataEXT")) {
        *addr = (void *)GetSamplerOpaqueCaptureDescriptorDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT && !strcmp(name, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT")) {
        *addr = (void *)GetAccelerationStructureOpaqueCaptureDescriptorDataEXT;
        return true;
    }

    // ---- VK_NV_fragment_shading_rate_enums extension commands
    if (nameHash == XXH3_vkCmdSetFragmentShadingRateEnumNV && !strcmp(name, "vkCmdSetFragmentShadingRateEnumNV")) {
        *addr = (void *)CmdSetFragmentShadingRateEnumNV;
        return true;
    }

    // ---- VK_EXT_device_fault extension commands
    if (nameHash == XXH3_vkGetDeviceFaultInfoEXT && !strcmp(name, "vkGetDeviceFaultInfoEXT")) {
        *addr = (void *)GetDeviceFaultInfoEXT;
        return true;
    }

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkAcquireWinrtDisplayNV && !strcmp(name, "vkAcquireWinrtDisplayNV")) {
        *addr = (void *)AcquireWinrtDisplayNV;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    if (nameHash == XXH3_vkGetWinrtDisplayNV && !strcmp(name, "vkGetWinrtDisplayNV")) {
        *addr = (void *)GetWinrtDisplayNV;
        return true;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_vertex_input_dynamic_state extension commands
    if (nameHash == XXH3_vkCmdSetVertexInputEXT && !strcmp(name, "vkCmdSetVertexInputEXT")) {
        *addr = (void *)CmdSetVertexInputEXT;
        return true;
    }

    // ---- VK_FUCHSIA_external_memory extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetMemoryZirconHandleFUCHSIA && !strcmp(name, "vkGetMemoryZirconHandleFUCHSIA")) {
        *addr = (void *)GetMemoryZirconHandleFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetMemoryZirconHandlePropertiesFUCHSIA && !strcmp(name, "vkGetMemoryZirconHandlePropertiesFUCHSIA")) {
        *addr = (void *)GetMemoryZirconHandlePropertiesFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_FUCHSIA_external_semaphore extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkImportSemaphoreZirconHandleFUCHSIA && !strcmp(name, "vkImportSemaphoreZirconHandleFUCHSIA")) {
        *addr = (void *)ImportSemaphoreZirconHandleFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetSemaphoreZirconHandleFUCHSIA && !strcmp(name, "vkGetSemaphoreZirconHandleFUCHSIA")) {
        *addr = (void *)GetSemaphoreZirconHandleFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_FUCHSIA_buffer_collection extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkCreateBufferCollectionFUCHSIA && !strcmp(name, "vkCreateBufferCollectionFUCHSIA")) {
        *addr = (void *)CreateBufferCollectionFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkSetBufferCollectionImageConstraintsFUCHSIA && !strcmp(name, "vkSetBufferCollectionImageConstraintsFUCHSIA")) {
        *addr = (void *)SetBufferCollectionImageConstraintsFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkSetBufferCollectionBufferConstraintsFUCHSIA && !strcmp(name, "vkSetBufferCollectionBufferConstraintsFUCHSIA")) {
        *addr = (void *)SetBufferCollectionBufferConstraintsFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkDestroyBufferCollectionFUCHSIA && !strcmp(name, "vkDestroyBufferCollectionFUCHSIA")) {
        *addr = (void *)DestroyBufferCollectionFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_FUCHSIA)
    if (nameHash == XXH3_vkGetBufferCollectionPropertiesFUCHSIA && !strcmp(name, "vkGetBufferCollectionPropertiesFUCHSIA")) {
        *addr = (void *)GetBufferCollectionPropertiesFUCHSIA;
        return true;
    }
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_HUAWEI_subpass_shading extension commands
    if (nameHash == XXH3_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI && !strcmp(name, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI")) {
        *addr = (void *)GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI;
        return true;
    }
    if (nameHash == XXH3_vkCmdSubpassShadingHUAWEI && !strcmp(name, "vkCmdSubpassShadingHUAWEI")) {
        *addr = (void *)CmdSubpassShadingHUAWEI;
        return true;
    }

    // ---- VK_HUAWEI_invocation_mask extension commands
    if (nameHash == XXH3_vkCmdBindInvocationMaskHUAWEI && !strcmp(name, "vkCmdBindInvocationMaskHUAWEI")) {
        *addr = (void *)CmdBindInvocationMaskHUAWEI;
        return true;
    }

    // ---- VK_NV_external_memory_rdma extension commands
    if (nameHash == XXH3_vkGetMemoryRemoteAddressNV && !strcmp(name, "vkGetMemoryRemoteAddressNV")) {
        *addr = (void *)GetMemoryRemoteAddressNV;
        return true;
    }

    // ---- VK_EXT_pipeline_properties extension commands
    if (nameHash == XXH3_vkGetPipelinePropertiesEXT && !strcmp(name, "vkGetPipelinePropertiesEXT")) {
        *addr = (void *)GetPipelinePropertiesEXT;
        return true;
    }

    // ---- VK_EXT_extended_dynamic_state2 extension commands
    if (nameHash == XXH3_vkCmdSetPatchControlPointsEXT && !strcmp(name, "vkCmdSetPatchControlPointsEXT")) {
        *addr = (void *)CmdSetPatchControlPointsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetRasterizerDiscardEnableEXT && !strcmp(name, "vkCmdSetRasterizerDiscardEnableEXT")) {
        *addr = (void *)CmdSetRasterizerDiscardEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthBiasEnableEXT && !strcmp(name, "vkCmdSetDepthBiasEnableEXT")) {
        *addr = (void *)CmdSetDepthBiasEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetLogicOpEXT && !strcmp(name, "vkCmdSetLogicOpEXT")) {
        *addr = (void *)CmdSetLogicOpEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetPrimitiveRestartEnableEXT && !strcmp(name, "vkCmdSetPrimitiveRestartEnableEXT")) {
        *addr = (void *)CmdSetPrimitiveRestartEnableEXT;
        return true;
    }

    // ---- VK_EXT_color_write_enable extension commands
    if (nameHash == XXH3_vkCmdSetColorWriteEnableEXT && !strcmp(name, "vkCmdSetColorWriteEnableEXT")) {
        *addr = (void *)CmdSetColorWriteEnableEXT;
        return true;
    }

    // ---- VK_EXT_multi_draw extension commands
    if (nameHash == XXH3_vkCmdDrawMultiEXT && !strcmp(name, "vkCmdDrawMultiEXT")) {
        *addr = (void *)CmdDrawMultiEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMultiIndexedEXT && !strcmp(name, "vkCmdDrawMultiIndexedEXT")) {
        *addr = (void *)CmdDrawMultiIndexedEXT;
        return true;
    }

    // ---- VK_EXT_opacity_micromap extension commands
    if (nameHash == XXH3_vkCreateMicromapEXT && !strcmp(name, "vkCreateMicromapEXT")) {
        *addr = (void *)CreateMicromapEXT;
        return true;
    }
    if (nameHash == XXH3_vkDestroyMicromapEXT && !strcmp(name, "vkDestroyMicromapEXT")) {
        *addr = (void *)DestroyMicromapEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBuildMicromapsEXT && !strcmp(name, "vkCmdBuildMicromapsEXT")) {
        *addr = (void *)CmdBuildMicromapsEXT;
        return true;
    }
    if (nameHash == XXH3_vkBuildMicromapsEXT && !strcmp(name, "vkBuildMicromapsEXT")) {
        *addr = (void *)BuildMicromapsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCopyMicromapEXT && !strcmp(name, "vkCopyMicromapEXT")) {
        *addr = (void *)CopyMicromapEXT;
        return true;
    }
    if (nameHash == XXH3_vkCopyMicromapToMemoryEXT && !strcmp(name, "vkCopyMicromapToMemoryEXT")) {
        *addr = (void *)CopyMicromapToMemoryEXT;
        return true;
    }
    if (nameHash == XXH3_vkCopyMemoryToMicromapEXT && !strcmp(name, "vkCopyMemoryToMicromapEXT")) {
        *addr = (void *)CopyMemoryToMicromapEXT;
        return true;
    }
    if (nameHash == XXH3_vkWriteMicromapsPropertiesEXT && !strcmp(name, "vkWriteMicromapsPropertiesEXT")) {
        *addr = (void *)WriteMicromapsPropertiesEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMicromapEXT && !strcmp(name, "vkCmdCopyMicromapEXT")) {
        *addr = (void *)CmdCopyMicromapEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMicromapToMemoryEXT && !strcmp(name, "vkCmdCopyMicromapToMemoryEXT")) {
        *addr = (void *)CmdCopyMicromapToMemoryEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMemoryToMicromapEXT && !strcmp(name, "vkCmdCopyMemoryToMicromapEXT")) {
        *addr = (void *)CmdCopyMemoryToMicromapEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdWriteMicromapsPropertiesEXT && !strcmp(name, "vkCmdWriteMicromapsPropertiesEXT")) {
        *addr = (void *)CmdWriteMicromapsPropertiesEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceMicromapCompatibilityEXT && !strcmp(name, "vkGetDeviceMicromapCompatibilityEXT")) {
        *addr = (void *)GetDeviceMicromapCompatibilityEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetMicromapBuildSizesEXT && !strcmp(name, "vkGetMicromapBuildSizesEXT")) {
        *addr = (void *)GetMicromapBuildSizesEXT;
        return true;
    }

    // ---- VK_HUAWEI_cluster_culling_shader extension commands
    if (nameHash == XXH3_vkCmdDrawClusterHUAWEI && !strcmp(name, "vkCmdDrawClusterHUAWEI")) {
        *addr = (void *)CmdDrawClusterHUAWEI;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawClusterIndirectHUAWEI && !strcmp(name, "vkCmdDrawClusterIndirectHUAWEI")) {
        *addr = (void *)CmdDrawClusterIndirectHUAWEI;
        return true;
    }

    // ---- VK_EXT_pageable_device_local_memory extension commands
    if (nameHash == XXH3_vkSetDeviceMemoryPriorityEXT && !strcmp(name, "vkSetDeviceMemoryPriorityEXT")) {
        *addr = (void *)SetDeviceMemoryPriorityEXT;
        return true;
    }

    // ---- VK_ARM_scheduling_controls extension commands
    if (nameHash == XXH3_vkCmdSetDispatchParametersARM && !strcmp(name, "vkCmdSetDispatchParametersARM")) {
        *addr = (void *)CmdSetDispatchParametersARM;
        return true;
    }

    // ---- VK_VALVE_descriptor_set_host_mapping extension commands
    if (nameHash == XXH3_vkGetDescriptorSetLayoutHostMappingInfoVALVE && !strcmp(name, "vkGetDescriptorSetLayoutHostMappingInfoVALVE")) {
        *addr = (void *)GetDescriptorSetLayoutHostMappingInfoVALVE;
        return true;
    }
    if (nameHash == XXH3_vkGetDescriptorSetHostMappingVALVE && !strcmp(name, "vkGetDescriptorSetHostMappingVALVE")) {
        *addr = (void *)GetDescriptorSetHostMappingVALVE;
        return true;
    }

    // ---- VK_NV_copy_memory_indirect extension commands
    if (nameHash == XXH3_vkCmdCopyMemoryIndirectNV && !strcmp(name, "vkCmdCopyMemoryIndirectNV")) {
        *addr = (void *)CmdCopyMemoryIndirectNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMemoryToImageIndirectNV && !strcmp(name, "vkCmdCopyMemoryToImageIndirectNV")) {
        *addr = (void *)CmdCopyMemoryToImageIndirectNV;
        return true;
    }

    // ---- VK_NV_memory_decompression extension commands
    if (nameHash == XXH3_vkCmdDecompressMemoryNV && !strcmp(name, "vkCmdDecompressMemoryNV")) {
        *addr = (void *)CmdDecompressMemoryNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdDecompressMemoryIndirectCountNV && !strcmp(name, "vkCmdDecompressMemoryIndirectCountNV")) {
        *addr = (void *)CmdDecompressMemoryIndirectCountNV;
        return true;
    }

    // ---- VK_NV_device_generated_commands_compute extension commands
    if (nameHash == XXH3_vkGetPipelineIndirectMemoryRequirementsNV && !strcmp(name, "vkGetPipelineIndirectMemoryRequirementsNV")) {
        *addr = (void *)GetPipelineIndirectMemoryRequirementsNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdUpdatePipelineIndirectBufferNV && !strcmp(name, "vkCmdUpdatePipelineIndirectBufferNV")) {
        *addr = (void *)CmdUpdatePipelineIndirectBufferNV;
        return true;
    }
    if (nameHash == XXH3_vkGetPipelineIndirectDeviceAddressNV && !strcmp(name, "vkGetPipelineIndirectDeviceAddressNV")) {
        *addr = (void *)GetPipelineIndirectDeviceAddressNV;
        return true;
    }

    // ---- VK_OHOS_external_memory extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    if (nameHash == XXH3_vkGetNativeBufferPropertiesOHOS && !strcmp(name, "vkGetNativeBufferPropertiesOHOS")) {
        *addr = (void *)GetNativeBufferPropertiesOHOS;
        return true;
    }
#endif // VK_USE_PLATFORM_OHOS
#if defined(VK_USE_PLATFORM_OHOS)
    if (nameHash == XXH3_vkGetMemoryNativeBufferOHOS && !strcmp(name, "vkGetMemoryNativeBufferOHOS")) {
        *addr = (void *)GetMemoryNativeBufferOHOS;
        return true;
    }
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_EXT_extended_dynamic_state3 extension commands
    if (nameHash == XXH3_vkCmdSetDepthClampEnableEXT && !strcmp(name, "vkCmdSetDepthClampEnableEXT")) {
        *addr = (void *)CmdSetDepthClampEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetPolygonModeEXT && !strcmp(name, "vkCmdSetPolygonModeEXT")) {
        *addr = (void *)CmdSetPolygonModeEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetRasterizationSamplesEXT && !strcmp(name, "vkCmdSetRasterizationSamplesEXT")) {
        *addr = (void *)CmdSetRasterizationSamplesEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetSampleMaskEXT && !strcmp(name, "vkCmdSetSampleMaskEXT")) {
        *addr = (void *)CmdSetSampleMaskEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetAlphaToCoverageEnableEXT && !strcmp(name, "vkCmdSetAlphaToCoverageEnableEXT")) {
        *addr = (void *)CmdSetAlphaToCoverageEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetAlphaToOneEnableEXT && !strcmp(name, "vkCmdSetAlphaToOneEnableEXT")) {
        *addr = (void *)CmdSetAlphaToOneEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetLogicOpEnableEXT && !strcmp(name, "vkCmdSetLogicOpEnableEXT")) {
        *addr = (void *)CmdSetLogicOpEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetColorBlendEnableEXT && !strcmp(name, "vkCmdSetColorBlendEnableEXT")) {
        *addr = (void *)CmdSetColorBlendEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetColorBlendEquationEXT && !strcmp(name, "vkCmdSetColorBlendEquationEXT")) {
        *addr = (void *)CmdSetColorBlendEquationEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetColorWriteMaskEXT && !strcmp(name, "vkCmdSetColorWriteMaskEXT")) {
        *addr = (void *)CmdSetColorWriteMaskEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetTessellationDomainOriginEXT && !strcmp(name, "vkCmdSetTessellationDomainOriginEXT")) {
        *addr = (void *)CmdSetTessellationDomainOriginEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetRasterizationStreamEXT && !strcmp(name, "vkCmdSetRasterizationStreamEXT")) {
        *addr = (void *)CmdSetRasterizationStreamEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetConservativeRasterizationModeEXT && !strcmp(name, "vkCmdSetConservativeRasterizationModeEXT")) {
        *addr = (void *)CmdSetConservativeRasterizationModeEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetExtraPrimitiveOverestimationSizeEXT && !strcmp(name, "vkCmdSetExtraPrimitiveOverestimationSizeEXT")) {
        *addr = (void *)CmdSetExtraPrimitiveOverestimationSizeEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthClipEnableEXT && !strcmp(name, "vkCmdSetDepthClipEnableEXT")) {
        *addr = (void *)CmdSetDepthClipEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetSampleLocationsEnableEXT && !strcmp(name, "vkCmdSetSampleLocationsEnableEXT")) {
        *addr = (void *)CmdSetSampleLocationsEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetColorBlendAdvancedEXT && !strcmp(name, "vkCmdSetColorBlendAdvancedEXT")) {
        *addr = (void *)CmdSetColorBlendAdvancedEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetProvokingVertexModeEXT && !strcmp(name, "vkCmdSetProvokingVertexModeEXT")) {
        *addr = (void *)CmdSetProvokingVertexModeEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetLineRasterizationModeEXT && !strcmp(name, "vkCmdSetLineRasterizationModeEXT")) {
        *addr = (void *)CmdSetLineRasterizationModeEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetLineStippleEnableEXT && !strcmp(name, "vkCmdSetLineStippleEnableEXT")) {
        *addr = (void *)CmdSetLineStippleEnableEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthClipNegativeOneToOneEXT && !strcmp(name, "vkCmdSetDepthClipNegativeOneToOneEXT")) {
        *addr = (void *)CmdSetDepthClipNegativeOneToOneEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetViewportWScalingEnableNV && !strcmp(name, "vkCmdSetViewportWScalingEnableNV")) {
        *addr = (void *)CmdSetViewportWScalingEnableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetViewportSwizzleNV && !strcmp(name, "vkCmdSetViewportSwizzleNV")) {
        *addr = (void *)CmdSetViewportSwizzleNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoverageToColorEnableNV && !strcmp(name, "vkCmdSetCoverageToColorEnableNV")) {
        *addr = (void *)CmdSetCoverageToColorEnableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoverageToColorLocationNV && !strcmp(name, "vkCmdSetCoverageToColorLocationNV")) {
        *addr = (void *)CmdSetCoverageToColorLocationNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoverageModulationModeNV && !strcmp(name, "vkCmdSetCoverageModulationModeNV")) {
        *addr = (void *)CmdSetCoverageModulationModeNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoverageModulationTableEnableNV && !strcmp(name, "vkCmdSetCoverageModulationTableEnableNV")) {
        *addr = (void *)CmdSetCoverageModulationTableEnableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoverageModulationTableNV && !strcmp(name, "vkCmdSetCoverageModulationTableNV")) {
        *addr = (void *)CmdSetCoverageModulationTableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetShadingRateImageEnableNV && !strcmp(name, "vkCmdSetShadingRateImageEnableNV")) {
        *addr = (void *)CmdSetShadingRateImageEnableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetRepresentativeFragmentTestEnableNV && !strcmp(name, "vkCmdSetRepresentativeFragmentTestEnableNV")) {
        *addr = (void *)CmdSetRepresentativeFragmentTestEnableNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetCoverageReductionModeNV && !strcmp(name, "vkCmdSetCoverageReductionModeNV")) {
        *addr = (void *)CmdSetCoverageReductionModeNV;
        return true;
    }

    // ---- VK_ARM_tensors extension commands
    if (nameHash == XXH3_vkCreateTensorARM && !strcmp(name, "vkCreateTensorARM")) {
        *addr = (void *)CreateTensorARM;
        return true;
    }
    if (nameHash == XXH3_vkDestroyTensorARM && !strcmp(name, "vkDestroyTensorARM")) {
        *addr = (void *)DestroyTensorARM;
        return true;
    }
    if (nameHash == XXH3_vkCreateTensorViewARM && !strcmp(name, "vkCreateTensorViewARM")) {
        *addr = (void *)CreateTensorViewARM;
        return true;
    }
    if (nameHash == XXH3_vkDestroyTensorViewARM && !strcmp(name, "vkDestroyTensorViewARM")) {
        *addr = (void *)DestroyTensorViewARM;
        return true;
    }
    if (nameHash == XXH3_vkGetTensorMemoryRequirementsARM && !strcmp(name, "vkGetTensorMemoryRequirementsARM")) {
        *addr = (void *)GetTensorMemoryRequirementsARM;
        return true;
    }
    if (nameHash == XXH3_vkBindTensorMemoryARM && !strcmp(name, "vkBindTensorMemoryARM")) {
        *addr = (void *)BindTensorMemoryARM;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceTensorMemoryRequirementsARM && !strcmp(name, "vkGetDeviceTensorMemoryRequirementsARM")) {
        *addr = (void *)GetDeviceTensorMemoryRequirementsARM;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyTensorARM && !strcmp(name, "vkCmdCopyTensorARM")) {
        *addr = (void *)CmdCopyTensorARM;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalTensorPropertiesARM && !strcmp(name, "vkGetPhysicalDeviceExternalTensorPropertiesARM")) {
        *addr = (void *)GetPhysicalDeviceExternalTensorPropertiesARM;
        return true;
    }
    if (nameHash == XXH3_vkGetTensorOpaqueCaptureDescriptorDataARM && !strcmp(name, "vkGetTensorOpaqueCaptureDescriptorDataARM")) {
        *addr = (void *)GetTensorOpaqueCaptureDescriptorDataARM;
        return true;
    }
    if (nameHash == XXH3_vkGetTensorViewOpaqueCaptureDescriptorDataARM && !strcmp(name, "vkGetTensorViewOpaqueCaptureDescriptorDataARM")) {
        *addr = (void *)GetTensorViewOpaqueCaptureDescriptorDataARM;
        return true;
    }

    // ---- VK_EXT_shader_module_identifier extension commands
    if (nameHash == XXH3_vkGetShaderModuleIdentifierEXT && !strcmp(name, "vkGetShaderModuleIdentifierEXT")) {
        *addr = (void *)GetShaderModuleIdentifierEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetShaderModuleCreateInfoIdentifierEXT && !strcmp(name, "vkGetShaderModuleCreateInfoIdentifierEXT")) {
        *addr = (void *)GetShaderModuleCreateInfoIdentifierEXT;
        return true;
    }

    // ---- VK_NV_optical_flow extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceOpticalFlowImageFormatsNV && !strcmp(name, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV")) {
        *addr = (void *)GetPhysicalDeviceOpticalFlowImageFormatsNV;
        return true;
    }
    if (nameHash == XXH3_vkCreateOpticalFlowSessionNV && !strcmp(name, "vkCreateOpticalFlowSessionNV")) {
        *addr = (void *)CreateOpticalFlowSessionNV;
        return true;
    }
    if (nameHash == XXH3_vkDestroyOpticalFlowSessionNV && !strcmp(name, "vkDestroyOpticalFlowSessionNV")) {
        *addr = (void *)DestroyOpticalFlowSessionNV;
        return true;
    }
    if (nameHash == XXH3_vkBindOpticalFlowSessionImageNV && !strcmp(name, "vkBindOpticalFlowSessionImageNV")) {
        *addr = (void *)BindOpticalFlowSessionImageNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdOpticalFlowExecuteNV && !strcmp(name, "vkCmdOpticalFlowExecuteNV")) {
        *addr = (void *)CmdOpticalFlowExecuteNV;
        return true;
    }

    // ---- VK_AMD_anti_lag extension commands
    if (nameHash == XXH3_vkAntiLagUpdateAMD && !strcmp(name, "vkAntiLagUpdateAMD")) {
        *addr = (void *)AntiLagUpdateAMD;
        return true;
    }

    // ---- VK_EXT_shader_object extension commands
    if (nameHash == XXH3_vkCreateShadersEXT && !strcmp(name, "vkCreateShadersEXT")) {
        *addr = (void *)CreateShadersEXT;
        return true;
    }
    if (nameHash == XXH3_vkDestroyShaderEXT && !strcmp(name, "vkDestroyShaderEXT")) {
        *addr = (void *)DestroyShaderEXT;
        return true;
    }
    if (nameHash == XXH3_vkGetShaderBinaryDataEXT && !strcmp(name, "vkGetShaderBinaryDataEXT")) {
        *addr = (void *)GetShaderBinaryDataEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdBindShadersEXT && !strcmp(name, "vkCmdBindShadersEXT")) {
        *addr = (void *)CmdBindShadersEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetDepthClampRangeEXT && !strcmp(name, "vkCmdSetDepthClampRangeEXT")) {
        *addr = (void *)CmdSetDepthClampRangeEXT;
        return true;
    }

    // ---- VK_QCOM_tile_properties extension commands
    if (nameHash == XXH3_vkGetFramebufferTilePropertiesQCOM && !strcmp(name, "vkGetFramebufferTilePropertiesQCOM")) {
        *addr = (void *)GetFramebufferTilePropertiesQCOM;
        return true;
    }
    if (nameHash == XXH3_vkGetDynamicRenderingTilePropertiesQCOM && !strcmp(name, "vkGetDynamicRenderingTilePropertiesQCOM")) {
        *addr = (void *)GetDynamicRenderingTilePropertiesQCOM;
        return true;
    }

    // ---- VK_NV_cooperative_vector extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeVectorPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceCooperativeVectorPropertiesNV")) {
        *addr = (void *)GetPhysicalDeviceCooperativeVectorPropertiesNV;
        return true;
    }
    if (nameHash == XXH3_vkConvertCooperativeVectorMatrixNV && !strcmp(name, "vkConvertCooperativeVectorMatrixNV")) {
        *addr = (void *)ConvertCooperativeVectorMatrixNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdConvertCooperativeVectorMatrixNV && !strcmp(name, "vkCmdConvertCooperativeVectorMatrixNV")) {
        *addr = (void *)CmdConvertCooperativeVectorMatrixNV;
        return true;
    }

    // ---- VK_NV_low_latency2 extension commands
    if (nameHash == XXH3_vkSetLatencySleepModeNV && !strcmp(name, "vkSetLatencySleepModeNV")) {
        *addr = (void *)SetLatencySleepModeNV;
        return true;
    }
    if (nameHash == XXH3_vkLatencySleepNV && !strcmp(name, "vkLatencySleepNV")) {
        *addr = (void *)LatencySleepNV;
        return true;
    }
    if (nameHash == XXH3_vkSetLatencyMarkerNV && !strcmp(name, "vkSetLatencyMarkerNV")) {
        *addr = (void *)SetLatencyMarkerNV;
        return true;
    }
    if (nameHash == XXH3_vkGetLatencyTimingsNV && !strcmp(name, "vkGetLatencyTimingsNV")) {
        *addr = (void *)GetLatencyTimingsNV;
        return true;
    }
    if (nameHash == XXH3_vkQueueNotifyOutOfBandNV && !strcmp(name, "vkQueueNotifyOutOfBandNV")) {
        *addr = (void *)QueueNotifyOutOfBandNV;
        return true;
    }

    // ---- VK_ARM_data_graph extension commands
    if (nameHash == XXH3_vkCreateDataGraphPipelinesARM && !strcmp(name, "vkCreateDataGraphPipelinesARM")) {
        *addr = (void *)CreateDataGraphPipelinesARM;
        return true;
    }
    if (nameHash == XXH3_vkCreateDataGraphPipelineSessionARM && !strcmp(name, "vkCreateDataGraphPipelineSessionARM")) {
        *addr = (void *)CreateDataGraphPipelineSessionARM;
        return true;
    }
    if (nameHash == XXH3_vkGetDataGraphPipelineSessionBindPointRequirementsARM && !strcmp(name, "vkGetDataGraphPipelineSessionBindPointRequirementsARM")) {
        *addr = (void *)GetDataGraphPipelineSessionBindPointRequirementsARM;
        return true;
    }
    if (nameHash == XXH3_vkGetDataGraphPipelineSessionMemoryRequirementsARM && !strcmp(name, "vkGetDataGraphPipelineSessionMemoryRequirementsARM")) {
        *addr = (void *)GetDataGraphPipelineSessionMemoryRequirementsARM;
        return true;
    }
    if (nameHash == XXH3_vkBindDataGraphPipelineSessionMemoryARM && !strcmp(name, "vkBindDataGraphPipelineSessionMemoryARM")) {
        *addr = (void *)BindDataGraphPipelineSessionMemoryARM;
        return true;
    }
    if (nameHash == XXH3_vkDestroyDataGraphPipelineSessionARM && !strcmp(name, "vkDestroyDataGraphPipelineSessionARM")) {
        *addr = (void *)DestroyDataGraphPipelineSessionARM;
        return true;
    }
    if (nameHash == XXH3_vkCmdDispatchDataGraphARM && !strcmp(name, "vkCmdDispatchDataGraphARM")) {
        *addr = (void *)CmdDispatchDataGraphARM;
        return true;
    }
    if (nameHash == XXH3_vkGetDataGraphPipelineAvailablePropertiesARM && !strcmp(name, "vkGetDataGraphPipelineAvailablePropertiesARM")) {
        *addr = (void *)GetDataGraphPipelineAvailablePropertiesARM;
        return true;
    }
    if (nameHash == XXH3_vkGetDataGraphPipelinePropertiesARM && !strcmp(name, "vkGetDataGraphPipelinePropertiesARM")) {
        *addr = (void *)GetDataGraphPipelinePropertiesARM;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM")) {
        *addr = (void *)GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM;
        return true;
    }
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM")) {
        *addr = (void *)GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM;
        return true;
    }

    // ---- VK_ARM_data_graph_instruction_set_tosa extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM")) {
        *addr = (void *)GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM;
        return true;
    }

    // ---- VK_EXT_attachment_feedback_loop_dynamic_state extension commands
    if (nameHash == XXH3_vkCmdSetAttachmentFeedbackLoopEnableEXT && !strcmp(name, "vkCmdSetAttachmentFeedbackLoopEnableEXT")) {
        *addr = (void *)CmdSetAttachmentFeedbackLoopEnableEXT;
        return true;
    }

    // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (nameHash == XXH3_vkGetScreenBufferPropertiesQNX && !strcmp(name, "vkGetScreenBufferPropertiesQNX")) {
        *addr = (void *)GetScreenBufferPropertiesQNX;
        return true;
    }
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_QCOM_tile_memory_heap extension commands
    if (nameHash == XXH3_vkCmdBindTileMemoryQCOM && !strcmp(name, "vkCmdBindTileMemoryQCOM")) {
        *addr = (void *)CmdBindTileMemoryQCOM;
        return true;
    }

    // ---- VK_EXT_memory_decompression extension commands
    if (nameHash == XXH3_vkCmdDecompressMemoryEXT && !strcmp(name, "vkCmdDecompressMemoryEXT")) {
        *addr = (void *)CmdDecompressMemoryEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDecompressMemoryIndirectCountEXT && !strcmp(name, "vkCmdDecompressMemoryIndirectCountEXT")) {
        *addr = (void *)CmdDecompressMemoryIndirectCountEXT;
        return true;
    }

    // ---- VK_NV_external_compute_queue extension commands
    if (nameHash == XXH3_vkCreateExternalComputeQueueNV && !strcmp(name, "vkCreateExternalComputeQueueNV")) {
        *addr = (void *)CreateExternalComputeQueueNV;
        return true;
    }
    if (nameHash == XXH3_vkDestroyExternalComputeQueueNV && !strcmp(name, "vkDestroyExternalComputeQueueNV")) {
        *addr = (void *)DestroyExternalComputeQueueNV;
        return true;
    }
    if (nameHash == XXH3_vkGetExternalComputeQueueDataNV && !strcmp(name, "vkGetExternalComputeQueueDataNV")) {
        *addr = (void *)GetExternalComputeQueueDataNV;
        return true;
    }

    // ---- VK_NV_cluster_acceleration_structure extension commands
    if (nameHash == XXH3_vkGetClusterAccelerationStructureBuildSizesNV && !strcmp(name, "vkGetClusterAccelerationStructureBuildSizesNV")) {
        *addr = (void *)GetClusterAccelerationStructureBuildSizesNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdBuildClusterAccelerationStructureIndirectNV && !strcmp(name, "vkCmdBuildClusterAccelerationStructureIndirectNV")) {
        *addr = (void *)CmdBuildClusterAccelerationStructureIndirectNV;
        return true;
    }

    // ---- VK_NV_partitioned_acceleration_structure extension commands
    if (nameHash == XXH3_vkGetPartitionedAccelerationStructuresBuildSizesNV && !strcmp(name, "vkGetPartitionedAccelerationStructuresBuildSizesNV")) {
        *addr = (void *)GetPartitionedAccelerationStructuresBuildSizesNV;
        return true;
    }
    if (nameHash == XXH3_vkCmdBuildPartitionedAccelerationStructuresNV && !strcmp(name, "vkCmdBuildPartitionedAccelerationStructuresNV")) {
        *addr = (void *)CmdBuildPartitionedAccelerationStructuresNV;
        return true;
    }

    // ---- VK_EXT_device_generated_commands extension commands
    if (nameHash == XXH3_vkGetGeneratedCommandsMemoryRequirementsEXT && !strcmp(name, "vkGetGeneratedCommandsMemoryRequirementsEXT")) {
        *addr = (void *)GetGeneratedCommandsMemoryRequirementsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdPreprocessGeneratedCommandsEXT && !strcmp(name, "vkCmdPreprocessGeneratedCommandsEXT")) {
        *addr = (void *)CmdPreprocessGeneratedCommandsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdExecuteGeneratedCommandsEXT && !strcmp(name, "vkCmdExecuteGeneratedCommandsEXT")) {
        *addr = (void *)CmdExecuteGeneratedCommandsEXT;
        return true;
    }
    if (nameHash == XXH3_vkCreateIndirectCommandsLayoutEXT && !strcmp(name, "vkCreateIndirectCommandsLayoutEXT")) {
        *addr = (void *)CreateIndirectCommandsLayoutEXT;
        return true;
    }
    if (nameHash == XXH3_vkDestroyIndirectCommandsLayoutEXT && !strcmp(name, "vkDestroyIndirectCommandsLayoutEXT")) {
        *addr = (void *)DestroyIndirectCommandsLayoutEXT;
        return true;
    }
    if (nameHash == XXH3_vkCreateIndirectExecutionSetEXT && !strcmp(name, "vkCreateIndirectExecutionSetEXT")) {
        *addr = (void *)CreateIndirectExecutionSetEXT;
        return true;
    }
    if (nameHash == XXH3_vkDestroyIndirectExecutionSetEXT && !strcmp(name, "vkDestroyIndirectExecutionSetEXT")) {
        *addr = (void *)DestroyIndirectExecutionSetEXT;
        return true;
    }
    if (nameHash == XXH3_vkUpdateIndirectExecutionSetPipelineEXT && !strcmp(name, "vkUpdateIndirectExecutionSetPipelineEXT")) {
        *addr = (void *)UpdateIndirectExecutionSetPipelineEXT;
        return true;
    }
    if (nameHash == XXH3_vkUpdateIndirectExecutionSetShaderEXT && !strcmp(name, "vkUpdateIndirectExecutionSetShaderEXT")) {
        *addr = (void *)UpdateIndirectExecutionSetShaderEXT;
        return true;
    }

    // ---- VK_OHOS_surface extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    if (nameHash == XXH3_vkCreateSurfaceOHOS && !strcmp(name, "vkCreateSurfaceOHOS")) {
        *addr = (ptr_instance->enabled_extensions.ohos_surface == 1)
                     ? (void *)CreateSurfaceOHOS
                     : NULL;
        return true;
    }
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_NV_cooperative_matrix2 extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV && !strcmp(name, "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV")) {
        *addr = (void *)GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV;
        return true;
    }

    // ---- VK_EXT_external_memory_metal extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkGetMemoryMetalHandleEXT && !strcmp(name, "vkGetMemoryMetalHandleEXT")) {
        *addr = (void *)GetMemoryMetalHandleEXT;
        return true;
    }
#endif // VK_USE_PLATFORM_METAL_EXT
#if defined(VK_USE_PLATFORM_METAL_EXT)
    if (nameHash == XXH3_vkGetMemoryMetalHandlePropertiesEXT && !strcmp(name, "vkGetMemoryMetalHandlePropertiesEXT")) {
        *addr = (void *)GetMemoryMetalHandlePropertiesEXT;
        return true;
    }
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_ARM_performance_counters_by_region extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM && !strcmp(name, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM")) {
        *addr = (void *)EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM;
        return true;
    }

    // ---- VK_ARM_shader_instrumentation extension commands
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM && !strcmp(name, "vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM")) {
        *addr = (void *)EnumeratePhysicalDeviceShaderInstrumentationMetricsARM;
        return true;
    }
    if (nameHash == XXH3_vkCreateShaderInstrumentationARM && !strcmp(name, "vkCreateShaderInstrumentationARM")) {
        *addr = (void *)CreateShaderInstrumentationARM;
        return true;
    }
    if (nameHash == XXH3_vkDestroyShaderInstrumentationARM && !strcmp(name, "vkDestroyShaderInstrumentationARM")) {
        *addr = (void *)DestroyShaderInstrumentationARM;
        return true;
    }
    if (nameHash == XXH3_vkCmdBeginShaderInstrumentationARM && !strcmp(name, "vkCmdBeginShaderInstrumentationARM")) {
        *addr = (void *)CmdBeginShaderInstrumentationARM;
        return true;
    }
    if (nameHash == XXH3_vkCmdEndShaderInstrumentationARM && !strcmp(name, "vkCmdEndShaderInstrumentationARM")) {
        *addr = (void *)CmdEndShaderInstrumentationARM;
        return true;
    }
    if (nameHash == XXH3_vkGetShaderInstrumentationValuesARM && !strcmp(name, "vkGetShaderInstrumentationValuesARM")) {
        *addr = (void *)GetShaderInstrumentationValuesARM;
        return true;
    }
    if (nameHash == XXH3_vkClearShaderInstrumentationMetricsARM && !strcmp(name, "vkClearShaderInstrumentationMetricsARM")) {
        *addr = (void *)ClearShaderInstrumentationMetricsARM;
        return true;
    }

    // ---- VK_EXT_fragment_density_map_offset extension commands
    if (nameHash == XXH3_vkCmdEndRendering2EXT && !strcmp(name, "vkCmdEndRendering2EXT")) {
        *addr = (void *)CmdEndRendering2EXT;
        return true;
    }

    // ---- VK_EXT_custom_resolve extension commands
    if (nameHash == XXH3_vkCmdBeginCustomResolveEXT && !strcmp(name, "vkCmdBeginCustomResolveEXT")) {
        *addr = (void *)CmdBeginCustomResolveEXT;
        return true;
    }

    // ---- VK_ARM_data_graph_optical_flow extension commands
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM")) {
        *addr = (void *)GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM;
        return true;
    }

    // ---- VK_NV_compute_occupancy_priority extension commands
    if (nameHash == XXH3_vkCmdSetComputeOccupancyPriorityNV && !strcmp(name, "vkCmdSetComputeOccupancyPriorityNV")) {
        *addr = (void *)CmdSetComputeOccupancyPriorityNV;
        return true;
    }

    // ---- VK_SEC_ubm_surface extension commands
#if defined(VK_USE_PLATFORM_UBM_SEC)
    if (nameHash == XXH3_vkCreateUbmSurfaceSEC && !strcmp(name, "vkCreateUbmSurfaceSEC")) {
        *addr = (ptr_instance->enabled_extensions.sec_ubm_surface == 1)
                     ? (void *)CreateUbmSurfaceSEC
                     : NULL;
        return true;
    }
#endif // VK_USE_PLATFORM_UBM_SEC
#if defined(VK_USE_PLATFORM_UBM_SEC)
    if (nameHash == XXH3_vkGetPhysicalDeviceUbmPresentationSupportSEC && !strcmp(name, "vkGetPhysicalDeviceUbmPresentationSupportSEC")) {
        *addr = (ptr_instance->enabled_extensions.sec_ubm_surface == 1)
                     ? (void *)GetPhysicalDeviceUbmPresentationSupportSEC
                     : NULL;
        return true;
    }
#endif // VK_USE_PLATFORM_UBM_SEC

    // ---- VK_EXT_primitive_restart_index extension commands
    if (nameHash == XXH3_vkCmdSetPrimitiveRestartIndexEXT && !strcmp(name, "vkCmdSetPrimitiveRestartIndexEXT")) {
        *addr = (void *)CmdSetPrimitiveRestartIndexEXT;
        return true;
    }

    // ---- VK_KHR_acceleration_structure extension commands
    if (nameHash == XXH3_vkCreateAccelerationStructureKHR && !strcmp(name, "vkCreateAccelerationStructureKHR")) {
        *addr = (void *)CreateAccelerationStructureKHR;
        return true;
    }
    if (nameHash == XXH3_vkDestroyAccelerationStructureKHR && !strcmp(name, "vkDestroyAccelerationStructureKHR")) {
        *addr = (void *)DestroyAccelerationStructureKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBuildAccelerationStructuresKHR && !strcmp(name, "vkCmdBuildAccelerationStructuresKHR")) {
        *addr = (void *)CmdBuildAccelerationStructuresKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdBuildAccelerationStructuresIndirectKHR && !strcmp(name, "vkCmdBuildAccelerationStructuresIndirectKHR")) {
        *addr = (void *)CmdBuildAccelerationStructuresIndirectKHR;
        return true;
    }
    if (nameHash == XXH3_vkBuildAccelerationStructuresKHR && !strcmp(name, "vkBuildAccelerationStructuresKHR")) {
        *addr = (void *)BuildAccelerationStructuresKHR;
        return true;
    }
    if (nameHash == XXH3_vkCopyAccelerationStructureKHR && !strcmp(name, "vkCopyAccelerationStructureKHR")) {
        *addr = (void *)CopyAccelerationStructureKHR;
        return true;
    }
    if (nameHash == XXH3_vkCopyAccelerationStructureToMemoryKHR && !strcmp(name, "vkCopyAccelerationStructureToMemoryKHR")) {
        *addr = (void *)CopyAccelerationStructureToMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCopyMemoryToAccelerationStructureKHR && !strcmp(name, "vkCopyMemoryToAccelerationStructureKHR")) {
        *addr = (void *)CopyMemoryToAccelerationStructureKHR;
        return true;
    }
    if (nameHash == XXH3_vkWriteAccelerationStructuresPropertiesKHR && !strcmp(name, "vkWriteAccelerationStructuresPropertiesKHR")) {
        *addr = (void *)WriteAccelerationStructuresPropertiesKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyAccelerationStructureKHR && !strcmp(name, "vkCmdCopyAccelerationStructureKHR")) {
        *addr = (void *)CmdCopyAccelerationStructureKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyAccelerationStructureToMemoryKHR && !strcmp(name, "vkCmdCopyAccelerationStructureToMemoryKHR")) {
        *addr = (void *)CmdCopyAccelerationStructureToMemoryKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdCopyMemoryToAccelerationStructureKHR && !strcmp(name, "vkCmdCopyMemoryToAccelerationStructureKHR")) {
        *addr = (void *)CmdCopyMemoryToAccelerationStructureKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetAccelerationStructureDeviceAddressKHR && !strcmp(name, "vkGetAccelerationStructureDeviceAddressKHR")) {
        *addr = (void *)GetAccelerationStructureDeviceAddressKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdWriteAccelerationStructuresPropertiesKHR && !strcmp(name, "vkCmdWriteAccelerationStructuresPropertiesKHR")) {
        *addr = (void *)CmdWriteAccelerationStructuresPropertiesKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetDeviceAccelerationStructureCompatibilityKHR && !strcmp(name, "vkGetDeviceAccelerationStructureCompatibilityKHR")) {
        *addr = (void *)GetDeviceAccelerationStructureCompatibilityKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetAccelerationStructureBuildSizesKHR && !strcmp(name, "vkGetAccelerationStructureBuildSizesKHR")) {
        *addr = (void *)GetAccelerationStructureBuildSizesKHR;
        return true;
    }

    // ---- VK_KHR_ray_tracing_pipeline extension commands
    if (nameHash == XXH3_vkCmdTraceRaysKHR && !strcmp(name, "vkCmdTraceRaysKHR")) {
        *addr = (void *)CmdTraceRaysKHR;
        return true;
    }
    if (nameHash == XXH3_vkCreateRayTracingPipelinesKHR && !strcmp(name, "vkCreateRayTracingPipelinesKHR")) {
        *addr = (void *)CreateRayTracingPipelinesKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR && !strcmp(name, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR")) {
        *addr = (void *)GetRayTracingCaptureReplayShaderGroupHandlesKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdTraceRaysIndirectKHR && !strcmp(name, "vkCmdTraceRaysIndirectKHR")) {
        *addr = (void *)CmdTraceRaysIndirectKHR;
        return true;
    }
    if (nameHash == XXH3_vkGetRayTracingShaderGroupStackSizeKHR && !strcmp(name, "vkGetRayTracingShaderGroupStackSizeKHR")) {
        *addr = (void *)GetRayTracingShaderGroupStackSizeKHR;
        return true;
    }
    if (nameHash == XXH3_vkCmdSetRayTracingPipelineStackSizeKHR && !strcmp(name, "vkCmdSetRayTracingPipelineStackSizeKHR")) {
        *addr = (void *)CmdSetRayTracingPipelineStackSizeKHR;
        return true;
    }

    // ---- VK_EXT_mesh_shader extension commands
    if (nameHash == XXH3_vkCmdDrawMeshTasksEXT && !strcmp(name, "vkCmdDrawMeshTasksEXT")) {
        *addr = (void *)CmdDrawMeshTasksEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectEXT && !strcmp(name, "vkCmdDrawMeshTasksIndirectEXT")) {
        *addr = (void *)CmdDrawMeshTasksIndirectEXT;
        return true;
    }
    if (nameHash == XXH3_vkCmdDrawMeshTasksIndirectCountEXT && !strcmp(name, "vkCmdDrawMeshTasksIndirectCountEXT")) {
        *addr = (void *)CmdDrawMeshTasksIndirectCountEXT;
        return true;
    }
    return false;
}

// Used to keep track of all enabled instance extensions
void fill_out_enabled_instance_extensions(uint32_t extension_count, const char *const * extension_list, struct loader_instance_extension_enable_list* enables) {
    for (uint32_t i = 0; i < extension_count; i++) {
        uint64_t extNameHash =  XXH3_64bits(extension_list[i], strlen(extension_list[i]));

    // ---- VK_KHR_surface extension commands
        if (extNameHash == XXH3_VK_KHR_surface && !strcmp(extension_list[i], VK_KHR_SURFACE_EXTENSION_NAME)) { enables->khr_surface = 1; }

    // ---- VK_KHR_display extension commands
        else if (extNameHash == XXH3_VK_KHR_display && !strcmp(extension_list[i], VK_KHR_DISPLAY_EXTENSION_NAME)) { enables->khr_display = 1; }

    // ---- VK_KHR_xlib_surface extension commands
#if defined(VK_USE_PLATFORM_XLIB_KHR)
        else if (extNameHash == XXH3_VK_KHR_xlib_surface && !strcmp(extension_list[i], VK_KHR_XLIB_SURFACE_EXTENSION_NAME)) { enables->khr_xlib_surface = 1; }
#endif // VK_USE_PLATFORM_XLIB_KHR

    // ---- VK_KHR_xcb_surface extension commands
#if defined(VK_USE_PLATFORM_XCB_KHR)
        else if (extNameHash == XXH3_VK_KHR_xcb_surface && !strcmp(extension_list[i], VK_KHR_XCB_SURFACE_EXTENSION_NAME)) { enables->khr_xcb_surface = 1; }
#endif // VK_USE_PLATFORM_XCB_KHR

    // ---- VK_KHR_wayland_surface extension commands
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
        else if (extNameHash == XXH3_VK_KHR_wayland_surface && !strcmp(extension_list[i], VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME)) { enables->khr_wayland_surface = 1; }
#endif // VK_USE_PLATFORM_WAYLAND_KHR

    // ---- VK_KHR_android_surface extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
        else if (extNameHash == XXH3_VK_KHR_android_surface && !strcmp(extension_list[i], VK_KHR_ANDROID_SURFACE_EXTENSION_NAME)) { enables->khr_android_surface = 1; }
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_KHR_win32_surface extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        else if (extNameHash == XXH3_VK_KHR_win32_surface && !strcmp(extension_list[i], VK_KHR_WIN32_SURFACE_EXTENSION_NAME)) { enables->khr_win32_surface = 1; }
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_get_physical_device_properties2 extension commands
        else if (extNameHash == XXH3_VK_KHR_get_physical_device_properties2 && !strcmp(extension_list[i], VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME)) { enables->khr_get_physical_device_properties2 = 1; }

    // ---- VK_KHR_device_group_creation extension commands
        else if (extNameHash == XXH3_VK_KHR_device_group_creation && !strcmp(extension_list[i], VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME)) { enables->khr_device_group_creation = 1; }

    // ---- VK_KHR_external_memory_capabilities extension commands
        else if (extNameHash == XXH3_VK_KHR_external_memory_capabilities && !strcmp(extension_list[i], VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME)) { enables->khr_external_memory_capabilities = 1; }

    // ---- VK_KHR_external_semaphore_capabilities extension commands
        else if (extNameHash == XXH3_VK_KHR_external_semaphore_capabilities && !strcmp(extension_list[i], VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME)) { enables->khr_external_semaphore_capabilities = 1; }

    // ---- VK_KHR_external_fence_capabilities extension commands
        else if (extNameHash == XXH3_VK_KHR_external_fence_capabilities && !strcmp(extension_list[i], VK_KHR_EXTERNAL_FENCE_CAPABILITIES_EXTENSION_NAME)) { enables->khr_external_fence_capabilities = 1; }

    // ---- VK_KHR_get_surface_capabilities2 extension commands
        else if (extNameHash == XXH3_VK_KHR_get_surface_capabilities2 && !strcmp(extension_list[i], VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME)) { enables->khr_get_surface_capabilities2 = 1; }

    // ---- VK_KHR_get_display_properties2 extension commands
        else if (extNameHash == XXH3_VK_KHR_get_display_properties2 && !strcmp(extension_list[i], VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME)) { enables->khr_get_display_properties2 = 1; }

    // ---- VK_KHR_surface_protected_capabilities extension commands
        else if (extNameHash == XXH3_VK_KHR_surface_protected_capabilities && !strcmp(extension_list[i], VK_KHR_SURFACE_PROTECTED_CAPABILITIES_EXTENSION_NAME)) { enables->khr_surface_protected_capabilities = 1; }

    // ---- VK_KHR_portability_enumeration extension commands
        else if (extNameHash == XXH3_VK_KHR_portability_enumeration && !strcmp(extension_list[i], VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)) { enables->khr_portability_enumeration = 1; }

    // ---- VK_KHR_surface_maintenance1 extension commands
        else if (extNameHash == XXH3_VK_KHR_surface_maintenance1 && !strcmp(extension_list[i], VK_KHR_SURFACE_MAINTENANCE_1_EXTENSION_NAME)) { enables->khr_surface_maintenance1 = 1; }

    // ---- VK_EXT_debug_report extension commands
        else if (extNameHash == XXH3_VK_EXT_debug_report && !strcmp(extension_list[i], VK_EXT_DEBUG_REPORT_EXTENSION_NAME)) { enables->ext_debug_report = 1; }

    // ---- VK_GGP_stream_descriptor_surface extension commands
#if defined(VK_USE_PLATFORM_GGP)
        else if (extNameHash == XXH3_VK_GGP_stream_descriptor_surface && !strcmp(extension_list[i], VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME)) { enables->ggp_stream_descriptor_surface = 1; }
#endif // VK_USE_PLATFORM_GGP

    // ---- VK_NV_external_memory_capabilities extension commands
        else if (extNameHash == XXH3_VK_NV_external_memory_capabilities && !strcmp(extension_list[i], VK_NV_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME)) { enables->nv_external_memory_capabilities = 1; }

    // ---- VK_EXT_validation_flags extension commands
        else if (extNameHash == XXH3_VK_EXT_validation_flags && !strcmp(extension_list[i], VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME)) { enables->ext_validation_flags = 1; }

    // ---- VK_NN_vi_surface extension commands
#if defined(VK_USE_PLATFORM_VI_NN)
        else if (extNameHash == XXH3_VK_NN_vi_surface && !strcmp(extension_list[i], VK_NN_VI_SURFACE_EXTENSION_NAME)) { enables->nn_vi_surface = 1; }
#endif // VK_USE_PLATFORM_VI_NN

    // ---- VK_EXT_direct_mode_display extension commands
        else if (extNameHash == XXH3_VK_EXT_direct_mode_display && !strcmp(extension_list[i], VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME)) { enables->ext_direct_mode_display = 1; }

    // ---- VK_EXT_acquire_xlib_display extension commands
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
        else if (extNameHash == XXH3_VK_EXT_acquire_xlib_display && !strcmp(extension_list[i], VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME)) { enables->ext_acquire_xlib_display = 1; }
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT

    // ---- VK_EXT_display_surface_counter extension commands
        else if (extNameHash == XXH3_VK_EXT_display_surface_counter && !strcmp(extension_list[i], VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME)) { enables->ext_display_surface_counter = 1; }

    // ---- VK_EXT_swapchain_colorspace extension commands
        else if (extNameHash == XXH3_VK_EXT_swapchain_colorspace && !strcmp(extension_list[i], VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME)) { enables->ext_swapchain_colorspace = 1; }

    // ---- VK_MVK_ios_surface extension commands
#if defined(VK_USE_PLATFORM_IOS_MVK)
        else if (extNameHash == XXH3_VK_MVK_ios_surface && !strcmp(extension_list[i], VK_MVK_IOS_SURFACE_EXTENSION_NAME)) { enables->mvk_ios_surface = 1; }
#endif // VK_USE_PLATFORM_IOS_MVK

    // ---- VK_MVK_macos_surface extension commands
#if defined(VK_USE_PLATFORM_MACOS_MVK)
        else if (extNameHash == XXH3_VK_MVK_macos_surface && !strcmp(extension_list[i], VK_MVK_MACOS_SURFACE_EXTENSION_NAME)) { enables->mvk_macos_surface = 1; }
#endif // VK_USE_PLATFORM_MACOS_MVK

    // ---- VK_EXT_debug_utils extension commands
        else if (extNameHash == XXH3_VK_EXT_debug_utils && !strcmp(extension_list[i], VK_EXT_DEBUG_UTILS_EXTENSION_NAME)) { enables->ext_debug_utils = 1; }

    // ---- VK_FUCHSIA_imagepipe_surface extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
        else if (extNameHash == XXH3_VK_FUCHSIA_imagepipe_surface && !strcmp(extension_list[i], VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME)) { enables->fuchsia_imagepipe_surface = 1; }
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_EXT_metal_surface extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
        else if (extNameHash == XXH3_VK_EXT_metal_surface && !strcmp(extension_list[i], VK_EXT_METAL_SURFACE_EXTENSION_NAME)) { enables->ext_metal_surface = 1; }
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_validation_features extension commands
        else if (extNameHash == XXH3_VK_EXT_validation_features && !strcmp(extension_list[i], VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME)) { enables->ext_validation_features = 1; }

    // ---- VK_EXT_headless_surface extension commands
        else if (extNameHash == XXH3_VK_EXT_headless_surface && !strcmp(extension_list[i], VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME)) { enables->ext_headless_surface = 1; }

    // ---- VK_EXT_surface_maintenance1 extension commands
        else if (extNameHash == XXH3_VK_EXT_surface_maintenance1 && !strcmp(extension_list[i], VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME)) { enables->ext_surface_maintenance1 = 1; }

    // ---- VK_EXT_acquire_drm_display extension commands
        else if (extNameHash == XXH3_VK_EXT_acquire_drm_display && !strcmp(extension_list[i], VK_EXT_ACQUIRE_DRM_DISPLAY_EXTENSION_NAME)) { enables->ext_acquire_drm_display = 1; }

    // ---- VK_EXT_directfb_surface extension commands
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
        else if (extNameHash == XXH3_VK_EXT_directfb_surface && !strcmp(extension_list[i], VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME)) { enables->ext_directfb_surface = 1; }
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

    // ---- VK_QNX_screen_surface extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
        else if (extNameHash == XXH3_VK_QNX_screen_surface && !strcmp(extension_list[i], VK_QNX_SCREEN_SURFACE_EXTENSION_NAME)) { enables->qnx_screen_surface = 1; }
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_GOOGLE_surfaceless_query extension commands
        else if (extNameHash == XXH3_VK_GOOGLE_surfaceless_query && !strcmp(extension_list[i], VK_GOOGLE_SURFACELESS_QUERY_EXTENSION_NAME)) { enables->google_surfaceless_query = 1; }

    // ---- VK_LUNARG_direct_driver_loading extension commands
        else if (extNameHash == XXH3_VK_LUNARG_direct_driver_loading && !strcmp(extension_list[i], VK_LUNARG_DIRECT_DRIVER_LOADING_EXTENSION_NAME)) { enables->lunarg_direct_driver_loading = 1; }

    // ---- VK_EXT_layer_settings extension commands
        else if (extNameHash == XXH3_VK_EXT_layer_settings && !strcmp(extension_list[i], VK_EXT_LAYER_SETTINGS_EXTENSION_NAME)) { enables->ext_layer_settings = 1; }

    // ---- VK_NV_display_stereo extension commands
        else if (extNameHash == XXH3_VK_NV_display_stereo && !strcmp(extension_list[i], VK_NV_DISPLAY_STEREO_EXTENSION_NAME)) { enables->nv_display_stereo = 1; }

    // ---- VK_OHOS_surface extension commands
#if defined(VK_USE_PLATFORM_OHOS)
        else if (extNameHash == XXH3_VK_OHOS_surface && !strcmp(extension_list[i], VK_OHOS_SURFACE_EXTENSION_NAME)) { enables->ohos_surface = 1; }
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_SEC_ubm_surface extension commands
#if defined(VK_USE_PLATFORM_UBM_SEC)
        else if (extNameHash == XXH3_VK_SEC_ubm_surface && !strcmp(extension_list[i], VK_SEC_UBM_SURFACE_EXTENSION_NAME)) { enables->sec_ubm_surface = 1; }
#endif // VK_USE_PLATFORM_UBM_SEC
    }
}

// Some device commands still need a terminator because the loader needs to unwrap something about them.
// In many cases, the item needing unwrapping is a VkPhysicalDevice or VkSurfaceKHR object.  But there may be other items
// in the future.
PFN_vkVoidFunction get_extension_device_proc_terminator(struct loader_device *dev, const char *name, uint64_t nameHash, bool* found_name) {
    *found_name = false;
    if (!name || name[0] != 'v' || name[1] != 'k') {
        return NULL;
    }
    // ---- VK_KHR_swapchain extension commands
    if (nameHash == XXH3_vkCreateSwapchainKHR && !strcmp(name, "vkCreateSwapchainKHR")) {
        *found_name = true;
        return dev->driver_extensions.khr_swapchain_enabled ?
            (PFN_vkVoidFunction)terminator_CreateSwapchainKHR : NULL;
    }
    if (nameHash == XXH3_vkGetDeviceGroupSurfacePresentModesKHR && !strcmp(name, "vkGetDeviceGroupSurfacePresentModesKHR")) {
        *found_name = true;
        return dev->driver_extensions.khr_swapchain_enabled || dev->driver_extensions.khr_device_group_enabled ?
            (PFN_vkVoidFunction)terminator_GetDeviceGroupSurfacePresentModesKHR : NULL;
    }
    // ---- VK_KHR_display_swapchain extension commands
    if (nameHash == XXH3_vkCreateSharedSwapchainsKHR && !strcmp(name, "vkCreateSharedSwapchainsKHR")) {
        *found_name = true;
        return dev->driver_extensions.khr_display_swapchain_enabled ?
            (PFN_vkVoidFunction)terminator_CreateSharedSwapchainsKHR : NULL;
    }
    // ---- VK_EXT_debug_marker extension commands
    if (nameHash == XXH3_vkDebugMarkerSetObjectTagEXT && !strcmp(name, "vkDebugMarkerSetObjectTagEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_marker_enabled ?
            (PFN_vkVoidFunction)terminator_DebugMarkerSetObjectTagEXT : NULL;
    }
    if (nameHash == XXH3_vkDebugMarkerSetObjectNameEXT && !strcmp(name, "vkDebugMarkerSetObjectNameEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_marker_enabled ?
            (PFN_vkVoidFunction)terminator_DebugMarkerSetObjectNameEXT : NULL;
    }
    // ---- VK_EXT_debug_utils extension commands
    if (nameHash == XXH3_vkSetDebugUtilsObjectNameEXT && !strcmp(name, "vkSetDebugUtilsObjectNameEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_SetDebugUtilsObjectNameEXT : NULL;
    }
    if (nameHash == XXH3_vkSetDebugUtilsObjectTagEXT && !strcmp(name, "vkSetDebugUtilsObjectTagEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_SetDebugUtilsObjectTagEXT : NULL;
    }
    if (nameHash == XXH3_vkQueueBeginDebugUtilsLabelEXT && !strcmp(name, "vkQueueBeginDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_QueueBeginDebugUtilsLabelEXT : NULL;
    }
    if (nameHash == XXH3_vkQueueEndDebugUtilsLabelEXT && !strcmp(name, "vkQueueEndDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_QueueEndDebugUtilsLabelEXT : NULL;
    }
    if (nameHash == XXH3_vkQueueInsertDebugUtilsLabelEXT && !strcmp(name, "vkQueueInsertDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_QueueInsertDebugUtilsLabelEXT : NULL;
    }
    if (nameHash == XXH3_vkCmdBeginDebugUtilsLabelEXT && !strcmp(name, "vkCmdBeginDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_CmdBeginDebugUtilsLabelEXT : NULL;
    }
    if (nameHash == XXH3_vkCmdEndDebugUtilsLabelEXT && !strcmp(name, "vkCmdEndDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_CmdEndDebugUtilsLabelEXT : NULL;
    }
    if (nameHash == XXH3_vkCmdInsertDebugUtilsLabelEXT && !strcmp(name, "vkCmdInsertDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_CmdInsertDebugUtilsLabelEXT : NULL;
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    // ---- VK_EXT_full_screen_exclusive extension commands
    if (nameHash == XXH3_vkGetDeviceGroupSurfacePresentModes2EXT && !strcmp(name, "vkGetDeviceGroupSurfacePresentModes2EXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_full_screen_exclusive_enabled ?
            (PFN_vkVoidFunction)terminator_GetDeviceGroupSurfacePresentModes2EXT : NULL;
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    return NULL;
}

// This table contains the loader's instance dispatch table, which contains
// default functions if no instance layers are activated.  This contains
// pointers to "terminator functions".
const VkLayerInstanceDispatchTable instance_disp = {

    // ---- Core Vulkan 1.0 commands
    .DestroyInstance = terminator_DestroyInstance,
    .EnumeratePhysicalDevices = terminator_EnumeratePhysicalDevices,
    .GetPhysicalDeviceFeatures = terminator_GetPhysicalDeviceFeatures,
    .GetPhysicalDeviceFormatProperties = terminator_GetPhysicalDeviceFormatProperties,
    .GetPhysicalDeviceImageFormatProperties = terminator_GetPhysicalDeviceImageFormatProperties,
    .GetPhysicalDeviceProperties = terminator_GetPhysicalDeviceProperties,
    .GetPhysicalDeviceQueueFamilyProperties = terminator_GetPhysicalDeviceQueueFamilyProperties,
    .GetPhysicalDeviceMemoryProperties = terminator_GetPhysicalDeviceMemoryProperties,
    .GetInstanceProcAddr = vkGetInstanceProcAddr,
    .EnumerateDeviceExtensionProperties = terminator_EnumerateDeviceExtensionProperties,
    .EnumerateDeviceLayerProperties = terminator_EnumerateDeviceLayerProperties,
    .GetPhysicalDeviceSparseImageFormatProperties = terminator_GetPhysicalDeviceSparseImageFormatProperties,

    // ---- Core Vulkan 1.1 commands
    .EnumeratePhysicalDeviceGroups = terminator_EnumeratePhysicalDeviceGroups,
    .GetPhysicalDeviceFeatures2 = terminator_GetPhysicalDeviceFeatures2,
    .GetPhysicalDeviceProperties2 = terminator_GetPhysicalDeviceProperties2,
    .GetPhysicalDeviceFormatProperties2 = terminator_GetPhysicalDeviceFormatProperties2,
    .GetPhysicalDeviceImageFormatProperties2 = terminator_GetPhysicalDeviceImageFormatProperties2,
    .GetPhysicalDeviceQueueFamilyProperties2 = terminator_GetPhysicalDeviceQueueFamilyProperties2,
    .GetPhysicalDeviceMemoryProperties2 = terminator_GetPhysicalDeviceMemoryProperties2,
    .GetPhysicalDeviceSparseImageFormatProperties2 = terminator_GetPhysicalDeviceSparseImageFormatProperties2,
    .GetPhysicalDeviceExternalBufferProperties = terminator_GetPhysicalDeviceExternalBufferProperties,
    .GetPhysicalDeviceExternalFenceProperties = terminator_GetPhysicalDeviceExternalFenceProperties,
    .GetPhysicalDeviceExternalSemaphoreProperties = terminator_GetPhysicalDeviceExternalSemaphoreProperties,

    // ---- Core Vulkan 1.3 commands
    .GetPhysicalDeviceToolProperties = terminator_GetPhysicalDeviceToolProperties,

    // ---- VK_KHR_surface extension commands
    .DestroySurfaceKHR = terminator_DestroySurfaceKHR,
    .GetPhysicalDeviceSurfaceSupportKHR = terminator_GetPhysicalDeviceSurfaceSupportKHR,
    .GetPhysicalDeviceSurfaceCapabilitiesKHR = terminator_GetPhysicalDeviceSurfaceCapabilitiesKHR,
    .GetPhysicalDeviceSurfaceFormatsKHR = terminator_GetPhysicalDeviceSurfaceFormatsKHR,
    .GetPhysicalDeviceSurfacePresentModesKHR = terminator_GetPhysicalDeviceSurfacePresentModesKHR,

    // ---- VK_KHR_swapchain extension commands
    .GetPhysicalDevicePresentRectanglesKHR = terminator_GetPhysicalDevicePresentRectanglesKHR,

    // ---- VK_KHR_display extension commands
    .GetPhysicalDeviceDisplayPropertiesKHR = terminator_GetPhysicalDeviceDisplayPropertiesKHR,
    .GetPhysicalDeviceDisplayPlanePropertiesKHR = terminator_GetPhysicalDeviceDisplayPlanePropertiesKHR,
    .GetDisplayPlaneSupportedDisplaysKHR = terminator_GetDisplayPlaneSupportedDisplaysKHR,
    .GetDisplayModePropertiesKHR = terminator_GetDisplayModePropertiesKHR,
    .CreateDisplayModeKHR = terminator_CreateDisplayModeKHR,
    .GetDisplayPlaneCapabilitiesKHR = terminator_GetDisplayPlaneCapabilitiesKHR,
    .CreateDisplayPlaneSurfaceKHR = terminator_CreateDisplayPlaneSurfaceKHR,

    // ---- VK_KHR_xlib_surface extension commands
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    .CreateXlibSurfaceKHR = terminator_CreateXlibSurfaceKHR,
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    .GetPhysicalDeviceXlibPresentationSupportKHR = terminator_GetPhysicalDeviceXlibPresentationSupportKHR,
#endif // VK_USE_PLATFORM_XLIB_KHR

    // ---- VK_KHR_xcb_surface extension commands
#if defined(VK_USE_PLATFORM_XCB_KHR)
    .CreateXcbSurfaceKHR = terminator_CreateXcbSurfaceKHR,
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    .GetPhysicalDeviceXcbPresentationSupportKHR = terminator_GetPhysicalDeviceXcbPresentationSupportKHR,
#endif // VK_USE_PLATFORM_XCB_KHR

    // ---- VK_KHR_wayland_surface extension commands
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    .CreateWaylandSurfaceKHR = terminator_CreateWaylandSurfaceKHR,
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    .GetPhysicalDeviceWaylandPresentationSupportKHR = terminator_GetPhysicalDeviceWaylandPresentationSupportKHR,
#endif // VK_USE_PLATFORM_WAYLAND_KHR

    // ---- VK_KHR_android_surface extension commands
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    .CreateAndroidSurfaceKHR = terminator_CreateAndroidSurfaceKHR,
#endif // VK_USE_PLATFORM_ANDROID_KHR

    // ---- VK_KHR_win32_surface extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .CreateWin32SurfaceKHR = terminator_CreateWin32SurfaceKHR,
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .GetPhysicalDeviceWin32PresentationSupportKHR = terminator_GetPhysicalDeviceWin32PresentationSupportKHR,
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_KHR_video_queue extension commands
    .GetPhysicalDeviceVideoCapabilitiesKHR = terminator_GetPhysicalDeviceVideoCapabilitiesKHR,
    .GetPhysicalDeviceVideoFormatPropertiesKHR = terminator_GetPhysicalDeviceVideoFormatPropertiesKHR,

    // ---- VK_KHR_get_physical_device_properties2 extension commands
    .GetPhysicalDeviceFeatures2KHR = terminator_GetPhysicalDeviceFeatures2,
    .GetPhysicalDeviceProperties2KHR = terminator_GetPhysicalDeviceProperties2,
    .GetPhysicalDeviceFormatProperties2KHR = terminator_GetPhysicalDeviceFormatProperties2,
    .GetPhysicalDeviceImageFormatProperties2KHR = terminator_GetPhysicalDeviceImageFormatProperties2,
    .GetPhysicalDeviceQueueFamilyProperties2KHR = terminator_GetPhysicalDeviceQueueFamilyProperties2,
    .GetPhysicalDeviceMemoryProperties2KHR = terminator_GetPhysicalDeviceMemoryProperties2,
    .GetPhysicalDeviceSparseImageFormatProperties2KHR = terminator_GetPhysicalDeviceSparseImageFormatProperties2,

    // ---- VK_KHR_device_group_creation extension commands
    .EnumeratePhysicalDeviceGroupsKHR = terminator_EnumeratePhysicalDeviceGroups,

    // ---- VK_KHR_external_memory_capabilities extension commands
    .GetPhysicalDeviceExternalBufferPropertiesKHR = terminator_GetPhysicalDeviceExternalBufferProperties,

    // ---- VK_KHR_external_semaphore_capabilities extension commands
    .GetPhysicalDeviceExternalSemaphorePropertiesKHR = terminator_GetPhysicalDeviceExternalSemaphoreProperties,

    // ---- VK_KHR_external_fence_capabilities extension commands
    .GetPhysicalDeviceExternalFencePropertiesKHR = terminator_GetPhysicalDeviceExternalFenceProperties,

    // ---- VK_KHR_performance_query extension commands
    .EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = terminator_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR,
    .GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = terminator_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR,

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    .GetPhysicalDeviceSurfaceCapabilities2KHR = terminator_GetPhysicalDeviceSurfaceCapabilities2KHR,
    .GetPhysicalDeviceSurfaceFormats2KHR = terminator_GetPhysicalDeviceSurfaceFormats2KHR,

    // ---- VK_KHR_get_display_properties2 extension commands
    .GetPhysicalDeviceDisplayProperties2KHR = terminator_GetPhysicalDeviceDisplayProperties2KHR,
    .GetPhysicalDeviceDisplayPlaneProperties2KHR = terminator_GetPhysicalDeviceDisplayPlaneProperties2KHR,
    .GetDisplayModeProperties2KHR = terminator_GetDisplayModeProperties2KHR,
    .GetDisplayPlaneCapabilities2KHR = terminator_GetDisplayPlaneCapabilities2KHR,

    // ---- VK_KHR_fragment_shading_rate extension commands
    .GetPhysicalDeviceFragmentShadingRatesKHR = terminator_GetPhysicalDeviceFragmentShadingRatesKHR,

    // ---- VK_KHR_video_encode_queue extension commands
    .GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = terminator_GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR,

    // ---- VK_KHR_cooperative_matrix extension commands
    .GetPhysicalDeviceCooperativeMatrixPropertiesKHR = terminator_GetPhysicalDeviceCooperativeMatrixPropertiesKHR,

    // ---- VK_KHR_calibrated_timestamps extension commands
    .GetPhysicalDeviceCalibrateableTimeDomainsKHR = terminator_GetPhysicalDeviceCalibrateableTimeDomainsKHR,

    // ---- VK_EXT_debug_report extension commands
    .CreateDebugReportCallbackEXT = terminator_CreateDebugReportCallbackEXT,
    .DestroyDebugReportCallbackEXT = terminator_DestroyDebugReportCallbackEXT,
    .DebugReportMessageEXT = terminator_DebugReportMessageEXT,

    // ---- VK_GGP_stream_descriptor_surface extension commands
#if defined(VK_USE_PLATFORM_GGP)
    .CreateStreamDescriptorSurfaceGGP = terminator_CreateStreamDescriptorSurfaceGGP,
#endif // VK_USE_PLATFORM_GGP

    // ---- VK_NV_external_memory_capabilities extension commands
    .GetPhysicalDeviceExternalImageFormatPropertiesNV = terminator_GetPhysicalDeviceExternalImageFormatPropertiesNV,

    // ---- VK_NN_vi_surface extension commands
#if defined(VK_USE_PLATFORM_VI_NN)
    .CreateViSurfaceNN = terminator_CreateViSurfaceNN,
#endif // VK_USE_PLATFORM_VI_NN

    // ---- VK_EXT_direct_mode_display extension commands
    .ReleaseDisplayEXT = terminator_ReleaseDisplayEXT,

    // ---- VK_EXT_acquire_xlib_display extension commands
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    .AcquireXlibDisplayEXT = terminator_AcquireXlibDisplayEXT,
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    .GetRandROutputDisplayEXT = terminator_GetRandROutputDisplayEXT,
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT

    // ---- VK_EXT_display_surface_counter extension commands
    .GetPhysicalDeviceSurfaceCapabilities2EXT = terminator_GetPhysicalDeviceSurfaceCapabilities2EXT,

    // ---- VK_MVK_ios_surface extension commands
#if defined(VK_USE_PLATFORM_IOS_MVK)
    .CreateIOSSurfaceMVK = terminator_CreateIOSSurfaceMVK,
#endif // VK_USE_PLATFORM_IOS_MVK

    // ---- VK_MVK_macos_surface extension commands
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    .CreateMacOSSurfaceMVK = terminator_CreateMacOSSurfaceMVK,
#endif // VK_USE_PLATFORM_MACOS_MVK

    // ---- VK_EXT_debug_utils extension commands
    .CreateDebugUtilsMessengerEXT = terminator_CreateDebugUtilsMessengerEXT,
    .DestroyDebugUtilsMessengerEXT = terminator_DestroyDebugUtilsMessengerEXT,
    .SubmitDebugUtilsMessageEXT = terminator_SubmitDebugUtilsMessageEXT,

    // ---- VK_EXT_descriptor_heap extension commands
    .GetPhysicalDeviceDescriptorSizeEXT = terminator_GetPhysicalDeviceDescriptorSizeEXT,

    // ---- VK_EXT_sample_locations extension commands
    .GetPhysicalDeviceMultisamplePropertiesEXT = terminator_GetPhysicalDeviceMultisamplePropertiesEXT,

    // ---- VK_EXT_calibrated_timestamps extension commands
    .GetPhysicalDeviceCalibrateableTimeDomainsEXT = terminator_GetPhysicalDeviceCalibrateableTimeDomainsEXT,

    // ---- VK_FUCHSIA_imagepipe_surface extension commands
#if defined(VK_USE_PLATFORM_FUCHSIA)
    .CreateImagePipeSurfaceFUCHSIA = terminator_CreateImagePipeSurfaceFUCHSIA,
#endif // VK_USE_PLATFORM_FUCHSIA

    // ---- VK_EXT_metal_surface extension commands
#if defined(VK_USE_PLATFORM_METAL_EXT)
    .CreateMetalSurfaceEXT = terminator_CreateMetalSurfaceEXT,
#endif // VK_USE_PLATFORM_METAL_EXT

    // ---- VK_EXT_tooling_info extension commands
    .GetPhysicalDeviceToolPropertiesEXT = terminator_GetPhysicalDeviceToolPropertiesEXT,

    // ---- VK_NV_cooperative_matrix extension commands
    .GetPhysicalDeviceCooperativeMatrixPropertiesNV = terminator_GetPhysicalDeviceCooperativeMatrixPropertiesNV,

    // ---- VK_NV_coverage_reduction_mode extension commands
    .GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = terminator_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV,

    // ---- VK_EXT_full_screen_exclusive extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .GetPhysicalDeviceSurfacePresentModes2EXT = terminator_GetPhysicalDeviceSurfacePresentModes2EXT,
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_headless_surface extension commands
    .CreateHeadlessSurfaceEXT = terminator_CreateHeadlessSurfaceEXT,

    // ---- VK_EXT_acquire_drm_display extension commands
    .AcquireDrmDisplayEXT = terminator_AcquireDrmDisplayEXT,
    .GetDrmDisplayEXT = terminator_GetDrmDisplayEXT,

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .AcquireWinrtDisplayNV = terminator_AcquireWinrtDisplayNV,
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .GetWinrtDisplayNV = terminator_GetWinrtDisplayNV,
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_EXT_directfb_surface extension commands
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    .CreateDirectFBSurfaceEXT = terminator_CreateDirectFBSurfaceEXT,
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    .GetPhysicalDeviceDirectFBPresentationSupportEXT = terminator_GetPhysicalDeviceDirectFBPresentationSupportEXT,
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

    // ---- VK_QNX_screen_surface extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    .CreateScreenSurfaceQNX = terminator_CreateScreenSurfaceQNX,
#endif // VK_USE_PLATFORM_SCREEN_QNX
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    .GetPhysicalDeviceScreenPresentationSupportQNX = terminator_GetPhysicalDeviceScreenPresentationSupportQNX,
#endif // VK_USE_PLATFORM_SCREEN_QNX

    // ---- VK_ARM_tensors extension commands
    .GetPhysicalDeviceExternalTensorPropertiesARM = terminator_GetPhysicalDeviceExternalTensorPropertiesARM,

    // ---- VK_NV_optical_flow extension commands
    .GetPhysicalDeviceOpticalFlowImageFormatsNV = terminator_GetPhysicalDeviceOpticalFlowImageFormatsNV,

    // ---- VK_NV_cooperative_vector extension commands
    .GetPhysicalDeviceCooperativeVectorPropertiesNV = terminator_GetPhysicalDeviceCooperativeVectorPropertiesNV,

    // ---- VK_ARM_data_graph extension commands
    .GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM = terminator_GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM,
    .GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM = terminator_GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM,

    // ---- VK_ARM_data_graph_instruction_set_tosa extension commands
    .GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM = terminator_GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM,

    // ---- VK_OHOS_surface extension commands
#if defined(VK_USE_PLATFORM_OHOS)
    .CreateSurfaceOHOS = terminator_CreateSurfaceOHOS,
#endif // VK_USE_PLATFORM_OHOS

    // ---- VK_NV_cooperative_matrix2 extension commands
    .GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV = terminator_GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV,

    // ---- VK_ARM_performance_counters_by_region extension commands
    .EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM = terminator_EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM,

    // ---- VK_ARM_shader_instrumentation extension commands
    .EnumeratePhysicalDeviceShaderInstrumentationMetricsARM = terminator_EnumeratePhysicalDeviceShaderInstrumentationMetricsARM,

    // ---- VK_ARM_data_graph_optical_flow extension commands
    .GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM = terminator_GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM,

    // ---- VK_SEC_ubm_surface extension commands
#if defined(VK_USE_PLATFORM_UBM_SEC)
    .CreateUbmSurfaceSEC = terminator_CreateUbmSurfaceSEC,
#endif // VK_USE_PLATFORM_UBM_SEC
#if defined(VK_USE_PLATFORM_UBM_SEC)
    .GetPhysicalDeviceUbmPresentationSupportSEC = terminator_GetPhysicalDeviceUbmPresentationSupportSEC,
#endif // VK_USE_PLATFORM_UBM_SEC
};

// A null-terminated list of all of the instance extensions supported by the loader.
// If an instance extension name is not in this list, but it is exported by one or more of the
// ICDs detected by the loader, then the extension name not in the list will be filtered out
// before passing the list of extensions to the application.
const char *const LOADER_INSTANCE_EXTENSIONS[] = {
                                                  VK_KHR_SURFACE_EXTENSION_NAME,
                                                  VK_KHR_DISPLAY_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_XLIB_KHR)
                                                  VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
                                                  VK_KHR_XCB_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
                                                  VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
                                                  VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
                                                  VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_WIN32_KHR
                                                  VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
                                                  VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME,
                                                  VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
                                                  VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME,
                                                  VK_KHR_EXTERNAL_FENCE_CAPABILITIES_EXTENSION_NAME,
                                                  VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME,
                                                  VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME,
                                                  VK_KHR_SURFACE_PROTECTED_CAPABILITIES_EXTENSION_NAME,
                                                  VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                                                  VK_KHR_SURFACE_MAINTENANCE_1_EXTENSION_NAME,
                                                  VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_GGP)
                                                  VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_GGP
                                                  VK_NV_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
                                                  VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_VI_NN)
                                                  VK_NN_VI_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_VI_NN
                                                  VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
                                                  VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
                                                  VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME,
                                                  VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_IOS_MVK)
                                                  VK_MVK_IOS_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
                                                  VK_MVK_MACOS_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_MACOS_MVK
                                                  VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_FUCHSIA)
                                                  VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_METAL_EXT)
                                                  VK_EXT_METAL_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_METAL_EXT
                                                  VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME,
                                                  VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME,
                                                  VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME,
                                                  VK_EXT_ACQUIRE_DRM_DISPLAY_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
                                                  VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
                                                  VK_QNX_SCREEN_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_SCREEN_QNX
                                                  VK_GOOGLE_SURFACELESS_QUERY_EXTENSION_NAME,
                                                  VK_LUNARG_DIRECT_DRIVER_LOADING_EXTENSION_NAME,
                                                  VK_EXT_LAYER_SETTINGS_EXTENSION_NAME,
                                                  VK_NV_DISPLAY_STEREO_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_OHOS)
                                                  VK_OHOS_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_OHOS
#if defined(VK_USE_PLATFORM_UBM_SEC)
                                                  VK_SEC_UBM_SURFACE_EXTENSION_NAME,
#endif // VK_USE_PLATFORM_UBM_SEC
                                                  NULL };
// clang-format on
