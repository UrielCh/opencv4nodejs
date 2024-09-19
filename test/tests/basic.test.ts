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

  it('basic Mat', () => {
    const mat = new cv.Mat(1, 2, cv.CV_8U, 255);
    expect(mat.at(0, 0)).to.be.equal(255);
  });

  it('ones', () => {
    const expected = Buffer.alloc(4, 0).fill(1);
    const mat = cv.Mat.ones(2, 2, cv.CV_8U);
    expect(mat.cols).to.be.equal(2);
    expect(mat.rows).to.be.equal(2);
    // const buf: Buffer = mat.getData();
    // expect(buf).to.be.deep.equal(expected);
  });

});
