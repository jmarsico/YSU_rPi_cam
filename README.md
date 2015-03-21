# YSU_rPi_cam
Youngstown State University workshop for building Raspberry Pi + openFrameworks digital camera. 

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


##Basic Usage
1. Hook up a button, connecting to a ground pin and pin 7 (using [wiringPi pin assignments][7])
2. Hook up an LED to another ground pin and pin 2 (again, using wiringPi pin assignments).
3. Within the ofApp.cpp, be sure to change the folder to which the files save. (look in the `saveGif()` and `saveOverlay()` functions)
4. Run the application!
5. A short press of the button will record a still image consisting of 10 overlaid images
6. A long (over 1 second) press of the button will record a 10 image GIF.


##More Information
Check out the [workshop google doc][8] for more detailed usage and assembly information, links to .stl files for the case, and an overview of the workshop schedule.

Special thanks to [Dana Sperry][9] for funding the development of the camera and hosting the workshop.

[1]: http://www.raspberrypi.org/
[2]: http://www.openframeworks.cc/
[3]: http://www.openframeworks.cc/download/
[4]: https://github.com/jesusgollonet/ofxGifEncoder
[5]: https://github.com/jmarsico/ofxWiringPi  
[6]: http://www.openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Getting-Started.html
[7]: https://projects.drogon.net/raspberry-pi/wiringpi/pins/
[8]: https://docs.google.com/document/d/1YMw73aOF5FGlJ_VMr5oSEBMXrsuZEWxUTwLzXXXZtwg/edit
[9]: http://www.danasperry.com/

