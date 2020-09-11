__Active Development, code might not work as expected__

# LoRaMessager
LoRa based, off-network private messaging.

## Overview
This project started when the need for intercommunication during walks in areas with limited to no network coverage was determined. The resulting product will likely be a ESP32/LoRa baseboard combined with a LiPo battery inside of a 3D printed shell.

## Existing solutions
* GoTenna (https://gotenna.com/) makes off grid communications nodes. One of the main downsides of the product is the fact that it is quite expensive and needs an app to function. This may have the unwanted side-effect of storing, analyzing or sending (personal)data to third-parties.
* GoToky (https://www.gotoky.com/) is a similar LoRa-based mesh communicator, however it is still in the development phase and only available as pre-order on IndieGoGo.
* BearTooth (https://beartooth.com/) claims to be the worlds smartest walkie-talkie. This entails that the device is mainly used for PTT (Push-To-Talk) functionality and voice-communication. 

## Requirements
* Portable design, must not weight >500g all incl.
* Long battery-life, must last at least 24h if not more.
* All messages and settings stored on the device, even after power-down.
* User should not have to download any specific app, and interface should work in any modern browser.
* Message encryption should be applied to make sure only intended recipient can read message. This can be implemented with for example private-keys.
* Messages should be error-checked and there should be a received feedback-mechanism implemented.

### Stretch goals
* The ability to send emoji's.
* Basic status messages via LEDs / a onboard screen.
* Battery-indicator in the interface.
* Discover other nodes on the network via a network scan.
* Sending messages into a mesh-network where it is routed to the correct recipient, instead of a direct-communication, to enable longer distance transmissions.
* Ability to send GPS coordinates.
* Group chats.

## Used technologies
* ESP32 programmed using C++ via PlatformIO.
* HTML/CSS/JS for the web-interface.
* Custom protocol for the LoRa transmissions.
