import path from 'path';
import fs from 'fs';
import cv, { Mat, Rect, Vec3 } from '@u4/opencv4nodejs';
export { default as cv } from '@u4/opencv4nodejs';
import Axios from 'axios';
import ProgressBar from 'progress';
import pc from 'picocolors';
import crypto from 'crypto';

export const delay = (ms: number): Promise<void> => new Promise(resolve => setTimeout(resolve, ms));

export function getExampleDirname(...names: string[]) {
  let dir = '.';
  try {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    dir = fileURLToPath(new URL('.', import.meta.url));
  } catch {
    dir = __dirname;
  }
  if (!names.length)
    return dir;
  return path.resolve(dir, ...names);
}

export function getCachedFile(localName: string, url: string, opts?: { notice?: string, noProgress?: boolean }): Promise<string> {
  opts = opts || {};
  const localFile = getExampleDirname(localName);
  if (fs.existsSync(localFile)) {
    return Promise.resolve(localFile);
  }
  if (opts.notice)
    console.log(opts.notice);
  console.log(`Can not find ${pc.yellow(localName)} try downloading file from ${pc.underline(pc.cyan(url))}`);
  const parent = path.dirname(localFile);
  try {
    fs.mkdirSync(parent, { recursive: true });
  } catch (e) {
    // ignore error
  }
  return new Promise<string>(async (done, reject) => {
    // console.log('Connecting server…');
    const { data, headers } = await Axios({
      url,
      method: 'GET',
      responseType: 'stream',
    });
    const totalLength = headers['content-length'] || "0";
    console.log(`Starting download ${localName}`);
    const writer = fs.createWriteStream(localFile);
    if (!opts?.noProgress) {
      const progressBar = new ProgressBar('-> downloading [:bar] :percent :etas', {
        width: 40,
        complete: '=',
        incomplete: ' ',
        renderThrottle: 1,
        total: parseInt(totalLength, 10),
      });
      data.on('data', (chunk: Buffer) => progressBar.tick(chunk.length));
    }
    data.pipe(writer);
    data.on('error', (e: unknown) => { console.log('reject', e); reject(e); });
    data.on('close', () => {
      const stats = fs.statSync(localFile);
      let size = '';
      if (stats.size < 1000)
        size = `${(stats.size)} Bytes`;
      else if (stats.size < 1024 * 1024)
        size = `${(stats.size / 1024).toFixed(2)} KB`;
      else if (stats.size < 1024 * 1024 * 1024)
        size = `${(stats.size / (1024 * 1024)).toFixed(2)} MB`;
      else
        size = `${(stats.size / (1024 * 1024 * 1024)).toFixed(2)} GB`;
      console.log(`${size} downloaded to ${localName}`); done(localFile);
    });
  })
}

/**
 * add some helpter for examples TS
 */

export const dataPath = getExampleDirname('..', '..', 'data');

// export const getDataFilePath = (fileName: string): string => {
//   const fullpath = path.resolve(dataPath, fileName)
//   return fullpath;
// };

export const getResourcePath = (name?: string): string => {
  const fullpath = path.resolve(dataPath, name || '.');
  return fullpath;
};

export const grabFrames = async (videoFile: number | string, kpDelay: number, onFrame: (mat: Mat, frameid: number) => void | Promise<void>): Promise<void> => {
  const cap = new cv.VideoCapture(videoFile);
  let done = false;
  let frameid = 0;
  //const intvl = setInterval(async () => {
  for (; ;) {
    let frame = cap.read();
    // loop back to start on end of stream reached
    if (frame.empty) {
      cap.reset();
      frame = cap.read();
    }
    frameid++;
    const p = onFrame(frame, frameid);
    if (p)
      await p;
    const key = cv.waitKey(kpDelay);
    done = key !== -1 && key !== 255;
    if (done) {
      //clearInterval(intvl);
      console.log('Key pressed, exiting.');
      return;
    }
     await delay(0);
  }
  //}, 0);
};

export const runVideoDetection = (src: number, detect: (mat: Mat) => void): void => {
  grabFrames(src, 1, frame => {
    detect(frame);
  });
};

export const drawRectAroundBlobs = (binaryImg: Mat, dstImg: Mat, minPxSize: number, fixedRectWidth?: number) => {
  const { centroids, stats } = binaryImg.connectedComponentsWithStats();

  // pretend label 0 is background
  for (let label = 1; label < centroids.rows; label += 1) {
    const [x1, y1] = [stats.at(label, cv.CC_STAT_LEFT), stats.at(label, cv.CC_STAT_TOP)];
    const [x2, y2] = [
      x1 + (fixedRectWidth || stats.at(label, cv.CC_STAT_WIDTH)),
      y1 + (fixedRectWidth || stats.at(label, cv.CC_STAT_HEIGHT)),
    ];
    const size = stats.at(label, cv.CC_STAT_AREA);
    const blue = new cv.Vec3(255, 0, 0);
    const thickness = 2;
    if (minPxSize < size) {
      dstImg.drawRectangle(
        new cv.Point2(x1, y1),
        new cv.Point2(x2, y2),
        blue,
        thickness,
      );
    }
  }
};
// drawRectangle(rect: Rect, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
export const drawRect = (image: Mat, rect: Rect, color: Vec3, opts = { thickness: 2 }): void =>
  image.drawRectangle(
    rect,
    color,
    opts.thickness,
    cv.LINE_8,
  );

const { HEADLESS } = process.env;

export async function wait4key(): Promise<'terminal' | 'window'> {
  if (HEADLESS) {
    await delay(100);
    return 'terminal';
  }
  // console.log('press a key to continue.');
  if (process.stdin.isTTY)
    process.stdin.setRawMode(true);
  process.stdin.resume();
  let done: 'terminal' | 'window' | null = null;
  const capture = (/*data: Buffer*/) => {
    // console.log({data})
    done = 'terminal';
  };
  process.stdin.on('data', capture);
  await delay(10);
  done = null;
  for (; ;) {
    await delay(10);
    if (~cv.waitKey(10)) {
      done = 'window';
      break;
    }
    if (done)
      break;
  }
  process.stdin.off('data', capture);
  process.stdin.pause();
  if (process.stdin.isTTY)
    process.stdin.setRawMode(false);
  return done;
}

/**
 * call cv.imshow() if HEADLESS is not set
 * else display image md5
 */
export function cv_imshow(winName: string, img: Mat): void {
  if (HEADLESS) {
    const md5sum = crypto.createHash('md5');
    const buffer = img.getData();
    md5sum.update(buffer)
    console.log(`display windows ${winName} MD5:${md5sum.digest('hex')}`);
  } else {
    return cv.imshow(winName, img);
  }
}

export function cv_setWindowProperty(winName: string, prop_id: number, prop_value: number): void {
  if (!HEADLESS) {
    return cv.setWindowProperty(winName, prop_id, prop_value);
  }
}

export const drawBlueRect = (image: Mat, rect: Rect, opts = { thickness: 2 }) =>
  drawRect(image, rect, new cv.Vec3(255, 0, 0), opts);
export const drawGreenRect = (image: Mat, rect: Rect, opts = { thickness: 2 }) =>
  drawRect(image, rect, new cv.Vec3(0, 255, 0), opts);
export const drawRedRect = (image: Mat, rect: Rect, opts = { thickness: 2 }) =>
  drawRect(image, rect, new cv.Vec3(0, 0, 255), opts);

