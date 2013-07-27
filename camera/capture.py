import os;
import time;
import cv;

storage = cv.CreateMemStorage()
haar = cv.Load('/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml')

filename = "./capture.jpg"

while (True):
  print "capturing image"
  start = time.time()
  os.system("/usr/bin/raspistill -w 800 -h 600 -vf -t 0 -o " + filename)
  end = time.time()
  print "captured image in " + str(end-start) + " seconds"

  print "processing image"
  start = time.time()
  image = cv.LoadImage(filename)
  detected = cv.HaarDetectObjects(image, haar, storage, 1.2, 2, cv.CV_HAAR_DO_CANNY_PRUNING, (100,100))
  end = time.time()
  print "processed image in " + str(end-start) + " seconds"

  if detected:
    print "detected face"
    for face in detected:
      print face
  else:
    print "no face"
