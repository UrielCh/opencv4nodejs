import path from 'node:path';
import { cv } from '@u4/opencv4nodejs';
import { getResourcePath, wait4key } from './utils.js';


export async function ocrHMMWords() {
  if (!cv.xmodules.text) {
    throw new Error('exiting: opencv4nodejs compiled without text module');
  }
  const dataPath = path.resolve(getResourcePath('text-data'));
  const modelsPath = path.resolve(getResourcePath('text-models'));

  const beamSearchModel = path.resolve(modelsPath, 'OCRBeamSearch_CNN_model_data.xml.gz');

  const vocabulary = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
  const lexicon = [
    'abb', 'riser', 'CHINA', 'HERE', 'HERO', 'President', 'smash', 'KUALA', 'Produkt', 'NINTENDO',
    'foo', 'asdf', 'BAR', 'this', 'makes', 'no', 'sense', 'at', 'all',
  ];

  const transitionP = cv.createOCRHMMTransitionsTable(vocabulary, lexicon);
  const emissionP = cv.Mat.eye(62, 62, cv.CV_64FC1);

  const hmmClassifier = cv.loadOCRHMMClassifierCNN(beamSearchModel);
  const hmmDecoder = new cv.OCRHMMDecoder(hmmClassifier, vocabulary, transitionP, emissionP);

  const wordImages = ['scenetext_word01.jpg', 'scenetext_word02.jpg']
    .map(file => path.resolve(dataPath, file))
    .map(cv.imread);

  for (const img of wordImages) {
    const grayImg = img.type === cv.CV_8U ? img : img.bgrToGray();
    const mask = grayImg.threshold(100, 255, cv.THRESH_BINARY_INV);

    const ret = hmmDecoder.runWithInfo(grayImg, mask);

    console.log('outputText:', ret.outputText);
    cv.imshow('mask', mask);
    cv.imshow('img', img);
    await wait4key();
  }
}

ocrHMMWords();