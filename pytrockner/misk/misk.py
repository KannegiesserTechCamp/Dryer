from time import sleep

def warte_millisekunde(zeit: int):
    # wenn 'zeit' Millisekunden sind, in Sekunden umrechnen
    if zeit < 0:
        raise ValueError("zeit muss >= 0 sein")
    sleep(zeit / 1000)