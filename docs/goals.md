# Metrics Collaboration

- [Metrics Collaboration](#Metrics-Collaboration)
  - [Overview](#Overview)
  - [HDB++ Metrics](#HDB-Metrics)
    - [Attributes Limits Per Subscriber](#Attributes-Limits-Per-Subscriber)
    - [Event Throughput](#Event-Throughput)
    - [Event Time (Per Attribute Type)](#Event-Time-Per-Attribute-Type)
    - [Database Comparison](#Database-Comparison)
    - [Maximum Total Events](#Maximum-Total-Events)

## Overview

The purpose of this document is to outline some possible metrics collaboration work. The intention is for the document to develop as the work does. This is currently a work in progress.

## HDB++ Metrics

Below is the start of some possible metrics to cover. Mainly interested in data events at this point.

### Attributes Limits Per Subscriber

A test to discover if there is a maximum number of attributes that an Event Subscriber can support.

To be expanded as the idea is developed.

### Event Throughput

A means to measure the total throughput for a given set of events on a given hardware platform.

To be expanded as the idea is developed.

### Event Time (Per Attribute Type)

Break down the total time to store an event between time spent in the Event Subscriber, and time spent in the back-end library. Useful for comparing different shared library back ends, different attribute types and storage latency.

The intention is to record a time at three points in the Event Subscriber:

- Event received time
- Before passing the event to the shared library
- After returning from the shared library.

To be expanded as the idea is developed.

### Database Comparison

Compare the currently supported databases. This would help to optimise the shared libraries to increase performance.

### Maximum Total Events

Total events the system can handle. Hard to measure, but interesting for truly large deployments of Tango. Likely to be dependent on the database back-end hardware.

To be expanded as the idea is developed.
