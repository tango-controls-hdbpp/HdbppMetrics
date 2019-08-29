#!/usr/bin/env python3

from plotly.subplots import make_subplots
import plotly.io as pio
import sys
import csv
import pprint
import plotly.graph_objects as go

points = []
es_time = []
ins_time = []

with open("dump.csv") as data_fp:
    reader = csv.reader(data_fp, delimiter=",")

    for record in reader:
        points.append(int(record[0]))
        es_time.append(int(record[2])/1000000)
        ins_time.append(int(record[3])/1000000)

fig = make_subplots(
    rows=2, cols=1,
    specs=[[{"type": "xy"}], [{"type": "domain"}]])

barchart = go.Figure(data=[
    go.Bar(name='Event Subscriber Time', x=points, y=es_time),
    go.Bar(name='Insert Time', x=points, y=ins_time)])

# Change the bar mode
barchart.update_layout(barmode='stack')

es_time_bar = go.Bar(name='Event Subscriber Time', x=points, y=es_time)
ins_time_bar = go.Bar(name='Insert Time', x=points, y=ins_time)

fig.append_trace(es_time_bar, row=1, col=1)
fig.append_trace(ins_time_bar, row=1, col=1)

labels=['Event Subscriber Time', 'Insert Time']

fig.append_trace(go.Pie(values=[sum(es_time), sum(ins_time)], labels=labels), row=2, col=1)

fig.show()

