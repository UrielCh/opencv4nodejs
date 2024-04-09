import { expect } from 'chai';
import { getTestContext } from '../model';
import toTest from '../toTest';

if (toTest.objdetect) {
  const { cv } = getTestContext();
  it('should be constructable without args', () => {
    expect(new cv.DetectionROI()).to.be.instanceOf(cv.DetectionROI);
  });

  it('should set props', () => {
    const detectionROI = new cv.DetectionROI();
    const params = {
      scale: 1.5,
      locations: [new cv.Point2(0, 0), new cv.Point2(10, 0), new cv.Point2(0, 10)],
      confidences: [1.5, 2.5, 3.5],
    };

    Object.keys(params).forEach((param) => { (detectionROI as any)[param] = (params as any)[param]; });
    expect(detectionROI).to.have.property('scale').to.equal(params.scale);
    expect(detectionROI).to.have.property('locations')
      .to.be.an('array')
      .lengthOf(3)
      .to.deep.equal(params.locations);
    expect(detectionROI).to.have.property('confidences')
      .to.be.an('array')
      .lengthOf(3)
      .to.deep.equal(params.confidences);
  });
}
