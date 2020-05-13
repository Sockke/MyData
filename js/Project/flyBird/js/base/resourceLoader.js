import {srcMap, audioMap} from './resource'

/**
 * 资源加载类
 */
export default class ResourceLoader {
    constructor() {
        this.srcMap = new Map(srcMap);
        this.srcMap.forEach((value, key)=> {
            const img = wx.createImage();
            img.src = value;
            this.srcMap.set(key, img);
        });
        this.audioMap = new Map(audioMap);
        this.audioMap.forEach((value, key)=> {
            const audio = wx.createInnerAudioContext();
            audio.src = value;
            this.audioMap.set(key, audio);
        });
    }

    // 资源加载
    onLoad(callback) {
        let loadCnt = 0;
        this.srcMap.forEach((value, key)=> {
            value.onload = ()=> {
                ++loadCnt;
                if (loadCnt >= this.srcMap.size) {
                    callback(this.srcMap, this.audioMap);
                }
            };
        });
    }
}