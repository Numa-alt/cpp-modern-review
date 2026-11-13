#pragma once

#include <fstream>

#include "DeviceEvent.h"

void WriteCurrentTime(std::ostream& ofs);

void WriteDeviceEvent(const DeviceEvent& deviceEvent, std::ostream& ofs);
