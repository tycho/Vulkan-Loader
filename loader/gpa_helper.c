/*
 *
 * Copyright (c) 2015-2024 The Khronos Group Inc.
 * Copyright (c) 2015-2024 Valve Corporation
 * Copyright (c) 2015-2024 LunarG, Inc.
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
 * Author: Jon Ashburn <jon@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

#include "gpa_helper.h"

#include <string.h>

#include "debug_utils.h"
#include "unknown_function_handling.h"
#include "vk_command_name_hashes.h"
#include "wsi.h"

void *trampoline_get_proc_addr(struct loader_instance *inst, const char *funcName) {
    const uint64_t name_hash = loader_hash_string(funcName);

    // Don't include or check global functions
    switch (name_hash) {
        case XXH3_vkGetInstanceProcAddr:
            if (!strcmp(funcName, "vkGetInstanceProcAddr")) return vkGetInstanceProcAddr;
            break;
        case XXH3_vkDestroyInstance:
            if (!strcmp(funcName, "vkDestroyInstance")) return vkDestroyInstance;
            break;
        case XXH3_vkEnumeratePhysicalDevices:
            if (!strcmp(funcName, "vkEnumeratePhysicalDevices")) return vkEnumeratePhysicalDevices;
            break;
        case XXH3_vkGetPhysicalDeviceFeatures:
            if (!strcmp(funcName, "vkGetPhysicalDeviceFeatures")) return vkGetPhysicalDeviceFeatures;
            break;
        case XXH3_vkGetPhysicalDeviceFormatProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceFormatProperties")) return vkGetPhysicalDeviceFormatProperties;
            break;
        case XXH3_vkGetPhysicalDeviceImageFormatProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceImageFormatProperties")) return vkGetPhysicalDeviceImageFormatProperties;
            break;
        case XXH3_vkGetPhysicalDeviceSparseImageFormatProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceSparseImageFormatProperties"))
                return vkGetPhysicalDeviceSparseImageFormatProperties;
            break;
        case XXH3_vkGetPhysicalDeviceProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceProperties")) return vkGetPhysicalDeviceProperties;
            break;
        case XXH3_vkGetPhysicalDeviceQueueFamilyProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceQueueFamilyProperties")) return vkGetPhysicalDeviceQueueFamilyProperties;
            break;
        case XXH3_vkGetPhysicalDeviceMemoryProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceMemoryProperties")) return vkGetPhysicalDeviceMemoryProperties;
            break;
        case XXH3_vkEnumerateDeviceLayerProperties:
            if (!strcmp(funcName, "vkEnumerateDeviceLayerProperties")) return vkEnumerateDeviceLayerProperties;
            break;
        case XXH3_vkEnumerateDeviceExtensionProperties:
            if (!strcmp(funcName, "vkEnumerateDeviceExtensionProperties")) return vkEnumerateDeviceExtensionProperties;
            break;
        case XXH3_vkCreateDevice:
            if (!strcmp(funcName, "vkCreateDevice")) return vkCreateDevice;
            break;
        case XXH3_vkGetDeviceProcAddr:
            if (!strcmp(funcName, "vkGetDeviceProcAddr")) return vkGetDeviceProcAddr;
            break;
        case XXH3_vkDestroyDevice:
            if (!strcmp(funcName, "vkDestroyDevice")) return vkDestroyDevice;
            break;
        case XXH3_vkGetDeviceQueue:
            if (!strcmp(funcName, "vkGetDeviceQueue")) return vkGetDeviceQueue;
            break;
        case XXH3_vkQueueSubmit:
            if (!strcmp(funcName, "vkQueueSubmit")) return vkQueueSubmit;
            break;
        case XXH3_vkQueueWaitIdle:
            if (!strcmp(funcName, "vkQueueWaitIdle")) return vkQueueWaitIdle;
            break;
        case XXH3_vkDeviceWaitIdle:
            if (!strcmp(funcName, "vkDeviceWaitIdle")) return vkDeviceWaitIdle;
            break;
        case XXH3_vkAllocateMemory:
            if (!strcmp(funcName, "vkAllocateMemory")) return vkAllocateMemory;
            break;
        case XXH3_vkFreeMemory:
            if (!strcmp(funcName, "vkFreeMemory")) return vkFreeMemory;
            break;
        case XXH3_vkMapMemory:
            if (!strcmp(funcName, "vkMapMemory")) return vkMapMemory;
            break;
        case XXH3_vkUnmapMemory:
            if (!strcmp(funcName, "vkUnmapMemory")) return vkUnmapMemory;
            break;
        case XXH3_vkFlushMappedMemoryRanges:
            if (!strcmp(funcName, "vkFlushMappedMemoryRanges")) return vkFlushMappedMemoryRanges;
            break;
        case XXH3_vkInvalidateMappedMemoryRanges:
            if (!strcmp(funcName, "vkInvalidateMappedMemoryRanges")) return vkInvalidateMappedMemoryRanges;
            break;
        case XXH3_vkGetDeviceMemoryCommitment:
            if (!strcmp(funcName, "vkGetDeviceMemoryCommitment")) return vkGetDeviceMemoryCommitment;
            break;
        case XXH3_vkGetImageSparseMemoryRequirements:
            if (!strcmp(funcName, "vkGetImageSparseMemoryRequirements")) return vkGetImageSparseMemoryRequirements;
            break;
        case XXH3_vkGetImageMemoryRequirements:
            if (!strcmp(funcName, "vkGetImageMemoryRequirements")) return vkGetImageMemoryRequirements;
            break;
        case XXH3_vkGetBufferMemoryRequirements:
            if (!strcmp(funcName, "vkGetBufferMemoryRequirements")) return vkGetBufferMemoryRequirements;
            break;
        case XXH3_vkBindImageMemory:
            if (!strcmp(funcName, "vkBindImageMemory")) return vkBindImageMemory;
            break;
        case XXH3_vkBindBufferMemory:
            if (!strcmp(funcName, "vkBindBufferMemory")) return vkBindBufferMemory;
            break;
        case XXH3_vkQueueBindSparse:
            if (!strcmp(funcName, "vkQueueBindSparse")) return vkQueueBindSparse;
            break;
        case XXH3_vkCreateFence:
            if (!strcmp(funcName, "vkCreateFence")) return vkCreateFence;
            break;
        case XXH3_vkDestroyFence:
            if (!strcmp(funcName, "vkDestroyFence")) return vkDestroyFence;
            break;
        case XXH3_vkGetFenceStatus:
            if (!strcmp(funcName, "vkGetFenceStatus")) return vkGetFenceStatus;
            break;
        case XXH3_vkResetFences:
            if (!strcmp(funcName, "vkResetFences")) return vkResetFences;
            break;
        case XXH3_vkWaitForFences:
            if (!strcmp(funcName, "vkWaitForFences")) return vkWaitForFences;
            break;
        case XXH3_vkCreateSemaphore:
            if (!strcmp(funcName, "vkCreateSemaphore")) return vkCreateSemaphore;
            break;
        case XXH3_vkDestroySemaphore:
            if (!strcmp(funcName, "vkDestroySemaphore")) return vkDestroySemaphore;
            break;
        case XXH3_vkCreateEvent:
            if (!strcmp(funcName, "vkCreateEvent")) return vkCreateEvent;
            break;
        case XXH3_vkDestroyEvent:
            if (!strcmp(funcName, "vkDestroyEvent")) return vkDestroyEvent;
            break;
        case XXH3_vkGetEventStatus:
            if (!strcmp(funcName, "vkGetEventStatus")) return vkGetEventStatus;
            break;
        case XXH3_vkSetEvent:
            if (!strcmp(funcName, "vkSetEvent")) return vkSetEvent;
            break;
        case XXH3_vkResetEvent:
            if (!strcmp(funcName, "vkResetEvent")) return vkResetEvent;
            break;
        case XXH3_vkCreateQueryPool:
            if (!strcmp(funcName, "vkCreateQueryPool")) return vkCreateQueryPool;
            break;
        case XXH3_vkDestroyQueryPool:
            if (!strcmp(funcName, "vkDestroyQueryPool")) return vkDestroyQueryPool;
            break;
        case XXH3_vkGetQueryPoolResults:
            if (!strcmp(funcName, "vkGetQueryPoolResults")) return vkGetQueryPoolResults;
            break;
        case XXH3_vkCreateBuffer:
            if (!strcmp(funcName, "vkCreateBuffer")) return vkCreateBuffer;
            break;
        case XXH3_vkDestroyBuffer:
            if (!strcmp(funcName, "vkDestroyBuffer")) return vkDestroyBuffer;
            break;
        case XXH3_vkCreateBufferView:
            if (!strcmp(funcName, "vkCreateBufferView")) return vkCreateBufferView;
            break;
        case XXH3_vkDestroyBufferView:
            if (!strcmp(funcName, "vkDestroyBufferView")) return vkDestroyBufferView;
            break;
        case XXH3_vkCreateImage:
            if (!strcmp(funcName, "vkCreateImage")) return vkCreateImage;
            break;
        case XXH3_vkDestroyImage:
            if (!strcmp(funcName, "vkDestroyImage")) return vkDestroyImage;
            break;
        case XXH3_vkGetImageSubresourceLayout:
            if (!strcmp(funcName, "vkGetImageSubresourceLayout")) return vkGetImageSubresourceLayout;
            break;
        case XXH3_vkCreateImageView:
            if (!strcmp(funcName, "vkCreateImageView")) return vkCreateImageView;
            break;
        case XXH3_vkDestroyImageView:
            if (!strcmp(funcName, "vkDestroyImageView")) return vkDestroyImageView;
            break;
        case XXH3_vkCreateShaderModule:
            if (!strcmp(funcName, "vkCreateShaderModule")) return vkCreateShaderModule;
            break;
        case XXH3_vkDestroyShaderModule:
            if (!strcmp(funcName, "vkDestroyShaderModule")) return vkDestroyShaderModule;
            break;
        case XXH3_vkCreatePipelineCache:
            if (!strcmp(funcName, "vkCreatePipelineCache")) return vkCreatePipelineCache;
            break;
        case XXH3_vkDestroyPipelineCache:
            if (!strcmp(funcName, "vkDestroyPipelineCache")) return vkDestroyPipelineCache;
            break;
        case XXH3_vkGetPipelineCacheData:
            if (!strcmp(funcName, "vkGetPipelineCacheData")) return vkGetPipelineCacheData;
            break;
        case XXH3_vkMergePipelineCaches:
            if (!strcmp(funcName, "vkMergePipelineCaches")) return vkMergePipelineCaches;
            break;
        case XXH3_vkCreateGraphicsPipelines:
            if (!strcmp(funcName, "vkCreateGraphicsPipelines")) return vkCreateGraphicsPipelines;
            break;
        case XXH3_vkCreateComputePipelines:
            if (!strcmp(funcName, "vkCreateComputePipelines")) return vkCreateComputePipelines;
            break;
        case XXH3_vkDestroyPipeline:
            if (!strcmp(funcName, "vkDestroyPipeline")) return vkDestroyPipeline;
            break;
        case XXH3_vkCreatePipelineLayout:
            if (!strcmp(funcName, "vkCreatePipelineLayout")) return vkCreatePipelineLayout;
            break;
        case XXH3_vkDestroyPipelineLayout:
            if (!strcmp(funcName, "vkDestroyPipelineLayout")) return vkDestroyPipelineLayout;
            break;
        case XXH3_vkCreateSampler:
            if (!strcmp(funcName, "vkCreateSampler")) return vkCreateSampler;
            break;
        case XXH3_vkDestroySampler:
            if (!strcmp(funcName, "vkDestroySampler")) return vkDestroySampler;
            break;
        case XXH3_vkCreateDescriptorSetLayout:
            if (!strcmp(funcName, "vkCreateDescriptorSetLayout")) return vkCreateDescriptorSetLayout;
            break;
        case XXH3_vkDestroyDescriptorSetLayout:
            if (!strcmp(funcName, "vkDestroyDescriptorSetLayout")) return vkDestroyDescriptorSetLayout;
            break;
        case XXH3_vkCreateDescriptorPool:
            if (!strcmp(funcName, "vkCreateDescriptorPool")) return vkCreateDescriptorPool;
            break;
        case XXH3_vkDestroyDescriptorPool:
            if (!strcmp(funcName, "vkDestroyDescriptorPool")) return vkDestroyDescriptorPool;
            break;
        case XXH3_vkResetDescriptorPool:
            if (!strcmp(funcName, "vkResetDescriptorPool")) return vkResetDescriptorPool;
            break;
        case XXH3_vkAllocateDescriptorSets:
            if (!strcmp(funcName, "vkAllocateDescriptorSets")) return vkAllocateDescriptorSets;
            break;
        case XXH3_vkFreeDescriptorSets:
            if (!strcmp(funcName, "vkFreeDescriptorSets")) return vkFreeDescriptorSets;
            break;
        case XXH3_vkUpdateDescriptorSets:
            if (!strcmp(funcName, "vkUpdateDescriptorSets")) return vkUpdateDescriptorSets;
            break;
        case XXH3_vkCreateFramebuffer:
            if (!strcmp(funcName, "vkCreateFramebuffer")) return vkCreateFramebuffer;
            break;
        case XXH3_vkDestroyFramebuffer:
            if (!strcmp(funcName, "vkDestroyFramebuffer")) return vkDestroyFramebuffer;
            break;
        case XXH3_vkCreateRenderPass:
            if (!strcmp(funcName, "vkCreateRenderPass")) return vkCreateRenderPass;
            break;
        case XXH3_vkDestroyRenderPass:
            if (!strcmp(funcName, "vkDestroyRenderPass")) return vkDestroyRenderPass;
            break;
        case XXH3_vkGetRenderAreaGranularity:
            if (!strcmp(funcName, "vkGetRenderAreaGranularity")) return vkGetRenderAreaGranularity;
            break;
        case XXH3_vkCreateCommandPool:
            if (!strcmp(funcName, "vkCreateCommandPool")) return vkCreateCommandPool;
            break;
        case XXH3_vkDestroyCommandPool:
            if (!strcmp(funcName, "vkDestroyCommandPool")) return vkDestroyCommandPool;
            break;
        case XXH3_vkResetCommandPool:
            if (!strcmp(funcName, "vkResetCommandPool")) return vkResetCommandPool;
            break;
        case XXH3_vkAllocateCommandBuffers:
            if (!strcmp(funcName, "vkAllocateCommandBuffers")) return vkAllocateCommandBuffers;
            break;
        case XXH3_vkFreeCommandBuffers:
            if (!strcmp(funcName, "vkFreeCommandBuffers")) return vkFreeCommandBuffers;
            break;
        case XXH3_vkBeginCommandBuffer:
            if (!strcmp(funcName, "vkBeginCommandBuffer")) return vkBeginCommandBuffer;
            break;
        case XXH3_vkEndCommandBuffer:
            if (!strcmp(funcName, "vkEndCommandBuffer")) return vkEndCommandBuffer;
            break;
        case XXH3_vkResetCommandBuffer:
            if (!strcmp(funcName, "vkResetCommandBuffer")) return vkResetCommandBuffer;
            break;
        case XXH3_vkCmdBindPipeline:
            if (!strcmp(funcName, "vkCmdBindPipeline")) return vkCmdBindPipeline;
            break;
        case XXH3_vkCmdBindDescriptorSets:
            if (!strcmp(funcName, "vkCmdBindDescriptorSets")) return vkCmdBindDescriptorSets;
            break;
        case XXH3_vkCmdBindVertexBuffers:
            if (!strcmp(funcName, "vkCmdBindVertexBuffers")) return vkCmdBindVertexBuffers;
            break;
        case XXH3_vkCmdBindIndexBuffer:
            if (!strcmp(funcName, "vkCmdBindIndexBuffer")) return vkCmdBindIndexBuffer;
            break;
        case XXH3_vkCmdSetViewport:
            if (!strcmp(funcName, "vkCmdSetViewport")) return vkCmdSetViewport;
            break;
        case XXH3_vkCmdSetScissor:
            if (!strcmp(funcName, "vkCmdSetScissor")) return vkCmdSetScissor;
            break;
        case XXH3_vkCmdSetLineWidth:
            if (!strcmp(funcName, "vkCmdSetLineWidth")) return vkCmdSetLineWidth;
            break;
        case XXH3_vkCmdSetDepthBias:
            if (!strcmp(funcName, "vkCmdSetDepthBias")) return vkCmdSetDepthBias;
            break;
        case XXH3_vkCmdSetBlendConstants:
            if (!strcmp(funcName, "vkCmdSetBlendConstants")) return vkCmdSetBlendConstants;
            break;
        case XXH3_vkCmdSetDepthBounds:
            if (!strcmp(funcName, "vkCmdSetDepthBounds")) return vkCmdSetDepthBounds;
            break;
        case XXH3_vkCmdSetStencilCompareMask:
            if (!strcmp(funcName, "vkCmdSetStencilCompareMask")) return vkCmdSetStencilCompareMask;
            break;
        case XXH3_vkCmdSetStencilWriteMask:
            if (!strcmp(funcName, "vkCmdSetStencilWriteMask")) return vkCmdSetStencilWriteMask;
            break;
        case XXH3_vkCmdSetStencilReference:
            if (!strcmp(funcName, "vkCmdSetStencilReference")) return vkCmdSetStencilReference;
            break;
        case XXH3_vkCmdDraw:
            if (!strcmp(funcName, "vkCmdDraw")) return vkCmdDraw;
            break;
        case XXH3_vkCmdDrawIndexed:
            if (!strcmp(funcName, "vkCmdDrawIndexed")) return vkCmdDrawIndexed;
            break;
        case XXH3_vkCmdDrawIndirect:
            if (!strcmp(funcName, "vkCmdDrawIndirect")) return vkCmdDrawIndirect;
            break;
        case XXH3_vkCmdDrawIndexedIndirect:
            if (!strcmp(funcName, "vkCmdDrawIndexedIndirect")) return vkCmdDrawIndexedIndirect;
            break;
        case XXH3_vkCmdDispatch:
            if (!strcmp(funcName, "vkCmdDispatch")) return vkCmdDispatch;
            break;
        case XXH3_vkCmdDispatchIndirect:
            if (!strcmp(funcName, "vkCmdDispatchIndirect")) return vkCmdDispatchIndirect;
            break;
        case XXH3_vkCmdCopyBuffer:
            if (!strcmp(funcName, "vkCmdCopyBuffer")) return vkCmdCopyBuffer;
            break;
        case XXH3_vkCmdCopyImage:
            if (!strcmp(funcName, "vkCmdCopyImage")) return vkCmdCopyImage;
            break;
        case XXH3_vkCmdBlitImage:
            if (!strcmp(funcName, "vkCmdBlitImage")) return vkCmdBlitImage;
            break;
        case XXH3_vkCmdCopyBufferToImage:
            if (!strcmp(funcName, "vkCmdCopyBufferToImage")) return vkCmdCopyBufferToImage;
            break;
        case XXH3_vkCmdCopyImageToBuffer:
            if (!strcmp(funcName, "vkCmdCopyImageToBuffer")) return vkCmdCopyImageToBuffer;
            break;
        case XXH3_vkCmdUpdateBuffer:
            if (!strcmp(funcName, "vkCmdUpdateBuffer")) return vkCmdUpdateBuffer;
            break;
        case XXH3_vkCmdFillBuffer:
            if (!strcmp(funcName, "vkCmdFillBuffer")) return vkCmdFillBuffer;
            break;
        case XXH3_vkCmdClearColorImage:
            if (!strcmp(funcName, "vkCmdClearColorImage")) return vkCmdClearColorImage;
            break;
        case XXH3_vkCmdClearDepthStencilImage:
            if (!strcmp(funcName, "vkCmdClearDepthStencilImage")) return vkCmdClearDepthStencilImage;
            break;
        case XXH3_vkCmdClearAttachments:
            if (!strcmp(funcName, "vkCmdClearAttachments")) return vkCmdClearAttachments;
            break;
        case XXH3_vkCmdResolveImage:
            if (!strcmp(funcName, "vkCmdResolveImage")) return vkCmdResolveImage;
            break;
        case XXH3_vkCmdSetEvent:
            if (!strcmp(funcName, "vkCmdSetEvent")) return vkCmdSetEvent;
            break;
        case XXH3_vkCmdResetEvent:
            if (!strcmp(funcName, "vkCmdResetEvent")) return vkCmdResetEvent;
            break;
        case XXH3_vkCmdWaitEvents:
            if (!strcmp(funcName, "vkCmdWaitEvents")) return vkCmdWaitEvents;
            break;
        case XXH3_vkCmdPipelineBarrier:
            if (!strcmp(funcName, "vkCmdPipelineBarrier")) return vkCmdPipelineBarrier;
            break;
        case XXH3_vkCmdBeginQuery:
            if (!strcmp(funcName, "vkCmdBeginQuery")) return vkCmdBeginQuery;
            break;
        case XXH3_vkCmdEndQuery:
            if (!strcmp(funcName, "vkCmdEndQuery")) return vkCmdEndQuery;
            break;
        case XXH3_vkCmdResetQueryPool:
            if (!strcmp(funcName, "vkCmdResetQueryPool")) return vkCmdResetQueryPool;
            break;
        case XXH3_vkCmdWriteTimestamp:
            if (!strcmp(funcName, "vkCmdWriteTimestamp")) return vkCmdWriteTimestamp;
            break;
        case XXH3_vkCmdCopyQueryPoolResults:
            if (!strcmp(funcName, "vkCmdCopyQueryPoolResults")) return vkCmdCopyQueryPoolResults;
            break;
        case XXH3_vkCmdPushConstants:
            if (!strcmp(funcName, "vkCmdPushConstants")) return vkCmdPushConstants;
            break;
        case XXH3_vkCmdBeginRenderPass:
            if (!strcmp(funcName, "vkCmdBeginRenderPass")) return vkCmdBeginRenderPass;
            break;
        case XXH3_vkCmdNextSubpass:
            if (!strcmp(funcName, "vkCmdNextSubpass")) return vkCmdNextSubpass;
            break;
        case XXH3_vkCmdEndRenderPass:
            if (!strcmp(funcName, "vkCmdEndRenderPass")) return vkCmdEndRenderPass;
            break;
        case XXH3_vkCmdExecuteCommands:
            if (!strcmp(funcName, "vkCmdExecuteCommands")) return vkCmdExecuteCommands;
            break;

        // Core 1.1 functions
        case XXH3_vkEnumeratePhysicalDeviceGroups:
            if (!strcmp(funcName, "vkEnumeratePhysicalDeviceGroups")) return vkEnumeratePhysicalDeviceGroups;
            break;
        case XXH3_vkGetPhysicalDeviceFeatures2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceFeatures2")) return vkGetPhysicalDeviceFeatures2;
            break;
        case XXH3_vkGetPhysicalDeviceProperties2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceProperties2")) return vkGetPhysicalDeviceProperties2;
            break;
        case XXH3_vkGetPhysicalDeviceFormatProperties2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceFormatProperties2")) return vkGetPhysicalDeviceFormatProperties2;
            break;
        case XXH3_vkGetPhysicalDeviceImageFormatProperties2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceImageFormatProperties2")) return vkGetPhysicalDeviceImageFormatProperties2;
            break;
        case XXH3_vkGetPhysicalDeviceQueueFamilyProperties2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceQueueFamilyProperties2")) return vkGetPhysicalDeviceQueueFamilyProperties2;
            break;
        case XXH3_vkGetPhysicalDeviceMemoryProperties2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceMemoryProperties2")) return vkGetPhysicalDeviceMemoryProperties2;
            break;
        case XXH3_vkGetPhysicalDeviceSparseImageFormatProperties2:
            if (!strcmp(funcName, "vkGetPhysicalDeviceSparseImageFormatProperties2"))
                return vkGetPhysicalDeviceSparseImageFormatProperties2;
            break;
        case XXH3_vkGetPhysicalDeviceExternalBufferProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceExternalBufferProperties"))
                return vkGetPhysicalDeviceExternalBufferProperties;
            break;
        case XXH3_vkGetPhysicalDeviceExternalSemaphoreProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceExternalSemaphoreProperties"))
                return vkGetPhysicalDeviceExternalSemaphoreProperties;
            break;
        case XXH3_vkGetPhysicalDeviceExternalFenceProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceExternalFenceProperties")) return vkGetPhysicalDeviceExternalFenceProperties;
            break;
        case XXH3_vkBindBufferMemory2:
            if (!strcmp(funcName, "vkBindBufferMemory2")) return vkBindBufferMemory2;
            break;
        case XXH3_vkBindImageMemory2:
            if (!strcmp(funcName, "vkBindImageMemory2")) return vkBindImageMemory2;
            break;
        case XXH3_vkGetDeviceGroupPeerMemoryFeatures:
            if (!strcmp(funcName, "vkGetDeviceGroupPeerMemoryFeatures")) return vkGetDeviceGroupPeerMemoryFeatures;
            break;
        case XXH3_vkCmdSetDeviceMask:
            if (!strcmp(funcName, "vkCmdSetDeviceMask")) return vkCmdSetDeviceMask;
            break;
        case XXH3_vkCmdDispatchBase:
            if (!strcmp(funcName, "vkCmdDispatchBase")) return vkCmdDispatchBase;
            break;
        case XXH3_vkGetImageMemoryRequirements2:
            if (!strcmp(funcName, "vkGetImageMemoryRequirements2")) return vkGetImageMemoryRequirements2;
            break;
        case XXH3_vkTrimCommandPool:
            if (!strcmp(funcName, "vkTrimCommandPool")) return vkTrimCommandPool;
            break;
        case XXH3_vkGetDeviceQueue2:
            if (!strcmp(funcName, "vkGetDeviceQueue2")) return vkGetDeviceQueue2;
            break;
        case XXH3_vkCreateSamplerYcbcrConversion:
            if (!strcmp(funcName, "vkCreateSamplerYcbcrConversion")) return vkCreateSamplerYcbcrConversion;
            break;
        case XXH3_vkDestroySamplerYcbcrConversion:
            if (!strcmp(funcName, "vkDestroySamplerYcbcrConversion")) return vkDestroySamplerYcbcrConversion;
            break;
        case XXH3_vkGetDescriptorSetLayoutSupport:
            if (!strcmp(funcName, "vkGetDescriptorSetLayoutSupport")) return vkGetDescriptorSetLayoutSupport;
            break;
        case XXH3_vkCreateDescriptorUpdateTemplate:
            if (!strcmp(funcName, "vkCreateDescriptorUpdateTemplate")) return vkCreateDescriptorUpdateTemplate;
            break;
        case XXH3_vkDestroyDescriptorUpdateTemplate:
            if (!strcmp(funcName, "vkDestroyDescriptorUpdateTemplate")) return vkDestroyDescriptorUpdateTemplate;
            break;
        case XXH3_vkUpdateDescriptorSetWithTemplate:
            if (!strcmp(funcName, "vkUpdateDescriptorSetWithTemplate")) return vkUpdateDescriptorSetWithTemplate;
            break;
        case XXH3_vkGetImageSparseMemoryRequirements2:
            if (!strcmp(funcName, "vkGetImageSparseMemoryRequirements2")) return vkGetImageSparseMemoryRequirements2;
            break;
        case XXH3_vkGetBufferMemoryRequirements2:
            if (!strcmp(funcName, "vkGetBufferMemoryRequirements2")) return vkGetBufferMemoryRequirements2;
            break;

        // Core 1.2 functions
        case XXH3_vkCreateRenderPass2:
            if (!strcmp(funcName, "vkCreateRenderPass2")) return vkCreateRenderPass2;
            break;
        case XXH3_vkCmdBeginRenderPass2:
            if (!strcmp(funcName, "vkCmdBeginRenderPass2")) return vkCmdBeginRenderPass2;
            break;
        case XXH3_vkCmdNextSubpass2:
            if (!strcmp(funcName, "vkCmdNextSubpass2")) return vkCmdNextSubpass2;
            break;
        case XXH3_vkCmdEndRenderPass2:
            if (!strcmp(funcName, "vkCmdEndRenderPass2")) return vkCmdEndRenderPass2;
            break;
        case XXH3_vkCmdDrawIndirectCount:
            if (!strcmp(funcName, "vkCmdDrawIndirectCount")) return vkCmdDrawIndirectCount;
            break;
        case XXH3_vkCmdDrawIndexedIndirectCount:
            if (!strcmp(funcName, "vkCmdDrawIndexedIndirectCount")) return vkCmdDrawIndexedIndirectCount;
            break;
        case XXH3_vkGetSemaphoreCounterValue:
            if (!strcmp(funcName, "vkGetSemaphoreCounterValue")) return vkGetSemaphoreCounterValue;
            break;
        case XXH3_vkWaitSemaphores:
            if (!strcmp(funcName, "vkWaitSemaphores")) return vkWaitSemaphores;
            break;
        case XXH3_vkSignalSemaphore:
            if (!strcmp(funcName, "vkSignalSemaphore")) return vkSignalSemaphore;
            break;
        case XXH3_vkGetBufferDeviceAddress:
            if (!strcmp(funcName, "vkGetBufferDeviceAddress")) return vkGetBufferDeviceAddress;
            break;
        case XXH3_vkGetBufferOpaqueCaptureAddress:
            if (!strcmp(funcName, "vkGetBufferOpaqueCaptureAddress")) return vkGetBufferOpaqueCaptureAddress;
            break;
        case XXH3_vkGetDeviceMemoryOpaqueCaptureAddress:
            if (!strcmp(funcName, "vkGetDeviceMemoryOpaqueCaptureAddress")) return vkGetDeviceMemoryOpaqueCaptureAddress;
            break;
        case XXH3_vkResetQueryPool:
            if (!strcmp(funcName, "vkResetQueryPool")) return vkResetQueryPool;
            break;

        // Core 1.3 functions
        case XXH3_vkGetPhysicalDeviceToolProperties:
            if (!strcmp(funcName, "vkGetPhysicalDeviceToolProperties")) return vkGetPhysicalDeviceToolProperties;
            break;
        case XXH3_vkCreatePrivateDataSlot:
            if (!strcmp(funcName, "vkCreatePrivateDataSlot")) return vkCreatePrivateDataSlot;
            break;
        case XXH3_vkDestroyPrivateDataSlot:
            if (!strcmp(funcName, "vkDestroyPrivateDataSlot")) return vkDestroyPrivateDataSlot;
            break;
        case XXH3_vkSetPrivateData:
            if (!strcmp(funcName, "vkSetPrivateData")) return vkSetPrivateData;
            break;
        case XXH3_vkGetPrivateData:
            if (!strcmp(funcName, "vkGetPrivateData")) return vkGetPrivateData;
            break;
        case XXH3_vkCmdSetEvent2:
            if (!strcmp(funcName, "vkCmdSetEvent2")) return vkCmdSetEvent2;
            break;
        case XXH3_vkCmdResetEvent2:
            if (!strcmp(funcName, "vkCmdResetEvent2")) return vkCmdResetEvent2;
            break;
        case XXH3_vkCmdWaitEvents2:
            if (!strcmp(funcName, "vkCmdWaitEvents2")) return vkCmdWaitEvents2;
            break;
        case XXH3_vkCmdPipelineBarrier2:
            if (!strcmp(funcName, "vkCmdPipelineBarrier2")) return vkCmdPipelineBarrier2;
            break;
        case XXH3_vkCmdWriteTimestamp2:
            if (!strcmp(funcName, "vkCmdWriteTimestamp2")) return vkCmdWriteTimestamp2;
            break;
        case XXH3_vkQueueSubmit2:
            if (!strcmp(funcName, "vkQueueSubmit2")) return vkQueueSubmit2;
            break;
        case XXH3_vkCmdCopyBuffer2:
            if (!strcmp(funcName, "vkCmdCopyBuffer2")) return vkCmdCopyBuffer2;
            break;
        case XXH3_vkCmdCopyImage2:
            if (!strcmp(funcName, "vkCmdCopyImage2")) return vkCmdCopyImage2;
            break;
        case XXH3_vkCmdCopyBufferToImage2:
            if (!strcmp(funcName, "vkCmdCopyBufferToImage2")) return vkCmdCopyBufferToImage2;
            break;
        case XXH3_vkCmdCopyImageToBuffer2:
            if (!strcmp(funcName, "vkCmdCopyImageToBuffer2")) return vkCmdCopyImageToBuffer2;
            break;
        case XXH3_vkCmdBlitImage2:
            if (!strcmp(funcName, "vkCmdBlitImage2")) return vkCmdBlitImage2;
            break;
        case XXH3_vkCmdResolveImage2:
            if (!strcmp(funcName, "vkCmdResolveImage2")) return vkCmdResolveImage2;
            break;
        case XXH3_vkCmdBeginRendering:
            if (!strcmp(funcName, "vkCmdBeginRendering")) return vkCmdBeginRendering;
            break;
        case XXH3_vkCmdEndRendering:
            if (!strcmp(funcName, "vkCmdEndRendering")) return vkCmdEndRendering;
            break;
        case XXH3_vkCmdSetCullMode:
            if (!strcmp(funcName, "vkCmdSetCullMode")) return vkCmdSetCullMode;
            break;
        case XXH3_vkCmdSetFrontFace:
            if (!strcmp(funcName, "vkCmdSetFrontFace")) return vkCmdSetFrontFace;
            break;
        case XXH3_vkCmdSetPrimitiveTopology:
            if (!strcmp(funcName, "vkCmdSetPrimitiveTopology")) return vkCmdSetPrimitiveTopology;
            break;
        case XXH3_vkCmdSetViewportWithCount:
            if (!strcmp(funcName, "vkCmdSetViewportWithCount")) return vkCmdSetViewportWithCount;
            break;
        case XXH3_vkCmdSetScissorWithCount:
            if (!strcmp(funcName, "vkCmdSetScissorWithCount")) return vkCmdSetScissorWithCount;
            break;
        case XXH3_vkCmdBindVertexBuffers2:
            if (!strcmp(funcName, "vkCmdBindVertexBuffers2")) return vkCmdBindVertexBuffers2;
            break;
        case XXH3_vkCmdSetDepthTestEnable:
            if (!strcmp(funcName, "vkCmdSetDepthTestEnable")) return vkCmdSetDepthTestEnable;
            break;
        case XXH3_vkCmdSetDepthWriteEnable:
            if (!strcmp(funcName, "vkCmdSetDepthWriteEnable")) return vkCmdSetDepthWriteEnable;
            break;
        case XXH3_vkCmdSetDepthCompareOp:
            if (!strcmp(funcName, "vkCmdSetDepthCompareOp")) return vkCmdSetDepthCompareOp;
            break;
        case XXH3_vkCmdSetDepthBoundsTestEnable:
            if (!strcmp(funcName, "vkCmdSetDepthBoundsTestEnable")) return vkCmdSetDepthBoundsTestEnable;
            break;
        case XXH3_vkCmdSetStencilTestEnable:
            if (!strcmp(funcName, "vkCmdSetStencilTestEnable")) return vkCmdSetStencilTestEnable;
            break;
        case XXH3_vkCmdSetStencilOp:
            if (!strcmp(funcName, "vkCmdSetStencilOp")) return vkCmdSetStencilOp;
            break;
        case XXH3_vkCmdSetRasterizerDiscardEnable:
            if (!strcmp(funcName, "vkCmdSetRasterizerDiscardEnable")) return vkCmdSetRasterizerDiscardEnable;
            break;
        case XXH3_vkCmdSetDepthBiasEnable:
            if (!strcmp(funcName, "vkCmdSetDepthBiasEnable")) return vkCmdSetDepthBiasEnable;
            break;
        case XXH3_vkCmdSetPrimitiveRestartEnable:
            if (!strcmp(funcName, "vkCmdSetPrimitiveRestartEnable")) return vkCmdSetPrimitiveRestartEnable;
            break;
        case XXH3_vkGetDeviceBufferMemoryRequirements:
            if (!strcmp(funcName, "vkGetDeviceBufferMemoryRequirements")) return vkGetDeviceBufferMemoryRequirements;
            break;
        case XXH3_vkGetDeviceImageMemoryRequirements:
            if (!strcmp(funcName, "vkGetDeviceImageMemoryRequirements")) return vkGetDeviceImageMemoryRequirements;
            break;
        case XXH3_vkGetDeviceImageSparseMemoryRequirements:
            if (!strcmp(funcName, "vkGetDeviceImageSparseMemoryRequirements")) return vkGetDeviceImageSparseMemoryRequirements;
            break;

        // Core 1.4 functions
        case XXH3_vkCmdSetLineStipple:
            if (!strcmp(funcName, "vkCmdSetLineStipple")) return vkCmdSetLineStipple;
            break;
        case XXH3_vkMapMemory2:
            if (!strcmp(funcName, "vkMapMemory2")) return vkMapMemory2;
            break;
        case XXH3_vkUnmapMemory2:
            if (!strcmp(funcName, "vkUnmapMemory2")) return vkUnmapMemory2;
            break;
        case XXH3_vkCmdBindIndexBuffer2:
            if (!strcmp(funcName, "vkCmdBindIndexBuffer2")) return vkCmdBindIndexBuffer2;
            break;
        case XXH3_vkGetRenderingAreaGranularity:
            if (!strcmp(funcName, "vkGetRenderingAreaGranularity")) return vkGetRenderingAreaGranularity;
            break;
        case XXH3_vkGetDeviceImageSubresourceLayout:
            if (!strcmp(funcName, "vkGetDeviceImageSubresourceLayout")) return vkGetDeviceImageSubresourceLayout;
            break;
        case XXH3_vkGetImageSubresourceLayout2:
            if (!strcmp(funcName, "vkGetImageSubresourceLayout2")) return vkGetImageSubresourceLayout2;
            break;
        case XXH3_vkCmdPushDescriptorSet:
            if (!strcmp(funcName, "vkCmdPushDescriptorSet")) return vkCmdPushDescriptorSet;
            break;
        case XXH3_vkCmdPushDescriptorSetWithTemplate:
            if (!strcmp(funcName, "vkCmdPushDescriptorSetWithTemplate")) return vkCmdPushDescriptorSetWithTemplate;
            break;
        case XXH3_vkCmdSetRenderingAttachmentLocations:
            if (!strcmp(funcName, "vkCmdSetRenderingAttachmentLocations")) return vkCmdSetRenderingAttachmentLocations;
            break;
        case XXH3_vkCmdSetRenderingInputAttachmentIndices:
            if (!strcmp(funcName, "vkCmdSetRenderingInputAttachmentIndices")) return vkCmdSetRenderingInputAttachmentIndices;
            break;
        case XXH3_vkCmdBindDescriptorSets2:
            if (!strcmp(funcName, "vkCmdBindDescriptorSets2")) return vkCmdBindDescriptorSets2;
            break;
        case XXH3_vkCmdPushConstants2:
            if (!strcmp(funcName, "vkCmdPushConstants2")) return vkCmdPushConstants2;
            break;
        case XXH3_vkCmdPushDescriptorSet2:
            if (!strcmp(funcName, "vkCmdPushDescriptorSet2")) return vkCmdPushDescriptorSet2;
            break;
        case XXH3_vkCmdPushDescriptorSetWithTemplate2:
            if (!strcmp(funcName, "vkCmdPushDescriptorSetWithTemplate2")) return vkCmdPushDescriptorSetWithTemplate2;
            break;
        case XXH3_vkCopyMemoryToImage:
            if (!strcmp(funcName, "vkCopyMemoryToImage")) return vkCopyMemoryToImage;
            break;
        case XXH3_vkCopyImageToMemory:
            if (!strcmp(funcName, "vkCopyImageToMemory")) return vkCopyImageToMemory;
            break;
        case XXH3_vkCopyImageToImage:
            if (!strcmp(funcName, "vkCopyImageToImage")) return vkCopyImageToImage;
            break;
        case XXH3_vkTransitionImageLayout:
            if (!strcmp(funcName, "vkTransitionImageLayout")) return vkTransitionImageLayout;
            break;
        default:
            break;
    }

    // Instance extensions
    void *addr;
    if (debug_extensions_InstanceGpa(inst, funcName, name_hash, &addr)) return addr;

    if (wsi_swapchain_instance_gpa(inst, funcName, name_hash, &addr)) return addr;

    if (extension_instance_gpa(inst, funcName, name_hash, &addr)) return addr;

    // Unknown physical device extensions
    addr = loader_phys_dev_ext_gpa_tramp(inst, funcName);
    if (NULL != addr) return addr;

    // Unknown device extensions
    addr = loader_dev_ext_gpa_tramp(inst, funcName);
    return addr;
}

void *globalGetProcAddr(const char *name) {
    uint64_t name_hash = loader_hash_string(name);

    switch (name_hash) {
        case XXH3_vkCreateInstance:
            if (!strcmp(name, "vkCreateInstance")) return vkCreateInstance;
            break;
        case XXH3_vkEnumerateInstanceExtensionProperties:
            if (!strcmp(name, "vkEnumerateInstanceExtensionProperties")) return vkEnumerateInstanceExtensionProperties;
            break;
        case XXH3_vkEnumerateInstanceLayerProperties:
            if (!strcmp(name, "vkEnumerateInstanceLayerProperties")) return vkEnumerateInstanceLayerProperties;
            break;
        case XXH3_vkEnumerateInstanceVersion:
            if (!strcmp(name, "vkEnumerateInstanceVersion")) return vkEnumerateInstanceVersion;
            break;
        default:
            break;
    }

    return NULL;
}
