import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';

process.env.OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING = '1';

describe('External Memory Tracking', () => {
  it('should be disabled if OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING is set', () => {
    /* we can not require cv before OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING is set */
    // process.env.OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING = 1;
    // const cv = requireCv();
    expect(cv.isCustomMatAllocatorEnabled()).to.be.false;
  });
});
