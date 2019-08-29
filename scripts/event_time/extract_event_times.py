#!/usr/bin/env python3

import sys
import csv
import argparse
import collections
import pprint

verbose = False


def load_files(received_log_name, db_insert_log_name):

    # the entire record across all files will be loaded as a dictionary, indexed on the event time in
    # microseconds as the id token
    event_index = collections.OrderedDict()

    with open(received_log_name) as rec_fp, open(db_insert_log_name) as insert_fp:

        rec_reader = csv.DictReader(rec_fp,
                                    fieldnames=("event", "id_token", "received_time", "event_time", "name", "quality", "type", "format", "write_type"),
                                    delimiter=",")

        insert_reader = csv.DictReader(insert_fp,
                                       fieldnames=("event", "id_token", "event_time"),
                                       delimiter=",")

        for record in rec_reader:
            if record["event"] == "DATA_EVENT":
                new_record = {}
                new_record = record

                # if a record is incomplete, then it is possible to check these
                # fields for None
                new_record["before_insert_time"] = None
                new_record["after_insert_time"] = None

                insert_fp.seek(0)

                for insert_record in insert_reader:
                    if insert_record["id_token"] == new_record["id_token"]:
                        if insert_record["event"] == "BEFORE_STORE_DATA_EVENT":
                            new_record["before_insert_time"] = insert_record["event_time"]

                        if insert_record["event"] == "AFTER_STORE_DATA_EVENT":
                            new_record["after_insert_time"] = insert_record["event_time"]

                event_index[new_record["id_token"]] = new_record

    return event_index


def dump_event_time_breakdown(event_index):

    with open("dump.csv", mode='w', newline='') as output_fp:
        writer = csv.writer(output_fp, delimiter=',', quoting=csv.QUOTE_MINIMAL)

        for key, value in event_index.items():
            if value["before_insert_time"] is not None and value["after_insert_time"] is not None:
                total_time = str(int(value["after_insert_time"]) - int(value["received_time"]))
                es_time = str(int(value["before_insert_time"]) - int(value["received_time"]))
                ins_time = str(int(value["after_insert_time"]) - int(value["before_insert_time"]))
                writer.writerow([key, total_time, es_time, ins_time])

    return True


def run_command(args):
    event_index = load_files(args.received, args.insert)
    pprint.pprint(event_index)

    if len(event_index) > 0:
        return dump_event_time_breakdown(event_index)
    else:
        print("No events found in input files")
        return False

    return True


def main():
    parser = argparse.ArgumentParser(description="Event time extraction script.")
    parser.add_argument("-v", "--verbose", action="store_true", help="verbose output")
    parser.add_argument("received", metavar="RECEIVED", type=str, help="Received event log")
    parser.add_argument("insert", metavar="INSERT", type=str, help="Insertion event log")
    parser.set_defaults(func=run_command)

    args = parser.parse_args()

    global verbose
    verbose = args.verbose

    return args.func(args)


if __name__ == "__main__":
    result = main()

    if result is not True:
        sys.stdout.write("Command failed\n")
