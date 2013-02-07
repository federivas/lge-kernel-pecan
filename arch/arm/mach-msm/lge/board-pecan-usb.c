/* arch/arm/mach-msm/lge/board-pecan-usb.c
 * Copyright (C) 2013 PecanCM, Org.
 * Copyright (c) 20010 LGE. Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include <linux/init.h>
#include <linux/platform_device.h>

#include <mach/board.h>
#include <mach/msm_iomap.h>
#include <mach/msm_hsusb.h>

#ifdef CONFIG_USB_FUNCTION
#include <linux/usb/mass_storage_function.h>
#endif
#ifdef CONFIG_USB_G_ANDROID
#include <linux/usb/android_composite.h>
#endif
#ifdef CONFIG_USB_ANDROID_ACCESSORY
#include <linux/usb/f_accessory.h>
#endif

#include <mach/board_lge.h>
#include <mach/gpio.h>

#include "devices.h"
#include "board-pecan.h"
#include "pm.h"


#ifdef CONFIG_USB_G_ANDROID

/* The binding list for LGE Android USB */
char *usb_functions_lge_all[] = {
#ifdef CONFIG_USB_ANDROID_MTP
	"mtp",
#endif
#ifdef CONFIG_USB_ANDROID_RNDIS
	"rndis",
#endif
#ifdef CONFIG_USB_ANDROID_ACM
	"acm",
#endif
#ifdef CONFIG_USB_ANDROID_DIAG
	"diag",
#endif
#ifdef CONFIG_USB_ANDROID_CDC_ECM
	"ecm",
	"acm2",
#endif
#ifdef CONFIG_USB_F_SERIAL
	"nmea",
#endif
#ifdef CONFIG_USB_SUPPORT_LGE_ANDROID_AUTORUN
	"usb_cdrom_storage",
	"charge_only",
#endif
	"usb_mass_storage",
	"adb",
};


/* LG Android Platform */
char *usb_functions_lge_android_plat[] = {
	"acm", "diag", "nmea", "usb_mass_storage",
};

char *usb_functions_lge_android_plat_adb[] = {
	"acm", "diag", "nmea", "usb_mass_storage", "adb",
};

#ifdef CONFIG_USB_ANDROID_CDC_ECM
/* LG AndroidNet */
char *usb_functions_lge_android_net[] = {
	"diag", "ecm", "acm2", "nmea", "usb_mass_storage",
};

char *usb_functions_lge_android_net_adb[] = {
	"diag", "ecm", "acm2", "nmea", "usb_mass_storage", "adb",
};
#endif

#ifdef CONFIG_USB_ANDROID_RNDIS
/* LG AndroidNet RNDIS ver */
char *usb_functions_lge_android_rndis[] = {
	"rndis",
};

char *usb_functions_lge_android_rndis_adb[] = {
	"rndis", "adb",
};
#endif

#ifdef CONFIG_USB_ANDROID_MTP
/* LG AndroidNet MTP (in future use) */
char *usb_functions_lge_android_mtp[] = {
	"mtp",
};

char *usb_functions_lge_android_mtp_adb[] = {
	"mtp", "adb",
};
#endif

/* LG Manufacturing mode */
char *usb_functions_lge_manufacturing[] = {
	"acm", "diag",
};

/* Mass storage only mode */
char *usb_functions_lge_mass_storage_only[] = {
	"usb_mass_storage",
};

#ifdef CONFIG_USB_SUPPORT_LGE_ANDROID_AUTORUN
/* CDROM storage only mode(Autorun default mode) */
char *usb_functions_lge_cdrom_storage_only[] = {
	"usb_cdrom_storage",
};

char *usb_functions_lge_cdrom_storage_adb[] = {
	"usb_cdrom_storage", "adb",
};

char *usb_functions_lge_charge_only[] = {
	"charge_only",
};
#endif

/* QCT original's composition array is existed in device_lge.c */
struct android_usb_product usb_products[] = {
	{
		.product_id = 0x618E,
		.num_functions = ARRAY_SIZE(usb_functions_lge_android_plat),
		.functions = usb_functions_lge_android_plat,
	},
	{
		.product_id = 0x618E,
		.num_functions = ARRAY_SIZE(usb_functions_lge_android_plat_adb),
		.functions = usb_functions_lge_android_plat_adb,
	},
#ifdef CONFIG_USB_ANDROID_CDC_ECM
	{
		.product_id = 0x61A2,
		.num_functions = ARRAY_SIZE(usb_functions_lge_android_net),
		.functions = usb_functions_lge_android_net,
	},
	{
		.product_id = 0x61A1,
		.num_functions = ARRAY_SIZE(usb_functions_lge_android_net_adb),
		.functions = usb_functions_lge_android_net_adb,
	},
#endif
#ifdef CONFIG_USB_ANDROID_RNDIS
	{
		.product_id = 0x61DA,
		.num_functions  = ARRAY_SIZE(usb_functions_lge_android_rndis),
		.functions  = usb_functions_lge_android_rndis,
	},
	{
		.product_id = 0x61D9,
		.num_functions  = ARRAY_SIZE(usb_functions_lge_android_rndis_adb),
		.functions  = usb_functions_lge_android_rndis_adb,
	},
#endif
#ifdef CONFIG_USB_ANDROID_MTP
	/* FIXME: These pids are experimental.
	 * Don't use them in official version.
	 */
	{
		.product_id = 0x61C7,
		.num_functions = ARRAY_SIZE(usb_functions_lge_android_mtp),
		.functions = usb_functions_lge_android_mtp,
	},
	{
		.product_id = 0x61F9,
		.num_functions = ARRAY_SIZE(usb_functions_lge_android_mtp_adb),
		.functions = usb_functions_lge_android_mtp_adb,
	},
#endif
	{
		.product_id = 0x6000,
		.num_functions  = ARRAY_SIZE(usb_functions_lge_manufacturing),
		.functions  = usb_functions_lge_manufacturing,
	},
	{
		.product_id = 0x61C5,
		.num_functions = ARRAY_SIZE(usb_functions_lge_mass_storage_only),
		.functions = usb_functions_lge_mass_storage_only,
	},
#ifdef CONFIG_USB_SUPPORT_LGE_ANDROID_AUTORUN
	{
		/* FIXME: This pid is just for test */
		.product_id = 0x91C8,
		.num_functions = ARRAY_SIZE(usb_functions_lge_cdrom_storage_only),
		.functions = usb_functions_lge_cdrom_storage_only,
	},
	{
		.product_id = 0x61A6,
		.num_functions = ARRAY_SIZE(usb_functions_lge_cdrom_storage_adb),
		.functions = usb_functions_lge_cdrom_storage_adb,
	},
	{
		/* Charge only doesn't have no specific pid */
		.product_id = 0xFFFF,
		.num_functions = ARRAY_SIZE(usb_functions_lge_charge_only),
		.functions = usb_functions_lge_charge_only,
	},
#endif
};

struct usb_mass_storage_platform_data mass_storage_pdata = {
	.nluns      = 1,
	.vendor     = "LGE",
	.product    = "Android Platform",
	.release    = 0x0100,
};

struct platform_device usb_mass_storage_device = {
	.name   = "usb_mass_storage",
	.id 	= -1,
	.dev    = {
		.platform_data = &mass_storage_pdata,
	},
};

struct usb_ether_platform_data rndis_pdata = {
	/* ethaddr is filled by board_serialno_setup */
	.vendorID   	= 0x1004,
	.vendorDescr    = "LG Electronics Inc.",
};

struct platform_device rndis_device = {
	.name   = "rndis",
	.id 	= -1,
	.dev    = {
		.platform_data = &rndis_pdata,
	},
};


#ifdef CONFIG_USB_ANDROID_CDC_ECM
/* LGE_CHANGE
 * To bind LG AndroidNet, add platform data for CDC ECM.
 * 2011-01-12, hyunhui.park@lge.com
 */
struct usb_ether_platform_data ecm_pdata = {
	/* ethaddr is filled by board_serialno_setup */
	.vendorID   	= 0x1004,
	.vendorDescr    = "LG Electronics Inc.",
};

struct platform_device ecm_device = {
	.name   = "ecm",
	.id 	= -1,
	.dev    = {
		.platform_data = &ecm_pdata,
	},
};
#endif

#ifdef CONFIG_USB_ANDROID_ACM
/* LGE_CHANGE
 * To bind LG AndroidNet, add platform data for CDC ACM.
 * 2011-01-12, hyunhui.park@lge.com
 */
struct acm_platform_data acm_pdata = {
	.num_inst	    = 1,
};

struct platform_device acm_device = {
	.name   = "acm",
	.id 	= -1,
	.dev    = {
		.platform_data = &acm_pdata,
	},
};
#endif

#ifdef CONFIG_USB_SUPPORT_LGE_ANDROID_AUTORUN
/* LGE_CHANGE
 * Add platform data and device for cdrom storage function.
 * It will be used in Autorun feature.
 * 2011-03-02, hyunhui.park@lge.com
 */
struct usb_cdrom_storage_platform_data cdrom_storage_pdata = {
	.nluns      = 1,
	.vendor     = "LGE",
	.product    = "Android Platform",
	.release    = 0x0100,
};

struct platform_device usb_cdrom_storage_device = {
	.name   = "usb_cdrom_storage",
	.id = -1,
	.dev    = {
		.platform_data = &cdrom_storage_pdata,
	},
};
#endif

struct android_usb_platform_data android_usb_pdata = {
	.vendor_id  = 0x1004,
	.product_id = 0x618E,
	.version    = 0x0100,
	.product_name       = "LGE Android Phone",
	.manufacturer_name  = "LG Electronics Inc.",
	.num_products = ARRAY_SIZE(usb_products),
	.products = usb_products,
	.num_functions = ARRAY_SIZE(usb_functions_lge_all),
	.functions = usb_functions_lge_all,
	.serial_number = "LG_ANDROID_P350_GB_",
};

static int __init board_serialno_setup(char *serialno)
{
	int i;
	char *src = serialno;

	/* create a fake MAC address from our serial number.
	 * first byte is 0x02 to signify locally administered.
	 */
	rndis_pdata.ethaddr[0] = 0x02;
	for (i = 0; *src; i++) {
		/* XOR the USB serial across the remaining bytes */
		rndis_pdata.ethaddr[i % (ETH_ALEN - 1) + 1] ^= *src++;
	}

	android_usb_pdata.serial_number = serialno;
	return 1;
}
__setup("androidboot.serialno=", board_serialno_setup);


#endif /* CONFIG_USB_G_ANDROID */


static void __init msm7x2x_init(void)
{

msm_add_usb_devices();

}
