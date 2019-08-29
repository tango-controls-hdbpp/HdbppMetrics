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

#include <iostream>
#include <memory>
#include <thread>
#include <stdexcept>
#include <atomic>
#include <fstream>
#include <vector>

// lockless queue from moodycamel
#include "blockingconcurrentqueue.h"

namespace hdbpp_metrics
{
// This class is a simple logging mechanism for recording events. The actual
// file logging is performed on a seperate thread to try reduce the load on the 
// main thread (likely being timed)
class EventRecorder
{
public:

    EventRecorder(const std::string &file_name, bool truncate = false) : 
        _log_file_name(file_name),
        _truncate(truncate) { }

    ~EventRecorder() { destroy(); }

    // Init the EventRecorder and internal logging thread
    void init()
    {
        if (!_thread)
        {
            _quit_thread = false;
            _error_thread = false;
            _thread = std::make_unique<std::thread>(&EventRecorder::dataSink,this);
        }
        else
        {
            throw std::logic_error("Timestamp sink thread already started.");
        }
    }

    // Gracefully destroy the recorder
    void destroy()
    {
        if (_thread)
        {
            _quit_thread = true;

            if (_thread->joinable())
                _thread->join();
        }
    }

    // Record an event, the caller can add any basic data fields they wish,
    // as long as they can be converted with a to_string call
    template<typename... ARGS>
    void recordEvent(const std::string &event, const ARGS&... args)
    {
        std::vector<std::string> params;
        stringify(params, args...);

        // put data onto thread
        _data_queue.enqueue(Data{event, params});
    }

    // check for thread errors, mainly on init
    bool inError() const { return _error_thread; }

private:

    // Data passed to the recorder thread
    struct Data
    {
        std::string event;
        std::vector<std::string> params;
    };

    template<typename T, typename... ARGS>
    void stringify(std::vector<std::string> &params, const T &arg, const ARGS&... args)
    {
        params.push_back(toString(arg));
        stringify(params, args...);
    }

    template<typename T>
    void stringify(std::vector<std::string> &params, const T &arg)
    {
        params.push_back(toString(arg));
    }

    void stringify(std::vector<std::string>&)
    { }

    template<typename T>
    std::string toString(const T &arg)
    {
        return std::to_string(arg);
    }

    std::string toString(const std::string &arg)
    {
        return std::string(arg);
    }

    std::string toString(const char *arg)
    {
        return std::string(arg);
    }

    // Handles dumping the event data to a file.
    void dataSink()
    {
        // open the logging file to receieve the data
        std::ofstream log_file;
        log_file.open(_log_file_name, _truncate ? std::ios::trunc : std::ios::app);

        if (!log_file)
        {
            _error_thread = true;
            return;
        }

        Data data;

        while(!_quit_thread)
        {
            // dequeue data from the queue, but wake anyway every 25 ms to check
            // if the class is requesting the thread be closed down
            if (_data_queue.wait_dequeue_timed(data, std::chrono::milliseconds(25)))
            {
                std::string params;

                // add any parameters to the line
                for(auto &item : data.params)
                    params += "," + item;

                // dump and flush to ensure its in the file
                log_file << data.event << params << std::endl;
                log_file.flush();
            }
        }

        log_file.close();
    }

    // threading model
    std::unique_ptr<std::thread> _thread;
    std::atomic<bool> _quit_thread;
    std::atomic<bool> _error_thread;

    // queue to pass data to the thread with
    moodycamel::BlockingConcurrentQueue<Data> _data_queue;

    std::string _log_file_name;
    bool _truncate;
};

} // namespace hdbpp_metrics