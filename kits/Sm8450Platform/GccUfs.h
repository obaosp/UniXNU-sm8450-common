// SPDX-License-Identifier: BSD-2-Clause-Patent
// SM8450 (waipio) GCC registers used by UFS.
//
// Transcribed from the public mainline clock driver:
//   drivers/clk/qcom/gcc-sm8450.c (torvalds/linux)
//
// These are facts, not a driver: no write is performed here. The block is NOT
// a constant offset from SM8550's 0x770xx range, so an SM8550 driver cannot be
// pointed at this SoC. Compare:
//   SM8450 ufs_phy_axi  0x87018    SM8550 0x77018
//   SM8450 ufs_phy_ahb  0x87020    SM8550 0x77024
//   SM8450 phy_aux      0x870a4    SM8550 0x770b0
#ifndef SM8450_GCC_UFS_H
#define SM8450_GCC_UFS_H

// Physical windows: clock-controller@100000, ufshc@1d84000 (sm8450.dtsi).
#define GCC_BASE                      0x00100000ULL
#define UFS_HC_BASE                   0x01d84000ULL
#define UFS_HC_SIZE                   0x3000ULL
#define UFS_PHY_BASE                  0x01d87000ULL

// GDSC: gcc-sm8450.c has a single ufs_phy_gdsc. There is no separate
// UFS_MEM_PHY_GDSC entry as on SM8550, so nothing may program 0x9e000.
#define GCC_UFS_PHY_GDSCR             0x87004

// clk_branch enable/halt registers (clk_branch2_ops, enable bit 0).
#define GCC_UFS_PHY_AXI_ENABLE        0x87018
#define GCC_UFS_PHY_AHB_ENABLE        0x87020
#define GCC_UFS_PHY_TX_SYMBOL0_ENABLE 0x87024
#define GCC_UFS_PHY_RX_SYMBOL0_ENABLE 0x87028
#define GCC_UFS_PHY_UNIPRO_CORE_ENABLE 0x87064
#define GCC_UFS_PHY_ICE_CORE_ENABLE   0x8706c
#define GCC_UFS_PHY_PHY_AUX_ENABLE    0x870a4
#define GCC_UFS_PHY_RX_SYMBOL1_ENABLE 0x870c0
// bus_aggr_clk in DT: gcc_aggre_ufs_phy_axi_clk, halt/enable 0x870d4, hwcg bit 1.
#define GCC_AGGRE_UFS_PHY_AXI_ENABLE  0x870d4

#define GCC_UFS_BRANCH_ENABLE_BIT     0x1U

// Hardware clock gating (hwcg_bit = 1) applies to axi, ahb, unipro_core,
// ice_core, phy_aux and aggre_ufs_phy_axi, so CLK_OFF=1 on an idle branch is
// normal and a probe must check the branch enable and gating together.
// Reset and RPMh/TCSR/QMP-PHY programming are not represented here; their
// semantics are not qualified and must not be written speculatively.
#endif
