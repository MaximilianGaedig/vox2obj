"use strict";
exports.__esModule = true;
var vox2obj = require('./build/Debug/vox2obj').vox2obj;
var fs = require('fs');
const vox = fs.readFileSync('test.vox');
const arrayVox = new Uint8Array(vox);
const obj = vox2obj(arrayVox);
fs.writeFileSync('test.obj', obj);
exports["default"] = vox2obj;
