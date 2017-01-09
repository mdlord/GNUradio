# GNUradio
CDMA spread sprectrum

Prerequisite:

	gstreamer: used for video compression and transmitting video through GNUradio
	gr-dvb: code blocks used in the above flowchart


How to run the Flowchart:

	terminal 1: 	mkfifo video1.ts
			gst-launch -e videotestsrc ! video/x-raw-yuv, framerate=15/1, width=320, 				height=180 ! progressreport name = progress ! x264enc !                mpegtsmux ! 				filesink location=video1.ts
			
	terminal 2: 	mkfifo video2.ts
			gst-launch -vv playbin uri=file:///home/mayank/video2.ts

	→compile the flowchart on GNUradio and run it.
