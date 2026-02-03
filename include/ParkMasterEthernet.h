#ifndef PARK_MASTER_ETHERNET_H
#define PARK_MASTER_ETHERNET_H
#include <SPI.h>
#include <Ethernet.h>
#include <ParkMasterDisplay.h>

// --- Pin Definitions ---
#define ETH_CS          5
// --- MAC Address Definition ---
#define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


byte mac[] = MAC_ADDRESS;

void setupEthernet()
{
    Ethernet.init(ETH_CS);
    if (Ethernet.begin(mac) == 0)
    {
        display.println("Eth Failed (DHCP)");
    }
    else
    {
        display.print("IP: ");
        display.println(Ethernet.localIP());
    }
    display.display();
}

#endif // PARK_MASTER_ETHERNET_H