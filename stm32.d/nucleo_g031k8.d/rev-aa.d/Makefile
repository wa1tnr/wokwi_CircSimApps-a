
#   pio project init --board adafruit_feather_esp32_v2

all:
	pio run

monitor:
	pio run -t monitor

devlist:
	pio device list

nsterm:
	sleep 2; ./cf-fastpico9t /dev/ttyACM0

term:
	sleep 2; ./cf-fastpico9t /dev/ttyACM0

upload:
	pio run -t upload

# install: spiffs upload term

upgrade:
	pio upgrade

platforma:
	# pio pkg update -p espressif32@6.3.1

platforms: platforma


# https://docs.platformio.org/en/latest/core/userguide/pkg/cmd_update.html#cmd-pkg-update

pkgupdate:
	pio pkg update

pkglist:
	pio pkg list

# https://docs.platformio.org/en/latest/core/userguide/pkg/cmd_outdated.html#cmd-pkg-outdated

outdated:
	pio pkg outdated

clean:
	pio run -t clean

distclean: clean
	rm -rf ./.pio
