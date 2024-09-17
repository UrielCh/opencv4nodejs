import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';

describe('static Mat methods', () => {
  it('symbolicName', () => {
    // const version = cv.version;
    expect(cv.version.major).to.be.equal(4);
    // expect(4).to.be.equal(4);
  });
  it('core', () => {
    // const version = cv.version;
    expect(cv.modules.core).to.be.equal(true);
    // expect(4).to.be.equal(4);
  });
  it('NORM_INF', () => {
    expect(cv.NORM_INF).to.be.equal(1);
  });
  it('CV_8U', () => {
    expect(cv.CV_8U).to.be.equal(0);
  });
  it('alloc Mat', () => {
    const mat = new cv.Mat(2, 3, cv.CV_8U);
    expect(mat.rows).to.be.equal(2);
    expect(mat.cols).to.be.equal(3);
    expect(mat.type).to.be.equal(cv.CV_8U);
  });
});
