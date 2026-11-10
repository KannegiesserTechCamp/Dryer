import network

#--------------------------------------------------------------------#

__NETWORK_NAME = 'Tech-Camp'
__NETWORK_PASSWORD = 'Kannegiesser2025'

def start_ap():
    ap = network.WLAN(network.AP_IF)
    ap.active(True)
    
    #authmode=network.AUTH_WPA_PSK
    ap.config(essid = __NETWORK_NAME,password = __NETWORK_PASSWORD, authmode=network.AUTH_WPA_PSK)
    print(ap.ifconfig())
    print("\n","Netzwerkname: ",__NETWORK_NAME," Passwort:",__NETWORK_PASSWORD, "\n")