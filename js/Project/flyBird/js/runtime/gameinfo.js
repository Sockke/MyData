/**
 * 小游戏的一些信息, 积分
 */

export default class GameInfo {
    constructor() {
        this.score = 0;
        this.flag = true; // 能否计分
    }

    renderGameScore(ctx, score) {
        this.score = score;

        ctx.font = '20px Arial';
        ctx.fillStyle = '#ffffff';
        ctx.fillText(
            this.score,
            10,
            30
        );
    }
}