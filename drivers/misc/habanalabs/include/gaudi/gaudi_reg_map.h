/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright 2019-2020 HabanaLabs, Ltd.
 * All Rights Reserved.
 *
 */

#ifndef GAUDI_REG_MAP_H_
#define GAUDI_REG_MAP_H_

/*
 * PSOC scratch-pad registers
 */
#define mmHW_STATE			mmPSOC_GLOBAL_CONF_SCRATCHPAD_0
/* TODO: remove mmGIC_HOST_IRQ_CTRL_POLL_REG */
#define mmGIC_HOST_IRQ_CTRL_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_1
#define mmGIC_HOST_PI_UPD_IRQ_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_1
#define mmGIC_TPC_QM_IRQ_CTRL_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_2
#define mmGIC_MME_QM_IRQ_CTRL_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_3
#define mmGIC_DMA_QM_IRQ_CTRL_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_4
#define mmGIC_NIC_QM_IRQ_CTRL_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_5
#define mmGIC_DMA_CR_IRQ_CTRL_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_6
#define mmGIC_HOST_HALT_IRQ_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_7
#define mmGIC_HOST_INTS_IRQ_POLL_REG	mmPSOC_GLOBAL_CONF_SCRATCHPAD_8
#define mmCPU_BOOT_DEV_STS0		mmPSOC_GLOBAL_CONF_SCRATCHPAD_20
#define mmCPU_BOOT_DEV_STS1		mmPSOC_GLOBAL_CONF_SCRATCHPAD_21
#define mmFUSE_VER_OFFSET		mmPSOC_GLOBAL_CONF_SCRATCHPAD_22
#define mmCPU_CMD_STATUS_TO_HOST	mmPSOC_GLOBAL_CONF_SCRATCHPAD_23
#define mmCPU_BOOT_ERR0			mmPSOC_GLOBAL_CONF_SCRATCHPAD_24
#define mmCPU_BOOT_ERR1			mmPSOC_GLOBAL_CONF_SCRATCHPAD_25
#define mmUPD_STS			mmPSOC_GLOBAL_CONF_SCRATCHPAD_26
#define mmUPD_CMD			mmPSOC_GLOBAL_CONF_SCRATCHPAD_27
#define mmPREBOOT_VER_OFFSET		mmPSOC_GLOBAL_CONF_SCRATCHPAD_28
#define mmUBOOT_VER_OFFSET		mmPSOC_GLOBAL_CONF_SCRATCHPAD_29
#define mmRDWR_TEST			mmPSOC_GLOBAL_CONF_SCRATCHPAD_30
#define mmBTL_ID			mmPSOC_GLOBAL_CONF_SCRATCHPAD_31
#define mmPREBOOT_PCIE_EN		mmPSOC_GLOBAL_CONF_COLD_RST_FLOPS_1
#define mmUPD_PENDING_STS		mmPSOC_GLOBAL_CONF_COLD_RST_FLOPS_3

#endif /* GAUDI_REG_MAP_H_ */
