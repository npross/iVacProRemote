# iVacProRemote
Control an iVac Pro Switch with a cheap 433 MHz Transmitter and an Arduino

# Introduction
I own an iVac Pro switch that is connected to my dust collector.  I was using it with my router table which uses a current sensing remote that turns the dust collector on and off whenever the router is turned on.  I recently aadded a small CNC machine.  I wanted to be able to control the DC when the spindle for the CNC machine turned on and off.  It seemed silly to use a current sensing device when I had a perfectly good 5V GPIO signal to control the switch.  Unfortunately there was no external input to the switch.

So I figured since it was controlled via RF, maybe I could use a cheap RF transmitter.

Here is the FCC filing for a remote iVac Pro controller which immediately tells us that this is a 433.92 Mhz device

FCC Info: https://fccid.io/YCHIVACPRO/Users-Manual/User-manual-1458445

# RTL-SDR + Universal Radio Hacker Made things easy

Using an RTL-SDR device to capture some samples with *Universal Radio Hacker* this is what I've figured out so far:

* Frequency: 433.92 MHz
* Encoding: ASK/OOK
* Bits: 36
* BitLength: 432us

# Encoding
I'm sure someone with actual experience decoding/encoding RF will know way more about this than me but as far as I can see there is a 
Header of 14 bits, followed by 6 bits of data, 2 bits destination, X bit Command (On/Off), 3 bits source, 1 bit checksum.  

Each data bit is preceded by a 01 transition

111010101010111 01 D 01 D 01 C 01 S 01 S 01 S 01 C

* Header: 111010101010111
* DD: 2 bits Destination switch (0-4)
* X:  1 bit Command (On/OFF)
* SSS: 3 bits Source (0-7)
* C: 1 bit Checksum (sum(DDXSSS))

