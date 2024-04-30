import { Mat } from '@u4/opencv4nodejs';
import { cv, getResourcePath } from '../utils.js';
import { runVideoFaceDetectionAsync } from './commons.js';

if (cv.version.minor === 4) {
  console.log('Warning: It seems like opencv 3.4 does not run the opencl version of detectMultiScale.');
}

const videoFile = getResourcePath('people.mp4');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

async function detectFaces(img: Mat) {
  const options = {
    scaleFactor: 1.1,
    minNeighbors: 10,
  };
  return (await classifier.detectMultiScaleGpuAsync(img.bgrToGray(), options)).objects;
}

runVideoFaceDetectionAsync(videoFile, detectFaces);
