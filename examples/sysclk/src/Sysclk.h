#pragma once

#include <Arduino.h>
#include "../drivers/sysclock/sysclock.h"
#include "../drivers/sysclock/sysclock_util.h"
#include "../core_hooks.h"


/**
 * @brief core_hook_sysclock_init实现
 * 
 * 此函数将系统时钟配置为使用外部XTAL晶振，并通过MPLL将其频率提升到200MHz
 * 
 * 配置过程:
 * 1. 配置Flash/SRAM等待周期，适用于高频
 * 2. 启用XTAL高速晶振
 * 3. 配置并启用MPLL，使用XTAL作为输入源
 * 4. 配置系统时钟分频器
 * 5. 更新性能模式
 * 6. 切换系统时钟源到MPLL
 * 7. 更新性能模式
 * 
 * 默认XTAL为8MHz
 * 目标频率为200MHz，计算方法：((XTAL / M) * N) / P = 200MHz
 * 设置：M=1, N=50, P=2，则 ((8 / 1) * 50) / 2 = 200MHz
 */
void core_hook_sysclock_init();

