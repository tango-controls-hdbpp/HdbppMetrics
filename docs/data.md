# Data Dumped

This is a short description of the data dumped by the patch. Two logs are created:

## received.log

In csv format and with no header. Two possible row types based on event type:

### DATA_EVENT/ERROR_DATA_EVENT

Has the follow columns:

- event type (DATA_EVENT/ERROR_DATA_EVENT)
- id token (event time in microseconds)
- received time (when received by the event subscriber) (nanoseconds)
- event time (when raised in the device class) (milliseconds)
- name (full qualified attribute name)
- quality (only for DATA_EVENT and ERROR_DATA_EVENT)
- type (attribute)
- format (attribute)
- write_type (attribute)

### PARAM_EVENT

Has the follow columns:

- event type (DATA_EVENT/ERROR_DATA_EVENT)
- id token (event time in microseconds)
- received time (when received by the event subscriber) (nanoseconds)
- event time (when raised in the device class) (milliseconds)
- name (full qualified attribute name)
- type (attribute)
- format (attribute)
- write_type (attribute)

## db_insertion.log 

Is in csv format with the following columns:

- event type: 
  - BEFORE_STORE_DATA_EVENT
  - AFTER_STORE_DATA_EVENT
  - AFTER_STORE_DATA_EVENT_EXCEPTION
  - BEFORE_STORE_PARAM_EVENT
  - AFTER_STORE_PARAM_EVENT
  - AFTER_STORE_PARAM_EVENT_EXCEPTION
- id_token (event time in microseconds)
- event time (time event occurs in event subscriber) (nanoseconds)
- 