import Sprite from "../base/sprite";
import {canvasWidth, canvasHeight, getIsReady} from '../databus'

/**
 * 陆地类
 */

export default class Land extends Sprite {
    constructor(img) {
        super(img, 0, canvasHeight * 4/5, canvasWidth, canvasHeight / 5);

        this.speed = 1.5;
    }

    drawToCanvas(ctx) {
        if (!this.visible) {
            return;
        }
        // 游戏是否开始
        if (getIsReady()) {
            this.x = this.x - this.speed;
        }
        if (this.x + canvasWidth <= 0) {
            this.x = 0;
        }
        ctx.drawImage(this.img, this.x, this.y, this.width, this.height);
        ctx.drawImage(this.img, this.x + canvasWidth, this.y, this.width, this.height);
    }
}