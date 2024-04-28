// # This code is written at BigVision LLC. It is based on the OpenCV project. It is subject to the license terms in the LICENSE file found in this distribution and at http://opencv.org/license.html

import mri from "mri";
import fs from "fs";
import path from "path";
import assert from 'assert';
import { cv } from "../utils";
import { Net, Mat, VideoCapture, VideoWriter, Size, Point2, Vec3, Rect } from '@u4/opencv4nodejs';

// # Usage example:  python3 object_detection_yolo.py --video=run.mp4
// #                 python3 object_detection_yolo.py --image=bird.jpg

// import cv2 as cv
// import argparse
// import sys
// import numpy as np
// import os.path

//  Initialize the parameters
const conf = {
    confThreshold: 0.5,//  #Confidence threshold
    nmsThreshold: 0.4,//  #Non-maximum suppression threshold
}
const inpWidth = 416;//  #608     #Width of network's input image
const inpHeight = 416;// #608     #Height of network's input image

const args: { image?: string, video?: string, device?: string, help?: boolean } = mri(process.argv.slice(2), { default: { device: 'cpu' }, alias: { h: 'help' } });

if (args.help) {
    console.log('Object Detection using YOLO in OPENCV');
    console.log('--device Device to perform inference on \'cpu\' or \'gpu\'. (default is cpu)');
    console.log('--image  Path to image file.');
    console.log('--video  Path to video file.');
    process.exit(0);
}

// Load names of classes
const classesFile = "classes.names";

const classes = fs.readFileSync(classesFile, { encoding: 'utf8' }).trim().split(/\n/g);

//  Give the configuration and weight files for the model and load the network using them.

const modelConfiguration = path.join(__dirname, 'darknet-yolov3.cfg');
const modelWeights = path.join(__dirname, 'weights', 'darknet-yolov3_final.weights'); // "/data-ssd/sunita/snowman/darknet-yolov3_final.weights";

const net = cv.readNetFromDarknet(modelConfiguration, modelWeights)
if (args.device == "cpu") {
    net.setPreferableBackend(cv.DNN_TARGET_CPU)
    console.log("Using CPU device")
} else if (args.device == "gpu") {
    net.setPreferableBackend(cv.DNN_BACKEND_CUDA)
    net.setPreferableTarget(cv.DNN_TARGET_CUDA)
    console.log("Using GPU device")
}

// Get the names of the output layers
function getOutputsNames(net: Net): string[] {
    // Get the names of all the layers in the network
    const layersNames = net.getLayerNames()
    // Get the names of the output layers, i.e. the layers with unconnected outputs
    const outLayersIds = net.getUnconnectedOutLayers();
    return outLayersIds.map(i => layersNames[i]).filter(a => a);
    // return [layersNames[i[0] - 1] for i in net.getUnconnectedOutLayers()]
}
// Draw the predicted bounding box
function drawPred(frame: Mat, classId: number, conf: number, left: number, top: number, right: number, bottom: number) {
    // Draw a bounding box.
    let color = new Vec3(255, 178, 50);
    color = new Vec3(0, 255, 0);
    frame.drawRectangle(new Point2(left, top), new Point2(right, bottom), color, 3)
    // 
    let label = conf.toFixed(2);
    //         
    // Get the label for the class name and its confidence
    if (classes) {
        assert.ok(classId < classes.length)
        label = `${classes[classId]}:${label}`;
    }
    //Display the label at the top of the bounding box
    const { size, baseLine } = cv.getTextSize(label, cv.FONT_HERSHEY_SIMPLEX, 0.5, 1)
    top = Math.max(top, size.height);
    // drawRectangle(pt0: Point2, pt1: Point2, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
    const pt0 = new Point2(left, top - Math.round(1.5 * size.height));
    const pt1 = new Point2(left + Math.round(1.5 * size.width), top + baseLine);
    frame.drawRectangle(pt0, pt1, new Vec3(0, 0, 255), cv.FILLED)
    // #cv.rectangle(frame, (left, top - round(1.5*labelSize[1])), (left + round(1.5*labelSize[0]), top + baseLine),    (255, 255, 255), cv.FILLED)
    frame.putText(label, new Point2(left, top), cv.FONT_HERSHEY_SIMPLEX, 0.75, new Vec3(0, 0, 0), 2)
}

// Remove the bounding boxes with low confidence using non-maxima suppression
function postprocess(frame: Mat, outs: Mat[]) {
    const frameHeight = frame.sizes[0] // 1024
    const frameWidth = frame.sizes[1] // 1024

    const classIds: number[] = []
    const confidences: number[] = []
    const boxes = []
    // Scan through all the bounding boxes output from the network and keep only the
    // ones with high confidence scores. Assign the box's class label as the class with the highest score.
    for (const out of outs) {
        console.log(`Mat Type is ${cv.toMatTypeName(out.type)} Dim: ${out.sizes}`);
        // (4) [1, 512, 13, 13]
        // (4) [1, 256, 26, 26]
        const datas = out.getDataAsArray();
        for (const detection of datas) { // failed returning NaN...
            // scores = detection[5:]
            const scores = detection.slice(5);

            // classId = np.argmax(scores)
            // confidence = scores[classId]
            let classId = -1;
            let confidence = 0;
            for (let i = 0; i < scores.length; i++) {
                if (scores[i] > confidence) {
                    confidence = scores[i];
                    classId = i;
                }
            }
            if (detection[4] > conf.confThreshold) {
                console.log(`${detection[4]} - ${scores[classId]} - th : ${conf.confThreshold}`)
                console.log(detection);
            }
            if (confidence > conf.confThreshold) {
                const [cx, cy, w, h] = detection;
                const center_x = Math.round(cx * frameWidth)
                const center_y = Math.round(cy * frameHeight)
                const width = Math.round(w * frameWidth)
                const height = Math.round(h * frameHeight)
                const left = Math.round(center_x - width / 2)
                const top = Math.round(center_y - height / 2)
                classIds.push(classId)
                confidences.push(confidence)
                boxes.push(new Rect(left, top, width, height))
            }
        }
        // Perform non maximum suppression to eliminate redundant overlapping boxes with
        // lower confidences.
        const indices = cv.NMSBoxes(boxes, confidences, conf.confThreshold, conf.nmsThreshold)
        for (const i of indices) {
            // i = i[0]
            const box = boxes[i]
            const left = box.x
            const top = box.y
            const width = box.width
            const height = box.height
            drawPred(frame, classIds[i], confidences[i], left, top, left + width, top + height)
            //drawPred(classIds[i], confidences[i], left, top, left + width, top + height)
        }
    }
}

function main() {
    // Process inputs
    const winName = 'Deep learning object detection in OpenCV'
    cv.namedWindow(winName, cv.WINDOW_NORMAL)
    let outputFile = "yolo_out_py.avi"

    let cap: VideoCapture;
    if (args.image) {
        // Open the image file
        if (!fs.existsSync(args.image)) {
            console.error("Input image file ", args.image, " doesn't exist")
            process.exit(1)
        }
        cap = new cv.VideoCapture(args.image)
        outputFile = args.image.substring(0, args.image.length - 4) + '_yolo_out_py.jpg'
    } else if (args.video) {
        // Open the video file
        if (!fs.existsSync(args.video)) {
            console.error("Input video file ", args.video, " doesn't exist")
            process.exit(1)
        }
        cap = new cv.VideoCapture(args.video)
        outputFile = args.video.substring(0, args.video.length - 4) + '_yolo_out_py.avi'
    } else {
        // Webcam input
        cap = new cv.VideoCapture(0)
    }
    let vid_writer: VideoWriter | null = null;
    // Get the video writer initialized to save the output video
    if (!args.image) {
        const fps = 30;
        const frameSize = new cv.Size(cap.get(cv.CAP_PROP_FRAME_WIDTH), cap.get(cv.CAP_PROP_FRAME_HEIGHT));
        vid_writer = new VideoWriter(outputFile, VideoWriter.fourcc('MJPG'), fps, frameSize);
    }

    while (cv.waitKey(1) < 0) {
        // get frame from the video
        const frame: Mat = cap.read()

        // Stop the program if reached end of video
        if (!frame || frame.sizes.length === 0) {
            console.log("Done processing !!!")
            console.log("Output file is stored as ", outputFile)
            cv.waitKey(6000)
            // Release device
            cap.release()
            break
        }

        // Create a 4D blob from a frame.
        const size = new Size(inpWidth, inpHeight);
        const mean = new Vec3(0, 0, 0);
        const blob = cv.blobFromImage(frame, { scaleFactor: 1 / 255, size, mean, swapRB: true, crop: false })

        // Sets the input to the network
        net.setInput(blob)

        // Runs the forward pass to get output of the output layers
        const names = getOutputsNames(net);
        const outs: Mat[] = net.forward(names);
        // 
        // Remove the bounding boxes with low confidence
        postprocess(frame, outs)
        // 
        // Put efficiency information. The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers(in layersTimes)
        const { retval } = net.getPerfProfile()
        const label = `Inference time: ${(retval * 1000.0 / cv.getTickFrequency()).toFixed(2)} ms`
        frame.putText(label, new Point2(0, 15), cv.FONT_HERSHEY_SIMPLEX, 0.5, new Vec3(0, 0, 255))
        // 
        // Write the frame with the detection boxes
        if (vid_writer)
            vid_writer.write(frame) //  vid_writer.write(frame.astype(np.uint8))
        else
            cv.imwrite(outputFile, frame) // cv.imwrite(outputFile, frame.astype(np.uint8));
        cv.imshow(winName, frame)
    }
}

main();