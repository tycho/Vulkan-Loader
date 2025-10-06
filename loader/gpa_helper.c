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

void *trampoline_get_proc_addr(struct loader_instance *inst, const char *name) {
    uint64_t nameHash = XXH3_64bits(name, strlen(name));

    // Don't include or check global functions
    if (nameHash == XXH3_vkGetInstanceProcAddr && !strcmp(name, "vkGetInstanceProcAddr")) return vkGetInstanceProcAddr;
    if (nameHash == XXH3_vkDestroyInstance && !strcmp(name, "vkDestroyInstance")) return vkDestroyInstance;
    if (nameHash == XXH3_vkEnumeratePhysicalDevices && !strcmp(name, "vkEnumeratePhysicalDevices")) return vkEnumeratePhysicalDevices;
    if (nameHash == XXH3_vkGetPhysicalDeviceFeatures && !strcmp(name, "vkGetPhysicalDeviceFeatures")) return vkGetPhysicalDeviceFeatures;
    if (nameHash == XXH3_vkGetPhysicalDeviceFormatProperties && !strcmp(name, "vkGetPhysicalDeviceFormatProperties")) return vkGetPhysicalDeviceFormatProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceImageFormatProperties && !strcmp(name, "vkGetPhysicalDeviceImageFormatProperties")) return vkGetPhysicalDeviceImageFormatProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceSparseImageFormatProperties && !strcmp(name, "vkGetPhysicalDeviceSparseImageFormatProperties")) return vkGetPhysicalDeviceSparseImageFormatProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceProperties && !strcmp(name, "vkGetPhysicalDeviceProperties")) return vkGetPhysicalDeviceProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyProperties && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyProperties")) return vkGetPhysicalDeviceQueueFamilyProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceMemoryProperties && !strcmp(name, "vkGetPhysicalDeviceMemoryProperties")) return vkGetPhysicalDeviceMemoryProperties;
    if (nameHash == XXH3_vkEnumerateDeviceLayerProperties && !strcmp(name, "vkEnumerateDeviceLayerProperties")) return vkEnumerateDeviceLayerProperties;
    if (nameHash == XXH3_vkEnumerateDeviceExtensionProperties && !strcmp(name, "vkEnumerateDeviceExtensionProperties")) return vkEnumerateDeviceExtensionProperties;
    if (nameHash == XXH3_vkCreateDevice && !strcmp(name, "vkCreateDevice")) return vkCreateDevice;
    if (nameHash == XXH3_vkGetDeviceProcAddr && !strcmp(name, "vkGetDeviceProcAddr")) return vkGetDeviceProcAddr;
    if (nameHash == XXH3_vkDestroyDevice && !strcmp(name, "vkDestroyDevice")) return vkDestroyDevice;
    if (nameHash == XXH3_vkGetDeviceQueue && !strcmp(name, "vkGetDeviceQueue")) return vkGetDeviceQueue;
    if (nameHash == XXH3_vkQueueSubmit && !strcmp(name, "vkQueueSubmit")) return vkQueueSubmit;
    if (nameHash == XXH3_vkQueueWaitIdle && !strcmp(name, "vkQueueWaitIdle")) return vkQueueWaitIdle;
    if (nameHash == XXH3_vkDeviceWaitIdle && !strcmp(name, "vkDeviceWaitIdle")) return vkDeviceWaitIdle;
    if (nameHash == XXH3_vkAllocateMemory && !strcmp(name, "vkAllocateMemory")) return vkAllocateMemory;
    if (nameHash == XXH3_vkFreeMemory && !strcmp(name, "vkFreeMemory")) return vkFreeMemory;
    if (nameHash == XXH3_vkMapMemory && !strcmp(name, "vkMapMemory")) return vkMapMemory;
    if (nameHash == XXH3_vkUnmapMemory && !strcmp(name, "vkUnmapMemory")) return vkUnmapMemory;
    if (nameHash == XXH3_vkFlushMappedMemoryRanges && !strcmp(name, "vkFlushMappedMemoryRanges")) return vkFlushMappedMemoryRanges;
    if (nameHash == XXH3_vkInvalidateMappedMemoryRanges && !strcmp(name, "vkInvalidateMappedMemoryRanges")) return vkInvalidateMappedMemoryRanges;
    if (nameHash == XXH3_vkGetDeviceMemoryCommitment && !strcmp(name, "vkGetDeviceMemoryCommitment")) return vkGetDeviceMemoryCommitment;
    if (nameHash == XXH3_vkGetImageSparseMemoryRequirements && !strcmp(name, "vkGetImageSparseMemoryRequirements")) return vkGetImageSparseMemoryRequirements;
    if (nameHash == XXH3_vkGetImageMemoryRequirements && !strcmp(name, "vkGetImageMemoryRequirements")) return vkGetImageMemoryRequirements;
    if (nameHash == XXH3_vkGetBufferMemoryRequirements && !strcmp(name, "vkGetBufferMemoryRequirements")) return vkGetBufferMemoryRequirements;
    if (nameHash == XXH3_vkBindImageMemory && !strcmp(name, "vkBindImageMemory")) return vkBindImageMemory;
    if (nameHash == XXH3_vkBindBufferMemory && !strcmp(name, "vkBindBufferMemory")) return vkBindBufferMemory;
    if (nameHash == XXH3_vkQueueBindSparse && !strcmp(name, "vkQueueBindSparse")) return vkQueueBindSparse;
    if (nameHash == XXH3_vkCreateFence && !strcmp(name, "vkCreateFence")) return vkCreateFence;
    if (nameHash == XXH3_vkDestroyFence && !strcmp(name, "vkDestroyFence")) return vkDestroyFence;
    if (nameHash == XXH3_vkGetFenceStatus && !strcmp(name, "vkGetFenceStatus")) return vkGetFenceStatus;
    if (nameHash == XXH3_vkResetFences && !strcmp(name, "vkResetFences")) return vkResetFences;
    if (nameHash == XXH3_vkWaitForFences && !strcmp(name, "vkWaitForFences")) return vkWaitForFences;
    if (nameHash == XXH3_vkCreateSemaphore && !strcmp(name, "vkCreateSemaphore")) return vkCreateSemaphore;
    if (nameHash == XXH3_vkDestroySemaphore && !strcmp(name, "vkDestroySemaphore")) return vkDestroySemaphore;
    if (nameHash == XXH3_vkCreateEvent && !strcmp(name, "vkCreateEvent")) return vkCreateEvent;
    if (nameHash == XXH3_vkDestroyEvent && !strcmp(name, "vkDestroyEvent")) return vkDestroyEvent;
    if (nameHash == XXH3_vkGetEventStatus && !strcmp(name, "vkGetEventStatus")) return vkGetEventStatus;
    if (nameHash == XXH3_vkSetEvent && !strcmp(name, "vkSetEvent")) return vkSetEvent;
    if (nameHash == XXH3_vkResetEvent && !strcmp(name, "vkResetEvent")) return vkResetEvent;
    if (nameHash == XXH3_vkCreateQueryPool && !strcmp(name, "vkCreateQueryPool")) return vkCreateQueryPool;
    if (nameHash == XXH3_vkDestroyQueryPool && !strcmp(name, "vkDestroyQueryPool")) return vkDestroyQueryPool;
    if (nameHash == XXH3_vkGetQueryPoolResults && !strcmp(name, "vkGetQueryPoolResults")) return vkGetQueryPoolResults;
    if (nameHash == XXH3_vkCreateBuffer && !strcmp(name, "vkCreateBuffer")) return vkCreateBuffer;
    if (nameHash == XXH3_vkDestroyBuffer && !strcmp(name, "vkDestroyBuffer")) return vkDestroyBuffer;
    if (nameHash == XXH3_vkCreateBufferView && !strcmp(name, "vkCreateBufferView")) return vkCreateBufferView;
    if (nameHash == XXH3_vkDestroyBufferView && !strcmp(name, "vkDestroyBufferView")) return vkDestroyBufferView;
    if (nameHash == XXH3_vkCreateImage && !strcmp(name, "vkCreateImage")) return vkCreateImage;
    if (nameHash == XXH3_vkDestroyImage && !strcmp(name, "vkDestroyImage")) return vkDestroyImage;
    if (nameHash == XXH3_vkGetImageSubresourceLayout && !strcmp(name, "vkGetImageSubresourceLayout")) return vkGetImageSubresourceLayout;
    if (nameHash == XXH3_vkCreateImageView && !strcmp(name, "vkCreateImageView")) return vkCreateImageView;
    if (nameHash == XXH3_vkDestroyImageView && !strcmp(name, "vkDestroyImageView")) return vkDestroyImageView;
    if (nameHash == XXH3_vkCreateShaderModule && !strcmp(name, "vkCreateShaderModule")) return vkCreateShaderModule;
    if (nameHash == XXH3_vkDestroyShaderModule && !strcmp(name, "vkDestroyShaderModule")) return vkDestroyShaderModule;
    if (nameHash == XXH3_vkCreatePipelineCache && !strcmp(name, "vkCreatePipelineCache")) return vkCreatePipelineCache;
    if (nameHash == XXH3_vkDestroyPipelineCache && !strcmp(name, "vkDestroyPipelineCache")) return vkDestroyPipelineCache;
    if (nameHash == XXH3_vkGetPipelineCacheData && !strcmp(name, "vkGetPipelineCacheData")) return vkGetPipelineCacheData;
    if (nameHash == XXH3_vkMergePipelineCaches && !strcmp(name, "vkMergePipelineCaches")) return vkMergePipelineCaches;
    if (nameHash == XXH3_vkCreateGraphicsPipelines && !strcmp(name, "vkCreateGraphicsPipelines")) return vkCreateGraphicsPipelines;
    if (nameHash == XXH3_vkCreateComputePipelines && !strcmp(name, "vkCreateComputePipelines")) return vkCreateComputePipelines;
    if (nameHash == XXH3_vkDestroyPipeline && !strcmp(name, "vkDestroyPipeline")) return vkDestroyPipeline;
    if (nameHash == XXH3_vkCreatePipelineLayout && !strcmp(name, "vkCreatePipelineLayout")) return vkCreatePipelineLayout;
    if (nameHash == XXH3_vkDestroyPipelineLayout && !strcmp(name, "vkDestroyPipelineLayout")) return vkDestroyPipelineLayout;
    if (nameHash == XXH3_vkCreateSampler && !strcmp(name, "vkCreateSampler")) return vkCreateSampler;
    if (nameHash == XXH3_vkDestroySampler && !strcmp(name, "vkDestroySampler")) return vkDestroySampler;
    if (nameHash == XXH3_vkCreateDescriptorSetLayout && !strcmp(name, "vkCreateDescriptorSetLayout")) return vkCreateDescriptorSetLayout;
    if (nameHash == XXH3_vkDestroyDescriptorSetLayout && !strcmp(name, "vkDestroyDescriptorSetLayout")) return vkDestroyDescriptorSetLayout;
    if (nameHash == XXH3_vkCreateDescriptorPool && !strcmp(name, "vkCreateDescriptorPool")) return vkCreateDescriptorPool;
    if (nameHash == XXH3_vkDestroyDescriptorPool && !strcmp(name, "vkDestroyDescriptorPool")) return vkDestroyDescriptorPool;
    if (nameHash == XXH3_vkResetDescriptorPool && !strcmp(name, "vkResetDescriptorPool")) return vkResetDescriptorPool;
    if (nameHash == XXH3_vkAllocateDescriptorSets && !strcmp(name, "vkAllocateDescriptorSets")) return vkAllocateDescriptorSets;
    if (nameHash == XXH3_vkFreeDescriptorSets && !strcmp(name, "vkFreeDescriptorSets")) return vkFreeDescriptorSets;
    if (nameHash == XXH3_vkUpdateDescriptorSets && !strcmp(name, "vkUpdateDescriptorSets")) return vkUpdateDescriptorSets;
    if (nameHash == XXH3_vkCreateFramebuffer && !strcmp(name, "vkCreateFramebuffer")) return vkCreateFramebuffer;
    if (nameHash == XXH3_vkDestroyFramebuffer && !strcmp(name, "vkDestroyFramebuffer")) return vkDestroyFramebuffer;
    if (nameHash == XXH3_vkCreateRenderPass && !strcmp(name, "vkCreateRenderPass")) return vkCreateRenderPass;
    if (nameHash == XXH3_vkDestroyRenderPass && !strcmp(name, "vkDestroyRenderPass")) return vkDestroyRenderPass;
    if (nameHash == XXH3_vkGetRenderAreaGranularity && !strcmp(name, "vkGetRenderAreaGranularity")) return vkGetRenderAreaGranularity;
    if (nameHash == XXH3_vkCreateCommandPool && !strcmp(name, "vkCreateCommandPool")) return vkCreateCommandPool;
    if (nameHash == XXH3_vkDestroyCommandPool && !strcmp(name, "vkDestroyCommandPool")) return vkDestroyCommandPool;
    if (nameHash == XXH3_vkResetCommandPool && !strcmp(name, "vkResetCommandPool")) return vkResetCommandPool;
    if (nameHash == XXH3_vkAllocateCommandBuffers && !strcmp(name, "vkAllocateCommandBuffers")) return vkAllocateCommandBuffers;
    if (nameHash == XXH3_vkFreeCommandBuffers && !strcmp(name, "vkFreeCommandBuffers")) return vkFreeCommandBuffers;
    if (nameHash == XXH3_vkBeginCommandBuffer && !strcmp(name, "vkBeginCommandBuffer")) return vkBeginCommandBuffer;
    if (nameHash == XXH3_vkEndCommandBuffer && !strcmp(name, "vkEndCommandBuffer")) return vkEndCommandBuffer;
    if (nameHash == XXH3_vkResetCommandBuffer && !strcmp(name, "vkResetCommandBuffer")) return vkResetCommandBuffer;
    if (nameHash == XXH3_vkCmdBindPipeline && !strcmp(name, "vkCmdBindPipeline")) return vkCmdBindPipeline;
    if (nameHash == XXH3_vkCmdBindDescriptorSets && !strcmp(name, "vkCmdBindDescriptorSets")) return vkCmdBindDescriptorSets;
    if (nameHash == XXH3_vkCmdBindVertexBuffers && !strcmp(name, "vkCmdBindVertexBuffers")) return vkCmdBindVertexBuffers;
    if (nameHash == XXH3_vkCmdBindIndexBuffer && !strcmp(name, "vkCmdBindIndexBuffer")) return vkCmdBindIndexBuffer;
    if (nameHash == XXH3_vkCmdSetViewport && !strcmp(name, "vkCmdSetViewport")) return vkCmdSetViewport;
    if (nameHash == XXH3_vkCmdSetScissor && !strcmp(name, "vkCmdSetScissor")) return vkCmdSetScissor;
    if (nameHash == XXH3_vkCmdSetLineWidth && !strcmp(name, "vkCmdSetLineWidth")) return vkCmdSetLineWidth;
    if (nameHash == XXH3_vkCmdSetDepthBias && !strcmp(name, "vkCmdSetDepthBias")) return vkCmdSetDepthBias;
    if (nameHash == XXH3_vkCmdSetBlendConstants && !strcmp(name, "vkCmdSetBlendConstants")) return vkCmdSetBlendConstants;
    if (nameHash == XXH3_vkCmdSetDepthBounds && !strcmp(name, "vkCmdSetDepthBounds")) return vkCmdSetDepthBounds;
    if (nameHash == XXH3_vkCmdSetStencilCompareMask && !strcmp(name, "vkCmdSetStencilCompareMask")) return vkCmdSetStencilCompareMask;
    if (nameHash == XXH3_vkCmdSetStencilWriteMask && !strcmp(name, "vkCmdSetStencilWriteMask")) return vkCmdSetStencilWriteMask;
    if (nameHash == XXH3_vkCmdSetStencilReference && !strcmp(name, "vkCmdSetStencilReference")) return vkCmdSetStencilReference;
    if (nameHash == XXH3_vkCmdDraw && !strcmp(name, "vkCmdDraw")) return vkCmdDraw;
    if (nameHash == XXH3_vkCmdDrawIndexed && !strcmp(name, "vkCmdDrawIndexed")) return vkCmdDrawIndexed;
    if (nameHash == XXH3_vkCmdDrawIndirect && !strcmp(name, "vkCmdDrawIndirect")) return vkCmdDrawIndirect;
    if (nameHash == XXH3_vkCmdDrawIndexedIndirect && !strcmp(name, "vkCmdDrawIndexedIndirect")) return vkCmdDrawIndexedIndirect;
    if (nameHash == XXH3_vkCmdDispatch && !strcmp(name, "vkCmdDispatch")) return vkCmdDispatch;
    if (nameHash == XXH3_vkCmdDispatchIndirect && !strcmp(name, "vkCmdDispatchIndirect")) return vkCmdDispatchIndirect;
    if (nameHash == XXH3_vkCmdCopyBuffer && !strcmp(name, "vkCmdCopyBuffer")) return vkCmdCopyBuffer;
    if (nameHash == XXH3_vkCmdCopyImage && !strcmp(name, "vkCmdCopyImage")) return vkCmdCopyImage;
    if (nameHash == XXH3_vkCmdBlitImage && !strcmp(name, "vkCmdBlitImage")) return vkCmdBlitImage;
    if (nameHash == XXH3_vkCmdCopyBufferToImage && !strcmp(name, "vkCmdCopyBufferToImage")) return vkCmdCopyBufferToImage;
    if (nameHash == XXH3_vkCmdCopyImageToBuffer && !strcmp(name, "vkCmdCopyImageToBuffer")) return vkCmdCopyImageToBuffer;
    if (nameHash == XXH3_vkCmdUpdateBuffer && !strcmp(name, "vkCmdUpdateBuffer")) return vkCmdUpdateBuffer;
    if (nameHash == XXH3_vkCmdFillBuffer && !strcmp(name, "vkCmdFillBuffer")) return vkCmdFillBuffer;
    if (nameHash == XXH3_vkCmdClearColorImage && !strcmp(name, "vkCmdClearColorImage")) return vkCmdClearColorImage;
    if (nameHash == XXH3_vkCmdClearDepthStencilImage && !strcmp(name, "vkCmdClearDepthStencilImage")) return vkCmdClearDepthStencilImage;
    if (nameHash == XXH3_vkCmdClearAttachments && !strcmp(name, "vkCmdClearAttachments")) return vkCmdClearAttachments;
    if (nameHash == XXH3_vkCmdResolveImage && !strcmp(name, "vkCmdResolveImage")) return vkCmdResolveImage;
    if (nameHash == XXH3_vkCmdSetEvent && !strcmp(name, "vkCmdSetEvent")) return vkCmdSetEvent;
    if (nameHash == XXH3_vkCmdResetEvent && !strcmp(name, "vkCmdResetEvent")) return vkCmdResetEvent;
    if (nameHash == XXH3_vkCmdWaitEvents && !strcmp(name, "vkCmdWaitEvents")) return vkCmdWaitEvents;
    if (nameHash == XXH3_vkCmdPipelineBarrier && !strcmp(name, "vkCmdPipelineBarrier")) return vkCmdPipelineBarrier;
    if (nameHash == XXH3_vkCmdBeginQuery && !strcmp(name, "vkCmdBeginQuery")) return vkCmdBeginQuery;
    if (nameHash == XXH3_vkCmdEndQuery && !strcmp(name, "vkCmdEndQuery")) return vkCmdEndQuery;
    if (nameHash == XXH3_vkCmdResetQueryPool && !strcmp(name, "vkCmdResetQueryPool")) return vkCmdResetQueryPool;
    if (nameHash == XXH3_vkCmdWriteTimestamp && !strcmp(name, "vkCmdWriteTimestamp")) return vkCmdWriteTimestamp;
    if (nameHash == XXH3_vkCmdCopyQueryPoolResults && !strcmp(name, "vkCmdCopyQueryPoolResults")) return vkCmdCopyQueryPoolResults;
    if (nameHash == XXH3_vkCmdPushConstants && !strcmp(name, "vkCmdPushConstants")) return vkCmdPushConstants;
    if (nameHash == XXH3_vkCmdBeginRenderPass && !strcmp(name, "vkCmdBeginRenderPass")) return vkCmdBeginRenderPass;
    if (nameHash == XXH3_vkCmdNextSubpass && !strcmp(name, "vkCmdNextSubpass")) return vkCmdNextSubpass;
    if (nameHash == XXH3_vkCmdEndRenderPass && !strcmp(name, "vkCmdEndRenderPass")) return vkCmdEndRenderPass;
    if (nameHash == XXH3_vkCmdExecuteCommands && !strcmp(name, "vkCmdExecuteCommands")) return vkCmdExecuteCommands;

    // Core 1.1 functions
    if (nameHash == XXH3_vkEnumeratePhysicalDeviceGroups && !strcmp(name, "vkEnumeratePhysicalDeviceGroups")) return vkEnumeratePhysicalDeviceGroups;
    if (nameHash == XXH3_vkGetPhysicalDeviceFeatures2 && !strcmp(name, "vkGetPhysicalDeviceFeatures2")) return vkGetPhysicalDeviceFeatures2;
    if (nameHash == XXH3_vkGetPhysicalDeviceProperties2 && !strcmp(name, "vkGetPhysicalDeviceProperties2")) return vkGetPhysicalDeviceProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceFormatProperties2 && !strcmp(name, "vkGetPhysicalDeviceFormatProperties2")) return vkGetPhysicalDeviceFormatProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceImageFormatProperties2 && !strcmp(name, "vkGetPhysicalDeviceImageFormatProperties2")) return vkGetPhysicalDeviceImageFormatProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceQueueFamilyProperties2 && !strcmp(name, "vkGetPhysicalDeviceQueueFamilyProperties2")) return vkGetPhysicalDeviceQueueFamilyProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceMemoryProperties2 && !strcmp(name, "vkGetPhysicalDeviceMemoryProperties2")) return vkGetPhysicalDeviceMemoryProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceSparseImageFormatProperties2 && !strcmp(name, "vkGetPhysicalDeviceSparseImageFormatProperties2"))
        return vkGetPhysicalDeviceSparseImageFormatProperties2;
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalBufferProperties && !strcmp(name, "vkGetPhysicalDeviceExternalBufferProperties")) return vkGetPhysicalDeviceExternalBufferProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalSemaphoreProperties && !strcmp(name, "vkGetPhysicalDeviceExternalSemaphoreProperties")) return vkGetPhysicalDeviceExternalSemaphoreProperties;
    if (nameHash == XXH3_vkGetPhysicalDeviceExternalFenceProperties && !strcmp(name, "vkGetPhysicalDeviceExternalFenceProperties")) return vkGetPhysicalDeviceExternalFenceProperties;
    if (nameHash == XXH3_vkBindBufferMemory2 && !strcmp(name, "vkBindBufferMemory2")) return vkBindBufferMemory2;
    if (nameHash == XXH3_vkBindImageMemory2 && !strcmp(name, "vkBindImageMemory2")) return vkBindImageMemory2;
    if (nameHash == XXH3_vkGetDeviceGroupPeerMemoryFeatures && !strcmp(name, "vkGetDeviceGroupPeerMemoryFeatures")) return vkGetDeviceGroupPeerMemoryFeatures;
    if (nameHash == XXH3_vkCmdSetDeviceMask && !strcmp(name, "vkCmdSetDeviceMask")) return vkCmdSetDeviceMask;
    if (nameHash == XXH3_vkCmdDispatchBase && !strcmp(name, "vkCmdDispatchBase")) return vkCmdDispatchBase;
    if (nameHash == XXH3_vkGetImageMemoryRequirements2 && !strcmp(name, "vkGetImageMemoryRequirements2")) return vkGetImageMemoryRequirements2;
    if (nameHash == XXH3_vkTrimCommandPool && !strcmp(name, "vkTrimCommandPool")) return vkTrimCommandPool;
    if (nameHash == XXH3_vkGetDeviceQueue2 && !strcmp(name, "vkGetDeviceQueue2")) return vkGetDeviceQueue2;
    if (nameHash == XXH3_vkCreateSamplerYcbcrConversion && !strcmp(name, "vkCreateSamplerYcbcrConversion")) return vkCreateSamplerYcbcrConversion;
    if (nameHash == XXH3_vkDestroySamplerYcbcrConversion && !strcmp(name, "vkDestroySamplerYcbcrConversion")) return vkDestroySamplerYcbcrConversion;
    if (nameHash == XXH3_vkGetDescriptorSetLayoutSupport && !strcmp(name, "vkGetDescriptorSetLayoutSupport")) return vkGetDescriptorSetLayoutSupport;
    if (nameHash == XXH3_vkCreateDescriptorUpdateTemplate && !strcmp(name, "vkCreateDescriptorUpdateTemplate")) return vkCreateDescriptorUpdateTemplate;
    if (nameHash == XXH3_vkDestroyDescriptorUpdateTemplate && !strcmp(name, "vkDestroyDescriptorUpdateTemplate")) return vkDestroyDescriptorUpdateTemplate;
    if (nameHash == XXH3_vkUpdateDescriptorSetWithTemplate && !strcmp(name, "vkUpdateDescriptorSetWithTemplate")) return vkUpdateDescriptorSetWithTemplate;
    if (nameHash == XXH3_vkGetImageSparseMemoryRequirements2 && !strcmp(name, "vkGetImageSparseMemoryRequirements2")) return vkGetImageSparseMemoryRequirements2;
    if (nameHash == XXH3_vkGetBufferMemoryRequirements2 && !strcmp(name, "vkGetBufferMemoryRequirements2")) return vkGetBufferMemoryRequirements2;

    // Core 1.2 functions
    if (nameHash == XXH3_vkCreateRenderPass2 && !strcmp(name, "vkCreateRenderPass2")) return vkCreateRenderPass2;
    if (nameHash == XXH3_vkCmdBeginRenderPass2 && !strcmp(name, "vkCmdBeginRenderPass2")) return vkCmdBeginRenderPass2;
    if (nameHash == XXH3_vkCmdNextSubpass2 && !strcmp(name, "vkCmdNextSubpass2")) return vkCmdNextSubpass2;
    if (nameHash == XXH3_vkCmdEndRenderPass2 && !strcmp(name, "vkCmdEndRenderPass2")) return vkCmdEndRenderPass2;
    if (nameHash == XXH3_vkCmdDrawIndirectCount && !strcmp(name, "vkCmdDrawIndirectCount")) return vkCmdDrawIndirectCount;
    if (nameHash == XXH3_vkCmdDrawIndexedIndirectCount && !strcmp(name, "vkCmdDrawIndexedIndirectCount")) return vkCmdDrawIndexedIndirectCount;
    if (nameHash == XXH3_vkGetSemaphoreCounterValue && !strcmp(name, "vkGetSemaphoreCounterValue")) return vkGetSemaphoreCounterValue;
    if (nameHash == XXH3_vkWaitSemaphores && !strcmp(name, "vkWaitSemaphores")) return vkWaitSemaphores;
    if (nameHash == XXH3_vkSignalSemaphore && !strcmp(name, "vkSignalSemaphore")) return vkSignalSemaphore;
    if (nameHash == XXH3_vkGetBufferDeviceAddress && !strcmp(name, "vkGetBufferDeviceAddress")) return vkGetBufferDeviceAddress;
    if (nameHash == XXH3_vkGetBufferOpaqueCaptureAddress && !strcmp(name, "vkGetBufferOpaqueCaptureAddress")) return vkGetBufferOpaqueCaptureAddress;
    if (nameHash == XXH3_vkGetDeviceMemoryOpaqueCaptureAddress && !strcmp(name, "vkGetDeviceMemoryOpaqueCaptureAddress")) return vkGetDeviceMemoryOpaqueCaptureAddress;
    if (nameHash == XXH3_vkResetQueryPool && !strcmp(name, "vkResetQueryPool")) return vkResetQueryPool;

    // Core 1.3 functions
    if (nameHash == XXH3_vkGetPhysicalDeviceToolProperties && !strcmp(name, "vkGetPhysicalDeviceToolProperties")) return vkGetPhysicalDeviceToolProperties;
    if (nameHash == XXH3_vkCreatePrivateDataSlot && !strcmp(name, "vkCreatePrivateDataSlot")) return vkCreatePrivateDataSlot;
    if (nameHash == XXH3_vkDestroyPrivateDataSlot && !strcmp(name, "vkDestroyPrivateDataSlot")) return vkDestroyPrivateDataSlot;
    if (nameHash == XXH3_vkSetPrivateData && !strcmp(name, "vkSetPrivateData")) return vkSetPrivateData;
    if (nameHash == XXH3_vkGetPrivateData && !strcmp(name, "vkGetPrivateData")) return vkGetPrivateData;
    if (nameHash == XXH3_vkCmdSetEvent2 && !strcmp(name, "vkCmdSetEvent2")) return vkCmdSetEvent2;
    if (nameHash == XXH3_vkCmdResetEvent2 && !strcmp(name, "vkCmdResetEvent2")) return vkCmdResetEvent2;
    if (nameHash == XXH3_vkCmdWaitEvents2 && !strcmp(name, "vkCmdWaitEvents2")) return vkCmdWaitEvents2;
    if (nameHash == XXH3_vkCmdPipelineBarrier2 && !strcmp(name, "vkCmdPipelineBarrier2")) return vkCmdPipelineBarrier2;
    if (nameHash == XXH3_vkCmdWriteTimestamp2 && !strcmp(name, "vkCmdWriteTimestamp2")) return vkCmdWriteTimestamp2;
    if (nameHash == XXH3_vkQueueSubmit2 && !strcmp(name, "vkQueueSubmit2")) return vkQueueSubmit2;
    if (nameHash == XXH3_vkCmdCopyBuffer2 && !strcmp(name, "vkCmdCopyBuffer2")) return vkCmdCopyBuffer2;
    if (nameHash == XXH3_vkCmdCopyImage2 && !strcmp(name, "vkCmdCopyImage2")) return vkCmdCopyImage2;
    if (nameHash == XXH3_vkCmdCopyBufferToImage2 && !strcmp(name, "vkCmdCopyBufferToImage2")) return vkCmdCopyBufferToImage2;
    if (nameHash == XXH3_vkCmdCopyImageToBuffer2 && !strcmp(name, "vkCmdCopyImageToBuffer2")) return vkCmdCopyImageToBuffer2;
    if (nameHash == XXH3_vkCmdBlitImage2 && !strcmp(name, "vkCmdBlitImage2")) return vkCmdBlitImage2;
    if (nameHash == XXH3_vkCmdResolveImage2 && !strcmp(name, "vkCmdResolveImage2")) return vkCmdResolveImage2;
    if (nameHash == XXH3_vkCmdBeginRendering && !strcmp(name, "vkCmdBeginRendering")) return vkCmdBeginRendering;
    if (nameHash == XXH3_vkCmdEndRendering && !strcmp(name, "vkCmdEndRendering")) return vkCmdEndRendering;
    if (nameHash == XXH3_vkCmdSetCullMode && !strcmp(name, "vkCmdSetCullMode")) return vkCmdSetCullMode;
    if (nameHash == XXH3_vkCmdSetFrontFace && !strcmp(name, "vkCmdSetFrontFace")) return vkCmdSetFrontFace;
    if (nameHash == XXH3_vkCmdSetPrimitiveTopology && !strcmp(name, "vkCmdSetPrimitiveTopology")) return vkCmdSetPrimitiveTopology;
    if (nameHash == XXH3_vkCmdSetViewportWithCount && !strcmp(name, "vkCmdSetViewportWithCount")) return vkCmdSetViewportWithCount;
    if (nameHash == XXH3_vkCmdSetScissorWithCount && !strcmp(name, "vkCmdSetScissorWithCount")) return vkCmdSetScissorWithCount;
    if (nameHash == XXH3_vkCmdBindVertexBuffers2 && !strcmp(name, "vkCmdBindVertexBuffers2")) return vkCmdBindVertexBuffers2;
    if (nameHash == XXH3_vkCmdSetDepthTestEnable && !strcmp(name, "vkCmdSetDepthTestEnable")) return vkCmdSetDepthTestEnable;
    if (nameHash == XXH3_vkCmdSetDepthWriteEnable && !strcmp(name, "vkCmdSetDepthWriteEnable")) return vkCmdSetDepthWriteEnable;
    if (nameHash == XXH3_vkCmdSetDepthCompareOp && !strcmp(name, "vkCmdSetDepthCompareOp")) return vkCmdSetDepthCompareOp;
    if (nameHash == XXH3_vkCmdSetDepthBoundsTestEnable && !strcmp(name, "vkCmdSetDepthBoundsTestEnable")) return vkCmdSetDepthBoundsTestEnable;
    if (nameHash == XXH3_vkCmdSetStencilTestEnable && !strcmp(name, "vkCmdSetStencilTestEnable")) return vkCmdSetStencilTestEnable;
    if (nameHash == XXH3_vkCmdSetStencilOp && !strcmp(name, "vkCmdSetStencilOp")) return vkCmdSetStencilOp;
    if (nameHash == XXH3_vkCmdSetRasterizerDiscardEnable && !strcmp(name, "vkCmdSetRasterizerDiscardEnable")) return vkCmdSetRasterizerDiscardEnable;
    if (nameHash == XXH3_vkCmdSetDepthBiasEnable && !strcmp(name, "vkCmdSetDepthBiasEnable")) return vkCmdSetDepthBiasEnable;
    if (nameHash == XXH3_vkCmdSetPrimitiveRestartEnable && !strcmp(name, "vkCmdSetPrimitiveRestartEnable")) return vkCmdSetPrimitiveRestartEnable;
    if (nameHash == XXH3_vkGetDeviceBufferMemoryRequirements && !strcmp(name, "vkGetDeviceBufferMemoryRequirements")) return vkGetDeviceBufferMemoryRequirements;
    if (nameHash == XXH3_vkGetDeviceImageMemoryRequirements && !strcmp(name, "vkGetDeviceImageMemoryRequirements")) return vkGetDeviceImageMemoryRequirements;
    if (nameHash == XXH3_vkGetDeviceImageSparseMemoryRequirements && !strcmp(name, "vkGetDeviceImageSparseMemoryRequirements")) return vkGetDeviceImageSparseMemoryRequirements;

    // Core 1.4 functions
    if (nameHash == XXH3_vkCmdSetLineStipple && !strcmp(name, "vkCmdSetLineStipple")) return vkCmdSetLineStipple;
    if (nameHash == XXH3_vkMapMemory2 && !strcmp(name, "vkMapMemory2")) return vkMapMemory2;
    if (nameHash == XXH3_vkUnmapMemory2 && !strcmp(name, "vkUnmapMemory2")) return vkUnmapMemory2;
    if (nameHash == XXH3_vkCmdBindIndexBuffer2 && !strcmp(name, "vkCmdBindIndexBuffer2")) return vkCmdBindIndexBuffer2;
    if (nameHash == XXH3_vkGetRenderingAreaGranularity && !strcmp(name, "vkGetRenderingAreaGranularity")) return vkGetRenderingAreaGranularity;
    if (nameHash == XXH3_vkGetDeviceImageSubresourceLayout && !strcmp(name, "vkGetDeviceImageSubresourceLayout")) return vkGetDeviceImageSubresourceLayout;
    if (nameHash == XXH3_vkGetImageSubresourceLayout2 && !strcmp(name, "vkGetImageSubresourceLayout2")) return vkGetImageSubresourceLayout2;
    if (nameHash == XXH3_vkCmdPushDescriptorSet && !strcmp(name, "vkCmdPushDescriptorSet")) return vkCmdPushDescriptorSet;
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplate && !strcmp(name, "vkCmdPushDescriptorSetWithTemplate")) return vkCmdPushDescriptorSetWithTemplate;
    if (nameHash == XXH3_vkCmdSetRenderingAttachmentLocations && !strcmp(name, "vkCmdSetRenderingAttachmentLocations")) return vkCmdSetRenderingAttachmentLocations;
    if (nameHash == XXH3_vkCmdSetRenderingInputAttachmentIndices && !strcmp(name, "vkCmdSetRenderingInputAttachmentIndices")) return vkCmdSetRenderingInputAttachmentIndices;
    if (nameHash == XXH3_vkCmdBindDescriptorSets2 && !strcmp(name, "vkCmdBindDescriptorSets2")) return vkCmdBindDescriptorSets2;
    if (nameHash == XXH3_vkCmdPushConstants2 && !strcmp(name, "vkCmdPushConstants2")) return vkCmdPushConstants2;
    if (nameHash == XXH3_vkCmdPushDescriptorSet2 && !strcmp(name, "vkCmdPushDescriptorSet2")) return vkCmdPushDescriptorSet2;
    if (nameHash == XXH3_vkCmdPushDescriptorSetWithTemplate2 && !strcmp(name, "vkCmdPushDescriptorSetWithTemplate2")) return vkCmdPushDescriptorSetWithTemplate2;
    if (nameHash == XXH3_vkCopyMemoryToImage && !strcmp(name, "vkCopyMemoryToImage")) return vkCopyMemoryToImage;
    if (nameHash == XXH3_vkCopyImageToMemory && !strcmp(name, "vkCopyImageToMemory")) return vkCopyImageToMemory;
    if (nameHash == XXH3_vkCopyImageToImage && !strcmp(name, "vkCopyImageToImage")) return vkCopyImageToImage;
    if (nameHash == XXH3_vkTransitionImageLayout && !strcmp(name, "vkTransitionImageLayout")) return vkTransitionImageLayout;

    // Instance extensions
    void *addr;
    if (debug_extensions_InstanceGpa(inst, name, nameHash, &addr)) return addr;

    if (wsi_swapchain_instance_gpa(inst, name, nameHash, &addr)) return addr;

    if (extension_instance_gpa(inst, name, nameHash, &addr)) return addr;

    // Unknown physical device extensions
    addr = loader_phys_dev_ext_gpa_tramp(inst, name);
    if (NULL != addr) return addr;

    // Unknown device extensions
    addr = loader_dev_ext_gpa_tramp(inst, name);
    return addr;
}

void *globalGetProcAddr(const char *name) {
    if (!name) return NULL;
    uint64_t nameHash = XXH3_64bits(name, strlen(name));

    if (nameHash == XXH3_vkCreateInstance && !strcmp(name, "vkCreateInstance")) return vkCreateInstance;
    if (nameHash == XXH3_vkEnumerateInstanceExtensionProperties && !strcmp(name, "vkEnumerateInstanceExtensionProperties")) return vkEnumerateInstanceExtensionProperties;
    if (nameHash == XXH3_vkEnumerateInstanceLayerProperties && !strcmp(name, "vkEnumerateInstanceLayerProperties")) return vkEnumerateInstanceLayerProperties;
    if (nameHash == XXH3_vkEnumerateInstanceVersion && !strcmp(name, "vkEnumerateInstanceVersion")) return vkEnumerateInstanceVersion;

    return NULL;
}
