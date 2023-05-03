# DockerFlushReload

## Abstract 
Side-channel and micro-architectural attacks have been of heightened interest in latest years. With the rise of cloud computing, we see that there is an increase of users deploying their application into the cloud. Cloud providers such as AWS use containerization technology to serve these servlerless applications. We set out to investigate the accuracy of the Flush+Reload side channel attack in a constructed container environment with Docker. We discover that Flush+Reload is not effective on containers running on a virtual machine. Despite this, we show that Flush+Reload 83.3% effective against containers running on OS installed on a bare-metal machine. 


