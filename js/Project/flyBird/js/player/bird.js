import Sprite from "../base/sprite";
import Main, {canvasWidth, canvasHeight, getIsReady} from '../databus'

/**
 * fly bird 类
 */

// 裁剪信息
const sideGap = 9;
const innerGap = 18;
const birdWidth = 34;
const birdHeight = 24;
const upGap = 10;

export default class Bird extends Sprite {
    constructor(img) {
        super(img, canvasWidth / 4, canvasHeight / 2, img.width, img.height);
        
        // 小鸟裁剪的x, y
        this.birdsCropX = [sideGap, sideGap + birdWidth + innerGap, sideGap + 2 * birdWidth + 2 * innerGap];
        this.birdsCropY = [upGap, upGap, upGap];
        // 小鸟裁剪的宽高
        this.birdsWidth = [birdWidth, birdWidth, birdWidth];
        this.birdsHeight = [birdHeight, birdHeight, birdHeight];

        // 小鸟的下标
        this.index = 0;

        // 小鸟煽动翅膀的速度
        this.speed = 0.1;

        // 物理变量
        this.t = 0;  // 初始时间
        this.h = this.y;  // 初始高度
        this.v = -5;
    }

    drawToCanvas(ctx) {
        if (!this.visible) {
            return;
        }

        // 获取小鸟的下标
        this.index = this.index + this.speed;
        if (this.index >= this.birdsCropX.length) {
            this.index = 0;
        }
        const i = Math.floor(this.index);

        if (getIsReady()) {
            // 小鸟的自由落体
            const g = 9.8;
            const dh = this.v * this.t + 0.5 * g * this.t * this.t;  // 重新做自由落体时的平滑度需要在time上做手脚
            this.t += 1/60;

            this.y = this.h + dh * 22;  // mm与px中间有个换算, 正常换算的话值会很大
        }

        ctx.drawImage(this.img, 
            this.birdsCropX[i],
            this.birdsCropY[i],
            this.birdsWidth[i],
            this.birdsHeight[i],
            this.x,
            this.y,
            this.birdsWidth[i],
            this.birdsHeight[i]);
    }

    onTouch() {
        this.h = this.y;
        this.t = 0;
    }
}