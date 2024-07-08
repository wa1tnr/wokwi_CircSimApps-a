#!/bin/sh

echo '    kludge script only - NOT USED.  This directory is setup for platformio.'
echo
echo '        whereas, this script is for arduino-cli only.'
echo ''
echo '    exiting - please see this shell script.'
echo ''

exit 0

CURRENT=src
# uncomment just one of these:
# arduino-cli compile --fqbn arduino:renesas_uno:minima ${CURRENT}
# arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi ${CURRENT}
# end.
