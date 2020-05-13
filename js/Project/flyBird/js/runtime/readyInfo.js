/**
 * 游戏开始前的信息
 */

import Sprite from "../base/sprite";
import {canvasWidth, canvasHeight} from '../databus'

export default class ReadyInfo extends Sprite {
    constructor(img) {
        super(img, canvasWidth / 2 - img.width / 2, canvasHeight / 2 - img.height / 2, img.width, img.height);
    }

    drawToCanvas(ctx) {
        if (!this.visible) {
            return;
        }

        ctx.drawImage(this.img, this.x, this.y, this.width, this.height);
    }
}