import type { Mat, Rect } from '@u4/opencv4nodejs';
import { cv } from '../utils';

export type Prediction = {
  classLabel: number
  confidence: number
  rect: Rect
}

export function extractResults(outputBlob: Mat, imgDimensions: { rows: number, cols: number }) {
  return Array(outputBlob.rows).fill(0)
    .map((res, i) => {
      const classLabel = outputBlob.at(i, 1);
      const confidence = outputBlob.at(i, 2);
      const bottomLeft = new cv.Point2(
        outputBlob.at(i, 3) * imgDimensions.cols,
        outputBlob.at(i, 6) * imgDimensions.rows,
      );
      const topRight = new cv.Point2(
        outputBlob.at(i, 5) * imgDimensions.cols,
        outputBlob.at(i, 4) * imgDimensions.rows,
      );
      const rect = new cv.Rect(
        bottomLeft.x,
        topRight.y,
        topRight.x - bottomLeft.x,
        bottomLeft.y - topRight.y,
      );

      return ({ classLabel, confidence, rect });
    });
}
