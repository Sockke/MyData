export const utils = {
    random: (left, right)=> {
        let num = left + Math.random() * (right - left);
        return Math.floor(num);
    }
    /*
    //获取DPI, dpi(像素点/英寸)
    getDPI: function () {
        var arrDPI = new Array();
        if ( window.screen.deviceXDPI != undefined ) {
            arrDPI[0] = window.screen.deviceXDPI;
            arrDPI[1] = window.screen.deviceYDPI;
        }
        else {
            var tmpNode = document.createElement( "DIV" );
            tmpNode.style.cssText = "width:1in;height:1in;position:absolute;left:0px;top:0px;z-index:99;visibility:hidden";
            document.body.appendChild( tmpNode );
            arrDPI[0] = parseInt( tmpNode.offsetWidth );
            arrDPI[1] = parseInt( tmpNode.offsetHeight );
            tmpNode.parentNode.removeChild( tmpNode );
        }
        return arrDPI;
    },
    mmToPx: function(num) {
        const dpi = this.getDPI();
        // mm=(px/dpi)*25.4        px=(mm*dpi)/25.4
        const px = [];
        px.push(num * dpi[0] / 25.4);
        px.push(num * dpi[1] /25.4);
        return px;
    }
    */
};