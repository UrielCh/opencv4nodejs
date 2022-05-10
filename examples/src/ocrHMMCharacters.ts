import { cv, getResource } from './utils';
import path from 'path';
import type { Mat } from '@u4/opencv4nodejs';


interface ClassConf {
  class: string;
  confidence: number;

}

/**
 * OCR One by one using OCRHMMClassifier
 */

if (!cv.xmodules || !cv.xmodules.text) {
  throw new Error('exiting: opencv4nodejs compiled without text module');
}

const dataPath = path.resolve(getResource('text-data'));
const modelsPath = path.resolve(getResource('text-models'));
const beamSearchModel = path.resolve(modelsPath, 'OCRBeamSearch_CNN_model_data.xml.gz');

const vocabulary = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';

const hmmClassifier = cv.loadOCRHMMClassifierCNN(beamSearchModel);

const charImages = ['scenetext_char01.jpg', 'scenetext_char02.jpg']
  .map(file => path.resolve(dataPath, file))
  .map(cv.imread);

const numbersImg = cv.imread(path.resolve(dataPath, 'numbers.png'));
const numberImages = [] as Mat[];

const h = numbersImg.rows / 2;
const w = numbersImg.cols / 5;
for (let r = 0; r < 2; r += 1) {
  for (let c = 0; c < 5; c += 1) {
    const cell = new cv.Rect(w * c, h * r, w, h);
    const numberImg = numbersImg.getRegion(cell);
    numberImages.push(numberImg.copy());
  }
}

charImages.concat(numberImages).forEach((img) => {
  const {
    classes,
    confidences
  } = hmmClassifier.eval(img);

  const minConfidence = 0.05;
  const predictions: ClassConf[] = classes
    .map(
      (clazz: number, i: number) => ({
        class: vocabulary[clazz],
        confidence: confidences[i]
      })
    )
    .filter((prediction: ClassConf) => prediction.confidence > minConfidence);

  console.log('result:', predictions.map(p => `${p.class} : ${(p.confidence * 100).toFixed(2)}%`));
  cv.imshowWait('image', img);
});
