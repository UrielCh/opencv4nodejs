import path from 'node:path';
import { type OpenCVBuildEnvParams } from '@u4/opencv-build';
import promisify from './promisify.js';
import extendWithJsSources from './ext/index.js';
import { getOpenCV } from './cvloader.js';
import type * as openCV from '../../typings/index.js';
import { getDirName } from './meta.js';
import { resolvePath } from './commons.js';

export type * as openCV from '../../typings/index.js';
export { getDirName, getRequire } from "./meta.js"

declare type OpenCVType = typeof openCV;

function loadOpenCV(opt?: OpenCVBuildEnvParams): OpenCVType {
  // load native binding
  const cvBase = getOpenCV(opt);
  // check the presence of any expected symbol, to ensure the library is loaded
  if (!cvBase.accumulate) {
    throw Error('failed to load opencv basic accumulate not found.')
  }
  if (!cvBase.blur) {
    throw Error('failed to load opencv basic blur not found.')
  }

  // resolve haarcascade and lbpCascades files paths
  const { haarCascades, lbpCascades } = cvBase;
  const dirname = getDirName();
  const xmlDir = path.join(dirname, '..', '..', 'src', 'lib');
  Object.keys(haarCascades).forEach(
    key => (cvBase as any)[key] = resolvePath(path.join(xmlDir, 'haarcascades'), haarCascades[key as keyof typeof haarCascades]));
  Object.keys(lbpCascades).forEach(
    key => (cvBase as any)[key] = resolvePath(path.join(xmlDir, 'lbpcascades'), lbpCascades[key as keyof typeof lbpCascades]));
  // promisify async methods
  let cvObj = promisify<OpenCVType>(cvBase);
  cvObj = extendWithJsSources(cvObj);
  // add xmodules alias if not present (moved to C++ part)
  // if (!cvObj.xmodules && cvObj.modules)
  //  cvObj.xmodules = cvObj.modules
  return cvObj;
}

export const cv = loadOpenCV({ prebuild: 'latestBuild' });

function dumpExports() {
  let allExports = Object.keys(cv);
  allExports = allExports.filter(key => !key.includes('"'));
  console.log('\n\n');
  while (allExports.length) {
    const keys = allExports.splice(0, 15);
    console.log(`const { ${keys} } = cv;`);
    console.log(`export { ${keys} };`);
  }
  console.log('\n\n'); 
}
// dumpExports();

//////////////
//// GENERATED code

const { isCustomMatAllocatorEnabled,dangerousEnableCustomMatAllocator,dangerousDisableCustomMatAllocator,getMemMetrics,version,modules,xmodules,CV_8U,CV_8S,CV_16U,CV_16S,CV_32S,CV_32F,CV_64F,CV_16F } = cv;
export { isCustomMatAllocatorEnabled,dangerousEnableCustomMatAllocator,dangerousDisableCustomMatAllocator,getMemMetrics,version,modules,xmodules,CV_8U,CV_8S,CV_16U,CV_16S,CV_32S,CV_32F,CV_64F,CV_16F };
const { CV_8UC1,CV_8UC2,CV_8UC3,CV_8UC4,CV_8SC1,CV_8SC2,CV_8SC3,CV_8SC4,CV_16UC1,CV_16UC2,CV_16UC3,CV_16UC4,CV_16SC1,CV_16SC2,CV_16SC3 } = cv;
export { CV_8UC1,CV_8UC2,CV_8UC3,CV_8UC4,CV_8SC1,CV_8SC2,CV_8SC3,CV_8SC4,CV_16UC1,CV_16UC2,CV_16UC3,CV_16UC4,CV_16SC1,CV_16SC2,CV_16SC3 };
const { CV_16SC4,CV_32SC1,CV_32SC2,CV_32SC3,CV_32SC4,CV_32FC1,CV_32FC2,CV_32FC3,CV_32FC4,CV_64FC1,CV_64FC2,CV_64FC3,CV_64FC4,CV_16FC1,CV_16FC2 } = cv;
export { CV_16SC4,CV_32SC1,CV_32SC2,CV_32SC3,CV_32SC4,CV_32FC1,CV_32FC2,CV_32FC3,CV_32FC4,CV_64FC1,CV_64FC2,CV_64FC3,CV_64FC4,CV_16FC1,CV_16FC2 };
const { CV_16FC3,CV_16FC4,NORM_INF,NORM_L1,NORM_L2,NORM_L2SQR,NORM_HAMMING,NORM_HAMMING2,NORM_TYPE_MASK,NORM_RELATIVE,NORM_MINMAX,KMEANS_RANDOM_CENTERS,KMEANS_PP_CENTERS,KMEANS_USE_INITIAL_LABELS,termCriteria } = cv;
export { CV_16FC3,CV_16FC4,NORM_INF,NORM_L1,NORM_L2,NORM_L2SQR,NORM_HAMMING,NORM_HAMMING2,NORM_TYPE_MASK,NORM_RELATIVE,NORM_MINMAX,KMEANS_RANDOM_CENTERS,KMEANS_PP_CENTERS,KMEANS_USE_INITIAL_LABELS,termCriteria };
const { haarCascades,lbpCascades,REDUCE_SUM,REDUCE_AVG,REDUCE_MAX,REDUCE_MIN,ROTATE_90_CLOCKWISE,ROTATE_180,ROTATE_90_COUNTERCLOCKWISE,DECOMP_LU,DECOMP_CHOLESKY,DECOMP_EIG,DECOMP_SVD,DECOMP_QR,DECOMP_NORMAL } = cv;
export { haarCascades,lbpCascades,REDUCE_SUM,REDUCE_AVG,REDUCE_MAX,REDUCE_MIN,ROTATE_90_CLOCKWISE,ROTATE_180,ROTATE_90_COUNTERCLOCKWISE,DECOMP_LU,DECOMP_CHOLESKY,DECOMP_EIG,DECOMP_SVD,DECOMP_QR,DECOMP_NORMAL };
const { BORDER_CONSTANT,BORDER_REPLICATE,BORDER_REFLECT,BORDER_WRAP,BORDER_REFLECT_101,BORDER_TRANSPARENT,BORDER_ISOLATED,BORDER_DEFAULT,Mat,Point,Point2,Point3,Vec,Vec2,Vec3 } = cv;
export { BORDER_CONSTANT,BORDER_REPLICATE,BORDER_REFLECT,BORDER_WRAP,BORDER_REFLECT_101,BORDER_TRANSPARENT,BORDER_ISOLATED,BORDER_DEFAULT,Mat,Point,Point2,Point3,Vec,Vec2,Vec3 };
const { Vec4,Vec6,Size,Rect,RotatedRect,TermCriteria,HistAxes,getBuildInformation,partition,kmeans,cartToPolar,cartToPolarAsync,polarToCart,polarToCartAsync,getNumThreads } = cv;
export { Vec4,Vec6,Size,Rect,RotatedRect,TermCriteria,HistAxes,getBuildInformation,partition,kmeans,cartToPolar,cartToPolarAsync,polarToCart,polarToCartAsync,getNumThreads };
const { setNumThreads,getThreadNum,addWeighted,addWeightedAsync,minMaxLoc,minMaxLocAsync,findNonZero,findNonZeroAsync,countNonZero,countNonZeroAsync,split,splitAsync,mulSpectrums,mulSpectrumsAsync,transform } = cv;
export { setNumThreads,getThreadNum,addWeighted,addWeightedAsync,minMaxLoc,minMaxLocAsync,findNonZero,findNonZeroAsync,countNonZero,countNonZeroAsync,split,splitAsync,mulSpectrums,mulSpectrumsAsync,transform };
const { transformAsync,perspectiveTransform,perspectiveTransformAsync,convertScaleAbs,convertScaleAbsAsync,sum,sumAsync,mean,meanAsync,meanStdDev,meanStdDevAsync,reduce,reduceAsync,eigen,eigenAsync } = cv;
export { transformAsync,perspectiveTransform,perspectiveTransformAsync,convertScaleAbs,convertScaleAbsAsync,sum,sumAsync,mean,meanAsync,meanStdDev,meanStdDevAsync,reduce,reduceAsync,eigen,eigenAsync };
const { min,minAsync,max,maxAsync,solve,solveAsync,magnitude,magnitudeAsync,getTickFrequency,getTickCount,getVersionMajor,getVersionMinor,getVersionRevision,WINDOW_NORMAL,WINDOW_AUTOSIZE } = cv;
export { min,minAsync,max,maxAsync,solve,solveAsync,magnitude,magnitudeAsync,getTickFrequency,getTickCount,getVersionMajor,getVersionMinor,getVersionRevision,WINDOW_NORMAL,WINDOW_AUTOSIZE };
const { WINDOW_OPENGL,WINDOW_FULLSCREEN,WINDOW_FREERATIO,WINDOW_KEEPRATIO,WINDOW_GUI_EXPANDED,WINDOW_GUI_NORMAL,WND_PROP_FULLSCREEN,WND_PROP_AUTOSIZE,WND_PROP_ASPECT_RATIO,WND_PROP_OPENGL,WND_PROP_VISIBLE,WND_PROP_TOPMOST,WND_PROP_VSYNC,EVENT_MOUSEMOVE,EVENT_LBUTTONDOWN } = cv;
export { WINDOW_OPENGL,WINDOW_FULLSCREEN,WINDOW_FREERATIO,WINDOW_KEEPRATIO,WINDOW_GUI_EXPANDED,WINDOW_GUI_NORMAL,WND_PROP_FULLSCREEN,WND_PROP_AUTOSIZE,WND_PROP_ASPECT_RATIO,WND_PROP_OPENGL,WND_PROP_VISIBLE,WND_PROP_TOPMOST,WND_PROP_VSYNC,EVENT_MOUSEMOVE,EVENT_LBUTTONDOWN };
const { EVENT_RBUTTONDOWN,EVENT_MBUTTONDOWN,EVENT_LBUTTONUP,EVENT_RBUTTONUP,EVENT_MBUTTONUP,EVENT_LBUTTONDBLCLK,EVENT_RBUTTONDBLCLK,EVENT_MBUTTONDBLCLK,EVENT_MOUSEWHEEL,EVENT_MOUSEHWHEEL,EVENT_FLAG_LBUTTON,EVENT_FLAG_RBUTTON,EVENT_FLAG_MBUTTON,EVENT_FLAG_CTRLKEY,EVENT_FLAG_SHIFTKEY } = cv;
export { EVENT_RBUTTONDOWN,EVENT_MBUTTONDOWN,EVENT_LBUTTONUP,EVENT_RBUTTONUP,EVENT_MBUTTONUP,EVENT_LBUTTONDBLCLK,EVENT_RBUTTONDBLCLK,EVENT_MBUTTONDBLCLK,EVENT_MOUSEWHEEL,EVENT_MOUSEHWHEEL,EVENT_FLAG_LBUTTON,EVENT_FLAG_RBUTTON,EVENT_FLAG_MBUTTON,EVENT_FLAG_CTRLKEY,EVENT_FLAG_SHIFTKEY };
const { EVENT_FLAG_ALTKEY,QT_FONT_LIGHT,QT_FONT_NORMAL,QT_FONT_DEMIBOLD,QT_FONT_BOLD,QT_FONT_BLACK,QT_STYLE_NORMAL,QT_STYLE_ITALIC,QT_STYLE_OBLIQUE,QT_PUSH_BUTTON,QT_CHECKBOX,QT_RADIOBOX,QT_NEW_BUTTONBAR,setWindowProperty,getWindowProperty } = cv;
export { EVENT_FLAG_ALTKEY,QT_FONT_LIGHT,QT_FONT_NORMAL,QT_FONT_DEMIBOLD,QT_FONT_BOLD,QT_FONT_BLACK,QT_STYLE_NORMAL,QT_STYLE_ITALIC,QT_STYLE_OBLIQUE,QT_PUSH_BUTTON,QT_CHECKBOX,QT_RADIOBOX,QT_NEW_BUTTONBAR,setWindowProperty,getWindowProperty };
const { setWindowTitle,moveWindow,namedWindow,resizeWindow,startWindowThread,REGULAR,LMEDS,RANSAC,RHO,SOLVEPNP_ITERATIVE,SOLVEPNP_EPNP,SOLVEPNP_P3P,SOLVEPNP_DLS,SOLVEPNP_UPNP,CALIB_CB_ADAPTIVE_THRESH } = cv;
export { setWindowTitle,moveWindow,namedWindow,resizeWindow,startWindowThread,REGULAR,LMEDS,RANSAC,RHO,SOLVEPNP_ITERATIVE,SOLVEPNP_EPNP,SOLVEPNP_P3P,SOLVEPNP_DLS,SOLVEPNP_UPNP,CALIB_CB_ADAPTIVE_THRESH };
const { CALIB_CB_NORMALIZE_IMAGE,CALIB_CB_FILTER_QUADS,CALIB_CB_FAST_CHECK,CALIB_CB_SYMMETRIC_GRID,CALIB_CB_ASYMMETRIC_GRID,CALIB_CB_CLUSTERING,CALIB_USE_INTRINSIC_GUESS,CALIB_FIX_ASPECT_RATIO,CALIB_FIX_PRINCIPAL_POINT,CALIB_ZERO_TANGENT_DIST,CALIB_FIX_FOCAL_LENGTH,CALIB_FIX_K1,CALIB_FIX_K2,CALIB_FIX_K3,CALIB_FIX_K4 } = cv;
export { CALIB_CB_NORMALIZE_IMAGE,CALIB_CB_FILTER_QUADS,CALIB_CB_FAST_CHECK,CALIB_CB_SYMMETRIC_GRID,CALIB_CB_ASYMMETRIC_GRID,CALIB_CB_CLUSTERING,CALIB_USE_INTRINSIC_GUESS,CALIB_FIX_ASPECT_RATIO,CALIB_FIX_PRINCIPAL_POINT,CALIB_ZERO_TANGENT_DIST,CALIB_FIX_FOCAL_LENGTH,CALIB_FIX_K1,CALIB_FIX_K2,CALIB_FIX_K3,CALIB_FIX_K4 };
const { CALIB_FIX_K5,CALIB_FIX_K6,CALIB_RATIONAL_MODEL,CALIB_THIN_PRISM_MODEL,CALIB_FIX_S1_S2_S3_S4,CALIB_FIX_INTRINSIC,CALIB_SAME_FOCAL_LENGTH,CALIB_ZERO_DISPARITY,CALIB_TILTED_MODEL,CALIB_FIX_TAUX_TAUY,CALIB_USE_LU,CALIB_USE_QR,SOLVEPNP_AP3P,SOLVEPNP_MAX_COUNT,CALIB_FIX_TANGENT_DIST } = cv;
export { CALIB_FIX_K5,CALIB_FIX_K6,CALIB_RATIONAL_MODEL,CALIB_THIN_PRISM_MODEL,CALIB_FIX_S1_S2_S3_S4,CALIB_FIX_INTRINSIC,CALIB_SAME_FOCAL_LENGTH,CALIB_ZERO_DISPARITY,CALIB_TILTED_MODEL,CALIB_FIX_TAUX_TAUY,CALIB_USE_LU,CALIB_USE_QR,SOLVEPNP_AP3P,SOLVEPNP_MAX_COUNT,CALIB_FIX_TANGENT_DIST };
const { FM_7POINT,FM_8POINT,FM_LMEDS,FM_RANSAC,findHomography,findHomographyAsync,composeRT,composeRTAsync,solvePnP,solvePnPAsync,solvePnPRansac,solvePnPRansacAsync,projectPoints,projectPointsAsync,initCameraMatrix2D } = cv;
export { FM_7POINT,FM_8POINT,FM_LMEDS,FM_RANSAC,findHomography,findHomographyAsync,composeRT,composeRTAsync,solvePnP,solvePnPAsync,solvePnPRansac,solvePnPRansacAsync,projectPoints,projectPointsAsync,initCameraMatrix2D };
const { initCameraMatrix2DAsync,stereoCalibrate,stereoCalibrateAsync,stereoRectifyUncalibrated,stereoRectifyUncalibratedAsync,findFundamentalMat,findFundamentalMatAsync,findEssentialMat,findEssentialMatAsync,recoverPose,recoverPoseAsync,computeCorrespondEpilines,computeCorrespondEpilinesAsync,getValidDisparityROI,getValidDisparityROIAsync } = cv;
export { initCameraMatrix2DAsync,stereoCalibrate,stereoCalibrateAsync,stereoRectifyUncalibrated,stereoRectifyUncalibratedAsync,findFundamentalMat,findFundamentalMatAsync,findEssentialMat,findEssentialMatAsync,recoverPose,recoverPoseAsync,computeCorrespondEpilines,computeCorrespondEpilinesAsync,getValidDisparityROI,getValidDisparityROIAsync };
const { estimateAffine3D,estimateAffine3DAsync,sampsonDistance,sampsonDistanceAsync,calibrateCamera,calibrateCameraAsync,calibrateCameraExtended,calibrateCameraExtendedAsync,estimateAffine2D,estimateAffine2DAsync,estimateAffinePartial2D,estimateAffinePartial2DAsync,solveP3P,solveP3PAsync,undistortPoints } = cv;
export { estimateAffine3D,estimateAffine3DAsync,sampsonDistance,sampsonDistanceAsync,calibrateCamera,calibrateCameraAsync,calibrateCameraExtended,calibrateCameraExtendedAsync,estimateAffine2D,estimateAffine2DAsync,estimateAffinePartial2D,estimateAffinePartial2DAsync,solveP3P,solveP3PAsync,undistortPoints };
const { undistortPointsAsync,DNN_BACKEND_OPENCV,DNN_BACKEND_INFERENCE_ENGINE,DNN_BACKEND_HALIDE,DNN_BACKEND_CUDA,DNN_TARGET_CPU,DNN_TARGET_OPENCL,DNN_TARGET_OPENCL_FP16,DNN_TARGET_MYRIAD,DNN_TARGET_CUDA,DNN_TARGET_CUDA_FP16,DNN_TARGET_HDDL,Net,readNetFromTensorflow,readNetFromTensorflowAsync } = cv;
export { undistortPointsAsync,DNN_BACKEND_OPENCV,DNN_BACKEND_INFERENCE_ENGINE,DNN_BACKEND_HALIDE,DNN_BACKEND_CUDA,DNN_TARGET_CPU,DNN_TARGET_OPENCL,DNN_TARGET_OPENCL_FP16,DNN_TARGET_MYRIAD,DNN_TARGET_CUDA,DNN_TARGET_CUDA_FP16,DNN_TARGET_HDDL,Net,readNetFromTensorflow,readNetFromTensorflowAsync };
const { readNetFromCaffe,readNetFromCaffeAsync,blobFromImage,blobFromImageAsync,blobFromImages,blobFromImagesAsync,readNetFromDarknet,readNetFromDarknetAsync,NMSBoxes,readNetFromONNX,readNetFromONNXAsync,readNet,readNetAsync,EigenFaceRecognizer,FisherFaceRecognizer } = cv;
export { readNetFromCaffe,readNetFromCaffeAsync,blobFromImage,blobFromImageAsync,blobFromImages,blobFromImagesAsync,readNetFromDarknet,readNetFromDarknetAsync,NMSBoxes,readNetFromONNX,readNetFromONNXAsync,readNet,readNetAsync,EigenFaceRecognizer,FisherFaceRecognizer };
const { LBPHFaceRecognizer,FacemarkAAM,FacemarkAAMData,FacemarkAAMParams,FacemarkLBF,FacemarkLBFParams,KeyPoint,KeyPointMatch,DescriptorMatch,matchFlannBased,matchBruteForce,matchBruteForceL1,matchBruteForceHamming,matchFlannBasedAsync,matchBruteForceAsync } = cv;
export { LBPHFaceRecognizer,FacemarkAAM,FacemarkAAMData,FacemarkAAMParams,FacemarkLBF,FacemarkLBFParams,KeyPoint,KeyPointMatch,DescriptorMatch,matchFlannBased,matchBruteForce,matchBruteForceL1,matchBruteForceHamming,matchFlannBasedAsync,matchBruteForceAsync };
const { matchBruteForceL1Async,matchBruteForceHammingAsync,matchBruteForceHammingLut,matchBruteForceSL2,matchBruteForceHammingLutAsync,matchBruteForceSL2Async,matchKnnFlannBased,matchKnnBruteForce,matchKnnBruteForceL1,matchKnnBruteForceHamming,matchKnnFlannBasedAsync,matchKnnBruteForceAsync,matchKnnBruteForceL1Async,matchKnnBruteForceHammingAsync,matchKnnBruteForceHammingLut } = cv;
export { matchBruteForceL1Async,matchBruteForceHammingAsync,matchBruteForceHammingLut,matchBruteForceSL2,matchBruteForceHammingLutAsync,matchBruteForceSL2Async,matchKnnFlannBased,matchKnnBruteForce,matchKnnBruteForceL1,matchKnnBruteForceHamming,matchKnnFlannBasedAsync,matchKnnBruteForceAsync,matchKnnBruteForceL1Async,matchKnnBruteForceHammingAsync,matchKnnBruteForceHammingLut };
const { matchKnnBruteForceSL2,matchKnnBruteForceHammingLutAsync,matchKnnBruteForceSL2Async,AGASTDetector,AGASTDetectorType,AKAZEDetector,AKAZEDescriptorType,BRISKDetector,BFMatcher,FASTDetector,FASTDetectorType,GFTTDetector,KAZEDetector,KAZEDiffusivityType,MSERDetector } = cv;
export { matchKnnBruteForceSL2,matchKnnBruteForceHammingLutAsync,matchKnnBruteForceSL2Async,AGASTDetector,AGASTDetectorType,AKAZEDetector,AKAZEDescriptorType,BRISKDetector,BFMatcher,FASTDetector,FASTDetectorType,GFTTDetector,KAZEDetector,KAZEDiffusivityType,MSERDetector };
const { ORBDetector,ORBScoreType,SimpleBlobDetectorParams,SimpleBlobDetector,drawKeyPoints,drawMatches,MORPH_RECT,MORPH_CROSS,MORPH_ELLIPSE,MORPH_ERODE,MORPH_DILATE,MORPH_OPEN,MORPH_CLOSE,MORPH_GRADIENT,MORPH_TOPHAT } = cv;
export { ORBDetector,ORBScoreType,SimpleBlobDetectorParams,SimpleBlobDetector,drawKeyPoints,drawMatches,MORPH_RECT,MORPH_CROSS,MORPH_ELLIPSE,MORPH_ERODE,MORPH_DILATE,MORPH_OPEN,MORPH_CLOSE,MORPH_GRADIENT,MORPH_TOPHAT };
const { MORPH_BLACKHAT,MORPH_HITMISS,INTER_NEAREST,INTER_LINEAR,INTER_CUBIC,INTER_AREA,INTER_LANCZOS4,INTER_MAX,INTER_LINEAR_EXACT,WARP_FILL_OUTLIERS,WARP_INVERSE_MAP,THRESH_BINARY,THRESH_BINARY_INV,THRESH_TRUNC,THRESH_TOZERO } = cv;
export { MORPH_BLACKHAT,MORPH_HITMISS,INTER_NEAREST,INTER_LINEAR,INTER_CUBIC,INTER_AREA,INTER_LANCZOS4,INTER_MAX,INTER_LINEAR_EXACT,WARP_FILL_OUTLIERS,WARP_INVERSE_MAP,THRESH_BINARY,THRESH_BINARY_INV,THRESH_TRUNC,THRESH_TOZERO };
const { THRESH_TOZERO_INV,THRESH_MASK,THRESH_OTSU,THRESH_TRIANGLE,ADAPTIVE_THRESH_MEAN_C,ADAPTIVE_THRESH_GAUSSIAN_C,GC_BGD,GC_FGD,GC_PR_BGD,GC_PR_FGD,GC_INIT_WITH_RECT,GC_INIT_WITH_MASK,GC_EVAL,TM_SQDIFF,TM_SQDIFF_NORMED } = cv;
export { THRESH_TOZERO_INV,THRESH_MASK,THRESH_OTSU,THRESH_TRIANGLE,ADAPTIVE_THRESH_MEAN_C,ADAPTIVE_THRESH_GAUSSIAN_C,GC_BGD,GC_FGD,GC_PR_BGD,GC_PR_FGD,GC_INIT_WITH_RECT,GC_INIT_WITH_MASK,GC_EVAL,TM_SQDIFF,TM_SQDIFF_NORMED };
const { TM_CCORR,TM_CCORR_NORMED,TM_CCOEFF,TM_CCOEFF_NORMED,DFT_INVERSE,DFT_SCALE,DFT_ROWS,DFT_COMPLEX_OUTPUT,DFT_REAL_OUTPUT,DCT_INVERSE,DCT_ROWS,HOUGH_STANDARD,HOUGH_PROBABILISTIC,HOUGH_MULTI_SCALE,HOUGH_GRADIENT } = cv;
export { TM_CCORR,TM_CCORR_NORMED,TM_CCOEFF,TM_CCOEFF_NORMED,DFT_INVERSE,DFT_SCALE,DFT_ROWS,DFT_COMPLEX_OUTPUT,DFT_REAL_OUTPUT,DCT_INVERSE,DCT_ROWS,HOUGH_STANDARD,HOUGH_PROBABILISTIC,HOUGH_MULTI_SCALE,HOUGH_GRADIENT };
const { HISTCMP_CORREL,HISTCMP_CHISQR,HISTCMP_INTERSECT,HISTCMP_BHATTACHARYYA,HISTCMP_HELLINGER,HISTCMP_CHISQR_ALT,HISTCMP_KL_DIV,FLOODFILL_FIXED_RANGE,FLOODFILL_MASK_ONLY,COLOR_BGR2BGRA,COLOR_RGB2RGBA,COLOR_BGRA2BGR,COLOR_RGBA2RGB,COLOR_BGR2RGBA,COLOR_RGB2BGRA } = cv;
export { HISTCMP_CORREL,HISTCMP_CHISQR,HISTCMP_INTERSECT,HISTCMP_BHATTACHARYYA,HISTCMP_HELLINGER,HISTCMP_CHISQR_ALT,HISTCMP_KL_DIV,FLOODFILL_FIXED_RANGE,FLOODFILL_MASK_ONLY,COLOR_BGR2BGRA,COLOR_RGB2RGBA,COLOR_BGRA2BGR,COLOR_RGBA2RGB,COLOR_BGR2RGBA,COLOR_RGB2BGRA };
const { COLOR_RGBA2BGR,COLOR_BGRA2RGB,COLOR_BGR2RGB,COLOR_RGB2BGR,COLOR_BGRA2RGBA,COLOR_RGBA2BGRA,COLOR_BGR2GRAY,COLOR_RGB2GRAY,COLOR_GRAY2BGR,COLOR_GRAY2RGB,COLOR_GRAY2BGRA,COLOR_GRAY2RGBA,COLOR_BGRA2GRAY,COLOR_RGBA2GRAY,COLOR_BGR2BGR565 } = cv;
export { COLOR_RGBA2BGR,COLOR_BGRA2RGB,COLOR_BGR2RGB,COLOR_RGB2BGR,COLOR_BGRA2RGBA,COLOR_RGBA2BGRA,COLOR_BGR2GRAY,COLOR_RGB2GRAY,COLOR_GRAY2BGR,COLOR_GRAY2RGB,COLOR_GRAY2BGRA,COLOR_GRAY2RGBA,COLOR_BGRA2GRAY,COLOR_RGBA2GRAY,COLOR_BGR2BGR565 };
const { COLOR_RGB2BGR565,COLOR_BGR5652BGR,COLOR_BGR5652RGB,COLOR_BGRA2BGR565,COLOR_RGBA2BGR565,COLOR_BGR5652BGRA,COLOR_BGR5652RGBA,COLOR_GRAY2BGR565,COLOR_BGR5652GRAY,COLOR_BGR2BGR555,COLOR_RGB2BGR555,COLOR_BGR5552BGR,COLOR_BGR5552RGB,COLOR_BGRA2BGR555,COLOR_RGBA2BGR555 } = cv;
export { COLOR_RGB2BGR565,COLOR_BGR5652BGR,COLOR_BGR5652RGB,COLOR_BGRA2BGR565,COLOR_RGBA2BGR565,COLOR_BGR5652BGRA,COLOR_BGR5652RGBA,COLOR_GRAY2BGR565,COLOR_BGR5652GRAY,COLOR_BGR2BGR555,COLOR_RGB2BGR555,COLOR_BGR5552BGR,COLOR_BGR5552RGB,COLOR_BGRA2BGR555,COLOR_RGBA2BGR555 };
const { COLOR_BGR5552BGRA,COLOR_BGR5552RGBA,COLOR_GRAY2BGR555,COLOR_BGR5552GRAY,COLOR_BGR2XYZ,COLOR_RGB2XYZ,COLOR_XYZ2BGR,COLOR_XYZ2RGB,COLOR_BGR2YCrCb,COLOR_RGB2YCrCb,COLOR_YCrCb2BGR,COLOR_YCrCb2RGB,COLOR_BGR2HSV,COLOR_RGB2HSV,COLOR_BGR2Lab } = cv;
export { COLOR_BGR5552BGRA,COLOR_BGR5552RGBA,COLOR_GRAY2BGR555,COLOR_BGR5552GRAY,COLOR_BGR2XYZ,COLOR_RGB2XYZ,COLOR_XYZ2BGR,COLOR_XYZ2RGB,COLOR_BGR2YCrCb,COLOR_RGB2YCrCb,COLOR_YCrCb2BGR,COLOR_YCrCb2RGB,COLOR_BGR2HSV,COLOR_RGB2HSV,COLOR_BGR2Lab };
const { COLOR_RGB2Lab,COLOR_BGR2Luv,COLOR_RGB2Luv,COLOR_BGR2HLS,COLOR_RGB2HLS,COLOR_HSV2BGR,COLOR_HSV2RGB,COLOR_Lab2BGR,COLOR_Lab2RGB,COLOR_Luv2BGR,COLOR_Luv2RGB,COLOR_HLS2BGR,COLOR_HLS2RGB,COLOR_BGR2HSV_FULL,COLOR_RGB2HSV_FULL } = cv;
export { COLOR_RGB2Lab,COLOR_BGR2Luv,COLOR_RGB2Luv,COLOR_BGR2HLS,COLOR_RGB2HLS,COLOR_HSV2BGR,COLOR_HSV2RGB,COLOR_Lab2BGR,COLOR_Lab2RGB,COLOR_Luv2BGR,COLOR_Luv2RGB,COLOR_HLS2BGR,COLOR_HLS2RGB,COLOR_BGR2HSV_FULL,COLOR_RGB2HSV_FULL };
const { COLOR_BGR2HLS_FULL,COLOR_RGB2HLS_FULL,COLOR_HSV2BGR_FULL,COLOR_HSV2RGB_FULL,COLOR_HLS2BGR_FULL,COLOR_HLS2RGB_FULL,COLOR_LBGR2Lab,COLOR_LRGB2Lab,COLOR_LBGR2Luv,COLOR_LRGB2Luv,COLOR_Lab2LBGR,COLOR_Lab2LRGB,COLOR_Luv2LBGR,COLOR_Luv2LRGB,COLOR_BGR2YUV } = cv;
export { COLOR_BGR2HLS_FULL,COLOR_RGB2HLS_FULL,COLOR_HSV2BGR_FULL,COLOR_HSV2RGB_FULL,COLOR_HLS2BGR_FULL,COLOR_HLS2RGB_FULL,COLOR_LBGR2Lab,COLOR_LRGB2Lab,COLOR_LBGR2Luv,COLOR_LRGB2Luv,COLOR_Lab2LBGR,COLOR_Lab2LRGB,COLOR_Luv2LBGR,COLOR_Luv2LRGB,COLOR_BGR2YUV };
const { COLOR_RGB2YUV,COLOR_YUV2BGR,COLOR_YUV2RGB,COLOR_YUV2RGB_NV12,COLOR_YUV2BGR_NV12,COLOR_YUV2RGB_NV21,COLOR_YUV2BGR_NV21,COLOR_YUV420sp2RGB,COLOR_YUV420sp2BGR,COLOR_YUV2RGBA_NV12,COLOR_YUV2BGRA_NV12,COLOR_YUV2RGBA_NV21,COLOR_YUV2BGRA_NV21,COLOR_YUV420sp2RGBA,COLOR_YUV420sp2BGRA } = cv;
export { COLOR_RGB2YUV,COLOR_YUV2BGR,COLOR_YUV2RGB,COLOR_YUV2RGB_NV12,COLOR_YUV2BGR_NV12,COLOR_YUV2RGB_NV21,COLOR_YUV2BGR_NV21,COLOR_YUV420sp2RGB,COLOR_YUV420sp2BGR,COLOR_YUV2RGBA_NV12,COLOR_YUV2BGRA_NV12,COLOR_YUV2RGBA_NV21,COLOR_YUV2BGRA_NV21,COLOR_YUV420sp2RGBA,COLOR_YUV420sp2BGRA };
const { COLOR_YUV2RGB_YV12,COLOR_YUV2BGR_YV12,COLOR_YUV2RGB_IYUV,COLOR_YUV2BGR_IYUV,COLOR_YUV2RGB_I420,COLOR_YUV2BGR_I420,COLOR_YUV420p2RGB,COLOR_YUV420p2BGR,COLOR_YUV2RGBA_YV12,COLOR_YUV2BGRA_YV12,COLOR_YUV2RGBA_IYUV,COLOR_YUV2BGRA_IYUV,COLOR_YUV2RGBA_I420,COLOR_YUV2BGRA_I420,COLOR_YUV420p2RGBA } = cv;
export { COLOR_YUV2RGB_YV12,COLOR_YUV2BGR_YV12,COLOR_YUV2RGB_IYUV,COLOR_YUV2BGR_IYUV,COLOR_YUV2RGB_I420,COLOR_YUV2BGR_I420,COLOR_YUV420p2RGB,COLOR_YUV420p2BGR,COLOR_YUV2RGBA_YV12,COLOR_YUV2BGRA_YV12,COLOR_YUV2RGBA_IYUV,COLOR_YUV2BGRA_IYUV,COLOR_YUV2RGBA_I420,COLOR_YUV2BGRA_I420,COLOR_YUV420p2RGBA };
const { COLOR_YUV420p2BGRA,COLOR_YUV2GRAY_420,COLOR_YUV2GRAY_NV21,COLOR_YUV2GRAY_NV12,COLOR_YUV2GRAY_YV12,COLOR_YUV2GRAY_IYUV,COLOR_YUV2GRAY_I420,COLOR_YUV420sp2GRAY,COLOR_YUV420p2GRAY,COLOR_YUV2RGB_UYVY,COLOR_YUV2BGR_UYVY,COLOR_YUV2RGB_Y422,COLOR_YUV2BGR_Y422,COLOR_YUV2RGB_UYNV,COLOR_YUV2BGR_UYNV } = cv;
export { COLOR_YUV420p2BGRA,COLOR_YUV2GRAY_420,COLOR_YUV2GRAY_NV21,COLOR_YUV2GRAY_NV12,COLOR_YUV2GRAY_YV12,COLOR_YUV2GRAY_IYUV,COLOR_YUV2GRAY_I420,COLOR_YUV420sp2GRAY,COLOR_YUV420p2GRAY,COLOR_YUV2RGB_UYVY,COLOR_YUV2BGR_UYVY,COLOR_YUV2RGB_Y422,COLOR_YUV2BGR_Y422,COLOR_YUV2RGB_UYNV,COLOR_YUV2BGR_UYNV };
const { COLOR_YUV2RGBA_UYVY,COLOR_YUV2BGRA_UYVY,COLOR_YUV2RGBA_Y422,COLOR_YUV2BGRA_Y422,COLOR_YUV2RGBA_UYNV,COLOR_YUV2BGRA_UYNV,COLOR_YUV2RGB_YUY2,COLOR_YUV2BGR_YUY2,COLOR_YUV2RGB_YVYU,COLOR_YUV2BGR_YVYU,COLOR_YUV2RGB_YUYV,COLOR_YUV2BGR_YUYV,COLOR_YUV2RGB_YUNV,COLOR_YUV2BGR_YUNV,COLOR_YUV2RGBA_YUY2 } = cv;
export { COLOR_YUV2RGBA_UYVY,COLOR_YUV2BGRA_UYVY,COLOR_YUV2RGBA_Y422,COLOR_YUV2BGRA_Y422,COLOR_YUV2RGBA_UYNV,COLOR_YUV2BGRA_UYNV,COLOR_YUV2RGB_YUY2,COLOR_YUV2BGR_YUY2,COLOR_YUV2RGB_YVYU,COLOR_YUV2BGR_YVYU,COLOR_YUV2RGB_YUYV,COLOR_YUV2BGR_YUYV,COLOR_YUV2RGB_YUNV,COLOR_YUV2BGR_YUNV,COLOR_YUV2RGBA_YUY2 };
const { COLOR_YUV2BGRA_YUY2,COLOR_YUV2RGBA_YVYU,COLOR_YUV2BGRA_YVYU,COLOR_YUV2RGBA_YUYV,COLOR_YUV2BGRA_YUYV,COLOR_YUV2RGBA_YUNV,COLOR_YUV2BGRA_YUNV,COLOR_YUV2GRAY_UYVY,COLOR_YUV2GRAY_YUY2,COLOR_YUV2GRAY_Y422,COLOR_YUV2GRAY_UYNV,COLOR_YUV2GRAY_YVYU,COLOR_YUV2GRAY_YUYV,COLOR_YUV2GRAY_YUNV,COLOR_RGBA2mRGBA } = cv;
export { COLOR_YUV2BGRA_YUY2,COLOR_YUV2RGBA_YVYU,COLOR_YUV2BGRA_YVYU,COLOR_YUV2RGBA_YUYV,COLOR_YUV2BGRA_YUYV,COLOR_YUV2RGBA_YUNV,COLOR_YUV2BGRA_YUNV,COLOR_YUV2GRAY_UYVY,COLOR_YUV2GRAY_YUY2,COLOR_YUV2GRAY_Y422,COLOR_YUV2GRAY_UYNV,COLOR_YUV2GRAY_YVYU,COLOR_YUV2GRAY_YUYV,COLOR_YUV2GRAY_YUNV,COLOR_RGBA2mRGBA };
const { COLOR_mRGBA2RGBA,COLOR_RGB2YUV_I420,COLOR_BGR2YUV_I420,COLOR_RGB2YUV_IYUV,COLOR_BGR2YUV_IYUV,COLOR_RGBA2YUV_I420,COLOR_BGRA2YUV_I420,COLOR_RGBA2YUV_IYUV,COLOR_BGRA2YUV_IYUV,COLOR_RGB2YUV_YV12,COLOR_BGR2YUV_YV12,COLOR_RGBA2YUV_YV12,COLOR_BGRA2YUV_YV12,COLOR_BayerBG2BGR,COLOR_BayerGB2BGR } = cv;
export { COLOR_mRGBA2RGBA,COLOR_RGB2YUV_I420,COLOR_BGR2YUV_I420,COLOR_RGB2YUV_IYUV,COLOR_BGR2YUV_IYUV,COLOR_RGBA2YUV_I420,COLOR_BGRA2YUV_I420,COLOR_RGBA2YUV_IYUV,COLOR_BGRA2YUV_IYUV,COLOR_RGB2YUV_YV12,COLOR_BGR2YUV_YV12,COLOR_RGBA2YUV_YV12,COLOR_BGRA2YUV_YV12,COLOR_BayerBG2BGR,COLOR_BayerGB2BGR };
const { COLOR_BayerRG2BGR,COLOR_BayerGR2BGR,COLOR_BayerBG2RGB,COLOR_BayerGB2RGB,COLOR_BayerRG2RGB,COLOR_BayerGR2RGB,COLOR_BayerBG2GRAY,COLOR_BayerGB2GRAY,COLOR_BayerRG2GRAY,COLOR_BayerGR2GRAY,COLOR_BayerBG2BGR_VNG,COLOR_BayerGB2BGR_VNG,COLOR_BayerRG2BGR_VNG,COLOR_BayerGR2BGR_VNG,COLOR_BayerBG2RGB_VNG } = cv;
export { COLOR_BayerRG2BGR,COLOR_BayerGR2BGR,COLOR_BayerBG2RGB,COLOR_BayerGB2RGB,COLOR_BayerRG2RGB,COLOR_BayerGR2RGB,COLOR_BayerBG2GRAY,COLOR_BayerGB2GRAY,COLOR_BayerRG2GRAY,COLOR_BayerGR2GRAY,COLOR_BayerBG2BGR_VNG,COLOR_BayerGB2BGR_VNG,COLOR_BayerRG2BGR_VNG,COLOR_BayerGR2BGR_VNG,COLOR_BayerBG2RGB_VNG };
const { COLOR_BayerGB2RGB_VNG,COLOR_BayerRG2RGB_VNG,COLOR_BayerGR2RGB_VNG,COLOR_BayerBG2BGR_EA,COLOR_BayerGB2BGR_EA,COLOR_BayerRG2BGR_EA,COLOR_BayerGR2BGR_EA,COLOR_BayerBG2RGB_EA,COLOR_BayerGB2RGB_EA,COLOR_BayerRG2RGB_EA,COLOR_BayerGR2RGB_EA,COLOR_COLORCVT_MAX,CC_STAT_LEFT,CC_STAT_TOP,CC_STAT_WIDTH } = cv;
export { COLOR_BayerGB2RGB_VNG,COLOR_BayerRG2RGB_VNG,COLOR_BayerGR2RGB_VNG,COLOR_BayerBG2BGR_EA,COLOR_BayerGB2BGR_EA,COLOR_BayerRG2BGR_EA,COLOR_BayerGR2BGR_EA,COLOR_BayerBG2RGB_EA,COLOR_BayerGB2RGB_EA,COLOR_BayerRG2RGB_EA,COLOR_BayerGR2RGB_EA,COLOR_COLORCVT_MAX,CC_STAT_LEFT,CC_STAT_TOP,CC_STAT_WIDTH };
const { CC_STAT_HEIGHT,CC_STAT_AREA,CC_STAT_MAX,CHAIN_APPROX_NONE,CHAIN_APPROX_SIMPLE,CHAIN_APPROX_TC89_L1,CHAIN_APPROX_TC89_KCOS,DIST_USER,DIST_L1,DIST_L2,DIST_C,DIST_L12,DIST_FAIR,DIST_WELSCH,DIST_HUBER } = cv;
export { CC_STAT_HEIGHT,CC_STAT_AREA,CC_STAT_MAX,CHAIN_APPROX_NONE,CHAIN_APPROX_SIMPLE,CHAIN_APPROX_TC89_L1,CHAIN_APPROX_TC89_KCOS,DIST_USER,DIST_L1,DIST_L2,DIST_C,DIST_L12,DIST_FAIR,DIST_WELSCH,DIST_HUBER };
const { DIST_MASK_3,DIST_MASK_5,DIST_MASK_PRECISE,DIST_LABEL_CCOMP,DIST_LABEL_PIXEL,RETR_EXTERNAL,RETR_LIST,RETR_CCOMP,RETR_TREE,RETR_FLOODFILL,CONTOURS_MATCH_I1,CONTOURS_MATCH_I2,CONTOURS_MATCH_I3,FONT_HERSHEY_SIMPLEX,FONT_HERSHEY_PLAIN } = cv;
export { DIST_MASK_3,DIST_MASK_5,DIST_MASK_PRECISE,DIST_LABEL_CCOMP,DIST_LABEL_PIXEL,RETR_EXTERNAL,RETR_LIST,RETR_CCOMP,RETR_TREE,RETR_FLOODFILL,CONTOURS_MATCH_I1,CONTOURS_MATCH_I2,CONTOURS_MATCH_I3,FONT_HERSHEY_SIMPLEX,FONT_HERSHEY_PLAIN };
const { FONT_HERSHEY_DUPLEX,FONT_HERSHEY_COMPLEX,FONT_HERSHEY_TRIPLEX,FONT_HERSHEY_COMPLEX_SMALL,FONT_HERSHEY_SCRIPT_SIMPLEX,FONT_HERSHEY_SCRIPT_COMPLEX,FONT_ITALIC,FILLED,LINE_4,LINE_8,LINE_AA,COLORMAP_AUTUMN,COLORMAP_BONE,COLORMAP_JET,COLORMAP_WINTER } = cv;
export { FONT_HERSHEY_DUPLEX,FONT_HERSHEY_COMPLEX,FONT_HERSHEY_TRIPLEX,FONT_HERSHEY_COMPLEX_SMALL,FONT_HERSHEY_SCRIPT_SIMPLEX,FONT_HERSHEY_SCRIPT_COMPLEX,FONT_ITALIC,FILLED,LINE_4,LINE_8,LINE_AA,COLORMAP_AUTUMN,COLORMAP_BONE,COLORMAP_JET,COLORMAP_WINTER };
const { COLORMAP_RAINBOW,COLORMAP_OCEAN,COLORMAP_SUMMER,COLORMAP_SPRING,COLORMAP_COOL,COLORMAP_HSV,COLORMAP_PINK,COLORMAP_HOT,COLORMAP_PARULA,getStructuringElement,getRotationMatrix2D,plot1DHist,fitLine,getAffineTransform,getPerspectiveTransform } = cv;
export { COLORMAP_RAINBOW,COLORMAP_OCEAN,COLORMAP_SUMMER,COLORMAP_SPRING,COLORMAP_COOL,COLORMAP_HSV,COLORMAP_PINK,COLORMAP_HOT,COLORMAP_PARULA,getStructuringElement,getRotationMatrix2D,plot1DHist,fitLine,getAffineTransform,getPerspectiveTransform };
const { getTextSize,getTextSizeAsync,applyColorMap,applyColorMapAsync,canny,cannyAsync,goodFeaturesToTrack,goodFeaturesToTrackAsync,blur,blurAsync,gaussianBlur,gaussianBlurAsync,medianBlur,medianBlurAsync,accumulate } = cv;
export { getTextSize,getTextSizeAsync,applyColorMap,applyColorMapAsync,canny,cannyAsync,goodFeaturesToTrack,goodFeaturesToTrackAsync,blur,blurAsync,gaussianBlur,gaussianBlurAsync,medianBlur,medianBlurAsync,accumulate };
const { accumulateAsync,accumulateProduct,accumulateProductAsync,accumulateSquare,accumulateSquareAsync,accumulateWeighted,accumulateWeightedAsync,calcHist,calcHistAsync,Moments,Contour,CAP_PROP_POS_MSEC,CAP_PROP_POS_FRAMES,CAP_PROP_POS_AVI_RATIO,CAP_PROP_FRAME_WIDTH } = cv;
export { accumulateAsync,accumulateProduct,accumulateProductAsync,accumulateSquare,accumulateSquareAsync,accumulateWeighted,accumulateWeightedAsync,calcHist,calcHistAsync,Moments,Contour,CAP_PROP_POS_MSEC,CAP_PROP_POS_FRAMES,CAP_PROP_POS_AVI_RATIO,CAP_PROP_FRAME_WIDTH };
const { CAP_PROP_FRAME_HEIGHT,CAP_PROP_FPS,CAP_PROP_FOURCC,CAP_PROP_FRAME_COUNT,CAP_PROP_FORMAT,CAP_PROP_MODE,CAP_PROP_BRIGHTNESS,CAP_PROP_CONTRAST,CAP_PROP_SATURATION,CAP_PROP_HUE,CAP_PROP_GAIN,CAP_PROP_EXPOSURE,CAP_PROP_CONVERT_RGB,CAP_PROP_WHITE_BALANCE_BLUE_U,CAP_PROP_RECTIFICATION } = cv;
export { CAP_PROP_FRAME_HEIGHT,CAP_PROP_FPS,CAP_PROP_FOURCC,CAP_PROP_FRAME_COUNT,CAP_PROP_FORMAT,CAP_PROP_MODE,CAP_PROP_BRIGHTNESS,CAP_PROP_CONTRAST,CAP_PROP_SATURATION,CAP_PROP_HUE,CAP_PROP_GAIN,CAP_PROP_EXPOSURE,CAP_PROP_CONVERT_RGB,CAP_PROP_WHITE_BALANCE_BLUE_U,CAP_PROP_RECTIFICATION };
const { CAP_PROP_MONOCHROME,CAP_PROP_SHARPNESS,CAP_PROP_AUTO_EXPOSURE,CAP_PROP_GAMMA,CAP_PROP_TEMPERATURE,CAP_PROP_TRIGGER,CAP_PROP_TRIGGER_DELAY,CAP_PROP_WHITE_BALANCE_RED_V,CAP_PROP_ZOOM,CAP_PROP_FOCUS,CAP_PROP_GUID,CAP_PROP_ISO_SPEED,CAP_PROP_BACKLIGHT,CAP_PROP_PAN,CAP_PROP_TILT } = cv;
export { CAP_PROP_MONOCHROME,CAP_PROP_SHARPNESS,CAP_PROP_AUTO_EXPOSURE,CAP_PROP_GAMMA,CAP_PROP_TEMPERATURE,CAP_PROP_TRIGGER,CAP_PROP_TRIGGER_DELAY,CAP_PROP_WHITE_BALANCE_RED_V,CAP_PROP_ZOOM,CAP_PROP_FOCUS,CAP_PROP_GUID,CAP_PROP_ISO_SPEED,CAP_PROP_BACKLIGHT,CAP_PROP_PAN,CAP_PROP_TILT };
const { CAP_PROP_ROLL,CAP_PROP_IRIS,CAP_PROP_SETTINGS,CAP_PROP_BUFFERSIZE,CAP_PROP_AUTOFOCUS,CAP_ANY,CAP_VFW,CAP_V4L,CAP_V4L2,CAP_FIREWIRE,CAP_IEEE1394,CAP_DC1394,CAP_CMU1394,CAP_QT,CAP_UNICAP } = cv;
export { CAP_PROP_ROLL,CAP_PROP_IRIS,CAP_PROP_SETTINGS,CAP_PROP_BUFFERSIZE,CAP_PROP_AUTOFOCUS,CAP_ANY,CAP_VFW,CAP_V4L,CAP_V4L2,CAP_FIREWIRE,CAP_IEEE1394,CAP_DC1394,CAP_CMU1394,CAP_QT,CAP_UNICAP };
const { CAP_DSHOW,CAP_PVAPI,CAP_OPENNI,CAP_OPENNI_ASUS,CAP_ANDROID,CAP_XIAPI,CAP_AVFOUNDATION,CAP_GIGANETIX,CAP_MSMF,CAP_WINRT,CAP_INTELPERC,CAP_OPENNI2,CAP_OPENNI2_ASUS,CAP_GPHOTO2,CAP_GSTREAMER } = cv;
export { CAP_DSHOW,CAP_PVAPI,CAP_OPENNI,CAP_OPENNI_ASUS,CAP_ANDROID,CAP_XIAPI,CAP_AVFOUNDATION,CAP_GIGANETIX,CAP_MSMF,CAP_WINRT,CAP_INTELPERC,CAP_OPENNI2,CAP_OPENNI2_ASUS,CAP_GPHOTO2,CAP_GSTREAMER };
const { CAP_FFMPEG,CAP_IMAGES,CAP_ARAVIS,VIDEOWRITER_PROP_QUALITY,VIDEOWRITER_PROP_FRAMEBYTES,VIDEOWRITER_PROP_NSTRIPES,VideoCapture,VideoWriter,imread,imshow,imshowWait,imwrite,waitKey,waitKeyEx,imencode } = cv;
export { CAP_FFMPEG,CAP_IMAGES,CAP_ARAVIS,VIDEOWRITER_PROP_QUALITY,VIDEOWRITER_PROP_FRAMEBYTES,VIDEOWRITER_PROP_NSTRIPES,VideoCapture,VideoWriter,imread,imshow,imshowWait,imwrite,waitKey,waitKeyEx,imencode };
const { imdecode,destroyWindow,destroyAllWindows,imreadAsync,imwriteAsync,imencodeAsync,imdecodeAsync,IMREAD_UNCHANGED,IMREAD_GRAYSCALE,IMREAD_COLOR,IMREAD_ANYDEPTH,IMREAD_ANYCOLOR,IMREAD_LOAD_GDAL,IMWRITE_JPEG_QUALITY,IMWRITE_JPEG_PROGRESSIVE } = cv;
export { imdecode,destroyWindow,destroyAllWindows,imreadAsync,imwriteAsync,imencodeAsync,imdecodeAsync,IMREAD_UNCHANGED,IMREAD_GRAYSCALE,IMREAD_COLOR,IMREAD_ANYDEPTH,IMREAD_ANYCOLOR,IMREAD_LOAD_GDAL,IMWRITE_JPEG_QUALITY,IMWRITE_JPEG_PROGRESSIVE };
const { IMWRITE_JPEG_OPTIMIZE,IMWRITE_JPEG_RST_INTERVAL,IMWRITE_JPEG_LUMA_QUALITY,IMWRITE_JPEG_CHROMA_QUALITY,IMWRITE_PNG_COMPRESSION,IMWRITE_PNG_STRATEGY,IMWRITE_PNG_BILEVEL,IMWRITE_PXM_BINARY,IMWRITE_WEBP_QUALITY,IMREAD_REDUCED_GRAYSCALE_2,IMREAD_REDUCED_COLOR_2,IMREAD_REDUCED_GRAYSCALE_4,IMREAD_REDUCED_COLOR_4,IMREAD_REDUCED_GRAYSCALE_8,IMREAD_REDUCED_COLOR_8 } = cv;
export { IMWRITE_JPEG_OPTIMIZE,IMWRITE_JPEG_RST_INTERVAL,IMWRITE_JPEG_LUMA_QUALITY,IMWRITE_JPEG_CHROMA_QUALITY,IMWRITE_PNG_COMPRESSION,IMWRITE_PNG_STRATEGY,IMWRITE_PNG_BILEVEL,IMWRITE_PXM_BINARY,IMWRITE_WEBP_QUALITY,IMREAD_REDUCED_GRAYSCALE_2,IMREAD_REDUCED_COLOR_2,IMREAD_REDUCED_GRAYSCALE_4,IMREAD_REDUCED_COLOR_4,IMREAD_REDUCED_GRAYSCALE_8,IMREAD_REDUCED_COLOR_8 };
const { IMREAD_IGNORE_ORIENTATION,IMWRITE_PAM_TUPLETYPE,IMWRITE_PAM_FORMAT_NULL,IMWRITE_PAM_FORMAT_BLACKANDWHITE,IMWRITE_PAM_FORMAT_GRAYSCALE,IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA,IMWRITE_PAM_FORMAT_RGB,IMWRITE_PAM_FORMAT_RGB_ALPHA,IMWRITE_PNG_STRATEGY_DEFAULT,IMWRITE_PNG_STRATEGY_FILTERED,IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY,IMWRITE_PNG_STRATEGY_RLE,IMWRITE_PNG_STRATEGY_FIXED,ml,statModel } = cv;
export { IMREAD_IGNORE_ORIENTATION,IMWRITE_PAM_TUPLETYPE,IMWRITE_PAM_FORMAT_NULL,IMWRITE_PAM_FORMAT_BLACKANDWHITE,IMWRITE_PAM_FORMAT_GRAYSCALE,IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA,IMWRITE_PAM_FORMAT_RGB,IMWRITE_PAM_FORMAT_RGB_ALPHA,IMWRITE_PNG_STRATEGY_DEFAULT,IMWRITE_PNG_STRATEGY_FILTERED,IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY,IMWRITE_PNG_STRATEGY_RLE,IMWRITE_PNG_STRATEGY_FIXED,ml,statModel };
const { TrainData,ParamGrid,StatModel,SVM,CascadeClassifier,HOGDescriptor,HOGHistogramNormType,DetectionROI,INPAINT_NS,INPAINT_TELEA,NORMAL_CLONE,MIXED_CLONE,MONOCHROME_TRANSFER,fastNlMeansDenoisingColored,fastNlMeansDenoisingColoredAsync } = cv;
export { TrainData,ParamGrid,StatModel,SVM,CascadeClassifier,HOGDescriptor,HOGHistogramNormType,DetectionROI,INPAINT_NS,INPAINT_TELEA,NORMAL_CLONE,MIXED_CLONE,MONOCHROME_TRANSFER,fastNlMeansDenoisingColored,fastNlMeansDenoisingColoredAsync };
const { inpaint,inpaintAsync,seamlessClone,seamlessCloneAsync,OCRHMMDecoder,OCRHMMClassifier,loadOCRHMMClassifierNM,loadOCRHMMClassifierNMAsync,loadOCRHMMClassifierCNN,loadOCRHMMClassifierCNNAsync,createOCRHMMTransitionsTable,createOCRHMMTransitionsTableAsync,TrackerBoostingParams,TrackerBoosting,TrackerMedianFlow } = cv;
export { inpaint,inpaintAsync,seamlessClone,seamlessCloneAsync,OCRHMMDecoder,OCRHMMClassifier,loadOCRHMMClassifierNM,loadOCRHMMClassifierNMAsync,loadOCRHMMClassifierCNN,loadOCRHMMClassifierCNNAsync,createOCRHMMTransitionsTable,createOCRHMMTransitionsTableAsync,TrackerBoostingParams,TrackerBoosting,TrackerMedianFlow };
const { TrackerMILParams,TrackerMIL,TrackerTLD,TrackerKCFParams,TrackerKCF,MultiTracker,trackerKCFModes,TrackerGOTURN,TrackerNano,TrackerMOSSE,TrackerCSRTParams,TrackerCSRT,BackgroundSubtractorMOG2,BackgroundSubtractorKNN,SIFTDetector,SURFDetector } = cv;
export { TrackerMILParams,TrackerMIL,TrackerTLD,TrackerKCFParams,TrackerKCF,MultiTracker,trackerKCFModes,TrackerGOTURN,TrackerNano,TrackerMOSSE,TrackerCSRTParams,TrackerCSRT,BackgroundSubtractorMOG2,BackgroundSubtractorKNN,SIFTDetector,SURFDetector };
const { SuperpixelSEEDS,SuperpixelSLIC,SuperpixelLSC,SLIC,SLICO,PHash,HAAR_EYE,HAAR_EYE_TREE_EYEGLASSES,HAAR_FRONTALCATFACE,HAAR_FRONTALCATFACE_EXTENDED,HAAR_FRONTALFACE_ALT,HAAR_FRONTALFACE_ALT2,HAAR_FRONTALFACE_ALT_TREE,HAAR_FRONTALFACE_DEFAULT,HAAR_FULLBODY } = cv;
export { SuperpixelSEEDS,SuperpixelSLIC,SuperpixelLSC,SLIC,SLICO,PHash,HAAR_EYE,HAAR_EYE_TREE_EYEGLASSES,HAAR_FRONTALCATFACE,HAAR_FRONTALCATFACE_EXTENDED,HAAR_FRONTALFACE_ALT,HAAR_FRONTALFACE_ALT2,HAAR_FRONTALFACE_ALT_TREE,HAAR_FRONTALFACE_DEFAULT,HAAR_FULLBODY };
const { HAAR_LEFTEYE_2SPLITS,HAAR_LICENCE_PLATE_RUS_16STAGES,HAAR_LOWERBODY,HAAR_PROFILEFACE,HAAR_RIGHTEYE_2SPLITS,HAAR_RUSSIAN_PLATE_NUMBER,HAAR_SMILE,HAAR_UPPERBODY,LBP_FRONTALCATFACE,LBP_FRONTALFACE,LBP_FRONTALFACE_IMPROVED,LBP_PROFILEFACE,LBP_SILVERWARE,drawTextBox,drawDetection } = cv;
export { HAAR_LEFTEYE_2SPLITS,HAAR_LICENCE_PLATE_RUS_16STAGES,HAAR_LOWERBODY,HAAR_PROFILEFACE,HAAR_RIGHTEYE_2SPLITS,HAAR_RUSSIAN_PLATE_NUMBER,HAAR_SMILE,HAAR_UPPERBODY,LBP_FRONTALCATFACE,LBP_FRONTALFACE,LBP_FRONTALFACE_IMPROVED,LBP_PROFILEFACE,LBP_SILVERWARE,drawTextBox,drawDetection };
const { getVersion,getVersionString,toMatTypeName,getScoreMax,dropOverlappingZone } = cv;
export { getVersion,getVersionString,toMatTypeName,getScoreMax,dropOverlappingZone };

// TODO FIX this export mess
export const AGAST = (cv as any)['"AGAST"'];
export const AKAZE = (cv as any)['"AKAZE"'] as { DESCRIPTOR_KAZE: 3, DESCRIPTOR_MLDB_UPRIGHT: 4, DESCRIPTOR_MLDB: 5 };
export const KAZE = (cv as any)['"KAZE"'];
export const FAST = (cv as any)['"FAST"'];
export const ORB = (cv as any)['"ORB"'];

export default cv;

