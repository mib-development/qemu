#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "qemu/module.h"
#include "qemu/units.h"
#include "hw/qdev-core.h"
#include "hw/sysbus.h"
#include "hw/char/serial-mm.h"
#include "hw/misc/unimp.h"
#include "hw/usb/hcd-ehci.h"
#include "hw/loader.h"
#include "sysemu/sysemu.h"
#include "hw/arm/tegra30.h"

static void tegra30_init(Object *obj)
{
    Tegra30State *s = TEGRA30(obj);

    info_report("Tegra 3 initialization: s=%p", s);

    for (int i = 0; i < TEGRA30_NUM_CPUS; i++) {
        object_initialize_child(obj, "cpu[*]", &s->cpus[i],
                                ARM_CPU_TYPE_NAME("cortex-a9"));
    }

    object_initialize_child(obj, "apb-misc", &s->apb_misc,
                            TYPE_TEGRA30_APB_MISC);

    object_initialize_child(obj, "clk", &s->clk, TYPE_TEGRA30_CLK);

    object_initialize_child(obj, "pmc", &s->pmc, TYPE_TEGRA30_PMC);

    info_report("Tegra 3 CPUs initialized");
}

static void tegra30_realize(DeviceState *dev, Error **errp)
{
    Tegra30State *s = TEGRA30(dev);

    info_report("Realizing Tegra 3");

    for (int i = 0; i < TEGRA30_NUM_CPUS; i++) {
        /*
         * Disable secondary CPUs. Guest EL3 firmware will start
         * them via CPU reset control registers.
         */
        qdev_prop_set_bit(DEVICE(&s->cpus[i]), "start-powered-off",
                          i > 0);

        qdev_realize(DEVICE(&s->cpus[i]), NULL, &error_fatal);
    }

    /* APB misc */
    sysbus_realize(SYS_BUS_DEVICE(&s->apb_misc), &error_fatal);
    sysbus_mmio_map(SYS_BUS_DEVICE(&s->apb_misc), 0, 0x70003000);

    /* Clock */
    sysbus_realize(SYS_BUS_DEVICE(&s->clk), &error_fatal);
    sysbus_mmio_map(SYS_BUS_DEVICE(&s->clk), 0, 0x60006000);

    /* PMC */
    sysbus_realize(SYS_BUS_DEVICE(&s->pmc), &error_fatal);
    sysbus_mmio_map(SYS_BUS_DEVICE(&s->pmc), 0, 0x7000E400);

    serial_mm_init(get_system_memory(), 0x70006000, 2, 0,
                   115200, serial_hd(0), DEVICE_NATIVE_ENDIAN);
    serial_mm_init(get_system_memory(), 0x70006040, 2, 0,
                   115200, serial_hd(1), DEVICE_NATIVE_ENDIAN);
    serial_mm_init(get_system_memory(), 0x70006200, 2, 0,
                   115200, serial_hd(2), DEVICE_NATIVE_ENDIAN);
    serial_mm_init(get_system_memory(), 0x70006300, 2, 0,
                   115200, serial_hd(3), DEVICE_NATIVE_ENDIAN);

    create_unimplemented_device("unimplemented-memory", 0, 0xFFFFFFFF);

    info_report("Tegra30 realized");
}

static void tegra30_class_init(ObjectClass *oc, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize = tegra30_realize;
}

static const TypeInfo tegra30_type_info = {
    .name = TYPE_TEGRA30,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(Tegra30State),
    .instance_init = tegra30_init,
    .class_init = tegra30_class_init,
};

static void tegra30_register_types(void)
{
    type_register_static(&tegra30_type_info);
}

type_init(tegra30_register_types)
