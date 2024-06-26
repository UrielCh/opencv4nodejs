import { Mat } from './Mat.d';
import { Size } from './Size.d';
import { Rect } from './Rect.d';
import { Point2 } from './Point2.d';

export interface HOGDescriptorArgs {
  winSize?: Size;
  blockSize?: Size;
  blockStride?: Size;
  cellSize?: Size;
  nbins?: number;
  derivAperture?: number;
  winSigma?: number;
  histogramNormType?: number;
  L2HysThreshold?: number;
  gammaCorrection?: boolean;
  nlevels?: number;
  signedGradient?: boolean;
}

export interface DetectMultiScaleROIRet {
  foundLocations: Rect[];
  foundWeights: number[];
}

export interface HOGDescriptorDetectROIRet {
  foundLocations: Point2[];
  confidences: number[];
}

export interface HOGDescriptorDetectRet {
  foundLocations: Point2[];
   weights: number[];
}

export interface HOGDescriptorComputeGradientRet {
  grad: Mat;
  angleOfs: Mat;
}

export class HOGDescriptor {
  readonly winSize: Size;
  readonly blockSize: Size;
  readonly blockStride: Size;
  readonly cellSize: Size;
  readonly nbins: number;
  readonly derivAperture: number;
  readonly histogramNormType: number;
  readonly nlevels: number;
  readonly winSigma: number;
  readonly L2HysThreshold: number;
  readonly gammaCorrection: boolean;
  readonly signedGradient: boolean;
  constructor(winSize?: Size, blockSize?: Size, blockStride?: Size, cellSize?: Size, nbins?: number, derivAperture?: number, winSigma?: number, histogramNormType?: number, L2HysThreshold?: number, gammaCorrection?: boolean, nlevels?: number, signedGradient?: boolean);
  constructor(params: HOGDescriptorArgs);

  checkDetectorSize(): boolean;
  
  compute(img: Mat, winStride?: Size, padding?: Size, locations?: Point2[]): number[];
  computeAsync(img: Mat, winStride?: Size, padding?: Size, locations?: Point2[]): Promise<number[]>;

  computeGradient(img: Mat, paddingTL?: Size, paddingBR?: Size): HOGDescriptorComputeGradientRet;
  computeGradientAsync(img: Mat, paddingTL?: Size, paddingBR?: Size): Promise<HOGDescriptorComputeGradientRet>;

  detect(img: Mat, hitThreshold?: number, winStride?: Size, padding?: Size, searchLocations?: Point2[]): HOGDescriptorDetectRet;
  detectAsync(img: Mat, hitThreshold?: number, winStride?: Size, padding?: Size, searchLocations?: Point2[]): Promise<HOGDescriptorDetectRet>;
  
  detectMultiScale(img: Mat, hitThreshold?: number, winStride?: Size, padding?: Size, scale?: number, finalThreshold?: number, useMeanshiftGrouping?: boolean): DetectMultiScaleROIRet;
  detectMultiScaleAsync(img: Mat, hitThreshold?: number, winStride?: Size, padding?: Size, scale?: number, finalThreshold?: number, useMeanshiftGrouping?: boolean): Promise<DetectMultiScaleROIRet>;

  detectMultiScaleROI(img: Mat, hitThreshold?: number, groupThreshold?: number): Rect[];
  detectMultiScaleROIAsync(img: Mat, hitThreshold?: number, groupThreshold?: number): Promise<Rect[]>;

  detectROI(img: Mat, locations: Point2[], hitThreshold?: number, winStride?: Size, padding?: Size): HOGDescriptorDetectROIRet;
  detectROIAsync(img: Mat, locations: Point2[], hitThreshold?: number, winStride?: Size, padding?: Size): Promise<HOGDescriptorDetectROIRet>;
  
  static getDaimlerPeopleDetector(): number[];
  static getDefaultPeopleDetector(): number[];

  groupRectangles(rectList: Rect[], weights: number[], groupThreshold: number, eps: number): Rect[];
  groupRectanglesAsync(rectList: Rect[], weights: number[], groupThreshold: number, eps: number): Promise<Rect[]>;

  load(path: string): void;
  save(path: string): void;
  setSVMDetector(detector: number[]): void;
}
