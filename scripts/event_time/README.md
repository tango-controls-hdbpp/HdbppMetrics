# Event Time

This script extracts the event times from the logs generated by an instrumented event subscriber. 

The script assumes the received.log is in csv format, with no header, and the following columns

- event (name as given in the metrics library, here we filter and use only DATA_EVENT)
- id_token (event time in microseconds)
- received_time (when received by the event subscriber)
- event_time (when raised in the device class)
- name (full attribute name)
- quality
- type (attribute)
- format (attribute)
- write_type (attribute)

The script also assumes the db_insertion.log is in csv format, with no headers and the following columns:

- event (filter and use only BEFORE_STORE_DATA_EVENT and AFTER_STORE_DATA_EVENT)
- id_token (event time in microseconds)
- event_time (time event was recorded in the event subscriber)

After the script is run, a dump.csv is created with the following data:

- id_token
- total time (in nanoseconds)
- event subscriber time (in nanoseconds)
- insert time (in nanoseconds)

This data can then be graphed. Some experimental graphing has been tested in event_breakdown_graph.py using plotly.