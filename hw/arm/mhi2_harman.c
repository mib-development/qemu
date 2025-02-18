#include "qemu/osdep.h"
#include "qemu/units.h"
#include "exec/address-spaces.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "hw/boards.h"
#include "hw/qdev-properties.h"
#include "hw/arm/tegra30.h"
#include "hw/arm/boot.h"

static struct arm_boot_info mhi2_harman_binfo;

static void mhi2_harman_init(MachineState *machine)
{
    Tegra30State *soc;

    info_report("Initializing MHI2 Harman");

    soc = TEGRA30(object_new(TYPE_TEGRA30));
    object_property_add_child(OBJECT(machine), "soc", OBJECT(soc));
    
    // TODO: SoC setup

    // TODO: Move emem init to tegra30.c
    memory_region_init_ram(&soc->emem, OBJECT(soc), "emem", machine->ram_size, &error_fatal);
    memory_region_add_subregion(get_system_memory(), 0x80000000, &soc->emem);

    sysbus_realize_and_unref(SYS_BUS_DEVICE(soc), &error_fatal);

    uint8_t *nor;
    size_t nor_size;
    if (!g_file_get_contents("/home/iscle/Documents/mib/mmx_fs0_k2589", (gchar **) &nor, (gsize *) &nor_size, NULL)) {
        error_report("Failed to load nor");
        exit(1);
    }

    memory_region_init_ram(&soc->nor_flash, OBJECT(soc), "nor-flash", nor_size, &error_fatal);
    memory_region_add_subregion(get_system_memory(), 0x48000000, &soc->nor_flash);

    AddressSpace *nsas = cpu_get_address_space(CPU(&soc->cpus[0]), ARMASIdx_NS);
    address_space_write(nsas, 0x48000000, MEMTXATTRS_UNSPECIFIED, nor, nor_size);
    address_space_write(nsas, 0x83F28000, MEMTXATTRS_UNSPECIFIED, nor, nor_size);

    cpu_set_pc(CPU(&soc->cpus[0]), 0x48000000 + 0xe0000);
}

static void mhi2_harman_machine_init(MachineClass *mc)
{
    static const char * const valid_cpu_types[] = {
        ARM_CPU_TYPE_NAME("cortex-a9"),
        NULL
    };

    mc->desc = "MHI2 Harman";
    mc->init = mhi2_harman_init;
    mc->block_default_type = IF_SD;
    mc->units_per_default_bus = 1;
    mc->min_cpus = TEGRA30_NUM_CPUS;
    mc->max_cpus = TEGRA30_NUM_CPUS;
    mc->default_cpus = TEGRA30_NUM_CPUS;
    mc->default_cpu_type = ARM_CPU_TYPE_NAME("cortex-a9");
    mc->valid_cpu_types = valid_cpu_types;
    mc->default_ram_size = 4 * GiB;
    mc->default_ram_id = "mhi2-harman.ram";
}

DEFINE_MACHINE("mhi2-harman", mhi2_harman_machine_init)
