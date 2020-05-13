import Sprite from '../base/sprite'
import {canvasWidth, canvasHeight} from '../databus'


/**
 * 游戏背景类
 */


export default class BackGround extends Sprite {
    constructor(img) {
        super(img, 0, 0, canvasWidth, canvasHeight);
    }
}