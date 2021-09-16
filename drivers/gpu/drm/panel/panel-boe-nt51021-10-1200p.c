// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2021
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct boe_nt51021_10_1200p {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data supplies[2];
	struct gpio_desc *reset_gpio;
	struct gpio_desc *backlight_gpio;
	bool prepared;
};

static inline
struct boe_nt51021_10_1200p *to_boe_nt51021_10_1200p(struct drm_panel *panel)
{
	return container_of(panel, struct boe_nt51021_10_1200p, panel);
}

#define dsi_dcs_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_dcs_write_buffer(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void boe_nt51021_10_1200p_reset(struct boe_nt51021_10_1200p *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(30);
}

static int boe_nt51021_10_1200p_on(struct boe_nt51021_10_1200p *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_dcs_write_seq(dsi, 0x83, 0x00);
	dsi_dcs_write_seq(dsi, 0x84, 0x00);
	dsi_dcs_write_seq(dsi, 0x8c, 0x80);
	dsi_dcs_write_seq(dsi, 0xcd, 0x6c);
	dsi_dcs_write_seq(dsi, 0xc8, 0xfc);
	dsi_dcs_write_seq(dsi, 0x9f, 0x00);
	dsi_dcs_write_seq(dsi, 0x97, 0x00);
	dsi_dcs_write_seq(dsi, 0x83, 0xbb);
	dsi_dcs_write_seq(dsi, 0x84, 0x22);
	dsi_dcs_write_seq(dsi, 0x96, 0x00);
	dsi_dcs_write_seq(dsi, 0x90, 0xc0);
	dsi_dcs_write_seq(dsi, 0x91, 0xa0);
	dsi_dcs_write_seq(dsi, 0x9a, 0x10);
	dsi_dcs_write_seq(dsi, 0x94, 0x78);
	dsi_dcs_write_seq(dsi, 0x95, 0xb1);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_DDB_START, 0xff);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_PPS_START, 0xfa);
	dsi_dcs_write_seq(dsi, 0xa3, 0xf3);
	dsi_dcs_write_seq(dsi, 0xa4, 0xed);
	dsi_dcs_write_seq(dsi, 0xa5, 0xe7);
	dsi_dcs_write_seq(dsi, 0xa6, 0xe2);
	dsi_dcs_write_seq(dsi, 0xa7, 0xdc);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_DDB_CONTINUE, 0xd7);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_PPS_CONTINUE, 0xd1);
	dsi_dcs_write_seq(dsi, 0xaa, 0xcc);
	dsi_dcs_write_seq(dsi, 0xb4, 0x1c);
	dsi_dcs_write_seq(dsi, 0xb5, 0x38);
	dsi_dcs_write_seq(dsi, 0xb6, 0x30);
	dsi_dcs_write_seq(dsi, 0x83, 0xaa);
	dsi_dcs_write_seq(dsi, 0x84, 0x11);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_PPS_CONTINUE, 0x4b);
	dsi_dcs_write_seq(dsi, 0x85, 0x04);
	dsi_dcs_write_seq(dsi, 0x86, 0x08);
	dsi_dcs_write_seq(dsi, 0x9c, 0x10);
	dsi_dcs_write_seq(dsi, 0x83, 0x00);
	dsi_dcs_write_seq(dsi, 0x84, 0x00);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}

	return 0;
}

static int boe_nt51021_10_1200p_off(struct boe_nt51021_10_1200p *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	dsi_dcs_write_seq(dsi, 0x10, 0x00);
	msleep(100);

	return 0;
}

static int boe_nt51021_10_1200p_prepare(struct drm_panel *panel)
{
	struct boe_nt51021_10_1200p *ctx = to_boe_nt51021_10_1200p(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	boe_nt51021_10_1200p_reset(ctx);

	ret = boe_nt51021_10_1200p_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int boe_nt51021_10_1200p_unprepare(struct drm_panel *panel)
{
	struct boe_nt51021_10_1200p *ctx = to_boe_nt51021_10_1200p(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = boe_nt51021_10_1200p_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode boe_nt51021_10_1200p_mode = {
	.clock = (1200 + 64 + 4 + 36) * (1920 + 104 + 2 + 24) * 60 / 1000,
	.hdisplay = 1200,
	.hsync_start = 1200 + 64,
	.hsync_end = 1200 + 64 + 4,
	.htotal = 1200 + 64 + 4 + 36,
	.vdisplay = 1920,
	.vsync_start = 1920 + 104,
	.vsync_end = 1920 + 104 + 2,
	.vtotal = 1920 + 104 + 2 + 24,
	.width_mm = 135,
	.height_mm = 217,
};

static int boe_nt51021_10_1200p_get_modes(struct drm_panel *panel,
					  struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &boe_nt51021_10_1200p_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs boe_nt51021_10_1200p_panel_funcs = {
	.prepare = boe_nt51021_10_1200p_prepare,
	.unprepare = boe_nt51021_10_1200p_unprepare,
	.get_modes = boe_nt51021_10_1200p_get_modes,
};

static int boe_nt51021_10_1200p_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	struct boe_nt51021_10_1200p *ctx = mipi_dsi_get_drvdata(dsi);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	gpiod_set_value_cansleep(ctx->backlight_gpio, !!brightness);

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int boe_nt51021_10_1200p_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness & 0xff;
}

static const struct backlight_ops boe_nt51021_10_1200p_bl_ops = {
	.update_status = boe_nt51021_10_1200p_bl_update_status,
	.get_brightness = boe_nt51021_10_1200p_bl_get_brightness,
};

static struct backlight_device *
boe_nt51021_10_1200p_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 255,
		.max_brightness = 255,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &boe_nt51021_10_1200p_bl_ops, &props);
}

static int boe_nt51021_10_1200p_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct boe_nt51021_10_1200p *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->supplies[0].supply = "vsp";
	ctx->supplies[1].supply = "vsn";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		return dev_err_probe(dev, ret, "Failed to get regulators\n");

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->backlight_gpio = devm_gpiod_get(dev, "backlight", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->backlight_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->backlight_gpio),
				     "Failed to get backlight-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		      MIPI_DSI_MODE_LPM,

	drm_panel_init(&ctx->panel, dev, &boe_nt51021_10_1200p_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->panel.backlight = boe_nt51021_10_1200p_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static int boe_nt51021_10_1200p_remove(struct mipi_dsi_device *dsi)
{
	struct boe_nt51021_10_1200p *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);

	return 0;
}

static const struct of_device_id boe_nt51021_10_1200p_of_match[] = {
	{ .compatible = "boe,nt51021-10-1200p" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, boe_nt51021_10_1200p_of_match);

static struct mipi_dsi_driver boe_nt51021_10_1200p_driver = {
	.probe = boe_nt51021_10_1200p_probe,
	.remove = boe_nt51021_10_1200p_remove,
	.driver = {
		.name = "panel-boe-nt51021-10-1200p",
		.of_match_table = boe_nt51021_10_1200p_of_match,
	},
};
module_mipi_dsi_driver(boe_nt51021_10_1200p_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>");
MODULE_DESCRIPTION("DRM driver for BOE_NT51021_10_1200P_VIDEO");
MODULE_LICENSE("GPL v2");
