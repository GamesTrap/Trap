/*
	Volk

	Copyright (C) 2018-2019, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
	Report bugs and download new versions at https://github.com/zeux/volk

	This library is distributed under the MIT License. See notice at the end of this file.

	Modified by: Jan "GamesTrap" Schuerkamp
*/

#ifndef _TRAP_VULKANLOADER_H_
#define _TRAP_VULKANLOADER_H_

#if defined(VULKAN_H_) && !defined(VK_NO_PROTOTYPES)
	#error To use the Vk loader, you need to define VK_NO_PROTOTYPES before including vulkan.h
#endif

/* VK_LOADER_GENERATE_VERSION_DEFINE */
constexpr uint32_t VK_LOADER_HEADER_VERSION = 152;
/* VK_LOADER_GENERATE_VERSION_DEFINE */

#ifndef VK_NO_PROTOTYPES
	#define VK_NO_PROTOTYPES
#endif

#ifndef VULKAN_H_
	#include <vulkan/vulkan.h>
#endif

//Disable VK_NVX_image_view_handle because SDK 140 introduced a change that can't be used with prior versions
#if VK_HEADER_VERSION < 140
	#undef VK_NVX_image_view_handle
#endif

struct VkDeviceTable;

/// <summary>
/// Initialize library by loading Vulkan loader; call this function before creating the Vulkan instance.
/// </summary>
/// <returns>VK_SUCCESS on success and VK_ERROR_INITIALIZATION_FAILED otherwise.</returns>
VkResult VkInitialize();

/// <summary>
/// Initialize library by providing a custom handler to load global symbols.<br>
/// This function can be used instead of VkInitialize.<br>
/// The handler function pointer will be asked to load global Vulkan symbols which require no instance
/// (such as vkCreateInstance, vkEnumerateInstance*and vkEnumerateInstanceVersion if available).
/// </summary>
/// <param name="handler">Function pointer for custom loading</param>
void VkInitializeCustom(PFN_vkGetInstanceProcAddr handler);

/// <summary>
/// Get Vulkan instance version supported by the Vulkan loader, or 0 if Vulkan isn't supported
/// </summary>
/// <returns>0 if VkInitialize wasn't called or failed.</returns>
uint32_t VkGetInstanceVersion();

/// <summary>
/// Load global function pointers using application-created VkInstance; call this function after creating the Vulkan instance.
/// </summary>
/// <param name="instance"></param>
void VkLoadInstance(VkInstance instance);

/// <summary>
/// Load global function pointers using application-created VkInstance; call this function after creating the Vulkan instance.<br>
/// Skips loading device-based function pointers, requires usage of VkLoadDevice afterwards.
/// </summary>
/// <param name="instance"></param>
void VkLoadInstanceOnly(VkInstance instance);

/// <summary>
/// Load global function pointers using application-created VkDevice; call this function after creating the Vulkan device.<br>
/// Note: this is not suitable for applications that want to use multiple VkDevice objects concurrently.
/// </summary>
/// <param name="device"></param>
void VkLoadDevice(VkDevice device);

/// <summary>
/// </summary>
/// <returns>Last VkInstance for which global function pointers have been loaded via VkLoadInstance(), or VK_NULL_HANDLE if VkLoadInstance() has not been called.</returns>
VkInstance VkGetLoadedInstance();

/// <summary>
/// </summary>
/// <returns>Last VkDevice for which global function pointers have been loaded via VkLoadDevice(), or VK_NULL_HANDLE if VkLoadDevice() has not been called.</returns>
VkDevice VkGetLoadedDevice();

/// <summary>
/// Load function pointers using application-created VkDevice into a table.<br>
/// Application should use function pointers from that table instead of using global function pointers.
/// </summary>
/// <param name="table">Pointer where to store loaded functions into</param>
/// <param name="device">Device from which function pointers should be loaded</param>
void VkLoadDeviceTable(struct VkDeviceTable* table, VkDevice device);

//Device-specific function pointer table
struct VkDeviceTable
{
	/* VK_LOADER_GENERATE_DEVICE_TABLE */
#if defined(VK_VERSION_1_0)
	PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
	PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
	PFN_vkAllocateMemory vkAllocateMemory;
	PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
	PFN_vkBindBufferMemory vkBindBufferMemory;
	PFN_vkBindImageMemory vkBindImageMemory;
	PFN_vkCmdBeginQuery vkCmdBeginQuery;
	PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
	PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
	PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
	PFN_vkCmdBindPipeline vkCmdBindPipeline;
	PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
	PFN_vkCmdBlitImage vkCmdBlitImage;
	PFN_vkCmdClearAttachments vkCmdClearAttachments;
	PFN_vkCmdClearColorImage vkCmdClearColorImage;
	PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
	PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
	PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
	PFN_vkCmdCopyImage vkCmdCopyImage;
	PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
	PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
	PFN_vkCmdDispatch vkCmdDispatch;
	PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
	PFN_vkCmdDraw vkCmdDraw;
	PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
	PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
	PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
	PFN_vkCmdEndQuery vkCmdEndQuery;
	PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
	PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
	PFN_vkCmdFillBuffer vkCmdFillBuffer;
	PFN_vkCmdNextSubpass vkCmdNextSubpass;
	PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
	PFN_vkCmdPushConstants vkCmdPushConstants;
	PFN_vkCmdResetEvent vkCmdResetEvent;
	PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
	PFN_vkCmdResolveImage vkCmdResolveImage;
	PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
	PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
	PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
	PFN_vkCmdSetEvent vkCmdSetEvent;
	PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
	PFN_vkCmdSetScissor vkCmdSetScissor;
	PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
	PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
	PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
	PFN_vkCmdSetViewport vkCmdSetViewport;
	PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
	PFN_vkCmdWaitEvents vkCmdWaitEvents;
	PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
	PFN_vkCreateBuffer vkCreateBuffer;
	PFN_vkCreateBufferView vkCreateBufferView;
	PFN_vkCreateCommandPool vkCreateCommandPool;
	PFN_vkCreateComputePipelines vkCreateComputePipelines;
	PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
	PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
	PFN_vkCreateEvent vkCreateEvent;
	PFN_vkCreateFence vkCreateFence;
	PFN_vkCreateFramebuffer vkCreateFramebuffer;
	PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
	PFN_vkCreateImage vkCreateImage;
	PFN_vkCreateImageView vkCreateImageView;
	PFN_vkCreatePipelineCache vkCreatePipelineCache;
	PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
	PFN_vkCreateQueryPool vkCreateQueryPool;
	PFN_vkCreateRenderPass vkCreateRenderPass;
	PFN_vkCreateSampler vkCreateSampler;
	PFN_vkCreateSemaphore vkCreateSemaphore;
	PFN_vkCreateShaderModule vkCreateShaderModule;
	PFN_vkDestroyBuffer vkDestroyBuffer;
	PFN_vkDestroyBufferView vkDestroyBufferView;
	PFN_vkDestroyCommandPool vkDestroyCommandPool;
	PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
	PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
	PFN_vkDestroyDevice vkDestroyDevice;
	PFN_vkDestroyEvent vkDestroyEvent;
	PFN_vkDestroyFence vkDestroyFence;
	PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
	PFN_vkDestroyImage vkDestroyImage;
	PFN_vkDestroyImageView vkDestroyImageView;
	PFN_vkDestroyPipeline vkDestroyPipeline;
	PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
	PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
	PFN_vkDestroyQueryPool vkDestroyQueryPool;
	PFN_vkDestroyRenderPass vkDestroyRenderPass;
	PFN_vkDestroySampler vkDestroySampler;
	PFN_vkDestroySemaphore vkDestroySemaphore;
	PFN_vkDestroyShaderModule vkDestroyShaderModule;
	PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
	PFN_vkEndCommandBuffer vkEndCommandBuffer;
	PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
	PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
	PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
	PFN_vkFreeMemory vkFreeMemory;
	PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
	PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
	PFN_vkGetDeviceQueue vkGetDeviceQueue;
	PFN_vkGetEventStatus vkGetEventStatus;
	PFN_vkGetFenceStatus vkGetFenceStatus;
	PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
	PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
	PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
	PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
	PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
	PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
	PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
	PFN_vkMapMemory vkMapMemory;
	PFN_vkMergePipelineCaches vkMergePipelineCaches;
	PFN_vkQueueBindSparse vkQueueBindSparse;
	PFN_vkQueueSubmit vkQueueSubmit;
	PFN_vkQueueWaitIdle vkQueueWaitIdle;
	PFN_vkResetCommandBuffer vkResetCommandBuffer;
	PFN_vkResetCommandPool vkResetCommandPool;
	PFN_vkResetDescriptorPool vkResetDescriptorPool;
	PFN_vkResetEvent vkResetEvent;
	PFN_vkResetFences vkResetFences;
	PFN_vkSetEvent vkSetEvent;
	PFN_vkUnmapMemory vkUnmapMemory;
	PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
	PFN_vkWaitForFences vkWaitForFences;
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
	PFN_vkBindBufferMemory2 vkBindBufferMemory2;
	PFN_vkBindImageMemory2 vkBindImageMemory2;
	PFN_vkCmdDispatchBase vkCmdDispatchBase;
	PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
	PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
	PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
	PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
	PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
	PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
	PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
	PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
	PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
	PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
	PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
	PFN_vkTrimCommandPool vkTrimCommandPool;
	PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
#endif /* defined(VK_VERSION_1_1) */
#if defined(VK_VERSION_1_2)
	PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
	PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
	PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
	PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
	PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
	PFN_vkCreateRenderPass2 vkCreateRenderPass2;
	PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
	PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
	PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
	PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
	PFN_vkResetQueryPool vkResetQueryPool;
	PFN_vkSignalSemaphore vkSignalSemaphore;
	PFN_vkWaitSemaphores vkWaitSemaphores;
#endif /* defined(VK_VERSION_1_2) */
#if defined(VK_AMD_buffer_marker)
	PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
#endif /* defined(VK_AMD_buffer_marker) */
#if defined(VK_AMD_display_native_hdr)
	PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
#endif /* defined(VK_AMD_display_native_hdr) */
#if defined(VK_AMD_draw_indirect_count)
	PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD;
	PFN_vkCmdDrawIndirectCountAMD vkCmdDrawIndirectCountAMD;
#endif /* defined(VK_AMD_draw_indirect_count) */
#if defined(VK_AMD_shader_info)
	PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#endif /* defined(VK_AMD_shader_info) */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
	PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
	PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif /* defined(VK_ANDROID_external_memory_android_hardware_buffer) */
#if defined(VK_EXT_buffer_device_address)
	PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
#endif /* defined(VK_EXT_buffer_device_address) */
#if defined(VK_EXT_calibrated_timestamps)
	PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
#endif /* defined(VK_EXT_calibrated_timestamps) */
#if defined(VK_EXT_conditional_rendering)
	PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
	PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
#endif /* defined(VK_EXT_conditional_rendering) */
#if defined(VK_EXT_debug_marker)
	PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
	PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
	PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
	PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
	PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
#endif /* defined(VK_EXT_debug_marker) */
#if defined(VK_EXT_discard_rectangles)
	PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
#endif /* defined(VK_EXT_discard_rectangles) */
#if defined(VK_EXT_display_control)
	PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
	PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
	PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
	PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
#endif /* defined(VK_EXT_display_control) */
#if defined(VK_EXT_extended_dynamic_state)
	PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
	PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
	PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
	PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
	PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
	PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
	PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
	PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
	PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
	PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
	PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
	PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
#endif /* defined(VK_EXT_extended_dynamic_state) */
#if defined(VK_EXT_external_memory_host)
	PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
#endif /* defined(VK_EXT_external_memory_host) */
#if defined(VK_EXT_full_screen_exclusive)
	PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
	PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
#endif /* defined(VK_EXT_full_screen_exclusive) */
#if defined(VK_EXT_hdr_metadata)
	PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
#endif /* defined(VK_EXT_hdr_metadata) */
#if defined(VK_EXT_host_query_reset)
	PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
#endif /* defined(VK_EXT_host_query_reset) */
#if defined(VK_EXT_image_drm_format_modifier)
	PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
#endif /* defined(VK_EXT_image_drm_format_modifier) */
#if defined(VK_EXT_line_rasterization)
	PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
#endif /* defined(VK_EXT_line_rasterization) */
#if defined(VK_EXT_private_data)
	PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
	PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
	PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
	PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
#endif /* defined(VK_EXT_private_data) */
#if defined(VK_EXT_sample_locations)
	PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
#endif /* defined(VK_EXT_sample_locations) */
#if defined(VK_EXT_transform_feedback)
	PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
	PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
	PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
	PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
	PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
	PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
#endif /* defined(VK_EXT_transform_feedback) */
#if defined(VK_EXT_validation_cache)
	PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
	PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
	PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
	PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
#endif /* defined(VK_EXT_validation_cache) */
#if defined(VK_GOOGLE_display_timing)
	PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
	PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
#endif /* defined(VK_GOOGLE_display_timing) */
#if defined(VK_INTEL_performance_query)
	PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
	PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
	PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
	PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
	PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
	PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
	PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
	PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
	PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
#endif /* defined(VK_INTEL_performance_query) */
#if defined(VK_KHR_bind_memory2)
	PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
	PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
#endif /* defined(VK_KHR_bind_memory2) */
#if defined(VK_KHR_buffer_device_address)
	PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
	PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
	PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
#endif /* defined(VK_KHR_buffer_device_address) */
#if defined(VK_KHR_create_renderpass2)
	PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
	PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
	PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
	PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
#endif /* defined(VK_KHR_create_renderpass2) */
#if defined(VK_KHR_deferred_host_operations)
	PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
	PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
	PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
	PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
	PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
#endif /* defined(VK_KHR_deferred_host_operations) */
#if defined(VK_KHR_descriptor_update_template)
	PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
	PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
	PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
#endif /* defined(VK_KHR_descriptor_update_template) */
#if defined(VK_KHR_device_group)
	PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
	PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
	PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
#endif /* defined(VK_KHR_device_group) */
#if defined(VK_KHR_display_swapchain)
	PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
#endif /* defined(VK_KHR_display_swapchain) */
#if defined(VK_KHR_draw_indirect_count)
	PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
	PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
#endif /* defined(VK_KHR_draw_indirect_count) */
#if defined(VK_KHR_external_fence_fd)
	PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
	PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
#endif /* defined(VK_KHR_external_fence_fd) */
#if defined(VK_KHR_external_fence_win32)
	PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
	PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
#endif /* defined(VK_KHR_external_fence_win32) */
#if defined(VK_KHR_external_memory_fd)
	PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
	PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#endif /* defined(VK_KHR_external_memory_fd) */
#if defined(VK_KHR_external_memory_win32)
	PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
	PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif /* defined(VK_KHR_external_memory_win32) */
#if defined(VK_KHR_external_semaphore_fd)
	PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
	PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
#endif /* defined(VK_KHR_external_semaphore_fd) */
#if defined(VK_KHR_external_semaphore_win32)
	PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
	PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
#endif /* defined(VK_KHR_external_semaphore_win32) */
#if defined(VK_KHR_get_memory_requirements2)
	PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
	PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
	PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
#endif /* defined(VK_KHR_get_memory_requirements2) */
#if defined(VK_KHR_maintenance1)
	PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
#endif /* defined(VK_KHR_maintenance1) */
#if defined(VK_KHR_maintenance3)
	PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
#endif /* defined(VK_KHR_maintenance3) */
#if defined(VK_KHR_performance_query)
	PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
	PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
#endif /* defined(VK_KHR_performance_query) */
#if defined(VK_KHR_pipeline_executable_properties)
	PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
	PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
	PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
#endif /* defined(VK_KHR_pipeline_executable_properties) */
#if defined(VK_KHR_push_descriptor)
	PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
#endif /* defined(VK_KHR_push_descriptor) */
#if defined(VK_KHR_ray_tracing)
	PFN_vkBindAccelerationStructureMemoryKHR vkBindAccelerationStructureMemoryKHR;
	PFN_vkBuildAccelerationStructureKHR vkBuildAccelerationStructureKHR;
	PFN_vkCmdBuildAccelerationStructureIndirectKHR vkCmdBuildAccelerationStructureIndirectKHR;
	PFN_vkCmdBuildAccelerationStructureKHR vkCmdBuildAccelerationStructureKHR;
	PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
	PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
	PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
	PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
	PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
	PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
	PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
	PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
	PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
	PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
	PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
	PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
	PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
	PFN_vkGetAccelerationStructureMemoryRequirementsKHR vkGetAccelerationStructureMemoryRequirementsKHR;
	PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
	PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
	PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
	PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
#endif /* defined(VK_KHR_ray_tracing) */
#if defined(VK_KHR_sampler_ycbcr_conversion)
	PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
	PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
#endif /* defined(VK_KHR_sampler_ycbcr_conversion) */
#if defined(VK_KHR_shared_presentable_image)
	PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#endif /* defined(VK_KHR_shared_presentable_image) */
#if defined(VK_KHR_swapchain)
	PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
	PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
	PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
	PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
	PFN_vkQueuePresentKHR vkQueuePresentKHR;
#endif /* defined(VK_KHR_swapchain) */
#if defined(VK_KHR_timeline_semaphore)
	PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
	PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
	PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
#endif /* defined(VK_KHR_timeline_semaphore) */
#if defined(VK_NVX_image_view_handle)
	PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
	PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
#endif /* defined(VK_NVX_image_view_handle) */
#if defined(VK_NV_clip_space_w_scaling)
	PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
#endif /* defined(VK_NV_clip_space_w_scaling) */
#if defined(VK_NV_device_diagnostic_checkpoints)
	PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
	PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
#endif /* defined(VK_NV_device_diagnostic_checkpoints) */
#if defined(VK_NV_device_generated_commands)
	PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
	PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
	PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
	PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
	PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
	PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
#endif /* defined(VK_NV_device_generated_commands) */
#if defined(VK_NV_external_memory_win32)
	PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
#endif /* defined(VK_NV_external_memory_win32) */
#if defined(VK_NV_mesh_shader)
	PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
	PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
	PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
#endif /* defined(VK_NV_mesh_shader) */
#if defined(VK_NV_ray_tracing)
	PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
	PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
	PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
	PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
	PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
	PFN_vkCompileDeferredNV vkCompileDeferredNV;
	PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
	PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
	PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
	PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
	PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
	PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
#endif /* defined(VK_NV_ray_tracing) */
#if defined(VK_NV_scissor_exclusive)
	PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
#endif /* defined(VK_NV_scissor_exclusive) */
#if defined(VK_NV_shading_rate_image)
	PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
	PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
	PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
#endif /* defined(VK_NV_shading_rate_image) */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
	PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif /* (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
	PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
#endif /* (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
	PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
	/* VK_LOADER_GENERATE_DEVICE_TABLE */
};

/* VK_LOADER_GENERATE_PROTOTYPES_H */
#if defined(VK_VERSION_1_0)
extern PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
extern PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
extern PFN_vkAllocateMemory vkAllocateMemory;
extern PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
extern PFN_vkBindBufferMemory vkBindBufferMemory;
extern PFN_vkBindImageMemory vkBindImageMemory;
extern PFN_vkCmdBeginQuery vkCmdBeginQuery;
extern PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
extern PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
extern PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
extern PFN_vkCmdBindPipeline vkCmdBindPipeline;
extern PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
extern PFN_vkCmdBlitImage vkCmdBlitImage;
extern PFN_vkCmdClearAttachments vkCmdClearAttachments;
extern PFN_vkCmdClearColorImage vkCmdClearColorImage;
extern PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
extern PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
extern PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
extern PFN_vkCmdCopyImage vkCmdCopyImage;
extern PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
extern PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
extern PFN_vkCmdDispatch vkCmdDispatch;
extern PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
extern PFN_vkCmdDraw vkCmdDraw;
extern PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
extern PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
extern PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
extern PFN_vkCmdEndQuery vkCmdEndQuery;
extern PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
extern PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
extern PFN_vkCmdFillBuffer vkCmdFillBuffer;
extern PFN_vkCmdNextSubpass vkCmdNextSubpass;
extern PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
extern PFN_vkCmdPushConstants vkCmdPushConstants;
extern PFN_vkCmdResetEvent vkCmdResetEvent;
extern PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
extern PFN_vkCmdResolveImage vkCmdResolveImage;
extern PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
extern PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
extern PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
extern PFN_vkCmdSetEvent vkCmdSetEvent;
extern PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
extern PFN_vkCmdSetScissor vkCmdSetScissor;
extern PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
extern PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
extern PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
extern PFN_vkCmdSetViewport vkCmdSetViewport;
extern PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
extern PFN_vkCmdWaitEvents vkCmdWaitEvents;
extern PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
extern PFN_vkCreateBuffer vkCreateBuffer;
extern PFN_vkCreateBufferView vkCreateBufferView;
extern PFN_vkCreateCommandPool vkCreateCommandPool;
extern PFN_vkCreateComputePipelines vkCreateComputePipelines;
extern PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
extern PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
extern PFN_vkCreateDevice vkCreateDevice;
extern PFN_vkCreateEvent vkCreateEvent;
extern PFN_vkCreateFence vkCreateFence;
extern PFN_vkCreateFramebuffer vkCreateFramebuffer;
extern PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
extern PFN_vkCreateImage vkCreateImage;
extern PFN_vkCreateImageView vkCreateImageView;
extern PFN_vkCreateInstance vkCreateInstance;
extern PFN_vkCreatePipelineCache vkCreatePipelineCache;
extern PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
extern PFN_vkCreateQueryPool vkCreateQueryPool;
extern PFN_vkCreateRenderPass vkCreateRenderPass;
extern PFN_vkCreateSampler vkCreateSampler;
extern PFN_vkCreateSemaphore vkCreateSemaphore;
extern PFN_vkCreateShaderModule vkCreateShaderModule;
extern PFN_vkDestroyBuffer vkDestroyBuffer;
extern PFN_vkDestroyBufferView vkDestroyBufferView;
extern PFN_vkDestroyCommandPool vkDestroyCommandPool;
extern PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
extern PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
extern PFN_vkDestroyDevice vkDestroyDevice;
extern PFN_vkDestroyEvent vkDestroyEvent;
extern PFN_vkDestroyFence vkDestroyFence;
extern PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
extern PFN_vkDestroyImage vkDestroyImage;
extern PFN_vkDestroyImageView vkDestroyImageView;
extern PFN_vkDestroyInstance vkDestroyInstance;
extern PFN_vkDestroyPipeline vkDestroyPipeline;
extern PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
extern PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
extern PFN_vkDestroyQueryPool vkDestroyQueryPool;
extern PFN_vkDestroyRenderPass vkDestroyRenderPass;
extern PFN_vkDestroySampler vkDestroySampler;
extern PFN_vkDestroySemaphore vkDestroySemaphore;
extern PFN_vkDestroyShaderModule vkDestroyShaderModule;
extern PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
extern PFN_vkEndCommandBuffer vkEndCommandBuffer;
extern PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
extern PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
extern PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
extern PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
extern PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
extern PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
extern PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
extern PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
extern PFN_vkFreeMemory vkFreeMemory;
extern PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
extern PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
extern PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
extern PFN_vkGetDeviceQueue vkGetDeviceQueue;
extern PFN_vkGetEventStatus vkGetEventStatus;
extern PFN_vkGetFenceStatus vkGetFenceStatus;
extern PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
extern PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
extern PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
extern PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
extern PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
extern PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
extern PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
extern PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
extern PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
extern PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
extern PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
extern PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
extern PFN_vkMapMemory vkMapMemory;
extern PFN_vkMergePipelineCaches vkMergePipelineCaches;
extern PFN_vkQueueBindSparse vkQueueBindSparse;
extern PFN_vkQueueSubmit vkQueueSubmit;
extern PFN_vkQueueWaitIdle vkQueueWaitIdle;
extern PFN_vkResetCommandBuffer vkResetCommandBuffer;
extern PFN_vkResetCommandPool vkResetCommandPool;
extern PFN_vkResetDescriptorPool vkResetDescriptorPool;
extern PFN_vkResetEvent vkResetEvent;
extern PFN_vkResetFences vkResetFences;
extern PFN_vkSetEvent vkSetEvent;
extern PFN_vkUnmapMemory vkUnmapMemory;
extern PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
extern PFN_vkWaitForFences vkWaitForFences;
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
extern PFN_vkBindBufferMemory2 vkBindBufferMemory2;
extern PFN_vkBindImageMemory2 vkBindImageMemory2;
extern PFN_vkCmdDispatchBase vkCmdDispatchBase;
extern PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
extern PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
extern PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
extern PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
extern PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
extern PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
extern PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
extern PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
extern PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
extern PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
extern PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
extern PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
extern PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
extern PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
extern PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
extern PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
extern PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
extern PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
extern PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
extern PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
extern PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
extern PFN_vkTrimCommandPool vkTrimCommandPool;
extern PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
#endif /* defined(VK_VERSION_1_1) */
#if defined(VK_VERSION_1_2)
extern PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
extern PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
extern PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
extern PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
extern PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
extern PFN_vkCreateRenderPass2 vkCreateRenderPass2;
extern PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
extern PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
extern PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
extern PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
extern PFN_vkResetQueryPool vkResetQueryPool;
extern PFN_vkSignalSemaphore vkSignalSemaphore;
extern PFN_vkWaitSemaphores vkWaitSemaphores;
#endif /* defined(VK_VERSION_1_2) */
#if defined(VK_AMD_buffer_marker)
extern PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
#endif /* defined(VK_AMD_buffer_marker) */
#if defined(VK_AMD_display_native_hdr)
extern PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
#endif /* defined(VK_AMD_display_native_hdr) */
#if defined(VK_AMD_draw_indirect_count)
extern PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD;
extern PFN_vkCmdDrawIndirectCountAMD vkCmdDrawIndirectCountAMD;
#endif /* defined(VK_AMD_draw_indirect_count) */
#if defined(VK_AMD_shader_info)
extern PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#endif /* defined(VK_AMD_shader_info) */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
extern PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
extern PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif /* defined(VK_ANDROID_external_memory_android_hardware_buffer) */
#if defined(VK_EXT_acquire_xlib_display)
extern PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
extern PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif /* defined(VK_EXT_acquire_xlib_display) */
#if defined(VK_EXT_buffer_device_address)
extern PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
#endif /* defined(VK_EXT_buffer_device_address) */
#if defined(VK_EXT_calibrated_timestamps)
extern PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
extern PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
#endif /* defined(VK_EXT_calibrated_timestamps) */
#if defined(VK_EXT_conditional_rendering)
extern PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
extern PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
#endif /* defined(VK_EXT_conditional_rendering) */
#if defined(VK_EXT_debug_marker)
extern PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
extern PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
extern PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
extern PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
extern PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
#endif /* defined(VK_EXT_debug_marker) */
#if defined(VK_EXT_debug_report)
extern PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
extern PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
extern PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
#endif /* defined(VK_EXT_debug_report) */
#if defined(VK_EXT_debug_utils)
extern PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
extern PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
extern PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
extern PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
extern PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
extern PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
extern PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
extern PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
extern PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
extern PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
extern PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
#endif /* defined(VK_EXT_debug_utils) */
#if defined(VK_EXT_direct_mode_display)
extern PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#endif /* defined(VK_EXT_direct_mode_display) */
#if defined(VK_EXT_directfb_surface)
extern PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
extern PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif /* defined(VK_EXT_directfb_surface) */
#if defined(VK_EXT_discard_rectangles)
extern PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
#endif /* defined(VK_EXT_discard_rectangles) */
#if defined(VK_EXT_display_control)
extern PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
extern PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
extern PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
extern PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
#endif /* defined(VK_EXT_display_control) */
#if defined(VK_EXT_display_surface_counter)
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
#endif /* defined(VK_EXT_display_surface_counter) */
#if defined(VK_EXT_extended_dynamic_state)
extern PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
extern PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
extern PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
extern PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
extern PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
extern PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
extern PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
extern PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
extern PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
extern PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
extern PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
extern PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
#endif /* defined(VK_EXT_extended_dynamic_state) */
#if defined(VK_EXT_external_memory_host)
extern PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
#endif /* defined(VK_EXT_external_memory_host) */
#if defined(VK_EXT_full_screen_exclusive)
extern PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
extern PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
extern PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
#endif /* defined(VK_EXT_full_screen_exclusive) */
#if defined(VK_EXT_hdr_metadata)
extern PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
#endif /* defined(VK_EXT_hdr_metadata) */
#if defined(VK_EXT_headless_surface)
extern PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#endif /* defined(VK_EXT_headless_surface) */
#if defined(VK_EXT_host_query_reset)
extern PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
#endif /* defined(VK_EXT_host_query_reset) */
#if defined(VK_EXT_image_drm_format_modifier)
extern PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
#endif /* defined(VK_EXT_image_drm_format_modifier) */
#if defined(VK_EXT_line_rasterization)
extern PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
#endif /* defined(VK_EXT_line_rasterization) */
#if defined(VK_EXT_metal_surface)
extern PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif /* defined(VK_EXT_metal_surface) */
#if defined(VK_EXT_private_data)
extern PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
extern PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
extern PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
extern PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
#endif /* defined(VK_EXT_private_data) */
#if defined(VK_EXT_sample_locations)
extern PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
extern PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
#endif /* defined(VK_EXT_sample_locations) */
#if defined(VK_EXT_tooling_info)
extern PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
#endif /* defined(VK_EXT_tooling_info) */
#if defined(VK_EXT_transform_feedback)
extern PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
extern PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
extern PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
extern PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
extern PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
extern PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
#endif /* defined(VK_EXT_transform_feedback) */
#if defined(VK_EXT_validation_cache)
extern PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
extern PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
extern PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
extern PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
#endif /* defined(VK_EXT_validation_cache) */
#if defined(VK_FUCHSIA_imagepipe_surface)
extern PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif /* defined(VK_FUCHSIA_imagepipe_surface) */
#if defined(VK_GGP_stream_descriptor_surface)
extern PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif /* defined(VK_GGP_stream_descriptor_surface) */
#if defined(VK_GOOGLE_display_timing)
extern PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
extern PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
#endif /* defined(VK_GOOGLE_display_timing) */
#if defined(VK_INTEL_performance_query)
extern PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
extern PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
extern PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
extern PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
extern PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
extern PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
extern PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
extern PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
extern PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
#endif /* defined(VK_INTEL_performance_query) */
#if defined(VK_KHR_android_surface)
extern PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif /* defined(VK_KHR_android_surface) */
#if defined(VK_KHR_bind_memory2)
extern PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
extern PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
#endif /* defined(VK_KHR_bind_memory2) */
#if defined(VK_KHR_buffer_device_address)
extern PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
extern PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
extern PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
#endif /* defined(VK_KHR_buffer_device_address) */
#if defined(VK_KHR_create_renderpass2)
extern PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
extern PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
extern PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
extern PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
#endif /* defined(VK_KHR_create_renderpass2) */
#if defined(VK_KHR_deferred_host_operations)
extern PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
extern PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
extern PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
extern PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
extern PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
#endif /* defined(VK_KHR_deferred_host_operations) */
#if defined(VK_KHR_descriptor_update_template)
extern PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
extern PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
extern PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
#endif /* defined(VK_KHR_descriptor_update_template) */
#if defined(VK_KHR_device_group)
extern PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
extern PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
extern PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
#endif /* defined(VK_KHR_device_group) */
#if defined(VK_KHR_device_group_creation)
extern PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
#endif /* defined(VK_KHR_device_group_creation) */
#if defined(VK_KHR_display)
extern PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
extern PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
extern PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
extern PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
extern PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
extern PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
extern PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
#endif /* defined(VK_KHR_display) */
#if defined(VK_KHR_display_swapchain)
extern PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
#endif /* defined(VK_KHR_display_swapchain) */
#if defined(VK_KHR_draw_indirect_count)
extern PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
extern PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
#endif /* defined(VK_KHR_draw_indirect_count) */
#if defined(VK_KHR_external_fence_capabilities)
extern PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
#endif /* defined(VK_KHR_external_fence_capabilities) */
#if defined(VK_KHR_external_fence_fd)
extern PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
extern PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
#endif /* defined(VK_KHR_external_fence_fd) */
#if defined(VK_KHR_external_fence_win32)
extern PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
extern PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
#endif /* defined(VK_KHR_external_fence_win32) */
#if defined(VK_KHR_external_memory_capabilities)
extern PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
#endif /* defined(VK_KHR_external_memory_capabilities) */
#if defined(VK_KHR_external_memory_fd)
extern PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
extern PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#endif /* defined(VK_KHR_external_memory_fd) */
#if defined(VK_KHR_external_memory_win32)
extern PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
extern PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif /* defined(VK_KHR_external_memory_win32) */
#if defined(VK_KHR_external_semaphore_capabilities)
extern PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
#endif /* defined(VK_KHR_external_semaphore_capabilities) */
#if defined(VK_KHR_external_semaphore_fd)
extern PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
extern PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
#endif /* defined(VK_KHR_external_semaphore_fd) */
#if defined(VK_KHR_external_semaphore_win32)
extern PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
extern PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
#endif /* defined(VK_KHR_external_semaphore_win32) */
#if defined(VK_KHR_get_display_properties2)
extern PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
extern PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
extern PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
extern PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
#endif /* defined(VK_KHR_get_display_properties2) */
#if defined(VK_KHR_get_memory_requirements2)
extern PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
extern PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
extern PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
#endif /* defined(VK_KHR_get_memory_requirements2) */
#if defined(VK_KHR_get_physical_device_properties2)
extern PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
extern PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
extern PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
extern PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
extern PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
#endif /* defined(VK_KHR_get_physical_device_properties2) */
#if defined(VK_KHR_get_surface_capabilities2)
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
#endif /* defined(VK_KHR_get_surface_capabilities2) */
#if defined(VK_KHR_maintenance1)
extern PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
#endif /* defined(VK_KHR_maintenance1) */
#if defined(VK_KHR_maintenance3)
extern PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
#endif /* defined(VK_KHR_maintenance3) */
#if defined(VK_KHR_performance_query)
extern PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
extern PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
extern PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
extern PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
#endif /* defined(VK_KHR_performance_query) */
#if defined(VK_KHR_pipeline_executable_properties)
extern PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
extern PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
extern PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
#endif /* defined(VK_KHR_pipeline_executable_properties) */
#if defined(VK_KHR_push_descriptor)
extern PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
#endif /* defined(VK_KHR_push_descriptor) */
#if defined(VK_KHR_ray_tracing)
extern PFN_vkBindAccelerationStructureMemoryKHR vkBindAccelerationStructureMemoryKHR;
extern PFN_vkBuildAccelerationStructureKHR vkBuildAccelerationStructureKHR;
extern PFN_vkCmdBuildAccelerationStructureIndirectKHR vkCmdBuildAccelerationStructureIndirectKHR;
extern PFN_vkCmdBuildAccelerationStructureKHR vkCmdBuildAccelerationStructureKHR;
extern PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
extern PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
extern PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
extern PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
extern PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
extern PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
extern PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
extern PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
extern PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
extern PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
extern PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
extern PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
extern PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
extern PFN_vkGetAccelerationStructureMemoryRequirementsKHR vkGetAccelerationStructureMemoryRequirementsKHR;
extern PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
extern PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
extern PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
extern PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
#endif /* defined(VK_KHR_ray_tracing) */
#if defined(VK_KHR_sampler_ycbcr_conversion)
extern PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
extern PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
#endif /* defined(VK_KHR_sampler_ycbcr_conversion) */
#if defined(VK_KHR_shared_presentable_image)
extern PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#endif /* defined(VK_KHR_shared_presentable_image) */
#if defined(VK_KHR_surface)
extern PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
#endif /* defined(VK_KHR_surface) */
#if defined(VK_KHR_swapchain)
extern PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
extern PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
extern PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
extern PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
extern PFN_vkQueuePresentKHR vkQueuePresentKHR;
#endif /* defined(VK_KHR_swapchain) */
#if defined(VK_KHR_timeline_semaphore)
extern PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
extern PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
extern PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
#endif /* defined(VK_KHR_timeline_semaphore) */
#if defined(VK_KHR_wayland_surface)
extern PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
extern PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif /* defined(VK_KHR_wayland_surface) */
#if defined(VK_KHR_win32_surface)
extern PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
extern PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif /* defined(VK_KHR_win32_surface) */
#if defined(VK_KHR_xcb_surface)
extern PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
extern PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif /* defined(VK_KHR_xcb_surface) */
#if defined(VK_KHR_xlib_surface)
extern PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
extern PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif /* defined(VK_KHR_xlib_surface) */
#if defined(VK_MVK_ios_surface)
extern PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif /* defined(VK_MVK_ios_surface) */
#if defined(VK_MVK_macos_surface)
extern PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif /* defined(VK_MVK_macos_surface) */
#if defined(VK_NN_vi_surface)
extern PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif /* defined(VK_NN_vi_surface) */
#if defined(VK_NVX_image_view_handle)
extern PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
extern PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
#endif /* defined(VK_NVX_image_view_handle) */
#if defined(VK_NV_clip_space_w_scaling)
extern PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
#endif /* defined(VK_NV_clip_space_w_scaling) */
#if defined(VK_NV_cooperative_matrix)
extern PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
#endif /* defined(VK_NV_cooperative_matrix) */
#if defined(VK_NV_coverage_reduction_mode)
extern PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#endif /* defined(VK_NV_coverage_reduction_mode) */
#if defined(VK_NV_device_diagnostic_checkpoints)
extern PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
extern PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
#endif /* defined(VK_NV_device_diagnostic_checkpoints) */
#if defined(VK_NV_device_generated_commands)
extern PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
extern PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
extern PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
extern PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
extern PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
extern PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
#endif /* defined(VK_NV_device_generated_commands) */
#if defined(VK_NV_external_memory_capabilities)
extern PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#endif /* defined(VK_NV_external_memory_capabilities) */
#if defined(VK_NV_external_memory_win32)
extern PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
#endif /* defined(VK_NV_external_memory_win32) */
#if defined(VK_NV_mesh_shader)
extern PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
extern PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
extern PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
#endif /* defined(VK_NV_mesh_shader) */
#if defined(VK_NV_ray_tracing)
extern PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
extern PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
extern PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
extern PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
extern PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
extern PFN_vkCompileDeferredNV vkCompileDeferredNV;
extern PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
extern PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
extern PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
extern PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
extern PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
extern PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
#endif /* defined(VK_NV_ray_tracing) */
#if defined(VK_NV_scissor_exclusive)
extern PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
#endif /* defined(VK_NV_scissor_exclusive) */
#if defined(VK_NV_shading_rate_image)
extern PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
extern PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
extern PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
#endif /* defined(VK_NV_shading_rate_image) */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
extern PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif /* (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
extern PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
#endif /* (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
extern PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
extern PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
extern PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
extern PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
/* VK_LOADER_GENERATE_PROTOTYPES_H */

#endif /*_TRAP_VULKANLOADER_H_*/

#ifdef _WIN32
	typedef const char* LPCSTR;
	typedef struct HINSTANCE__* HINSTANCE;
	typedef HINSTANCE HMODULE;
	#ifdef _WIN64
		typedef __int64(__stdcall* FARPROC)();
	#else
		typedef int(__stdcall* FARPROC)();
	#endif
#else
	#include <dlfcn.h>
#endif

#ifdef _WIN32
	#include "Utils/Win.h"
	
	#ifdef far
		#undef far
	#endif
	#ifdef min
		#undef min
	#endif
	#ifdef max
		#undef max
	#endif
	#ifdef CreateWindow
		#undef CreateWindow
	#endif
	#ifdef GetWindowStyle
		#undef GetWindowStyle
	#endif
	#ifdef GetWindowExStyle
		#undef GetWindowExStyle
	#endif
	#ifdef IsMaximized
		#undef IsMaximized
	#endif
	#ifdef IsMinimized
		#undef IsMinimized
	#endif
	#ifdef IsRestored
		#undef IsRestored
	#endif
	#ifdef near
		#undef near
	#endif
	#ifdef DELETE
		#undef DELETE
	#endif
	#ifdef isnan
		#undef isnan
	#endif
	#ifdef isinf
		#undef isinf
	#endif
	#ifdef log2
		#undef log2
	#endif
	#ifdef GetKeyboardLayoutName
		#undef GetKeyboardLayoutName
	#endif
	#ifdef GetMessage
		#undef GetMessage
	#endif
	#ifdef CreateDirectory
		#undef CreateDirectory
	#endif
	#ifdef DeleteFile
		#undef DeleteFile
	#endif
#endif

static VkInstance loadedInstance = VK_NULL_HANDLE;
static VkDevice loadedDevice = VK_NULL_HANDLE;

static void VkGenLoadLoader(void* context, PFN_vkVoidFunction(*load)(void*, const char*));
static void VkGenLoadInstance(void* context, PFN_vkVoidFunction(*load)(void*, const char*));
static void VkGenLoadDevice(void* context, PFN_vkVoidFunction(*load)(void*, const char*));
static void VkGenLoadDeviceTable(struct VkDeviceTable* table, void* context, PFN_vkVoidFunction(*load)(void*, const char*));

static PFN_vkVoidFunction vkGetInstanceProcAddrStub(void* context, const char* name)
{
	return vkGetInstanceProcAddr(static_cast<VkInstance>(context), name);
}

static PFN_vkVoidFunction vkGetDeviceProcAddrStub(void* context, const char* name)
{
	return vkGetDeviceProcAddr(static_cast<VkDevice>(context), name);
}

inline VkResult VkInitialize()
{
#if defined(_WIN32)
	const HMODULE module = LoadLibraryA("vulkan-1.dll");
	if (!module)
		return VK_ERROR_INITIALIZATION_FAILED;

	//Note: function pointer is cast through void function pointer to silence cast-function-type warning on gcc8
	vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(reinterpret_cast<void(*)()>(GetProcAddress(module, "vkGetInstanceProcAddr")));
#else
	void* module = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
	if (!module)
		module = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
	if (!module)
		return VK_ERROR_INITIALIZATION_FAILED;

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(module, "vkGetInstanceProcAddr");
#endif

	VkGenLoadLoader(nullptr, vkGetInstanceProcAddrStub);

	return VK_SUCCESS;
}

inline void VkInitializeCustom(PFN_vkGetInstanceProcAddr handler)
{
	vkGetInstanceProcAddr = handler;

	VkGenLoadLoader(nullptr, vkGetInstanceProcAddrStub);
}

inline uint32_t VkGetInstanceVersion()
{
#if defined(VK_VERSION_1_1)
	uint32_t apiVersion = 0;
	if (vkEnumerateInstanceVersion && vkEnumerateInstanceVersion(&apiVersion) == VK_SUCCESS)
		return apiVersion;
#endif

	if (vkCreateInstance)
		return VK_API_VERSION_1_0;

	return 0;
}

inline void VkLoadInstance(VkInstance instance)
{
	loadedInstance = instance;
	VkGenLoadInstance(instance, vkGetInstanceProcAddrStub);
	VkGenLoadDevice(instance, vkGetInstanceProcAddrStub);
}

inline void VkLoadInstanceOnly(VkInstance instance)
{
	loadedInstance = instance;
	VkGenLoadInstance(instance, vkGetInstanceProcAddrStub);
}

inline VkInstance VkGetLoadedInstance()
{
	return loadedInstance;
}

inline void VkLoadDevice(VkDevice device)
{
	loadedDevice = device;
	VkGenLoadDevice(device, vkGetDeviceProcAddrStub);
}

inline VkDevice VkGetLoadedDevice()
{
	return loadedDevice;
}

inline void VkLoadDeviceTable(struct VkDeviceTable* table, VkDevice device)
{
	VkGenLoadDeviceTable(table, device, vkGetDeviceProcAddrStub);
}

static void VkGenLoadLoader(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	/* VK_LOADER_GENERATE_LOAD_LOADER */
#if defined(VK_VERSION_1_0)
	vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(load(context, "vkCreateInstance"));
	vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(load(context, "vkEnumerateInstanceExtensionProperties"));
	vkEnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(load(context, "vkEnumerateInstanceLayerProperties"));
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
	vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(load(context, "vkEnumerateInstanceVersion"));
#endif /* defined(VK_VERSION_1_1) */
	/* VK_LOADER_GENERATE_LOAD_LOADER */
}

static void VkGenLoadInstance(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	/* VK_LOADER_GENERATE_LOAD_INSTANCE */
#if defined(VK_VERSION_1_0)
	vkCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(load(context, "vkCreateDevice"));
	vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(load(context, "vkDestroyInstance"));
	vkEnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(load(context, "vkEnumerateDeviceExtensionProperties"));
	vkEnumerateDeviceLayerProperties = reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(load(context, "vkEnumerateDeviceLayerProperties"));
	vkEnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(load(context, "vkEnumeratePhysicalDevices"));
	vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(load(context, "vkGetDeviceProcAddr"));
	vkGetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(load(context, "vkGetPhysicalDeviceFeatures"));
	vkGetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(load(context, "vkGetPhysicalDeviceFormatProperties"));
	vkGetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(load(context, "vkGetPhysicalDeviceImageFormatProperties"));
	vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(load(context, "vkGetPhysicalDeviceMemoryProperties"));
	vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(load(context, "vkGetPhysicalDeviceProperties"));
	vkGetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(load(context, "vkGetPhysicalDeviceQueueFamilyProperties"));
	vkGetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(load(context, "vkGetPhysicalDeviceSparseImageFormatProperties"));
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
	vkEnumeratePhysicalDeviceGroups = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(load(context, "vkEnumeratePhysicalDeviceGroups"));
	vkGetPhysicalDeviceExternalBufferProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(load(context, "vkGetPhysicalDeviceExternalBufferProperties"));
	vkGetPhysicalDeviceExternalFenceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(load(context, "vkGetPhysicalDeviceExternalFenceProperties"));
	vkGetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(load(context, "vkGetPhysicalDeviceExternalSemaphoreProperties"));
	vkGetPhysicalDeviceFeatures2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(load(context, "vkGetPhysicalDeviceFeatures2"));
	vkGetPhysicalDeviceFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(load(context, "vkGetPhysicalDeviceFormatProperties2"));
	vkGetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(load(context, "vkGetPhysicalDeviceImageFormatProperties2"));
	vkGetPhysicalDeviceMemoryProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(load(context, "vkGetPhysicalDeviceMemoryProperties2"));
	vkGetPhysicalDeviceProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(load(context, "vkGetPhysicalDeviceProperties2"));
	vkGetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(load(context, "vkGetPhysicalDeviceQueueFamilyProperties2"));
	vkGetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(load(context, "vkGetPhysicalDeviceSparseImageFormatProperties2"));
#endif /* defined(VK_VERSION_1_1) */
#if defined(VK_EXT_acquire_xlib_display)
	vkAcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(load(context, "vkAcquireXlibDisplayEXT"));
	vkGetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(load(context, "vkGetRandROutputDisplayEXT"));
#endif /* defined(VK_EXT_acquire_xlib_display) */
#if defined(VK_EXT_calibrated_timestamps)
	vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT>(load(context, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#endif /* defined(VK_EXT_calibrated_timestamps) */
#if defined(VK_EXT_debug_report)
	vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(load(context, "vkCreateDebugReportCallbackEXT"));
	vkDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(load(context, "vkDebugReportMessageEXT"));
	vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(load(context, "vkDestroyDebugReportCallbackEXT"));
#endif /* defined(VK_EXT_debug_report) */
#if defined(VK_EXT_debug_utils)
	vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(load(context, "vkCmdBeginDebugUtilsLabelEXT"));
	vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(load(context, "vkCmdEndDebugUtilsLabelEXT"));
	vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(load(context, "vkCmdInsertDebugUtilsLabelEXT"));
	vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(load(context, "vkCreateDebugUtilsMessengerEXT"));
	vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(load(context, "vkDestroyDebugUtilsMessengerEXT"));
	vkQueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(load(context, "vkQueueBeginDebugUtilsLabelEXT"));
	vkQueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(load(context, "vkQueueEndDebugUtilsLabelEXT"));
	vkQueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(load(context, "vkQueueInsertDebugUtilsLabelEXT"));
	vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(load(context, "vkSetDebugUtilsObjectNameEXT"));
	vkSetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(load(context, "vkSetDebugUtilsObjectTagEXT"));
	vkSubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(load(context, "vkSubmitDebugUtilsMessageEXT"));
#endif /* defined(VK_EXT_debug_utils) */
#if defined(VK_EXT_direct_mode_display)
	vkReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(load(context, "vkReleaseDisplayEXT"));
#endif /* defined(VK_EXT_direct_mode_display) */
#if defined(VK_EXT_directfb_surface)
	vkCreateDirectFBSurfaceEXT = reinterpret_cast<PFN_vkCreateDirectFBSurfaceEXT>(load(context, "vkCreateDirectFBSurfaceEXT"));
	vkGetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT>(load(context, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
#endif /* defined(VK_EXT_directfb_surface) */
#if defined(VK_EXT_display_surface_counter)
	vkGetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(load(context, "vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
#endif /* defined(VK_EXT_display_surface_counter) */
#if defined(VK_EXT_full_screen_exclusive)
	vkGetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT>(load(context, "vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif /* defined(VK_EXT_full_screen_exclusive) */
#if defined(VK_EXT_headless_surface)
	vkCreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(load(context, "vkCreateHeadlessSurfaceEXT"));
#endif /* defined(VK_EXT_headless_surface) */
#if defined(VK_EXT_metal_surface)
	vkCreateMetalSurfaceEXT = reinterpret_cast<PFN_vkCreateMetalSurfaceEXT>(load(context, "vkCreateMetalSurfaceEXT"));
#endif /* defined(VK_EXT_metal_surface) */
#if defined(VK_EXT_sample_locations)
	vkGetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(load(context, "vkGetPhysicalDeviceMultisamplePropertiesEXT"));
#endif /* defined(VK_EXT_sample_locations) */
#if defined(VK_EXT_tooling_info)
	vkGetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceToolPropertiesEXT>(load(context, "vkGetPhysicalDeviceToolPropertiesEXT"));
#endif /* defined(VK_EXT_tooling_info) */
#if defined(VK_FUCHSIA_imagepipe_surface)
	vkCreateImagePipeSurfaceFUCHSIA = reinterpret_cast<PFN_vkCreateImagePipeSurfaceFUCHSIA>(load(context, "vkCreateImagePipeSurfaceFUCHSIA"));
#endif /* defined(VK_FUCHSIA_imagepipe_surface) */
#if defined(VK_GGP_stream_descriptor_surface)
	vkCreateStreamDescriptorSurfaceGGP = reinterpret_cast<PFN_vkCreateStreamDescriptorSurfaceGGP>(load(context, "vkCreateStreamDescriptorSurfaceGGP"));
#endif /* defined(VK_GGP_stream_descriptor_surface) */
#if defined(VK_KHR_android_surface)
	vkCreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(load(context, "vkCreateAndroidSurfaceKHR"));
#endif /* defined(VK_KHR_android_surface) */
#if defined(VK_KHR_device_group_creation)
	vkEnumeratePhysicalDeviceGroupsKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroupsKHR>(load(context, "vkEnumeratePhysicalDeviceGroupsKHR"));
#endif /* defined(VK_KHR_device_group_creation) */
#if defined(VK_KHR_display)
	vkCreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(load(context, "vkCreateDisplayModeKHR"));
	vkCreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(load(context, "vkCreateDisplayPlaneSurfaceKHR"));
	vkGetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(load(context, "vkGetDisplayModePropertiesKHR"));
	vkGetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(load(context, "vkGetDisplayPlaneCapabilitiesKHR"));
	vkGetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(load(context, "vkGetDisplayPlaneSupportedDisplaysKHR"));
	vkGetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(load(context, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
	vkGetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(load(context, "vkGetPhysicalDeviceDisplayPropertiesKHR"));
#endif /* defined(VK_KHR_display) */
#if defined(VK_KHR_external_fence_capabilities)
	vkGetPhysicalDeviceExternalFencePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR>(load(context, "vkGetPhysicalDeviceExternalFencePropertiesKHR"));
#endif /* defined(VK_KHR_external_fence_capabilities) */
#if defined(VK_KHR_external_memory_capabilities)
	vkGetPhysicalDeviceExternalBufferPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR>(load(context, "vkGetPhysicalDeviceExternalBufferPropertiesKHR"));
#endif /* defined(VK_KHR_external_memory_capabilities) */
#if defined(VK_KHR_external_semaphore_capabilities)
	vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR>(load(context, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR"));
#endif /* defined(VK_KHR_external_semaphore_capabilities) */
#if defined(VK_KHR_get_display_properties2)
	vkGetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(load(context, "vkGetDisplayModeProperties2KHR"));
	vkGetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(load(context, "vkGetDisplayPlaneCapabilities2KHR"));
	vkGetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(load(context, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
	vkGetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(load(context, "vkGetPhysicalDeviceDisplayProperties2KHR"));
#endif /* defined(VK_KHR_get_display_properties2) */
#if defined(VK_KHR_get_physical_device_properties2)
	vkGetPhysicalDeviceFeatures2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2KHR>(load(context, "vkGetPhysicalDeviceFeatures2KHR"));
	vkGetPhysicalDeviceFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2KHR>(load(context, "vkGetPhysicalDeviceFormatProperties2KHR"));
	vkGetPhysicalDeviceImageFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2KHR>(load(context, "vkGetPhysicalDeviceImageFormatProperties2KHR"));
	vkGetPhysicalDeviceMemoryProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(load(context, "vkGetPhysicalDeviceMemoryProperties2KHR"));
	vkGetPhysicalDeviceProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2KHR>(load(context, "vkGetPhysicalDeviceProperties2KHR"));
	vkGetPhysicalDeviceQueueFamilyProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR>(load(context, "vkGetPhysicalDeviceQueueFamilyProperties2KHR"));
	vkGetPhysicalDeviceSparseImageFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR>(load(context, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR"));
#endif /* defined(VK_KHR_get_physical_device_properties2) */
#if defined(VK_KHR_get_surface_capabilities2)
	vkGetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(load(context, "vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
	vkGetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(load(context, "vkGetPhysicalDeviceSurfaceFormats2KHR"));
#endif /* defined(VK_KHR_get_surface_capabilities2) */
#if defined(VK_KHR_performance_query)
	vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR>(load(context, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"));
	vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR>(load(context, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"));
#endif /* defined(VK_KHR_performance_query) */
#if defined(VK_KHR_surface)
	vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(load(context, "vkDestroySurfaceKHR"));
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(load(context, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
	vkGetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(load(context, "vkGetPhysicalDeviceSurfaceFormatsKHR"));
	vkGetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(load(context, "vkGetPhysicalDeviceSurfacePresentModesKHR"));
	vkGetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(load(context, "vkGetPhysicalDeviceSurfaceSupportKHR"));
#endif /* defined(VK_KHR_surface) */
#if defined(VK_KHR_wayland_surface)
	vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(load(context, "vkCreateWaylandSurfaceKHR"));
	vkGetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(load(context, "vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif /* defined(VK_KHR_wayland_surface) */
#if defined(VK_KHR_win32_surface)
	vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(load(context, "vkCreateWin32SurfaceKHR"));
	vkGetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(load(context, "vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif /* defined(VK_KHR_win32_surface) */
#if defined(VK_KHR_xcb_surface)
	vkCreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(load(context, "vkCreateXcbSurfaceKHR"));
	vkGetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(load(context, "vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif /* defined(VK_KHR_xcb_surface) */
#if defined(VK_KHR_xlib_surface)
	vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(load(context, "vkCreateXlibSurfaceKHR"));
	vkGetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(load(context, "vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif /* defined(VK_KHR_xlib_surface) */
#if defined(VK_MVK_ios_surface)
	vkCreateIOSSurfaceMVK = reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(load(context, "vkCreateIOSSurfaceMVK"));
#endif /* defined(VK_MVK_ios_surface) */
#if defined(VK_MVK_macos_surface)
	vkCreateMacOSSurfaceMVK = reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(load(context, "vkCreateMacOSSurfaceMVK"));
#endif /* defined(VK_MVK_macos_surface) */
#if defined(VK_NN_vi_surface)
	vkCreateViSurfaceNN = reinterpret_cast<PFN_vkCreateViSurfaceNN>(load(context, "vkCreateViSurfaceNN"));
#endif /* defined(VK_NN_vi_surface) */
#if defined(VK_NV_cooperative_matrix)
	vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV>(load(context, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
#endif /* defined(VK_NV_cooperative_matrix) */
#if defined(VK_NV_coverage_reduction_mode)
	vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(load(context, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#endif /* defined(VK_NV_coverage_reduction_mode) */
#if defined(VK_NV_external_memory_capabilities)
	vkGetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(load(context, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#endif /* defined(VK_NV_external_memory_capabilities) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkGetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(load(context, "vkGetPhysicalDevicePresentRectanglesKHR"));
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
	/* VK_LOADER_GENERATE_LOAD_INSTANCE */
}

static void VkGenLoadDevice(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	/* VK_LOADER_GENERATE_LOAD_DEVICE */
#if defined(VK_VERSION_1_0)
	vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(load(context, "vkAllocateCommandBuffers"));
	vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(load(context, "vkAllocateDescriptorSets"));
	vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(load(context, "vkAllocateMemory"));
	vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(load(context, "vkBeginCommandBuffer"));
	vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(load(context, "vkBindBufferMemory"));
	vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(load(context, "vkBindImageMemory"));
	vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(load(context, "vkCmdBeginQuery"));
	vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(load(context, "vkCmdBeginRenderPass"));
	vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(load(context, "vkCmdBindDescriptorSets"));
	vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(load(context, "vkCmdBindIndexBuffer"));
	vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(load(context, "vkCmdBindPipeline"));
	vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(load(context, "vkCmdBindVertexBuffers"));
	vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(load(context, "vkCmdBlitImage"));
	vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(load(context, "vkCmdClearAttachments"));
	vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(load(context, "vkCmdClearColorImage"));
	vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(load(context, "vkCmdClearDepthStencilImage"));
	vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(load(context, "vkCmdCopyBuffer"));
	vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(load(context, "vkCmdCopyBufferToImage"));
	vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(load(context, "vkCmdCopyImage"));
	vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(load(context, "vkCmdCopyImageToBuffer"));
	vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(load(context, "vkCmdCopyQueryPoolResults"));
	vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(load(context, "vkCmdDispatch"));
	vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(load(context, "vkCmdDispatchIndirect"));
	vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(load(context, "vkCmdDraw"));
	vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(load(context, "vkCmdDrawIndexed"));
	vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(load(context, "vkCmdDrawIndexedIndirect"));
	vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(load(context, "vkCmdDrawIndirect"));
	vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(load(context, "vkCmdEndQuery"));
	vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(load(context, "vkCmdEndRenderPass"));
	vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(load(context, "vkCmdExecuteCommands"));
	vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(load(context, "vkCmdFillBuffer"));
	vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(load(context, "vkCmdNextSubpass"));
	vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(load(context, "vkCmdPipelineBarrier"));
	vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(load(context, "vkCmdPushConstants"));
	vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(load(context, "vkCmdResetEvent"));
	vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(load(context, "vkCmdResetQueryPool"));
	vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(load(context, "vkCmdResolveImage"));
	vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(load(context, "vkCmdSetBlendConstants"));
	vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(load(context, "vkCmdSetDepthBias"));
	vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(load(context, "vkCmdSetDepthBounds"));
	vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(load(context, "vkCmdSetEvent"));
	vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(load(context, "vkCmdSetLineWidth"));
	vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(load(context, "vkCmdSetScissor"));
	vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(load(context, "vkCmdSetStencilCompareMask"));
	vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(load(context, "vkCmdSetStencilReference"));
	vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(load(context, "vkCmdSetStencilWriteMask"));
	vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(load(context, "vkCmdSetViewport"));
	vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(load(context, "vkCmdUpdateBuffer"));
	vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(load(context, "vkCmdWaitEvents"));
	vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(load(context, "vkCmdWriteTimestamp"));
	vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(load(context, "vkCreateBuffer"));
	vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(load(context, "vkCreateBufferView"));
	vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(load(context, "vkCreateCommandPool"));
	vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(load(context, "vkCreateComputePipelines"));
	vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(load(context, "vkCreateDescriptorPool"));
	vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(load(context, "vkCreateDescriptorSetLayout"));
	vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(load(context, "vkCreateEvent"));
	vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(load(context, "vkCreateFence"));
	vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(load(context, "vkCreateFramebuffer"));
	vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(load(context, "vkCreateGraphicsPipelines"));
	vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(load(context, "vkCreateImage"));
	vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(load(context, "vkCreateImageView"));
	vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(load(context, "vkCreatePipelineCache"));
	vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(load(context, "vkCreatePipelineLayout"));
	vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(load(context, "vkCreateQueryPool"));
	vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(load(context, "vkCreateRenderPass"));
	vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(load(context, "vkCreateSampler"));
	vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(load(context, "vkCreateSemaphore"));
	vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(load(context, "vkCreateShaderModule"));
	vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(load(context, "vkDestroyBuffer"));
	vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(load(context, "vkDestroyBufferView"));
	vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(load(context, "vkDestroyCommandPool"));
	vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(load(context, "vkDestroyDescriptorPool"));
	vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(load(context, "vkDestroyDescriptorSetLayout"));
	vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(load(context, "vkDestroyDevice"));
	vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(load(context, "vkDestroyEvent"));
	vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(load(context, "vkDestroyFence"));
	vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(load(context, "vkDestroyFramebuffer"));
	vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(load(context, "vkDestroyImage"));
	vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(load(context, "vkDestroyImageView"));
	vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(load(context, "vkDestroyPipeline"));
	vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(load(context, "vkDestroyPipelineCache"));
	vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(load(context, "vkDestroyPipelineLayout"));
	vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(load(context, "vkDestroyQueryPool"));
	vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(load(context, "vkDestroyRenderPass"));
	vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(load(context, "vkDestroySampler"));
	vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(load(context, "vkDestroySemaphore"));
	vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(load(context, "vkDestroyShaderModule"));
	vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(load(context, "vkDeviceWaitIdle"));
	vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(load(context, "vkEndCommandBuffer"));
	vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(load(context, "vkFlushMappedMemoryRanges"));
	vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(load(context, "vkFreeCommandBuffers"));
	vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(load(context, "vkFreeDescriptorSets"));
	vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(load(context, "vkFreeMemory"));
	vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(load(context, "vkGetBufferMemoryRequirements"));
	vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(load(context, "vkGetDeviceMemoryCommitment"));
	vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(load(context, "vkGetDeviceQueue"));
	vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(load(context, "vkGetEventStatus"));
	vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(load(context, "vkGetFenceStatus"));
	vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(load(context, "vkGetImageMemoryRequirements"));
	vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(load(context, "vkGetImageSparseMemoryRequirements"));
	vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(load(context, "vkGetImageSubresourceLayout"));
	vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(load(context, "vkGetPipelineCacheData"));
	vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(load(context, "vkGetQueryPoolResults"));
	vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(load(context, "vkGetRenderAreaGranularity"));
	vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(load(context, "vkInvalidateMappedMemoryRanges"));
	vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(load(context, "vkMapMemory"));
	vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(load(context, "vkMergePipelineCaches"));
	vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(load(context, "vkQueueBindSparse"));
	vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(load(context, "vkQueueSubmit"));
	vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(load(context, "vkQueueWaitIdle"));
	vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(load(context, "vkResetCommandBuffer"));
	vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(load(context, "vkResetCommandPool"));
	vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(load(context, "vkResetDescriptorPool"));
	vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(load(context, "vkResetEvent"));
	vkResetFences = reinterpret_cast<PFN_vkResetFences>(load(context, "vkResetFences"));
	vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(load(context, "vkSetEvent"));
	vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(load(context, "vkUnmapMemory"));
	vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(load(context, "vkUpdateDescriptorSets"));
	vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(load(context, "vkWaitForFences"));
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
	vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(load(context, "vkBindBufferMemory2"));
	vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(load(context, "vkBindImageMemory2"));
	vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(load(context, "vkCmdDispatchBase"));
	vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(load(context, "vkCmdSetDeviceMask"));
	vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(load(context, "vkCreateDescriptorUpdateTemplate"));
	vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(load(context, "vkCreateSamplerYcbcrConversion"));
	vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(load(context, "vkDestroyDescriptorUpdateTemplate"));
	vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(load(context, "vkDestroySamplerYcbcrConversion"));
	vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(load(context, "vkGetBufferMemoryRequirements2"));
	vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(load(context, "vkGetDescriptorSetLayoutSupport"));
	vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(load(context, "vkGetDeviceGroupPeerMemoryFeatures"));
	vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(load(context, "vkGetDeviceQueue2"));
	vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(load(context, "vkGetImageMemoryRequirements2"));
	vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(load(context, "vkGetImageSparseMemoryRequirements2"));
	vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(load(context, "vkTrimCommandPool"));
	vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(load(context, "vkUpdateDescriptorSetWithTemplate"));
#endif /* defined(VK_VERSION_1_1) */
#if defined(VK_VERSION_1_2)
	vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(load(context, "vkCmdBeginRenderPass2"));
	vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(load(context, "vkCmdDrawIndexedIndirectCount"));
	vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(load(context, "vkCmdDrawIndirectCount"));
	vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(load(context, "vkCmdEndRenderPass2"));
	vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(load(context, "vkCmdNextSubpass2"));
	vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(load(context, "vkCreateRenderPass2"));
	vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(load(context, "vkGetBufferDeviceAddress"));
	vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(load(context, "vkGetBufferOpaqueCaptureAddress"));
	vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(load(context, "vkGetDeviceMemoryOpaqueCaptureAddress"));
	vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(load(context, "vkGetSemaphoreCounterValue"));
	vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(load(context, "vkResetQueryPool"));
	vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(load(context, "vkSignalSemaphore"));
	vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(load(context, "vkWaitSemaphores"));
#endif /* defined(VK_VERSION_1_2) */
#if defined(VK_AMD_buffer_marker)
	vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(load(context, "vkCmdWriteBufferMarkerAMD"));
#endif /* defined(VK_AMD_buffer_marker) */
#if defined(VK_AMD_display_native_hdr)
	vkSetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(load(context, "vkSetLocalDimmingAMD"));
#endif /* defined(VK_AMD_display_native_hdr) */
#if defined(VK_AMD_draw_indirect_count)
	vkCmdDrawIndexedIndirectCountAMD = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountAMD>(load(context, "vkCmdDrawIndexedIndirectCountAMD"));
	vkCmdDrawIndirectCountAMD = reinterpret_cast<PFN_vkCmdDrawIndirectCountAMD>(load(context, "vkCmdDrawIndirectCountAMD"));
#endif /* defined(VK_AMD_draw_indirect_count) */
#if defined(VK_AMD_shader_info)
	vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(load(context, "vkGetShaderInfoAMD"));
#endif /* defined(VK_AMD_shader_info) */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
	vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(load(context, "vkGetAndroidHardwareBufferPropertiesANDROID"));
	vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(load(context, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif /* defined(VK_ANDROID_external_memory_android_hardware_buffer) */
#if defined(VK_EXT_buffer_device_address)
	vkGetBufferDeviceAddressEXT = reinterpret_cast<PFN_vkGetBufferDeviceAddressEXT>(load(context, "vkGetBufferDeviceAddressEXT"));
#endif /* defined(VK_EXT_buffer_device_address) */
#if defined(VK_EXT_calibrated_timestamps)
	vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(load(context, "vkGetCalibratedTimestampsEXT"));
#endif /* defined(VK_EXT_calibrated_timestamps) */
#if defined(VK_EXT_conditional_rendering)
	vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(load(context, "vkCmdBeginConditionalRenderingEXT"));
	vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(load(context, "vkCmdEndConditionalRenderingEXT"));
#endif /* defined(VK_EXT_conditional_rendering) */
#if defined(VK_EXT_debug_marker)
	vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(load(context, "vkCmdDebugMarkerBeginEXT"));
	vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(load(context, "vkCmdDebugMarkerEndEXT"));
	vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(load(context, "vkCmdDebugMarkerInsertEXT"));
	vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(load(context, "vkDebugMarkerSetObjectNameEXT"));
	vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(load(context, "vkDebugMarkerSetObjectTagEXT"));
#endif /* defined(VK_EXT_debug_marker) */
#if defined(VK_EXT_discard_rectangles)
	vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(load(context, "vkCmdSetDiscardRectangleEXT"));
#endif /* defined(VK_EXT_discard_rectangles) */
#if defined(VK_EXT_display_control)
	vkDisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(load(context, "vkDisplayPowerControlEXT"));
	vkGetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(load(context, "vkGetSwapchainCounterEXT"));
	vkRegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(load(context, "vkRegisterDeviceEventEXT"));
	vkRegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(load(context, "vkRegisterDisplayEventEXT"));
#endif /* defined(VK_EXT_display_control) */
#if defined(VK_EXT_extended_dynamic_state)
	vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(load(context, "vkCmdBindVertexBuffers2EXT"));
	vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(load(context, "vkCmdSetCullModeEXT"));
	vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(load(context, "vkCmdSetDepthBoundsTestEnableEXT"));
	vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(load(context, "vkCmdSetDepthCompareOpEXT"));
	vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(load(context, "vkCmdSetDepthTestEnableEXT"));
	vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(load(context, "vkCmdSetDepthWriteEnableEXT"));
	vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(load(context, "vkCmdSetFrontFaceEXT"));
	vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(load(context, "vkCmdSetPrimitiveTopologyEXT"));
	vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(load(context, "vkCmdSetScissorWithCountEXT"));
	vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(load(context, "vkCmdSetStencilOpEXT"));
	vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(load(context, "vkCmdSetStencilTestEnableEXT"));
	vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(load(context, "vkCmdSetViewportWithCountEXT"));
#endif /* defined(VK_EXT_extended_dynamic_state) */
#if defined(VK_EXT_external_memory_host)
	vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(load(context, "vkGetMemoryHostPointerPropertiesEXT"));
#endif /* defined(VK_EXT_external_memory_host) */
#if defined(VK_EXT_full_screen_exclusive)
	vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(load(context, "vkAcquireFullScreenExclusiveModeEXT"));
	vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(load(context, "vkReleaseFullScreenExclusiveModeEXT"));
#endif /* defined(VK_EXT_full_screen_exclusive) */
#if defined(VK_EXT_hdr_metadata)
	vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(load(context, "vkSetHdrMetadataEXT"));
#endif /* defined(VK_EXT_hdr_metadata) */
#if defined(VK_EXT_host_query_reset)
	vkResetQueryPoolEXT = reinterpret_cast<PFN_vkResetQueryPoolEXT>(load(context, "vkResetQueryPoolEXT"));
#endif /* defined(VK_EXT_host_query_reset) */
#if defined(VK_EXT_image_drm_format_modifier)
	vkGetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(load(context, "vkGetImageDrmFormatModifierPropertiesEXT"));
#endif /* defined(VK_EXT_image_drm_format_modifier) */
#if defined(VK_EXT_line_rasterization)
	vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(load(context, "vkCmdSetLineStippleEXT"));
#endif /* defined(VK_EXT_line_rasterization) */
#if defined(VK_EXT_private_data)
	vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(load(context, "vkCreatePrivateDataSlotEXT"));
	vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(load(context, "vkDestroyPrivateDataSlotEXT"));
	vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(load(context, "vkGetPrivateDataEXT"));
	vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(load(context, "vkSetPrivateDataEXT"));
#endif /* defined(VK_EXT_private_data) */
#if defined(VK_EXT_sample_locations)
	vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(load(context, "vkCmdSetSampleLocationsEXT"));
#endif /* defined(VK_EXT_sample_locations) */
#if defined(VK_EXT_transform_feedback)
	vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(load(context, "vkCmdBeginQueryIndexedEXT"));
	vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(load(context, "vkCmdBeginTransformFeedbackEXT"));
	vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(load(context, "vkCmdBindTransformFeedbackBuffersEXT"));
	vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(load(context, "vkCmdDrawIndirectByteCountEXT"));
	vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(load(context, "vkCmdEndQueryIndexedEXT"));
	vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(load(context, "vkCmdEndTransformFeedbackEXT"));
#endif /* defined(VK_EXT_transform_feedback) */
#if defined(VK_EXT_validation_cache)
	vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(load(context, "vkCreateValidationCacheEXT"));
	vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(load(context, "vkDestroyValidationCacheEXT"));
	vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(load(context, "vkGetValidationCacheDataEXT"));
	vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(load(context, "vkMergeValidationCachesEXT"));
#endif /* defined(VK_EXT_validation_cache) */
#if defined(VK_GOOGLE_display_timing)
	vkGetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(load(context, "vkGetPastPresentationTimingGOOGLE"));
	vkGetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(load(context, "vkGetRefreshCycleDurationGOOGLE"));
#endif /* defined(VK_GOOGLE_display_timing) */
#if defined(VK_INTEL_performance_query)
	vkAcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(load(context, "vkAcquirePerformanceConfigurationINTEL"));
	vkCmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(load(context, "vkCmdSetPerformanceMarkerINTEL"));
	vkCmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(load(context, "vkCmdSetPerformanceOverrideINTEL"));
	vkCmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(load(context, "vkCmdSetPerformanceStreamMarkerINTEL"));
	vkGetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(load(context, "vkGetPerformanceParameterINTEL"));
	vkInitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(load(context, "vkInitializePerformanceApiINTEL"));
	vkQueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(load(context, "vkQueueSetPerformanceConfigurationINTEL"));
	vkReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(load(context, "vkReleasePerformanceConfigurationINTEL"));
	vkUninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(load(context, "vkUninitializePerformanceApiINTEL"));
#endif /* defined(VK_INTEL_performance_query) */
#if defined(VK_KHR_bind_memory2)
	vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(load(context, "vkBindBufferMemory2KHR"));
	vkBindImageMemory2KHR = reinterpret_cast<PFN_vkBindImageMemory2KHR>(load(context, "vkBindImageMemory2KHR"));
#endif /* defined(VK_KHR_bind_memory2) */
#if defined(VK_KHR_buffer_device_address)
	vkGetBufferDeviceAddressKHR = reinterpret_cast<PFN_vkGetBufferDeviceAddressKHR>(load(context, "vkGetBufferDeviceAddressKHR"));
	vkGetBufferOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddressKHR>(load(context, "vkGetBufferOpaqueCaptureAddressKHR"));
	vkGetDeviceMemoryOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR>(load(context, "vkGetDeviceMemoryOpaqueCaptureAddressKHR"));
#endif /* defined(VK_KHR_buffer_device_address) */
#if defined(VK_KHR_create_renderpass2)
	vkCmdBeginRenderPass2KHR = reinterpret_cast<PFN_vkCmdBeginRenderPass2KHR>(load(context, "vkCmdBeginRenderPass2KHR"));
	vkCmdEndRenderPass2KHR = reinterpret_cast<PFN_vkCmdEndRenderPass2KHR>(load(context, "vkCmdEndRenderPass2KHR"));
	vkCmdNextSubpass2KHR = reinterpret_cast<PFN_vkCmdNextSubpass2KHR>(load(context, "vkCmdNextSubpass2KHR"));
	vkCreateRenderPass2KHR = reinterpret_cast<PFN_vkCreateRenderPass2KHR>(load(context, "vkCreateRenderPass2KHR"));
#endif /* defined(VK_KHR_create_renderpass2) */
#if defined(VK_KHR_deferred_host_operations)
	vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(load(context, "vkCreateDeferredOperationKHR"));
	vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(load(context, "vkDeferredOperationJoinKHR"));
	vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(load(context, "vkDestroyDeferredOperationKHR"));
	vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(load(context, "vkGetDeferredOperationMaxConcurrencyKHR"));
	vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(load(context, "vkGetDeferredOperationResultKHR"));
#endif /* defined(VK_KHR_deferred_host_operations) */
#if defined(VK_KHR_descriptor_update_template)
	vkCreateDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplateKHR>(load(context, "vkCreateDescriptorUpdateTemplateKHR"));
	vkDestroyDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplateKHR>(load(context, "vkDestroyDescriptorUpdateTemplateKHR"));
	vkUpdateDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplateKHR>(load(context, "vkUpdateDescriptorSetWithTemplateKHR"));
#endif /* defined(VK_KHR_descriptor_update_template) */
#if defined(VK_KHR_device_group)
	vkCmdDispatchBaseKHR = reinterpret_cast<PFN_vkCmdDispatchBaseKHR>(load(context, "vkCmdDispatchBaseKHR"));
	vkCmdSetDeviceMaskKHR = reinterpret_cast<PFN_vkCmdSetDeviceMaskKHR>(load(context, "vkCmdSetDeviceMaskKHR"));
	vkGetDeviceGroupPeerMemoryFeaturesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR>(load(context, "vkGetDeviceGroupPeerMemoryFeaturesKHR"));
#endif /* defined(VK_KHR_device_group) */
#if defined(VK_KHR_display_swapchain)
	vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(load(context, "vkCreateSharedSwapchainsKHR"));
#endif /* defined(VK_KHR_display_swapchain) */
#if defined(VK_KHR_draw_indirect_count)
	vkCmdDrawIndexedIndirectCountKHR = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountKHR>(load(context, "vkCmdDrawIndexedIndirectCountKHR"));
	vkCmdDrawIndirectCountKHR = reinterpret_cast<PFN_vkCmdDrawIndirectCountKHR>(load(context, "vkCmdDrawIndirectCountKHR"));
#endif /* defined(VK_KHR_draw_indirect_count) */
#if defined(VK_KHR_external_fence_fd)
	vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(load(context, "vkGetFenceFdKHR"));
	vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(load(context, "vkImportFenceFdKHR"));
#endif /* defined(VK_KHR_external_fence_fd) */
#if defined(VK_KHR_external_fence_win32)
	vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(load(context, "vkGetFenceWin32HandleKHR"));
	vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(load(context, "vkImportFenceWin32HandleKHR"));
#endif /* defined(VK_KHR_external_fence_win32) */
#if defined(VK_KHR_external_memory_fd)
	vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(load(context, "vkGetMemoryFdKHR"));
	vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(load(context, "vkGetMemoryFdPropertiesKHR"));
#endif /* defined(VK_KHR_external_memory_fd) */
#if defined(VK_KHR_external_memory_win32)
	vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(load(context, "vkGetMemoryWin32HandleKHR"));
	vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(load(context, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif /* defined(VK_KHR_external_memory_win32) */
#if defined(VK_KHR_external_semaphore_fd)
	vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(load(context, "vkGetSemaphoreFdKHR"));
	vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(load(context, "vkImportSemaphoreFdKHR"));
#endif /* defined(VK_KHR_external_semaphore_fd) */
#if defined(VK_KHR_external_semaphore_win32)
	vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(load(context, "vkGetSemaphoreWin32HandleKHR"));
	vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(load(context, "vkImportSemaphoreWin32HandleKHR"));
#endif /* defined(VK_KHR_external_semaphore_win32) */
#if defined(VK_KHR_get_memory_requirements2)
	vkGetBufferMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(load(context, "vkGetBufferMemoryRequirements2KHR"));
	vkGetImageMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageMemoryRequirements2KHR>(load(context, "vkGetImageMemoryRequirements2KHR"));
	vkGetImageSparseMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2KHR>(load(context, "vkGetImageSparseMemoryRequirements2KHR"));
#endif /* defined(VK_KHR_get_memory_requirements2) */
#if defined(VK_KHR_maintenance1)
	vkTrimCommandPoolKHR = reinterpret_cast<PFN_vkTrimCommandPoolKHR>(load(context, "vkTrimCommandPoolKHR"));
#endif /* defined(VK_KHR_maintenance1) */
#if defined(VK_KHR_maintenance3)
	vkGetDescriptorSetLayoutSupportKHR = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupportKHR>(load(context, "vkGetDescriptorSetLayoutSupportKHR"));
#endif /* defined(VK_KHR_maintenance3) */
#if defined(VK_KHR_performance_query)
	vkAcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(load(context, "vkAcquireProfilingLockKHR"));
	vkReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(load(context, "vkReleaseProfilingLockKHR"));
#endif /* defined(VK_KHR_performance_query) */
#if defined(VK_KHR_pipeline_executable_properties)
	vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(load(context, "vkGetPipelineExecutableInternalRepresentationsKHR"));
	vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(load(context, "vkGetPipelineExecutablePropertiesKHR"));
	vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(load(context, "vkGetPipelineExecutableStatisticsKHR"));
#endif /* defined(VK_KHR_pipeline_executable_properties) */
#if defined(VK_KHR_push_descriptor)
	vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(load(context, "vkCmdPushDescriptorSetKHR"));
#endif /* defined(VK_KHR_push_descriptor) */
#if defined(VK_KHR_ray_tracing)
	vkBindAccelerationStructureMemoryKHR = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryKHR>(load(context, "vkBindAccelerationStructureMemoryKHR"));
	vkBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkBuildAccelerationStructureKHR>(load(context, "vkBuildAccelerationStructureKHR"));
	vkCmdBuildAccelerationStructureIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureIndirectKHR>(load(context, "vkCmdBuildAccelerationStructureIndirectKHR"));
	vkCmdBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureKHR>(load(context, "vkCmdBuildAccelerationStructureKHR"));
	vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(load(context, "vkCmdCopyAccelerationStructureKHR"));
	vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(load(context, "vkCmdCopyAccelerationStructureToMemoryKHR"));
	vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(load(context, "vkCmdCopyMemoryToAccelerationStructureKHR"));
	vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(load(context, "vkCmdTraceRaysIndirectKHR"));
	vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(load(context, "vkCmdTraceRaysKHR"));
	vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(load(context, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
	vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(load(context, "vkCopyAccelerationStructureKHR"));
	vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(load(context, "vkCopyAccelerationStructureToMemoryKHR"));
	vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(load(context, "vkCopyMemoryToAccelerationStructureKHR"));
	vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(load(context, "vkCreateAccelerationStructureKHR"));
	vkCreateRayTracingPipelinesKHR = reinterpret_cast>PFN_vkCreateRayTracingPipelinesKHR > (load(context, "vkCreateRayTracingPipelinesKHR"));
	vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(load(context, "vkDestroyAccelerationStructureKHR"));
	vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(load(context, "vkGetAccelerationStructureDeviceAddressKHR"));
	vkGetAccelerationStructureMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsKHR>(load(context, "vkGetAccelerationStructureMemoryRequirementsKHR"));
	vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(load(context, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
	vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(load(context, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
	vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(load(context, "vkGetRayTracingShaderGroupHandlesKHR"));
	vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(load(context, "vkWriteAccelerationStructuresPropertiesKHR"));
#endif /* defined(VK_KHR_ray_tracing) */
#if defined(VK_KHR_sampler_ycbcr_conversion)
	vkCreateSamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversionKHR>(load(context, "vkCreateSamplerYcbcrConversionKHR"));
	vkDestroySamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversionKHR>(load(context, "vkDestroySamplerYcbcrConversionKHR"));
#endif /* defined(VK_KHR_sampler_ycbcr_conversion) */
#if defined(VK_KHR_shared_presentable_image)
	vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(load(context, "vkGetSwapchainStatusKHR"));
#endif /* defined(VK_KHR_shared_presentable_image) */
#if defined(VK_KHR_swapchain)
	vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(load(context, "vkAcquireNextImageKHR"));
	vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(load(context, "vkCreateSwapchainKHR"));
	vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(load(context, "vkDestroySwapchainKHR"));
	vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(load(context, "vkGetSwapchainImagesKHR"));
	vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(load(context, "vkQueuePresentKHR"));
#endif /* defined(VK_KHR_swapchain) */
#if defined(VK_KHR_timeline_semaphore)
	vkGetSemaphoreCounterValueKHR = reinterpret_cast<PFN_vkGetSemaphoreCounterValueKHR>(load(context, "vkGetSemaphoreCounterValueKHR"));
	vkSignalSemaphoreKHR = reinterpret_cast<PFN_vkSignalSemaphoreKHR>(load(context, "vkSignalSemaphoreKHR"));
	vkWaitSemaphoresKHR = reinterpret_cast<PFN_vkWaitSemaphoresKHR>(load(context, "vkWaitSemaphoresKHR"));
#endif /* defined(VK_KHR_timeline_semaphore) */
#if defined(VK_NVX_image_view_handle)
	vkGetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(load(context, "vkGetImageViewAddressNVX"));
	vkGetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(load(context, "vkGetImageViewHandleNVX"));
#endif /* defined(VK_NVX_image_view_handle) */
#if defined(VK_NV_clip_space_w_scaling)
	vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(load(context, "vkCmdSetViewportWScalingNV"));
#endif /* defined(VK_NV_clip_space_w_scaling) */
#if defined(VK_NV_device_diagnostic_checkpoints)
	vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(load(context, "vkCmdSetCheckpointNV"));
	vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(load(context, "vkGetQueueCheckpointDataNV"));
#endif /* defined(VK_NV_device_diagnostic_checkpoints) */
#if defined(VK_NV_device_generated_commands)
	vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(load(context, "vkCmdBindPipelineShaderGroupNV"));
	vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(load(context, "vkCmdExecuteGeneratedCommandsNV"));
	vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(load(context, "vkCmdPreprocessGeneratedCommandsNV"));
	vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(load(context, "vkCreateIndirectCommandsLayoutNV"));
	vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(load(context, "vkDestroyIndirectCommandsLayoutNV"));
	vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(load(context, "vkGetGeneratedCommandsMemoryRequirementsNV"));
#endif /* defined(VK_NV_device_generated_commands) */
#if defined(VK_NV_external_memory_win32)
	vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(load(context, "vkGetMemoryWin32HandleNV"));
#endif /* defined(VK_NV_external_memory_win32) */
#if defined(VK_NV_mesh_shader)
	vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(load(context, "vkCmdDrawMeshTasksIndirectCountNV"));
	vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(load(context, "vkCmdDrawMeshTasksIndirectNV"));
	vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(load(context, "vkCmdDrawMeshTasksNV"));
#endif /* defined(VK_NV_mesh_shader) */
#if defined(VK_NV_ray_tracing)
	vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(load(context, "vkBindAccelerationStructureMemoryNV"));
	vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(load(context, "vkCmdBuildAccelerationStructureNV"));
	vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(load(context, "vkCmdCopyAccelerationStructureNV"));
	vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(load(context, "vkCmdTraceRaysNV"));
	vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(load(context, "vkCmdWriteAccelerationStructuresPropertiesNV"));
	vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(load(context, "vkCompileDeferredNV"));
	vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(load(context, "vkCreateAccelerationStructureNV"));
	vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(load(context, "vkCreateRayTracingPipelinesNV"));
	vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(load(context, "vkDestroyAccelerationStructureNV"));
	vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(load(context, "vkGetAccelerationStructureHandleNV"));
	vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(load(context, "vkGetAccelerationStructureMemoryRequirementsNV"));
	vkGetRayTracingShaderGroupHandlesNV = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesNV>(load(context, "vkGetRayTracingShaderGroupHandlesNV"));
#endif /* defined(VK_NV_ray_tracing) */
#if defined(VK_NV_scissor_exclusive)
	vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(load(context, "vkCmdSetExclusiveScissorNV"));
#endif /* defined(VK_NV_scissor_exclusive) */
#if defined(VK_NV_shading_rate_image)
	vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(load(context, "vkCmdBindShadingRateImageNV"));
	vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(load(context, "vkCmdSetCoarseSampleOrderNV"));
	vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(load(context, "vkCmdSetViewportShadingRatePaletteNV"));
#endif /* defined(VK_NV_shading_rate_image) */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
	vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(load(context, "vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif /* (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
	vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(load(context, "vkCmdPushDescriptorSetWithTemplateKHR"));
#endif /* (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(load(context, "vkGetDeviceGroupPresentCapabilitiesKHR"));
	vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(load(context, "vkGetDeviceGroupSurfacePresentModesKHR"));
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(load(context, "vkAcquireNextImage2KHR"));
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
	/* VK_LOADER_GENERATE_LOAD_DEVICE */
}

static void VkGenLoadDeviceTable(struct VkDeviceTable* table, void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	/* VK_LOADER_GENERATE_LOAD_DEVICE_TABLE */
#if defined(VK_VERSION_1_0)
	table->vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(load(context, "vkAllocateCommandBuffers"));
	table->vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(load(context, "vkAllocateDescriptorSets"));
	table->vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(load(context, "vkAllocateMemory"));
	table->vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(load(context, "vkBeginCommandBuffer"));
	table->vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(load(context, "vkBindBufferMemory"));
	table->vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(load(context, "vkBindImageMemory"));
	table->vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(load(context, "vkCmdBeginQuery"));
	table->vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(load(context, "vkCmdBeginRenderPass"));
	table->vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(load(context, "vkCmdBindDescriptorSets"));
	table->vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(load(context, "vkCmdBindIndexBuffer"));
	table->vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(load(context, "vkCmdBindPipeline"));
	table->vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(load(context, "vkCmdBindVertexBuffers"));
	table->vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(load(context, "vkCmdBlitImage"));
	table->vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(load(context, "vkCmdClearAttachments"));
	table->vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(load(context, "vkCmdClearColorImage"));
	table->vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(load(context, "vkCmdClearDepthStencilImage"));
	table->vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(load(context, "vkCmdCopyBuffer"));
	table->vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(load(context, "vkCmdCopyBufferToImage"));
	table->vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(load(context, "vkCmdCopyImage"));
	table->vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(load(context, "vkCmdCopyImageToBuffer"));
	table->vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(load(context, "vkCmdCopyQueryPoolResults"));
	table->vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(load(context, "vkCmdDispatch"));
	table->vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(load(context, "vkCmdDispatchIndirect"));
	table->vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(load(context, "vkCmdDraw"));
	table->vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(load(context, "vkCmdDrawIndexed"));
	table->vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(load(context, "vkCmdDrawIndexedIndirect"));
	table->vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(load(context, "vkCmdDrawIndirect"));
	table->vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(load(context, "vkCmdEndQuery"));
	table->vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(load(context, "vkCmdEndRenderPass"));
	table->vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(load(context, "vkCmdExecuteCommands"));
	table->vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(load(context, "vkCmdFillBuffer"));
	table->vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(load(context, "vkCmdNextSubpass"));
	table->vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(load(context, "vkCmdPipelineBarrier"));
	table->vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(load(context, "vkCmdPushConstants"));
	table->vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(load(context, "vkCmdResetEvent"));
	table->vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(load(context, "vkCmdResetQueryPool"));
	table->vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(load(context, "vkCmdResolveImage"));
	table->vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(load(context, "vkCmdSetBlendConstants"));
	table->vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(load(context, "vkCmdSetDepthBias"));
	table->vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(load(context, "vkCmdSetDepthBounds"));
	table->vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(load(context, "vkCmdSetEvent"));
	table->vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(load(context, "vkCmdSetLineWidth"));
	table->vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(load(context, "vkCmdSetScissor"));
	table->vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(load(context, "vkCmdSetStencilCompareMask"));
	table->vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(load(context, "vkCmdSetStencilReference"));
	table->vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(load(context, "vkCmdSetStencilWriteMask"));
	table->vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(load(context, "vkCmdSetViewport"));
	table->vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(load(context, "vkCmdUpdateBuffer"));
	table->vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(load(context, "vkCmdWaitEvents"));
	table->vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(load(context, "vkCmdWriteTimestamp"));
	table->vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(load(context, "vkCreateBuffer"));
	table->vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(load(context, "vkCreateBufferView"));
	table->vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(load(context, "vkCreateCommandPool"));
	table->vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(load(context, "vkCreateComputePipelines"));
	table->vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(load(context, "vkCreateDescriptorPool"));
	table->vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(load(context, "vkCreateDescriptorSetLayout"));
	table->vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(load(context, "vkCreateEvent"));
	table->vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(load(context, "vkCreateFence"));
	table->vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(load(context, "vkCreateFramebuffer"));
	table->vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(load(context, "vkCreateGraphicsPipelines"));
	table->vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(load(context, "vkCreateImage"));
	table->vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(load(context, "vkCreateImageView"));
	table->vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(load(context, "vkCreatePipelineCache"));
	table->vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(load(context, "vkCreatePipelineLayout"));
	table->vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(load(context, "vkCreateQueryPool"));
	table->vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(load(context, "vkCreateRenderPass"));
	table->vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(load(context, "vkCreateSampler"));
	table->vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(load(context, "vkCreateSemaphore"));
	table->vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(load(context, "vkCreateShaderModule"));
	table->vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(load(context, "vkDestroyBuffer"));
	table->vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(load(context, "vkDestroyBufferView"));
	table->vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(load(context, "vkDestroyCommandPool"));
	table->vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(load(context, "vkDestroyDescriptorPool"));
	table->vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(load(context, "vkDestroyDescriptorSetLayout"));
	table->vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(load(context, "vkDestroyDevice"));
	table->vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(load(context, "vkDestroyEvent"));
	table->vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(load(context, "vkDestroyFence"));
	table->vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(load(context, "vkDestroyFramebuffer"));
	table->vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(load(context, "vkDestroyImage"));
	table->vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(load(context, "vkDestroyImageView"));
	table->vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(load(context, "vkDestroyPipeline"));
	table->vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(load(context, "vkDestroyPipelineCache"));
	table->vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(load(context, "vkDestroyPipelineLayout"));
	table->vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(load(context, "vkDestroyQueryPool"));
	table->vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(load(context, "vkDestroyRenderPass"));
	table->vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(load(context, "vkDestroySampler"));
	table->vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(load(context, "vkDestroySemaphore"));
	table->vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(load(context, "vkDestroyShaderModule"));
	table->vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(load(context, "vkDeviceWaitIdle"));
	table->vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(load(context, "vkEndCommandBuffer"));
	table->vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(load(context, "vkFlushMappedMemoryRanges"));
	table->vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(load(context, "vkFreeCommandBuffers"));
	table->vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(load(context, "vkFreeDescriptorSets"));
	table->vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(load(context, "vkFreeMemory"));
	table->vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(load(context, "vkGetBufferMemoryRequirements"));
	table->vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(load(context, "vkGetDeviceMemoryCommitment"));
	table->vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(load(context, "vkGetDeviceQueue"));
	table->vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(load(context, "vkGetEventStatus"));
	table->vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(load(context, "vkGetFenceStatus"));
	table->vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(load(context, "vkGetImageMemoryRequirements"));
	table->vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(load(context, "vkGetImageSparseMemoryRequirements"));
	table->vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(load(context, "vkGetImageSubresourceLayout"));
	table->vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(load(context, "vkGetPipelineCacheData"));
	table->vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(load(context, "vkGetQueryPoolResults"));
	table->vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(load(context, "vkGetRenderAreaGranularity"));
	table->vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(load(context, "vkInvalidateMappedMemoryRanges"));
	table->vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(load(context, "vkMapMemory"));
	table->vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(load(context, "vkMergePipelineCaches"));
	table->vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(load(context, "vkQueueBindSparse"));
	table->vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(load(context, "vkQueueSubmit"));
	table->vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(load(context, "vkQueueWaitIdle"));
	table->vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(load(context, "vkResetCommandBuffer"));
	table->vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(load(context, "vkResetCommandPool"));
	table->vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(load(context, "vkResetDescriptorPool"));
	table->vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(load(context, "vkResetEvent"));
	table->vkResetFences = reinterpret_cast<PFN_vkResetFences>(load(context, "vkResetFences"));
	table->vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(load(context, "vkSetEvent"));
	table->vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(load(context, "vkUnmapMemory"));
	table->vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(load(context, "vkUpdateDescriptorSets"));
	table->vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(load(context, "vkWaitForFences"));
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
	table->vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(load(context, "vkBindBufferMemory2"));
	table->vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(load(context, "vkBindImageMemory2"));
	table->vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(load(context, "vkCmdDispatchBase"));
	table->vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(load(context, "vkCmdSetDeviceMask"));
	table->vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(load(context, "vkCreateDescriptorUpdateTemplate"));
	table->vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(load(context, "vkCreateSamplerYcbcrConversion"));
	table->vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(load(context, "vkDestroyDescriptorUpdateTemplate"));
	table->vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(load(context, "vkDestroySamplerYcbcrConversion"));
	table->vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(load(context, "vkGetBufferMemoryRequirements2"));
	table->vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(load(context, "vkGetDescriptorSetLayoutSupport"));
	table->vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(load(context, "vkGetDeviceGroupPeerMemoryFeatures"));
	table->vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(load(context, "vkGetDeviceQueue2"));
	table->vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(load(context, "vkGetImageMemoryRequirements2"));
	table->vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(load(context, "vkGetImageSparseMemoryRequirements2"));
	table->vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(load(context, "vkTrimCommandPool"));
	table->vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(load(context, "vkUpdateDescriptorSetWithTemplate"));
#endif /* defined(VK_VERSION_1_1) */
#if defined(VK_VERSION_1_2)
	table->vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(load(context, "vkCmdBeginRenderPass2"));
	table->vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(load(context, "vkCmdDrawIndexedIndirectCount"));
	table->vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(load(context, "vkCmdDrawIndirectCount"));
	table->vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(load(context, "vkCmdEndRenderPass2"));
	table->vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(load(context, "vkCmdNextSubpass2"));
	table->vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(load(context, "vkCreateRenderPass2"));
	table->vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(load(context, "vkGetBufferDeviceAddress"));
	table->vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(load(context, "vkGetBufferOpaqueCaptureAddress"));
	table->vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(load(context, "vkGetDeviceMemoryOpaqueCaptureAddress"));
	table->vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(load(context, "vkGetSemaphoreCounterValue"));
	table->vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(load(context, "vkResetQueryPool"));
	table->vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(load(context, "vkSignalSemaphore"));
	table->vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(load(context, "vkWaitSemaphores"));
#endif /* defined(VK_VERSION_1_2) */
#if defined(VK_AMD_buffer_marker)
	table->vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(load(context, "vkCmdWriteBufferMarkerAMD"));
#endif /* defined(VK_AMD_buffer_marker) */
#if defined(VK_AMD_display_native_hdr)
	table->vkSetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(load(context, "vkSetLocalDimmingAMD"));
#endif /* defined(VK_AMD_display_native_hdr) */
#if defined(VK_AMD_draw_indirect_count)
	table->vkCmdDrawIndexedIndirectCountAMD = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountAMD>(load(context, "vkCmdDrawIndexedIndirectCountAMD"));
	table->vkCmdDrawIndirectCountAMD = reinterpret_cast<PFN_vkCmdDrawIndirectCountAMD>(load(context, "vkCmdDrawIndirectCountAMD"));
#endif /* defined(VK_AMD_draw_indirect_count) */
#if defined(VK_AMD_shader_info)
	table->vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(load(context, "vkGetShaderInfoAMD"));
#endif /* defined(VK_AMD_shader_info) */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
	table->vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(load(context, "vkGetAndroidHardwareBufferPropertiesANDROID"));
	table->vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(load(context, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif /* defined(VK_ANDROID_external_memory_android_hardware_buffer) */
#if defined(VK_EXT_buffer_device_address)
	table->vkGetBufferDeviceAddressEXT = reinterpret_cast<PFN_vkGetBufferDeviceAddressEXT>(load(context, "vkGetBufferDeviceAddressEXT"));
#endif /* defined(VK_EXT_buffer_device_address) */
#if defined(VK_EXT_calibrated_timestamps)
	table->vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(load(context, "vkGetCalibratedTimestampsEXT"));
#endif /* defined(VK_EXT_calibrated_timestamps) */
#if defined(VK_EXT_conditional_rendering)
	table->vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(load(context, "vkCmdBeginConditionalRenderingEXT"));
	table->vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(load(context, "vkCmdEndConditionalRenderingEXT"));
#endif /* defined(VK_EXT_conditional_rendering) */
#if defined(VK_EXT_debug_marker)
	table->vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(load(context, "vkCmdDebugMarkerBeginEXT"));
	table->vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(load(context, "vkCmdDebugMarkerEndEXT"));
	table->vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(load(context, "vkCmdDebugMarkerInsertEXT"));
	table->vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(load(context, "vkDebugMarkerSetObjectNameEXT"));
	table->vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(load(context, "vkDebugMarkerSetObjectTagEXT"));
#endif /* defined(VK_EXT_debug_marker) */
#if defined(VK_EXT_discard_rectangles)
	table->vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(load(context, "vkCmdSetDiscardRectangleEXT"));
#endif /* defined(VK_EXT_discard_rectangles) */
#if defined(VK_EXT_display_control)
	table->vkDisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(load(context, "vkDisplayPowerControlEXT"));
	table->vkGetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(load(context, "vkGetSwapchainCounterEXT"));
	table->vkRegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(load(context, "vkRegisterDeviceEventEXT"));
	table->vkRegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(load(context, "vkRegisterDisplayEventEXT"));
#endif /* defined(VK_EXT_display_control) */
#if defined(VK_EXT_extended_dynamic_state)
	table->vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(load(context, "vkCmdBindVertexBuffers2EXT"));
	table->vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(load(context, "vkCmdSetCullModeEXT"));
	table->vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(load(context, "vkCmdSetDepthBoundsTestEnableEXT"));
	table->vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(load(context, "vkCmdSetDepthCompareOpEXT"));
	table->vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(load(context, "vkCmdSetDepthTestEnableEXT"));
	table->vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(load(context, "vkCmdSetDepthWriteEnableEXT"));
	table->vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(load(context, "vkCmdSetFrontFaceEXT"));
	table->vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(load(context, "vkCmdSetPrimitiveTopologyEXT"));
	table->vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(load(context, "vkCmdSetScissorWithCountEXT"));
	table->vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(load(context, "vkCmdSetStencilOpEXT"));
	table->vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(load(context, "vkCmdSetStencilTestEnableEXT"));
	table->vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(load(context, "vkCmdSetViewportWithCountEXT"));
#endif /* defined(VK_EXT_extended_dynamic_state) */
#if defined(VK_EXT_external_memory_host)
	table->vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(load(context, "vkGetMemoryHostPointerPropertiesEXT"));
#endif /* defined(VK_EXT_external_memory_host) */
#if defined(VK_EXT_full_screen_exclusive)
	table->vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(load(context, "vkAcquireFullScreenExclusiveModeEXT"));
	table->vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(load(context, "vkReleaseFullScreenExclusiveModeEXT"));
#endif /* defined(VK_EXT_full_screen_exclusive) */
#if defined(VK_EXT_hdr_metadata)
	table->vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(load(context, "vkSetHdrMetadataEXT"));
#endif /* defined(VK_EXT_hdr_metadata) */
#if defined(VK_EXT_host_query_reset)
	table->vkResetQueryPoolEXT = reinterpret_cast<PFN_vkResetQueryPoolEXT>(load(context, "vkResetQueryPoolEXT"));
#endif /* defined(VK_EXT_host_query_reset) */
#if defined(VK_EXT_image_drm_format_modifier)
	table->vkGetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(load(context, "vkGetImageDrmFormatModifierPropertiesEXT"));
#endif /* defined(VK_EXT_image_drm_format_modifier) */
#if defined(VK_EXT_line_rasterization)
	table->vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(load(context, "vkCmdSetLineStippleEXT"));
#endif /* defined(VK_EXT_line_rasterization) */
#if defined(VK_EXT_private_data)
	table->vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(load(context, "vkCreatePrivateDataSlotEXT"));
	table->vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(load(context, "vkDestroyPrivateDataSlotEXT"));
	table->vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(load(context, "vkGetPrivateDataEXT"));
	table->vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(load(context, "vkSetPrivateDataEXT"));
#endif /* defined(VK_EXT_private_data) */
#if defined(VK_EXT_sample_locations)
	table->vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(load(context, "vkCmdSetSampleLocationsEXT"));
#endif /* defined(VK_EXT_sample_locations) */
#if defined(VK_EXT_transform_feedback)
	table->vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(load(context, "vkCmdBeginQueryIndexedEXT"));
	table->vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(load(context, "vkCmdBeginTransformFeedbackEXT"));
	table->vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(load(context, "vkCmdBindTransformFeedbackBuffersEXT"));
	table->vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(load(context, "vkCmdDrawIndirectByteCountEXT"));
	table->vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(load(context, "vkCmdEndQueryIndexedEXT"));
	table->vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(load(context, "vkCmdEndTransformFeedbackEXT"));
#endif /* defined(VK_EXT_transform_feedback) */
#if defined(VK_EXT_validation_cache)
	table->vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(load(context, "vkCreateValidationCacheEXT"));
	table->vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(load(context, "vkDestroyValidationCacheEXT"));
	table->vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(load(context, "vkGetValidationCacheDataEXT"));
	table->vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(load(context, "vkMergeValidationCachesEXT"));
#endif /* defined(VK_EXT_validation_cache) */
#if defined(VK_GOOGLE_display_timing)
	table->vkGetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(load(context, "vkGetPastPresentationTimingGOOGLE"));
	table->vkGetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(load(context, "vkGetRefreshCycleDurationGOOGLE"));
#endif /* defined(VK_GOOGLE_display_timing) */
#if defined(VK_INTEL_performance_query)
	table->vkAcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(load(context, "vkAcquirePerformanceConfigurationINTEL"));
	table->vkCmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(load(context, "vkCmdSetPerformanceMarkerINTEL"));
	table->vkCmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(load(context, "vkCmdSetPerformanceOverrideINTEL"));
	table->vkCmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(load(context, "vkCmdSetPerformanceStreamMarkerINTEL"));
	table->vkGetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(load(context, "vkGetPerformanceParameterINTEL"));
	table->vkInitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(load(context, "vkInitializePerformanceApiINTEL"));
	table->vkQueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(load(context, "vkQueueSetPerformanceConfigurationINTEL"));
	table->vkReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(load(context, "vkReleasePerformanceConfigurationINTEL"));
	table->vkUninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(load(context, "vkUninitializePerformanceApiINTEL"));
#endif /* defined(VK_INTEL_performance_query) */
#if defined(VK_KHR_bind_memory2)
	table->vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(load(context, "vkBindBufferMemory2KHR"));
	table->vkBindImageMemory2KHR = reinterpret_cast<PFN_vkBindImageMemory2KHR>(load(context, "vkBindImageMemory2KHR"));
#endif /* defined(VK_KHR_bind_memory2) */
#if defined(VK_KHR_buffer_device_address)
	table->vkGetBufferDeviceAddressKHR = reinterpret_cast<PFN_vkGetBufferDeviceAddressKHR>(load(context, "vkGetBufferDeviceAddressKHR"));
	table->vkGetBufferOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddressKHR>(load(context, "vkGetBufferOpaqueCaptureAddressKHR"));
	table->vkGetDeviceMemoryOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR>(load(context, "vkGetDeviceMemoryOpaqueCaptureAddressKHR"));
#endif /* defined(VK_KHR_buffer_device_address) */
#if defined(VK_KHR_create_renderpass2)
	table->vkCmdBeginRenderPass2KHR = reinterpret_cast<PFN_vkCmdBeginRenderPass2KHR>(load(context, "vkCmdBeginRenderPass2KHR"));
	table->vkCmdEndRenderPass2KHR = reinterpret_cast<PFN_vkCmdEndRenderPass2KHR>(load(context, "vkCmdEndRenderPass2KHR"));
	table->vkCmdNextSubpass2KHR = reinterpret_cast<PFN_vkCmdNextSubpass2KHR>(load(context, "vkCmdNextSubpass2KHR"));
	table->vkCreateRenderPass2KHR = reinterpret_cast<PFN_vkCreateRenderPass2KHR>(load(context, "vkCreateRenderPass2KHR"));
#endif /* defined(VK_KHR_create_renderpass2) */
#if defined(VK_KHR_deferred_host_operations)
	table->vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(load(context, "vkCreateDeferredOperationKHR"));
	table->vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(load(context, "vkDeferredOperationJoinKHR"));
	table->vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(load(context, "vkDestroyDeferredOperationKHR"));
	table->vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(load(context, "vkGetDeferredOperationMaxConcurrencyKHR"));
	table->vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(load(context, "vkGetDeferredOperationResultKHR"));
#endif /* defined(VK_KHR_deferred_host_operations) */
#if defined(VK_KHR_descriptor_update_template)
	table->vkCreateDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplateKHR>(load(context, "vkCreateDescriptorUpdateTemplateKHR"));
	table->vkDestroyDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplateKHR>(load(context, "vkDestroyDescriptorUpdateTemplateKHR"));
	table->vkUpdateDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplateKHR>(load(context, "vkUpdateDescriptorSetWithTemplateKHR"));
#endif /* defined(VK_KHR_descriptor_update_template) */
#if defined(VK_KHR_device_group)
	table->vkCmdDispatchBaseKHR = reinterpret_cast<PFN_vkCmdDispatchBaseKHR>(load(context, "vkCmdDispatchBaseKHR"));
	table->vkCmdSetDeviceMaskKHR = reinterpret_cast<PFN_vkCmdSetDeviceMaskKHR>(load(context, "vkCmdSetDeviceMaskKHR"));
	table->vkGetDeviceGroupPeerMemoryFeaturesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR>(load(context, "vkGetDeviceGroupPeerMemoryFeaturesKHR"));
#endif /* defined(VK_KHR_device_group) */
#if defined(VK_KHR_display_swapchain)
	table->vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(load(context, "vkCreateSharedSwapchainsKHR"));
#endif /* defined(VK_KHR_display_swapchain) */
#if defined(VK_KHR_draw_indirect_count)
	table->vkCmdDrawIndexedIndirectCountKHR = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountKHR>(load(context, "vkCmdDrawIndexedIndirectCountKHR"));
	table->vkCmdDrawIndirectCountKHR = reinterpret_cast<PFN_vkCmdDrawIndirectCountKHR>(load(context, "vkCmdDrawIndirectCountKHR"));
#endif /* defined(VK_KHR_draw_indirect_count) */
#if defined(VK_KHR_external_fence_fd)
	table->vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(load(context, "vkGetFenceFdKHR"));
	table->vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(load(context, "vkImportFenceFdKHR"));
#endif /* defined(VK_KHR_external_fence_fd) */
#if defined(VK_KHR_external_fence_win32)
	table->vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(load(context, "vkGetFenceWin32HandleKHR"));
	table->vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(load(context, "vkImportFenceWin32HandleKHR"));
#endif /* defined(VK_KHR_external_fence_win32) */
#if defined(VK_KHR_external_memory_fd)
	table->vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(load(context, "vkGetMemoryFdKHR"));
	table->vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(load(context, "vkGetMemoryFdPropertiesKHR"));
#endif /* defined(VK_KHR_external_memory_fd) */
#if defined(VK_KHR_external_memory_win32)
	table->vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(load(context, "vkGetMemoryWin32HandleKHR"));
	table->vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(load(context, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif /* defined(VK_KHR_external_memory_win32) */
#if defined(VK_KHR_external_semaphore_fd)
	table->vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(load(context, "vkGetSemaphoreFdKHR"));
	table->vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(load(context, "vkImportSemaphoreFdKHR"));
#endif /* defined(VK_KHR_external_semaphore_fd) */
#if defined(VK_KHR_external_semaphore_win32)
	table->vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(load(context, "vkGetSemaphoreWin32HandleKHR"));
	table->vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(load(context, "vkImportSemaphoreWin32HandleKHR"));
#endif /* defined(VK_KHR_external_semaphore_win32) */
#if defined(VK_KHR_get_memory_requirements2)
	table->vkGetBufferMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(load(context, "vkGetBufferMemoryRequirements2KHR"));
	table->vkGetImageMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageMemoryRequirements2KHR>(load(context, "vkGetImageMemoryRequirements2KHR"));
	table->vkGetImageSparseMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2KHR>(load(context, "vkGetImageSparseMemoryRequirements2KHR"));
#endif /* defined(VK_KHR_get_memory_requirements2) */
#if defined(VK_KHR_maintenance1)
	table->vkTrimCommandPoolKHR = reinterpret_cast<PFN_vkTrimCommandPoolKHR>(load(context, "vkTrimCommandPoolKHR"));
#endif /* defined(VK_KHR_maintenance1) */
#if defined(VK_KHR_maintenance3)
	table->vkGetDescriptorSetLayoutSupportKHR = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupportKHR>(load(context, "vkGetDescriptorSetLayoutSupportKHR"));
#endif /* defined(VK_KHR_maintenance3) */
#if defined(VK_KHR_performance_query)
	table->vkAcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(load(context, "vkAcquireProfilingLockKHR"));
	table->vkReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(load(context, "vkReleaseProfilingLockKHR"));
#endif /* defined(VK_KHR_performance_query) */
#if defined(VK_KHR_pipeline_executable_properties)
	table->vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(load(context, "vkGetPipelineExecutableInternalRepresentationsKHR"));
	table->vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(load(context, "vkGetPipelineExecutablePropertiesKHR"));
	table->vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(load(context, "vkGetPipelineExecutableStatisticsKHR"));
#endif /* defined(VK_KHR_pipeline_executable_properties) */
#if defined(VK_KHR_push_descriptor)
	table->vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(load(context, "vkCmdPushDescriptorSetKHR"));
#endif /* defined(VK_KHR_push_descriptor) */
#if defined(VK_KHR_ray_tracing)
	table->vkBindAccelerationStructureMemoryKHR = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryKHR>(load(context, "vkBindAccelerationStructureMemoryKHR"));
	table->vkBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkBuildAccelerationStructureKHR>(load(context, "vkBuildAccelerationStructureKHR"));
	table->vkCmdBuildAccelerationStructureIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureIndirectKHR>(load(context, "vkCmdBuildAccelerationStructureIndirectKHR"));
	table->vkCmdBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureKHR>(load(context, "vkCmdBuildAccelerationStructureKHR"));
	table->vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(load(context, "vkCmdCopyAccelerationStructureKHR"));
	table->vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(load(context, "vkCmdCopyAccelerationStructureToMemoryKHR"));
	table->vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(load(context, "vkCmdCopyMemoryToAccelerationStructureKHR"));
	table->vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(load(context, "vkCmdTraceRaysIndirectKHR"));
	table->vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(load(context, "vkCmdTraceRaysKHR"));
	table->vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(load(context, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
	table->vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(load(context, "vkCopyAccelerationStructureKHR"));
	table->vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(load(context, "vkCopyAccelerationStructureToMemoryKHR"));
	table->vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(load(context, "vkCopyMemoryToAccelerationStructureKHR"));
	table->vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(load(context, "vkCreateAccelerationStructureKHR"));
	table->vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(load(context, "vkCreateRayTracingPipelinesKHR"));
	table->vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(load(context, "vkDestroyAccelerationStructureKHR"));
	table->vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(load(context, "vkGetAccelerationStructureDeviceAddressKHR"));
	table->vkGetAccelerationStructureMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsKHR>(load(context, "vkGetAccelerationStructureMemoryRequirementsKHR"));
	table->vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(load(context, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
	table->vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(load(context, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
	table->vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(load(context, "vkGetRayTracingShaderGroupHandlesKHR"));
	table->vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(load(context, "vkWriteAccelerationStructuresPropertiesKHR"));
#endif /* defined(VK_KHR_ray_tracing) */
#if defined(VK_KHR_sampler_ycbcr_conversion)
	table->vkCreateSamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversionKHR>(load(context, "vkCreateSamplerYcbcrConversionKHR"));
	table->vkDestroySamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversionKHR>(load(context, "vkDestroySamplerYcbcrConversionKHR"));
#endif /* defined(VK_KHR_sampler_ycbcr_conversion) */
#if defined(VK_KHR_shared_presentable_image)
	table->vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(load(context, "vkGetSwapchainStatusKHR"));
#endif /* defined(VK_KHR_shared_presentable_image) */
#if defined(VK_KHR_swapchain)
	table->vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(load(context, "vkAcquireNextImageKHR"));
	table->vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(load(context, "vkCreateSwapchainKHR"));
	table->vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(load(context, "vkDestroySwapchainKHR"));
	table->vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(load(context, "vkGetSwapchainImagesKHR"));
	table->vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(load(context, "vkQueuePresentKHR"));
#endif /* defined(VK_KHR_swapchain) */
#if defined(VK_KHR_timeline_semaphore)
	table->vkGetSemaphoreCounterValueKHR = reinterpret_cast<PFN_vkGetSemaphoreCounterValueKHR>(load(context, "vkGetSemaphoreCounterValueKHR"));
	table->vkSignalSemaphoreKHR = reinterpret_cast<PFN_vkSignalSemaphoreKHR>(load(context, "vkSignalSemaphoreKHR"));
	table->vkWaitSemaphoresKHR = reinterpret_cast<PFN_vkWaitSemaphoresKHR>(load(context, "vkWaitSemaphoresKHR"));
#endif /* defined(VK_KHR_timeline_semaphore) */
#if defined(VK_NVX_image_view_handle)
	table->vkGetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(load(context, "vkGetImageViewAddressNVX"));
	table->vkGetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(load(context, "vkGetImageViewHandleNVX"));
#endif /* defined(VK_NVX_image_view_handle) */
#if defined(VK_NV_clip_space_w_scaling)
	table->vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(load(context, "vkCmdSetViewportWScalingNV"));
#endif /* defined(VK_NV_clip_space_w_scaling) */
#if defined(VK_NV_device_diagnostic_checkpoints)
	table->vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(load(context, "vkCmdSetCheckpointNV"));
	table->vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(load(context, "vkGetQueueCheckpointDataNV"));
#endif /* defined(VK_NV_device_diagnostic_checkpoints) */
#if defined(VK_NV_device_generated_commands)
	table->vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(load(context, "vkCmdBindPipelineShaderGroupNV"));
	table->vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(load(context, "vkCmdExecuteGeneratedCommandsNV"));
	table->vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(load(context, "vkCmdPreprocessGeneratedCommandsNV"));
	table->vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(load(context, "vkCreateIndirectCommandsLayoutNV"));
	table->vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(load(context, "vkDestroyIndirectCommandsLayoutNV"));
	table->vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(load(context, "vkGetGeneratedCommandsMemoryRequirementsNV"));
#endif /* defined(VK_NV_device_generated_commands) */
#if defined(VK_NV_external_memory_win32)
	table->vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(load(context, "vkGetMemoryWin32HandleNV"));
#endif /* defined(VK_NV_external_memory_win32) */
#if defined(VK_NV_mesh_shader)
	table->vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(load(context, "vkCmdDrawMeshTasksIndirectCountNV"));
	table->vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(load(context, "vkCmdDrawMeshTasksIndirectNV"));
	table->vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(load(context, "vkCmdDrawMeshTasksNV"));
#endif /* defined(VK_NV_mesh_shader) */
#if defined(VK_NV_ray_tracing)
	table->vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(load(context, "vkBindAccelerationStructureMemoryNV"));
	table->vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(load(context, "vkCmdBuildAccelerationStructureNV"));
	table->vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(load(context, "vkCmdCopyAccelerationStructureNV"));
	table->vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(load(context, "vkCmdTraceRaysNV"));
	table->vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(load(context, "vkCmdWriteAccelerationStructuresPropertiesNV"));
	table->vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(load(context, "vkCompileDeferredNV"));
	table->vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(load(context, "vkCreateAccelerationStructureNV"));
	table->vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(load(context, "vkCreateRayTracingPipelinesNV"));
	table->vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(load(context, "vkDestroyAccelerationStructureNV"));
	table->vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(load(context, "vkGetAccelerationStructureHandleNV"));
	table->vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(load(context, "vkGetAccelerationStructureMemoryRequirementsNV"));
	table->vkGetRayTracingShaderGroupHandlesNV = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesNV>(load(context, "vkGetRayTracingShaderGroupHandlesNV"));
#endif /* defined(VK_NV_ray_tracing) */
#if defined(VK_NV_scissor_exclusive)
	table->vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(load(context, "vkCmdSetExclusiveScissorNV"));
#endif /* defined(VK_NV_scissor_exclusive) */
#if defined(VK_NV_shading_rate_image)
	table->vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(load(context, "vkCmdBindShadingRateImageNV"));
	table->vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(load(context, "vkCmdSetCoarseSampleOrderNV"));
	table->vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(load(context, "vkCmdSetViewportShadingRatePaletteNV"));
#endif /* defined(VK_NV_shading_rate_image) */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
	table->vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(load(context, "vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif /* (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
	table->vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(load(context, "vkCmdPushDescriptorSetWithTemplateKHR"));
#endif /* (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	table->vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(load(context, "vkGetDeviceGroupPresentCapabilitiesKHR"));
	table->vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(load(context, "vkGetDeviceGroupSurfacePresentModesKHR"));
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	table->vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(load(context, "vkAcquireNextImage2KHR"));
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
	/* VK_LOADER_GENERATE_LOAD_DEVICE_TABLE */
}

#ifdef __GNUC__
	#pragma GCC visibility push(hidden)
#endif

/* VK_LOADER_GENERATE_PROTOTYPES_C */
#if defined(VK_VERSION_1_0)
inline PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
inline PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
inline PFN_vkAllocateMemory vkAllocateMemory;
inline PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
inline PFN_vkBindBufferMemory vkBindBufferMemory;
inline PFN_vkBindImageMemory vkBindImageMemory;
inline PFN_vkCmdBeginQuery vkCmdBeginQuery;
inline PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
inline PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
inline PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
inline PFN_vkCmdBindPipeline vkCmdBindPipeline;
inline PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
inline PFN_vkCmdBlitImage vkCmdBlitImage;
inline PFN_vkCmdClearAttachments vkCmdClearAttachments;
inline PFN_vkCmdClearColorImage vkCmdClearColorImage;
inline PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
inline PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
inline PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
inline PFN_vkCmdCopyImage vkCmdCopyImage;
inline PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
inline PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
inline PFN_vkCmdDispatch vkCmdDispatch;
inline PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
inline PFN_vkCmdDraw vkCmdDraw;
inline PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
inline PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
inline PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
inline PFN_vkCmdEndQuery vkCmdEndQuery;
inline PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
inline PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
inline PFN_vkCmdFillBuffer vkCmdFillBuffer;
inline PFN_vkCmdNextSubpass vkCmdNextSubpass;
inline PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
inline PFN_vkCmdPushConstants vkCmdPushConstants;
inline PFN_vkCmdResetEvent vkCmdResetEvent;
inline PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
inline PFN_vkCmdResolveImage vkCmdResolveImage;
inline PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
inline PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
inline PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
inline PFN_vkCmdSetEvent vkCmdSetEvent;
inline PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
inline PFN_vkCmdSetScissor vkCmdSetScissor;
inline PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
inline PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
inline PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
inline PFN_vkCmdSetViewport vkCmdSetViewport;
inline PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
inline PFN_vkCmdWaitEvents vkCmdWaitEvents;
inline PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
inline PFN_vkCreateBuffer vkCreateBuffer;
inline PFN_vkCreateBufferView vkCreateBufferView;
inline PFN_vkCreateCommandPool vkCreateCommandPool;
inline PFN_vkCreateComputePipelines vkCreateComputePipelines;
inline PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
inline PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
inline PFN_vkCreateDevice vkCreateDevice;
inline PFN_vkCreateEvent vkCreateEvent;
inline PFN_vkCreateFence vkCreateFence;
inline PFN_vkCreateFramebuffer vkCreateFramebuffer;
inline PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
inline PFN_vkCreateImage vkCreateImage;
inline PFN_vkCreateImageView vkCreateImageView;
inline PFN_vkCreateInstance vkCreateInstance;
inline PFN_vkCreatePipelineCache vkCreatePipelineCache;
inline PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
inline PFN_vkCreateQueryPool vkCreateQueryPool;
inline PFN_vkCreateRenderPass vkCreateRenderPass;
inline PFN_vkCreateSampler vkCreateSampler;
inline PFN_vkCreateSemaphore vkCreateSemaphore;
inline PFN_vkCreateShaderModule vkCreateShaderModule;
inline PFN_vkDestroyBuffer vkDestroyBuffer;
inline PFN_vkDestroyBufferView vkDestroyBufferView;
inline PFN_vkDestroyCommandPool vkDestroyCommandPool;
inline PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
inline PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
inline PFN_vkDestroyDevice vkDestroyDevice;
inline PFN_vkDestroyEvent vkDestroyEvent;
inline PFN_vkDestroyFence vkDestroyFence;
inline PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
inline PFN_vkDestroyImage vkDestroyImage;
inline PFN_vkDestroyImageView vkDestroyImageView;
inline PFN_vkDestroyInstance vkDestroyInstance;
inline PFN_vkDestroyPipeline vkDestroyPipeline;
inline PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
inline PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
inline PFN_vkDestroyQueryPool vkDestroyQueryPool;
inline PFN_vkDestroyRenderPass vkDestroyRenderPass;
inline PFN_vkDestroySampler vkDestroySampler;
inline PFN_vkDestroySemaphore vkDestroySemaphore;
inline PFN_vkDestroyShaderModule vkDestroyShaderModule;
inline PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
inline PFN_vkEndCommandBuffer vkEndCommandBuffer;
inline PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
inline PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
inline PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
inline PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
inline PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
inline PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
inline PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
inline PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
inline PFN_vkFreeMemory vkFreeMemory;
inline PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
inline PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
inline PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
inline PFN_vkGetDeviceQueue vkGetDeviceQueue;
inline PFN_vkGetEventStatus vkGetEventStatus;
inline PFN_vkGetFenceStatus vkGetFenceStatus;
inline PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
inline PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
inline PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
inline PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
inline PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
inline PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
inline PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
inline PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
inline PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
inline PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
inline PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
inline PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
inline PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
inline PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
inline PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
inline PFN_vkMapMemory vkMapMemory;
inline PFN_vkMergePipelineCaches vkMergePipelineCaches;
inline PFN_vkQueueBindSparse vkQueueBindSparse;
inline PFN_vkQueueSubmit vkQueueSubmit;
inline PFN_vkQueueWaitIdle vkQueueWaitIdle;
inline PFN_vkResetCommandBuffer vkResetCommandBuffer;
inline PFN_vkResetCommandPool vkResetCommandPool;
inline PFN_vkResetDescriptorPool vkResetDescriptorPool;
inline PFN_vkResetEvent vkResetEvent;
inline PFN_vkResetFences vkResetFences;
inline PFN_vkSetEvent vkSetEvent;
inline PFN_vkUnmapMemory vkUnmapMemory;
inline PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
inline PFN_vkWaitForFences vkWaitForFences;
#endif /* defined(VK_VERSION_1_0) */
#if defined(VK_VERSION_1_1)
inline PFN_vkBindBufferMemory2 vkBindBufferMemory2;
inline PFN_vkBindImageMemory2 vkBindImageMemory2;
inline PFN_vkCmdDispatchBase vkCmdDispatchBase;
inline PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
inline PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
inline PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
inline PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
inline PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
inline PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
inline PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
inline PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
inline PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
inline PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
inline PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
inline PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
inline PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
inline PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
inline PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
inline PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
inline PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
inline PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
inline PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
inline PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
inline PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
inline PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
inline PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
inline PFN_vkTrimCommandPool vkTrimCommandPool;
inline PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
#endif /* defined(VK_VERSION_1_1) */
#if defined(VK_VERSION_1_2)
inline PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
inline PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
inline PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
inline PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
inline PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
inline PFN_vkCreateRenderPass2 vkCreateRenderPass2;
inline PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
inline PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
inline PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
inline PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
inline PFN_vkResetQueryPool vkResetQueryPool;
inline PFN_vkSignalSemaphore vkSignalSemaphore;
inline PFN_vkWaitSemaphores vkWaitSemaphores;
#endif /* defined(VK_VERSION_1_2) */
#if defined(VK_AMD_buffer_marker)
inline PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
#endif /* defined(VK_AMD_buffer_marker) */
#if defined(VK_AMD_display_native_hdr)
inline PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
#endif /* defined(VK_AMD_display_native_hdr) */
#if defined(VK_AMD_draw_indirect_count)
inline PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD;
inline PFN_vkCmdDrawIndirectCountAMD vkCmdDrawIndirectCountAMD;
#endif /* defined(VK_AMD_draw_indirect_count) */
#if defined(VK_AMD_shader_info)
inline PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#endif /* defined(VK_AMD_shader_info) */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
inline PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
inline PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif /* defined(VK_ANDROID_external_memory_android_hardware_buffer) */
#if defined(VK_EXT_acquire_xlib_display)
inline PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
inline PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif /* defined(VK_EXT_acquire_xlib_display) */
#if defined(VK_EXT_buffer_device_address)
inline PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
#endif /* defined(VK_EXT_buffer_device_address) */
#if defined(VK_EXT_calibrated_timestamps)
inline PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
inline PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
#endif /* defined(VK_EXT_calibrated_timestamps) */
#if defined(VK_EXT_conditional_rendering)
inline PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
inline PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
#endif /* defined(VK_EXT_conditional_rendering) */
#if defined(VK_EXT_debug_marker)
inline PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
inline PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
inline PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
inline PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
inline PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
#endif /* defined(VK_EXT_debug_marker) */
#if defined(VK_EXT_debug_report)
inline PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
inline PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
inline PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
#endif /* defined(VK_EXT_debug_report) */
#if defined(VK_EXT_debug_utils)
inline PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
inline PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
inline PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
inline PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
inline PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
inline PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
inline PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
inline PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
inline PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
inline PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
inline PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
#endif /* defined(VK_EXT_debug_utils) */
#if defined(VK_EXT_direct_mode_display)
inline PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#endif /* defined(VK_EXT_direct_mode_display) */
#if defined(VK_EXT_directfb_surface)
inline PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
inline PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif /* defined(VK_EXT_directfb_surface) */
#if defined(VK_EXT_discard_rectangles)
inline PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
#endif /* defined(VK_EXT_discard_rectangles) */
#if defined(VK_EXT_display_control)
inline PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
inline PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
inline PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
inline PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
#endif /* defined(VK_EXT_display_control) */
#if defined(VK_EXT_display_surface_counter)
inline PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
#endif /* defined(VK_EXT_display_surface_counter) */
#if defined(VK_EXT_extended_dynamic_state)
inline PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
inline PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
inline PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
inline PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
inline PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
inline PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
inline PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
inline PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
inline PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
inline PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
inline PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
inline PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
#endif /* defined(VK_EXT_extended_dynamic_state) */
#if defined(VK_EXT_external_memory_host)
inline PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
#endif /* defined(VK_EXT_external_memory_host) */
#if defined(VK_EXT_full_screen_exclusive)
inline PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
inline PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
inline PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
#endif /* defined(VK_EXT_full_screen_exclusive) */
#if defined(VK_EXT_hdr_metadata)
inline PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
#endif /* defined(VK_EXT_hdr_metadata) */
#if defined(VK_EXT_headless_surface)
inline PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#endif /* defined(VK_EXT_headless_surface) */
#if defined(VK_EXT_host_query_reset)
inline PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
#endif /* defined(VK_EXT_host_query_reset) */
#if defined(VK_EXT_image_drm_format_modifier)
inline PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
#endif /* defined(VK_EXT_image_drm_format_modifier) */
#if defined(VK_EXT_line_rasterization)
inline PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
#endif /* defined(VK_EXT_line_rasterization) */
#if defined(VK_EXT_metal_surface)
inline PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif /* defined(VK_EXT_metal_surface) */
#if defined(VK_EXT_private_data)
inline PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
inline PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
inline PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
inline PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
#endif /* defined(VK_EXT_private_data) */
#if defined(VK_EXT_sample_locations)
inline PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
inline PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
#endif /* defined(VK_EXT_sample_locations) */
#if defined(VK_EXT_tooling_info)
inline PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
#endif /* defined(VK_EXT_tooling_info) */
#if defined(VK_EXT_transform_feedback)
inline PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
inline PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
inline PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
inline PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
inline PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
inline PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
#endif /* defined(VK_EXT_transform_feedback) */
#if defined(VK_EXT_validation_cache)
inline PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
inline PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
inline PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
inline PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
#endif /* defined(VK_EXT_validation_cache) */
#if defined(VK_FUCHSIA_imagepipe_surface)
inline PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif /* defined(VK_FUCHSIA_imagepipe_surface) */
#if defined(VK_GGP_stream_descriptor_surface)
inline PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif /* defined(VK_GGP_stream_descriptor_surface) */
#if defined(VK_GOOGLE_display_timing)
inline PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
inline PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
#endif /* defined(VK_GOOGLE_display_timing) */
#if defined(VK_INTEL_performance_query)
inline PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
inline PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
inline PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
inline PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
inline PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
inline PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
inline PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
inline PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
inline PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
#endif /* defined(VK_INTEL_performance_query) */
#if defined(VK_KHR_android_surface)
inline PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif /* defined(VK_KHR_android_surface) */
#if defined(VK_KHR_bind_memory2)
inline PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
inline PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
#endif /* defined(VK_KHR_bind_memory2) */
#if defined(VK_KHR_buffer_device_address)
inline PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
inline PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
inline PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
#endif /* defined(VK_KHR_buffer_device_address) */
#if defined(VK_KHR_create_renderpass2)
inline PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
inline PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
inline PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
inline PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
#endif /* defined(VK_KHR_create_renderpass2) */
#if defined(VK_KHR_deferred_host_operations)
inline PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
inline PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
inline PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
inline PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
inline PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
#endif /* defined(VK_KHR_deferred_host_operations) */
#if defined(VK_KHR_descriptor_update_template)
inline PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
inline PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
inline PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
#endif /* defined(VK_KHR_descriptor_update_template) */
#if defined(VK_KHR_device_group)
inline PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
inline PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
inline PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
#endif /* defined(VK_KHR_device_group) */
#if defined(VK_KHR_device_group_creation)
inline PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
#endif /* defined(VK_KHR_device_group_creation) */
#if defined(VK_KHR_display)
inline PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
inline PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
inline PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
inline PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
inline PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
inline PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
inline PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
#endif /* defined(VK_KHR_display) */
#if defined(VK_KHR_display_swapchain)
inline PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
#endif /* defined(VK_KHR_display_swapchain) */
#if defined(VK_KHR_draw_indirect_count)
inline PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
inline PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
#endif /* defined(VK_KHR_draw_indirect_count) */
#if defined(VK_KHR_external_fence_capabilities)
inline PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
#endif /* defined(VK_KHR_external_fence_capabilities) */
#if defined(VK_KHR_external_fence_fd)
inline PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
inline PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
#endif /* defined(VK_KHR_external_fence_fd) */
#if defined(VK_KHR_external_fence_win32)
inline PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
inline PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
#endif /* defined(VK_KHR_external_fence_win32) */
#if defined(VK_KHR_external_memory_capabilities)
inline PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
#endif /* defined(VK_KHR_external_memory_capabilities) */
#if defined(VK_KHR_external_memory_fd)
inline PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
inline PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#endif /* defined(VK_KHR_external_memory_fd) */
#if defined(VK_KHR_external_memory_win32)
inline PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
inline PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif /* defined(VK_KHR_external_memory_win32) */
#if defined(VK_KHR_external_semaphore_capabilities)
inline PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
#endif /* defined(VK_KHR_external_semaphore_capabilities) */
#if defined(VK_KHR_external_semaphore_fd)
inline PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
inline PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
#endif /* defined(VK_KHR_external_semaphore_fd) */
#if defined(VK_KHR_external_semaphore_win32)
inline PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
inline PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
#endif /* defined(VK_KHR_external_semaphore_win32) */
#if defined(VK_KHR_get_display_properties2)
inline PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
inline PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
inline PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
inline PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
#endif /* defined(VK_KHR_get_display_properties2) */
#if defined(VK_KHR_get_memory_requirements2)
inline PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
inline PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
inline PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
#endif /* defined(VK_KHR_get_memory_requirements2) */
#if defined(VK_KHR_get_physical_device_properties2)
inline PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
inline PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
inline PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
inline PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
inline PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
inline PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
inline PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
#endif /* defined(VK_KHR_get_physical_device_properties2) */
#if defined(VK_KHR_get_surface_capabilities2)
inline PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
inline PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
#endif /* defined(VK_KHR_get_surface_capabilities2) */
#if defined(VK_KHR_maintenance1)
inline PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
#endif /* defined(VK_KHR_maintenance1) */
#if defined(VK_KHR_maintenance3)
inline PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
#endif /* defined(VK_KHR_maintenance3) */
#if defined(VK_KHR_performance_query)
inline PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
inline PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
inline PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
inline PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
#endif /* defined(VK_KHR_performance_query) */
#if defined(VK_KHR_pipeline_executable_properties)
inline PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
inline PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
inline PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
#endif /* defined(VK_KHR_pipeline_executable_properties) */
#if defined(VK_KHR_push_descriptor)
inline PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
#endif /* defined(VK_KHR_push_descriptor) */
#if defined(VK_KHR_ray_tracing)
inline PFN_vkBindAccelerationStructureMemoryKHR vkBindAccelerationStructureMemoryKHR;
inline PFN_vkBuildAccelerationStructureKHR vkBuildAccelerationStructureKHR;
inline PFN_vkCmdBuildAccelerationStructureIndirectKHR vkCmdBuildAccelerationStructureIndirectKHR;
inline PFN_vkCmdBuildAccelerationStructureKHR vkCmdBuildAccelerationStructureKHR;
inline PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
inline PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
inline PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
inline PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
inline PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
inline PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
inline PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
inline PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
inline PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
inline PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
inline PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
inline PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
inline PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
inline PFN_vkGetAccelerationStructureMemoryRequirementsKHR vkGetAccelerationStructureMemoryRequirementsKHR;
inline PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
inline PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
inline PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
inline PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
#endif /* defined(VK_KHR_ray_tracing) */
#if defined(VK_KHR_sampler_ycbcr_conversion)
inline PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
inline PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
#endif /* defined(VK_KHR_sampler_ycbcr_conversion) */
#if defined(VK_KHR_shared_presentable_image)
inline PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#endif /* defined(VK_KHR_shared_presentable_image) */
#if defined(VK_KHR_surface)
inline PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
inline PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
inline PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
inline PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
inline PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
#endif /* defined(VK_KHR_surface) */
#if defined(VK_KHR_swapchain)
inline PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
inline PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
inline PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
inline PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
inline PFN_vkQueuePresentKHR vkQueuePresentKHR;
#endif /* defined(VK_KHR_swapchain) */
#if defined(VK_KHR_timeline_semaphore)
inline PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
inline PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
inline PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
#endif /* defined(VK_KHR_timeline_semaphore) */
#if defined(VK_KHR_wayland_surface)
inline PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
inline PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif /* defined(VK_KHR_wayland_surface) */
#if defined(VK_KHR_win32_surface)
inline PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
inline PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif /* defined(VK_KHR_win32_surface) */
#if defined(VK_KHR_xcb_surface)
inline PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
inline PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif /* defined(VK_KHR_xcb_surface) */
#if defined(VK_KHR_xlib_surface)
inline PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
inline PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif /* defined(VK_KHR_xlib_surface) */
#if defined(VK_MVK_ios_surface)
inline PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif /* defined(VK_MVK_ios_surface) */
#if defined(VK_MVK_macos_surface)
inline PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif /* defined(VK_MVK_macos_surface) */
#if defined(VK_NN_vi_surface)
inline PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif /* defined(VK_NN_vi_surface) */
#if defined(VK_NVX_image_view_handle)
inline PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
inline PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
#endif /* defined(VK_NVX_image_view_handle) */
#if defined(VK_NV_clip_space_w_scaling)
inline PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
#endif /* defined(VK_NV_clip_space_w_scaling) */
#if defined(VK_NV_cooperative_matrix)
inline PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
#endif /* defined(VK_NV_cooperative_matrix) */
#if defined(VK_NV_coverage_reduction_mode)
inline PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#endif /* defined(VK_NV_coverage_reduction_mode) */
#if defined(VK_NV_device_diagnostic_checkpoints)
inline PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
inline PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
#endif /* defined(VK_NV_device_diagnostic_checkpoints) */
#if defined(VK_NV_device_generated_commands)
inline PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
inline PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
inline PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
inline PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
inline PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
inline PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
#endif /* defined(VK_NV_device_generated_commands) */
#if defined(VK_NV_external_memory_capabilities)
inline PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#endif /* defined(VK_NV_external_memory_capabilities) */
#if defined(VK_NV_external_memory_win32)
inline PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
#endif /* defined(VK_NV_external_memory_win32) */
#if defined(VK_NV_mesh_shader)
inline PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
inline PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
inline PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
#endif /* defined(VK_NV_mesh_shader) */
#if defined(VK_NV_ray_tracing)
inline PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
inline PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
inline PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
inline PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
inline PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
inline PFN_vkCompileDeferredNV vkCompileDeferredNV;
inline PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
inline PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
inline PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
inline PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
inline PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
inline PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
#endif /* defined(VK_NV_ray_tracing) */
#if defined(VK_NV_scissor_exclusive)
inline PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
#endif /* defined(VK_NV_scissor_exclusive) */
#if defined(VK_NV_shading_rate_image)
inline PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
inline PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
inline PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
#endif /* defined(VK_NV_shading_rate_image) */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
inline PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif /* (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
inline PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
#endif /* (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
inline PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
inline PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
inline PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
inline PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
#endif /* (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) */
/* VK_LOADER_GENERATE_PROTOTYPES_C */

#ifdef __GNUC__
	#pragma GCC visibility pop
#endif

/**
 * Copyright (c) 2018-2019 Arseny Kapoulkine
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
