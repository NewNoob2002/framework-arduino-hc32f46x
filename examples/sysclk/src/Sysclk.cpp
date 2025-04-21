#include "Sysclk.h"

void core_hook_sysclock_init()
{
    // 1. 配置Flash等待周期，使其适用于高频运行
    sysclock_configure_flash_wait_cycles();
    
    // 2. 配置并启用XTAL高速晶振
    sysclock_configure_xtal();
    
    // 3. 配置MPLL，使用XTAL作为输入源
    // PLL输出时钟计算: ((clock_source / M) * N) / [P|Q|R]
    // M是预分频器，N是预乘器，[P|Q|R]是通道分频器
    stc_clk_mpll_cfg_t mpllConfig = {
        .PllpDiv = 2,   // P分频 = 2
        .PllqDiv = 2,   // Q分频 = 2 (用于其他外设)
        .PllrDiv = 2,   // R分频 = 2 (用于其他外设)
        .plln = 50,     // N = 50 (倍频)
        .pllmDiv = 1,   // M = 1 (分频)
    };
    
    // 配置MPLL，使用XTAL作为时钟源，并应用上述配置
    sysclock_configure_mpll(ClkPllSrcXTAL, &mpllConfig);
    
    // 4. 配置系统时钟分频器
    stc_clk_sysclk_cfg_t sysClkConfig = {
        .enHclkDiv = ClkSysclkDiv1,    // HCLK = SYSCLK / 1 = 200MHz
        .enExclkDiv = ClkSysclkDiv2,   // EXCLK = SYSCLK / 2 = 100MHz (最大值为100MHz)
        .enPclk0Div = ClkSysclkDiv1,   // PCLK0 = SYSCLK / 1 = 200MHz
        .enPclk1Div = ClkSysclkDiv2,   // PCLK1 = SYSCLK / 2 = 100MHz (最大值为100MHz)
        .enPclk2Div = ClkSysclkDiv4,   // PCLK2 = SYSCLK / 4 = 50MHz (最大值为60MHz)
        .enPclk3Div = ClkSysclkDiv4,   // PCLK3 = SYSCLK / 4 = 50MHz (最大值为50MHz)
        .enPclk4Div = ClkSysclkDiv2,   // PCLK4 = SYSCLK / 2 = 100MHz (最大值为100MHz)
    };
    sysclock_set_clock_dividers(&sysClkConfig);
    
    // 5. 更新性能模式到最高性能
    power_mode_update_pre(200000000);
    
    // 6. 切换系统时钟源到MPLL
    CLK_SetSysClkSource(CLKSysSrcMPLL);
    
    // 7. 更新性能模式
    power_mode_update_post(200000000);
    
    // 更新系统时钟频率变量
    update_system_clock_frequencies();
} 
