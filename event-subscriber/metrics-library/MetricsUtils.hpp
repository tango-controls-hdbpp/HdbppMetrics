/* Copyright (C) : 2014-2019
   European Synchrotron Radiation Facility
   BP 220, Grenoble 38043, FRANCE

   This file is part of hdb++metrics

   hdb++metrics is free software: you can redistribute it and/or modify
   it under the terms of the Lesser GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   hdb++metrics is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser
   GNU General Public License for more details.

   You should have received a copy of the Lesser GNU General Public License
   along with hdb++metrics.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include <chrono>
#include <time.h>

namespace hdbpp_metrics
{
// Collection of utility functions for the metrics library
class MetricsUtils
{
public:

    static uint64_t nowInMiliSec()
    {
        auto duration =  std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    static uint64_t nowInMicroSec()
    {
        auto duration =  std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    static uint64_t nowInNanoSec()
    {
        auto duration =  std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    static uint64_t timevalToMiliSec(time_t tv_sec, long tv_usec)
    {
        return tv_sec * 1000 + static_cast<uint64_t>(tv_usec) / 1000;
    }

    static uint64_t timevalToMicroSec(time_t tv_sec, long tv_usec)
    {
        return tv_sec * 1000000 + tv_usec;
    }
};

} // namespace hdbpp_metrics