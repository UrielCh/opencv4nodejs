#include "HistAxes.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Size.h"
#include "TermCriteria.h"
#include "Vec.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_CORE_H__
#define __FF_CORE_H__

class Core : public Napi::ObjectWrap<Core> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  // export function getBuildInformation(): string;
  static Napi::Value GetBuildInformation(const Napi::CallbackInfo& info);
  // export function partition<T extends Point2|Point3|Vec2|Vec3|Vec4|Vec6|Mat>(data: Array<T>, predicate: (pt1: T, pt2: T) => boolean): { labels: number[], numLabels: number };
  static Napi::Value Partition(const Napi::CallbackInfo& info);
  // export function kmeans<T extends Point2|Point3>(data: T[], k: number, termCriteria: TermCriteria, attempts: number, flags: number): { labels: number[], centers: T[] };
  static Napi::Value Kmeans(const Napi::CallbackInfo& info);
  // export function cartToPolar(x: Mat, y: Mat, magnitude: Mat, angle: Mat, angleInDegrees?: boolean): { magnitude: Mat, angle: Mat };
  static Napi::Value CartToPolar(const Napi::CallbackInfo& info);
  // export function cartToPolarAsync(x: Mat, y: Mat, magnitude: Mat, angle: Mat, angleInDegrees?: boolean): Promise<{ magnitude: Mat, angle: Mat }>;
  static Napi::Value CartToPolarAsync(const Napi::CallbackInfo& info);
  // export function polarToCart(magnitude: Mat, angle: Mat, angleInDegrees?: boolean): { x: Mat, y: Mat };
  static Napi::Value PolarToCart(const Napi::CallbackInfo& info);
  // export function polarToCartAsync(magnitude: Mat, angle: Mat, angleInDegrees?: boolean): Promise<{ x: Mat, y: Mat }>;
  static Napi::Value PolarToCartAsync(const Napi::CallbackInfo& info);
  // export function getNumThreads(): number;
  static Napi::Value GetNumThreads(const Napi::CallbackInfo& info);
  // export function setNumThreads(nthreads: number): void;
  static void SetNumThreads(const Napi::CallbackInfo& info);
  // export function getThreadNum(): number;
  static Napi::Value GetThreadNum(const Napi::CallbackInfo& info);
  // Mat.addWeighted(alpha: number, mat2: Mat, beta: number, gamma: number, dtype?: number): Mat;
  static Napi::Value AddWeighted(const Napi::CallbackInfo& info);
  // Mat.addWeightedAsync(alpha: number, mat2: Mat, beta: number, gamma: number, dtype?: number): Promise<Mat>;
  static Napi::Value AddWeightedAsync(const Napi::CallbackInfo& info);
  // minMaxLoc(mask?: Mat): { minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 };
  static Napi::Value MinMaxLoc(const Napi::CallbackInfo& info);
  // minMaxLocAsync(mask?: Mat): Promise<{ minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 }>;
  static Napi::Value MinMaxLocAsync(const Napi::CallbackInfo& info);
  // export function findNonZero(src: Mat, idx?: Mat): Point2[];
  static Napi::Value FindNonZero(const Napi::CallbackInfo& info);
  // export function findNonZeroAsync(src: Mat, idx?: Mat): Promise<Point2[]>;
  static Napi::Value FindNonZeroAsync(const Napi::CallbackInfo& info);
  // export function countNonZero(mat: Mat): number;
  static Napi::Value CountNonZero(const Napi::CallbackInfo& info);
  // export function countNonZeroAsync(mat: Mat): Promise<number>;
  static Napi::Value CountNonZeroAsync(const Napi::CallbackInfo& info);
  // normalize(this: Mat, alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat): Mat;
  // normalize(this: Mat, opt: { alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat }): Mat;
  static Napi::Value Normalize(const Napi::CallbackInfo& info);
  // normalizeAsync(this: Mat, alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat): Promise<Mat>;
  // normalizeAsync(this: Mat, opt: { alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat }): Promise<Mat>;
  static Napi::Value NormalizeAsync(const Napi::CallbackInfo& info);
  // export function split(mat: Mat): Mat[];
  static Napi::Value Split(const Napi::CallbackInfo& info);
  // export function splitAsync(mat: Mat): Promise<Mat[]>;
  static Napi::Value SplitAsync(const Napi::CallbackInfo& info);
  // export function mulSpectrums(src1: Mat, src2: Mat, dftRows?: boolean, conjB?: boolean): Mat;
  static Napi::Value MulSpectrums(const Napi::CallbackInfo& info);
  // export function mulSpectrumsAsync(src1: Mat, src2: Mat, dftRows?: boolean, conjB?: boolean): Promise<Mat>;
  static Napi::Value MulSpectrumsAsync(const Napi::CallbackInfo& info);
  // transform(m: Mat): Mat;
  static Napi::Value Transform(const Napi::CallbackInfo& info);
  // transformAsync(m: Mat): Promise<Mat>;
  static Napi::Value TransformAsync(const Napi::CallbackInfo& info);
  // perspectiveTransform(this: Mat, m: Mat): Mat;
  static Napi::Value PerspectiveTransform(const Napi::CallbackInfo& info);
  // perspectiveTransformAsync(this: Mat, m: Mat): Promise<Mat>;
  static Napi::Value PerspectiveTransformAsync(const Napi::CallbackInfo& info);
  // export function sum(mat: Mat): number | Vec2 | Vec3 | Vec4;
  static Napi::Value Sum(const Napi::CallbackInfo& info);
  // export function sumAsync(mat: Mat): Promise<number | Vec2 | Vec3 | Vec4>;
  static Napi::Value SumAsync(const Napi::CallbackInfo& info);
  // convertScaleAbs(alpha: number, beta: number): Mat;
  static Napi::Value ConvertScaleAbs(const Napi::CallbackInfo& info);
  // convertScaleAbsAsync(alpha: number, beta: number): Promise<Mat>;
  static Napi::Value ConvertScaleAbsAsync(const Napi::CallbackInfo& info);
  // mean(): Vec4;
  static Napi::Value Mean(const Napi::CallbackInfo& info);
  // meanAsync(): Promise<Vec4>;
  static Napi::Value MeanAsync(const Napi::CallbackInfo& info);
  // meanStdDev(mask?: Mat): { mean: Mat, stddev: Mat };
  static Napi::Value MeanStdDev(const Napi::CallbackInfo& info);
  // meanStdDevAsync(mask?: Mat): Promise<{ mean: Mat, stddev: Mat }>;
  static Napi::Value MeanStdDevAsync(const Napi::CallbackInfo& info);
  // reduce(dim: number, rtype: number, dtype?: number): Mat;
  static Napi::Value Reduce(const Napi::CallbackInfo& info);
  // reduceAsync(dim: number, rtype: number, dtype?: number): Promise<Mat>;
  static Napi::Value ReduceAsync(const Napi::CallbackInfo& info);
  // export function min(src1: Mat, src2: Mat, dst: Mat): Mat;
  static Napi::Value Min(const Napi::CallbackInfo& info);
  // export function minAsync(src1: Mat, src2: Mat, dst: Mat): Promise<Mat>;
  static Napi::Value MinAsync(const Napi::CallbackInfo& info);
  // export function max(src1: Mat, src2: Mat, dst: Mat): Mat;
  static Napi::Value Max(const Napi::CallbackInfo& info);
  // export function maxAsync(src1: Mat, src2: Mat, dst: Mat): Promise<Mat>;
  static Napi::Value MaxAsync(const Napi::CallbackInfo& info);
  // export function eigen(src: Mat, eigenvalues?: Mat, eigenvectors?: Mat): Mat;
  static Napi::Value Eigen(const Napi::CallbackInfo& info);
  // static void EigenAsync(const Napi::CallbackInfo& info);
  static Napi::Value EigenAsync(const Napi::CallbackInfo& info);
  // solve(this: Mat, mat2: Mat, flags?: number): Mat;
  static Napi::Value Solve(const Napi::CallbackInfo& info);
  // solveAsync(this: Mat, mat2: Mat, flags?: number): Promise<Mat>;
  static Napi::Value SolveAsync(const Napi::CallbackInfo& info);
  // export function magnitude(x: Mat, y: Mat, magnitude: Mat): Mat;
  static Napi::Value Magnitude(const Napi::CallbackInfo& info);
  // export function magnitudeAsync(x: Mat, y: Mat, magnitude: Mat): Promise<Mat>;
  static Napi::Value MagnitudeAsync(const Napi::CallbackInfo& info);
  // export function getTickFrequency(): number;
  static Napi::Value GetTickFrequency(const Napi::CallbackInfo& info);
  // export function getTickCount(): number;
  static Napi::Value GetTickCount(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  // export function getVersionMajor(): number;
  static Napi::Value GetVersionMajor(const Napi::CallbackInfo& info);
  // export function GetVersionMinor(): number;
  static Napi::Value GetVersionMinor(const Napi::CallbackInfo& info);
  // export function GetVersionRevision(): number;
  static Napi::Value GetVersionRevision(const Napi::CallbackInfo& info);
#endif
};

#endif
