# YSU_rPi_cam
YSU Raspberry Pi + openFrameworks DIY camera workshop

##Overview
This is a DIY digital camera designed to introduce workshop attendees the [Raspberry Pi computer][1], [openFrameworks C++ toolkit][2] and basic image processing. This repo includes an openFrameworks application that pulls in video from a webcam, processes that video into either an overlaid still image or a GIF. The application saves files to a different partition on the Pi's SD card. That way, users can turn off the pi, remove the SD card, plug the SD card into their computer and access the images, similar to a traditional digital camera. This has been developed and tested on `2015-02-16-raspbian-wheezy`. 




##Dependencies
You will need to download the following:

1. [openFrameworks for Raspberry Pi (linux armv6)][3]
2. [ofxGifEncoder][4]
3. [ofxWiringPi][5] (this was developed by Joshua Noble, but the linked branch has a different directory structure that works with the included configure.make)


##Installation
1. Download and install openframeworks. Follow the setup instructions [here][6]. 
2. Move into the addons folder within openFrameworks and clone ofxGifEncoder ofxWiringPi
3. Move into the apps/myApps/YSU_rPi_cam folder.  Make sure there is a copy of ofxWiringPi in the addons folder within YSU_rPi_cam. If the folder is empty, copy ofxWiringPi from the main openFrameworks addons folder to this addons folder

[1]: http://www.raspberrypi.org/
[2]: http://www.openframeworks.cc/
[3]: http://www.openframeworks.cc/download/
[4]: https://github.com/jesusgollonet/ofxGifEncoder
[5]: https://github.com/jmarsico/ofxWiringPi  
[6]: http://www.openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Getting-Started.html

