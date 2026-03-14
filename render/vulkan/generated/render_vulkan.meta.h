// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

//- GENERATED CODE

#ifndef RENDER_VULKAN_META_H
#define RENDER_VULKAN_META_H

typedef struct R_VK_CmdNode R_VK_CmdNode; struct R_VK_CmdNode{R_VK_CmdNode *next; VkCommandBuffer v;};
#define R_VK_DeclStackNils \
struct\
{\
R_VK_CmdNode cmd_nil_stack_top;\
}
#define R_VK_InitStackNils(state) \
state->cmd_nil_stack_top.v = 0;\

#define R_VK_DeclStacks \
struct\
{\
struct { R_VK_CmdNode *top; VkCommandBuffer bottom_val; R_VK_CmdNode *free; B32 auto_pop; } cmd_stack;\
}
#define R_VK_InitStacks(state) \
state->cmd_stack.top = &state->cmd_nil_stack_top; state->cmd_stack.bottom_val = 0; state->cmd_stack.free = 0; state->cmd_stack.auto_pop = 0;\

#define R_VK_AutoPopStacks(state) \
if(state->cmd_stack.auto_pop) { r_vk_pop_cmd(); state->cmd_stack.auto_pop = 0; }\

internal VkCommandBuffer            r_vk_top_cmd(void);
internal VkCommandBuffer            r_vk_bottom_cmd(void);
internal VkCommandBuffer            r_vk_push_cmd(VkCommandBuffer v);
internal VkCommandBuffer            r_vk_pop_cmd(void);
internal VkCommandBuffer            r_vk_set_next_cmd(VkCommandBuffer v);
#endif // RENDER_VULKAN_META_H
