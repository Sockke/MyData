/**
 * 简单的对象池
 */
export default class Pool {
    static instance() {
        if (!Pool._instance) {
            Pool._instance = new Pool();
        } 
        return Pool._instance;
    }

    constructor() {
        this._pool = new Map();
    }

    // 对象的引入
    add(key, value) {
        this._pool.set(key, value);
    }

    // 对象的引用
    get(key) {
        return this._pool.get(key);
    }

    // 对象的销毁
    remove(key) {
        if (!this._pool.has(key)) {
            this._pool[key] = null;  // 引用-1
            this._pool.delete(key);
        }
    }

    // 销毁所有对象
    destroyAll() {
        this._pool.forEach(value=> {
            value = null;
        })
    }
}