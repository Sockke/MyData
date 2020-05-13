import BackGround from "./runtime/background";
import Land from "./runtime/land";
import ResourceLoader from "./base/resourceLoader";
import Pipe from './runtime/pipe';
import Pool from "./base/pool";
import Bird from "./player/bird";
import GameInfo from "./runtime/gameinfo";
import ReadyInfo from "./runtime/readyInfo";
import OverInfo from "./runtime/overInfo";

import {ctx} from './databus';
import {setIsReady, getIsReady} from './databus'

/**
 * 主类
 */
/*
const canvas = wx.createCanvas();
const ctx = canvas.getContext('2d');

// 屏幕的分辨率, 宽高
export const canvasWidth = canvas.width;
export const canvasHeight = canvas.height;
*/

export default class Main {
    constructor() {
        // 维护当前requestAnimationFrame的id
        this.aniId = 0;

        // 资源加载
        this.resourceLoader = new ResourceLoader();
        this.resourceLoader.onLoad(this.onLoading.bind(this));
        this.srcMap = null;
        this.audioMap = null;
    }

    // 游戏是否结束
    static isOver = false;

    // 加载
    onLoading(srcMap, audioMap) {
        this.srcMap = srcMap;
        this.audioMap = audioMap;
        this.onEvent();
        this.onInit();
    }

    // 初始化
    onInit() {
        Pool.instance().add('background', new BackGround(this.srcMap.get('background')));
        Pool.instance().add('text_ready', new ReadyInfo(this.srcMap.get('text_ready')));
        Pool.instance().add('land', new Land(this.srcMap.get('land')));
        Pool.instance().add('pipe', new Pipe(this.srcMap.get('pipe_down'), this.srcMap.get('pipe_up')));
        Pool.instance().add('bird', new Bird(this.srcMap.get('bird')));
        Pool.instance().add('gameInfo', new GameInfo());
        Pool.instance().add('text_over', new OverInfo(this.srcMap.get('text_over')));

        this.onRender();
    }

    // 渲染
    onRender() {
        this.onCollision();
        if (!Main.isOver) {
            Pool.instance().get('background').drawToCanvas(ctx);
            Pool.instance().get('pipe').drawToCanvas(ctx);
            Pool.instance().get('land').drawToCanvas(ctx);
            Pool.instance().get('bird').drawToCanvas(ctx);
            Pool.instance().get('gameInfo').renderGameScore(ctx, Pool.instance().get('gameInfo').score);

            Pool.instance().get('text_ready').drawToCanvas(ctx);

            this.aniId = requestAnimationFrame(this.onRender.bind(this));
        } else {
            this.audioMap.get('collision').play();
            //Pool.instance().get('text_over').drawToCanvas(ctx);
            cancelAnimationFrame(this.aniId);
            setIsReady(false);
            Pool.instance().destroyAll();
            wx.triggerGC();
        } 
    }

    // 绑定事件
    onEvent() {
        wx.onTouchStart(e=> {
            if (!getIsReady() && !Main.isOver) {
                setIsReady(true);
                Pool.instance().get('text_ready').setVisiable(false);
            } else if (!getIsReady() && Main.isOver) {
                Main.isOver = false;
                // 初始化
                this.onInit();
            } else {
                Pool.instance().get('bird').onTouch();
                this.audioMap.get('fly').play();
            }
        });
    }

    // 碰撞检测
    onCollision() {
        const bird_up_y = Pool.instance().get('bird').y;
        const bird_down_y = bird_up_y + Pool.instance().get('bird').birdsHeight[0];
        const bird_left_x = Pool.instance().get('bird').x;
        const bird_right_x =bird_left_x + Pool.instance().get('bird').birdsWidth[0];
        // 天空碰撞
        if (bird_up_y <= 0) {
            Main.isOver = true;
            return;
        }
        // 地板碰撞
        if (bird_down_y >= Pool.instance().get('land').y) {
            Main.isOver = true;
            return;
        } 
        // 管道碰撞
        const pipe_width = Pool.instance().get('pipe').img_down.width;
        const downTop1 = Pool.instance().get('pipe').downTop1;
        const downTop2 = Pool.instance().get('pipe').downTop2;
        const pipe_left_x1 = Pool.instance().get('pipe').x1;
        const pipe_right_x1 = pipe_left_x1 + pipe_width;
        const pipe_left_x2 = Pool.instance().get('pipe').x2;
        const pipe_right_x2 = pipe_left_x2 + pipe_width;
        if ((bird_right_x >= pipe_left_x1 && bird_left_x <= pipe_right_x1)
        && (bird_up_y <= downTop1 || bird_down_y >= downTop1 + Pipe.innerGap)) {
            Main.isOver = true;
            return;
        }
        if ((bird_right_x >= pipe_left_x2 && bird_left_x <= pipe_right_x2)
        && (bird_up_y <= downTop2 || bird_down_y >= downTop2 + Pipe.innerGap)) {
            Main.isOver = true;
            return;
        } 

        // 计分
        if (Pool.instance().get('gameInfo').flag
        && (bird_left_x > pipe_right_x1 || bird_left_x > pipe_right_x2)) {
            Pool.instance().get('gameInfo').flag = false;
            Pool.instance().get('gameInfo').score += 1; 
            this.audioMap.get('through').play();
            return;
        }
        if (!Pool.instance().get('gameInfo').flag
        && ((bird_right_x > pipe_left_x1 && bird_left_x < pipe_right_x1) 
        || (bird_right_x > pipe_left_x2 && bird_left_x < pipe_right_x2))) {
            Pool.instance().get('gameInfo').flag = true;
        }
    }
}
