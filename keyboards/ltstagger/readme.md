# LTStagger

## Firmware building
After cloning the QMK repo and installing dfu-programmer build and flash with. Be sure to reset your keyboard!

    make ltstagger:default:dfu

To just test your build with the default keymap

    make ltstagger:default

Gadgets and options can be enabled/disabled in keyboards/gergo/keymaps/default/rules.mk . Copy the default directory and make any changes to your layout, if you think they're worth sharing submit a PR!

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Source

Keyboard folder coppied from gergo
