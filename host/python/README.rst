=====================
arduino_olfactometer
=====================

arduino_olfactometer is a python package to control the Arduino
olfactometer over USB, using the python module, the command line, a
GUI, or a webpage using a webserver.


Install
-------

See INSTALL.txt

Python Module
-------------

Typical usage often looks like this::

    from arduino_olfactometer import ArduinoOlfactometer, ArduinoOlfactometers

    olfactometers = ArduinoOlfactometers()
    device_count = len(olfactometers)
    if device_count == 0:
        raise RuntimeError('No Arduino olfactometers detected, check connections.')
    valve_count = olfactometers[0].valve_count
    mfc_count = olfactometers[0].mfc_count

    o = ArduinoOlfactometers[0]
    o.setMfcFlowRate(mfc=1,percent_capacity=75)
    print o.getMfcFlowRateSetting(mfc=1)
    print o.getMfcFlowRateMeasure(mfc=0)
    o.setOdorValveOn(valve=4)
    o.setOdorValvesOff()

Author: Peter Polidoro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
