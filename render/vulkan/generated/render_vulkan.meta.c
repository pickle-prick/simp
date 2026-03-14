// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

//- GENERATED CODE

#if 1
#define R_VK_Cmd_Scope(v) DeferLoop(r_vk_push_cmd(v), r_vk_pop_cmd())
#endif
internal VkCommandBuffer r_vk_top_cmd(void) { R_VK_StackTopImpl(r_vk_state, Cmd, cmd) }
internal VkCommandBuffer r_vk_bottom_cmd(void) { R_VK_StackBottomImpl(r_vk_state, Cmd, cmd) }
internal VkCommandBuffer r_vk_push_cmd(VkCommandBuffer v) { R_VK_StackPushImpl(r_vk_state, Cmd, cmd, VkCommandBuffer, v) }
internal VkCommandBuffer r_vk_pop_cmd(void) { R_VK_StackPopImpl(r_vk_state, Cmd, cmd) }
internal VkCommandBuffer r_vk_set_next_cmd(VkCommandBuffer v) { R_VK_StackSetNextImpl(r_vk_state, Cmd, cmd, VkCommandBuffer, v) }
