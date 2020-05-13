export const canvas = wx.createCanvas();
export const ctx = canvas.getContext('2d');

// 屏幕的分辨率, 宽高
export const canvasWidth = canvas.width;
export const canvasHeight = canvas.height;

let isReady = false;

export function setIsReady(flag) {
  isReady = flag;
};

export  function getIsReady() {
  return isReady;
}