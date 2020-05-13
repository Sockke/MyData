/**
 * 游戏结束的信息
 */

import Sprite from "../base/sprite";
import {canvasWidth, canvasHeight} from '../databus'

export default class OverInfo extends Sprite {
    constructor(img) {
        super(img, canvasWidth / 2 - img.width / 2, canvasHeight / 2 - img.height / 2, img.width, img.height);
    }
}