FROM python:3.11-slim

RUN pip install platformio

WORKDIR /workspace

COPY platformio.ini .

RUN pio pkg install

COPY . . 

ARG WIFI_SSID=test_ssid
ARG WIFI_PASS=test_pass

ENV WIFI_SSID=${WIFI_SSID} 
ENV WIFI_PASS=${WIFI_PASS}


RUN pio run 

