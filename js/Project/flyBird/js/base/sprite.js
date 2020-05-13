/**
 * 游戏精灵类, 游戏中所有元素的基类
 */

export default class Sprite {
    constructor(img = '', 
    x = 0, y = 0, width = 0, height = 0) {
        // 图片对象
        this.img = img;

        // 图片的位置
        this.x = x;
        this.y = y;

        // 图片的宽高
        this.width = width;
        this.height = height;

        // 图片是否显示
        this.visible = true;
    }

    /**
     * 将精灵元素绘制在canvas上
     */
    drawToCanvas(ctx) {
        if (!this.visible) {
            return;
        }

        // 先加载, 后绘制
        ctx.drawImage(this.img, this.x, this.y, this.width, this.height);
    }

    setVisiable(isVisiable) {
        this.visible = isVisiable;
    }
}