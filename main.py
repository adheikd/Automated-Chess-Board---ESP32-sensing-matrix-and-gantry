# import Server
import wifimgr
from time import sleep
import machine

try:
  import usocket as socket
except:
  import socket

def main():
    wlan = wifimgr.get_connection()
    if wlan is None:
        print("Could not initialize the network connection.")
        while True:
            pass  # you shall not pass :D
        # Main Code goes here, wlan is a working network.WLAN(STA_IF) instance.
    print("ESP OK")

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(('', 80))
        s.listen(5)
    except OSError as e:
        machine.reset()
    # Server.start_server()

if __name__ == "__main__":
    main()
