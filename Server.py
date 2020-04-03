#!/usr/bin/env python
import socket
import sys
import datetime
import matplotlib.pyplot as plot
from matplotlib import animation
from Crypto.Cipher import AES

# server network configuration
SERVER_IP_ADDRESS = "0.0.0.0"
PORT = 50123

time = [0]*50
 for i in range(0,50):
		time[i]=i
ax_points = [float(0)]*50
ay_points = [float(0)]*50
az_points = [float(0)]*50

print("starting UDP Server Setup")
sys.stdout.flush()

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind( (SERVER_IP_ADDRESS, PORT) )

print("waiting for data to receive")
sys.stdout.flush()

iv = b.'9331626268227018'
KEY = b.'3874460957140850'
