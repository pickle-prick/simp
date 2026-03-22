#ifndef RENDER_VK_H
#define RENDER_VK_H

////////////////////////////////
//~ Generated Includes

#include "generated/render_vulkan.meta.h"

////////////////////////////////
//~ Limits & Constants

// Syncronization
// We choose the number 2 here because we don't want the CPU to get too far
// ahead of the GPU With 2 frames in flight, the CPU and the GPU can be working
// on their own tasks at the same time If the CPU finishes early, it will wait
// till the GPU finishes rendering before submitting more work With 3 or more
// frames in flight, the CPU could get ahead of the GPU, because the work load
// of the GPU could be too larger for it to handle, so the CPU would end up
// waiting a lot, adding frames of latency Generally extra latency isn't desired
#define R_VK_MAX_FRAMES_IN_FLIGHT 1
#define R_VK_STAGING_IN_FLIGHT_COUNT 2
// support max 4K with 32x32 sized tile
#define R_VK_TILE_SIZE 32
#define R_VK_MAX_TILES_PER_PASS ((3840*2160)/(R_VK_TILE_SIZE*R_VK_TILE_SIZE))
#define R_VK_MAX_LIGHTS_PER_TILE 200
#define R_VK_MAX_SURFACE_FORMATS 16
#define R_VK_MAX_SURFACE_PRESENT_MODES 16

////////////////////////////////
//~ Enums

typedef enum R_VK_VShadKind
{
  R_VK_VShadKind_Rect,
  // R_VK_VShadKind_Blur,
  R_VK_VShadKind_Noise,
  R_VK_VShadKind_Edge,
  R_VK_VShadKind_Crt,
  R_VK_VShadKind_Geo2D_Forward,
  R_VK_VShadKind_Geo2D_Composite,
  R_VK_VShadKind_Geo3D_ZPre,
  R_VK_VShadKind_Geo3D_Debug,
  R_VK_VShadKind_Geo3D_Forward,
  R_VK_VShadKind_Geo3D_Composite,
  R_VK_VShadKind_Finalize,
  R_VK_VShadKind_COUNT,
} R_VK_VShadKind;

typedef enum R_VK_FShadKind
{
  R_VK_FShadKind_Rect,
  // R_VK_FShadKind_Blur,
  R_VK_FShadKind_Noise,
  R_VK_FShadKind_Edge,
  R_VK_FShadKind_Crt,
  R_VK_FShadKind_Geo2D_Forward,
  R_VK_FShadKind_Geo2D_Composite,
  R_VK_FShadKind_Geo3D_ZPre,
  R_VK_FShadKind_Geo3D_Debug,
  R_VK_FShadKind_Geo3D_Forward,
  R_VK_FShadKind_Geo3D_Composite,
  R_VK_FShadKind_Finalize,
  R_VK_FShadKind_COUNT,
} R_VK_FShadKind;

typedef enum R_VK_CShadKind
{
  R_VK_CShadKind_Geo3D_TileFrustum,
  R_VK_CShadKind_Geo3D_LightCulling,
  R_VK_CShadKind_COUNT,
} R_VK_CShadKind;

// FIXME: we could also add a Dedicate kind for dedicated allocation
typedef enum R_VK_MemoryHeapUsage
{
  R_VK_MemoryHeapUsage_Linear,
  R_VK_MemoryHeapUsage_NonLinear,
  R_VK_MemoryHeapUsage_COUNT,
} R_VK_MemoryHeapUsage;

typedef enum R_VK_UBOTypeKind
{
  R_VK_UBOTypeKind_Rect,
  // R_VK_UBOTypeKind_Blur,
  R_VK_UBOTypeKind_Geo2D,
  R_VK_UBOTypeKind_Geo3D,
  R_VK_UBOTypeKind_Geo3D_TileFrustum,
  R_VK_UBOTypeKind_Geo3D_LightCulling,
  R_VK_UBOTypeKind_COUNT,
} R_VK_UBOTypeKind;

typedef enum R_VK_SBOTypeKind
{
  R_VK_SBOTypeKind_Geo3D_Joints,
  R_VK_SBOTypeKind_Geo3D_Materials,
  R_VK_SBOTypeKind_Geo3D_Tiles,
  R_VK_SBOTypeKind_Geo3D_Lights,
  R_VK_SBOTypeKind_Geo3D_LightIndices,
  R_VK_SBOTypeKind_Geo3D_TileLights,
  R_VK_SBOTypeKind_COUNT,
} R_VK_SBOTypeKind;

typedef enum R_VK_DescriptorSetKind
{
  R_VK_DescriptorSetKind_Tex2D,
  // ui
  R_VK_DescriptorSetKind_UBO_Rect,
  // 2d
  R_VK_DescriptorSetKind_UBO_Geo2D,
  // 3d
  R_VK_DescriptorSetKind_UBO_Geo3D,
  R_VK_DescriptorSetKind_UBO_Geo3D_TileFrustum,
  R_VK_DescriptorSetKind_UBO_Geo3D_LightCulling,
  R_VK_DescriptorSetKind_SBO_Geo3D_Joints,
  R_VK_DescriptorSetKind_SBO_Geo3D_Materials,
  R_VK_DescriptorSetKind_SBO_Geo3D_Tiles,
  R_VK_DescriptorSetKind_SBO_Geo3D_Lights,
  R_VK_DescriptorSetKind_SBO_Geo3D_LightIndices,
  R_VK_DescriptorSetKind_SBO_Geo3D_TileLights,
  R_VK_DescriptorSetKind_COUNT,
} R_VK_DescriptorSetKind;

typedef enum R_VK_PipelineKind
{
  // gfx pipeline
  R_VK_PipelineKind_GFX_Rect,
  // R_VK_PipelineKind_GFX_Blur,
  R_VK_PipelineKind_GFX_Noise,
  R_VK_PipelineKind_GFX_Edge,
  R_VK_PipelineKind_GFX_Crt,
  // 2d
  R_VK_PipelineKind_GFX_Geo2D_Forward,
  R_VK_PipelineKind_GFX_Geo2D_Composite,
  // 3d
  R_VK_PipelineKind_GFX_Geo3D_ZPre,
  R_VK_PipelineKind_GFX_Geo3D_Debug,
  R_VK_PipelineKind_GFX_Geo3D_Forward,
  R_VK_PipelineKind_GFX_Geo3D_Composite,
  R_VK_PipelineKind_GFX_Finalize,
  // compute pipeline
  R_VK_PipelineKind_CMP_Geo3D_TileFrustum,
  R_VK_PipelineKind_CMP_Geo3D_LightCulling,
  R_VK_PipelineKind_COUNT,
} R_VK_PipelineKind;

typedef enum R_VK_Light3DKind
{
  R_VK_Light3DKind_Directional,
  R_VK_Light3DKind_Point,
  R_VK_Light3DKind_Spot,
  R_VK_Light3DKind_COUNT,
} R_VK_Light3DKind;

////////////////////////////////
//~ Light Calc Types

typedef struct R_VK_Plane R_VK_Plane;
struct R_VK_Plane
{
  Vec3F32 N; // plane normal
  F32 d; // distance to the origin
};

typedef struct R_VK_Frustum R_VK_Frustum;
struct R_VK_Frustum
{
  R_VK_Plane planes[6];
};

////////////////////////////////
//~ C-side Shader Types (ubo,push,sbo)

//- ubo

typedef struct R_VK_UBO_Rect R_VK_UBO_Rect;
struct R_VK_UBO_Rect
{
  Vec2F32 viewport_size;
  F32 opacity;
  F32 _padding0_;
  Vec4F32 texture_sample_channel_map[4];
  Vec2F32 texture_t2d_size;
  Vec2F32 translate;
  Vec4F32 xform[3];
  Vec2F32 xform_scale;
  F32 _padding1_[2];
};
// StaticAssert(sizeof(R_VK_UBO_Rect) % 256 == 0, NotAligned); // constant count/offset must be aligned to 256 bytes

// typedef struct R_D3D11_Uniforms_BlurPass R_D3D11_Uniforms_BlurPass;
// struct R_D3D11_Uniforms_BlurPass
// {
//   Rng2F32 rect;
//   Vec4F32 corner_radii;
//   Vec2F32 direction;
//   Vec2F32 viewport_size;
//   U32 blur_count;
//   U8 _padding0_[204];
// };
// StaticAssert(sizeof(R_D3D11_Uniforms_BlurPass) % 256 == 0, NotAligned); // constant count/offset must be aligned to 256 bytes

// typedef struct R_D3D11_Uniforms_Blur R_D3D11_Uniforms_Blur;
// struct R_D3D11_Uniforms_Blur
// {
//   R_D3D11_Uniforms_BlurPass passes[Axis2_COUNT];
//   Vec4F32 kernel[32];
// };

typedef struct R_VK_UBO_Geo2D R_VK_UBO_Geo2D;
struct R_VK_UBO_Geo2D
{
  Mat4x4F32 proj;
  Mat4x4F32 proj_inv;
  Mat4x4F32 view;
  Mat4x4F32 view_inv;
};

typedef struct R_VK_UBO_Geo3D R_VK_UBO_Geo3D;
struct R_VK_UBO_Geo3D
{
  Mat4x4F32 view;
  Mat4x4F32 view_inv;
  Mat4x4F32 proj;
  Mat4x4F32 proj_inv;

  // Debug
  U32       show_grid;
  U32       _padding_0[3];
};

typedef struct R_VK_UBO_Geo3D_TileFrustum R_VK_UBO_Geo3D_TileFrustum;
struct R_VK_UBO_Geo3D_TileFrustum
{
  Mat4x4F32 proj_inv;
  Vec2U32 grid_size;
  U32 _padding_0[2];
};

typedef struct R_VK_UBO_Geo3D_LightCulling R_VK_UBO_Geo3D_LightCulling;
struct R_VK_UBO_Geo3D_LightCulling
{
  Mat4x4F32 proj_inv;
  U32 light_count;
  U32 _padding_0[3];
};

//- push

typedef struct R_VK_PUSH_Geo3D_Forward R_VK_PUSH_Geo3D_Forward;
struct R_VK_PUSH_Geo3D_Forward
{
  Vec2F32 viewport;
  Vec2U32 light_grid_size;
};

typedef struct R_VK_PUSH_Noise R_VK_PUSH_Noise;
struct R_VK_PUSH_Noise
{
  Vec2F32 resolution;
  Vec2F32 mouse;
  F32 time;
};

typedef struct R_VK_PUSH_Edge R_VK_PUSH_Edge;
struct R_VK_PUSH_Edge
{
  F32 time;
};

typedef struct R_VK_PUSH_Crt R_VK_PUSH_Crt;
struct R_VK_PUSH_Crt
{
  Vec2F32 resolution;
  F32 warp;
  F32 scan;
  F32 time;
};

// -sbo

#define R_VK_SBO_Geo3D_Joint Mat4x4F32

typedef struct R_VK_SBO_Geo3D_Tile R_VK_SBO_Geo3D_Tile;
struct R_VK_SBO_Geo3D_Tile
{
  R_VK_Frustum frustum;
};

#define R_VK_SBO_Geo3D_Light R_Geo3D_Light

// NOTE(k): first element will be used as indice_count
// NOTE(K): we are using std140, so packed it to 16 bytes boundary
#define R_VK_SBO_Geo3D_LightIndice U32[4]

typedef struct R_VK_SBO_Geo3D_TileLights R_VK_SBO_Geo3D_TileLights;
struct R_VK_SBO_Geo3D_TileLights
{
  U32 offset;  
  U32 light_count;
  F32 _padding_0[2];
};

#define R_VK_SBO_Geo3D_Material R_Geo3D_Material

////////////////////////////////
//~ Vulkan Device Types

typedef struct R_VK_Surface R_VK_Surface;
struct R_VK_Surface
{
  VkSurfaceKHR h;

  VkSurfaceCapabilitiesKHR caps;
  VkSurfaceFormatKHR formats[R_VK_MAX_SURFACE_FORMATS];
  U32 format_count;
  VkPresentModeKHR prest_modes[R_VK_MAX_SURFACE_PRESENT_MODES];
  U32 prest_mode_count;
};

typedef struct R_VK_Image R_VK_Image;
struct R_VK_Image
{
  VkImage h;
  VkFormat format;
  struct R_VK_Memory *memory;
  VkImageView view;
  VkExtent2D extent;
  // FIXME: didn't use for now, may remove it later
  VkImageLayout gpu_layout;
};

typedef struct R_VK_Swapchain R_VK_Swapchain;
struct R_VK_Swapchain
{
  VkSwapchainKHR h;
  VkExtent2D extent;
  VkFormat format;
  VkColorSpaceKHR color_space;
  U32 image_count;
  VkImage images[8];
  VkImageView image_views[8];
  // Semaphores that are waited on by QueuePresent are buffered based on the bumber of swapchain images
  VkSemaphore submit_semaphores[8];
};

typedef struct R_VK_PhysicalDevice R_VK_PhysicalDevice;
struct R_VK_PhysicalDevice
{
  VkPhysicalDevice h;
  VkPhysicalDeviceProperties properties;
  VkPhysicalDeviceMemoryProperties mem_properties;
  VkPhysicalDeviceFeatures features;
  VkExtensionProperties *extensions;
  U64 extension_count;
  U32 gfx_queue_family_index;
  U32 cmp_queue_family_index;
  U32 prest_queue_family_index;
  // U32 xfer_queue_family_index;
  VkFormat depth_image_format;
};

typedef struct R_VK_LogicalDevice R_VK_LogicalDevice;
struct R_VK_LogicalDevice
{
  VkDevice h;
  VkQueue gfx_queue;
  VkQueue prest_queue;
  // VkQueue  xfer_queue;
};

typedef struct R_VK_Memory R_VK_Memory;
struct R_VK_Memory
{
  VkDeviceMemory h;
  U64 offset; // offset into the heap blcok
  U64 size;
  void *mapped; // already account for offset
};

// NOTE(k): every block is a dedicated memory allocation
typedef struct R_VK_MemoryHeapBlockSlot R_VK_MemoryHeapBlockSlot;
struct R_VK_MemoryHeapBlockSlot
{
  R_VK_MemoryHeapBlockSlot *free_next;
  R_VK_Memory memory;
  struct R_VK_MemoryHeapBlock *block; // NOTE(k): we need to get heap block when doing memory mapping, since we can't map vk_memory twice
};

typedef struct R_VK_MemoryHeapBlock R_VK_MemoryHeapBlock;
struct R_VK_MemoryHeapBlock
{
  struct R_VK_MemoryHeapPool *pool;
  VkDeviceMemory memory_handle;
  void *mapped;

  R_VK_MemoryHeapBlock *free_next;

  R_VK_MemoryHeapBlock *next;
  R_VK_MemoryHeapBlock *prev;

  R_VK_MemoryHeapBlockSlot *slots;
  U64 slot_count;
  U64 slot_size;

  // free slot stack
  R_VK_MemoryHeapBlockSlot *first_free_slot;
};

read_only global U64 r_vk_memory_chunk_sizes[] =
{
  256ULL,                // 0.25 KB (Minimum Vulkan alignment)
  1024ULL,               // 1 KB
  4096ULL,               // 4 KB
  16384ULL,              // 16 KB
  65536ULL,              // 64 KB
  262144ULL,             // 256 KB
  1048576ULL,            // 1 MB
  4194304ULL,            // 4 MB
  16777216ULL,           // 16 MB
  67108864ULL,           // 64 MB
  268435456ULL,          // 256 MB
  1073741824ULL,         // 1 GB
  // 0xffffffffffffffffull, // Fallback for huge manual allocations
};
// FIXME: these sizes need to be power of 2, we need to do some static assertion here

typedef struct R_VK_MemoryHeapPool R_VK_MemoryHeapPool;
struct R_VK_MemoryHeapPool
{
  // free stack (blocks which has free slot)
  R_VK_MemoryHeapBlock *first_free_block;

  // linear links
  R_VK_MemoryHeapBlock *first_block;
  R_VK_MemoryHeapBlock *last_block;
  U64 block_count;
};

typedef struct R_VK_LogicalMemoryHeap R_VK_LogicalMemoryHeap;
struct R_VK_LogicalMemoryHeap
{
  U32 physical_heap_idx;
  VkMemoryPropertyFlags property_flags;
  // NOTE(k): alignment == chunk_size
  R_VK_MemoryHeapPool pools[ArrayCount(r_vk_memory_chunk_sizes)][R_VK_MemoryHeapUsage_COUNT];
};

typedef struct R_VK_PhysicalMemoryHeap R_VK_PhysicalMemoryHeap;
struct R_VK_PhysicalMemoryHeap
{
  VkMemoryHeapFlags flags;
  U64 cmt;
  U64 res;
  U64 cap; // total size avaiable for this heap on the device
};

typedef struct R_VK_MemoryAllocator R_VK_MemoryAllocator;
struct R_VK_MemoryAllocator
{
  R_VK_LogicalMemoryHeap *logical_heaps;
  U64 logical_heap_count;

  R_VK_PhysicalMemoryHeap *physical_heaps;
  U64 physical_heap_count;
};

typedef struct R_VK_Pipeline R_VK_Pipeline;
struct R_VK_Pipeline
{
  R_VK_PipelineKind kind;
  VkPipeline h;
  VkPipelineLayout layout;
};

typedef struct R_VK_Buffer R_VK_Buffer;
struct R_VK_Buffer
{
  R_VK_Buffer *next;
  U64 generation;

  VkBuffer h;
  R_VK_Memory *memory;

  R_ResourceKind kind; // NOTE(k): used for application side, we don't really need this internally

  U64 size;
};

typedef struct R_VK_DescriptorSetLayout R_VK_DescriptorSetLayout;
struct R_VK_DescriptorSetLayout
{
  VkDescriptorSetLayoutBinding *bindings;
  U64 binding_count;
  VkDescriptorSetLayout h;
};

typedef struct R_VK_DescriptorSetPool R_VK_DescriptorSetPool;
struct R_VK_DescriptorSetPool
{
  R_VK_DescriptorSetPool *next;
  R_VK_DescriptorSetKind kind;
  VkDescriptorPool h;
  U64 cmt;
  U64 cap;
};

typedef struct R_VK_DescriptorSet R_VK_DescriptorSet;
struct R_VK_DescriptorSet
{
  VkDescriptorSet h;
  R_VK_DescriptorSetPool *pool;
};

// FIXME: we should remove UBOBuffer and SBOBuffer types, just create BufferArray or something else 
typedef struct R_VK_UBOBuffer R_VK_UBOBuffer;
struct R_VK_UBOBuffer
{
  R_VK_Buffer buffer;
  R_VK_DescriptorSet set;
  U64 unit_count;
  U64 stride;
};

typedef struct R_VK_SBOBuffer R_VK_SBOBuffer;
struct R_VK_SBOBuffer
{
  R_VK_Buffer buffer;
  R_VK_DescriptorSet set;
  U64 unit_count;
  U64 stride;
};

typedef struct R_VK_Tex2D R_VK_Tex2D;
struct R_VK_Tex2D
{
  R_VK_Tex2D *next;
  U64 generation;
  R_VK_DescriptorSet desc_set;
  R_VK_Image image;
  R_Tex2DFormat format;
  R_Tex2DSampleKind sample_kind;
};

typedef struct R_VK_RenderTargets R_VK_RenderTargets;
struct R_VK_RenderTargets
{
  R_VK_RenderTargets *next;
  // NOTE(k): If swapchain image format changed, we would need to recreate renderpass and pipeline
  //          If only extent of swapchain image changed, we could just recrete the swapchain
  R_VK_Swapchain     swapchain;

  R_VK_Image         stage_color_image;
  R_VK_DescriptorSet stage_color_ds;
  R_VK_Image         stage_id_image;
  R_VK_Buffer        stage_id_cpu;
  // scratch
  R_VK_Image         scratch_color_image;
  R_VK_DescriptorSet scratch_color_ds;
  // edge
  R_VK_Image         edge_image;
  R_VK_DescriptorSet edge_ds;
  // 2d
  R_VK_Image         geo2d_color_image;
  R_VK_DescriptorSet geo2d_color_ds;

  // 3d
  // TODO(XXX): this is a mess, cleanup unused image, also add toon shading post pass
  R_VK_Image         geo3d_color_image;
  R_VK_DescriptorSet geo3d_color_ds;
  R_VK_Image         geo3d_normal_depth_image;
  R_VK_DescriptorSet geo3d_normal_depth_ds;
  R_VK_Image         geo3d_depth_image;
  R_VK_Image         geo3d_pre_depth_image;
  R_VK_DescriptorSet geo3d_pre_depth_ds;

  U64                rc;
  U64                deprecated_at_frame;
};

typedef struct R_VK_Frame R_VK_Frame;
struct R_VK_Frame
{
  VkSemaphore img_acq_sem;
  VkFence inflt_fence;
  U32 img_idx;
  VkCommandBuffer cmd_buf;

  R_VK_RenderTargets *render_targets_ref;

  // UBO buffer and descriptor set
  R_VK_UBOBuffer ubo_buffers[R_VK_UBOTypeKind_COUNT];

  // Storage buffer and descriptor set
  R_VK_SBOBuffer sbo_buffers[R_VK_SBOTypeKind_COUNT];

  // Instance buffer
  R_VK_Buffer inst_buffer_rect[R_MAX_RECT_PASS];
  R_VK_Buffer inst_buffer_mesh2d[R_MAX_GEO2D_PASS];
  R_VK_Buffer inst_buffer_mesh3d[R_MAX_GEO3D_PASS];
};

typedef struct R_VK_Window R_VK_Window;
struct R_VK_Window
{
  // allocation link
  U64 generation;
  R_VK_Window *next;

  OS_Handle os_wnd;

  R_VK_Surface surface;
  R_VK_RenderTargets *render_targets;
  union
  {
    struct
    {
      R_VK_Pipeline rect;
      // R_VK_Pipeline blur;
      R_VK_Pipeline noise;
      R_VK_Pipeline edge;
      R_VK_Pipeline crt;
      struct
      {
        R_VK_Pipeline forward[R_GeoTopologyKind_COUNT * R_GeoPolygonKind_COUNT];
        R_VK_Pipeline composite;
      } geo2d;
      struct
      {
        R_VK_Pipeline tile_frustum;
        R_VK_Pipeline light_culling;
        R_VK_Pipeline z_pre[R_GeoTopologyKind_COUNT * R_GeoPolygonKind_COUNT];
        R_VK_Pipeline debug[R_GeoTopologyKind_COUNT * R_GeoPolygonKind_COUNT];
        R_VK_Pipeline forward[R_GeoTopologyKind_COUNT * R_GeoPolygonKind_COUNT];
        R_VK_Pipeline composite;
      } geo3d;
      R_VK_Pipeline finalize;
    };
    // TODO(XXX): not sure if we need some paddings here
    R_VK_Pipeline arr[R_GeoTopologyKind_COUNT * R_GeoPolygonKind_COUNT * 4 + 9];
  } pipelines;

  R_VK_Frame frames[R_VK_MAX_FRAMES_IN_FLIGHT];
  U64 curr_frame_idx;

  // buffer index/offset per frame (for dynamic buffer)
  U64 ui_group_index;   // ubo is per ui group
  U64 ui_pass_index;    // inst buffer is per ui pass
  U64 geo2d_pass_index; // ubo and inst buffer is per geo2d pass
  U64 geo3d_pass_index; // ubo and inst buffer is per geo3d pass
};

////////////////////////////////
//~ Staging Ring Buffer

typedef struct R_VK_StagingRing R_VK_StagingRing;
struct R_VK_StagingRing
{
  VkBuffer buffer;
  VkDeviceMemory memory;
  void *mapped;

  U64 cap;
  U64 head; // next write offset
  U64 tail; // oldest in-flight offset (safe to reuse before this) 
};

typedef struct R_VK_StagingSlice R_VK_StagingSlice;
struct R_VK_StagingSlice
{
  U64 offset;
  U64 size;
  void *ptr; // mapped + offset
};

// per frame
typedef struct R_VK_StagingBatch R_VK_StagingBatch;
struct R_VK_StagingBatch
{
  // per-upload state
  U64 size;
  U64 start;
  U64 end;
  B32 submitted;
  // per-frame artifacts (darray)
  R_VK_Image **images;
};

typedef struct R_VK_Stage R_VK_Stage;
struct R_VK_Stage
{
  R_VK_StagingRing ring;
  VkCommandBuffer cmds[R_VK_STAGING_IN_FLIGHT_COUNT];
  VkFence fences[R_VK_STAGING_IN_FLIGHT_COUNT];
  R_VK_StagingBatch batches[R_VK_STAGING_IN_FLIGHT_COUNT];
  U64 idx; // in-flight rotation index
  U64 last_touch_frame_index;
};

////////////////////////////////
//~ State Types

typedef struct R_VK_State R_VK_State;
struct R_VK_State
{
  bool                                debug;
  VkDebugUtilsMessengerEXT            debug_messenger;
  PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;

  Arena                               *arena;
  Arena                               *frame_arena;
  RWMutex                             device_rw_mutex; // FIXME: not used for now

  /* Instance Info */
  // The interface between application and the Vulkan library (the driver/loader)
  VkInstance                          instance;
  U32                                 instance_version_major;
  U32                                 instance_version_minor;
  U32                                 instance_version_patch;

  /* Device */
  R_VK_PhysicalDevice                 *physical_device;
  R_VK_LogicalDevice                  *logical_device;

  VkSampler                           samplers[R_Tex2DSampleKind_COUNT];
  R_VK_DescriptorSetLayout            set_layouts[R_VK_DescriptorSetKind_COUNT];

  /* Shader modules */
  VkShaderModule                      vshad_modules[R_VK_VShadKind_COUNT];
  VkShaderModule                      fshad_modules[R_VK_FShadKind_COUNT];
  VkShaderModule                      cshad_modules[R_VK_CShadKind_COUNT];

  // FIXME: clean it up
  VkCommandPool                       cmd_pool;
  // TODO(Next): deprecated, remove this ASAP
  // For copying staging buffer or transition image layout
  VkCommandBuffer                     oneshot_cmd_buf;

  // FIXME: don't need it either, we need some kind of StageBatch here
  R_VK_Stage                          stage;

  R_VK_MemoryAllocator                *allocator;

  /* Resource free list */
  R_VK_Window                         *first_free_window;
  R_VK_Tex2D                          *first_free_tex2d;
  R_VK_Buffer                         *first_free_buffer;
  R_VK_RenderTargets                  *first_free_render_targets;
  R_VK_DescriptorSetPool              *first_avail_ds_pool[R_VK_DescriptorSetKind_COUNT];
  R_VK_RenderTargets                  *first_to_free_render_targets;
  R_VK_RenderTargets                  *last_to_free_render_targets;

  // TODO(k): first_free_descriptor, we could update descriptor to point a new buffer or image/sampler
  // TODO(k): we may want to keep track of filled ds_pool

  /* Misc */
  R_Handle                            backup_texture;
  U64                                 frame_index;

  /* Stack */
  R_VK_DeclStackNils;
  R_VK_DeclStacks;
};

////////////////////////////////
//~ Globals

global R_VK_State *r_vk_state = 0;

////////////////////////////////
//~ Window Functions

internal R_Handle     r_vk_handle_from_window(R_VK_Window *window);
internal R_VK_Window* r_vk_window_from_handle(R_Handle handle);
internal void         r_vk_window_resize(R_VK_Window *window);

////////////////////////////////
//~ Tex2D Functions

internal R_VK_Tex2D* r_vk_tex2d_from_handle(R_Handle handle);
internal R_Handle    r_vk_handle_from_tex2d(R_VK_Tex2D *texture);

////////////////////////////////
//~ Buffer Functions

internal R_VK_Buffer* r_vk_buffer_from_handle(R_Handle handle);
internal R_Handle     r_vk_handle_from_buffer(R_VK_Buffer *buffer);

////////////////////////////////
//~ State Getter

#define r_vk_pdevice() (r_vk_state->physical_device)
#define r_vk_ldevice() (r_vk_state->logical_device)

////////////////////////////////
//~ Stage Ring Buffer Functions

internal void              r_vk_stage_init();
internal R_VK_StagingSlice r_vk_staging_slice_from_size(U64 size, U64 alignment);
internal U64               r_vk_free_size_from_staging_ring(U64 alignment);
internal void              r_vk_stage_begin();
internal void              r_vk_stage_end();
internal void              r_vk_stage_bump();
internal void              r_vk_stage_copy_image(void *src, U64 size, R_VK_Image *dst, Vec3S32 offset, Vec3S32 extent);

////////////////////////////////
//~ Vulkan Resource Allocation

//- swapchain
internal R_VK_Swapchain        r_vk_swapchain(R_VK_Surface *surface, OS_Handle os_wnd, VkFormat format, VkColorSpaceKHR color_space, R_VK_Swapchain *old);
internal void                  r_vk_format_for_swapchain(VkSurfaceFormatKHR *formats, U64 count, VkFormat *format, VkColorSpaceKHR *color_space);

//- surface
internal VkFormat              r_vk_optimal_depth_format_from_pdevice(VkPhysicalDevice pdevice);
internal void                  r_vk_surface_update(R_VK_Surface *surface);

//- memory
internal R_VK_Memory*          r_vk_memory_alloc(R_VK_MemoryHeapUsage usage, VkMemoryRequirements mem_requirements, VkMemoryPropertyFlagBits preferred_property_flags, VkMemoryPropertyFlagBits fallback_property_flags);
internal void                  r_vk_memory_release(R_VK_Memory *memory);
internal void                  r_vk_memory_map(R_VK_Memory *memory);
internal VkMemoryPropertyFlags r_vk_property_flags_from_memroy(R_VK_Memory *memory);

//- buffer
internal R_VK_UBOBuffer        r_vk_ubo_buffer_alloc(R_VK_UBOTypeKind kind, U64 unit_count);
internal R_VK_SBOBuffer        r_vk_sbo_buffer_alloc(R_VK_SBOTypeKind kind, U64 unit_count);
internal R_VK_Buffer*          r_vk_stage_buffer_from_size(U64 size);
internal void                  r_vk_buffer_release(R_VK_Buffer *buffer);

//- render targets
internal R_VK_RenderTargets*   r_vk_render_targets_alloc(OS_Handle os_wnd, R_VK_Surface *surface, R_VK_RenderTargets *old);
internal void                  r_vk_render_targets_destroy(R_VK_RenderTargets *render_targets);

//- descriptor
internal void                  r_vk_descriptor_set_alloc(R_VK_DescriptorSetKind kind, U64 set_count, U64 cap, VkBuffer *buffers, VkImageView *image_views, VkSampler *sampler, R_VK_DescriptorSet *sets);
internal void                  r_vk_descriptor_set_destroy(R_VK_DescriptorSet *set);

//- sync primitives
internal VkFence               r_vk_fence();
internal VkSemaphore           r_vk_semaphore(VkDevice device);
internal void                  r_vk_cleanup_unsafe_semaphore(VkQueue queue, VkSemaphore semaphore);

//- sync helpers
internal void                  r_vk_image_transition(VkCommandBuffer cmd_buf, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout, VkPipelineStageFlags src_stage, VkAccessFlags src_access_flag, VkPipelineStageFlags dst_stage, VkAccessFlags dst_access_flag, VkImageAspectFlags aspect_mask);

//- pipeline
internal R_VK_Pipeline         r_vk_gfx_pipeline(R_VK_PipelineKind kind, R_GeoTopologyKind topology, R_GeoPolygonKind polygon, VkFormat swapchain_format, R_VK_Pipeline *old);
internal R_VK_Pipeline         r_vk_cmp_pipeline(R_VK_PipelineKind kind);

//- sampler
internal VkSampler             r_vk_sampler2d(R_Tex2DSampleKind kind);

//- helpers
internal S32                   r_vk_memory_index_from_type_filer(U32 type_bits, VkMemoryPropertyFlags properties);

//- instance buffers

internal R_VK_InstanceBuffer*  r_vk_instance_buffer_from_size(U64 size);
// internal void r_usage_access_flags_from_resource_kind(R_ResourceKind kind, D3D11_USAGE *out_vulkan_usage, UINT *out_cpu_access_flags);

////////////////////////////////
//~ Helper Functions

//- debug
internal VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data, void *p_userdata);
#define VK_Assert(result) \
  do { \
    if((result) != VK_SUCCESS) { \
      Temp scratch = scratch_begin(0, 0); \
      String8 err_msg = push_str8f(scratch.arena, "[VK_ERROR] [CODE: %d] in (%s)(%s:%i)", result, __FUNCTION__, __FILE__, __LINE__); \
      os_graphical_message(1, str8_lit("Fatal Error"), err_msg); \
      Trap(); \
      os_abort(1); \
      scratch_end(scratch); \
    } \
  } while (0)

//- command buffer scope
internal void r_vk_cmd_begin(VkCommandBuffer cmd_buf);
internal void r_vk_cmd_end(VkCommandBuffer cmd_buf);
#define CmdScope(c) DeferLoop((r_vk_cmd_begin((c))), r_vk_cmd_end((c)))

#endif
