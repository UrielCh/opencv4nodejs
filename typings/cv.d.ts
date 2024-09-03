import { Mat } from './Mat.d';
import { Size } from './Size.d';
import { Vec2 } from './Vec2.d';
import { Vec3 } from './Vec3.d';
import { Vec4 } from './Vec4.d';
import { Point2 } from './Point2.d';
import { Point3 } from './Point3.d';
import { KeyPoint } from './KeyPoint.d';
import { DescriptorMatch } from './DescriptorMatch.d';
import { Rect } from './Rect.d';
import { OCRHMMClassifier } from './OCRHMMClassifier.d';

export class HistAxes {
  channel: number;
  bins: number;
  ranges: [number, number];

  constructor(channel: number, bins: number, ranges: [number, number]);
  constructor(opts: { channel: number, bins: number, ranges: [number, number] });
}

export * from './group/calib3d';
export * from './group/core_array';
export * from './group/core_cluster';
export * from './group/core_utils';
export * from './group/imgproc_motion';
export * from './group/dnn';
export * from './group/highgui.d';
export * from './group/imgcodecs.d';
export * from './group/imgproc_colormap';
export * from './group/imgproc_filter';
export * from './group/imgproc_motion';
// export * from './group/imgproc_draw';

/** @deprecated */
export function calcHist(img: Mat, histAxes: { channel: number, bins: number, ranges: [number, number] }[], mask?: Mat): Mat;
export function calcHist(img: Mat, histAxes: HistAxes[], mask?: Mat): Mat;
export function calcHistAsync(img: Mat, histAxes: HistAxes[], mask?: Mat): Promise<Mat>;

export function canny(dx: Mat, dy: Mat, threshold1: number, threshold2: number, L2gradient?: boolean): Mat;
export function cannyAsync(dx: Mat, dy: Mat, threshold1: number, threshold2: number, L2gradient?: boolean): Promise<Mat>;

export function computeCorrespondEpilines(points: Point2[], whichImage: number, F: Mat): Vec3[];
export function computeCorrespondEpilinesAsync(points: Point2[], whichImage: number, F: Mat): Promise<Vec3[]>;

export function createOCRHMMTransitionsTable(vocabulary: string, lexicon: string[]): Mat;
export function createOCRHMMTransitionsTableAsync(vocabulary: string, lexicon: string[]): Promise<Mat>;
export function drawKeyPoints(img: Mat, keyPoints: KeyPoint[]): Mat;
export function drawMatches(img1: Mat, img2: Mat, keyPoints1: KeyPoint[], keyPoints2: KeyPoint[], matches: DescriptorMatch[]): Mat;

export function fastNlMeansDenoisingColored(src: Mat, h?: number, hColor?: number, templateWindowSize?: number, searchWindowSize?: number): Mat;
export function fastNlMeansDenoisingColoredAsync(src: Mat, h?: number, hColor?: number, templateWindowSize?: number, searchWindowSize?: number): Promise<Mat>;
export function inpaint(src: Mat, mask: Mat, inpaintRadius: number, flags: number): Mat;
export function inpaintAsync(src: Mat, mask: Mat, inpaintRadius: number, flags: number): Promise<Mat>;

export function findEssentialMat(points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, method?: number, prob?: number, threshold?: number): { E: Mat, mask: Mat };
export function findEssentialMatAsync(points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, method?: number, prob?: number, threshold?: number): Promise<{ E: Mat, mask: Mat }>;

export function findFundamentalMat(points1: Point2[], points2: Point2[], method?: number, param1?: number, param2?: number): { F: Mat, mask: Mat };
export function findFundamentalMatAsync(points1: Point2[], points2: Point2[], method?: number, param1?: number, param2?: number): Promise<{ F: Mat, mask: Mat }>;

export function fitLine(points: Point2[], distType: number, param: number, reps: number, aeps: number): Vec4;
export function fitLine(points: Point3[], distType: number, param: number, reps: number, aeps: number): number[];
export function getAffineTransform(srcPoints: Point2[], dstPoints: Point2[]): Mat;
export function getBuildInformation(): string;
export function getPerspectiveTransform(srcPoints: Point2[], dstPoints: Point2[]): Mat;
export function getRotationMatrix2D(center: Point2, angle: number, scale?: number): Mat;


/**
 * openCV 3 and 4 are not compatible
 * 
 * Calculates the width and height of a text string.
 * param text	Input text string.
 * param fontHeight	Drawing font size by pixel unit.
 * param thickness	Thickness of lines used to render the text. See putText for details.
 * param baseLine	y-coordinate of the baseline relative to the bottom-most text point.
 * 
 * @param text	Input text string.
 * @param fontFace	Font to use, see HersheyFonts.
 * @param fontScale	Font scale factor that is multiplied by the font-specific base size.
 * @param thickness	Thickness of lines used to render the text. See putText for details.
 * @param [out]	baseLine	y-coordinate of the baseline relative to the bottom-most text point.
 */
export function getTextSize(text: string, fontFace: number, fontScale: number, thickness: number): { size: Size, baseLine: number };
export function getTextSizeAsync(text: string, fontFace: number, fontScale: number, thickness: number): Promise<{ size: Size, baseLine: number }>;

export function getValidDisparityROI(roi1: Rect[], roi2: Rect[], minDisparity: number, numberOfDisparities: number, SADWindowSize: number): Rect;
export function getValidDisparityROIAsync(roi1: Rect[], roi2: Rect[], minDisparity: number, numberOfDisparities: number, SADWindowSize: number): Promise<Rect>;

export function goodFeaturesToTrack(mat: Mat, maxCorners: number, qualityLevel: number, minDistance: number, mask?: Mat, blockSize?: number, gradientSize?: number, useHarrisDetector?: boolean, harrisK?: number): Point2[];
export function goodFeaturesToTrackAsync(mat: Mat, maxCorners: number, qualityLevel: number, minDistance: number, mask?: Mat, blockSize?: number, gradientSize?: number, useHarrisDetector?: boolean, harrisK?: number): Promise<Point2[]>;

/**
 * sane as imshow(winName, img); waitKey()
 */
export function imshowWait(winName: string, img: Mat): void;
export function initCameraMatrix2D(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, aspectRatio?: number): Mat;
export function initCameraMatrix2DAsync(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, aspectRatio?: number): Promise<Mat>;
export function loadOCRHMMClassifierCNN(file: string): OCRHMMClassifier;
export function loadOCRHMMClassifierCNNAsync(file: string): Promise<OCRHMMClassifier>;
export function loadOCRHMMClassifierNM(file: string): OCRHMMClassifier;
export function loadOCRHMMClassifierNMAsync(file: string): Promise<OCRHMMClassifier>;
export function matchBruteForce(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceHamming(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceHammingAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceHammingLut(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceHammingLutAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceL1(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceL1Async(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceSL2(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceSL2Async(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchFlannBased(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchFlannBasedAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchKnnBruteForce(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceHamming(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceHammingAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceHammingLut(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceHammingLutAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceL1(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceL1Async(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceSL2(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceSL2Async(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnFlannBased(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnFlannBasedAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;

export function minMaxLoc(mat: Mat, mask?: Mat): { minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 };
export function minMaxLocAsync(mat: Mat, mask?: Mat): Promise<{ minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 }>;

export function plot1DHist(hist: Mat, plotImg: Mat, color: Vec3, lineType?: number, thickness?: number, shift?: number): Mat;
export function getNumThreads(): number;
export function setNumThreads(nthreads: number): void;
export function getThreadNum(): number;

export function projectPoints(objectPoints: Point3[], imagePoints: Point2[], rvec: Vec3, tvec: Vec3, cameraMatrix: Mat, distCoeffs: number[], aspectRatio?: number): { imagePoints: Point2[], jacobian: Mat };
export function projectPointsAsync(objectPoints: Point3[], imagePoints: Point2[], rvec: Vec3, tvec: Vec3, cameraMatrix: Mat, distCoeffs: number[], aspectRatio?: number): Promise<{ imagePoints: Point2[], jacobian: Mat }>;

export function recoverPose(E: Mat, points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, mask?: Mat): { returnValue: number, R: Mat, T: Vec3 };
export function recoverPoseAsync(E: Mat, points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, mask?: Mat): Promise<{ returnValue: number, R: Mat, T: Vec3 }>;

export function sampsonDistance(pt1: Vec2, pt2: Vec2, F: Mat): number;
export function sampsonDistanceAsync(pt1: Vec2, pt2: Vec2, F: Mat): Promise<number>;

export function seamlessClone(src: Mat, dst: Mat, mask: Mat, p: Point2, flags: number): Mat;
export function seamlessCloneAsync(src: Mat, dst: Mat, mask: Mat, p: Point2, flags: number): Promise<Mat>;

export function isCustomMatAllocatorEnabled(): boolean;
export function dangerousEnableCustomMatAllocator(): boolean;
export function dangerousDisableCustomMatAllocator(): boolean;
export function getMemMetrics(): { TotalAlloc: number, TotalKnownByJS: number, NumAllocations: number, NumDeAllocations: number };

/**
 * All non-native functions signatures go here.
 * Implementation are injected fron lib/src/index.ts
 */

// drawDetection TextLines type FontParams, type DrawDetectionParams, type DrawParams
export * from '../types/lib/src/drawUtils';

// dropOverlappingZone getScoreMax toMatTypeName
export * from '../types/lib/src/misc'

// experimental, need improvements / rewrite
export function min(src1: Mat, src2: Mat, dst: Mat): Mat;
export function minAsync(src1: Mat, src2: Mat, dst: Mat): Promise<Mat>;

export function max(src1: Mat, src2: Mat, dst: Mat): Mat;
export function maxAsync(src1: Mat, src2: Mat, dst: Mat): Promise<Mat>;

export function magnitude(x: Mat, y: Mat, magnitude: Mat): Mat;
export function magnitudeAsync(x: Mat, y: Mat, magnitude: Mat): Promise<Mat>;

export const haarCascades: {
  HAAR_EYE: string;
  HAAR_EYE_TREE_EYEGLASSES: string;
  HAAR_FRONTALCATFACE: string;
  HAAR_FRONTALCATFACE_EXTENDED: string;
  HAAR_FRONTALFACE_ALT: string;
  HAAR_FRONTALFACE_ALT2: string;
  HAAR_FRONTALFACE_ALT_TREE: string;
  HAAR_FRONTALFACE_DEFAULT: string;
  HAAR_FULLBODY: string;
  HAAR_LEFTEYE_2SPLITS: string;
  HAAR_LICENCE_PLATE_RUS_16STAGES: string;
  HAAR_LOWERBODY: string;
  HAAR_PROFILEFACE: string;
  HAAR_RIGHTEYE_2SPLITS: string;
  HAAR_RUSSIAN_PLATE_NUMBER: string;
  HAAR_SMILE: string;
  HAAR_UPPERBODY: string;
};
export const lbpCascades: {
  LBP_FRONTALCATFACE: string;
  LBP_FRONTALFACE: string;
  LBP_FRONTALFACE_IMPROVED: string;
  LBP_PROFILEFACE: string;
  LBP_SILVERWARE: string;
};
export const HOGHistogramNormType: { L2Hys: string};
// TODO Fill this types
export class KeyPointMatch {
  distance: number;
  kpTo?: object;
  kpFrom?: object;
}
export class StatModel {}
