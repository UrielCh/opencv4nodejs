/* eslint-disable @typescript-eslint/no-explicit-any */
import { expect } from 'chai';
import { Mat, Point2, Point3 } from '@u4/opencv4nodejs';
import asyncHooks from 'async_hooks';
import { getTestContext } from '../model';
import {
  assertPropsWithValue,
  expectToBeVec2,
  expectToBeVec3,
  expectToBeVec4,
  funcShouldRequireArgs,
} from '../../utils/testUtils';
import { assertDataDeepEquals, assertMetaData } from '../../utils/matTestUtils';
import { generateAPITests } from '../../utils/generateAPITests';
import toTest from '../toTest';

// let asyncHooks = null;
// try {
//   asyncHooks = require('async_hooks');
// } catch (e) {
//   //
// }

if (toTest.core) {
  const args = getTestContext();
  const {
    cv,
    generateClassMethodTests,
    getNodeMajorVersion,
  } = args;

  const partitionTests = (createInstance: () => Point2) => {
    it('should return labels and numLabels', () => {
      const { labels, numLabels } = cv.partition([createInstance(), createInstance()], () => true);

      expect(labels).to.be.an('array').lengthOf(2);
      expect(numLabels).be.a('number');
    });

    it('should assign every point to same cluster', () => {
      const num = 5;
      const instances = Array(num).fill(0).map(() => createInstance());
      const { labels, numLabels } = cv.partition(instances, () => true);

      expect(numLabels).to.equal(1);
      expect(new Set(labels).size).to.equal(1);
    });

    it('should assign every point to different cluster', () => {
      const num = 5;
      const instances = Array(num).fill(0).map(() => createInstance());
      const { labels, numLabels } = cv.partition(instances, () => false);

      expect(numLabels).to.equal(num);
      expect(new Set(labels).size).to.equal(num);
    });
  };

  describe('getBuildInformation', () => {
    generateAPITests({
      getDut: () => cv,
      methodName: 'getBuildInformation',
      hasAsync: false,
      expectOutput: () => { /* empty */ },
    });
  });

  describe('partition', () => {
  // @ts-expect-error need args
    funcShouldRequireArgs(() => cv.partition());

    describe('Point2 input', () => {
      partitionTests(() => new cv.Point2(0, 0));
    });

    describe('Point3 input', () => {
      partitionTests(() => new cv.Point3(0, 0, 0));
    });

    describe('Vec2 input', () => {
    // @ts-ignore
      partitionTests(() => new cv.Vec2(0, 0));
    });

    describe('Vec3 input', () => {
    // @ts-ignore
      partitionTests(() => new cv.Vec3(0, 0, 0));
    });

    describe('Vec4 input', () => {
    // @ts-ignore
      partitionTests(() => new cv.Vec4(0, 0, 0, 0));
    });

    describe('Vec6 input', () => {
    // @ts-ignore
      partitionTests(() => new cv.Vec6(0, 0, 0, 0, 0, 0));
    });

    describe('Mat input', () => {
    // @ts-ignore
      partitionTests(() => new cv.Mat());
    });
  });

  describe('kmeans', () => {
  // @ts-expect-error kmeans constructor expect partameters
    funcShouldRequireArgs(() => cv.kmeans());
    const points2 = [
      [0, 0], [1000, 900], [-1000, -900], [-1100, -1000], [1100, 1000], [10, 10],
    ].map(([x, y]) => new cv.Point2(x, y));

    const k = 3;
    const termCriteria = new cv.TermCriteria(cv.termCriteria.COUNT, 100, 0.8);
    const attempts = 10;
    const flags = cv.KMEANS_RANDOM_CENTERS;

    it('should return labels and centers', () => {
      const ret = cv.kmeans(points2, k, termCriteria, attempts, flags);

      expect(ret).to.have.property('labels').to.be.an('array').lengthOf(6);
      expect(ret).to.have.property('centers').to.be.an('array').lengthOf(k);
    });

    it('should return correct labels', () => {
      const ret = cv.kmeans(points2, k, termCriteria, attempts, flags);

      const l0 = ret.labels[0];
      const l1 = ret.labels[1];
      const l2 = ret.labels[2];
      expect(ret.labels).to.have.ordered.members([l0, l1, l2, l2, l1, l0]);
    });

    it('should return correct centers', () => {
      const ret = cv.kmeans(points2, k, termCriteria, attempts, flags);

      const l0 = ret.labels[0];
      const l1 = ret.labels[1];
      const l2 = ret.labels[2];
      expect(ret.centers[l0].x).to.equal(5);
      expect(ret.centers[l0].y).to.equal(5);
      expect(ret.centers[l1].x).to.equal(1050);
      expect(ret.centers[l1].y).to.equal(950);
      expect(ret.centers[l2].x).to.equal(-1050);
      expect(ret.centers[l2].y).to.equal(-950);
    });

    // related to https://github.com/justadudewhohacks/opencv4nodejs/issues/379
    const points3: Point3[] = [
      [255, 0, 0], [255, 0, 0], [255, 0, 255], [255, 0, 255], [255, 255, 255],
    ].map(([x, y, z]) => new cv.Point3(x, y, z));

    it('should return correct centers with Point3', () => {
    // TODO check Typescript error
      const ret = cv.kmeans(points3, k, termCriteria, attempts, flags) as { labels: number[], centers: Point3[] };

      const l0 = ret.labels[0];
      const l1 = ret.labels[2];
      const l2 = ret.labels[4];
      expect(ret.centers[l0].x).to.equal(255);
      expect(ret.centers[l0].y).to.equal(0);
      expect(ret.centers[l0].z).to.equal(0);
      expect(ret.centers[l1].x).to.equal(255);
      expect(ret.centers[l1].y).to.equal(0);
      expect(ret.centers[l1].z).to.equal(255);
      expect(ret.centers[l2].x).to.equal(255);
      expect(ret.centers[l2].y).to.equal(255);
      expect(ret.centers[l2].y).to.equal(255);
    });
  });

  describe('cartToPolar', () => {
    const x = new cv.Mat([[0, 1, 100]], cv.CV_32F);
    const y = new cv.Mat([[0, 1, 100]], cv.CV_32F);
    const angleInDegrees = true;

    const expectOutput = (res: { magnitude: Mat, angle: Mat }) => {
      expect(res).to.have.property('magnitude').to.be.instanceOf(cv.Mat);
      expect(res).to.have.property('angle').to.be.instanceOf(cv.Mat);
      assertMetaData(res.magnitude)(1, 3, cv.CV_32F);
      assertMetaData(res.angle)(1, 3, cv.CV_32F);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'cartToPolar',
      getRequiredArgs: () => ([
        x, y,
      ]),
      getOptionalArg: () => angleInDegrees,
      expectOutput,
    });
  });

  describe('polarToCart', () => {
    const magnitude = new cv.Mat([[0, 1, 100]], cv.CV_32F);
    const angle = new cv.Mat([[0, Math.PI / 2, Math.PI]], cv.CV_32F);
    const angleInDegrees = true;

    const expectOutput = (res: { x: Mat | number[]; y: Mat | number[]; }) => {
      expect(res).to.have.property('x').to.be.instanceOf(cv.Mat);
      expect(res).to.have.property('y').to.be.instanceOf(cv.Mat);
      assertMetaData(res.x)(1, 3, cv.CV_32F);
      assertMetaData(res.y)(1, 3, cv.CV_32F);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'polarToCart',
      getRequiredArgs: () => ([
        magnitude, angle,
      ]),
      getOptionalArg: () => angleInDegrees,
      expectOutput,
    });
  });

  describe('getNumThreads', () => {
    it('should return the number of threads that used by OpenCV', () => {
      expect(cv.getNumThreads()).to.be.an('number');
    });
  });

  describe('setNumThreads', () => {
    it('should try to set the number of threads that used by OpenCV', () => {
      const number = 2;
      cv.setNumThreads(number);
    // OpenCV will **try** to set the number of threads for the
    // next parallel region so that `cv.getNumThreads()` don't react
    // to this immediately.
    // expect(cv.getNumThreads()).to.be.equal(number);
    });

    it('should throw when the argument is not integer', () => {
      const expectError = (fn: { (): void; (): void; (): void; }, msg: string) => {
        let err;
        try {
          fn();
        } catch (e) {
          err = e;
        }

        expect(err).to.be.equal(msg);
      };

      expectError(
      // @ts-expect-error expected argument 0 to be of type int
        () => cv.setNumThreads('hello'),
        'Core::SetNumThreads - Error: expected argument 0 to be of type int',
      );
      expectError(
        () => cv.setNumThreads(1.1),
        'Core::SetNumThreads - Error: expected argument 0 to be of type int',
      );
    });
  });

  describe('GetThreadNum', () => {
    it('should returns the index of the currently executed thread', () => {
      expect(cv.getThreadNum()).to.be.an('number');
    });
  });

  describe('class constructor call', () => {
    it('should throw errors if we call a constructor without "new"', () => {
      let err;

      try {
      // @ts-expect-error must be call with new keyword
        cv.Mat();
      } catch (e) {
        err = e;
      }

      expect(err).to.be.equal('Mat::New - constructor has to be called with "new" keyword');
    });
  });

  if (asyncHooks && getNodeMajorVersion() > 8) {
    describe('async_hooks', () => {
      it('should trigger `init` callback in async_hooks', () => {
        let typeFound = false;
        const hook = asyncHooks.createHook({
        // eslint-disable-next-line no-unused-vars, @typescript-eslint/no-unused-vars
          init: (_asyncId, type, _triggerAsyncId, _resource) => {
            if (type.indexOf('opencv4nodejs') === 0) {
              typeFound = true;
              hook.disable();
            }
          },
        });
        hook.enable();

        const createInstance = () => new cv.Point2(0, 0);
        const num = 5;
        const instances = Array(num).fill(0).map(() => createInstance());
        // eslint-disable-next-line no-unused-vars
        // const { labels, numLabels } =
        cv.partition(instances, () => true);
        expect(typeFound).to.be.equal(true);
      });
    });
  }

  describe('addWeighted', () => {
    const expectOutput = (res: { getDataAsArray: () => any; }) => {
      assertDataDeepEquals([
        [120, 140, 160],
        [180, 200, 220],
      ], res.getDataAsArray());
    };

    const alpha = 1;
    const beta = 0.5;
    const gamma = 100;

    const mat1 = new cv.Mat([
      [10, 20, 30],
      [40, 50, 60],
    ], cv.CV_8U);
    const mat2 = new cv.Mat([
      [20, 40, 60],
      [80, 100, 120],
    ], cv.CV_8U);

    generateClassMethodTests({
      getClassInstance: () => mat1,
      methodName: 'addWeighted',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      getRequiredArgs: () => ([
        alpha,
        mat2,
        beta,
        gamma,
      ]),
      expectOutput,
    });
  });

  describe('minMaxLoc', () => {
    const mat = new cv.Mat([
      [0.1, 0.2, 0.3],
      [0.4, 0.5, 0.6],
    ], cv.CV_64F);

    const mask = new cv.Mat([
      [0, 1, 1],
      [1, 1, 0],
    ], cv.CV_8U);

    const expectOutput = (res: { minVal: number; maxVal: number; minLoc: { x: number, y: number }; maxLoc: { x: number, y: number }; }, dut: any, args2: any[]) => {
      if (!args2.some((arg: Mat) => arg === mask)) {
      // without mask
        expect(res.minVal).to.equal(0.1);
        expect(res.maxVal).to.equal(0.6);
        assertPropsWithValue(res.minLoc, { x: 0, y: 0 });
        assertPropsWithValue(res.maxLoc, { x: 2, y: 1 });
      } else {
      // with mask
        expect(res.minVal).to.equal(0.2);
        expect(res.maxVal).to.equal(0.5);
        assertPropsWithValue(res.minLoc, { x: 1, y: 0 });
        assertPropsWithValue(res.maxLoc, { x: 1, y: 1 });
      }
    };

    generateClassMethodTests({
      getClassInstance: () => mat,
      methodName: 'minMaxLoc',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      getOptionalArg: () => mask,
      expectOutput,
    });
  });

  describe('findNonZero', () => {
    const expectOutput = (res: Point2[]) => {
      expect(res).to.be.an('array').lengthOf(3);
    };

    const mat = new cv.Mat([
      [1, 0, 1],
      [0, 1, 0],
    ], cv.CV_8U);

    generateClassMethodTests({
      getClassInstance: () => mat,
      methodName: 'findNonZero',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      expectOutput,
    });
  });

  describe('countNonZero', () => {
    const expectOutput = (res: number) => {
      expect(res).to.be.a('number').to.equal(3);
    };

    const mat = new cv.Mat([
      [1, 0, 1],
      [0, 1, 0],
    ], cv.CV_8U);

    generateClassMethodTests({
      getClassInstance: () => mat,
      methodName: 'countNonZero',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      expectOutput,
    });
  });

  describe('split', () => {
    const mat = new cv.Mat(4, 3, cv.CV_8UC3);
    const expectOutput = (res: Array<Mat | number[]>) => {
      expect(res).to.be.an('array').lengthOf(3);
      res.forEach((channel: Mat | number[]) => assertMetaData(channel)(mat.rows, mat.cols, cv.CV_8U));
    };

    generateClassMethodTests({
      getClassInstance: () => mat,
      methodName: 'split',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      expectOutput,
    });
  });

  describe('mulSpectrums', () => {
    const mat = new cv.Mat([
      [0.9, 0.9, 0, 0],
      [0.9, 0, -0.9, -0.9],
      [-0.9, 0, 0.9, -0.9],
      [0.9, 0, -0.9, 0],
    ], cv.CV_64F);

    const expectOutput = (res: Mat | number[]) => {
      assertMetaData(res)(mat.rows, mat.cols, cv.CV_64F);
    };

    const flags = 0;

    generateClassMethodTests({
      getClassInstance: () => mat,
      methodName: 'mulSpectrums',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      getRequiredArgs: () => ([
        mat,
        flags,
      ]),
      getOptionalArgsMap: () => ([
        ['conjB', true],
      ]),
      expectOutput,
    });
  });

  describe('transform', () => {
    const mat = cv.Mat.eye(3, 3, cv.CV_64FC3);
    const expectOutput = (res: number | { rows: number; cols: number; type: number; }) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(mat)(res);
    };

    describe('transform', () => {
      const M = cv.Mat.eye(3, 3, cv.CV_64F);

      generateClassMethodTests({
        getClassInstance: () => mat,
        methodName: 'transform',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getRequiredArgs: () => [M],
        expectOutput,
      });
    });

    describe('perspectiveTransform', () => {
      const M = cv.Mat.eye(4, 4, cv.CV_64F);

      generateClassMethodTests({
        getClassInstance: () => mat,
        methodName: 'perspectiveTransform',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getRequiredArgs: () => [M],
        expectOutput,
      });
    });
  });

  describe('sum', () => {
    describe('C1', () => {
      const src = new cv.Mat([
        [0.5, 0.5],
        [0.5, 0.5],
      ], cv.CV_64F);

      generateClassMethodTests({
        getClassInstance: () => src,
        methodName: 'sum',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        expectOutput: (res) => {
          expect(res).to.equal(2);
        },
      });
    });

    describe('C2', () => {
      const src = new cv.Mat([
        [[0.5, 1.5], [0.5, 1.5]],
        [[0.5, 1.5], [0.5, 1.5]],
      ], cv.CV_64FC2);

      generateClassMethodTests({
        getClassInstance: () => src,
        methodName: 'sum',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        expectOutput: (res) => {
          expectToBeVec2(res);
          expect(res.x).to.equal(2);
          expect(res.y).to.equal(6);
        },
      });
    });

    describe('C3', () => {
      const src = new cv.Mat([
        [[0.5, 1.5, 2.5], [0.5, 1.5, 2.5]],
        [[0.5, 1.5, 2.5], [0.5, 1.5, 2.5]],
      ], cv.CV_64FC3);

      generateClassMethodTests({
        getClassInstance: () => src,
        methodName: 'sum',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        expectOutput: (res) => {
          expectToBeVec3(res);
          expect(res.x).to.equal(2);
          expect(res.y).to.equal(6);
          expect(res.z).to.equal(10);
        },
      });
    });

    describe('C4', () => {
      const src = new cv.Mat([
        [[0.5, 1.5, 2.5, 3.5], [0.5, 1.5, 2.5, 3.5]],
        [[0.5, 1.5, 2.5, 3.5], [0.5, 1.5, 2.5, 3.5]],
      ], cv.CV_64FC4);

      generateClassMethodTests({
        getClassInstance: () => src,
        methodName: 'sum',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        expectOutput: (res) => {
          expectToBeVec4(res);
          expect(res.w).to.equal(2);
          expect(res.x).to.equal(6);
          expect(res.y).to.equal(10);
          expect(res.z).to.equal(14);
        },
      });
    });
  });

  describe('convertScaleAbs', () => {
    const srcMat = new cv.Mat([
      [0.5, 0.5],
      [0.5, 0.5],
    ], cv.CV_64F);

    generateClassMethodTests({
      getClassInstance: () => srcMat,
      methodName: 'convertScaleAbs',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      getOptionalArgsMap: () => ([
        ['alpha', 0.5],
        ['beta', 0.5],
      ]),
      expectOutput: (res) => {
        expect(srcMat).to.be.instanceOf(cv.Mat);
        assertMetaData(res)(srcMat.rows, srcMat.cols, cv.CV_8U);
      },
    });
  });

  describe('mean', () => {
    const mask = new cv.Mat(1, 2, cv.CV_8U, 255);
    describe('C1', () => {
      const matData = [
        [0.5, 1],
      ];

      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(matData, cv.CV_32FC1),
        methodName: 'mean',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getOptionalArg: () => mask,
        expectOutput: (res) => {
          expect(res.at(0)).to.eq(0.75);
        },
      });
    });

    describe('C2', () => {
      const matData = [
        [[0.5, 0.5], [1, 1.5]],
      ];

      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(matData, cv.CV_32FC2),
        methodName: 'mean',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getOptionalArg: () => mask,
        expectOutput: (res) => {
          expect(res.at(0)).to.eq(0.75);
          expect(res.at(1)).to.eq(1);
        },
      });
    });

    describe('C3', () => {
      const matData = [
        [[0.5, 0.5, 0.5], [1, 1.5, 2.5]],
      ];

      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(matData, cv.CV_32FC3),
        methodName: 'mean',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getOptionalArg: () => mask,
        expectOutput: (res) => {
          expect(res.at(0)).to.eq(0.75);
          expect(res.at(1)).to.eq(1);
          expect(res.at(2)).to.eq(1.5);
        },
      });
    });

    describe('C4', () => {
      const matData = [
        [[0.5, 0.5, 0.5, 0.5], [1, 1.5, 2.5, 3.5]],
      ];

      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(matData, cv.CV_32FC4),
        methodName: 'mean',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getOptionalArg: () => mask,
        expectOutput: (res) => {
          expect(res.at(0)).to.eq(0.75);
          expect(res.at(1)).to.eq(1);
          expect(res.at(2)).to.eq(1.5);
          expect(res.at(3)).to.eq(2);
        },
      });
    });
  });

  describe('meanStdDev', () => {
    const mask = new cv.Mat(20, 20, cv.CV_8U, 255);
    generateClassMethodTests({
      getClassInstance: () => new cv.Mat(20, 20, cv.CV_32F, 0.5),
      methodName: 'meanStdDev',
      classNameSpace: 'Mat',
      methodNameSpace: 'Core',
      getOptionalArg: () => mask,
      expectOutput: (res) => {
        expect(res).to.have.property('mean').to.be.instanceOf(cv.Mat);
        expect(res).to.have.property('stddev').to.be.instanceOf(cv.Mat);
      },
    });
  });

  describe('reduce', () => {
    const makeTest = (dim: number, rtype: number, dtype: number, expectedResults: number[][]) => () => {
      const rows = 1;
      const cols = 3;
      const type = cv.CV_8UC1;
      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(rows, cols, type, [1]), // was [[1]]
        methodName: 'reduce',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getRequiredArgs: () => ([dim, rtype, dtype]),
        // eslint-disable-next-line no-unused-vars
        expectOutput: (res) => {
          expect(res).to.be.instanceOf(cv.Mat);
          expect(res.getDataAsArray()).to.eql(expectedResults);
        },
      });
    };

    describe('Column sum', makeTest(0, cv.REDUCE_SUM, cv.CV_32F, [[1, 1, 1]]));
    describe('Column average', makeTest(0, cv.REDUCE_AVG, cv.CV_32F, [[1, 1, 1]]));
    describe('Column max', makeTest(0, cv.REDUCE_MAX, -1, [[1, 1, 1]]));
    describe('Column min', makeTest(0, cv.REDUCE_MIN, -1, [[1, 1, 1]]));

    describe('Row sum', makeTest(1, cv.REDUCE_SUM, cv.CV_32F, [[3]]));
    describe('Row average', makeTest(1, cv.REDUCE_AVG, cv.CV_32F, [[1]]));
    describe('Row max', makeTest(1, cv.REDUCE_MAX, -1, [[1]]));
    describe('Row min', makeTest(1, cv.REDUCE_MIN, -1, [[1]]));
  });

  describe('eigen', () => {
    const makeTest = (values: number[][] | number[][][] | number[][][][], expectedResults: number[][]) => () => {
      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(values, cv.CV_32F),
        methodName: 'eigen',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        // eslint-disable-next-line no-unused-vars
        expectOutput: (res: Mat) => {
          expect(res).to.be.instanceOf(cv.Mat);
          const arrayRes = res.getDataAsArray();
          const tolerance = 1e-6;
          arrayRes.forEach((r: number[], i1: number) => {
            r.forEach((n: number, i2: number) => {
              expect(n).to.be.at.least(expectedResults[i1][i2] - tolerance);
              expect(n).to.be.at.most(expectedResults[i1][i2] + tolerance);
            });
          });
        },
      });
    };

    describe('eigen', makeTest([[2, 1], [1, 2]], [[3], [1]]));
  });

  describe('solve', () => {
    const makeTest = (values1: number[][] | number[][][] | number[][][][], values2: number[][] | number[][][] | number[][][][], flags: number, expectedResults: number[][]) => () => {
      const m2 = new cv.Mat(values2, cv.CV_32F);

      generateClassMethodTests({
        getClassInstance: () => new cv.Mat(values1, cv.CV_32F),
        methodName: 'solve',
        classNameSpace: 'Mat',
        methodNameSpace: 'Core',
        getOptionalArgsMap: () => ([
          ['flags', flags],
        ]),
        getRequiredArgs: () => ([m2]),
        // eslint-disable-next-line no-unused-vars
        expectOutput: (res: Mat) => {
          expect(res).to.be.instanceOf(cv.Mat);
          const arrayRes = res.getDataAsArray();
          const tolerance = 1e-6;
          arrayRes.forEach((r: number[], i1: number) => {
            r.forEach((n: number, i2: number) => {
              expect(n).to.be.at.least(expectedResults[i1][i2] - tolerance);
              expect(n).to.be.at.most(expectedResults[i1][i2] + tolerance);
            });
          });
        },
      });
    };

    describe('Solve y = x equation on Id = X Id', makeTest([[1, 0, 0], [0, 1, 0], [0, 0, 1]], [[1, 0, 0], [0, 1, 0], [0, 0, 1]], cv.DECOMP_LU, [[1, 0, 0], [0, 1, 0], [0, 0, 1]]));
    describe('Solve y = x equation on Id = X Id', makeTest([[1, 2], [3, 4]], [[5, 6], [7, 8]], cv.DECOMP_LU, [[-3, -4], [4, 5]]));
  });

  describe('magnitude', () => {
    const x = new cv.Mat([[2, 0], [0, -2]], cv.CV_32F);
    const y = new cv.Mat([[0, 1], [-1, 0]], cv.CV_32F);

    const expectOutput = (res: Mat) => {
      expect(res).to.be.instanceOf(cv.Mat);
      // Yields: [[2, 1],[1, 2]]
      expect(res.at(0, 0)).to.equal(2);
      expect(res.at(0, 1)).to.equal(1);
      expect(res.at(1, 1)).to.equal(2);
    };

    generateAPITests({
      getDut: () => cv,
      hasAsync: true,
      methodName: 'magnitude',
      getRequiredArgs: () => ([
        x, y,
      ]),
      expectOutput,
    });
  });
}
