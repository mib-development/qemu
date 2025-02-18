#ifndef HW_ARM_TEGRA30_H
#define HW_ARM_TEGRA30_H

#include "qom/object.h"
#include "hw/intc/arm_gic.h"
#include "target/arm/cpu.h"
#include "sysemu/block-backend.h"
#include "hw/misc/tegra30_apb_misc.h"
#include "hw/misc/tegra30_clk.h"
#include "hw/misc/tegra30_pmc.h"

/** Total number of CPU cores in the Tegra 3 SoC */
#define TEGRA30_NUM_CPUS      (4)

/**
 * nVidia Tegra 3 object model
 * @{
 */

/** Object type for the nVidia Tegra 3 SoC */
#define TYPE_TEGRA30 "tegra30"

/** Convert input object to nVidia Tegra 3 state object */
OBJECT_DECLARE_SIMPLE_TYPE(Tegra30State, TEGRA30)

/** @} */

/**
 * nVidia Tegra 3 object
 *
 * This struct contains the state of all the devices
 * which are currently emulated by the Tegra 3 SoC code.
 */
struct Tegra30State {
    SysBusDevice parent_obj;

    ARMCPU cpus[TEGRA30_NUM_CPUS];
    Tegra30ApbMiscState apb_misc;
    Tegra30ClkState clk;
    Tegra30PmcState pmc;

    MemoryRegion emem;
    MemoryRegion nor_flash;
};

#endif /* HW_ARM_TEGRA30_H */
