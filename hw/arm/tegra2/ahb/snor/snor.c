/*
 * ARM NVIDIA Tegra2 emulation.
 *
 * Copyright (c) 2025 Iscle Gil <albertiscle9@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "tegra_common.h"

#include "hw/sysbus.h"
#include "sysemu/block-backend.h"
#include "hw/block/block.h"
#include "hw/block/flash.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"

#include "snor.h"
#include "iomap.h"
#include "tegra_trace.h"

#define TYPE_TEGRA_SNOR "tegra.snor"
#define TEGRA_SNOR(obj) OBJECT_CHECK(tegra_snor, (obj), TYPE_TEGRA_SNOR)

typedef struct tegra_snor_state {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    BlockBackend *blk;
    int64_t length;
    uint8_t *storage;
} tegra_snor;

static Property snor_properties[] = {
    DEFINE_PROP_DRIVE("drive", tegra_snor, blk),
    DEFINE_PROP_END_OF_LIST(),
};

static const VMStateDescription vmstate_tegra_snor = {
    .name = "tegra.snor",
    .version_id = 1,
    .fields = (VMStateField[]) {
        // VMSTATE_UINT32(snor_config.reg32, tegra_snor),
        VMSTATE_END_OF_LIST()
    }
};

static uint64_t tegra_snor_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    tegra_snor *s = opaque;
    uint64_t ret = 0;

    if (offset < s->length) {
        ret = s->storage[offset];
    } else {
        printf("tegra.snor: read from invalid offset 0x%" HWADDR_PRIx "\n", offset);
    }
    
    TRACE_READ(s->iomem.addr, offset, ret);

    return ret;
}

static void tegra_snor_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    tegra_snor *s = opaque;

    if (offset < s->length) {
        TRACE_WRITE(s->iomem.addr, offset, s->storage[offset], value);
        s->storage[offset] = value;
    } else {
        TRACE_WRITE(s->iomem.addr, offset, 0, value);
        printf("tegra.snor: write to invalid offset 0x%" HWADDR_PRIx "\n", offset);
    }
}

static const MemoryRegionOps tegra_snor_mem_ops = {
    .read = tegra_snor_read,
    .write = tegra_snor_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void tegra_snor_realize(DeviceState *dev, Error **errp)
{
    tegra_snor *s = TEGRA_SNOR(dev);

    memory_region_init_io(&s->iomem, OBJECT(dev), &tegra_snor_mem_ops, s,
                          "tegra.snor", TEGRA_NOR_FLASH_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(dev), &s->iomem);

    if (s->blk) {
        s->length = blk_getlength(s->blk);
        if (s->length < 0) {
            // error_setg_errno(errp, -s->length,
            //                  "can't get size of %s block backend",
            //                  blk_name(s->blk));
            printf("tegra.snor: can't get size of %s block backend\n", blk_name(s->blk));
            return;
        }
        if (s->length > TEGRA_NOR_FLASH_SIZE) {
            // error_setg(errp, "block backend size %" PRId64 " exceeds flash size",
            //            s->length);
            printf("tegra.snor: block backend size %" PRId64 " exceeds flash size\n",
                   s->length);
            return;
        }

        s->storage = blk_blockalign(s->blk, s->length);

        if (!blk_check_size_and_read_all(s->blk, DEVICE(dev),
                                         s->storage, s->length, errp)) {
            // error_setg(errp, "can't read %s block backend for %s device",
            //            blk_name(s->blk), object_get_typename(OBJECT(dev)));
            printf("tegra.snor: can't read %s block backend for %s device\n",
                   blk_name(s->blk), object_get_typename(OBJECT(dev)));
            return;
        }

        printf("tegra.snor: block backend %s, size %" PRId64 "\n",
               blk_name(s->blk), s->length);

        for (int i = 0; i < 0x2c; i++) {
            printf("%02x ", s->storage[i]);
        }
    } else {
        printf("tegra.snor: no drive specified\n");
    }
}

static void tegra_snor_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    device_class_set_props(dc, snor_properties);
    dc->realize = tegra_snor_realize;
    dc->vmsd = &vmstate_tegra_snor;
}

static const TypeInfo tegra_snor_info = {
    .name = TYPE_TEGRA_SNOR,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(tegra_snor),
    .class_init = tegra_snor_class_init,
};

static void tegra_snor_register_types(void)
{
    type_register_static(&tegra_snor_info);
}

type_init(tegra_snor_register_types)
