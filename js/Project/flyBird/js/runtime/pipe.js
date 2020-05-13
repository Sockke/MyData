import Sprite from "../base/sprite";
import {utils} from '../base/utils';
import {canvasWidth, canvasHeight, getIsReady} from '../databus'


/**
 * 管道障碍物类
 */
export default class Pipe extends Sprite {
    constructor(img_down, img_up) {
        super();

        this.init();

        this.img_down = img_down;
        this.img_up = img_up;

        this.x1 = canvasWidth + Pipe.sideGap / 2;
        this.x2 = this.x1 + this.img_down.width + Pipe.sideGap;

        this.speed = 1.5;
        this.downTop1 = utils.random(Pipe.minTop, this.img_down.height);
        this.downTop2 = utils.random(Pipe.minTop, this.img_down.height);
    }

    init() {
        Pipe.minTop = canvasHeight / 8;
        Pipe.innerGap = canvasHeight / 6;
        Pipe.sideGap = canvasWidth / 1.5;
    }

    static minTop = null;
    // 上下管道之间的距离
    static innerGap = null;
    static sideGap = null;
    
    drawToCanvas(ctx) {
        // 管道的移动
        if (getIsReady()) {
            this.x1 = this.x1 - this.speed;
            this.x2 = this.x2 - this.speed;
        }

        if (this.x1 + this.img_down.width <= 0) {
            this.downTop1 = utils.random(Pipe.minTop, this.img_down.height);
            this.x1 = this.x2 + this.img_down.width + Pipe.sideGap;
        }
        if (this.x2 + this.img_down.width <= 0) {
            this.downTop2 = utils.random(Pipe.minTop, this.img_down.height);
            this.x2 = this.x1 + this.img_down.width + Pipe.sideGap;
        }
        
        ctx.drawImage(this.img_down, this.x1, this.downTop1 - this.img_down.height, this.img_down.width, this.img_down.height);
        ctx.drawImage(this.img_up, this.x1, this.downTop1 + Pipe.innerGap, this.img_up.width, canvasHeight/2);
        ctx.drawImage(this.img_down, this.x2, this.downTop2 - this.img_down.height, this.img_down.width, this.img_down.height);
        ctx.drawImage(this.img_up, this.x2, this.downTop2 + Pipe.innerGap, this.img_up.width, canvasHeight/2);
    }
}

