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
});
